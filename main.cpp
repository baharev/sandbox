#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "read_csv.hpp"
using namespace std;

// returns true if successfull
bool copy_file(const string& source, const string& destination) {

	ifstream in(source.c_str(), ios::binary);

	ofstream out(destination.c_str(), ios::binary);

	out << in.rdbuf();

	return in && out;
}

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

	copy_file(src, dest);

	int n = read_line_by_line(dest);

	cout << "Read " << n << " lines" << endl;

	read_csv(dest);

	check_id_is_int();

	dump_table("dump_"+dest);

	return 0;
}
