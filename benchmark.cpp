#include <stdio.h>

#include <ctime>
#include <chrono>
#include <functional>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <list>
#include <set>
#include <numeric>

using namespace std;
using namespace std::chrono;

auto timeFunction = [](auto && F, auto && ... params) {
    auto start = high_resolution_clock::now();
    std::forward<decltype(F)>(F)
        (std::forward<decltype(params)>(params)...);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
};

long calcMean(vector<long int> vals) {
    auto sum = std::accumulate(vals.begin(), vals.end(), 0);
    return sum/vals.size();
}
long calcStddev(vector<long int> vals) {
    long int mean = calcMean(vals);
    std::vector<long int> diffs(vals.size());
    std::transform(vals.begin(), vals.end(), diffs.begin(),
            [mean](long int x){return x - mean;});
    auto sum = std::inner_product(diffs.begin(), diffs.end(), diffs.begin(), 0);
    return std::sqrt(sum/vals.size());
}

long calcMedian(vector<long int> vals) {
    std::nth_element(vals.begin(), vals.begin() + vals.size()/2, vals.end());
    return vals[vals.size()/2];
}

class BenchmarkInterface {
    public:
    /*clock_t timing(void(BenchmarkInterface::*func)()) {
        clock_t start = clock();
        (*func)();
        return clock() - start;
    }*/
    long size;
    long searchVal;
    virtual void iterate() = 0;
    virtual void insertSetup() = 0;
    virtual void insert() = 0;
    virtual void search() = 0;
    virtual void eraseSetup() = 0;
    virtual void erase() = 0;

    // I know all of these are the same, but struggling with passing in class function pointers.
    auto timeIterate() {
        auto start = high_resolution_clock::now();
        iterate();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }
    auto timeInsert() {
        insertSetup();
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
        eraseSetup();
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
        vector<long int> results(times);
        int warmup = 25;

        if(command == "iterate") {
            for(int i=0; i<warmup; i++) {
                timeIterate();
            }
            for(int i=0; i<times; i++) {
                results[i] = timeIterate();
            }
        }
        else if(command == "insert") {
            for(int i=0; i<warmup; i++) {
                timeInsert();
            }
            for(int i=0; i<times; i++) {
                results[i] = timeInsert();
            }
        }
        else if(command == "search") {
            for(int i=0; i<warmup; i++) {
                timeSearch();
            }
            for(int i=0; i<times; i++) {
                results[i] = timeSearch();
            }
        }
        else if(command == "erase") {
            for(int i=0; i<warmup; i++) {
                timeErase();
            }
            for(int i=0; i<times; i++) {
                results[i] = timeErase();
            }
        }

        cout << "Running " << command << " " << times << "times:" << endl;
        /*for(int i=0; i<times; i++) {
            cout << results[i] << endl;
        }*/
        cout << "Mean: " << calcMean(results) << endl;
        cout << "Median: " << calcMedian(results) << endl;
        cout << "Stddev: " << calcStddev(results) << endl;

    }
};

class VectorBenchmark : public BenchmarkInterface {
    public:
    vector<long> testVector;
    vector<long> tmpVector;

    VectorBenchmark(long elements) {
        size = elements;
        testVector.resize(elements);
        std::generate(testVector.begin(),
                testVector.end(), 
                [max = elements]() {
                return (rand() % max);
                });
        searchVal = rand() % elements;
    }

    void iterate() {
        int count = 0;
        for(auto it=testVector.begin();
                it!= testVector.end();
                ++it) {
            count = *it;
        }
    }

    void insertSetup() {
        tmpVector = testVector;
    }
    void insert() {
        tmpVector.push_back(-1);
    }

    void search() {
        find(testVector.begin(), testVector.end(), searchVal);
    }

    void eraseSetup() {
        tmpVector = testVector;
    }
    void erase() {
        long item = rand() % size;
        for(auto it=tmpVector.begin();
               it != tmpVector.end();
              ++it) {
           if(*it == item) {
              tmpVector.erase(it);
              break;
           }
        }
    } 

};

class ListBenchmark : public BenchmarkInterface {
    public:
    std::list<long int> testList;
    std::list<long int> tmpList;

    ListBenchmark(long elements) {
        size = elements;
        testList.resize(elements);
        std::generate(testList.begin(),
                testList.end(), 
                [max = elements]() {
                return (rand() % max);
                });
        searchVal = rand() % elements;
    }

    void iterate() {
        long count = 0;
        for(auto it=testList.begin();
                it!= testList.end();
                ++it) {
            count = *it;
        }
    }

    void insertSetup() {
        tmpList = testList;
    }
    void insert() {
        tmpList.push_back(-1);
    }

    void search() {
        find(testList.begin(), testList.end(), searchVal);
    }

    void eraseSetup() {
        tmpList = testList;
    }
    void erase() {
        long item = rand() % size;
        for(auto it=tmpList.begin();
               it != tmpList.end();
              ++it) {
           if(*it == item) {
              tmpList.erase(it);
              break;
           }
        }
    } 


};

class MapBenchmark : public BenchmarkInterface {
    public:
    std::map<long, int> testMap;
    std::map<long, int> tmpMap;
    long searchVal;

    MapBenchmark(long elements) {
        size = elements;
        for(long i=0; i<size; i++) {
            testMap[i] = 1;
        }
        searchVal = rand() % size;
    }
        
    void iterate() {
        int count = 0;
        for(std::map<long, int>::iterator it=testMap.begin();
                it!=testMap.end();
                ++it) {
            count = it->first;
        }
    }

    void insertSetup() {
        tmpMap = testMap;
    }
    void insert() {
        tmpMap.insert(std::pair<long, int>(100, 100));
    }

    void search() {
        testMap.find(searchVal);
    }
    void eraseSetup() {
        tmpMap = testMap;
    }
    void erase() {
        tmpMap.erase(searchVal);
    }

};


class SetBenchmark : public BenchmarkInterface {
    public:
    std::set<long> testSet;
    std::set<long> tmpSet;
    long searchVal;

    SetBenchmark(long elements) {
        size = elements;
        for(long i=0; i<size; i++) {
            testSet.insert(i);
        }
        searchVal = rand() % size;
    }
        
    void iterate() {
        int count = 0;
        for(auto it=testSet.begin();
                it!=testSet.end();
                ++it) {
            count = *it;
        }
    }

    void insertSetup() {
        tmpSet = testSet;
    }
    void insert() {
        tmpSet.insert(100);
    }

    void search() {
        testSet.find(searchVal);
    }
    void eraseSetup() {
        tmpSet = testSet;
    }
    void erase() {
        tmpSet.erase(searchVal);
    }
};

void testBenchmark(BenchmarkInterface *b, int runs) {
    b->run();
    b->repeat("iterate", runs);
    b->repeat("search", runs);
    b->repeat("insert", runs);
    b->repeat("erase", runs);
}

int main(int argc, char* argv[]) {

    /*
     * inputs:
     *  number of elements
     *  percent iterate, insert, search, delete
     */
    
    VectorBenchmark v(pow(10, 6));
    testBenchmark(&v, 1000);

    return 0;
}
