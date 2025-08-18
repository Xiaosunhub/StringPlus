//   ________  ___________  ________       ____________  ______       ___  __________     ________    ___          ___      ___   ________ 
//  /  ______| |___  ____| |  _____ \      |____  ____|  |     \      | |  /  ______  \   |  ___  \   | |          | |      | |  /  ______|
//  | |            | |     | |     \ |         |  |      |  |\  \     | |  |  |     |__|  |  |   \ |  | |          | |      | |  | |
//  | |_______     | |     | |_____| |         |  |      |  | \  \    | |  |  |           |  |___/ |  | |          | |      | |  | |_______ 
//  \_______  \    | |     |   ___   |         |  |      |  |  \  \   | |  |  |  _____    |  ______/  | |          | |      | |  \_______  \
//          \  |   | |     |  |   \  \         |  |      |  |   \  \  | |  |  |  |__  |   |  |        | |          | |      | |          \  |
//          |  |   | |     |  |    \  \        |  |      |  |    \  \ | |  |  |     | |   |  |        | |          | |      | |          |  | 
//   _______|  |   | |     |  |     \  \   ____|  |____  |  |     \  \| |  |  |_____| |   |  |        | |_______   | \______/ |   _______|  |
//  |_________/    |_|     |__|      \__\  |__________|  |__|      \____|  \__________|   |__|        |_________|   \________/   |_________/
// 
// 
//Copyright(c)[2025][孙鸿宇]
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
// 
//StringPlus
// |- StringPlus.h <--
// |- utf8.h
// |- coding.h

#pragma once
#ifndef __INC_STRINGPLUS_H__
#define __INC_STRINGPLUS_H__

#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <cctype>
#include <memory>
#include <cstdio>
#include <utility>
#include <sstream>
#include <iomanip>
#include <regex>
#include <locale>
#include <functional>
#include <Windows.h>
#include <map>
#include <cstdlib>
#include <exception>
#undef StringPlus

// Macro
#define StringPlusCharTypeUpper   "upper"    // Char Upper
#define StringPlusCharTypeLower   "lower"    // Char Lower
#define StringPlusCharTypeDigit   "digit"    // Char Digit
#define StringPlusCharTypeElse    "else"     // Char Else
#define StringPlusLetterTypeUpper "upper"    // Letter Upper
#define StringPlusLetterTypeLower "lower"    // Letter Lower

namespace std 
{

    class string_error : public std::exception                                   // Defined a C++ exception class called string_error, which inherits from the standard std::exception and provides two construction methods: string and character pointer. It is used to encapsulate error information related to string processing and implements cross platform compatibility for exception handling through macro definitions
    {
    public:
        using _Mybase = std::exception;

        explicit string_error(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit string_error(const char* _Message) : _Mybase(_Message) {}

#if !_HAS_EXCEPTIONS
    protected:
        void _Doraise() const override { // perform class-specific exception handling
            _RAISE(*this);
        }
#endif // !_HAS_EXCEPTIONS
    };

    class string_to_type_out_of_range : public std::exception                          // Defined an exception class string_to_type_out_of_range that inherits from std::exception, used for handling value out of bounds errors during string type conversion, providing two construction methods and supporting cross platform exception handling
    {
    public:
        using _Mybase = std::exception;

        explicit string_to_type_out_of_range(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit string_to_type_out_of_range(const char* _Message) : _Mybase(_Message) {}

#if !_HAS_EXCEPTIONS
    protected:
        void _Doraise() const override { // perform class-specific exception handling
            _RAISE(*this);
        }
#endif // !_HAS_EXCEPTIONS
    };

    class index_is_out_of_string : public std::exception                          // Defined an exception class named index_is_out_of_string that inherits from std::exception, specifically designed for string index out of bounds errors, providing two construction methods and supporting cross platform exception handling
    {
    public:
        using _Mybase = std::exception;

        explicit index_is_out_of_string(const std::string& _Message) : _Mybase(_Message.c_str()) {}
        explicit index_is_out_of_string(const char* _Message) : _Mybase(_Message) {}

#if !_HAS_EXCEPTIONS
    protected:
        void _Doraise() const override { // perform class-specific exception handling
            _RAISE(*this);
        }
#endif // !_HAS_EXCEPTIONS
    };

    // C++string upgrade version, public of std::string
    extern "C++" class StringPlus : public std::string
    {
    private:
        std::string str;

    public:
        // Type alias (public of string)
        using pos_type = std::string::size_type;
        using value_type = std::string::value_type;
        using size_type = std::string::size_type;
        using iterator = std::string::iterator;
        using const_iterator = std::string::const_iterator;
        using reverse_iterator = std::string::reverse_iterator;
        using const_reverse_iterator = std::string::const_reverse_iterator;
        using int_type = int;
        
        // Unable to find the mark of the item ---- nopos
        static constexpr pos_type nopos = static_cast<pos_type>(-1);

        // Character type enumeration
        enum Chars { Upper = 1, Lower = 2, Digit = 3, Else = 4, };
        // Letter types enumeration
        enum Letter { upper = 1, lower = 2, };

        // Constructors and assignment operators
        StringPlus() = default;                                               // Conventional constructor, Assign a null value to a variable ("")
        explicit StringPlus(const std::string& s) : str(s) {}                 // Initialize with a string to assign a variable a given value
        explicit StringPlus(std::string&& s) noexcept : str(std::move(s)) {}  // Use right-hand pass and std::move to create variables
        explicit StringPlus(const char* cc) : str(cc ? cc : "") {}            // Initialize with a const char* to assign a variable a given value
        StringPlus(const StringPlus&) = default;                              // A regular copy constructor
        StringPlus(StringPlus&&) noexcept = default;                          // Use right-hand pass to copy constructor
        StringPlus(int_type num) : str(to_string(num)) {}                          // Directly use the value of int to create variables
        StringPlus(long long num) : str(to_string(num)) {}                    // Directly use the value of long long to create variables
        StringPlus(float num) : str(to_string(num)) {}                        // Directly use the value of float to create variables
        StringPlus(double num) : str(to_string(num)) {}                       // Directly use the value of double to create variables
        StringPlus(unsigned int num) : str(to_string(num)) {}                 // Directly use the value of unsigned int to create variables
        StringPlus(std::string s, size_type size) : str(s.substr(0, size)) {} // Pass in the parameters s and size, extract the 0-size index of s as the parameter to create a variable, where s is the string to be truncated and size is the truncated index

        StringPlus& operator=(const StringPlus&) = default;                                    // Pass in StringPlus as a parameter and assign a value to the variable using this parameter
        StringPlus& operator=(StringPlus&&) noexcept = default;                                // Pass the right-handed value to StringPlus as a parameter and use this parameter to assign a value to the variable
        StringPlus& operator=(const std::string& s) { str = s; return *this; }                 // Assigns the given std::string to this object and returns self-reference for chaining
        StringPlus& operator=(std::string&& s) noexcept { str = std::move(s); return *this; }  // Pass string as a right-handed parameter and use this parameter in conjunction with std::move to assign a value to the variable
        StringPlus& operator=(const char* cc) { str = cc ? cc : ""; return *this; }            // Use C-style strings (const char *) to assign values to StringPlus objects

        ~StringPlus() = default;                                              // Ordinary destructor

        // Conversion Operators
        explicit operator std::string() const& { return str; }                  // Convert to std::string
        explicit operator std::string()&& { return std::move(str); }            // Convert to a right-handed std::string
        explicit operator const char* () const noexcept { return str.c_str(); } // Convert to C-style strings (const char*)
        explicit operator bool() const noexcept { return !str.empty(); }        // Convert to bool

        // Accessor
        const std::string& s_str() const& noexcept { return str; }              // defines a constant lvalue reference member function s_str(), which returns the constant lvalue reference of the str member in the class, and promises not to modify the object state (const) and not to throw an exception (noexcept)
        std::string&& s_str() && noexcept { return std::move(str); }            // This line of code defines a right-handed reference qualified member function s_str(), which is called when the object is right-handed, moves the member variable str and returns its right-handed reference, while ensuring that no exceptions are thrown (noexcept)
        const char* c_str() const noexcept { return str.c_str(); }              // Defined a constant lvalue reference member function c_str(), which returns the C-style string (const char *) of the str member in the class and promises not to modify the object state (const) or throw an exception (noexcept)
        const char* data() const noexcept { return str.data(); }                // Defined a constant member function data(), which returns a pointer to the underlying character array, ensuring that the object is not modified and no exceptions are thrown
        char* data() noexcept { return &str[0]; }                               // Defined a pointer function data(), which returns the first character of the string str, used to directly access its underlying character array
        string operator*() { return str; }                                      // The dereference operator is used to return the value of a variable

        // Capacity related
        bool empty() const noexcept { return str.empty(); }                     // Check if the variable is empty ("")
        size_type size() const noexcept { return str.size(); }                  // Defined a constant member function called size(), which returns the length of the string str and does not throw an exception (noexcept)
        size_type length() const noexcept { return str.length(); }              // Defined a constant member function called length(), which returns the length of the string str and does not throw an exception (noexcept)
        size_type capacity() const noexcept { return str.capacity(); }          // Defined a function capacity(), that returns the capacity of the internal storage space of the current string object (i.e. the maximum number of characters that can be accommodated without reallocating memory), represented as size_type, and does not throw an exception (noexcept)
        void reserve(size_type new_cap) { str.reserve(new_cap); }               // Defined a function reserve(), that allows a string to reserve storage space of at least new_cap characters (possibly expanded to reduce reallocation during subsequent insertions), but does not change the actual content or size of the string
        void shrink_to_fit() { str.shrink_to_fit(); }                           // Defined a function shrink_to_fit(), that requests a string to release excess capacity and reduce memory usage to just fit the current content (specific implementation may not fully shrink)

        // modifier
        void clear() noexcept { str.clear(); }                                                     // Defined a function append(), clears the string content (making its length 0), but does not change the underlying capacity, and this operation ensures that no exception is thrown (noexcept)
        StringPlus& append(const std::string& s) { str.append(s); return *this; }                  // Defined a function append(), that append the string s to the end of the current string and return a reference to the current object to supports chain calls
        StringPlus& append(const char* s, size_type count) { str.append(s, count); return *this; } // Defined a function append(), that adds the first count characters of the character array pointed to by pointer s to the end of the current string and returns a reference to the current object to supports chain calls
        StringPlus& append(const char* s) { str.append(s); return *this; }                         // Defined a function append(), that append the C-style string (const char*) s to the end of the current string (until '\ 0' is encountered) and returns a reference to the current object (supports chain calls)
        StringPlus& append(size_type count, char ch) { str.append(count, ch); return *this; }      // Defined a function append(), that adds the count character ch to the end of a variable and returns a reference to the current object to support chain calls
        
        template<class InputIt>
        StringPlus& append(InputIt first, InputIt last) { str.append(first, last); return *this; } // Defined a function append(), that append characters within the scope of the iterator [first, last) to the end of the string str and returns a reference to the current object to supports chain calls

        StringPlus operator*(int_type n)                                                           // This code overloads the * operator, allowing StringPlus objects to repeat strings n times like Python strings through str * n
        {
            StringPlus strpl = str;
            for (int i = 1;i < n;i++)
                strpl += str;
            return strpl;
        }

        StringPlus& operator*=(int_type n)                                                         // This code overloads the *=operator, allowing the StringPlus object to repeat the string in place n times (similar to str *=n) and return its own reference to support chain operations
        {
            StringPlus strpl = str;
            for (int i = 1;i < n;i++)
                strpl += str;
            str = strpl;
            return this;
        }

        // Operator overloading
        StringPlus& operator+=(const StringPlus& rhs) { str += rhs.str; return *this; } // Overload the +=operator to append the content of the StringPlus object on the right to the end of the current string and return a reference to the current object to support chain operations
        StringPlus& operator+=(const std::string& rhs) { str += rhs; return *this; }    // Overload the +=operator to append the content of the std::string object on the right to the end of the current string and return a reference to the current object to support chain operations
        StringPlus& operator+=(const char* rhs) { str += rhs; return *this; }           // Overload the +=operator to append the content of the C-style string (const char*) object on the right to the end of the current string and return a reference to the current object to support chain operations
        StringPlus& operator+=(char ch) { str += ch; return *this; }                    // Overload the +=operator to append the content of the char object on the right to the end of the current string and return a reference to the current object to support chain operations

        // AND operator
        StringPlus operator&(const StringPlus& rhs) const                               // Overload &operator, perform bitwise AND operation on two StringPlus objects character by character, and return the result object (if the lengths are different, only process the common length part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] &= rhs.str[i];
            
            return result;
        }

        StringPlus operator&(const std::string& rhs) const                              // Overload &operator, perform bitwise AND operation on the current StringPlus object and the standard string rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] &= rhs[i];
            
            return result;
        }

        StringPlus operator&(const char* rhs) const                                     // Overload &operator, perform bitwise AND operation on the current StringPlus object and the C-style string (const char*) rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] &= rhs[i];
            
            return result;
        }

        // OR operator
        StringPlus operator|(const StringPlus& rhs) const                               // Overload |operator, perform bitwise OR operation on two StringPlus objects character by character, and return the result object (if the lengths are different, only process the common length part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] |= rhs.str[i];
            
            return result;
        }

        StringPlus operator|(const std::string& rhs) const                              // Overload |operator, perform bitwise OR operation on the current StringPlus object and the standard string rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] |= rhs[i];
            
            return result;
        }

        StringPlus operator|(const char* rhs) const                                     // Overload |operator, perform bitwise OR operation on the current StringPlus object and the C-style string (const char*) rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i)
                result.str[i] |= rhs[i];
            
            return result;
        }

        // XOR operator
        StringPlus operator^(const StringPlus& rhs) const                               // Overload ^operator, perform bitwise XOR operation on two StringPlus objects character by character, and return the result object (if the lengths are different, only process the common length part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] ^= rhs.str[i];
            
            return result;
        }

        StringPlus operator^(const std::string& rhs) const                             // Overload ^operator, perform bitwise XOR operation on the current StringPlus object and the standard string rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] ^= rhs[i];
            
            return result;
        }

        StringPlus operator^(const char* rhs) const                                    // Overload ^operator, perform bitwise XOR operation on the current StringPlus object and the C-style string (const char*) rhs character by character, and return the result object (only processing the common length part, no operation on the excess part)
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i) 
                result.str[i] ^= rhs[i];
            
            return result;
        }

        // compound assignment operators
        StringPlus& operator&=(const StringPlus& rhs)                                 // Overload the &=operator to perform bitwise AND operation on the contents of the StringPlus object on the right side and the current object character by character (only processing the common length part), and return a reference to the current object to support chain operations
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                str[i] &= rhs.str[i];
            
            return *this;
        }

        StringPlus& operator|=(const StringPlus& rhs)                                 // Overload the |=operator to perform bitwise OR operation on the contents of the StringPlus object on the right side and the current object character by character (only processing the common length part), and return a reference to the current object to support chain operations
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                str[i] |= rhs.str[i];
            
            return *this;
        }

        StringPlus& operator^=(const StringPlus& rhs)                                 // Overload the ^=operator to perform bitwise XOR operation on the contents of the StringPlus object on the right side and the current object character by character (only processing the common length part), and return a reference to the current object to support chain operations
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) 
                str[i] ^= rhs.str[i];
            return *this;
        }

        // Deleted operator
        StringPlus operator~() const = delete;                       // This statement explicitly removes (= delete) the overloading of the bitwise inversion operator, which prohibits bitwise inversion operations on StringPlus objects (usually because this operation has no practical meaning or potential risks to string types)
        StringPlus operator<<(size_type) const = delete;             // This statement explicitly removes (= delete) the overload of the left shift operator<<, prohibiting displacement operations on StringPlus objects (usually because displacement operations have no practical meaning or are prone to ambiguity for string types)
        StringPlus operator>>(size_type) const = delete;             // This statement explicitly removes (= delete) the overload of the right shift operator>>, prohibiting the use of shift operations on StringPlus objects (usually because bitwise operations are meaningless to string types or may cause undefined behavior)
        
        StringPlus& operator<<=(size_type) = delete;                 // This statement explicitly removes (= delete) the overload of the composite left shift assignment operator<<=, and prohibits displacement composite assignment operations on StringPlus objects (usually because bit level operations on string types are not semantically logical and have potential risks)
        StringPlus& operator>>=(size_type) = delete;                 // This statement explicitly removes (= delete) the overload of the compound right shift assignment operator>>=, and prohibits the displacement compound assignment operation on StringPlus objects (usually because bit level operations on string types are not semantically logical and have potential risks)
        
        StringPlus& operator-=(char) = delete;                       // This statement explicitly removes (= delete) the character overload of the -=operator and prohibits the use of this operator to remove characters from a string (usually because the semantics of this operation are unclear, it is recommended to use explicit methods such as erase() instead)
        StringPlus& operator-=(const StringPlus&) = delete;          // This statement explicitly removes (= delete) the overload of the -=operator on the StringPlus object, prohibiting direct string subtraction operations using this operator (usually due to the lack of clear semantic definitions in string subtraction, erase() or custom string processing methods are recommended as alternatives)
        StringPlus& operator-=(const char*) = delete;                // This statement explicitly removes (= delete) the overloading of the -=operator on C-style strings (const char *), forcing the use of more explicit string manipulation methods (such as erase()) to avoid semantic ambiguity and potential errors
        StringPlus& operator-=(const std::string&) = delete;         // This statement explicitly disables the operation of the -=operator on standard strings and enforces the use of explicit member functions (such as erase()) to avoid semantic ambiguity and ensure clear and readable code intent

        StringPlus operator-(char) const = delete;                   // This statement explicitly removes (= delete) operator overloading of characters and prohibits the removal of characters from strings through subtraction operators (due to unclear semantics, it is recommended to use methods with clear intent such as erase() to manipulate strings)
        StringPlus operator-(const StringPlus&) const = delete;      // This statement explicitly removes (= delete) the overloading of string subtraction operators because there is no recognized standard semantics for string subtraction operations, which can easily cause ambiguity. It is recommended to use explicit methods such as erase() instead
        StringPlus operator-(const char*) const = delete;            // This statement explicitly prohibits the subtraction operation between strings and C-style strings (const char *), and enforces the use of semantically explicit member functions (such as erase()) to avoid ambiguity and ensure clear and maintainable code behavior
        StringPlus operator-(const std::string&) const = delete;     // This statement explicitly removes (= delete) subtraction operations between strings and enforces the use of explicit methods such as erase() to manipulate strings, avoiding semantic ambiguity and improving code readability and security

        StringPlus& operator*=(char) = delete;                       // This statement explicitly disables the multiplication assignment operation between strings and characters, as this operation lacks clear semantic definition. It is recommended to use clearer methods such as append() or constructor to achieve string repetition
        StringPlus& operator*=(const StringPlus&) = delete;          // This statement explicitly removes (= delete) multiplication and assignment operations between strings, as string multiplication lacks proper semantics. It is recommended to use explicit operations such as append() or custom concatenation methods
        StringPlus& operator*=(const char*) = delete;                // This statement explicitly removes (= delete) the multiplication assignment operation between strings and C-style strings (const char *), as this operation lacks clear semantic definition. It is recommended to use clearer operations such as append() or string concatenation instead
        StringPlus& operator*=(const std::string&) = delete;         // This statement explicitly removes string multiplication assignment operations because string multiplication does not have recognized semantics. It is recommended to use explicit methods such as append() or insert() to implement string extension
        
        StringPlus operator*(char) const = delete;                   // This statement explicitly removes (= delete) the multiplication operation between strings and characters, as this operation lacks clear semantic definition. It is recommended to use clearer methods such as constructors or append() to implement character duplication
        StringPlus operator*(const StringPlus&) const = delete;      // This statement explicitly removes (= delete) multiplication operations between strings, as there is no recognized semantic interpretation for multiplying two strings. It is recommended to use concatenation operations (+) or custom methods to achieve specific requirements
        StringPlus operator*(const char*) const = delete;            // This statement explicitly prohibits the multiplication operation between strings and C-style strings (const char *), as this operation has no recognized semantics. It is recommended to use explicit concatenation (+) or custom functions instead
        StringPlus operator*(const std::string&) const = delete;     // This statement explicitly removes (= delete) the multiplication operation between strings and std::strings, as string multiplication lacks proper semantics. It is recommended to use concatenation (+) or custom string handling functions instead

        StringPlus& operator/=(char) = delete;                       // This statement explicitly removes (= delete) the division assignment operation between variables and characters, as this operation is meaningless for string types. It is recommended to use more reasonable string segmentation or replacement methods instead
        StringPlus& operator/=(const StringPlus&) = delete;          // This statement explicitly removes (= delete) the division assignment operation between strings, as string division has no logical meaning. It is recommended to use semantically clear string processing methods such as split() or replace()
        StringPlus& operator/=(const char*) = delete;                // This statement explicitly removes (= delete) the division assignment operation between variables and C-style strings (const char *), as this operation has no practical meaning for string types. It is recommended to use semantically clear string handling methods such as split() or erase() instead
        StringPlus& operator/=(const std::string&) = delete;         // This statement explicitly removes (= delete) the division assignment operation between variables and standard strings, as this operation has no practical meaning for string types. It is recommended to use semantically clear string processing methods such as split() or erase() instead

        StringPlus operator/(char) const = delete;                   // This statement explicitly removes (= delete) the division operation between variables and characters, as this operation has no logical meaning for string types. It is recommended to use semantically clear string processing methods such as split() or find() instead
        StringPlus operator/(const StringPlus&) const = delete;      // This statement explicitly prohibits division operations between variables, as such operations lack proper semantics. It is recommended to use specialized string processing methods such as split() or find() instead
        StringPlus operator/(const char*) const = delete;            // This statement explicitly removes (= delete) the division operation between variables and C strings, as this operation has no practical meaning for string types. It is recommended to use specialized string processing methods such as split() or find() instead
        StringPlus operator/(const std::string&) const = delete;     // This statement explicitly removes (= delete) the division operation between variables and standard strings, as this operation does not have reasonable semantics for string types. It is recommended to use specialized string processing methods such as split() or substr() instead
        
        // Internal string data access
        char& operator[](size_type pos) { return str[pos]; }             // Overloads the [] operator and returns a modifiable reference to the character at the specified position pos in the string (without boundary checking, the caller needs to ensure that the index is valid)
        const char& operator[](size_type pos) const { return str[pos]; } // Overloads the [] operator and returns a read-only reference to the character at the specified position pos in the string (applicable to const objects, without boundary checking)
        
        char& at(size_type pos) { return str.at(pos); }                  // Defined a function at(), that accesses the character at position pos in a string, returns a modifiable reference, and throws a std::out_of_range exception when it is out of bounds to ensure security
        const char& at(size_type pos) const { return str.at(pos); }      // Defined a function at(), that accesses the character at position pos in a string, returns a read-only reference (applicable to const objects), and throws a std::out_of_range exception when it is out of bounds to ensure security
        
        char& front() { return str.front(); }                            // Defined a function front(), that returns a modifiable reference to the first character of a string (requires a non empty string, undefined behavior if the string is empty)
        const char& front() const { return str.front(); }                // Defined a function front(), that returns a read-only reference to the first character of a string (applicable to const objects, ensuring that the string is not empty, otherwise the behavior is undefined)
        char& back() { return str.back(); }                              // Defined a function back(), that returns a modifiable reference to the last character of a string (if the string is empty, the behavior is undefined, and empty() should be checked before calling)
        const char& back() const { return str.back(); }                  // Defined a function back(), that returns a read-only reference to the last character of a string (applicable to const objects, if the string is empty, the behavior is undefined, and empty() needs to be checked before calling)

        // Iterator support
        iterator begin() noexcept { return str.begin(); }                         // Defined a function begin(), that returns an iterator pointing to the starting position of a string (supports modification operations), while ensuring that no exceptions are thrown (noexcept)
        const_iterator begin() const noexcept { return str.begin(); }             // Defined a function begin(), that returns a read-only iterator (const _iterator) pointing to the starting position of a string, while ensuring that no exceptions are thrown (noexcept), suitable for traversing const objects
        const_iterator cbegin() const noexcept { return str.cbegin(); }           // Defined a function cbegin(), that returns a constant iterator (const) pointing to the starting position of a string without throwing exceptions (noexcept), specifically designed for const objects to ensure read-only access
        iterator end() noexcept { return str.end(); }                             // Defined a function end(), that returns an iterator pointing to the end (termination position) of a string (supports modification operations), while ensuring that no exceptions are thrown (noexcept)
        const_iterator end() const noexcept { return str.end(); }                 // Defined a function end(), that returns a read-only iterator (const _iterator) pointing to the end of a string, while ensuring that no exceptions are thrown (noexcept), suitable for traversing const objects
        const_iterator cend() const noexcept { return str.cend(); }               // Defined a function cend(), that returns a constant iterator (const) pointing to the end of a string without throwing exceptions (noexcept), specifically designed for const objects to ensure secure read-only access
        reverse_iterator rbegin() noexcept { return str.rbegin(); }               // Defined a function rbegin(), that returns a reverse iterator pointing to the reverse starting position (i.e. the end) of a string (supports modification operations), while ensuring that no exceptions are thrown (noexcept)
        const_reverse_iterator rbegin() const noexcept { return str.rbegin(); }   // Defined a function rbegin(), that returns a read-only reverse iterator (const _ reverse_interator) pointing to the reverse starting position (i.e. the end) of a string, while ensuring that no exceptions are thrown (noexcept), suitable for reverse traversal of const objects
        const_reverse_iterator crbegin() const noexcept { return str.crbegin(); } // Defined a function crbegin(), that returns a constant reverse iterator (const _ reverse _ iterator) pointing to the reverse starting position (i.e. the end) of a string, while ensuring that no exceptions are thrown (noexcept). Designed specifically for const objects to ensure secure reverse read-only access
        reverse_iterator rend() noexcept { return str.rend(); }                   // Defined a function rend(), that returns a reverse iterator pointing to the reverse end position of a string (i.e. before the first character) (supports modification operations), while ensuring that no exceptions are thrown (noexcept)
        const_reverse_iterator rend() const noexcept { return str.rend(); }       // Defined a function rend(), that returns a read-only reverse iterator (const _ reverse_interator) pointing to the reverse end of a string (i.e. before the first character), while ensuring that no exceptions are thrown (noexcept), suitable for reverse traversal of const objects
        const_reverse_iterator crend() const noexcept { return str.crend(); }     // Defined a function crend(), that returns a constant reverse iterator (const _ reverse _ iterator) pointing to the reverse end of a string (i.e. before the first character), while ensuring that no exceptions are thrown (noexcept). Designed specifically for const objects to ensure secure reverse read-only access

        // String operation
        StringPlus substr(pos_type pos = 0, pos_type count = nopos) const                // Defined a function substr(), that returns a substring starting from position pos and containing count characters (if count is nopos or out of range, it ends), encapsulated as a new StringPlus object
        {
            return StringPlus(str.substr(pos, count));
        }

        StringPlus substr(pos_type start_pos, pos_type end_pos) const                    // Defined a function substr(), to implement secure substring truncation, throwing std::out_of_range exception when the starting or ending position is out of bounds, ensuring parameter validity
        {
            if (start_pos > str.size() || end_pos > str.size() || start_pos > end_pos) 
                throw out_of_range("invalid position range")
            return StringPlus(str.substr(start_pos, end_pos - start_pos));
        }

        pos_type find(const StringPlus& s, pos_type pos = 0) const noexcept              // Defined a function find(), that searches for substring s starting from the specified position pos, returns the starting position of the match (nopos if not found), and ensures that no exception is thrown (noexcept)
        {
            return str.find(s.str, pos);
        }

        pos_type find(const char* s, pos_type pos = 0) const                             // Defined a function find(), that searches for a C-style string (const char *) s starting from position pos, returns the first matching position (nopos if not found), and inherits the exception safety guarantee of the standard library
        {
            return str.find(s, pos);
        }

        pos_type find(char ch, pos_type pos = 0) const noexcept                          // Defined a function find(), that searches for the character ch starting from position pos, returns the first occurrence position (nopos if not found), and ensures that no exception is thrown (noexcept)
        {
            return str.find(ch, pos);
        }

        // toggle case
        StringPlus& toUpper() noexcept                           // Defined a function toUpper(), that converts all letter characters in a string to uppercase (modified in place), returns a reference to the current object to support chain calls, and ensures that no exceptions are thrown (noexcept). Note: Valid only for ASCII characters
        {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c) { return std::toupper(c); });
            return *this;
        }

        StringPlus& toLower() noexcept                           // Defined a function toLower(), that converts all letter characters in a string to lowercase (modified in place), returns a reference to the current object to support chain calls, and ensures that no exceptions are thrown (noexcept). Note: Valid only for ASCII characters
        {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return *this;
        }

        StringPlus toUpperCopy() const noexcept                   // Defined a function toUpperCopy(), to create an uppercase copy of the current string (keeping the original string unchanged), return a new StringPlus object, and ensure that no exceptions are thrown (noexcept)
        {
            StringPlus result(str);
            result.toUpper();
            return result;
        }

        StringPlus toLowerCopy() const noexcept                   // Defined a function toLowerCopy() to create a lowercase copy of the current string (keeping the original string unchanged), return a new StringPlus object, and ensure that no exceptions are thrown (noexcept)
        {
            StringPlus result(str);
            result.toLower();
            return result;
        }

        // Remove blank space
        StringPlus& trimLeft()                                                          // Defined a function trimLeft(), that removes all leading whitespace characters (including spaces/tabs/line breaks, etc.) from a string, returns an object reference to support chain calls, and should be aware that Unicode whitespace characters are not handled
        {
            str.erase(str.begin(), std::find_if(str.begin(), str.end(),
                [](unsigned char ch) { return !std::isspace(ch); }));
            return *this;
        }

        StringPlus& trimRight()                                                         // Defined a function trimRight(), that locates the starting position of the trailing whitespace character using a reverse iterator, removes all trailing whitespace characters using erase(), and returns the current object reference to support chain calls
        {
            str.erase(std::find_if(str.rbegin(), str.rend(),
                [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
            return *this;
        }

        StringPlus& trim()                                                              // Defined a function trim(), that removes whitespace characters at both ends of a string and returns a reference to the current object to support chain calls
        {
            trimLeft();
            trimRight();
            return *this;
        }

        StringPlus trimLeftCopy() const                                                 // Defined a function trimLeftCpy(), to create a left trim copy of the current string (keeping the original string unchanged), implemented through copy construction+trimLeft(), and returns the processed new object
        {
            StringPlus result(str);
            result.trimLeft();
            return result;        
        }

        StringPlus trimRightCopy() const                                                // Defined a function trimRightCopy()£¬ to create a right trim copy of the current string (keeping the original string unchanged), implemented by copying construction+trimRight(), and returning the processed new object
        {
            StringPlus result(str);
            result.trimRight();
            return result;
        }

        StringPlus trimCopy() const                                                     // Defined a function trimCopy(), to create a trim copy of the current string (while removing the leading and trailing whitespace characters and keeping the original string unchanged), implemented by copying construction+trim(), and returning the processed new object
        {
            StringPlus result(str);
            result.trim();
            return result;
        }

        // String replacement
        StringPlus& replaceAll(const StringPlus& from, const StringPlus& to)            // Defined a function replaceAll() to implement global replacement, replacing all matching substrings from a string with to, returning the reference of the current object to support chain calls, and automatically skipping the replaced part during processing to avoid infinite loops
        {
            pos_type pos = 0;
            while ((pos = str.find(from.str, pos)) != nopos) 
            {
                str.replace(pos, from.length(), to.str);
                pos += to.length();
            }
            return *this;
        }

        StringPlus replaceAllCopy(const StringPlus& from, const StringPlus& to) const   // Defined a function replaceAllCopy(), to create a global replacement copy of the current string (keeping the original string unchanged), replacing all matching substrings from with to, and returning the processed new object
        {
            StringPlus result(str);
            result.replaceAll(from, to);
            return result;
        }

        // String check
        bool startsWith(const StringPlus& prefix) const noexcept                                  // Defined a function startsWith(), to check if the current string starts with the specified prefix prefix prefix. If the length is insufficient, it returns false directly. Otherwise, it compares the content to ensure that no exception is thrown (noexcept)
        {
            if (prefix.length() > str.length()) return false;
            return str.compare(0, prefix.length(), prefix.str) == 0;
        }

        bool endsWith(const StringPlus& suffix) const noexcept                                    // Defined a function endsith(), to check if the current string ends with the specified suffix suffix suffix. If the length is insufficient, it returns false directly. Otherwise, it compares the content from the end to ensure that no exception is thrown (noexcept)
        {
            if (suffix.length() > str.length()) return false;
            return str.compare(str.length() - suffix.length(), suffix.length(), suffix.str) == 0; 
        }

        bool contains(const StringPlus& s) const noexcept                                         // Defined a function contains(), to check if the current string contains a substring s (searched by find()), returns true if it exists, returns false if not, ensuring no exception is thrown (noexcept)
        {
            return str.find(s.str) != nopos;
        }

        bool contains(char ch) const noexcept                                                     // Defined a function contains(), to check if the current string contains the specified character ch, returns true if it exists, returns false if not, ensuring no exception is thrown (noexcept)
        {
            return str.find(ch) != nopos;
        }

        // digital conversion
        static StringPlus fromInt(int_type value)                                      // Defined a function fromInt(), to convert an integer value into a corresponding decimal string, and encapsulated it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromUInt(unsigned int value)                                 // Defined a function fromUInt(), to convert an unsigned integer value into a corresponding decimal string and encapsulate it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromLong(long value)                                         // Defined a function fromLong(), to convert a long integer value into a corresponding decimal string, and encapsulated it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromULong(unsigned long value)                               // Defined a function fromULong(), to convert an unsigned long integer value to a decimal string and encapsulate it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromLongLong(long long value)                                // Defined a function fromLongLong(), to convert a 64 bit long long integer value into a decimal string and encapsulate it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromULongLong(unsigned long long value)                      // Defined a function fromULongLong(), to convert a 64 bit unsigned long long integer value to a decimal string and encapsulate it as a StringPlus object to return
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromFloat(float value, int precision = 6)                    // Defined a function fromFloat(), to convert floating-point values into strings, supports custom precision control, and encapsulates them as StringPlus objects to return
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(precision) << value;
            return StringPlus(ss.str());
        }

        static StringPlus fromDouble(double value, int precision = 6)                  // Defined a function fromDouble(), to convert a double precision floating-point value to a string, supports custom decimal places, and encapsulates it as a StringPlus object to return
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(precision) << value;
            return StringPlus(ss.str());
        }

        int_type toInt(bool* ok = nullptr) const                                       // Defined a function toInt(), for safely converting strings to integers, implemented through std::stoi() conversion. The optional ok parameter returns a success status, and when exceeded, throws the string_to-type_out_of_range exception
        {
            try {
                if (ok) *ok = true;
                return std::stoi(str);
            }
            catch (out_of_range err)
            {
                if (ok) *ok = false;
                throw string_to_type_out_of_range("number is out of int max or min");
            }
            catch (...) 
            {
                if (ok) *ok = false;
                return 0;
            }
        }

        float toFloat(bool* ok = nullptr) const                                        // Defined a function toFloat(), to safely convert strings to float type, using std::stof() for conversion, returns the status through the ok parameter, throws an exception string_to_type_out_of_range when the value exceeds the limit, returns 0.0f for non numeric input and marks failure
        {
            try
            {
                if (ok) *ok = true;
                return std::stof(str);
            }
            catch (out_of_range err)
            {
                if (ok) *ok = false;
                throw string_to_type_out_of_range("number is out of float max or min");
            }
            catch (...)
            {
                if (ok) *ok = false;
                return 0;
            }
        }

        double toDouble(bool* ok = nullptr)                                            // Defined a function toDouble()£¬ to convert a string to a double type, using std::stod() for secure conversion. Optional parameter ok returns a success status, throws an exception string_to-type_out_of_range when out of bounds, returns 0.0 for invalid input and marks failure
        {
            try
            {
                if (ok) *ok = true;
                return std::stod(str);
            }
            catch (out_of_range err)
            {
                if (ok) *ok = false;
                throw string_to_type_out_of_range("number is out of double max or min");
            }
            catch (...)
            {
                if (ok) *ok = false;
                return 0;
            }
        }

        // format string
        template<typename... Args>
        static StringPlus format(const char* fmt, Args&&... args)                     // Defined a function format(), for implementing type safe formatted string constructors, using C-style printf format syntax, but avoiding the security risks of traditional formatting functions through template parameters and smart pointers
        {
            int size = std::snprintf(nullptr, 0, fmt, args...);
            if (size <= 0) return StringPlus();

            std::unique_ptr<char[]> buf(new char[size + 1]);
            std::snprintf(buf.get(), size + 1, fmt, args...);

            return StringPlus(buf.get());
        }

        // string concatenation
        template<typename... Args>
        static StringPlus concat(Args&&... args)               // Defined a function concat(), for efficient concatenation of mutable parameters, which adds any number of parameters to a string through a fold expression and returns the concatenated new object
        {
            StringPlus result;
            (result.append(std::forward<Args>(args)), ...);
            return result;
        }

        // comparison operator
        bool operator==(const StringPlus& rhs) const noexcept { return str == rhs.str; } // This member function overloads the ==operator, which is used to compare whether the underlying string contents of two StringPlus objects are exactly the same, ensuring that no exceptions are thrown during the comparison process (noexcept)
        bool operator!=(const StringPlus& rhs) const noexcept { return str != rhs.str; } // This member function overloads the !=operator, used to determine whether the underlying string content of two StringPlus objects is different, ensuring that no exception is thrown during the comparison process (noexcept)
        bool operator<(const StringPlus& rhs) const noexcept                             // This member function overloads the <operator to implement lexicographic comparison. When the string length is different, the length is compared first, and when the length is the same, the content is compared to ensure that no exceptions are thrown (noexcept)
        {
            if (str.size() == rhs.size())
                return str < rhs.str;
            else
                return str.size() < rhs.size();
        }
        bool operator<=(const StringPlus& rhs) const noexcept { return str <= rhs.str; } // This member function overloads the <=operator, which is used to determine whether the current string's lexicographic order is less than or equal to the target string rhs. The comparison process ensures that no exceptions are thrown (noexcept)
        bool operator>(const StringPlus& rhs) const noexcept                             // This member function overloads the >operator to implement length first lexicographic order comparison, satisfying strict weak order relationships and ensuring no exceptions are thrown
        {
            if (str.size() == rhs.size())
                return str > rhs.str;
            else
                return str.size() > rhs.size();
        }
        bool operator>=(const StringPlus& rhs) const noexcept { return str >= rhs.str; } // This member function overloads the >=operator, which is used to determine whether the current string has a lexicographic order greater than or equal to the target string rhs. The comparison process ensures that no exceptions are thrown (noexcept)

        // Other Operations
        void push_back(char c) { str.push_back(c); } // Defined a function push_back(), to efficiently append a single character (char type) to the end of a string, which will automatically trigger expansion when the string capacity is insufficient
        void pop_back() { str.pop_back(); }          // Defined a function pop_back(), to delete the last character (char) of a string

        // Regular expression support
        bool matches(const StringPlus& pattern) const                                          // Defined a function matches()£¬ for regular expression to check if a string exactly matches a given pattern. If the conversion fails (regex_error, runtime_error), it throws an exception string_error and returns false for other exceptions
        {
            try {
                std::regex re(pattern.str);
                return std::regex_match(str, re);
            }
            catch (regex_error err) { throw string_error("regex error"); }
            catch (bad_alloc err) { throw string_error("out of memory"); }
            catch (...) { return false; }
        }

        StringPlus regexReplace(const StringPlus& pattern, const StringPlus& replacement) const // Defined a function regexReplaced(), to implement global replacement of regular expressions, replacing all substrings in a string that match a given pattern with specified content, returning a new string, and throwing an exception string_ error if an error occurs (regex_ error, runtime_ error thrown)
        {
            try {
                std::regex re(pattern.str);
                return StringPlus(std::regex_replace(str, re, replacement.str));
            }
            catch (regex_error err) { throw string_error("regex logic error"); }
            catch (bad_alloc err) { throw string_error("out of memory"); }
            catch (...) {
                return *this;
            }
        }

        // Wide character conversion (using Windows API)
        static StringPlus fromWide(const std::wstring& wstr)                                                                // Defined a function fromWide(), to convert a wide character string (std::wstring) to a UTF-8 encoded regular string (StringPlus), using Windows API's WideCharToMultiByte() for secure conversion, automatically handling empty strings and buffer size calculations
        {
            if (wstr.empty()) return StringPlus();

            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
            std::string str(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &str[0], size_needed, nullptr, nullptr);
            return StringPlus(str);
        }

        std::wstring toWide() const                                                                                         // Defined a function toWide() to convert a regular string (StringPlus) into a wide character string (std::wstring), using Windows API's MultiByteToWideChar() for secure conversion, automatically handling empty strings and buffer calculations, ensuring encoding correctness
        {
            if (str.empty()) return std::wstring();

            int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
            std::wstring wstr(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &wstr[0], size_needed);
            return wstr;
        }

        // String Split
        std::vector<StringPlus> split(const StringPlus& delimiter, bool keepEmpty = false) const // Defined a function split(), to implement string splitting function, which splits the current string into substring arrays according to the specified delimiter, and returns the collection of std:: vector<StringPlus>
        {
            std::vector<StringPlus> tokens;
            pos_type start = 0;
            pos_type end = str.find(delimiter.str);

            while (end != nopos) 
            {
                if (start != end || keepEmpty)
                {
                    tokens.emplace_back(str.substr(start, end - start));
                }
                start = end + delimiter.length();
                end = str.find(delimiter.str, start);
            }

            if (start < str.length() || keepEmpty) 
            {
                tokens.emplace_back(str.substr(start));
            }

            return tokens;
        }

        // UTF-8 support
        size_type utf8Length() const noexcept                                               // Defined a function utf8Length(), has been defined to calculate the character length (non byte length) of UTF-8 encoded strings. By analyzing byte header tags, it intelligently counts the number of Unicode characters to ensure that no exceptions are thrown.
        {
            size_type len = 0;
            for (unsigned char c : str)
            {
                if ((c & 0xC0) != 0x80) ++len;
            }
            return len;
        }

        StringPlus utf8Substr(pos_type pos, pos_type count = nopos) const                   // Defined a function utf8Substr(), to implement UTF-8 secure substring truncation, operating based on Unicode character positions rather than byte positions, to avoid garbled characters when cutting multi byte characters
        {
            pos_type bytePos = 0;
            pos_type charCount = 0;

            for (; bytePos < str.size() && charCount < pos; ++bytePos) 
            {
                if ((str[bytePos] & 0xC0) != 0x80) ++charCount;
            }

            if (charCount < pos) return StringPlus();

            pos_type start = bytePos;
            pos_type end = start;

            for (charCount = 0; end < str.size() && (count == nopos || charCount < count); ++end) 
            {
                if ((str[end] & 0xC0) != 0x80) ++charCount;
            }

            return StringPlus(str.substr(start, end - start));
        }

        // practical method
        bool is_clear() const noexcept { return str.empty(); }       // Defined a function is_clear(), to check if a string is empty (length 0), ensuring no exceptions are thrown and execution efficiency is O (1)

        bool is_printable() const noexcept                           // Defined a function is_printable(), to check if a string is entirely composed of printable ASCII characters, implemented using the standard algorithm std:: all_of() to ensure no exceptions are thrown (noexcept)
        {
            return std::all_of(str.begin(), str.end(), [](char c) 
                {
                return c >= 32 && c <= 126;
                });
        }

        StringPlus reverse() const                                   // Defined a function reverse() to implement string inversion, creating a reverse copy of the current string and returning it, while keeping the original string unchanged
        {
            StringPlus result(*this);
            std::reverse(result.str.begin(), result.str.end());
            return result;
        }

        [[nodiscard("Without storing data, it is impossible to output")]] Chars GetIndexCharType(size_type index) // Defined a function GetIndexCharType(), that checks the type of a character at a specified position in a string (uppercase/lowercase/numeric/other). If the index is out of bounds, it throws a exception index_is_out_of_string and forces the caller to handle the return value through [[nodiscard]]
        {
            if (index > size())
                throw index_is_out_of_string("index is out of size.");

            if (isupper(str[index]))
                return Chars::Upper;
            else if (islower(str[index]))
                return Chars::Lower;
            else if (isdigit(str[index])) 
                return Chars::Digit;
            else 
                return Chars::Else;
        }

        // String filling
        StringPlus& padLeft(size_type totalLen, char padChar = ' ') //Defined a function padLeft(), that fills the specified character (default space) on the left side of the string until the target length is reached, and only fills it when it is insufficient, and returns the reference of the current object to support chain calls
        {
            if (str.length() < totalLen) 
                str.insert(0, totalLen - str.length(), padChar);
            return *this;
        }

        // string repetition
        StringPlus repeat(size_type count) const  // Defined a function repetiti(), to concatenate the current string a specified number of times, optimize performance through pre allocated memory, and return a new string object without modifying the original string
        {
            StringPlus result;
            result.reserve(str.length() * count);
            for (size_type i = 0; i < count; ++i) 
            {
                result += str;
            }
            return result;
        }

        // Character settings
        void SetIndexCharType(size_type index, Letter lettertype)                                       // Defined a function SetIndexCharType(), to modify the case of letters in a specified position of a string (ensuring that the index is valid and the target is a letter character), and throws an exception (index_is_out_of_string or string_comror) when input is illegal
        {
            if (index < 0 || index > size())
                throw index_is_out_of_string("index is out of size.");
            if (!((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z')))
                throw string_error("the character at the index position is not a letter.");

            if (lettertype == Letter::upper)
                str[index] = toupper(str[index]);
            else
                str[index] = tolower(str[index]);
        }

        //Get character case
        [[nodiscard("Without storing data, it is impossible to output")]]Letter GetIndexLetterType(size_type index)   // Defined a function GetIndexLetterType(), to detect the case type (uppercase/lowercase) of letters at a specified position in a string. If the index is out of bounds or non letter characters, it throws a corresponding exception and enforces the return value through [nodiscard]
        {
            if (index < 0 || index > size())
                throw index_is_out_of_string("index is out of size.");
            if (!((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z')))
                throw string_error("the character at the index position is not a letter.");

            if (isupper(str[index]))
                return Letter::upper;
            else
                return Letter::lower;
        }

        [[nodiscard("Without storing data, it is impossible to output")]] std::map<std::string, int> GetCharTypeCount() // Defined a function GetCharTypeCount(), to count the occurrence of various types of characters in a string (uppercase/lowercase/numeric/other), returned the std:: map structure, and enforced the processing result through [[nodiscard]]
        {
            std::map<std::string, int> mpcnt;

            for (char c : str)
            {
                if (isupper(c))
                    mpcnt["upper"]++;
                else if (islower(c))
                    mpcnt["lower"]++;
                else if (isdigit(c))
                    mpcnt["digit"]++;
                else
                    mpcnt["else"]++;
            }

            return mpcnt;
        }

        [[nodiscard("Without storing data, it is impossible to output")]] std::map<std::string, int> GetLetterTypeCount() // Defined a function GetLetterTypeCount(), to count the number of occurrences of uppercase and lowercase letters in a string, returned a std:: map containing the statistical result, and forced the caller to process the return value through [[nodiscard]]
        {
            std::map<std::string, int> mpcnt;

            for (char c : str)
            {
                if (isupper(c))
                    mpcnt["upper"]++;
                else if (islower(c))
                    mpcnt["lower"]++;
            }
            return mpcnt;
        }
    }; // class StringPlus

    void clstr(std::string& str) noexcept { str.clear(); }        // Defined a function clstr(), to clear the contents of a standard strings, preserve memory allocation, and ensure no exceptions are thrown
    void clstr(StringPlus& str) noexcept { str.clear(); }         // Defined a function clstr(), to clear the contents of a strengthened string (StringPlus), preserve memory allocation, and ensure no exceptions are thrown
    void clstr(const char*& str) noexcept { str = ""; }           // Defined a function clstr(), to clear the contents of a C-style string (const char *) to an empty string '' (only changing the pointer point without freeing the original memory), ensuring that no exceptions are thrown.
    void pause() { system("pause"); }                             // Defined a function pause(), to pause the program (Windows platform depends on system ("pause")) with no return value
    [[noreturn]]void Exit(int code) noexcept { std::exit(code); } // Defined a function Exit(), to immediately terminate the program and return a status code. The annotation [norturn] indicates that the function will not return control, ensuring that no exceptions are thrown

    // Character type value conversion
    std::string PrintCharType(StringPlus::Chars chartype)             // Defined a function PrintCharType(), to convert character type enumeration values into corresponding string descriptions (uppercase/lowercase/numeric/other), returning easily understandable classification results
    {
        if (chartype == StringPlus::Chars::Upper)
            return "Upper";
        else if (chartype == StringPlus::Chars::Lower)
            return "Lower";
        else if (chartype == StringPlus::Chars::Digit)
            return "Digit";
        else
            return "Else";
    }

    void sPrintCharType(std::string& str, StringPlus::Chars chartype) // Defined a function sPintCharType(), to convert character type enumeration values into corresponding string descriptions (uppercase/lowercase/numeric/other) and store the results in the passed string reference, avoiding the cost of copying return values
    {
        if (chartype == StringPlus::Chars::Upper)
            str = "Upper";
        else if (chartype == StringPlus::Chars::Lower)
            str = "Lower";
        else if (chartype == StringPlus::Chars::Digit)
            str = "Digit";
        else
            str = "Else";
    }

    size_t strlen(StringPlus str) { return str.size(); }          // Defined a function strlen(), to implement the length query function for StringPlus class objects, returning the valid number of characters (excluding the terminator) of the current string
    size_t strlen(std::string str) { return str.size(); }         // Defined a function strlen(), to provide a length query for the standard string std:: string
    size_t strmaxsize(std::string str) { return str.max_size(); } // Defined a function strmaxsize(), to return the maximum theoretical length that std:: string can support in the current system environment, which depends on the memory architecture and standard library implementation
    
    StringPlus operator""sp(const char* str, size_t size) { return StringPlus(str, size); } // Define the Literal Operator (UDL) sp, to directly construct a StringPlus object using the concise syntax of "text" sp, efficiently forwarding C-style strings and their lengths to the constructor
    
} // namespace std

// Flow operator
inline std::ostream& operator<<(std::ostream& os, const std::StringPlus& str) // Overloading the <<operator to enable StringPlus objects to directly output content through the standard output stream, internally calling the s_str() method to retrieve string data and supporting chain operations
{
    return os << str.s_str();
}

inline std::istream& operator>>(std::istream& is, std::StringPlus& str)       // Overloading the >>operator, allowing data to be directly read into a StringPlus object through a standard input stream, using an intermediate std:: string to temporarily store data and optimize performance by moving constructs, and finally returning an input stream reference to support chained input operations
{
    std::string s;
    is >> s;
    str = std::StringPlus(std::move(s));
    return is;
}

// Type alias
using StringPlusArray = std::vector<std::StringPlus>; // Define the dynamic array type of StringPlus, based on the standard library's std:: vector container implementation, providing complete container functionality such as dynamic scaling and iterator access, suitable for scenarios where multiple StringPlus objects need to be stored (such as string lists, batch processing, etc.)
using StringPlus_ptr = std::StringPlus*;              // Define the primitive pointer type StringPlus_ptr for StringPlus, used to directly manage or manipulate StringPlus objects in heap memory, suitable for low-level operations that require explicit control of memory lifecycle or interaction with C-style APIs


#endif // __INC_STRINGPLUS_H__
