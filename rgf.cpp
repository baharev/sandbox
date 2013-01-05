#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include "rgf.hpp"
#include "util.hpp"

using namespace std;

namespace {

vector <vector <string> > rgf_to_check;

//--------------------------------------------


const string headers[] = {
		"DATA_ID",
		"GC",
		"COLOR",
		"LOC",
		"LOCX",
		"LOCY",
		"FORMATION",
		"DATATYPE",
		"corrDIPDIR",
		"corrDIP",
		"corrLDIR",
		"corrLDIP",
		"SENSE",
		"PALEONORTH",
		"COMMENT"
};

const vector<string> reserved_headers = from_array(headers);

vector<vector<string> > orig_table;

vector<pair<size_t,size_t> > index_map;

const size_t NOT_FOUND = numeric_limits<size_t>::max();

}

template <typename Container, typename T>
size_t find_index(const Container& c, const T& value) {

	typename Container::const_iterator beg = c.begin();
	typename Container::const_iterator end = c.end();
	typename Container::const_iterator pos = std::find(beg, end, value);

	return (pos == end) ? NOT_FOUND : std::distance(beg, pos);
}

string to_uppercase(string s) {

	transform(s.begin(), s.end(), s.begin(), ::toupper);

	return s;
}


void push_to_table(const string& line) {

	vector<string> row;

	string cell;

	istringstream iss(line);

	while (getline(iss, cell, '\t')) {

		row.push_back(cell);
	}

	orig_table.push_back(row);
}

int read_csv(const string& file_name) {

	orig_table.clear();

	int lines_read = 0;

	ifstream in(file_name.c_str());

	string line;

	while (getline(in, line)) {

		++lines_read;

		push_to_table(line);

	}

	return lines_read;
}

size_t index_in_header(const string& s) {

	return find_index(reserved_headers, s);
}

void build_column_map() {

	index_map.clear();

	const vector<string>& header = orig_table.at(0);

	for (size_t i=0; i<header.size(); ++i) {

		const string& col_name = header.at(i);

		size_t index = index_in_header(col_name);

		if (index!=NOT_FOUND) {

			index_map.push_back(make_pair(i,index));
		}
	}
}

size_t cell_index(size_t i) {

	return 0; // FIXME Finish!
}

void convert_row(const vector<string>& orig_row, size_t index) {

	const size_t n_col = reserved_headers.size();

	vector<string> row(n_col);

	for (size_t i=0; i<orig_row.size(); ++i) {

		size_t index = cell_index(i);

		if (index!=NOT_FOUND) {

			row.at(index) = to_uppercase( orig_row.at(i) ); // TODO Also convert to uppercase?
		}
	}

	rgf_to_check.push_back(row);
}

void convert_csv_rgf() {

	build_column_map();

	for (size_t i=1; i<orig_table.size(); ++i) {

		convert_row(orig_table.at(i), i-1);
	}
}

void csv_to_rgf() {

	rgf_to_check.clear();

	convert_csv_rgf();
}

void read_rgf(const string& file_name) {

	int lines_read = read_csv(file_name);

	if (lines_read<1) {
		cerr << "No header read, exiting..." << endl;
		exit(1); // TODO Do the appropriate thing here
	}

	csv_to_rgf();
}
