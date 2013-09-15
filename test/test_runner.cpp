//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <iostream>
#include <iterator>
#include "test_runner.hpp"
#include "all_classes_include.hpp"
#include "test.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

test_runner::test_runner(int argc, char* argv[])
:   args(argv+1, argv+argc)
{ }

void test_runner::execute() {

    cout << "Invoked with arguments:";

    show_args(args);

    add_all_tests();

    if (args.empty()) {

        show_available_tests();
    }
    else {

        run();
    }
}

void test_runner::show_args(const vector<string>& v) const {

    for (const auto& arg : v) {

        cout << " \"" << arg << "\"";
    }

    cout << endl;
}

void test_runner::show_available_tests() const {

    cout << "Available tests: \n";

    for (const auto& t : tests) {

        cout << "  " << t.first << '\n';
    }

    cout << endl;
}

void test_runner::run() const {

//    try {

        string name = args.at(0);

        cout << "Trying to run test " << name << endl;

        run_test(name);

        cout << "Test passed!" << endl;
//    }
//    catch (...) {
//
//        cout << "Test failed!" << endl;
//    }
}

void test_runner::run_test(const string& name) const {

    auto test_to_run = tests.find(name);

    if (test_to_run==tests.end()) {

        cout << "Error: test \"" << name << "\" not found!" << endl;

        return;
    }

    vector<string> test_args{ args.size()==2 ? args.at(1) : string() };

    cout << "Invoking test with arguments:";

    show_args(test_args);

    test_to_run->second.execute(test_args);
}

void test_runner::add_all_tests() {

    std::pair<string,test> test_array[] = {
#include "test_classes"
    };

    std::move(std::begin(test_array), std::end(test_array), std::inserter(tests, tests.end()));
}


test_runner::~test_runner() {
    // out of line dtor due to incomplete type test
}
