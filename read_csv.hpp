#ifndef READ_CSV_HPP
#define READ_CSV_HPP

#include <string>

int read_csv(const std::string& file_name);

void check_id();

void check_names();

void check_values();

void dump_table(const std::string& file_name);

#endif
