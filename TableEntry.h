#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
        std::string key;
	V value;

	TableEntry(std::string key, V value);
	TableEntry(std::string key);
	TableEntry();
	template <typename U>
	friend bool operator==(const TableEntry<U> &te1, const TableEntry<U> &te2);
	template <typename U>
	friend bool operator!=(const TableEntry<U> &te1, const TableEntry<U> &te2);
	template <typename U>
	friend std::ostream& operator<<(std::ostream &out, const TableEntry<U> &te);
};

template <typename V>
TableEntry<V>::TableEntry(std::string key, V value){
	this->key = key;
	this->value = value;	
}

template <typename V>
TableEntry<V>::TableEntry(std::string key){
	this->key = key;
	this->value = V();
}

template <typename V>
TableEntry<V>::TableEntry(){
	this->key = "";
	this->value = V();
}

template <typename V>
bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
	return te1.key == te2.key;
}

template <typename V>
bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
	return te1.key != te2.key;
}

template <typename V>
std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
	out << "Clave-> [ " << te.key << ", " << te.value << " ]";
	return out;
}

#endif
