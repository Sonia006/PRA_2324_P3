#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key);

    public:
        HashTable(int size);
	~HashTable();
	int capacity();
	V operator[](std::string key);
	template <typename U>
	friend std::ostream& operator<<(std::ostream &out, const HashTable<U> &th);

	void insert(std::string key, V value) override;
	V search(std::string key) override;
	V remove(std::string key) override;
	int entries() override;
        
};

template <typename V>
int HashTable<V>::h(std::string key){
	int suma = 0;
	for(int i = 0; i < key.size(); i++){
		suma = suma + int(key.at(i));
	}
	return suma % max;
}

template <typename V>
HashTable<V>::HashTable(int size){
	max = size;
	n = 0;
	table = new ListLinked<TableEntry<V>>[max];
}

template <typename V>
HashTable<V>::~HashTable(){
	delete[] table;
}

template <typename V>
int HashTable<V>::capacity(){
	return max;
}

template <typename V>
V HashTable<V>::operator[](std::string key){
	int k = h(key);
	for (int i = 0; i < table[k].size(); i++){
		TableEntry<V> entry = table[k].get(i);
		if(entry.key == key)
			return entry.value;
	}
	throw std::runtime_error("Clave no encontrada");
	
}

template <typename V>
std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
	for(int i = 0; i < th.max; i++){
		out << "Cubeta " << i << ": ";
		for(int j = 0; j < th.table[i].size(); j++){
			TableEntry<V> entry = th.table[i].get(j);
			out << "[" << entry.key << " -> " << entry.value << "] ";
		}
		out << "\n";
	}
	return out;
}

template <typename V>
void HashTable<V>::insert(std::string key, V value){
	int k = h(key);
        for (int i = 0; i < table[k].size(); i++){
        	TableEntry<V> entry = table[k].get(i);
		if(entry.key == key){
			throw std::runtime_error("Clave existente");
		}
	}
	TableEntry<V> nuevo(key, value);
    	table[k].insert(table[k].size(), nuevo);
    	n++;
}

template <typename V>
V HashTable<V>::search(std::string key){
	int k = h(key);
	for (int i = 0; i < table[k].size(); i++){
        	TableEntry<V> entry = table[k].get(i);
		if (entry.key = key)
			return entry->value;
	}
	throw std::runtime_error("Clave no encontrada");
}

template <typename V>
V HashTable<V>::remove(std::string key){
	int k = h(key);
	for (int i = 0; i < table[k].size(); i++){
		TableEntry<V> entry = table[k].get(i);
		if(entry.key == key){
			table[k].remove(i);
			n--;
			return;
		}
	}
	throw std::runtime_error("Clave no encontrada");
}

template <typename V>
int HashTable<V>::entries(){
	int count = 0;
        for(int i = 0; i < max; i++){
               	count+=table(i).size();
        }
        return count;
}

#endif
