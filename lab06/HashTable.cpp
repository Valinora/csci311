// CSCI 311 - Spring 2023
// Lab 6 - Hash Table cpp
// Author: Colin Jamison

#include "HashTable.h"

#include <math.h>

#include <iostream>

HashTable::HashTable() : size(11), p(31), numElements(0) { this->table.resize(11); }

HashTable::HashTable(int s, int mult) {
    this->size = s;
    this->p = mult;
    this->numElements = 0;
    this->table.resize(s);
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

    for (int i = 0; i < this->table[hash].size(); i++) {
        if (this->table[hash][i] == s) {
            return hash;
        }
    }

    return -1;
}

void HashTable::insert(std::string s) {
    int hash = HashTable::hash(s);

    if (this->table[hash].size() == 0) {
        this->table[hash] = std::vector<std::string>();
    }

    this->table[hash].push_back(s);
    this->numElements++;
}

void HashTable::remove(std::string s) {
    int hash = HashTable::hash(s);
    int idx = HashTable::search(s);

    if (idx != -1) {
        for (int i = 0; i < this->table[hash].size(); i++) {
            if (this->table[hash][i] == s) {
                this->table[hash].erase(this->table[hash].begin() + i);
                this->numElements--;
                break;
            }
        }
    }
}

void HashTable::resize(int s) {
    std::vector<std::vector<std::string>> newTable;
    newTable.resize(s);

    for (const auto& bucket : this->table) {
        for (const auto& item : bucket) {
            int hash = HashTable::hash(item, s);

            if (newTable[hash].size() == 0) {
                newTable[hash] = std::vector<std::string>();
            }

            newTable[hash].emplace_back(item);
        }
    }

    this->table = std::move(newTable);
    this->size = s;
}

int HashTable::hash(std::string s, int tableSize) {
    unsigned int hash = 0;
    for (int i = 0; i < s.length(); i++) {
        hash += (int)s[i] * std::pow(this->p, i);
    }

    return hash % tableSize;
}

int HashTable::hash(std::string s) { return HashTable::hash(s, this->size); }