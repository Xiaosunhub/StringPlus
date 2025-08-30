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
        size_type length() const noexcept { return str.length(); }              // 
        size_type capacity() const noexcept { return str.capacity(); }          // 
        void reserve(size_type new_cap) { str.reserve(new_cap); }               // 
        void shrink_to_fit() { str.shrink_to_fit(); }                           // 

        // 修改器
        void clear() noexcept { str.clear(); }
        StringPlus& append(const std::string& s) { str.append(s); return *this; }
        StringPlus& append(const char* s, size_type count) { str.append(s, count); return *this; }
        StringPlus& append(const char* s) { str.append(s); return *this; }
        StringPlus& append(size_type count, char ch) { str.append(count, ch); return *this; }

        template<class InputIt>
        StringPlus& append(InputIt first, InputIt last) { str.append(first, last); return *this; }

        StringPlus operator*(int_type n)
        {
            StringPlus strpl = (StringPlus)str;
            for (int i = 1;i < n;i++)
                strpl += str;
            return strpl;
        }

        StringPlus& operator*=(int_type n)
        {
            StringPlus strpl = (StringPlus)str;
            for (int i = 1;i < n;i++)
                strpl += str;
            str = strpl;
            return *this;
        }

        // 运算符重载
        StringPlus& operator+=(const StringPlus& rhs) { str += rhs.str; return *this; }
        StringPlus& operator+=(const std::string& rhs) { str += rhs; return *this; }
        StringPlus& operator+=(const char* rhs) { str += rhs; return *this; }
        StringPlus& operator+=(char ch) { str += ch; return *this; }

        // AND 运算符
        StringPlus operator&(const StringPlus& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] &= rhs.str[i];
            }
            return result;
        }

        StringPlus operator&(const std::string& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] &= rhs[i];
            }
            return result;
        }

        StringPlus operator&(const char* rhs) const
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] &= rhs[i];
            }
            return result;
        }

        // OR 运算符
        StringPlus operator|(const StringPlus& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] |= rhs.str[i];
            }
            return result;
        }

        StringPlus operator|(const std::string& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] |= rhs[i];
            }
            return result;
        }

        StringPlus operator|(const char* rhs) const
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] |= rhs[i];
            }
            return result;
        }

        // XOR 运算符
        StringPlus operator^(const StringPlus& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] ^= rhs.str[i];
            }
            return result;
        }

        StringPlus operator^(const std::string& rhs) const
        {
            StringPlus result(*this);
            size_type min_size = min(result.str.size(), rhs.size());
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] ^= rhs[i];
            }
            return result;
        }

        StringPlus operator^(const char* rhs) const
        {
            StringPlus result(*this);
            size_type rhs_len = std::strlen(rhs);
            size_type min_size = min(result.str.size(), rhs_len);
            for (size_type i = 0; i < min_size; ++i) {
                result.str[i] ^= rhs[i];
            }
            return result;
        }

        // 复合赋值运算符
        StringPlus& operator&=(const StringPlus& rhs)
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                str[i] &= rhs.str[i];
            }
            return *this;
        }

        StringPlus& operator|=(const StringPlus& rhs)
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                str[i] |= rhs.str[i];
            }
            return *this;
        }

        StringPlus& operator^=(const StringPlus& rhs)
        {
            size_type min_size = min(this->str.size(), rhs.str.size());
            for (size_type i = 0; i < min_size; ++i) {
                str[i] ^= rhs.str[i];
            }
            return *this;
        }

        // 已删除的运算符
        StringPlus operator~() const = delete;
        StringPlus operator<<(size_type) const = delete;
        StringPlus operator>>(size_type) const = delete;
        StringPlus& operator<<=(size_type) = delete;
        StringPlus& operator>>=(size_type) = delete;

        StringPlus& operator-=(char ch) = delete;
        StringPlus& operator-=(const StringPlus& rhs) = delete;
        StringPlus& operator-=(const char* cc) = delete;
        StringPlus& operator-=(const std::string& rhs) = delete;

        StringPlus operator-(char ch) const = delete;
        StringPlus operator-(const StringPlus& rhs) const = delete;
        StringPlus operator-(const char* cc) const = delete;
        StringPlus operator-(const std::string& rhs) const = delete;

        StringPlus& operator*=(char ch) = delete;
        StringPlus& operator*=(const StringPlus& rhs) = delete;
        StringPlus& operator*=(const char* cc) = delete;
        StringPlus& operator*=(const std::string& rhs) = delete;

        StringPlus operator*(char ch) const = delete;
        StringPlus operator*(const StringPlus& rhs) const = delete;
        StringPlus operator*(const char* cc) const = delete;
        StringPlus operator*(const std::string& rhs) const = delete;

        StringPlus& operator/=(char ch) = delete;
        StringPlus& operator/=(const StringPlus& rhs) = delete;
        StringPlus& operator/=(const char* cc) = delete;
        StringPlus& operator/=(const std::string& rhs) = delete;

        StringPlus operator/(char ch) const = delete;
        StringPlus operator/(const StringPlus& rhs) const = delete;
        StringPlus operator/(const char* cc) const = delete;
        StringPlus operator/(const std::string& rhs) const = delete;

        char& operator[](size_type pos) { return str[pos]; }
        const char& operator[](size_type pos) const { return str[pos]; }

        char& at(size_type pos) { return str.at(pos); }
        const char& at(size_type pos) const { return str.at(pos); }

        char& front() { return str.front(); }
        const char& front() const { return str.front(); }
        char& back() { return str.back(); }
        const char& back() const { return str.back(); }

        // 迭代器支持
        iterator begin() noexcept { return str.begin(); }
        const_iterator begin() const noexcept { return str.begin(); }
        const_iterator cbegin() const noexcept { return str.cbegin(); }
        iterator end() noexcept { return str.end(); }
        const_iterator end() const noexcept { return str.end(); }
        const_iterator cend() const noexcept { return str.cend(); }
        reverse_iterator rbegin() noexcept { return str.rbegin(); }
        const_reverse_iterator rbegin() const noexcept { return str.rbegin(); }
        const_reverse_iterator crbegin() const noexcept { return str.crbegin(); }
        reverse_iterator rend() noexcept { return str.rend(); }
        const_reverse_iterator rend() const noexcept { return str.rend(); }
        const_reverse_iterator crend() const noexcept { return str.crend(); }

        //字符类型枚举
        enum Chars
        {
            Upper = 1, Lower = 2, Digit = 3, Else = 4,
        };
        //字母类型枚举
        enum Letter
        {
            upper = 1, lower = 2,
        };

        // 字符串操作
        StringPlus substr(pos_type pos = 0, pos_type count = nopos) const
        {
            return StringPlus(str.substr(pos, count));
        }

        pos_type find(const StringPlus& s, pos_type pos = 0) const noexcept
        {
            return str.find(s.str, pos);
        }

        pos_type find(const char* s, pos_type pos = 0) const
        {
            return str.find(s, pos);
        }

        pos_type find(char ch, pos_type pos = 0) const noexcept
        {
            return str.find(ch, pos);
        }

        // 大小写转换
        StringPlus& toUpper() noexcept
        {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c) { return std::toupper(c); });
            return *this;
        }

        StringPlus& toLower() noexcept
        {
            std::transform(str.begin(), str.end(), str.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return *this;
        }

        StringPlus toUpperCopy() const noexcept
        {
            StringPlus result(str);
            result.toUpper();
            return result;
        }

        StringPlus toLowerCopy() const noexcept
        {
            StringPlus result(str);
            result.toLower();
            return result;
        }

        // 去除空白
        StringPlus& trimLeft()
        {
            str.erase(str.begin(), std::find_if(str.begin(), str.end(),
                [](unsigned char ch) { return !std::isspace(ch); }));
            return *this;
        }

        StringPlus& trimRight()
        {
            str.erase(std::find_if(str.rbegin(), str.rend(),
                [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
            return *this;
        }

        StringPlus& trim()
        {
            trimLeft();
            trimRight();
            return *this;
        }

        StringPlus trimLeftCopy() const
        {
            StringPlus result(str);
            result.trimLeft();
            return result;
        }

        StringPlus trimRightCopy() const
        {
            StringPlus result(str);
            result.trimRight();
            return result;
        }

        StringPlus trimCopy() const
        {
            StringPlus result(str);
            result.trim();
            return result;
        }

        // 字符串替换
        StringPlus& replaceAll(const StringPlus& from, const StringPlus& to)
        {
            pos_type pos = 0;
            while ((pos = str.find(from.str, pos)) != nopos) {
                str.replace(pos, from.length(), to.str);
                pos += to.length();
            }
            return *this;
        }

        StringPlus replaceAllCopy(const StringPlus& from, const StringPlus& to) const
        {
            StringPlus result(str);
            result.replaceAll(from, to);
            return result;
        }

        // 字符串检查
        bool startsWith(const StringPlus& prefix) const noexcept
        {
            if (prefix.length() > str.length()) return false;
            return str.compare(0, prefix.length(), prefix.str) == 0;
        }

        bool endsWith(const StringPlus& suffix) const noexcept
        {
            if (suffix.length() > str.length()) return false;
            return str.compare(str.length() - suffix.length(), suffix.length(), suffix.str) == 0;
        }

        bool contains(const StringPlus& s) const noexcept
        {
            return str.find(s.str) != nopos;
        }

        bool contains(char ch) const noexcept
        {
            return str.find(ch) != nopos;
        }

        // 数字转换
        static StringPlus fromInt(int_type value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromUInt(unsigned int value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromLong(long value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromULong(unsigned long value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromLongLong(long long value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromULongLong(unsigned long long value)
        {
            return StringPlus(std::to_string(value));
        }

        static StringPlus fromFloat(float value, int precision = 6)
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(precision) << value;
            return StringPlus(ss.str());
        }

        static StringPlus fromDouble(double value, int precision = 6)
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(precision) << value;
            return StringPlus(ss.str());
        }

        int_type toInt(bool* ok = nullptr) const
        {
            try {
                if (ok) *ok = true;
                return std::stoi(str);
            }
            catch (...) {
                if (ok) *ok = false;
                return 0;
            }
        }

        float toFloat(bool* ok = nullptr) const
        {
            try
            {
                if (ok) *ok = true;
                return std::stof(str);
            }
            catch (...)
            {
                if (ok) *ok = false;
                return 0;
            }
        }

        double toDouble(bool* ok = nullptr)
        {
            try
            {
                if (ok) *ok = true;
                return std::stod(str);
            }
            catch (...)
            {
                if (ok) *ok = false;
                return 0;
            }
        }

        // 格式化字符串
        template<typename... Args>
        static StringPlus format(const char* fmt, Args&&... args)
        {
            int size = std::snprintf(nullptr, 0, fmt, args...);
            if (size <= 0) return StringPlus();

            std::unique_ptr<char[]> buf(new char[size + 1]);
            std::snprintf(buf.get(), size + 1, fmt, args...);

            return StringPlus(buf.get());
        }

        // 字符串连接
        template<typename... Args>
        static StringPlus concat(Args&&... args)
        {
            StringPlus result;
            (result.append(std::forward<Args>(args)), ...);
            return result;
        }

        // 比较运算符
        bool operator==(const StringPlus& rhs) const noexcept { return str == rhs.str; }
        bool operator!=(const StringPlus& rhs) const noexcept { return str != rhs.str; }
        bool operator<(const StringPlus& rhs) const noexcept
        {
            if (str.size() == rhs.size())
                return str < rhs.str;
            else
                return str.size() < rhs.size();
        }
        bool operator<=(const StringPlus& rhs) const noexcept { return str <= rhs.str; }
        bool operator>(const StringPlus& rhs) const noexcept
        {
            if (str.size() == rhs.size())
                return str > rhs.str;
            else
                return str.size() > rhs.size();
        }
        bool operator>=(const StringPlus& rhs) const noexcept { return str >= rhs.str; }

        // 其他操作
        void push_back(char c) { str.push_back(c); }
        void pop_back() { str.pop_back(); }

        // 正则表达式支持
        bool matches(const StringPlus& pattern) const
        {
            try {
                std::regex re(pattern.str);
                return std::regex_match(str, re);
            }
            catch (...) {
                return false;
            }
        }

        StringPlus regexReplace(const StringPlus& pattern, const StringPlus& replacement) const
        {
            try {
                std::regex re(pattern.str);
                return StringPlus(std::regex_replace(str, re, replacement.str));
            }
            catch (...) {
                return *this;
            }
        }

        // 宽字符转换 (使用Windows API)
        static StringPlus fromWide(const std::wstring& wstr)
        {
            if (wstr.empty()) return StringPlus();

            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
            std::string str(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &str[0], size_needed, nullptr, nullptr);
            return StringPlus(str);
        }

        std::wstring toWide() const
        {
            if (str.empty()) return std::wstring();

            int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
            std::wstring wstr(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &wstr[0], size_needed);
            return wstr;
        }

        // 字符串分割
        std::vector<StringPlus> split(const StringPlus& delimiter, bool keepEmpty = false) const
        {
            std::vector<StringPlus> tokens;
            pos_type start = 0;
            pos_type end = str.find(delimiter.str);

            while (end != nopos) {
                if (start != end || keepEmpty) {
                    tokens.emplace_back(str.substr(start, end - start));
                }
                start = end + delimiter.length();
                end = str.find(delimiter.str, start);
            }

            if (start < str.length() || keepEmpty) {
                tokens.emplace_back(str.substr(start));
            }

            return tokens;
        }

        // UTF-8支持
        size_type utf8Length() const noexcept
        {
            size_type len = 0;
            for (unsigned char c : str) {
                if ((c & 0xC0) != 0x80) ++len;
            }
            return len;
        }

        StringPlus utf8Substr(pos_type pos, pos_type count = nopos) const
        {
            pos_type bytePos = 0;
            pos_type charCount = 0;

            // 找到起始字节位置
            for (; bytePos < str.size() && charCount < pos; ++bytePos) {
                if ((str[bytePos] & 0xC0) != 0x80) ++charCount;
            }

            if (charCount < pos) return StringPlus();

            pos_type start = bytePos;
            pos_type end = start;

            // 找到结束字节位置
            for (charCount = 0; end < str.size() && (count == nopos || charCount < count); ++end) {
                if ((str[end] & 0xC0) != 0x80) ++charCount;
            }

            return StringPlus(str.substr(start, end - start));
        }

        // 实用方法
        bool is_clear() const noexcept { return str.empty(); }

        bool is_printable() const noexcept
        {
            return std::all_of(str.begin(), str.end(), [](char c) {
                return c >= 32 && c <= 126;
                });
        }

        StringPlus reverse() const
        {
            StringPlus result(*this);
            std::reverse(result.str.begin(), result.str.end());
            return result;
        }

        [[nodiscard("Without storing data, it is impossible to output")]] Chars GetIndexCharType(size_type index)
        {
            if (index > size())
                throw out_of_range("index is out of size.");

            if (isupper(str[index]))
                return Chars::Upper;
            else if (islower(str[index]))
                return Chars::Lower;
            else if (isdigit(str[index]))
                return Chars::Digit;
            else
                return Chars::Else;
        }

        // 字符串填充
        StringPlus& padLeft(size_type totalLen, char padChar = ' ') {
            if (str.length() < totalLen) {
                str.insert(0, totalLen - str.length(), padChar);
            }
            return *this;
        }

        // 字符串重复
        StringPlus repeat(size_type count) const {
            StringPlus result;
            result.reserve(str.length() * count);
            for (size_type i = 0; i < count; ++i) {
                result += str;
            }
            return result;
        }

        //字符设置
        void SetIndexCharType(size_type index, Letter lettertype)
        {
            if (index < 0 || index > size())
                throw out_of_range("index is out of size.");
            if (lettertype == Letter::upper)
                str[index] = toupper(str[index]);
            else
                str[index] = tolower(str[index]);
        }
        //获取字符大小写
        [[nodiscard("Without storing data, it is impossible to output")]]Letter GetIndexLetterType(size_type index)
        {
            if (index < 0 || index > size())
                throw out_of_range("index is out of size.");
            if (isupper(str[index]))
                return Letter::upper;
            else
                return Letter::lower;
        }
        [[nodiscard("Without storing data, it is impossible to output")]] std::map<std::string, int> GetCharTypeCount()
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
        [[nodiscard("Without storing data, it is impossible to output")]] std::map<std::string, int> GetLetterTypeCount()
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
    };

    void clstr(std::string& str) noexcept { str.clear(); }
    void clstr(StringPlus& str) noexcept { str.clear(); }
    void clstr(const char*& str) noexcept { str = ""; }
    void pause() { system("pause"); }
    [[noreturn]]void Exit(int Val) noexcept { std::exit(Val); }

    //字符类型值转换
    std::string PrintCharType(StringPlus::Chars chartype)
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
    void sPrintCharType(std::string& str, StringPlus::Chars chartype)
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
    size_t strlen(StringPlus str) { return str.size(); }
    size_t strlen(std::string str) { return str.size(); }
    size_t strmaxsize(std::string str) { return str.max_size(); }
} // namespace std

// 流操作符
inline std::ostream& operator<<(std::ostream& os, const std::StringPlus& str)
{
    return os << str.s_str();
}

inline std::istream& operator>>(std::istream& is, std::StringPlus& str)
{
    std::string s;
    is >> s;
    str = std::StringPlus(std::move(s));
    return is;
}

// 类型别名
using StringPlusArray = std::vector<std::StringPlus>;
using StringPlus_ptr = std::StringPlus*;

#endif
