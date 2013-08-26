#ifndef _UTIL_UTF8ITERATOR_HPP
#define _UTIL_UTF8ITERATOR_HPP

#include <string>

class Utf8Iterator : public std::iterator<std::bidirectional_iterator_tag, char32_t, std::string::difference_type, const char32_t*, const char32_t&> {
public:
    Utf8Iterator(std::string::const_iterator it);
    Utf8Iterator(const Utf8Iterator& source);
    Utf8Iterator& operator=(const Utf8Iterator& rhs);

    char32_t operator *() const;
    bool operator ==(const Utf8Iterator& rhs) const;
    bool operator !=(const Utf8Iterator& rhs) const;
    Utf8Iterator& operator ++();
    Utf8Iterator operator ++(int);
    Utf8Iterator& operator --();
    Utf8Iterator operator --(int);

    bool operator ==(std::string::iterator rhs) const;
    bool operator ==(std::string::const_iterator rhs) const;
    bool operator !=(std::string::iterator rhs) const;
    bool operator !=(std::string::const_iterator rhs) const;

    const unsigned char kFirstBitMask = 128; // 1000000
    const unsigned char kSecondBitMask = 64; // 0100000
    const unsigned char kThirdBitMask = 32; // 0010000
    const unsigned char kFourthBitMask = 16; // 0001000
    const unsigned char kFifthBitMask = 8; // 0000100
private:
    std::string::const_iterator mStringIterator;
};

#endif
