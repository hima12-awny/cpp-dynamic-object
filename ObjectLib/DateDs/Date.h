#pragma once


#ifndef DATE_CLS
#define DATE_CLS

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

#include "../enums/enums.h"

class Object;


using namespace std;

class Date
{
	unsigned int  year;
	unsigned char month;
	unsigned char day;

	char find_delimiter(string datestr);
	Date parseDateFromString(string dateStr, DateFormat dateFormat);
	vector<Object> validate_date_str(Object date_str);

public:

	Date();
	Date(const char date_str[]);
	Date(Object date_str);
	Date(unsigned int year, unsigned char month, unsigned char day);
	Date(Object datestr, DateFormat dateformat);


	static Date now();


	Object get_year()  const;
	Object get_month() const;
	Object get_day()   const;

	unsigned int get_year_num  ();
	unsigned char get_month_num();
	unsigned char get_day_num  ();

	string get() const;

	DateFormat extractDateFormate(Object date_str);



	bool operator < (const Date& other) const;
	bool operator > (const Date& other) const;

	bool operator <= (const Date& other) const;
	bool operator >= (const Date& other) const;
	bool operator == (const Date& other) const;


	bool operator < (Object& other) const;
	bool operator > (Object& other) const;

	bool operator <= (Object& other) const;
	bool operator >= (Object& other) const;
	bool operator == (Object& other) const;

	Date& operator = (const Date& otherDate);

	friend ostream& operator << (ostream& os, const Date& date) {
		os << date.get();
		return os;
	}
};


#endif // !DATE