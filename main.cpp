#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
using namespace std;

int main() {
    forward_list<char> trg{'a','b','c'};
    forward_list<char> src{'1','2','3','4'};

    auto before_first = src.begin();
    auto last = find(src.begin(), src.end(), '3');
    cout << "before_first = " << *before_first << ", last = " << *last << "\n";

    // trg.splice(trg.begin(), src, before_first, last); // no such splice
    auto end = last;
    ++end; // Ouch! splice has to find last again although I already had it  :(
    trg.splice_after(trg.begin(), src, before_first, end);

    cout << "Target after splice:\n";
    copy(trg.begin(), trg.end(), ostream_iterator<char>(cout," "));

    cout << "\nSource after splice:\n";
    copy(src.begin(), src.end(), ostream_iterator<char>(cout," "));

    cout << endl;
}

