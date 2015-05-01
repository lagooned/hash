#include "hashtable.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * default constructor
 */
HashTable::HashTable() {
    // setup
    size = 0;
    tableSize = 11;

    // create array of pointers
    array = new pair<Date, vector<string> >*[tableSize];

    // initialize all array values to null
    for (int i = 0; i < tableSize; i++) {
        array[i] = NULL;
    }

    // read in primes to array
    string line;
    ifstream file("primes.txt");
    if (file.is_open()) {
        for (int i = 0; getline(file, line); i++) {
            primes[i] = atoi(line.c_str());
        }
    }
}

/**
 * default destructor
 */
HashTable::~HashTable() {
    delete[] array;
}

/**
 * gets all the names associated with a date
 */
vector<string> HashTable::getNames(const Date &b) const {
    int index = find(b);

    if (index >= 0) {
        return array[find(b)]->second;
    } else {
        throw -1;
    }
}

/**
 * adds a date and a name to the hash table
 */
void HashTable::add(Date b, string name) {
    // possible resize
    if (size > 0) {
        if ((size+1)/ (float) tableSize > 0.45f) {
            resize();
        }
    }

    // hash the date object
    int hash = this->hash(b, tableSize);

    // create pair
    vector<string> v;
    v.push_back(name);
    pair<Date, vector<string> > p(b, v);

    insert(p, array, hash, 1, tableSize);

    // increment size
    size++;
}

/**
 * inserts a date=>name pair into the hash table
 */
void HashTable::insert(const pair<Date, vector<string> > &p,
                           std::pair<Date, std::vector<std::string> > **&arr,
                           int h, int i, int max) {
    // slot is empty
    if (arr[h] == NULL) {
        // insert pair
        arr[h] = new pair<Date, vector<string> >(p);

    } else {
        // see if dates are the same
        if(arr[h]->first.equals(p.first)) {
            // add all the names from p to second
            for(int j = 0; j < p.second.size(); j++)
                arr[h]->second.push_back(p.second[j]);
        }

        // if not the same dates
        else {
            // try to add at different index
            insert(p, arr, (h + 2*i) % max, i+1, max);
        }
    }
}

/**
 * finds the index of a given date
 */
int HashTable::find(const Date &b) const {
    // hash date in question
    int h = hash(b, tableSize);

    // get index recursively
    return find(b, h, 1);
}

/**
 * recursively searches for the index of a date
 */
int HashTable::find(const Date &b, int h, int i) const {
    // if this index is empty
    if (array[h] == NULL) {
        // the element can't be in the table
        return -1;
    } else {
        // see if the element here is b
        if (array[h]->first.equals(b)) {
            return h;
        } else {
            // quadratically find the next possible place
            find(b, (h + 2*i) % tableSize, i + 1);
        }
    }
}

/**
 * produces a hash for a given date where 0 < hash < max
 */
int HashTable::hash(const Date &b, int max) const {
    int hash = 13;

    hash += pow(b.getMonth() + 1, 3);
    hash += pow(b.getDay() + 1, 2);
    hash += pow(b.getYear(), 1);

    hash = hash % max;

    return hash;
}

/**
 * resizes the hash array to the next appropriate prime
 */
void HashTable::resize() {
    // iterate through primes
    int i = 0;
    while ((size + 1) / (double) primes[i] > 0.45) i++;

    // find new table size
    int newTableSize = primes[i];
    resize(newTableSize);
    tableSize = newTableSize;
}

/**
 * resizes the array to newSize
 */
void HashTable::resize(int newSize) {
    // keep temp array
    std::pair<Date, std::vector<std::string> > **temp =
                                    new pair<Date, vector<string> >*[newSize];

    // initialize temp pointers to null
    for (int i = 0; i < newSize; i++) { temp[i] = NULL; }

    // iterate through current array
    for (int i = 0; i < tableSize; i++) {
        // hash keys from current array and add to temp array
        if (array[i] != NULL) {
            // hash current date at i
            int index = hash(array[i]->first, newSize);
            // insert into temp starting at index
            insert(*array[i], temp, index, 1, newSize);
        }
    }

    // delete array and point array to the temp array
    delete[] array;
    array = temp;
}

/**
 * MAIN USER INTERFACE
 */
int main() {
    // init hash table
    HashTable h;

    // read in csv
    string line;
    ifstream file("randomNames.csv");
    if (file.is_open()) {
        while (getline(file, line)) {
            int day = 0;
            int month = 0;
            int year = 0;

            // separate name and date
            int comma = line.find(",");
            string name = line.substr(0, comma);
            string date = line.substr(comma+1, line.length());

            // get day
            int firstSlash = date.find("/");
            string strDay = date.substr(0, firstSlash);
            day = atoi(strDay.c_str());

            // get month
            int secondSlash = date.find("/", firstSlash + 1);
            string strMonth = date.substr(firstSlash + 1, secondSlash);
            month = atoi(strMonth.c_str());

            // get year
            string strYear = date.substr(secondSlash + 1, date.length());
            year = atoi(strYear.c_str());

            // add anonymous date (doesn't matter it's copied into hash table)
            h.add(Date(month, day, year), name);
        }
    }

    // init vars
    int day = 0;
    int month = 0;
    int year = 0;

    // prompt user
    cout << "Input date to search: " << endl;

    // get day
    cout << "day => ";
    cin >> day;

    // get month
    cout << "month => ";
    cin >> month;

    // get year
    cout << "year => ";
    cin >> year;

    cout << endl;

    // if valid date
    if (day > 0 && day < 32
        && month > 0 && month < 13
        && year > 0) {

        try {
            // retrieve names
            vector<string> v = h.getNames(Date(month, day, year));

            cout << "Birthdays on this day: " << endl;
            cout << "----------------------- " << endl;

            // print out names
            for (int i = 0; i < v.size(); i++) {
                cout << v[i] << endl;
            }

        } catch(int e) {
            cout << "No birthdays found!" << endl;
        }
    }

    else {
        cout << "Invalid date, exiting...";
        return -1;
    }

    return 0;
}
