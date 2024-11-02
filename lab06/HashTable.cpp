// CSCI 311 - Spring 2023
// Lab 6 - Hash Table cpp
// Author: Colin Jamison

#include "HashTable.h"

#include <math.h>

#include <iostream>

HashTable::HashTable() : size(11), p(31) { this->table.reserve(11); }

HashTable::HashTable(int s, int mult) {
    this->size = s;
    this->p = mult;
    this->table.reserve(s);
}

int HashTable::getSize() { return this->size; }
int HashTable::getNumElements() { return this->numElements; }
int HashTable::getP() { return this->p; }

void HashTable::printTable() {
    std::cout << "HASH TABLE CONTENTS" << std::endl;
    for (int i = 0; i < table.size(); i++) {
        if (table[i].size() > 0) {
            std::cout << i << ": ";
            for (int j = 0; j < table[i].size() - 1; j++) {
                std::cout << table[i][j] << ", ";
            }
            std::cout << table[i][table[i].size() - 1] << std::endl;
        }
    }
}

int HashTable::search(std::string s) {
    int hash = HashTable::hash(s);
    int idx = -1;

    for (int i = 0; i < this->table[hash].size(); i++) {
        if (this->table[hash][i] == s) {
            idx = i;
        }
    }

    return idx;
}

void HashTable::insert(std::string s) {
    int hash = HashTable::hash(s);
    this->table[hash].push_back(s);
    this->numElements++;
}

void HashTable::remove(std::string s) {}

void HashTable::resize(int s) {}

int HashTable::hash(std::string s) {
    unsigned int hash = 0;
    for (int i = 0; i < s.length(); i++) {
        hash += (int)s[i] * std::pow(this->p, i);
    }

    return hash % this->size;
}