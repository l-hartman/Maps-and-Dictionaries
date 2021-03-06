#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SimpleDictionary.h"
#include "MapDictionary.h"

// Number of elements to add to the test dictionary
const int NUM_ELEMENTS = 150;

std::string randomValue() {
    const int MIN_LEN = 1;
    const int MAX_LEN = 2;
    std::string ans;
    int len = rand() % (MAX_LEN - MIN_LEN + 1) + MIN_LEN;
    for (int i=0; i<len; i++) {
        char c = 'A';
        if (rand() % 2 == 0) {
            c = 'a';
        }
        ans += (c + rand() % 26);
    }
    return ans;
}

void runTest(const SimpleDictionary<std::string, std::string> &sd,
             const MapDictionary<std::string, std::string> &md) {
    assert(sd.size() == md.size());
    for (int i=0; i<sd.size(); i++) {
        auto key = sd.keyAtIndex(i);
        auto value = sd.getValue(key);
        assert(md.keyExists(key) == true);
        assert(md.getValue(key) == value);
        auto foundKey = md.getKey(value);
        assert(md.getValue(foundKey) == value);
        assert(sd.keyExists(foundKey));
        assert(sd.getValue(foundKey) == value);
    }

    for (int i=0; i<NUM_ELEMENTS * 10; i++) {
        auto k = randomValue();
        if (!sd.keyExists(k)) {
            assert(!md.keyExists(k));
            bool exceptSuccess = false;
            try {
                md.getValue(k);
            } catch (DictionaryException &e) {
                exceptSuccess = true;
            } catch (std::exception &e) {
                std::cerr << "Expected an exception of";
                std::cerr << " class DictionaryException" << std::endl;
                abort();
            }
            // Assert that the exception was properly thrown.
            assert(exceptSuccess);
            
        } else {
            assert(md.keyExists(k));
        }
    }
}

int main() {
    time_t seed = time(0);
    std::cerr << "Current seed: " << seed << std::endl;

    // change line below ("seed = seed;") to force seed to take on a
    // specific value.
    seed = seed;
    // Seed random number generator, and create our dictionaries.
    srand(seed);

    SimpleDictionary<std::string, std::string> sd(NUM_ELEMENTS * 2);
    MapDictionary<std::string, std::string> md;

    // Create the dictionary by adding a number of keys and values
    std::cerr << "Creating dictionary...";
    for (int i=0; i<NUM_ELEMENTS; i++) {
        auto k = randomValue();
        auto v = randomValue();
        if (sd.keyExists(k)) {
            std::cerr << "u";
        } else {
            std::cerr << "a";
        }
        sd.add(k, v);
        md.add(k, v);
        runTest(sd, md);
    }
    runTest(sd, md);

    std::cerr << "\nDone" << std::endl;
    
    for (int i=0; i<NUM_ELEMENTS * 10; i++) {
        auto k = randomValue();
        if (sd.keyExists(k)) {
            std::cerr << "Removing " << k << "...";
            md.remove(k);
            sd.remove(k);
            runTest(sd, md);
            std::cerr << "Done" << std::endl;
        } else {
            // If TEST_EXCEPTIONS, test to make sure remove() and getValue()
            // will throw exceptions when necessary.
            bool success = false;
            try {
                md.remove(k);
            } catch (DictionaryException &e) {
                success = true;
            } catch (std::exception &e) {
                std::cerr << "Expected an exception of";
                std::cerr << " class DictionaryException" << std::endl;
                abort();
            }
            // Assert that the DictionaryException was properly thrown
            // by remove().
            assert(success);
            success = false;
            try {
                md.getValue(k);
            } catch (DictionaryException &e) {
                success = true;
            } catch (std::exception &e) {
                std::cerr << "Expected an exception of";
                std::cerr << " class DictionaryException" << std::endl;
                abort();
            }
            // Assert that the DictionaryException was properly thrown
            // by getValue().
            assert(success);
        }
    }
    std::cerr << "Test successful!! :D" << std::endl;
}