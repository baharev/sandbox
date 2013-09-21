//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <chrono>
#include <iostream>
#include "clock_test.hpp"

void clock_test::init(const std::vector<std::string>& ) {

}

void clock_test::run() {

    using namespace std;
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    for (int i=0; i<1000; ++i)
        cerr << ' ' << flush;
    cerr << endl;

    auto finish = high_resolution_clock::now();

    cout << duration_cast<microseconds>(finish-start).count() << " us" << endl;

}



