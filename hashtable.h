#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "date.h"
#include <utility>
#include <string>
#include <vector>

class HashTable {
    private:
        int size;
        int tableSize;
        std::pair<Date, std::vector<std::string> > **array;
        int primes[3244];

        void resize(int newSize);
        void insert(const std::pair<Date, std::vector<std::string> > &,
            std::pair<Date, std::vector<std::string> > **&, int, int, int);

    public:
        HashTable();
        ~HashTable();
        int getSize() { return size; }
        void add(Date, std::string);
        int hash(const Date &b, int max) const;
        void resize();
        std::string toString();
};

#endif
