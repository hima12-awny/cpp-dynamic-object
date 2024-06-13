
#ifndef ENUMS
#define ENUMS

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

enum class Dtype {
	STRING,
	NUMBER,

	DATE,
	DATE_YEAR,
	DATE_MONTH,
	DATE_DAY,

	NA
};
std::ostream& operator<<(std::ostream& os, const Dtype& dtype); // Declaration

// Declaration of the unordered map
extern const unordered_map<Dtype, string> dtypeMap;

enum class DateFormat {

	YYYY_MM_DD,
	YYYY_DD_MM,
	DD_MM_YYYY,
	MM_DD_YYYY
};

std::ostream& operator<<(std::ostream& os, const DateFormat& dtype); // Declaration


#endif