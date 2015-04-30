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
        std::pair<Date, std::vector<std::string> >* *array;

        void resize(int newSize);
        void findAndAdd(const std::pair<Date, std::vector<std::string> > &p, int);

    public:
        HashTable();
        ~HashTable();
        void add(Date, std::string);
        int hash(const Date &b) const;
        void resize();
};

#endif
