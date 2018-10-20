#include <stdio.h>

#include <ctime>
#include <chrono>
#include <functional>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

auto timeFunction = [](auto && F, auto && ... params) {
    auto start = high_resolution_clock::now();
    std::forward<decltype(F)>(F)
        (std::forward<decltype(params)>(params)...);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
};

class BenchmarkInterface {
    public:
    /*clock_t timing(void(BenchmarkInterface::*func)()) {
        clock_t start = clock();
        (*func)();
        return clock() - start;
    }*/
    virtual void iterate() = 0;
    virtual void insert() = 0;
    virtual void search() = 0;
    virtual void erase() = 0;

    // I know all of these are the same, but struggling with passing in class function pointers.
    auto timeIterate() {
        auto start = high_resolution_clock::now();
        iterate();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }
    auto timeInsert() {
        auto start = high_resolution_clock::now();
        insert();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }
    auto timeSearch() {
        auto start = high_resolution_clock::now();
        search();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }
    auto timeErase() {
        auto start = high_resolution_clock::now();
        erase();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }

    void run() {
        std::cout << "iterate: " << timeIterate() << std::endl;
        std::cout << "insert: " << timeInsert() << std::endl;
        std::cout << "search: " << timeSearch() << std::endl;
        std::cout << "erase: " << timeErase() << std::endl;
    }

    void repeat(string command, int times) {
        long int results[times];
        if(command == "iterate") {
            for(int i=0; i<times; i++) {
                results[i] = timeIterate();
            }
        }
        if(command == "insert") {
            for(int i=0; i<times; i++) {
                results[i] = timeInsert();
            }
        }
        if(command == "search") {
            for(int i=0; i<times; i++) {
                results[i] = timeSearch();
            }
        }
        if(command == "erase") {
            for(int i=0; i<times; i++) {
                results[i] = timeErase();
            }
        }

        cout << "Running " << command << " " << times << "times:" << endl;
        for(int i=0; i<times; i++) {
            cout << results[i] << endl;
        }
    }
};

class VectorBenchmark : public BenchmarkInterface {
    public:
    vector<long> testVector;
    long size;

    VectorBenchmark(long elements) {
        size = elements;
        testVector.resize(elements);
        std::generate(testVector.begin(),
                testVector.end(), 
                [max = elements]() {
                return (rand() % max);
                });
    }

    void iterate() {
        int count = 0;
        for(auto it=testVector.begin();
                it!= testVector.end();
                ++it) {
            count = *it;
        }
    }

    void insert() {
        testVector.push_back(-1);
    }

    void search() {
        long item = rand() % size;
        find(testVector.begin(), testVector.end(), item);
    }

    void erase() {
        long item = rand() % size;
        for(auto it=testVector.begin();
               it != testVector.end();
              ++it) {
           if(*it == item) {
              testVector.erase(it);
              break;
           }
        }
    } 

};

//class ListBenchmark : public BenchmarkIterface {
//};

class MapBenchmark : public BenchmarkInterface {
    public:
    std::map<int, int> testMap;

    MapBenchmark(long elements) {
        testMap[0] = 1;
        testMap[1] = 2;
    }
        


    void iterate() {
        int count = 0;
        for(std::map<int, int>::iterator it=testMap.begin();
                it!=testMap.end();
                ++it) {
            count = it->first;
        }
    }

    void insert() {
        testMap.insert(std::pair<int, int>(100, 100));
    }

};


//class SetBenchmark : public BenchmarkIterface {

//};
//



int main() {

    /*
     * inputs:
     *  number of elements
     *  percent iterate, insert, search, delete
     */
    
    VectorBenchmark v(100000);
    v.run();
    v.repeat("iterate", 100);

    return 0;
}
