#ifndef READ_CSV_HPP
#define READ_CSV_HPP

#include <string>

int read_csv(const std::string& file_name);

void check_id_is_int();

void dump_table(const std::string& file_name);

#endif
