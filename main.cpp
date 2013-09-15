//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//

#include "test_runner.hpp"

int main(int argc, char* argv[]) {

    test_runner tr(argc, argv);

    tr.execute();

    return 0;
}

