#include <iostream>
#include <chrono>
#include <memory>
#include <string>

#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>


class X {
public:
    std::string name;
    int age;
    float weight;

    long references;

    X(std::string n, int a, float w) : name(n), age(a), weight(w), references(0) {}
};



inline void intrusive_ptr_add_ref(X* x) {
    ++x->references;
}


inline void intrusive_ptr_release(X* x) {
    if (--x->references == 0)
        delete x;
}


int main()
{
    size_t rounds = 100000000;

    std::chrono::duration<double> dur;

    // /*
    auto start = std::chrono::system_clock::now();

    for(size_t i = 0; i < rounds; i++)
    {
        std::shared_ptr<X> myX = std::make_shared<X>("Dilbert", 40, 188.8);
        myX->age++;
        myX->weight += 0.1f;
    }
    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to generate " << rounds << " of std::shared_ptr using make_shared is "
    << dur.count() << "seconds" << std::endl;
    // */

    /*
    auto start = std::chrono::system_clock::now();

    for(size_t i = 0; i < rounds; i++)
    {
        boost::intrusive_ptr<X> myX(new X("Dilbert", 40, 188.8));
        myX->age++;
        myX->weight += 0.1f;
    }
    dur = std::chrono::system_clock::now() - start;
    std::cout << "Time taken to generate " << rounds << " of intrusive_ptr is "
    << dur.count() << "seconds" << std::endl;
    */


    return 0;
}
