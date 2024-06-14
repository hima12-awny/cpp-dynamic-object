# Introduction

We know that C++ is Static Data type only if you have Text value stored in a variable with data type string if a number is any data type valid with numbers like int, float and so on.
And arrays are strict must-have elements with only a single data type. 
If I want to put different values with different data types in one vector, this made a low-performance solution for me because all vector's values are strictly in String data type and converting any value to handle anything latter like numbers of dates.
<br>
so i decided to make something to holed and handle most data type used Like String, Numbers and Dates.
<br>
called

# Object Class

The `Object` class in C++ offers a versatile data structure capable of storing various types of data, including strings, numbers, and dates. It provides functionalities for type conversion, arithmetic operations, random value generation, and string manipulation.

## Key Features

### 1. **Dynamic** Data Dtype and Flexible Data Storage

The `Object` class can store data of different types, making it suitable for a wide range of applications.

```cpp
#include <iostream>
#include "Object.h"
using namespace std;

int main() {

    // Creating objects with different types
    Object var1 = "Hello, world!";

    Object var2 = 42;
    Object var3 = "42";

    Object var4(2000, 5, 3);

    // output
    // string value
    cout << var1 << " : " << var1.type; // Hello, world! : STRING

    // detecting number values
    cout << var2 << " : " << var2.type; // 42 : NUMBER
    cout << var3 << " : " << var3.type; // 42 : NUMBER

    // date value
    cout << var4 << " : " << var4.type; // 2000-05-03 : DATE

    return 0;
}
```

### 2. Arithmetic Operations

It supports basic arithmetic operations such as addition, subtraction, multiplication, and division for numerical data types and Also **Strings!**
see this...

```cpp
#include <iostream>
#include "Object.h"
using namespace std;

int main() {

	// Creating objects with different types

    // String values
	Object var1 = "Hima";
	Object var2 = "Hima";

    // number value
	Object var3 = 42;

	var1 = var1 * 2;   // multiply with int   value (repeating the string)
	var2 = var2 * 2.5; // multiply with float value (can you predict the result?)

	var3 = var3 * 2;   // normal numbers multiplication

	// output
	// string values
	cout << var1 << " : " << var1.type; // HimaHima : STRING


	cout << var2 << " : " << var2.type; // HimaHi : STRING
                                        // i think same what you think!
                                        // you can see more operation later in this repo.

	// number value
	cout << var3 << " : " << var3.type; // 82 : NUMBER

	return 0;
}
```

### 3. Type Conversion

The class includes methods for converting between different data types, to travel from data type to another using abstracted tools!

```cpp
#include <iostream>
#include "Object.h"
using namespace std;

int main() {

	// Creating objects with different types
	Object var1 = "2020/05/25"; // now it is STRING Dtype
	Object var2 = 42;           // now it is NUMBER Dtype

    // converting them to different data types
	var1 = var1.to_date();
	var2 = var2.to_str() * 2; // you can guess the result of this?

	// output
	cout << var1 << " : " << var1.type; // 2020-05-25 : DATE

	cout << var2 << " : " << var2.type; // 4242 : STRING
                                        // i think you got me ;)

	return 0;
}
```

### 4. `String` Manipulation (more about String)

The `Object` class provides methods from Class Called `String` for common string manipulation tasks, such as stripping whitespace and obtaining the length of a string, and many more like **Python** what do.

```cpp
#include <iostream>
#include "Object.h"
#include <vector>
using namespace std;

int main() {

	Object str_value = "   Nothing is impossible, the solution is more knowledge and some passion.   ";

	str_value = str_value.strip();
	cout << "str_value: " << str_value << endl;
	// str_value: "Nothing is impossible, the solution is more knowledge and some passion."

	str_value = str_value.up();
	cout << "str_value: " << str_value << endl;
	// str_value: "NOTHING IS IMPOSSIBLE, THE SOLUTION IS MORE KNOWLEDGE AND SOME PASSION."

	str_value = str_value.lw();
	cout << "str_value: " << str_value << endl;
	// str_value: "nothing is impossible, the solution is more knowledge and some passion."

	str_value = str_value.title();
	cout << "str_value: " << str_value << endl;
	// str_value: "Nothing Is Impossible, The Solution Is More Knowledge And Some Passion."

	str_value = str_value.replace("Solution", "Key");
	cout << "str_value: " << str_value << endl;
	// str_value: "Nothing Is Impossible, The Key Is More Knowledge And Some Passion.".
	// and you can replace more than one value by passing like that
	// "Solution|Is" and so on.

	cout << "'Key' start index: " << str_value.find("Key") << endl; // 27

	// count the number of occurrences of the Input String in my str_value
	cout << "'Is' Count in str: " << str_value.count("Is") << endl; // 2

	// splitting the string into list of strings separated by separator as input
	vector<Object> list_of_words = str_value.split(" ");
	// list_of_words contains:
	// {"Nothing", "Is", "Impossible,", "The", "Key", "Is", "More", "Knowledge", "And", "Some", "Passion".}

	// str_value.split(" ") split words and return list of strings,
	// in case i have numbers in this string, i want to converting it while separating them, so
	Object sep_numbers_str = "2003/5/17";

	// make param enable_numbers = true to handle Number Converting.
	vector<Object> numbers = sep_numbers_str.split("/", true);
	// numbers vector be like (in NUMBER Dtypes):
	// {2003, 5, 17}


	Object new_str_value = String::join("->", list_of_words);
	cout << "new_str_value: " << new_str_value << endl;
	// new_str_value: "Nothing->Is->Impossible,->The->Key->Is->More->Knowledge->And->Some->Passion."

	return 0;
}
```

### 4. `Date` manipulation (more about date)

The `Object` class provides methods from Class Called `Date` can add some additional features like converting the input string into date automatically
by extracting it's format. and some comparisons features i will show it next.

```cpp
#include <iostream>
#include "Object.h"
using namespace std;

int main() {

	// making date with;
	// year : 2003
	// month: 5
	// day  : 9
	Date date(2003, 5, 9);

	cout << "date: " << date << endl;
	// output always in format DateFormat::YYYY_MM_DD
	// output: 2003-05-09

	// you can convert data from the string representation
	// based on input DateFormat you want, like:
	date = Date("2003/9/5", DateFormat::YYYY_DD_MM);
	cout << "input formatted date: " << date << endl;
	// output still: 2003-05-09
	//
	// see a lot of DateFormats In file emums.h

	// and can automatically convert from the string representation to date format.
	// can extract the separator and the year and month and days too,
	// and can validate it from any noise or misunderstand characters
	// see source code for more information.
	date = "2003/25/9";
	cout << "extracted date: " << date << endl;
	// output: 2003-09-25

	// and can get any attribute from the date
	// to using it later in Comparisons.
	Object year  = date.get_year();  // the Date type is DATE_YEAR
	Object month = date.get_month(); // the Date type is DATE_MONTH
	Object day   = date.get_day();   // the Date type is DATE_DAY

	return 0;
}
```

### 5. **Comparison** operators

the `Object` can deals with the all Comparison operators if the two operands are **The Same Data type**, BUT we can modify that only if the one of the operands is `Date` and the second is one of the _Date Attribute_ like:

```cpp
#include <iostream>
#include "Object.h"
using namespace std;
#include <vector>

int main() {

	// remember this?
	Date date(2003, 5, 9);

	cout << "date: " << date << endl;
	// output always in format DateFormat::YYYY_MM_DD
	// output: 2003-05-09

	Object year  = Object(2003, Dtype::DATE_YEAR );  // the Date type is DATE_YEAR
	Object month = Object(5   , Dtype::DATE_MONTH);  // the Date type is DATE_MONTH
	Object day   = Object(8   , Dtype::DATE_DAY  );  // the Date type is DATE_DAY

	// what do you think the outputs?!
	cout << "Same Year ? " << ((date == year ) ? "Yes" : "No") << endl;
	cout << "Same Month? " << ((date == month) ? "Yes" : "No") << endl;
	cout << "Same Day  ? " << ((date == day  ) ? "Yes" : "No") << endl;

	return 0;
}
```

### 6. **Multiple Data Dtypes** in One Vector?

one of the most important reason to give me the passion to make this `Object`
that to to make me able to but some of different items in one thing. some one bigger than me told me before the solution is the `struct` ok, this is limited solution and not dynamic too, i think a lot to make this real for me.
i made `Object`, thing to make this thing actionable and solve the limited knowledge for me.

```cpp
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
		cout << i << ": value: " << items[i]      << endl
		            "   dtype: " << items[i].type << endl << endl;
	}

	/*
	 output

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

	// splitting the address and enabling parsing the numbers.
	// to get different data type in return.
	items = address_str.split(" ", true);

	cout << "\nitems of address_str:\n";
	for (int i = 0; i < items.size(); i++)
	{
		cout << i << ": value: " << items[i]      << endl
		            "   dtype: " << items[i].type << endl << endl;
	}

	/*
	output
		items of address_str:
			0: value: 15
			   dtype: NUMBER

			1: value: str_nyc
			   dtype: STRING
   */


	// you can convert the whole vector of doubles to vector of
	// Objects easily by calling static method from the Object Class.
	// you can see more converting functions in the source file.

	vector<double> values = { .454, 4, 98, 5 };
	items = Object::from_vector_double(values);

	return 0;
}
```

## 7. **Inspiration**

like I have said, I made this `Object` to prove to myself if there is something impossible for me, it is just that because of my limited knowledge of this something. <br>
this may not be the hardest thing I have done, but sometimes when you feel failed at something, and feel not good enough to be there where you like to be.

recognize that the solution is just **Time and well-directed Passion.** Time means patience and well-directed Passion means choosing things as input in your way, because humans being humans make mistakes so be patient when you treat yourself. <br> <br>

## 8. **Acknowledgement**

I would like to express my sincere gratitude to [Ahmed Khaled](https://www.linkedin.com/in/ahmad-khaled-hamed/) for his invaluable assistance in brainstorming, to [Ahmed Khafagy](https://www.linkedin.com/in/ahmednaderkhafagy/) for his crucial support in helping me present my work, and to [Abdelrahman H. Soliman](https://www.instagram.com/abdelrahmantalks?utm_source=ig_web_button_share_sheet&igsh=ZDNlZDc0MzIxNw==) for his unwavering encouragement, which motivated me to continue and complete this project.

there is a lot in source code to improve if you want, and if you find any bugs please don't hesitate to inform me.
<br> <br>
Thank you for reading.
<br> with love <br>
feel free to [Email me](mailto:hima12awny@gmail.com)
<br> **Ibrahim Awny.**
