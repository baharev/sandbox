//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <boost/chrono.hpp>
#include "build_test.hpp"

using namespace std;

#define BUILD_STR_NODES

struct str_node;

namespace {

typedef double T;
typedef uint32_t offset;
typedef offset(*operation)(offset );

offset counter = 0;
vector<offset> offsets;

#ifdef BUILD_STR_NODES
vector<operation> functions;
vector<str_node> nodes;
#endif

vector<operation> T_functions;
vector<T>         T_nodes;

vector<offset> var_pos;
vector<offset> con_pos;
vector<pair<offset,double>> num_pos;

}

struct str_node {

    str_node() : index(counter++) {
#ifdef BUILD_STR_NODES
        stringstream ss;
        ss << "v" << index;
        name = ss.str();
        nodes.push_back(*this);
#endif
        T_nodes.push_back(T{});
        assert(counter!=numeric_limits<offset>::max());
    }

    str_node(string&& given_name)
    : name(move(given_name)),
      index(counter++)
    {
#ifdef BUILD_STR_NODES
        nodes.push_back(*this);
#endif
        T_nodes.push_back(T{});
        var_pos.push_back(index);
        assert(counter!=numeric_limits<offset>::max());
    }

    explicit str_node(double d)
    : name("n"+to_string(counter)), index(counter++)
    {
#ifdef BUILD_STR_NODES
        nodes.push_back(*this);
#endif
        T_nodes.push_back(T(d));
        num_pos.push_back({index, d});
        assert(counter!=numeric_limits<offset>::max());
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

    offset index;
};

str_node add_binary_node(operation op, operation T_op, const str_node& lhs, const str_node& rhs) {
#ifdef BUILD_STR_NODES
    functions.push_back(op);
#endif
    T_functions.push_back(T_op);

    str_node res;

    offsets.push_back(lhs.index);

    offsets.push_back(rhs.index);

    offsets.push_back(res.index);

    return res;
}

str_node add_unary_node(operation op, operation T_op, const str_node& arg) {
#ifdef BUILD_STR_NODES
    functions.push_back(op);
#endif
    T_functions.push_back(T_op);

    str_node res;

    offsets.push_back(arg.index);

    offsets.push_back(res.index);

    return res;
}

namespace detail {

offset add(offset args) {

    offset lhs = offsets.at(args  );

    offset rhs = offsets.at(args+1);

    offset res = offsets.at(args+2);
#ifdef BUILD_STR_NODES
    cout << nodes.at(res).name << " = ";

    cout << nodes.at(lhs).name << " + " << nodes.at(rhs).name << endl;
#endif
    return args+3;
}

offset mul(offset args) {

    offset lhs = offsets.at(args  );

    offset rhs = offsets.at(args+1);

    offset res = offsets.at(args+2);
#ifdef BUILD_STR_NODES
    cout << nodes.at(res).name << " = ";

    cout << nodes.at(lhs).name << " * " << nodes.at(rhs).name << endl;
#endif
    return args+3;
}

offset exp(offset args) {

    offset arg = offsets.at(args  );

    offset res = offsets.at(args+1);
#ifdef BUILD_STR_NODES
    cout << nodes.at(res).name << " = ";

    cout << "exp(" << nodes.at(arg).name << ")" << endl;
#endif
    return args+2;
}

offset sumlist(offset args) {

    offset n   = offsets.at(args);

    offset res = offsets.at(args+n+1);

    cout << nodes.at(res).name << " = " << flush;

    for (offset i=1; i<n; i+=2) {

        offset c = offsets.at(args+i  );

        offset x = offsets.at(args+i+1);

        if (i!=1) cout << " + ";

        cout << nodes.at(c).name << " * " << nodes.at(x).name;
    }

    cout << endl;

    return args+n+2;
}

} // namespace detail

namespace safe {

offset add(offset args) {

    offset lhs = offsets.at(args  );

    offset rhs = offsets.at(args+1);

    offset res = offsets.at(args+2);

    T_nodes.at(res) = T_nodes.at(lhs) + T_nodes.at(rhs);

    return args+3;
}

offset mul(offset args) {

    offset lhs = offsets.at(args  );

    offset rhs = offsets.at(args+1);

    offset res = offsets.at(args+2);

    T_nodes.at(res) = T_nodes.at(lhs) * T_nodes.at(rhs);

    return args+3;
}

offset exp(offset args) {

    offset arg = offsets.at(args  );

    offset res = offsets.at(args+1);

    T_nodes.at(res) = std::exp(T_nodes.at(arg));

    return args+2;
}

} // namespace safe

offset add(offset args) {

    offset lhs = offsets[args  ];

    offset rhs = offsets[args+1];

    offset res = offsets[args+2];

    T_nodes[res] = T_nodes[lhs] + T_nodes[rhs];

    return args+3;
}

offset mul(offset args) {

    offset lhs = offsets[args  ];

    offset rhs = offsets[args+1];

    offset res = offsets[args+2];

    T_nodes[res] = T_nodes[lhs] * T_nodes[rhs];

    return args+3;
}

offset exp(offset args) {

    offset arg = offsets[args  ];

    offset res = offsets[args+1];

    T_nodes[res] = exp(T_nodes[arg]);

    return args+2;
}

str_node operator+(const str_node& lhs, const str_node& rhs) {

    return add_binary_node(detail::add, add, lhs, rhs);
}

str_node operator*(const str_node& lhs, const str_node& rhs) {

    return add_binary_node(detail::mul, mul, lhs, rhs);
}

str_node operator*(double d, const str_node& rhs) {

    return str_node(d)*rhs;
}

str_node exp(const str_node& arg) {

    return add_unary_node(detail::exp, exp, arg);
}

str_node sumlist_cx(const str_node& c, const str_node& x) {

    str_node res;

    offsets.push_back(c.index);

    offsets.push_back(x.index);

    offsets.push_back(res.index);

    return res;
}

template <typename... Args>
str_node sumlist_cx(const str_node& c, const str_node& x, Args&&... s) {

    offsets.push_back(c.index);

    offsets.push_back(x.index);

    return sumlist(forward<Args>(s)...);
}


template <typename... Args>
str_node sumlist(Args&&... s) {

    offset n = sizeof... (Args);

    functions.push_back(detail::sumlist);

    offsets.push_back(n);

    return sumlist_cx(forward<Args>(s)...);
}

str_node sumlist(initializer_list<str_node> s) {

    offset n = static_cast<offset>(s.size());

    functions.push_back(detail::sumlist);

    offsets.push_back(n);

    str_node res;

    for (const str_node& node : s) {

        offsets.push_back(node.index);
    }

    offsets.push_back(res.index);

    return res;
}

void build_test::init(const std::vector<std::string>& ) {

}

void build_test::show() {

#ifdef BUILD_STR_NODES

    cout << "variables" << endl;

    for (auto var : var_pos) {

        const str_node& node = nodes.at(var);

        cout << node.name << " ("<< node.index << ")\n";
    }

    cout << "constraints" << endl;

    for (auto con : con_pos) {

        const str_node& node = nodes.at(con);

        cout << node.name << '\n';
    }

    cout << "numeric constants" << endl;

    for (const auto& num : num_pos) {

        const auto& node = nodes.at(num.first);

        cout << node.name << "   " << num.second << '\n';
    }

    cout << "evaluation" << endl;

    offset args = 0;

    for (auto f : functions) {

        args = f(args);
    }

#endif

}

void build_test::forward_sweep() {

    for (auto var : var_pos) {

        T_nodes.at(var) = 1.1;
    }

//    cout << "variables" << endl;
//
//    for (auto var : var_pos) {
//
//        cout << T_nodes.at(var) << '\n';
//    }

    using namespace boost::chrono;

    auto start = high_resolution_clock::now();

    offset args = 0;

    for (auto f : T_functions) {

        args = f(args);
    }

    auto finish = high_resolution_clock::now();

    cout << duration_cast<milliseconds>(finish-start).count() << " ms" << endl;
    cout << duration_cast<microseconds>(finish-start).count() << " us" << endl;

//    cout << "residuals" << endl;
//
//    for (auto con : con_pos) {
//
//        cout << T_nodes.at(con) << '\n';
//    }
}

void build_test::run() {

    bratu_with_sumlist();

#ifdef BUILD_STR_NODES

    show();

    nodes = vector<str_node>();

    functions = vector<operation>();

#endif

    forward_sweep();
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

void build_test::bratu_with_sumlist() {

    const int n = 3;

    const double h2 = std::pow(1.0/(n+1), 2);

    str_node x1("x1");

    str_node x2("x2");

    //str_node con1 = x2 + (-2)*x1 + h2*exp(x1);

    str_node y1 = exp(x1);

    str_node con1 = sumlist({str_node(1), x2, str_node(-2), x1, str_node(h2), y1});

    con1.push_constraint();

    int index = 3;

    str_node x3("x3");

    for (int i=2; i<n; ++i) {

        //str_node con = x3 + (-2)*x2 + x1 + h2*exp(x2);
        str_node y2 = exp(x2);

        str_node con = sumlist({str_node(1), x3, str_node(-2), x2, str_node(1), x1, str_node(h2), y2});

        con.push_constraint();

        x1 = std::move(x2);
        x2 = std::move(x3);

        if (i<n-1) {
            x3 = str_node("x"+to_string(index++));
        }
    }

    str_node y2 = exp(x2);

    str_node last_con = sumlist({str_node(-2), x2, str_node(1), x1, str_node(h2), y2});

    last_con.push_constraint();
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
