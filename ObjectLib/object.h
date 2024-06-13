#pragma once

#ifndef Object_CLS
#define Object_CLS

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <random>

#include "StringDs/String.h"
#include "DateDs/Date.h"

#include "enums/enums.h"

using namespace std;

class Object
{
    void* value;
	Dtype getTypeFromStr(const string& str);

	void copyFrom(const Object& other);
	void desteroy();

	Object to_date_attr(Dtype date_attr_type);

public:

	Dtype type;

	Object() noexcept;

	Object(String invalue, Dtype intype);

	Object(const char invalue[]);
	Object(string invalue);

	Object(String invalue);

	Object(double invalue);
	Object(const Object& invalue);

	Object(Date date);
	Object(unsigned int year, unsigned char month, unsigned char day);
	Object(string datestr, DateFormat dateformat);
	Object(Object datestr, DateFormat dateformat);

	Object(unsigned int date_attr, Dtype date_attr_type);

	~Object();

	String* ptr_str() const;
	double* ptr_num() const;
	Date* ptr_date () const;
	unsigned int* ptr_date_attr() const;

	// genrail
	string get();
	void print_info();

	// date attr
	Object getYear ();
	Object getMonth();
	Object getDay  ();

	// string 
	Object stripl();
	Object stripr();
	Object strip ();
	size_t len   ();

	int count(string target);
	vector<Object> split(string sep="", bool enable_numbers = false);
	Object replace(string from, string to);

	Object substr(int start, int end=-1);

	Object    up();
	Object    lw();
	Object title();
	size_t find(string target, int start = 0);


	//////////////////////////////////////////
	// 
	// Numbers ///////////////////////////////


	static Object         rand_num (int max=1000, int min = 0);
	static vector<Object> rand_nums(int size, int max, int min = 0);

	//////////////////////////////////////////


	// generating random things
	// numbers

	static Date rand_date();

	// converting (parseing) a group a value of some dtype to Object.

	Object to_str ();
	Object to_num ();
	Object to_date();

	Object to_date_day  ();
	Object to_date_month();
	Object to_date_year ();


	static vector<Object> from_vector_string(vector<string> values);
	static vector<Object> from_vector_double(vector<double> values);
	static vector<Object> from_vector_int   (vector<int   > values);
	static vector<Object> from_set_string   (set   <string> values);

	Object& operator = (const Object& other);

	Object operator + (Object other);
	Object operator - (Object other);
	Object operator / (Object other);
	Object operator * (Object other);

	Object operator + (double other);
	Object operator - (double other);
	Object operator / (double other);
	Object operator * (double other);

	void operator += (Object other);
	void operator -= (Object other);
	void operator /= (Object other);
	void operator *= (Object other);

	void operator += (double other);
	void operator -= (double other);
	void operator /= (double other);
	void operator *= (double other);

	bool operator < (Object other);
	bool operator > (Object other);
	bool operator <= (Object other);
	bool operator >= (Object other);
	bool operator == (Object other);

	friend ostream& operator <<(ostream& os,const Object& obj);
};
#endif // !Object_CLS
