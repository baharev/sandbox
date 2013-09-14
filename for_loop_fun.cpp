#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <typename Cont, typename Func>
void for_each_indexed(const Cont& c, Func f, size_t index = 0) {

  for (const auto& e : c)

    f(index++, e);

}

void have_fun() {

  set<char> s{'b', 'a', 'c'};

  // with index, starting with 1 instead of 0
  for_each_indexed(s, [](size_t i, char e) { cout<<i<<'\t'<<e<<'\n'; } , 1);

  cout << "-----" << endl;

  vector<int> v{77, 88, 99};

  // without index
  for_each_indexed(v, [](size_t i, int e) { cout<<i<<'\t'<<e<<'\n'; });

}
