#include <algorithm>
#include <vector>
#include "allowed_values.hpp"
#include "util.hpp"

using namespace std;

namespace {

string names[] = {
		"Alice",
		"Bob",
		"Christine",
		"Dave"
};

int numbers[] = {
		1,
		2,
		5,
		10
};

vector<string> allowed_names(from_array(names));

vector<int> allowed_numbers(from_array(numbers));

}


bool is_allowed_name(const string& s) {

	return contains(allowed_names, s);
}


bool is_allowed_name_ignore_case(const string& s) {

	for (size_t i=0; i<allowed_names.size(); ++i) {

		if (equals_ignore_case(s, allowed_names.at(i))) {

			return true;
		}
	}

	return false;
}


bool is_allowed_number(int i) {

	return contains(allowed_numbers, i);
}


bool is_allowed_number(const string& s) {

	bool failed = true;

	int i = str2int(s, failed);

	return !failed && is_allowed_number(i);
}


