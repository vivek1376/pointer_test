#include <iostream>
#include <chrono>
#include <memory>
#include <string>

#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>

static const long long numInt= 100000000;


class X {
public:
    std::string name;
    int age;

    long references;

    X(std::string n, int a) : name(n), age(a), references(0) {}
};



inline void intrusive_ptr_add_ref(X* x) {
    ++x->references;
}


inline void intrusive_ptr_release(X* x) {
    if (--x->references == 0)
        delete x;
}


void boost_test()
{

    // time_t t=clock();
    size_t rounds = 100000000;

    std::chrono::duration<double> dur;
    std::cout << "h1" << std::endl;
    auto start = std::chrono::system_clock::now();


    /*
    t=clock();
    for(size_t i = 0; i < rounds; i++)
    {
        std::shared_ptr<X> myX(new X("Michael", 40));
        myX->age++;
    }
    std::cout << "Time taken to generate " << rounds << " of Microsoft shared_ptr is "
    << clock()-t << std::endl;
    */


    for(size_t i = 0; i < rounds; i++)
    {
        std::shared_ptr<X> myX=std::make_shared<X>("Michael",40);
        myX->age++;
    }
    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to generate " << rounds << " of std::shared_ptr using make_shared is "
    << dur.count() << "seconds" << std::endl;
    start = std::chrono::system_clock::now();

    /*

    for(size_t i = 0; i < rounds; i++)
    {
        boost::shared_ptr<X> myX(new X("Michael", 40));
        myX->age++;
    }
    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to generate " << rounds << " of shared_ptr is "
    << dur.count() << "seconds" << std::endl;
    start = std::chrono::system_clock::now();


    t=clock();
    for(size_t i = 0; i < rounds; i++)
    {
        boost::shared_ptr<X> myX = boost::make_shared<X>("Michael", 40);
        myX->age++;
    }
    std::cout << "Time taken to generate " << rounds << " of shared_ptr using make_shared is "
    << clock()-t << std::endl;
    */

    for(size_t i = 0; i < rounds; i++)
    {
        boost::intrusive_ptr<X> myX(new X("Michael", 40));
        myX->age++;
    }
    dur = std::chrono::system_clock::now() - start;
    std::cout << "Time taken to generate " << rounds << " of intrusive_ptr is "
    << dur.count() << "seconds" << std::endl;

}


int main()
{
    boost_test();

    return 0;

    auto start = std::chrono::system_clock::now();

    for ( long long i=0 ; i < numInt; ++i) {
        // int* tmp(new int(i));
        // delete tmp;

        std::unique_ptr<int> tmp(new int(i));
        // std::unique_ptr<int> tmp(std::make_unique<int>(i));

        // std::shared_ptr<int> tmp(std::make_shared<int>(i));
    }

    std::chrono::duration<double> dur;
    dur = std::chrono::system_clock::now() - start;
    std::cout << "time native: " << dur.count() << " seconds" << std::endl;

    return 0;
}
