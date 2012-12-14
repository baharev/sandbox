#include <fstream>
#include <iostream>
#include "read_csv.hpp"
#include "util.hpp"
using namespace std;

// returns number of lines processed
int read_line_by_line(const string& file_name) {

	int at_line = 0;

	ifstream in(file_name.c_str());

	string buffer;

	while (getline(in, buffer)) {

		++at_line;

		// buffer has the whole line read
	}

	return at_line;
}

int main(int argc, char* argv[]) {

	vector<string> args(argv, argv+argc);

	string src(args.at(1)), dest(args.at(2));



	bool success = copy_file(src, dest);

	cout << "Copy was successful? " << (success?"yes":"no") << endl;



	int n = read_line_by_line(dest);

	cout << "Read " << n << " lines" << endl;



	read_csv(dest);

	cout << "----------------------------------------------------------------------" << endl;
	cout << "Checking IDs: must be integer" << endl;

	check_id();


	cout << "----------------------------------------------------------------------" << endl;
	cout << "Checking names, must be in a given set" << endl;

	check_names();


	cout << "----------------------------------------------------------------------" << endl;
	cout << "Checking values, must be in a given integer set" << endl;

	check_values();


	cout << "----------------------------------------------------------------------" << endl;
	cout << "Building the table row-by-row as records" << endl;

	convert_table();


	dump_table("dump_"+dest);



	return 0;
}
