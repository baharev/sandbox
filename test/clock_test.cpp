//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <chrono>
#include <iostream>
#include <boost/chrono.hpp>
#include "clock_test.hpp"

using std::cerr;
using std::endl;
using std::flush;

volatile size_t n_times = 1000;
volatile size_t dummy;

void clock_test::init(const std::vector<std::string>& ) {

}

void clock_test::std_clock() {

    using namespace std::chrono;

    typedef duration<double, std::nano> NS;

    NS ns = high_resolution_clock::duration(1);

    cerr << "Claimed precision of the high_resolution_clock is " << ns.count() << " ns" << endl;

    auto start = high_resolution_clock::now();

    for (int i=0; i<1; ++i)
        cerr << ' ' << flush;
    cerr << endl;

    auto finish = high_resolution_clock::now();

    cerr << duration_cast<microseconds>(finish-start).count() << " us" << endl;
}

void clock_test::boost_clock() {

    using namespace boost::chrono;

    typedef duration<double, boost::nano> NS;

    NS ns = high_resolution_clock::duration(1);

    cerr << "Claimed precision of the high_resolution_clock is " << ns.count() << " ns" << endl;

    auto start = high_resolution_clock::now();

    for (size_t i=0; i<n_times; ++i)
        dummy += i;

    auto finish = high_resolution_clock::now();

    cerr << duration_cast<microseconds>(finish-start).count() << " us" << endl;
}

void clock_test::run() {

    std_clock();

    boost_clock();
}



