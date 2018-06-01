#include <map>
#include <iostream>

#include "Dictionary.h"

template<class K, class V>
class MapDictionary: public Dictionary<K, V> {
    public:
        // Add a given key, value pair to the dictionary.  If key is already
        // a key in the dictionary, REPLACE the associated value.
        void add(K key, V value) override {
			if (keyExists(key)) {			
				data[key] = value;
			}
			else {
				data.insert(make_pair(key,value));
			}
        }

        // Return the value associated with the given key.  If the key doesn't
        // exist, throws an exception of class DictionaryException
        V getValue(K key) const override {
			if (keyExists(key)) {
				return data.find(key)->second;
			}   
			throw DictionaryException("key does not exist...");     
		}

        // Return the key associated with the given value.  In the case where
        // multiple values are equal to the passed-in value, returning any
        // associated key is correct.  If no values are equal to value,
        // throws an exception of class DictionaryException.
        K getKey(V value) const  override {
			for (auto i:data) {
				if (i.second == value)
					return i.first;
			}
			throw DictionaryException("value not found...");
        }

        // Remove the given key and associated value from the dictionary.  In
        // the case where key doesn't exist, this function throws an exception
        // of class DictionaryException.
        void remove(K key) override {
			if(keyExists(key))
				data.erase(key);
			else 
				throw DictionaryException("key not in dictionary...");       
		}

        // Display the dictionary on standard output, indicating what keys are
        // associated with what values.  The order of keys can be in any order.
        void display() const override {
			for (auto i:data){
				std::cout << i.first << " " << i.second << std::endl;
			}
        }

        // Return the number of key-value pairs in this dictionary.
        int size() const override {
			return data.size();
        }

        // Returns true if the key exists and false otherwise.
        bool keyExists(K key) const override {
			auto ptr = data.find(key);
			if (ptr == data.end()) {
				return false;
			}
			else 
				return true;
        }
    private:
        // You are NOT allowed to add additional member variables.
        std::map<K, V> data;
};
