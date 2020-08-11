#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <string>

#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>


class X1 {
public:

    std::string name;
    int age;
    float weight;

    long references;

    X1(std::string n, int a, float w) : name(n), age(a), weight(w), references(0) {}
};


class X2 {
public:
    std::string name;
    int age;
    float weight;

    X2(std::string n, int a, float w) : name(n), age(a), weight(w) {}
};


inline void intrusive_ptr_add_ref(X1* x) {
    ++x->references;
}


inline void intrusive_ptr_release(X1* x) {
    if (--x->references == 0)
        delete x;
}


int main()
{
    size_t arrsize = 10000000;
    size_t loop_array_count = 200;

    std::chrono::duration<double> dur;

    // /*
    std::shared_ptr<X2>** arr_sharedptrs = new std::shared_ptr<X2>*[arrsize];

    for (size_t i = 0; i < arrsize; i++) {
        arr_sharedptrs[i] = new std::shared_ptr<X2> (new X2("Dilbert", 40, 188.8));
    }

    auto start = std::chrono::system_clock::now();

    for(size_t i = 0; i < loop_array_count; i++) {
        for (size_t j = 0; j < arrsize; j++) {
            (*arr_sharedptrs[j])->age++;
            (*arr_sharedptrs[j])->weight += 0.1f;
        }
    }

    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to iterate over " << arrsize << " objects managed by std::shared_ptr, " << loop_array_count
              << " times over: " << dur.count() << "seconds" << std::endl;

    // */


    /*

    boost::intrusive_ptr<X1>** arr_boostptrs = new boost::intrusive_ptr<X1>*[arrsize];

    // store pointers
    for (size_t i = 0; i < arrsize; i++) {
        arr_boostptrs[i] = new boost::intrusive_ptr<X1> (new X1("Dilbert", 40, 188.8));
    }

    auto start = std::chrono::system_clock::now();

    for (size_t i = 0; i < loop_array_count; i++) {
        for(size_t j = 0; j < arrsize; j++)
        {
            // boost::intrusive_ptr<X1> myX(new X1("Dilbert", 40, 188.8));
            (*arr_boostptrs[j])->age++;
            (*arr_boostptrs[j])->weight += 0.1f;
        }
    }

    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to iterate over " << arrsize << " objects managed by boost::intrusive_ptr, " << loop_array_count
              << " times over: " << dur.count() << " seconds" << std::endl;
    */

    // add sleep
    // std::this_thread::sleep_for(std::chrono::seconds(20));


    return 0;
}
