#pragma once

#ifndef STRING_cls
#define STRING_cls

#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <cctype>
#include "../enums/enums.h"

class Object;

using namespace std;


class String {

	string value;

	vector<size_t> get_min_find(string value, vector<string> from, int start_pos);

public:

	String();
	String(string value);
	String(const char value[]);
	string get() const;

	String stripl();
	String stripr();
	String strip();
	size_t len() const;

	int count(string target);

	String		   substr (int start, int end=-1);
	size_t         find   (string target, int start=0);
	String         replace(string from, string to);
	vector<Object> split  (string sep="", bool parsing_numbers=false);
	String static  join   (string sep, vector<Object> arr);

	String up();
	String lw();
	String title();

	String operator + (const String& other) const;
	String operator - (const String& other) const;
	String operator * (const float& other) const;

	void operator += (const String& other);
	void operator -= (const String& other);
	void operator *= (const float& other);

	// Comparison operators String
	bool operator < (const String& other) const;
	bool operator > (const String& other) const;
	bool operator <=(const String& other) const;
	bool operator >=(const String& other) const;
	bool operator ==(const String& other) const;
	bool operator !=(const String& other) const;


	String& operator=(const String& onther) {
		
		value = onther.value;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const String& obj) {
		os << obj.value;
		return os;
	}

};


#endif // !STRING

