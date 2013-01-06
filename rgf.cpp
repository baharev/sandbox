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

// TODO Agree on the identifiers, then share the code with the GUI
const string headers[] = {
		"DATA_ID",
		"GROUPCODE",
		"COLORCODE",
		"LOCATION",
		"LOC_X",
		"LOC_Y",
		"FORMATION",
		"DATATYPE",
		"DIPDIR",
		"DIP",
		"LDIR",
		"LDIP",
		"SENSE",
		"PALEONORTH",
		"COMMENT"
};

const vector<string> reserved_headers = from_array(headers);

vector<vector<string> > orig_table;

vector<size_t> index_map;

const size_t NOT_FOUND = numeric_limits<size_t>::max();

}

template <typename Container, typename T>
size_t find_index(const Container& c, const T& value) {

	typename Container::const_iterator pos = std::find(c.begin(), c.end(), value);

	return (pos == c.end()) ? NOT_FOUND : std::distance(c.begin(), pos);
}

string to_uppercase(string s) {

	transform(s.begin(), s.end(), s.begin(), ::toupper);

	return s;
}

void push_to_table(const string& line) {

	vector<string> row;

	istringstream iss(line);

	string cell;

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

		push_to_table(line+'\t'); // so that we don't loose trailing tabs

	}

	return lines_read;
}

size_t cell_index(size_t i) {

	return (i < index_map.size()) ? index_map.at(i) : NOT_FOUND;
}

void dbg_dump_index_map() {

	cout << "Column map: original -> rgf \n";

	const vector<string>& header = orig_table.at(0);

	for (size_t i=0; i<header.size(); ++i) {

		cout << header.at(i) << " -> ";

		size_t index = cell_index(i);

		if (index==NOT_FOUND) {

			cout << "(none)\n";
		}
		else {

			cout << reserved_headers.at(index) << '\n';
		}
	}
}

void check_duplicates(const vector<size_t>& dup) {

	if (dup.empty()) {

		return;
	}

	cout << "Error: the following reserved column names were found multiple times:\n";

	for (size_t i=0; i<dup.size(); ++i) {

		cout << reserved_headers.at(dup.at(i)) << '\n';
	}

	cout << "Exiting..." << endl;

	exit(1); // TODO Do the appropriate thing here
}

void build_column_map() {

	vector<size_t> duplicates;

	const vector<string>& header = orig_table.at(0);

	index_map.assign(header.size(), NOT_FOUND);

	for (size_t i=0; i<header.size(); ++i) {

		const string& col_name = header.at(i);

		size_t index = find_index(reserved_headers, col_name); // TODO to_uppercase(col_name) if case insensitive

		if (index==NOT_FOUND) {

			// That's OK
		}
		else if (contains(index_map, index)) {

			duplicates.push_back(index);
		}
		else {

			index_map.at(i) = index;
		}
	}

	check_duplicates(duplicates);

	dbg_dump_index_map(); // TODO Comment out if ready
}

void convert_row(const vector<string>& orig_row, size_t index) {

	const size_t n_col = reserved_headers.size();

	vector<string> row(n_col);

	for (size_t i=0; i<orig_row.size(); ++i) {

		size_t index = cell_index(i);

		if (index!=NOT_FOUND) {

			//row.at(index) = to_uppercase( orig_row.at(i) ); // TODO Convert to uppercase?
			row.at(index) = orig_row.at(i);
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
		cerr << "Nothing has been read from file " << file_name << ", exiting..." << endl; // we don't know why (empty or open() failed)
		exit(1); // TODO Do the appropriate thing here
	}

	csv_to_rgf();

	// TODO There may not be any data at this point, check!
}

void dump_table(const string& file_name, const vector<vector<string> >& table) {

	ofstream out(file_name.c_str());

	for (size_t i=0; i<table.size(); ++i) {

		const vector<string>& row = table.at(i);

		for (size_t j=0; j<row.size(); ++j) {

			const string& cell = row.at(j);

			out << cell << ((j < row.size()-1)? '\t' : '\n');
		}
	}
}

void dbg_dump_tables() {

	dump_table("orig.txt", orig_table);

	dump_table("conv.txt", rgf_to_check);
}
