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
        int find(const Date &, int, int) const;
        int find(const Date &) const;

    public:
        HashTable();
        ~HashTable();
        std::vector<std::string> getNames(const Date &) const;
        int getSize() { return size; }
        void add(Date, std::string);
        int hash(const Date &, int max) const;
        void resize();
};

#endif
