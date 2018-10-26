#include <stdio.h>
#include <stdlib.h>

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
#include <unordered_set>
#include <numeric>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

int WARMUP = 25;

double calcMean(vector<float> vals) {
    auto sum = std::accumulate(vals.begin(), vals.end(), 0);
    return sum/vals.size();
}
double calcStddev(vector<float> vals) {
    double mean = calcMean(vals);
    std::vector<float> diffs(vals.size());
    std::transform(vals.begin(), vals.end(), diffs.begin(),
            [mean](float x){return x - mean;});
    auto sum = std::inner_product(diffs.begin(), diffs.end(), diffs.begin(), 0);
    return std::sqrt(sum/(vals.size()));
}

double calcMedian(vector<float> vals) {
    std::nth_element(vals.begin(), vals.begin() + vals.size()/2, vals.end());
    return vals[vals.size()/2];
}

class BenchmarkInterface {
    public:
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
        return duration_cast<nanoseconds>(stop - start).count();
    }
    auto timeInsert() {
        insertSetup();
        auto start = high_resolution_clock::now();
        insert();
        auto stop = high_resolution_clock::now();
        return duration_cast<nanoseconds>(stop - start).count();
    }
    auto timeSearch() {
        auto start = high_resolution_clock::now();
        search();
        auto stop = high_resolution_clock::now();
        return duration_cast<nanoseconds>(stop - start).count();
    }
    auto timeErase() {
        eraseSetup();
        auto start = high_resolution_clock::now();
        erase();
        auto stop = high_resolution_clock::now();
        return duration_cast<nanoseconds>(stop - start).count();
    }

    void run() {
        std::cout << "iterate: " << timeIterate() << std::endl;
        std::cout << "insert: " << timeInsert() << std::endl;
        std::cout << "search: " << timeSearch() << std::endl;
        std::cout << "erase: " << timeErase() << std::endl;
    }

    void warmupIterate() {
	for(int i=0; i<WARMUP; i++) {
	    timeIterate();
	}
    }

    void warmupSearch() {
	for(int i=0; i<WARMUP; i++) {
	    timeSearch();
	}
    }

    void warmupInsert() {
	for(int i=0; i<WARMUP; i++) {
	    timeInsert();
	}
    }

    void warmupErase() {
	for(int i=0; i<WARMUP; i++) {
	    timeErase();
	}
    }

    void repeat(string command, int times) {
        vector<float> results(times);

        if(command == "iterate") {
	    warmupIterate();
            for(int i=0; i<times; i++) {
                results[i] = timeIterate();
            }
        }
        else if(command == "insert") {
	    warmupInsert();
            for(int i=0; i<times; i++) {
                results[i] = timeInsert();
            }
        }
        else if(command == "search") {
            warmupSearch();
            for(int i=0; i<times; i++) {
                results[i] = timeSearch();
            }
        }
        else if(command == "erase") {
            warmupErase();
            for(int i=0; i<times; i++) {
                results[i] = timeErase();
            }
        }

        cout << "Running " << command << " " << times << "times:" << endl;
        /*for(int i=0; i<times; i++) {
            cout << results[i] << endl;
        }*/
        //cout << "Mean: " << calcMean(results) << endl;
        //cout << "Median: " << calcMedian(results) << endl;
        //cout << "Stddev: " << calcStddev(results) << endl;
        cout<<calcMean(results)<<"\t"<<calcMedian(results)<<"\t"<<calcStddev(results)<<endl;
    }


    auto simulateWorkload(int num_runs, 
            double percent_iterate,
            double percent_search,
            double percent_insert,
            double percent_erase) {
        long total_time=0;

        //cout<<"Iterate"<<endl;
	    warmupIterate();
        for(int i=0; i<(int)(num_runs*percent_iterate); i++) {
            auto t = timeIterate();
            total_time += t;
            //cout<<t<<endl;
        }

        //cout<<"Insert"<<endl;
	    warmupInsert();
        for(int i=0; i<(int)(num_runs*percent_insert); i++) {
            auto t = timeInsert();
            total_time += t;
            //cout<<t<<endl;
        }

        //cout<<"Search"<<endl;
        warmupSearch();
        for(int i=0; i<(int)(num_runs*percent_search); i++) {
            auto t = timeSearch();
            total_time += t;
            //cout<<t<<endl;
        }

        //cout<<"Erase"<<endl;
        warmupErase();
        for(int i=0; i<(int)(num_runs*percent_erase); i++) {
            auto t = timeErase();
            total_time += t;
            //cout<<t<<endl;
        }
        return total_time;

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
        tmpVector.push_back(rand() % size);
    }

    void search() {
        find(testVector.begin(), testVector.end(), rand() % size);
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
        tmpList.push_back(rand() % size);
    }

    void search() {
        find(testList.begin(), testList.end(), rand() % size);
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
        tmpMap.insert(std::pair<long, int>(rand() % size, 100));
    }

    void search() {
        testMap.find(rand() % size);
    }
    void eraseSetup() {
        tmpMap = testMap;
    }
    void erase() {
        tmpMap.erase(rand() % size);
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
        tmpSet.insert(rand() % size);
    }

    void search() {
        testSet.find(rand() % size);
    }
    void eraseSetup() {
        tmpSet = testSet;
    }
    void erase() {
        tmpSet.erase(rand() % size);
    }
};

class UnorderedSetBenchmark : public BenchmarkInterface {
    public:
    std::unordered_set<long> testSet;
    std::unordered_set<long> tmpSet;
    long searchVal;

    UnorderedSetBenchmark(long elements) {
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
        tmpSet.insert(rand() % size);
    }

    void search() {
        testSet.find(rand() % size);
    }
    void eraseSetup() {
        tmpSet = testSet;
    }
    void erase() {
        tmpSet.erase(rand() % size);
    }
};

void testBenchmark(BenchmarkInterface *b, int runs) {
    //b->run();
    
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
    
    if(argc <= 3) {
        cout << "Args:"<< endl <<
            "  -p size(power) (default 6)" << endl <<
            "  -n number_of_times_to_repeat (default 100)" <<endl <<
            "  -I percent iterate (as decimal) " << endl <<
            "  -N percent insert" << endl <<
            "  -S percent search" << endl <<
            "  -D percent delete" << endl;
        return 1;
    }
    int opt;
    int num_pow = 6;
    int num_runs = 100;
    double iterate = 0;
    double insert = 0;
    double search = 0;
    double erase = 0;
    while ((opt = getopt(argc, argv, "p:n:I:N:S:D:")) != -1) {
        switch(opt) {
            case 'p':
                num_pow = atoi(optarg);
                break;
            case 'n':
                num_runs = atoi(optarg);
                break;
            case 'I':
                iterate = atof(optarg);
                break;
            case 'N':
                insert = atof(optarg);
                break;
            case 'S':
                search = atof(optarg);
                break;
            case 'D':
                erase = atof(optarg);
                break;
        }
    }
    int size = pow(10, num_pow);


    VectorBenchmark v(size);
    auto t = v.simulateWorkload(num_runs, iterate, search, insert, erase);
    auto v_t = t/num_runs;
    cout<<"vector: "<<v_t<<endl;
    auto fastest = v_t;
    string winner = "vector";

    ListBenchmark l(size);
    t = l.simulateWorkload(num_runs, iterate, search, insert, erase);
    auto l_t = t/num_runs;
    cout<<"list: "<<l_t<<endl;
    if(l_t < fastest) {
        winner = "list";
    }

    MapBenchmark m(size);
    t = m.simulateWorkload(num_runs, iterate, search, insert, erase);
    auto m_t = t/num_runs;
    cout<<"map: "<<m_t<<endl;
    if(m_t < fastest) {
        winner = "map";
    }

    SetBenchmark s(size);
    t = s.simulateWorkload(num_runs, iterate, search, insert, erase);
    auto s_t = t/num_runs;
    cout<<"set: "<<s_t<<endl;
    if(s_t < fastest) {
        winner = "set";
    }

    UnorderedSetBenchmark us(size);
    t = us.simulateWorkload(num_runs, iterate, search, insert, erase);
    auto us_t = t/num_runs;
    cout<<"unordered set: "<<us_t<<endl;
    if(us_t < fastest) {
        winner = "unordered set";
    }

    //cout <<v_t<<"\t"<<l_t<<"\t"<<m_t<<"\t"<<s_t<<"\t"<<us_t<<endl;

    cout << "Winner: " << winner <<endl;
/*
    cout << "Vector" << endl;
    VectorBenchmark v(size);
    testBenchmark(&v, num_runs);

    cout << "List" << endl;
    ListBenchmark l(size);
    testBenchmark(&l, num_runs);

    cout << "Map" << endl;
    MapBenchmark m(size);
    testBenchmark(&m, num_runs);

   cout << "Set" << endl;
    SetBenchmark s(size);
    testBenchmark(&s, num_runs);

    cout << "Unordered Set" << endl;
    UnorderedSetBenchmark us(size);
    testBenchmark(&us, num_runs);
*/
    return 0;
}
