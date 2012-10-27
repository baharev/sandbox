#include <iostream>
using namespace std;

class C {
public:
	C() : v(nullptr) { }

	C& operator=(const C& other) {
    	cout << "copy" << endl;
    	// copy contents of v[]
    	return *this;
    }

    C& operator=(C&& other) {
    	cout << "move" << endl;
    	v = other.v, other.v = nullptr;
    	return *this;
    }

private:
	int* v;
};

const C const_is_returned() { return C(); }

C nonconst_is_returned() { return C(); }

int main(int argc, char* argv[]) {
	C c;
	c = const_is_returned();
	c = nonconst_is_returned();
	return 0;
}
