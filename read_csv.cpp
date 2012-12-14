#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "allowed_values.hpp"
#include "util.hpp"

using namespace std;

namespace {

vector<vector<string> > table;

//enum column {
//	DATA_ID,
//	GC,
//	COLOR,
//	LOC,
//	LOCX,
//	LOCY,
//	FORMATION,
//	DATATYPE,
//	corrDIPDIR,
//	corrDIP,
//	corrLDIR,
//	corrLDIP,
//	SENSE,
//	PALEONORTH,
//	COMMENT,
//	SIZE
//};

enum column {
	ID,
	NAME,
	VALUE,
	SIZE
};

}


void push_to_table(const string& line) {

	vector<string> row;

	string cell;

	istringstream iss(line);

	while (getline(iss, cell, '\t')) {

		row.push_back(cell);
	}

	if (row.size() < SIZE) {

		row.resize(SIZE);
	}

	table.push_back(row);
}


int read_csv(const string& file_name) {

	table.clear();

	int lines_read = 0;

	ifstream in(file_name.c_str());

	string line;

	while (getline(in, line)) {

		++lines_read;

		push_to_table(line);

	}

	return lines_read;
}


void check_id() {

	for (size_t i=0; i<table.size(); ++i) {

		bool failed = true;

		string id = table.at(i).at(ID);

		int value = str2int(id, failed);

		if (failed) {

			cout << "Line " << (i+1) << " contains non-integer ID: \"" << id << "\""<< endl;
		}
		else {

			cout << "Line " << (i+1) << " is OK, ID is: \"" << id << "\"";
			cout << (( equals_int(id, (i+1)) ) ? " and it equals the line number" : "") << endl;
		}
	}
}


void check_names() {

	for (size_t i=0; i<table.size(); ++i) {

		string name = table.at(i).at(NAME);

		bool valid = is_allowed_name(name);
		//bool valid = is_allowed_name_ignore_case(name);

		if (valid) {

			cout << "Line " << (i+1) << " has a valid name: \"" << name << "\""<< endl;
		}
		else {

			cout << "Line " << (i+1) << " has an invalid name: \"" << name << "\"" << endl;
		}
	}
}


void check_values() {

	for (size_t i=0; i<table.size(); ++i) {

		string value = table.at(i).at(VALUE);

		bool valid = is_allowed_integer(value);

		if (valid) {

			cout << "Line " << (i+1) << " has a valid value: \"" << value << "\""<< endl;
		}
		else {

			cout << "Line " << (i+1) << " has an invalid value: \"" << value << "\"" << endl;
		}
	}
}


void dump_table(const string& file_name) {

	ofstream out(file_name.c_str());

	for (size_t i=0; i<table.size(); ++i) {

		const vector<string>& row = table.at(i);

		for (size_t j=0; j<row.size(); ++j) {

			const string& cell = row.at(j);

			out << cell << '\t';
		}

		out << '\n';
	}
}



