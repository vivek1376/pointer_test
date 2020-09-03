#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <string>
#include <random>

#include <cstdio>
#include <csignal>
#include <unistd.h>

#include <boost/intrusive_ptr.hpp>
// #include <boost/atomic.hpp>


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

void shared_ptr_test(const size_t arrsize, const size_t loop_array_count, const size_t* arr_randindex) {

    // std::chrono::duration<double> dur;

    std::shared_ptr<X2> *arr_sharedptrs = new std::shared_ptr<X2>[arrsize];

    for (size_t i = 0; i < arrsize; i++) {
        arr_sharedptrs[i] = std::make_shared<X2>("Dilbert", 40, 188.8);
    }

    // auto start = std::chrono::system_clock::now();

    for(size_t i = 0; i < loop_array_count; i++) {
        for (size_t j = 0; j < arrsize; j++) {
            std::shared_ptr<X2> temp(arr_sharedptrs[arr_randindex[j]]);
            temp->age++;
            temp->weight += 0.1f;
        }
    }

    /*
    dur = std::chrono::system_clock::now() - start;

    std::cout << "Time taken to randomly access " << arrsize << " objects managed by std::shared_ptr "
              << loop_array_count << " times over: " << dur.count() << "seconds" << std::endl;
    */
}


void intrusive_ptr_test(const size_t arrsize, const size_t loop_array_count, const size_t* arr_randindex) {

    // std::chrono::duration<double> dur;

    boost::intrusive_ptr<X1> *arr_boostptrs = new boost::intrusive_ptr<X1>[arrsize];

    for (size_t i = 0; i < arrsize; i++) {
        arr_boostptrs[i] = new X1("Dilbert", 40, 188.8);
    }

    // auto start2 = std::chrono::system_clock::now();

    for (size_t i = 0; i < loop_array_count; i++) {
        for(size_t j = 0; j < arrsize; j++) {
            boost::intrusive_ptr<X1> temp(arr_boostptrs[arr_randindex[j]]);
            temp->age++;
            temp->weight += 0.1f;
        }
    }

    /*
    dur = std::chrono::system_clock::now() - start2;

    std::cout << "Time taken to randomly access " << arrsize << " objects managed by "
                 "boost::intrusive_ptr, " << loop_array_count << " times over: "
              << dur.count() << " seconds" << std::endl;
    */
}

int main()
{
    const size_t arrsize = 1000000;
    const size_t loop_array_count = 200;

    // https://stackoverflow.com/a/13445752/9894266
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand_dist(0, arrsize - 1);

    size_t* arr_randindex = new size_t[arrsize];

    // fill an array with random indexes
    for (size_t i = 0; i < arrsize; i++) {
        arr_randindex[i] = rand_dist(rng);
    }

    int pid = getpid();
    int cpid = fork();

    if (cpid == 0) {
        char buf[200];
        sprintf(buf, "perf stat -e instructions:u,L1-dcache-loads:u,L1-dcache-load-misses:u,cache-misses:u,dTLB-load-misses:u,dTLB-loads:u -p %d 2>&1", pid);
        execl("/bin/sh", "sh", "-c", buf, NULL);
    } else {
        setpgid(cpid, 0);

        // shared_ptr_test(arrsize, loop_array_count, arr_randindex);
        intrusive_ptr_test(arrsize, loop_array_count, arr_randindex);

        kill (-cpid, SIGINT);
    }



    // add sleep
    // std::this_thread::sleep_for(std::chrono::seconds(20));


    return 0;
}
