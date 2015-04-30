#include "hashtable.h"
#include <cmath>

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

    // TODO: create pair in here and pass it to
    vector<string> v;
    v.push_back(name);

    pair<Date, vector<string> > p(b, v);
    findAndAdd(p, hash);

    // increment size
    size++;

    // p is destroyed but a copy of p is left
    // in memory due to dynamic allocation
    // in the helper method
}

// TODO: make this take a pair and i instead
void HashTable::findAndAdd(const pair<Date, vector<string> > &p, int i) {
    // slot is empty
    if (array[i] == NULL) {
        // add pair via copy
        array[i] = new pair<Date, vector<string> >(p);
    } else {
        // see if dates are the same
        if(array[i]->first.equals(p.first)) {
            // add all the names from p to second
            for(int j = 0; j < p.second.size(); j++)
                array[i]->second.push_back(p.second[j]);
        }
        // if not the same dates
        else {
            // try to add at different index using quad probing
            findAndAdd(p, (int)pow(i, 2) % tableSize);
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
    // until size/prime < 0.45
    // resize(prime)
    // tableSize = prime;
}

void HashTable::resize(int newSize) {
    // keep temp array
    // iterate through current array
}
