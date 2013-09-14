#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <glog/logging.h>

enum level {
    NONE, // Don't use it!
    NORMAL,
    DEBUG,
    TRACE
};

#define LOGGER(level)  VLOG(level)<<__FILE__<<':'<<__LINE__<<"   "<<__PRETTY_FUNCTION__ << "   "

#endif

