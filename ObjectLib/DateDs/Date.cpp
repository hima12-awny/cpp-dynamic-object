#include "Date.h"
#include "../object.h"
#include <chrono>
#include<iomanip>


char Date::find_delimiter(string datestr)
{
	for (char letter : datestr) {
		if (!std::isdigit(letter)) return letter;
	}
	return -1;
}
Date Date::parseDateFromString(string dateStr, DateFormat dateFormat)
{
	unsigned  int year_;
	unsigned char month_;
	unsigned char day_;

	std::istringstream iss(dateStr);

	char delimiter = find_delimiter(dateStr);
	string token;

	switch (dateFormat)
	{
	case DateFormat::YYYY_MM_DD:
	{
		getline(iss, token, delimiter);
		year_ = stoul(token);

		getline(iss, token, delimiter);
		month_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		day_ = static_cast<unsigned char>(stoul(token));
		break;
	}
	case DateFormat::YYYY_DD_MM:
	{
		getline(iss, token, delimiter);
		year_ = stoul(token);

		getline(iss, token, delimiter);
		day_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		month_ = static_cast<unsigned char>(stoul(token));
		break;
	}

	case DateFormat::DD_MM_YYYY:
	{
		getline(iss, token, delimiter);
		day_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		month_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		year_ = stoul(token);

		break;
	}
	case DateFormat::MM_DD_YYYY:
	{
		getline(iss, token, delimiter);
		month_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		day_ = static_cast<unsigned char>(stoul(token));

		getline(iss, token, delimiter);
		year_ = stoul(token);
		break;
	}

	default:
		year_ = 0;
		month_ = 0;
		day_ = 0;
	}


	return Date(year_, month_, day_);
}
vector<Object> Date::validate_date_str(Object date_str)
{
	string str_ = date_str.get();

	char delimiter = find_delimiter(str_);

	if (delimiter == -1) {

		date_str.print_info();
		assert(0 && "Can't to Parse This String to Date");
	}

	int delimiter_counter = 0;
	int str_len = str_.length();

	bool is_my_delimiter;

	for (size_t i = 0; i < str_len; i++)
	{
		is_my_delimiter = str_[i] == delimiter;

		if (is_my_delimiter) {
			if (delimiter_counter == 2) {

				cout << "Can't to Parse This String to Date " << endl <<
					"Because the first Detected delimiter(" << delimiter << ") " <<
					"appears more the 2 times" << endl;

				assert(0);
			}
			++delimiter_counter;
		}

		if (!std::isalnum(str_[i]) && !is_my_delimiter) {

			date_str.print_info();
			cout << "Can't to Parse This String to Date " << endl <<
				"Because there is (" << str_[i] << ") Not Number" <<
				" or Not First Detected delimiter(" << delimiter << ")" << endl;

			assert(0);
		}
	}


	vector<Object> attrs = date_str.split(string(1, delimiter), true);
	int above_31_counter = 0, above_12_counter = 0;

	for (size_t i = 0; i < 3; i++)
	{
		if (attrs[i].type != Dtype::NUMBER) {

			date_str.print_info();
			cout << "Can't to Parse This String to Date " << endl <<
				"Because there is (" << attrs[i] << ") Not Number\n";

			assert(0);
		}
		if (attrs[i] > 31) {

			if (above_31_counter == 1) {

				date_str.print_info();
				cout << "Can't to Parse This String to Date " << endl <<
					"Because there is NUMBER(" << attrs[i] << ") " << 
					"that also bigger than 31 And Year That only Number can be.\n";

				assert(0);
			}
			++above_31_counter;
		}
		if (attrs[i] > 12) {

			if (above_12_counter == 2) {

				date_str.print_info();
				cout << "Can't to Parse This String to Date " << endl <<
					"Because there are Two Numbers "<<
					"that also bigger than 12 And Year and Month That only Number can be.\n";

				assert(0);
			}
			++above_12_counter;
		}
	}
	return attrs;
}

Date::Date() {
	year = 0;
	month = 0;
	day = 0;
}
Date::Date(const char date_str[])
{
	*this = Date(Object(date_str, Dtype::STRING));
}
Date::Date(Object date_str)
{
	DateFormat extracted_format = Date::extractDateFormate(date_str);
	*this = Date(date_str.get(), extracted_format);
}
Date::Date(unsigned int year, unsigned char month, unsigned char day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}
Date::Date(Object datestr, DateFormat dateformat)
{
	*this = parseDateFromString(datestr.get(), dateformat);
}


Object Date::get_year () const
{
	return Object(year, Dtype::DATE_YEAR);
}
Object Date::get_month() const
{
	return Object(month, Dtype::DATE_MONTH);
}
Object Date::get_day  () const
{
	return Object(day, Dtype::DATE_DAY);
}

unsigned int  Date::get_year_num ()
{
	return year;
}
unsigned char Date::get_month_num()
{
	return month;

}
unsigned char Date::get_day_num  ()
{
	return day;
}


string Date::get() const
{
	string str_year  = to_string(year);
	string str_month = to_string(month);
	string str_day   = to_string(day);

	int len_y = 4 - str_year.length();

	for (int i = 0; i < len_y; i++)
	{
		str_year = "0" + str_year;
	}

	if (str_month.length() == 1) {
		str_month = "0" + str_month;
	}

	if (str_day.length() == 1) {
		str_day = "0" + str_day;
	}

	return str_year + "-" + str_month + "-" + str_day;
}


DateFormat Date::extractDateFormate(Object date_str)
{
	vector<Object> attrs = validate_date_str(date_str);

	int year_index = 0, month_index = 1;

	// get year
	for (size_t i = 0; i < 3; i++)
	{
		if (attrs[i] > 31) {
			year_index = i;
			break;
		}
	}

	// get month
	for (size_t i = 0; i < 3; i++)
	{
		if (attrs[i] < 12) {
			month_index = i;
			break;
		}
	}

	if (year_index == 0 && month_index == 1)
		return DateFormat::YYYY_MM_DD;

	else if (year_index == 0 && month_index == 2)
		return DateFormat::YYYY_DD_MM;

	else if (year_index == 2 && month_index == 0)
		return DateFormat::MM_DD_YYYY;
	else
		return DateFormat::DD_MM_YYYY;
	
}

Date Date::now()
{
	time_t currentTime = time(NULL);
	tm localTime;
	localtime_s(&localTime, &currentTime);

	int currentY = localTime.tm_year + 1900;
	int currentM = localTime.tm_mon + 1;
	int currentD = localTime.tm_mday;

	return Date(currentY, currentM, currentD);
}


bool Date::operator < (const Date& other)  const {

	return (
		day   < other.day   &&
		month < other.month &&
		year  < other.year
		);
}
bool Date::operator > (const Date& other)  const {


	return (
		day   > other.day   &&
		month > other.month &&
		year  > other.year
		);
}

bool Date::operator <= (const Date& other) const {

	return (
		day   <= other.day   &&
		month <= other.month &&
		year  <= other.year
		);
}
bool Date::operator >= (const Date& other) const {

	return (
		day   >= other.day   &&
		month >= other.month &&
		year  >= other.year
		);
}

bool Date::operator == (const Date& other) const {

	return (
		day   == other.day   &&
		month == other.month &&
		year  == other.year
		);
}

bool Date::operator < (Object& other)  const
{

	switch (other.type)
	{
	case Dtype::DATE:		return *this < *other.ptr_date();
	case Dtype::DATE_YEAR:  return year  < *other.ptr_date_attr();
	case Dtype::DATE_MONTH: return month < *other.ptr_date_attr();
	case Dtype::DATE_DAY:	return day   < *other.ptr_date_attr();

	default:

		string operation = " == ";
		cout << "Comparision Error:: " <<
			Dtype::DATE << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);

		break;
	}
}
bool Date::operator > (Object& other)  const
{
	switch (other.type)
	{
	case Dtype::DATE:		return *this > *other.ptr_date();
	case Dtype::DATE_YEAR:  return year  > *other.ptr_date_attr();
	case Dtype::DATE_MONTH: return month > *other.ptr_date_attr();
	case Dtype::DATE_DAY:	return day   > *other.ptr_date_attr();

	default:

		string operation = " > ";
		cout << "Comparision Error:: " <<
			Dtype::DATE << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
		break;
	}
}

bool Date::operator <= (Object& other)  const
{
	switch (other.type)
	{
	case Dtype::DATE:		return *this <= *other.ptr_date();
	case Dtype::DATE_YEAR:  return year  <= *other.ptr_date_attr();
	case Dtype::DATE_MONTH: return month <= *other.ptr_date_attr();
	case Dtype::DATE_DAY:	return day   <= *other.ptr_date_attr();

	default:

		string operation = " <= ";
		cout << "Comparision Error:: " <<
			Dtype::DATE << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
		break;
	}
}
bool Date::operator >= (Object& other)  const
{
	switch (other.type)
	{
	case Dtype::DATE:		return *this >= *other.ptr_date();
	case Dtype::DATE_YEAR:  return year  >= *other.ptr_date_attr();
	case Dtype::DATE_MONTH: return month >= *other.ptr_date_attr();
	case Dtype::DATE_DAY:	return day   >= *other.ptr_date_attr();

	default:


		string operation = " >= ";
		cout << "Comparision Error:: " <<
			Dtype::DATE << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;

		assert(0);		
		break;
	}
}

bool Date::operator == (Object& other)  const
{
	switch (other.type)
	{
	case Dtype::DATE:		return *this == *other.ptr_date();
	case Dtype::DATE_YEAR:  return year  == *other.ptr_date_attr();
	case Dtype::DATE_MONTH: return month == *other.ptr_date_attr();
	case Dtype::DATE_DAY:	return day   == *other.ptr_date_attr();

	default:


		string operation = " == ";
		cout << "Comparision Error:: " <<
			Dtype::DATE << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);

		break;
	}
}

Date& Date::operator = (const Date& other)
{
	if (this != &other) {
		day   = other.day;
		month = other.month;
		year  = other.year;
	}
	return *this;
}
