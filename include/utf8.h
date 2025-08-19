//   ________  ___________  ________       ____________  ______       ___   __________    ________    ___          ___      ___   ________ 
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
// |- StringPlus.h
// |- utf8.h       <--
// |- coding.h

#pragma once
#ifndef __INC_STRINGPLUS_UTF8_H__
#define __INC_STRINGPLUS_UTF8_H__

#include <string>
#include <vector>
#include <stdexcept>
#include <StringPlus.h>

namespace std 
{
    class UTF8 : public std::StringPlus
    {
    public:
        // Check if a character is a subsequent byte of a UTF-8 multi byte sequence
        static bool is_continuation_byte(unsigned char c) // Defined a function is_comtination_byte () to check if a byte is a contiguous byte in UTF-8 encoding (i.e., not the first byte), by determining if the high-order bit of the byte starts with 10 (0xC0 mask)
        {
            return (c & 0xC0) == 0x80;
        }

        // Get the byte length of UTF-8 characters
        static size_t char_length(unsigned char first_byte)              // Defined a function char_length() to analyze the high-order pattern of the first byte in UTF-8 and determine the number of bytes occupied by the character (1-4 bytes). Illegal bytes return 0
        {
            if ((first_byte & 0x80) == 0x00) return 1;       // 0xxxxxxx
            if ((first_byte & 0xE0) == 0xC0) return 2;       // 110xxxxx
            if ((first_byte & 0xF0) == 0xE0) return 3;       // 1110xxxx
            if ((first_byte & 0xF8) == 0xF0) return 4;       // 11110xxx
            return 0;
        }

        // Verify the validity of UTF-8 strings
        static bool is_valid_utf8(const std::string& str)    // Defined a function is_falid_utf8(), which is used to verify the validity of UTF-8 encoding byte by byte, check whether the character length flag and continuous byte format are correct, and return the verification result after traversing the string completely
        {
            for (size_t i = 0; i < str.size(); ) 
            {
                unsigned char c = str[i];
                size_t length = char_length(c);

                if (length == 0) return false;

                if (i + length > str.size()) return false;

                for (size_t j = 1; j < length; ++j)
                {
                    if (!is_continuation_byte(str[i + j])) 
                    {
                        return false;
                    }
                }

                i += length;
            }
            return true;
        }

        // Get the number of characters (code points) in a UTF-8 string
        static size_t char_count(const std::string& str)                // Defined a function char_count() to count the number of characters (non byte) in a UTF-8 string, first verifying the validity of the encoding, then iterating to calculate the number of characters and returning
        {
            if (!is_valid_utf8(str)) 
            {
                throw std::runtime_error("Invalid UTF-8 string");
            }

            size_t count = 0;
            for (size_t i = 0; i < str.size(); ) 
            {
                unsigned char c = str[i];
                size_t length = char_length(c);
                i += length;
                ++count;
            }
            return count;
        }

        // Retrieve the nth character from a UTF-8 string
        static std::string index_char(const std::string& str, size_t n) // Defined a function index_char() to securely retrieve the substring of the nth character in a UTF-8 string (counted by Unicode characters), traverse and locate after encoding validation, and throw an exception when the index is out of bounds
        {
            if (!is_valid_utf8(str)) 
            {
                throw std::runtime_error("Invalid UTF-8 string");
            }

            size_t count = 0;
            for (size_t i = 0; i < str.size(); ) 
            {
                unsigned char c = str[i];
                size_t length = char_length(c);

                if (count == n) 
                {
                    return str.substr(i, length);
                }

                i += length;
                ++count;
            }

            throw std::out_of_range("UTF-8 character index out of range");
        }

        // Split UTF-8 strings into character vectors
        static std::vector<std::string> split(const std::string& str) // Defined a function split() to split a UTF-8 string into a vector composed of individual Unicode characters, verify the validity of the encoding, split by character boundaries, and return the result
        {
            if (!is_valid_utf8(str))
            {
                throw std::runtime_error("Invalid UTF-8 string");
            }

            std::vector<std::string> chars;
            for (size_t i = 0; i < str.size(); ) 
            {
                unsigned char c = str[i];
                size_t length = char_length(c);
                chars.push_back(str.substr(i, length));
                i += length;
            }
            return chars;
        }

        // Extract the first n characters of a UTF-8 string
        static std::string substr(const std::string& str, size_t pos, size_t len = std::string::npos) // Defined a function substr() for implementing UTF-8 secure substring truncation, operating based on Unicode character positions rather than byte positions, automatically handling multi byte character boundaries, and avoiding garbled characters
        {
            if (!is_valid_utf8(str)) 
            {
                throw std::runtime_error("Invalid UTF-8 string");
            }

            std::string result;
            size_t count = 0;
            for (size_t i = 0; i < str.size(); ) 
            {
                unsigned char c = str[i];
                size_t length = char_length(c);

                if (count >= pos && count < pos + len) 
                {
                    result.append(str.substr(i, length));
                }

                i += length;
                ++count;

                if (count >= pos + len)
                {
                    break;
                }
            }
            return result;
        }
    };

} // namespace std


#endif // __INC_STRINGPLUS_UTF8_H__
