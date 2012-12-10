#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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

		// extract whatever is in it
		stringstream line(buffer, ios::in);

		int id;
		string name;
		string comment;

		line >> id; // ignores errors

		getline(line, name, '\t'); // ignores errors

		getline(line, comment); // ignores errors
	}

	return at_line;
}

int main(int argc, char* argv[]) {

	vector<string> args(argv, argv+argc);

	copy_file(args.at(1), args.at(2));

	int n = read_line_by_line(args.at(2));

	cout << "Read " << n << " lines" << endl;

	return 0;
}
