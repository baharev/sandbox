#include <iostream>
#include <sstream>
using namespace std;

void dump(const string& token) {

	static int counter = 0;

	cout << ++counter << "\t{" << token << "}\n";
}

void parse_line(const string& line) {

	istringstream iss(line);

    size_t first(0), pos(0);

    while ((pos = line.find('\t', first)) != std::string::npos) {

   		dump(line.substr(first, pos-first));

        first = pos+1;
    }

    if (first < line.length()) { // adds the empty cell due to trailing tab

    	dump(line.substr(first, std::string::npos));
    }
}


int main() {

	string line("a\tb\t\t\t");

	parse_line(line);

	return 0;
}
