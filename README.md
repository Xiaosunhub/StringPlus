StringPlus - C++String Enhancement Library

StringPlus is an optimized extension of the C++standard library std:: string, providing richer and more convenient string manipulation functions.



##Functional characteristics
-Enhanced string operations: including common operations such as case conversion, whitespace trimming, substring replacement, etc
-Type conversion support: Supports the conversion between numbers and strings, as well as the conversion between wide and narrow characters
-Regular expression integration: built-in regular matching and replacement functions
-UTF-8 support: Provides UTF-8 string length calculation and substring truncation
-Bit operation extension: supports string bitwise AND, OR, XOR operations
-Case and other character statistics: GetCharTypeCount() in StringPlus can be called to return the type std:: map<std:: string, int>sring represents the character type, which includes "upper", "lower", "digit", "else", and int represents the number of occurrences
-Case statistics: You can call VNet etterTypeCount() in StringPlus, which returns the type std:: map<std:: string, int>sring represents the character type, with "upper" and "lower", and int is the number of occurrences
-Character enumeration: StringPlus:: Chars provides values for each character type
-Case enumeration: StringPlus: Letter provides values for each letter type, which can be used in the SetIndexLetterType() function

##Installation Guide
#Preconditions
-C++17 or higher (/sd: c++17)
-Windows platform (if wide character conversion function is required)

##Installation steps

Download the StringPlus. h header file
Copy the file to the included directory in Visual Studio, for example:
[Installation Path] \ Microsoft Visual Studio \ 2022 \ Community \ VC \ Auxilia \ VS \ include

Include header files in the project:
#include <StringPlus.h>

##Alternative installation method

You can also directly place the header file in the project directory and use a relative path to include:
#include "path/to/StringPlus.h"

##Example usage

#include <StringPlus.h>

int main() {
//Create a string
std::StringPlus str = "  Hello World! 123 ";

//Trim and convert uppercase letters
str.trim().toUpper();

//Type conversion
int num = str.substr(12).toInt(); //Extract '123' and convert it to an integer
	
//Regular replacement
str.regexReplace("WORLD", "CPP");
	
//Character statistics
int sum = str.GetCharTypeCount()["upper"];

return 0;
}

