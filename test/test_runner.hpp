//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#ifndef TEST_RUNNER_HPP_
#define TEST_RUNNER_HPP_
#include <map>
#include <string>
#include <vector>

class test;

class test_runner {

public:

    test_runner(int argc, char* argv[]);

    void execute();

    ~test_runner();

private:

    void add_all_tests();

    void show_available_tests() const;

    void show_args(const std::vector<std::string>& v) const;

    void run() const;

    void run_test(const std::string& name) const;

    std::vector<std::string> args;

    std::map<std::string,test> tests;
};

#endif

