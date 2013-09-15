//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "build_test.hpp"

using namespace std;

struct str_node;

namespace {

typedef int(*operation)(int );

int counter = 0;
vector<int> offsets;
vector<operation> functions;
vector<str_node> nodes;

vector<int> var_pos;
vector<int> con_pos;
vector<pair<int,double>> num_pos;

}

struct str_node {

    str_node() : index(counter++) {
        stringstream ss;
        ss << "v" << index;
        name = ss.str();
        nodes.push_back(*this);
    }

    str_node(string&& name)
    : name(move(name)),
      index(counter++)
    {
        nodes.push_back(*this);
        var_pos.push_back(index);
    }

    explicit str_node(double d)
    : name("n"+to_string(counter)), index(counter++)
    {
        nodes.push_back(*this);
        num_pos.push_back({index, d});
    }

    str_node(const str_node& ) = default;

    str_node(str_node&& ) noexcept = default;

    str_node& operator=(str_node&& other) noexcept {
        index = other.index;
        name.swap(other.name);
        return *this;
    }

    void push_constraint() {

        con_pos.push_back(index);
    }

    string name;

    int index;
};

str_node add_binary_node(operation op, const str_node& lhs, const str_node& rhs) {

    functions.push_back(op);

    str_node res;

    offsets.push_back(lhs.index);

    offsets.push_back(rhs.index);

    offsets.push_back(res.index);

    return res;
}

str_node add_unary_node(operation op, const str_node& arg) {

    functions.push_back(op);

    str_node res;

    offsets.push_back(arg.index);

    offsets.push_back(res.index);

    return res;
}

int add(int args) {

    int lhs = offsets.at(args  );

    int rhs = offsets.at(args+1);

    int res = offsets.at(args+2);

    cout << nodes.at(res).name << " = ";

    cout << nodes.at(lhs).name << " + " << nodes.at(rhs).name << endl;

    return args+3;
}

int mul(int args) {

    int lhs = offsets.at(args  );

    int rhs = offsets.at(args+1);

    int res = offsets.at(args+2);

    cout << nodes.at(res).name << " = ";

    cout << nodes.at(lhs).name << " * " << nodes.at(rhs).name << endl;

    return args+3;
}

int exp(int args) {

    int arg = offsets.at(args  );

    int res = offsets.at(args+1);

    cout << nodes.at(res).name << " = ";

    cout << "exp(" << nodes.at(arg).name << ")" << endl;

    return args+2;
}

str_node operator+(const str_node& lhs, const str_node& rhs) {

    return add_binary_node(add, lhs, rhs);
}

str_node operator*(const str_node& lhs, const str_node& rhs) {

    return add_binary_node(mul, lhs, rhs);
}

str_node operator*(double d, const str_node& rhs) {

    return str_node(d)*rhs;
}

str_node exp(const str_node& arg) {

    return add_unary_node(exp, arg);
}

void build_test::init(const std::vector<std::string>& ) {

}

void build_test::show() {

    int args = 0;

    cout << "variables" << endl;

    for (int var : var_pos) {

        const str_node& node = nodes.at(var);

        cout << node.name << " ("<< node.index << ")\n";
    }

    cout << "constraints" << endl;

    for (int con : con_pos) {

        const str_node& node = nodes.at(con);

        cout << node.name << '\n';
    }

    cout << "numeric constants" << endl;

    for (const auto& num : num_pos) {

        const auto& node = nodes.at(num.first);

        cout << node.name << "   " << num.second << '\n';
    }

    cout << "evaluation" << endl;

    for (const auto& f : functions) {

        args = f(args);
    }
}

void build_test::run() {

    bratu();

    show();
}

void build_test::dummy_example() {

    // x + y + z = 0
    str_node x("x");
    str_node y("y");
    str_node z("z");

    str_node con1(x+y+z);

    con1.push_constraint();

    // p + q = 0
    str_node p("p");
    str_node q("q");

    str_node con2(p+q);

    con2.push_constraint();
}

void build_test::bratu() {

    const int n = 3;

    const double h2 = std::pow(1.0/(n+1), 2);

    str_node x1("x1");

    str_node x2("x2");

    str_node con1 = x2 + (-2)*x1 + h2*exp(x1);

    con1.push_constraint();

    int index = 3;

    str_node x3("x3");

    for (int i=2; i<n; ++i) {

        str_node con = x3 + (-2)*x2 + x1 + h2*exp(x2);

        con.push_constraint();

        x1 = std::move(x2);
        x2 = std::move(x3);

        if (i<n-1) {
            x3 = str_node("x"+to_string(index++));
        }
    }

    str_node last_con = (-2)*x2 + x1 + h2*exp(x2);

    last_con.push_constraint();

}
