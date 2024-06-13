#include "Object.h"

Dtype Object::getTypeFromStr(const string& str)
{
	// detect if an alpha letter or 
	// an not a digit and is not a "."
	// so the type is a string 
	// else The type is a number.

	if (str == ".") return Dtype::STRING;

	for (char letter : str) {

		if (isalpha(letter) || (!isdigit(letter) && letter != '.')) return Dtype::STRING;
	}
	
	return Dtype::NUMBER;
}

void Object::copyFrom(const Object& other)
{

	if (this == &other) return;

	type = other.type;

	switch (type) {

	case Dtype::STRING:
		value = new String(*((String*)other.value));
		break;
	case Dtype::NUMBER:
		value = new double(*((double*)other.value));
		break;

	case Dtype::DATE:
		value = new Date(*((Date*)other.value));
		break;

	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		value = new unsigned int(*((unsigned int*)other.value));
		break;


	case Dtype::NA:
		value = nullptr;
		break;
	default:
		break;
	}
}

String* Object::ptr_str	() const
{
	return (String*)value;
}
double* Object::ptr_num	() const
{
	return (double*)value;
}
Date*	Object::ptr_date() const
{
	return (Date*)value;
}
unsigned int* Object::ptr_date_attr() const
{
	return (unsigned int*)value;
}


void Object::desteroy()
{
	if (value != nullptr) {

		switch (type) {

		case Dtype::STRING:
			delete ptr_str();
			break;

		case Dtype::NUMBER:
			delete ptr_num();
			break;

		case Dtype::DATE:
			delete ptr_date();
			break;
		
		case Dtype::DATE_YEAR:
		case Dtype::DATE_MONTH:
		case Dtype::DATE_DAY:
			delete ptr_date_attr();
			break;


		default:
			break;
		}
		value = nullptr;
		type = Dtype::NA;
	}
}


Object::Object() noexcept
{
    value = NULL;
    type = Dtype::NA;
}

//Object::Object(string invalue, Dtype intype)
//{
//
//	type = intype;
//
//	// to parse it and put it in right place.
//	switch (type)
//	{
//	case Dtype::STRING:
//	{
//		value = new String(invalue);
//		break;
//	}
//
//	case Dtype::NUMBER:
//	{
//		value = new double(stod(invalue));
//		break;
//	}
//	case Dtype::NA:
//		value = NULL;
//		break;
//	default:
//
//		value = NULL;
//		break;
//	}
//
//}
Object::Object(String invalue, Dtype intype)
{
	type = intype;

	// to parse it and put it in right place.
	switch (type)
	{
	case Dtype::STRING:
	{
		value = new String(invalue);
		break;
	}
	case Dtype::NUMBER:
	{
		value = new double(stod(invalue.get()));
		break;
	}
	case Dtype::NA:
		value = NULL;
		break;
	default:

		value = NULL;
		break;
	}
}

Object::Object(const char invalue[])
{
	 type = getTypeFromStr(invalue);

	 // to parse it and put it in right place.
	 switch (type)
	 {
	 case Dtype::STRING:
	 {
		 value = new String(invalue);
		 break;
	 }

	 case Dtype::NUMBER:
	 {
		 value = new double(stod(invalue));
		 break;
	 }
	 case Dtype::NA:
		 value = NULL;
		 break;
	 default:

		 value = NULL;
		 break;
	 }
}

Object::Object(string invalue)
{
	type = getTypeFromStr(invalue);

	// to parse it and put it in right place.
	switch (type)
	{
	case Dtype::STRING:
	{
		value = new String(invalue);
		break;
	}

	case Dtype::NUMBER:
	{
		value = new double(stod(invalue));
		break;
	}
	case Dtype::NA:
		value = NULL;
		break;
	default:

		value = NULL;
		break;
	}
}

Object::Object(String invalue)
{
	type = getTypeFromStr(invalue.get());

	// to parse it and put it in right place.
	switch (type)
	{
	case Dtype::STRING:
	{
		value = new String(invalue);
		break;
	}

	case Dtype::NUMBER:
	{
		value = new double(stod(invalue.get()));
		break;
	}
	case Dtype::NA:
		value = NULL;
		break;
	default:

		value = NULL;
		break;
	}
}

Object::Object(double invalue)
{
	value = new double(invalue);
	type = Dtype::NUMBER;
}

Object::Object(const Object& invalue)
{
	copyFrom(invalue);
}


// date constructors
Object::Object(Date date)
{
	value = new Date(date.get_year_num(), date.get_month_num(), date.get_day_num());
	type = Dtype::DATE;

}

Object::Object(unsigned int year, unsigned char month, unsigned char day)
{
	type = Dtype::DATE;
	value = new Date(year, month, day);
}

Object::Object(string datestr, DateFormat dateformat)
{
	type = Dtype::DATE;
	value = new Date(datestr, dateformat);
}

Object::Object(Object datestr, DateFormat dateformat)
{
	type = Dtype::DATE;
	value = new Date(datestr, dateformat);
}

Object::Object(unsigned int date_attr, Dtype date_attr_type)
{
	type = date_attr_type;
	value = new unsigned int(date_attr);
}

Object::~Object()
{
	desteroy();
}

string Object::get() {

	if (value != nullptr) {

		switch (type) {

		case Dtype::STRING:
			return (*ptr_str()).get();

		case Dtype::NUMBER: {

			double temp_num = *ptr_num();
			int num_int = temp_num;
			if (temp_num == num_int) {
				return to_string(num_int);
			}
			return to_string(temp_num);
		}
		case Dtype::DATE:
			return	(*ptr_date()).get();
			break;

		case Dtype::DATE_YEAR:
		case Dtype::DATE_MONTH:
		case Dtype::DATE_DAY:
			return  to_string(*ptr_date_attr());

		default:
			assert(0 && "The Value IS Not Can't be get");
			break;
		}
	}
	else {
		return "NULL";
	}
}

void Object::print_info()
{

	string str = this->get();
	if (str.length() > 30) {

		str = str.substr(0, 30) + "... (len:" + to_string(str.length()) + ")";
	}

	cout << endl;
	cout << "Object {" << endl;
	cout << " value: " << str << endl;
	cout << " dtype: " << type << endl;
	cout << "}" << endl;
}

// date attrs
Object Object::getYear ()
{
	if (type == Dtype::DATE) {

		return ptr_date()->get_year();	
	}

	print_info();
	assert(false && "this Methoud (getYear) Valied only for DATE dtype.");
}
Object Object::getMonth()
{
	if (type == Dtype::DATE) {

		return ptr_date()->get_month();
	}

	print_info();
	assert(false && "this Methoud (getMonth) Valied only for DATE dtype.");
}
Object Object::getDay  ()
{
	if (type == Dtype::DATE) {

		return ptr_date()->get_day();
	}

	print_info();
	assert(false && "Methoud (getDay) Valied only for DATE dtype.");
}

// string 
Object Object::stripl()
{
	if (type == Dtype::STRING) {
		return ptr_str()->stripl();
	}

	print_info();
	assert(false && "Methoud (stripl) Valied only for STRING dtype.");
}
Object Object::stripr()
{
	if (type == Dtype::STRING) {
		return ptr_str()->stripr();
	}

	print_info();
	assert(false && "Methoud (stripr) Valied only for STRING dtype.");
}
Object Object::strip ()
{
	if (type == Dtype::STRING) {
		return ptr_str()->strip();
	}

	print_info();
	assert(false && "Methoud (strip) Valied only for STRING dtype.");
}

size_t Object::len()
{
	if (type == Dtype::STRING) {
		return ptr_str()->len();
	}

	print_info();
	assert(false && "Methoud (len) Valied only for STRING dtype.");
}

int Object::count(string target)
{
	if (type == Dtype::STRING) {
		return ptr_str()->count(target);
	}

	print_info();
	assert(false && "Methoud (count) Valied only for STRING dtype.");
}	

vector<Object> Object::split(string sep, bool enable_numbers)
{
	if (type == Dtype::STRING) {
		return ptr_str()->split(sep, enable_numbers);
	}

	print_info();
	assert(false && "Methoud (split) Valied only for STRING dtype.");
}

size_t		   Object::find(string target, int start)
{
	if (type == Dtype::STRING) {
		return ptr_str()->find(target, start);
	}

	print_info();
	assert(false && "Methoud (find) Valied only for STRING dtype.");
}


Object Object::replace(string from ,string to )
{
	if (type == Dtype::STRING) {
		return Object(ptr_str()->replace(from, to), Dtype::STRING);
	}

	print_info();
	assert(false && "Methoud (replace) Valied only for STRING dtype.");
}
Object Object::substr (int    start,   int end)
{
	if (type == Dtype::STRING) {
		return Object(ptr_str()->substr(start, end), Dtype::STRING);
	}

	print_info();
	assert(false && "Methoud (substr) Valied only for STRING dtype.");
}

Object Object::up()
{
	if (type == Dtype::STRING) {
		return Object(ptr_str()->up(), Dtype::STRING);
	}

	print_info();
	assert(false && "Methoud (up) Valied only for STRING dtype.");
}
Object Object::lw()
{
	if (type == Dtype::STRING) {
		return Object(ptr_str()->lw(), Dtype::STRING);
	}
	print_info();
	assert(false && "Methoud (lw) Valied only for STRING dtype.");
}
Object Object::title()
{
	if (type == Dtype::STRING) {
		return Object(ptr_str()->title(), Dtype::STRING);
	}

	print_info();
	assert(false && "Methoud (title) Valied only for STRING dtype.");
}


// generating random things
Object Object::		   rand_num (int max, int min)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for integers in the range [min, max]
	std::uniform_int_distribution<int> dist(min, max);

	return Object(dist(gen));
}
vector<Object> Object::rand_nums(int size, int max, int min)
{
	vector<Object> values(size);

	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for integers in the range [min, max]
	std::uniform_int_distribution<int> dist(min, max);

	for (int i = 0; i < size; i++)
	{
		values[i] = dist(gen);
	}

	return values;
}
Date Object::		   rand_date()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for integers in the range [min, max]
	std::uniform_int_distribution<int> dist(0, 10000);


	int year  = 1900 + dist(gen) % 125;  // Random year between 1900 and 2024
	int month = 1    + dist(gen) % 12;   // Random month between 1 and 12
	int day   = 1    + dist(gen) % 31;   // Random day between 1 and 31 (not handling leap years)

	return Date(year, month, day);
}


// convertings

Object Object::to_str()
{
	return Object(get(), Dtype::STRING);
}
Object Object::to_num()
{
	switch (type)
	{
	case Dtype::STRING: {

		try
		{
			double value_num = stod(ptr_str()->get());
			return Object(value_num);
		}
		catch (const std::exception&)
		{
			print_info();
			assert(false && "Can't Converting The string to Number.");
		}

		break;
	}
	case Dtype::NUMBER:
		return Object(*ptr_num());
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		return Object(*ptr_date_attr());

		break;
	default:
		{
			print_info();
			assert(false && "Can't Converting The string to Number.");
			break;
		}
	}
}

Object Object::to_date()
{
	if (type == Dtype::STRING) {
		return Object(Date(*ptr_str()));
	}
	else if (type == Dtype::DATE)
		return *this;

	print_info();
	assert(false && "Can't Converting The Object to Date.");
}

Object Object::to_date_attr(Dtype date_attr_type)
{
	if (type == date_attr_type) return *this;

	switch (type)
	{
	case Dtype::STRING: {

		try
		{
			double value_num = stod(ptr_str()->get());
			return Object(value_num, date_attr_type);
		}
		catch (const std::exception&)
		{
			print_info();
			cout << "Can't Converting The string to " << date_attr_type;
			assert(false);
		}

		break;
	}
	case Dtype::NUMBER:
		return Object(*ptr_num(), date_attr_type);
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		return Object(*ptr_date_attr(), date_attr_type);

		break;
	default:
		{
			print_info();
			cout << "Can't Converting The " << *this << " to " << date_attr_type;
			assert(false);
		}
	}
}

Object Object::to_date_day  ()
{
	return to_date_attr(Dtype::DATE_DAY);
}
Object Object::to_date_month()
{
	return to_date_attr(Dtype::DATE_MONTH);
}
Object Object::to_date_year ()
{
	return to_date_attr(Dtype::DATE_YEAR);
}


vector<Object> Object::from_vector_string(vector<string> values)
{
	int values_size = values.size();

	vector<Object> res(values_size);
	for (int i = 0; i < values_size; i++)
	{
		//res[i] = Object(values[i]); old version
		res[i] = values[i];
	}
	return res;
}
vector<Object> Object::from_vector_double(vector<double> values)
{
	int values_size = values.size();

	vector<Object> res(values_size);
	for (int i = 0; i < values_size; i++)
	{
		//res[i] = Object(values[i]); old version
		res[i] = values[i];
	}
	return res;
}
vector<Object> Object::from_vector_int	 (vector<int   > values)
{
	int values_size = values.size();

	vector<Object> res(values_size);
	for (int i = 0; i < values_size; i++)
	{
		//res[i] = Object(values[i]); old version
		res[i] = values[i];
	}
	return res;
}
vector<Object> Object::from_set_string	 (set   <string> values)
{
	vector<Object> res(values.size());

	int i = 0;
	for (string value : values) {
		//res[i++] = Object(value);
		res[i++] = value;
	}

	return res;
}


Object& Object::operator =(const Object& other)
{
	if (this->type != other.type) {
		desteroy();
		copyFrom(other);
	}
	else {
		switch (type)
		{
		case Dtype::STRING:
			*ptr_str() = *other.ptr_str();
			break;

		case Dtype::NUMBER:
			*ptr_num() = *other.ptr_num();
			break;

		case Dtype::DATE:
			*ptr_date() = *other.ptr_date();
			break;

		case Dtype::DATE_YEAR:
		case Dtype::DATE_MONTH:
		case Dtype::DATE_DAY:
			*ptr_date_attr() = *other.ptr_date_attr();
			break;
		default:
			break;
		}
	}
	
	return *this;
}


Object Object::operator +(Object other)
{

	if (type != other.type) {
		string operation = " + ";
		cout << "Calculation Error:: "<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return Object(*ptr_str() + *other.ptr_str(), Dtype::STRING);
	case Dtype::NUMBER:
		return  Object(*ptr_num() + *other.ptr_num());
	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY: 
		return  Object(*ptr_date_attr() + *other.ptr_date_attr(), type);
	
	case Dtype::NA:
		break;
	default:
		break;
	}

	return Object();
}
Object Object::operator -(Object other)
{
	if (type != other.type) {
		string operation = " - ";
		cout << "Calculation Error:: "<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
	{
		return Object(*ptr_str() - *other.ptr_str(), Dtype::STRING);
		break;
	}
	case Dtype::NUMBER:
		return  Object(*ptr_num() - *other.ptr_num());
		break;
	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		return  Object(*ptr_date_attr() - *other.ptr_date_attr(), type);

		break;
	case Dtype::NA:
		break;
	default:
		break;
	}

	return Object();
}
Object Object::operator /(Object other)
{

	assert(

		((type != Dtype::STRING || other.type != Dtype::STRING) || 
			(type != Dtype::DATE || other.type != Dtype::DATE))

		&& "Calculation Error:: can't handle / with strings");

	if (type != other.type) {
		string operation = " / ";
		cout << "Calculation Error:: " 
			<< dtypeMap.at(type)	   + "(" << *this << ")"
			<< operation
			<< other.type <<  "(" << other << ")" 
			<< endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::NUMBER:
		return  Object(*ptr_num() / *other.ptr_num());
	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		return  Object(*ptr_date_attr() / *other.ptr_date_attr(), type);

	case Dtype::NA:
		break;
	default:
		break;
	}

	return Object();
}
Object Object::operator *(Object other)
{

	bool is_str_op = ((type == Dtype::STRING && other.type == Dtype::NUMBER) ||
					  (type == Dtype::NUMBER && other.type == Dtype::STRING));


	assert(!is_str_op
		&& "Calculation Error:: can't handle * with strings");

	if (type != other.type && !is_str_op) {
		string operation = " * ";
		cout << "Calculation Error:: "
			<<  type << "(" << *this << ")"
			<< operation
			<< other.type << "(" << other << ")"
			<< endl;
		assert(0);
	}



	switch (type)
	{
	case Dtype::STRING:
		return Object(*ptr_str() * *other.ptr_num(), Dtype::STRING);
	
	case Dtype::NUMBER:
	{
		switch (other.type)
		{
		case Dtype::STRING: return Object(*other.ptr_str() * *ptr_num());
		case Dtype::NUMBER: return Object(*other.ptr_num() * *ptr_num());

		default:
			break;
		}
		break;
	}

	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		return  Object(*ptr_date_attr() * *other.ptr_date_attr(), type);

	case Dtype::NA:
		break;
	default:
		break;
	}

	return Object();
}

Object Object::operator +(double other)
{
	if (type == Dtype::NUMBER) {
		return Object(*ptr_num() + other);
	}

	string operation = " + ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);

	return Object();
}
Object Object::operator -(double other)
{
	if (type == Dtype::NUMBER) {
		return Object(*ptr_num() - other);
	}

	string operation = " - ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);
	return Object();
}
Object Object::operator /(double other)
{
	if (type == Dtype::NUMBER) {
		return Object(*ptr_num() / other);
	}

	string operation = " / ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);

	return Object();
}
Object Object::operator *(double other)
{
	if (type == Dtype::NUMBER) {
		return Object(*ptr_num() * other);
	}
	else if (type == Dtype::STRING) {
		return Object(*ptr_str() * other, Dtype::STRING);
	}

	string operation = " * ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);


	return Object();
}


void Object::operator +=(Object other)
{
	if (type != other.type) {
		string operation = " + ";
		cout << "Calculation Error:: "<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		*ptr_str() = *ptr_str() + *other.ptr_str();

	case Dtype::NUMBER:
		*ptr_num() = *ptr_num() + *other.ptr_num();

	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;

	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		*ptr_date_attr() = *ptr_date_attr() + *other.ptr_date_attr();
	default:
		break;
	}
}
void Object::operator -=(Object other)
{
	if (type != other.type) {
		string operation = " - ";
		cout << "Calculation Error:: " 
			+ dtypeMap.at(type)	      + "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		*ptr_str() = *ptr_str() - *other.ptr_str();
	case Dtype::NUMBER:
		*ptr_num() = *ptr_num() - *other.ptr_num();

	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;

	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		*ptr_date_attr() = *ptr_date_attr() - *other.ptr_date_attr();
	default:
		break;
	}
}
void Object::operator /=(Object other)
{
	assert(

		((type != Dtype::STRING || other.type != Dtype::STRING) ||
			(type != Dtype::DATE || other.type != Dtype::DATE))

		&& "Calculation Error:: can't handle / with strings");

	if (type != other.type) {
		string operation = " / ";
		cout << "Calculation Error:: "
			<<  type << "(" << *this << ")"
			<< operation
			<< other.type <<  "(" << other << ")"
			<< endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::NUMBER: {
		*ptr_num() = (*ptr_num() / *other.ptr_num());
		break;
	}
		
	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY: {
		*ptr_date_attr() = *ptr_date_attr() / *other.ptr_date_attr();
	}
		

	case Dtype::NA:
		break;
	default:
		break;
	}
}
void Object::operator *=(Object other)
{
	bool is_str_op = ((type == Dtype::STRING && other.type == Dtype::NUMBER) ||
		(type == Dtype::NUMBER && other.type == Dtype::STRING));

	assert(!is_str_op && "Calculation Error:: can't handle *= with strings and numbers");

	if (type != other.type) {
		string operation = " * ";
		cout << "Calculation Error with *= :: "
			<<  type << "(" << *this << ")"
			<< operation
			<< other.type <<  "(" << other << ")"
			<< endl;
		assert(0);
	}


	switch (type)
	{

	case Dtype::NUMBER:
	{
		*ptr_num() = *other.ptr_num() * *ptr_num();
		break;
	}

	case Dtype::DATE:
		assert(false && "The Date Object Not Handled");
		break;
	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
		*ptr_date_attr() = *ptr_date_attr() * *other.ptr_date_attr();
		break;

	case Dtype::NA:
		break;
	default:
		break;
	}


}

void Object::operator +=(double other)
{
	if (type == Dtype::NUMBER) {
		*ptr_num() += other;
		return;

	}

	string operation = " + ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);

}
void Object::operator -=(double other)
{
	if (type == Dtype::NUMBER) {
		*ptr_num() -= other;
		return;
	}

	string operation = " - ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);
}
void Object::operator /=(double other)
{
	if (type == Dtype::NUMBER) {
		*ptr_num() /= other;
		return;
	}

	string operation = " / ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);
}
void Object::operator *=(double other)
{
	if (type == Dtype::NUMBER) {
		*ptr_num() *= other;
		return;
	}

	string operation = " * ";
	cout << "Calculation Error:: "
		<<  type << "(" << *this << ")"
		<< operation
		<< "NUMBER (" << other << ")"
		<< endl;
	assert(0);
}


bool Object::operator < (Object other) 
{

	if (type != other.type && (
		type == Dtype::STRING || 
		type == Dtype::NUMBER || 
		type == Dtype::NA	  	
		)) {
		string operation = " < ";
		cout << "Comparision Error:: " 
			<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return *ptr_str() < *other.ptr_str();

	case Dtype::NUMBER:
		return *ptr_num() < *other.ptr_num();
	case Dtype::DATE:

		return *ptr_date() < other;
	case Dtype::DATE_YEAR: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() < other.ptr_date()->get_year_num();
		case Dtype::DATE_YEAR: return *ptr_date_attr() < *other.ptr_date_attr();
		default:
			break;
		}

	}
	case Dtype::DATE_MONTH: {

		switch (other.type)
		{
		case Dtype::DATE:       return *ptr_date_attr() < other.ptr_date()->get_month_num();
		case Dtype::DATE_MONTH: return *ptr_date_attr() < *other.ptr_date_attr();
		default:
			break;
		}
	}
	case Dtype::DATE_DAY: {

		switch (other.type)
		{
		case Dtype::DATE:     return *ptr_date_attr() < other.ptr_date()->get_day_num();
		case Dtype::DATE_DAY: return *ptr_date_attr() < *other.ptr_date_attr();
		default:
			break;
		}
	}
		
	case Dtype::NA: return 1;

	default:
		break;
	}

	return false;
}
bool Object::operator > (Object other)
{
	if (type != other.type && (
		type == Dtype::STRING ||
		type == Dtype::NUMBER ||
		type == Dtype::NA
		)) {
		string operation = " > ";
		cout << "Comparision Error:: "
			<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return (*ptr_str() > *other.ptr_str());
		break;
	case Dtype::NUMBER:
		return (*ptr_num() > *other.ptr_num());
		break;
	case Dtype::DATE:
		return (*ptr_date() > other);
		break;

	case Dtype::DATE_YEAR: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() > other.ptr_date()->get_year_num();
		case Dtype::DATE_YEAR: return *ptr_date_attr() > *other.ptr_date_attr();
		default:
			break;
		}

	}
	case Dtype::DATE_MONTH: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() > other.ptr_date()->get_month_num();
		case Dtype::DATE_MONTH: return *ptr_date_attr() > *other.ptr_date_attr();
		default:
			break;
		}
	}
	case Dtype::DATE_DAY: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() > other.ptr_date()->get_day_num();
		case Dtype::DATE_DAY: return *ptr_date_attr() > *other.ptr_date_attr();
		default:
			break;
		}
	}

	case Dtype::NA: return 1;

	default:
		break;
	}

	return false;
}
bool Object::operator <=(Object other)
{
	if (type != other.type && (
		type == Dtype::STRING ||
		type == Dtype::NUMBER ||
		type == Dtype::NA
		)) {
		string operation = " <= ";
		cout << "Comparision Error:: "
			<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return (*ptr_str() <= *other.ptr_str());
		break;
	case Dtype::NUMBER:
		return (*ptr_num() <= *other.ptr_num());
		break;
	case Dtype::DATE:
		return (*ptr_date() <= other);
		break;

	case Dtype::DATE_YEAR: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() <= other.ptr_date()->get_year_num();
		case Dtype::DATE_YEAR: return *ptr_date_attr() <= *other.ptr_date_attr();
		default:
			break;
		}

	}
	case Dtype::DATE_MONTH: {

		switch (other.type)
		{
		case Dtype::DATE:       return *ptr_date_attr() <= other.ptr_date()->get_month_num();
		case Dtype::DATE_MONTH: return *ptr_date_attr() <= *other.ptr_date_attr();
		default:
			break;
		}
	}
	case Dtype::DATE_DAY: {

		switch (other.type)
		{
		case Dtype::DATE:     return *ptr_date_attr() <= other.ptr_date()->get_day_num();
		case Dtype::DATE_DAY: return *ptr_date_attr() <= *other.ptr_date_attr();
		default:
			break;
		}
	}

	case Dtype::NA: return 1;

	default:
		break;
	}

	return false;
}
bool Object::operator >=(Object other)
{
	if (type != other.type && (
		type == Dtype::STRING ||
		type == Dtype::NUMBER ||
		type == Dtype::NA
		)) {
		string operation = " >= ";
		cout << "Comparision Error:: "
			<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return (*ptr_str() >= *other.ptr_str());
		break;
	case Dtype::NUMBER:
		return (*ptr_num() >= *other.ptr_num());
		break;
	case Dtype::DATE:
		return (*ptr_date() >= other);
		break;

	case Dtype::DATE_YEAR: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() >= other.ptr_date()->get_year_num();
		case Dtype::DATE_YEAR: return *ptr_date_attr() >= *other.ptr_date_attr();
		default:
			break;
		}

	}
	case Dtype::DATE_MONTH: {

		switch (other.type)
		{
		case Dtype::DATE:       return *ptr_date_attr() >= other.ptr_date()->get_month_num();
		case Dtype::DATE_MONTH: return *ptr_date_attr() >= *other.ptr_date_attr();
		default:
			break;
		}
	}
	case Dtype::DATE_DAY: {

		switch (other.type)
		{
		case Dtype::DATE:     return *ptr_date_attr() >= other.ptr_date()->get_day_num();
		case Dtype::DATE_DAY: return *ptr_date_attr() >= *other.ptr_date_attr();
		default:
			break;
		}
	}

	case Dtype::NA: return 1;

	default:
		break;
	}

	return false;
}

bool Object::operator ==(Object other)
{
	if (type != other.type && (
		type == Dtype::STRING ||
		type == Dtype::NUMBER ||
		type == Dtype::NA
		)) {
		string operation = " == ";
		cout << "Comparision Error:: "
			<<  type << "(" << *this << ")"
			+ operation
			<< other.type << "(" << other << ")" << endl;
		assert(0);
	}

	switch (type)
	{
	case Dtype::STRING:
		return (*ptr_str() == *other.ptr_str());
		break;
	case Dtype::NUMBER:
		return (*ptr_num() == *other.ptr_num());
		break;
	case Dtype::DATE:
		return (*ptr_date() == other);
		break;

	case Dtype::DATE_YEAR: {

		switch (other.type)
		{
		case Dtype::DATE:      return *ptr_date_attr() == other.ptr_date()->get_year_num();
		case Dtype::DATE_YEAR: return *ptr_date_attr() == *other.ptr_date_attr();
		default:
			break;
		}

	}
	case Dtype::DATE_MONTH: {

		switch (other.type)
		{
		case Dtype::DATE:       return *ptr_date_attr() == other.ptr_date()->get_month_num();
		case Dtype::DATE_MONTH: return *ptr_date_attr() == *other.ptr_date_attr();
		default:
			break;
		}
	}
	case Dtype::DATE_DAY: {

		switch (other.type)
		{
		case Dtype::DATE:     return *ptr_date_attr() == other.ptr_date()->get_day_num();
		case Dtype::DATE_DAY: return *ptr_date_attr() == *other.ptr_date_attr();
		default:
			break;
		}
	}

	case Dtype::NA: return 1;

	default:
		break;
	}

	return false;
}


ostream& operator<<(ostream& os, const Object& obj)
{
	switch (obj.type)
	{
	case Dtype::STRING:
	{
		os << *obj.ptr_str();
		break;
	}
	case Dtype::NUMBER:
	{
		os << *obj.ptr_num();
		break;
	}
	case Dtype::DATE:
	{
		os << obj.ptr_date()->get();
		break;
	}

	case Dtype::DATE_YEAR:
	case Dtype::DATE_MONTH:
	case Dtype::DATE_DAY:
	{
		os << *obj.ptr_date_attr();
		break;
	}
	default:
		os << "NULL";
	}
	return os;
}