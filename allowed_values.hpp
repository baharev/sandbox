#ifndef ALLOWED_VALUES_HPP
#define ALLOWED_VALUES_HPP

#include <string>

bool is_allowed_name(const std::string& s);

bool is_allowed_name_ignore_case(const std::string& s);

bool is_allowed_number(int i);

bool is_allowed_number(const std::string& s);

#endif
