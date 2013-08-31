#include "a.hpp"
#include "b.hpp"

void real_main() {

    a_function();

    b_function();
}

//==============================================================================

#include "logger.hpp"

int main(int argc, char* argv[]) {

    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);

    real_main();

	return 0;
}
