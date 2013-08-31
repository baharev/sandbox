#include <vector>
#include <string>
#include "b.hpp"
#include "logger.hpp"

using namespace std;

void vector_fun();

void b_function() {

    LOGGER(NORMAL) << "This log is shown at normal, debug and trace levels";

    LOGGER(DEBUG) << "This log is shown at debug and trace levels";

    LOGGER(TRACE) << "This log is only shown at trace level";

    vector_fun();
}

void vector_fun() {

    LOGGER(DEBUG) << "Dumping a vector of strings, just for fun";

    vector<string> v = { "1", "2", "3" };

    for (auto&& e : v) {

        LOGGER(DEBUG) << e;
    }

}
