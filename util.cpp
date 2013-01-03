#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include "util.hpp"

using namespace std;

template <typename T>
T convert(const string& s, bool& failed) {

	istringstream iss(s);

	T value;

	iss >> value;

	failed = (iss.fail() || !iss.eof()) ? true : false;

	return value;
}


template <typename T>
bool equals(const string& s, const T& value) {

	bool failed = true;

	T other = convert<T>(s, failed);

	return !failed && (value==other);
}


bool equals_int(const string& s, int i) {

	return equals(s, i);
}


bool equals_double(const string& s, double x) {

	return equals(s, x);
}


int str2int(const string& s, bool& failed) {

	return convert<int>(s, failed);
}


double str2double(const string& s, bool& failed) {

	return convert<double>(s, failed);
}


bool equals_ignore_case(const string& a, const string& b) {

    string::size_type n = a.size();

    if (b.size() != n) {

    	return false;
    }

    for (string::size_type i=0; i<n; ++i) {

        if (toupper(a.at(i)) != toupper(b.at(i))) {

        	return false;
        }
    }

    return true;
}


// returns true if successful
bool copy_file(const string& source, const string& destination) {

	ifstream in(source.c_str(), ios::binary);

	ofstream out(destination.c_str(), ios::binary);

	out << in.rdbuf();

	return !in.fail() && !out.fail();
}


string build_date() {

	struct tm date = { 0 };

	strptime(__DATE__, "%b %e %Y", &date);

	char buff[10];

	return strftime(buff, sizeof(buff), "%d/%m/%y", &date) ? buff : "";
}

string build_date2() {

	struct tm date = { 0 };

	strptime(__DATE__, "%b %e %Y", &date);

	string str_date(asctime(&date));

	return str_date.substr(0, str_date.size()-1);
}

time_t build_date_to_time_t() {

	struct tm date = { 0 };

	strptime(__DATE__, "%b %e %Y", &date);

	return mktime(&date);
}

string build_time() {

	return __TIME__;
}
