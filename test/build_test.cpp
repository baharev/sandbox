//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "build_test.hpp"

using namespace std;

typedef int(*operation)(int, int);

int add(int z, int args);

struct str_node {

    str_node() {
        stringstream ss;
        ss << "v" << counter;
        name = ss.str();
        index = counter++;
        nodes.push_back(*this);
    }

    str_node(string&& name)
    : name(move(name)),
      index(counter++)
    {
        nodes.push_back(*this);
    }

    string name;

    int index;

    static vector<int> offsets;

    static vector<operation> functions;

    static vector<str_node> nodes;

    static int counter;
};

int str_node::counter = 0;
vector<int> str_node::offsets;
vector<operation> str_node::functions;
vector<str_node> str_node::nodes;

str_node add_binary_node(operation op, const str_node& lhs, const str_node& rhs) {

    str_node z;

    str_node::offsets.push_back(lhs.index);

    str_node::offsets.push_back(rhs.index);

    str_node::functions.push_back(op);

    return z;
}

int add(int z, int args) {

    cout << str_node::nodes.at(z).name << " ?= ";

    int lhs = str_node::offsets.at(args);

    int rhs = str_node::offsets.at(args+1);

    cout << str_node::nodes.at(lhs).name << " + " << str_node::nodes.at(rhs).name << endl;

    return args+2;
}

str_node operator+(const str_node& lhs, const str_node& rhs) {

    return add_binary_node(add, lhs, rhs);
}

void build_test::init(const std::vector<std::string>& ) {

}

void build_test::run() {

    // x + y + z = 0
    str_node x("x");
    str_node y("y");
    str_node z("z");

    str_node con1(x+y+z);

    // p + q = 0
    str_node p("p");
    str_node q("q");

    str_node con2(p+q);

    int result = 3;

    int args = 0;

    for (const auto& f : str_node::functions) {

        args = f(result++, args);
    }
}
