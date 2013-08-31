#include "logger.hpp"

void a_function() {

    LOGGER(NORMAL) << "This log is shown at normal, debug and trace levels";

    LOGGER(DEBUG) << "This log is shown at debug and trace levels";

    LOGGER(TRACE) << "This log is only shown at trace level";
}
