#include "enums.h"


// Definition and initialization of the unordered map
const unordered_map<Dtype, string> dtypeMap = {
	{Dtype::STRING     	, "STRING"},
	{Dtype::NUMBER		, "NUMBER"},
	{Dtype::DATE		, "DATE"},
	{Dtype::DATE_YEAR	, "DATE_YEAR"},
	{Dtype::DATE_MONTH	, "DATE_MONTH"},
	{Dtype::DATE_DAY	, "DATE_DAY"},
	{Dtype::NA		, "NA"}
};

std::ostream& operator<<(std::ostream& os,const Dtype& dtype) {

	os << dtypeMap.at(dtype);

	return os;
}
	
std::ostream& operator<<(std::ostream& os, const DateFormat& dateFormate) {

	switch (dateFormate)
	{
	case DateFormat::YYYY_MM_DD:
		os << "YYYY_MM_DD";
		break;

	case DateFormat::YYYY_DD_MM:
		os << "YYYY_DD_MM";
		break;

	case DateFormat::DD_MM_YYYY:
		os << "DD_MM_YYYY";
		break;
	case DateFormat::MM_DD_YYYY:
		os << "MM_DD_YYYY";
		break;

	default:
		break;
	}
	return os;
}
