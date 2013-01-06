#include <string>
#include <vector>
#include "ReservedColumnNames.hpp"
#include "util.hpp"

using namespace std;

namespace {

// TODO Agree on the identifiers, then share the code with the GUI
// TODO If changes -> update the enum of columns appropriately
const string headers[] = {
		"DATA_ID",
		"GROUP_CODE",
		"COLOR_CODE",
		"LOCATION",
		"LOC_X",
		"LOC_Y",
		"FORMATION",
		"DATATYPE",
		"DIP_DIR",
		"DIP",
		"L_DIR",
		"L_DIP",
		"SENSE",
		"PALEONORTH",
		"COMMENT"
};

const vector<string> reserved_headers = from_array(headers);

}

const std::vector<std::string>& reserved_column_names() {

	return reserved_headers;
}
