#include "Utf8Iterator.hpp"

Utf8Iterator::Utf8Iterator(std::string::const_iterator it)
    : mStringIterator(it)
{}

Utf8Iterator::Utf8Iterator(const Utf8Iterator& source)
    : mStringIterator(source.mStringIterator)
{}

Utf8Iterator& Utf8Iterator::operator=(const Utf8Iterator& rhs)
{
    mStringIterator = rhs.mStringIterator;
    return *this;
}

char32_t Utf8Iterator::operator *() const
{
    char32_t codePoint = 0;

    char firstByte = *mStringIterator;

    if(firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
    {
        if(firstByte & kThirdBitMask) // This means that the first byte has a value greater than 191, and so it must be at least a three-octet code point.
        {
            if(firstByte & kFourthBitMask) // This means that the first byte has a value greater than 224, and so it must be a four-octet code point.
            {
                codePoint = (firstByte & 0x07) << 18;
                char secondByte = *(mStringIterator + 1);
                codePoint +=  (secondByte & 0x3f) << 12;
                char thirdByte = *(mStringIterator + 2);
                codePoint +=  (thirdByte & 0x3f) << 6;;
                char fourthByte = *(mStringIterator + 3);
                codePoint += (fourthByte & 0x3f);
            }
            else
            {
                codePoint = (firstByte & 0x0f) << 12;
                char secondByte = *(mStringIterator + 1);
                codePoint += (secondByte & 0x3f) << 6;
                char thirdByte = *(mStringIterator + 2);
                codePoint +=  (thirdByte & 0x3f);
            }
        }
        else
        {
            codePoint = (firstByte & 0x1f) << 6;
            char secondByte = *(mStringIterator + 1);
            codePoint +=  (secondByte & 0x3f);
        }
    }
    else
    {
        codePoint = firstByte;
    }

    return codePoint;
}

Utf8Iterator& Utf8Iterator::operator++()
{
    char firstByte = *mStringIterator;
    std::string::difference_type offset = 1;
    if(firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
    {
        if(firstByte & kThirdBitMask) // This means that the first byte has a value greater than 224, and so it must be at least a three-octet code point.
        {
            if(firstByte & kFourthBitMask) // This means that the first byte has a value greater than 240, and so it must be a four-octet code point.
                offset = 4;
            else
                offset = 3;
        }
        else
        {
            offset = 2;
        }
    }

    mStringIterator += offset;
    return *this;
}

Utf8Iterator Utf8Iterator::operator++(int)
{
    Utf8Iterator temp = *this;
    ++(*this);
    return temp;
}

Utf8Iterator& Utf8Iterator::operator--()
{
    --mStringIterator;

    if(*mStringIterator & kFirstBitMask) // This means that the previous byte is not an ASCII character.
    {
        --mStringIterator;
        if((*mStringIterator & kSecondBitMask) == 0)
        {
            --mStringIterator;
            if((*mStringIterator & kSecondBitMask) == 0)
            {
                --mStringIterator;
            }
        }
    }
    return *this;
}

Utf8Iterator Utf8Iterator::operator--(int)
{
    Utf8Iterator temp = *this;
    --(*this);
    return temp;
}


bool Utf8Iterator::operator==(std::string::iterator rhs) const
{
    return mStringIterator ==  rhs;
}

bool Utf8Iterator::operator==(std::string::const_iterator rhs) const
{
    return mStringIterator ==  rhs;
}

bool Utf8Iterator::operator!=(std::string::iterator rhs) const
{
    return mStringIterator !=  rhs;
}

bool Utf8Iterator::operator!=(std::string::const_iterator rhs) const
{
    return mStringIterator !=  rhs;
}
