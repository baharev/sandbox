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

enum column {
	ID,    // ID    = 0,
	NAME,  // NAME  = 1,
	VALUE, // VALUE = 2,
	SIZE   // SIZE  = 3
};

int ID_index() {

	return ID;
}

int NAME_index() {

	return NAME;
}

int VALUE_index() {

	return VALUE;
}

struct record {

	record() : id(-1), name("default name"), value(-1) { }

	int    id;
	string name;
	int    value;
};

vector<record> converted_table;

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

//------------------------------------------------------------------------------

void convert_id(int row_index, record& rec) {

	string id = table.at(row_index).at(ID_index());

	bool failed = true;

	int id_int = str2int(id, failed);

	if (failed) {

		cout << "Line " << (row_index+1) << ": conversion of id \"" << id << "\" failed" << endl;
	}
	else {

		rec.id = id_int;
	}
}

void check_name(int row_index, record& rec) {

	string name = table.at(row_index).at(NAME_index());

	if (is_allowed_name_ignore_case(name)) {

		rec.name = name;
	}
	else {

		cout << "Line " << (row_index+1) << ": name \"" << name << "\" is not allowed" << endl;

	}
}

void convert_value(int row_index, record& rec) {

	string val = table.at(row_index).at(VALUE_index());

	bool failed = true;

	int value = str2int(val, failed);

	if (failed) {

		cout << "Line " << (row_index+1) << " conversion of value \"" << val << "\" failed" << endl;
	}
	else {

		rec.value = value;
	}

}

void convert_table() {

	converted_table.clear();

	for (size_t i=0; i<table.size(); ++i) {

		record rec;

		convert_id(i, rec);

		check_name(i, rec);

		convert_value(i, rec);

		converted_table.push_back(rec);
	}
}

