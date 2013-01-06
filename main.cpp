#include <iostream>
#include <sstream>
using namespace std;

int counter = 0;

void dump(const string& token) {

	cout << ++counter << "\t{" << token << "}\n";
}

void parse(const string& line) {

	counter = 0;

	istringstream iss(line);

    size_t first(0), pos(0);

    while ((pos = line.find('\t', first)) != std::string::npos) {

    	//cout << "while\n";

   		dump(line.substr(first, pos-first));

        first = pos+1;
    }

    if (first < line.length()) { // adds the empty cell due to trailing tab

    	//cout << "if\n";

    	dump(line.substr(first, std::string::npos));
    }
}

void parse2(const string& line) {

	counter = 0;

	istringstream iss(line);

	string token;

    while (getline(iss, token, '\t')) {

   		dump(token);
    }
}

int main() {

	string a("a\t\t");

	parse2(a);

	cout << "-------------------------" << endl;

	string b("a\t");

	parse2(b);

	return 0;
}
