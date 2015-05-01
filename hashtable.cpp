#include "hashtable.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

HashTable::HashTable() {
    // cout << "setup" << endl;
    size = 0;
    tableSize = 11;

    // cout << "create array of pointers" << endl;
    array = new pair<Date, vector<string> >*[tableSize];

    // cout << "initialize all array values to null" << endl;
    for (int i = 0; i < tableSize; i++) {
        array[i] = NULL;
    }

    // read in primes to static array
    string line;
    ifstream file("primes.txt");
    if (file.is_open()) {
        for (int i = 0; getline(file, line); i++) {
            primes[i] = atoi(line.c_str());
        }
    }
}

HashTable::~HashTable() {
    delete[] array;
}

void HashTable::add(Date b, string name) {

    if (size > 0) {
        if ((size+1)/ (float) tableSize > 0.45f) {
            cout << "\n\n\nRESIZING ARRAY:" << endl;
            resize();
        }
    }

    cout << "hash the date object: " << b.toString() << " -> ";
    int hash = this->hash(b, tableSize);
    cout << hash << endl;

    // create pair
    vector<string> v;
    v.push_back(name);
    pair<Date, vector<string> > p(b, v);

    insert(p, array, hash, 1, tableSize);

    cout << "increment size: " << size;
    size++;
    cout << " -> " << size << endl;
}

void HashTable::insert(const pair<Date, vector<string> > &p,
                           std::pair<Date, std::vector<std::string> > **&arr,
                           int h, int i, int max) {

    // slot is empty
    if (arr[h] == NULL) {
        cout << "insert pair -> " << h << endl;
        arr[h] = new pair<Date, vector<string> >(p);
    } else {
        cout << "see if dates are the same" << endl;
        cout << arr[h]->first.equals(p.first) << endl;
        if(arr[h]->first.equals(p.first)) {
            cout << "add all the names from p to second" << endl;
            for(int j = 0; j < p.second.size(); j++)
                arr[h]->second.push_back(p.second[j]);
        }
        // if not the same dates
        else {
            cout << "try to add at different index" << endl;
            insert(p, arr, (h + 2*i) % max, i+1, max);
        }
    }
}

int HashTable::hash(const Date &b, int max) const {
    int hash = 13;

    hash += pow(b.getMonth() + 1, 3);
    hash += pow(b.getDay() + 1, 2);
    hash += pow(b.getYear(), 1);

    hash = hash % max;

    return hash;
}

void HashTable::resize() {
    cout << "iterate through primes" << endl;
    int i = 0;
    while ((size + 1) / (double) primes[i] > 0.45) i++;
    int newTableSize = primes[i];

    cout << "NEW TABLE SIZE: " << newTableSize << endl << endl;
    resize(newTableSize);
    tableSize = newTableSize;
}

void HashTable::resize(int newSize) {
    // keep temp array
    std::pair<Date, std::vector<std::string> > **temp = new pair<Date, vector<string> >*[newSize];

    // initialize temp pointers to null
    for (int i = 0; i < newSize; i++) { temp[i] = NULL; }

    // iterate through current array
    for (int i = 0; i < tableSize; i++) {
        // hash keys from current array and add to temp array
        if (array[i] != NULL) {
            cout << "hash current date at " << i << endl;
            int index = hash(array[i]->first, newSize);
            // insert into temp starting at index
            insert(*array[i], temp, index, 1, newSize);
        }
    }

    // delete array and point array to the temp array
    delete[] array;
    array = temp;
}

string toString() {
    return "";
}

int main() {
    HashTable h;

    Date a(1,1,2000);
    h.add(a,"Jared");

    Date b(2,1,2000);
    h.add(b, "Good");

    Date c(3,1,2000);
    h.add(c, "Joe");

    Date d(3,1,2000);
    h.add(d, "Julie");

    Date e(5,1,2000);
    h.add(e, "Kevin");

    Date f(6,1,2000);
    h.add(f, "Deb");

    Date g(7,1,2000);
    h.add(g, "Al");

    Date i(8,1,2000);
    h.add(i, "Mike");

    Date j(8,1,2000);
    h.add(j, "Bob");

    return 0;
}
