//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#ifndef BUILD_TEST_HPP_
#define BUILD_TEST_HPP_
#include <vector>
#include <string>

class build_test {

public:

    void init(const std::vector<std::string>& args);

    void run();

private:

    void dummy_example();

    void bratu();

    void show();

    void forward_sweep();

};

#endif
