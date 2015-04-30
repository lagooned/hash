#include "hashtable.h"
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

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
    // resize before adding
    if (size + 1 / (float) tableSize < 0.45f) {
        resize();
    }

    // hash the date object
    int hash = this->hash(b);

    // create pair in here and pass it to
    vector<string> v;
    v.push_back(name);
    pair<Date, vector<string> > p(b, v);

    insert(p, array, hash);

    // increment size
    size++;

    // p is destroyed but a copy of p is left
    // in memory due to dynamic allocation
    // in the helper method
}

void HashTable::insert(const pair<Date, vector<string> > &p,
                           std::pair<Date, std::vector<std::string> > **&arr,
                           int i) {

    // slot is empty
    if (arr[i] == NULL) {
        // add pair via copy
        arr[i] = new pair<Date, vector<string> >(p);
    } else {
        // see if dates are the same
        if(arr[i]->first.equals(p.first)) {
            // add all the names from p to second
            for(int j = 0; j < p.second.size(); j++)
                arr[i]->second.push_back(p.second[j]);
        }
        // if not the same dates
        else {
            // try to add at different index using quad probing
            insert(p, arr, (int)pow(i, 2) % tableSize);
        }
    }
}

int HashTable::hash(const Date &b) const {
    int hash = 13;

    hash += pow(b.getMonth(), 1);
    hash += pow(b.getDay(), 2);
    hash += pow(b.getYear(), 3);

    hash = hash % tableSize;

    return hash;
}

void HashTable::resize() {
    // iterate through primes
    int i = 0;
    while ( size / (float) primes[i] < 0.45f) i++;
    int newTableSize;
    resize(primes[i] = newTableSize);
    tableSize = newTableSize;
}

void HashTable::resize(int newSize) {
    // keep temp array
    std::pair<Date, std::vector<std::string> > **temp = new pair<Date, vector<string> >*[newSize];
    // iterate through current array
    for (int i = 0; i < size; i++) {
        // hash keys and add to temp array
        if (array[i] != NULL) {
            // hash current date at i
            int index = hash(array[i]->first);
            // insert into temp starting at index
            insert(*array[i], temp, index);
        }
    }

    // delete array and point array to the temp array
    delete[] array;
    array = temp;
}
