#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
	COL1,
	COL2,
	COL3,
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


template <typename T>
T convert(const string& s, bool& failed) {

	failed = true;

	T value = T();

	istringstream iss(s);

	iss.exceptions(ios::failbit | ios::badbit);

	try {

		iss >> value;
	}
	catch (...) {

		return value;
	}

	if (iss.eof()) {

		failed = false;
	}

	return value;
}


void check_id_is_int() {

	for (size_t i=0; i<table.size(); ++i) {

		bool failed = true;

		string id = table.at(i).at(COL1);

		int value = convert<int>(id, failed);

		if (failed) {

			cout << "Line " << (i+1) << " contains non-integer COL1: \"" << id << "\""<< endl;
		}
		else {

			cout << "Line " << (i+1) << " is OK, id is: \"" << id << "\""<< endl;
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



