

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <limits>
#include "ObjectLib/object.h"



using namespace std;

std::ostream& operator<<(std::ostream& os, const vector<Object>& obj)
{

	os << "\n[" << String::join(", ", obj) << "]\n";
	return os;
}

//int main()
//{

	/*Object words_str_1 =
		"154 the majestic mountains stood tall against the azure sky, "
		"their peaks kissed by wisps of clouds. A gentle breeze whispered through "
		"the dense forest, rustling the leaves with a soothing melody. Sunlight filtered "
		"through the canopes beauty surrounded me, filling my heart with peace and wonder.";


	Object words_str = words_str_1
		.up()
		.replace(".|, | ", "");


	vector<Object> words = words_str.split();
	cout << words_str.getYear();

	Object num_str = Object("123456", Dtype::STRING);
	Object num = (num_str * 10).to_num();

	num_str.print_info();
	num.print_info();


	Object date = Object(2003, 5, 17);
	Object day = date.getDay();

	date.print_info();
	day.print_info();

	cout << (date == day) << endl;

	cout << (date == day.to_num());


	String str = "546";

	cout << (Object((str * 2)) == Object(str).to_str());

	*/

	// Object date = "2020-25-5";
	// Object day(25, Dtype::DATE_DAY);

	// date.print_info();
	// cout << (date == day);

	// date = date.to_date();
	// date.print_info();
	// cout << (date == day);

	 //Date my_date = "2003/0/5";
	 //Object day(5, Dtype::DATE_DAY);
	 //cout << my_date;
	 //cout << (my_date == day);

//	return 0;
//}

//int main() {
//
//	Object str_value = "   Nothing is impossible, the solution is more knowledge and some passion.   ";
//
//	str_value = str_value.strip();
//	cout << "str_value: " << str_value << endl;
//	// str_value: "Nothing is impossible, the solution is more knowledge and some passion."
//
//	str_value = str_value.up();
//	cout << "str_value: " << str_value << endl;
//	// str_value: "NOTHING IS IMPOSSIBLE, THE SOLUTION IS MORE KNOWLEDGE AND SOME PASSION."
//
//	str_value = str_value.lw();
//	cout << "str_value: " << str_value << endl;
//	// str_value: "nothing is impossible, the solution is more knowledge and some passion."
//
//	str_value = str_value.title();
//	cout << "str_value: " << str_value << endl;
//	// str_value: "Nothing Is Impossible, The Solution Is More Knowledge And Some Passion."
//
//	str_value = str_value.replace("Solution", "Key");	
//	cout << "str_value: " << str_value << endl;
//	// str_value: "Nothing Is Impossible, The Key Is More Knowledge And Some Passion."
//
//	cout << "'Key' start index: " << str_value.find("Key") << endl; // 27
//
//	// count the number of occurrences of the Input String in my str_value
//	cout << "'Is' Count in str: " << str_value.count("Is") << endl; // 2
//
//	// splitting the string into list of strings separated by separator as input
//	vector<Object> list_of_words = str_value.split(" ");
//	// list_of_words contains:
//	// {"Nothing", "Is", "Impossible,", "The", "Key", "Is", "More", "Knowledge", "And", "Some", "Passion".}
//
//	// str_value.split(" ") split words and return list of strings,
//	// in case i have numbers in this string, i want to converting it while separating them, so
//	Object sep_numbers_str = "2003/5/17";
//
//	// make param enable_numbers = true to handle Number Converting.
//	vector<Object> numbers = sep_numbers_str.split("/", true);
//	// numbers vectore be like (in NUMBER Dtypes):
//	// {2003, 5, 17}
//
//
//	Object new_str_value = String::join("->", list_of_words);
//
//	cout << "new_str_value: " << new_str_value << endl;
//	// new_str_value: "Nothing->Is->Impossible,->The->Key->Is->More->Knowledge->And->Some->Passion."
//
//	return 0;
//}

//int main() {
//	
//	// remember this?
//	Date date(2003, 5, 9);
//
//	cout << "date: " << date << endl;
//	// output always in format DateFormat::YYYY_MM_DD
//	// output: 2003-05-09
//
//	Object year  = Object(2003, Dtype::DATE_YEAR );  // the Date type is DATE_YEAR
//	Object month = Object(5   , Dtype::DATE_MONTH);  // the Date type is DATE_MONTH
//	Object day   = Object(8   , Dtype::DATE_DAY  );  // the Date type is DATE_DAY
//
//	// what do you think the outputs?!
//	cout << "Same year ? " << ((date == year ) ? "Yes" : "No") << endl;
//	cout << "Same month? " << ((date == month) ? "Yes" : "No") << endl;
//	cout << "Same day  ? " << ((date == day  ) ? "Yes" : "No") << endl;
//
//	return 0;
//}



int main() {

	vector<Object> items = {
		4.5,
		"545",
		"hima",
		2,
		Date(2003, 5, 9)
	};

	for (int i = 0; i < items.size(); i++)
	{
		cout << i << ": value: " << items[i] << "\n   dtype: " << items[i].type << endl << endl;
	}

	/*
	* output

		0: value: 4.5
		   dtype: NUMBER

		1: value: 545
		   dtype: NUMBER

		2: value: hima
		   dtype: STRING

		3: value: 2
		   dtype: NUMBER

		4: value: 2003-05-09
		   dtype: DATE
   */

	Object address_str = "15 str_nyc";

	// spletting the address and enabling parsing the numbers.
	// to get diffrents data type in return.
	items = address_str.split(" ", true);

	cout << "\nitems of address_str:\n";
	for (int i = 0; i < items.size(); i++)
	{
		cout << i << ": value: " << items[i] << "\n   dtype: " << items[i].type << endl << endl;
	}
	/*
	* output
		items of address_str:
			0: value: 15
			   dtype: NUMBER

			1: value: str_nyc
			   dtype: STRING
   */

   // you can convert the whole vector of doubles to vector of 
   // Objects easly by calling static methouf from the Object Class.
   // you can see more converting functions in the source file.
	vector<double> values = { .454, 4, 98, 5 };
	items = Object::from_vector_double(values);

	return 0;
}