//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <chrono>
#include <iostream>
#include <boost/chrono.hpp>
#include "clock_test.hpp"

namespace detail {

template <class Clock>
void display_precision()
{
    typedef std::chrono::duration<double, std::nano> NS;
    NS ns = typename Clock::duration(1);
    std::cout << ns.count() << " ns" << std::endl;
}

} // namespace detail

void clock_test::init(const std::vector<std::string>& ) {

}

void clock_test::std_clock() {

    using namespace std;
    using namespace std::chrono;

    cout << "Claimed precision of the high_resolution_clock is ";

    detail::display_precision<high_resolution_clock>();

    auto start = high_resolution_clock::now();

    for (int i=0; i<1; ++i)
        cerr << ' ' << flush;
    cerr << endl;

    auto finish = high_resolution_clock::now();

    cout << duration_cast<microseconds>(finish-start).count() << " us" << endl;
}

void clock_test::boost_clock() {

    using namespace boost;
    using namespace boost::chrono;
    using std::cerr;
    using std::endl;
    using std::flush;

    cerr << "Claimed precision of the high_resolution_clock is ";

    typedef boost::chrono::duration<double, boost::nano> NS;

    NS ns = boost::chrono::high_resolution_clock::duration(1);

    std::cout << ns.count() << " ns" << std::endl;

    auto start = high_resolution_clock::now();

    for (int i=0; i<1; ++i)
        cerr << ' ' << flush;
    cerr << endl;

    auto finish = high_resolution_clock::now();

    cerr << duration_cast<microseconds>(finish-start).count() << " us" << endl;
}

void clock_test::run() {

    std_clock();

    boost_clock();
}



