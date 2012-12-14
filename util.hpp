#include <algorithm>
#include <vector>
#ifndef UTIL_HPP
#define UTIL_HPP

int str2int(const std::string& s, bool& failed);

double str2double(const std::string& s, bool& failed);

bool equals_int(const std::string& s, int i);

bool equals_double(const std::string& s, double x);

bool equals_ignore_case(const std::string& a, const std::string& b);

template <typename T, size_t n>
std::vector<T> from_array(const T (&array)[n]) {

	return std::vector<T>(array, array+n);
}

template <typename T>
bool contains(const std::vector<T>& vec, const T& elem) {

	return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

#endif
