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
// |- StringPlus.h
// |- utf8.h
// |- coding.h     <--

#ifndef __INC_STRINGPLUS_CODING_H__
#define __INC_STRINGPLUS_CODING_H__

#include <StringPlus.h>
#include <algorithm>
#include <stdexcept>

namespace coding 
{

    // ===================== Caesar encoding / decoding =====================
    inline StringPlus Caesar_code(const StringPlus& str, int shift, bool encrypt = true) // Defined a function Caesar_code(), to implement the encryption/decryption function of Caesar Cipher, which replaces letter characters with a configurable shift while keeping non letter characters unchanged
    {
        if (str.empty())
            return str;

        StringPlus result;
        result.reserve(str.length());

        int direction = encrypt ? 1 : -1;
        shift = shift * direction;

        for (auto c : str)
        {
            if (isalpha(c)) 
            {
                char base = isupper(c) ? 'A' : 'a';
                c = static_cast<char>((c - base + shift + 26) % 26 + base);
            }
            result += c;
        }

        return result;
    }

    // ===================== XOR encoding / decoding =====================
    inline StringPlus XOR_code(const StringPlus& str, char key) // Defined a function XOR_code(), to implement XOR encryption and decryption function, which performs character by character XOR operation on a string through a single key character
    {
        if (str.empty())
            return str;

        StringPlus result;
        result.reserve(str.length());

        for (auto c : str)
        {
            result += c ^ key;
        }

        return result;
    }

    // ===================== Base64 encoding/decoding =====================
    namespace Base64 
    {
        const StringPlus base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // Defined 64 standard character sets for Base64 encoding (uppercase and lowercase letters, numbers,+, and/)

        inline bool isBase64(unsigned char c) { return (isalnum(c) || (c == '+') || (c == '/')); }         // Defined a function isBase64() to check if a character is a valid Base64 encoded character (letter, number, or+/)
    } // namespace Base64

    inline StringPlus Base64_encode(const StringPlus& str)                                                 // Defined a function Base64_encode() to implement Base64 encoding, which groups the input string into 4 Base64 characters every 3 bytes, fills in zeros and=padding when less than 3 bytes, and finally returns the encoded string
    {
        StringPlus ret;
        int i = 0;
        int j = 0;
        unsigned char charArray3[3];
        unsigned char charArray4[4];

        for (auto c : str) 
        {
            charArray3[i++] = c;
            if (i == 3) 
            {
                charArray4[0] = (charArray3[0] & 0xfc) >> 2;
                charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
                charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6;
                charArray4[3] = charArray3[2] & 0x3f;

                for (i = 0; i < 4; i++)
                    ret += Base64::base64Chars[charArray4[i]];
                i = 0;
            }
        }

        if (i) 
        {
            for (j = i; j < 3; j++)
                charArray3[j] = '\0';

            charArray4[0] = (charArray3[0] & 0xfc) >> 2;
            charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4;
            charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
            charArray4[3] = charArray3[2] & 0x3f;

            for (j = 0; j < i + 1; j++)
                ret += Base64::base64Chars[charArray4[j]];

            while (i++ < 3)
                ret += '=';
        }

        return ret;
    }

    inline StringPlus Base64_decode(const StringPlus& str)                                                 // Defined a function Base64_decode() for Base64 decoding, which converts the Base64 encoded string back to the original data, processes 4-character groups and ignores non Base64 characters, automatically removes the=padding at the end, and returns the decoded binary string
    { 
        StringPlus ret;
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char charArray3[3];
        unsigned char charArray4[4];

        for (auto c : str) 
        {
            if (!isBase64(c)) break;

            charArray4[i++] = c;
            if (i == 4)
            {
                for (i = 0; i < 4; i++)
                    charArray4[i] = base64Chars.find(charArray4[i]);

                charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4;
                charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2;
                charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

                for (i = 0; i < 3; i++)
                    ret += charArray3[i];
                i = 0;
            }
        }

        if (i)
        {
            for (j = i; j < 4; j++)
                charArray4[j] = 0;

            for (j = 0; j < 4; j++)
                charArray4[j] = base64Chars.find(charArray4[j]);

            charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4;
            charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
            charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];

            for (j = 0; j < i - 1; j++)
                ret += charArray3[j];
        }

        return ret;
    }

    // ===================== String inversion =====================
    inline StringPlus reverseString(const StringPlus& str) // Defined a function reverseString() to implement string reversal function. By creating a copy and calling the std:: reverse() algorithm to reverse the character sequence, the function returns a new string without modifying the original string
    {
        StringPlus result(str);
        std::reverse(result.begin(), result.end());
        return result;
    }

    // ===================== Replace codeing =====================
    inline StringPlus replace_code(const StringPlus& str,
        const StringPlus& fromChars,
        const StringPlus& toChars)                         // Defined a function replace_code() to implement character set replacement encoding, replacing characters that appear in from Chars with characters at the corresponding position in toChars (requiring the two character sets to be of the same length), and returning a new string
    {
        if (fromChars.length() != toChars.length()) 
        {
            throw string_error("From and to character sets must be of equal length");
        }

        StringPlus result(str);
        for (size_t i = 0; i < result.length(); ++i)
        {
            size_t pos = fromChars.find(result[i]);
            if (pos != StringPlus::npos) 
                result[i] = toChars[pos];
        }
        return result;
    }

} // namespace std


#endif // __INC_STRINGPLUS_CODING_H__

