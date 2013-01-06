#include <iostream>
#include <sstream>
using namespace std;

int counter = 0;

void dump(const string& token) {

	cout << ++counter << "\t{" << token << "}\n";
}

void parse_line(const string& line) {

	counter = 0;

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

	string a("\t");
	string b("\n");

	parse_line(a);

	cout << "-------------------------" << endl;

	parse_line(b);

	return 0;
}
