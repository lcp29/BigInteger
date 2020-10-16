
#include "BigInteger.h"

void BigInteger::fixPosition(int p)
{
    while (num.length() <= p)
        num.insert(1, "0");
}

BigInteger BigInteger::mulLowP(long long t) const
{
    BigInteger r;
    for (int i = 1; i <= t; ++i)
        r = r + *this;
    return r;
}

BigInteger::BigInteger()
{
    num = "+0";
}

BigInteger::BigInteger(long long initNum)
{
    long long r = LLONG_MAX_R;
    bool firstDigit = false;
    int digit = 0;
    if (initNum >= 0)
        num.append("+");
    else
    {
        num.append("-");
        initNum = -initNum;
    }
    if (initNum == 0)
    {
        num = "+0";
        return;
    }
    for (int i = 0; i <= LLONG_MAX_DIGITS - 1; i++)
    {
        digit = initNum / r;
        if (digit != 0)
            firstDigit = true;
        if (firstDigit == true)
        {
            std::string d = std::to_string(digit);
            num.append(d);
            initNum -= r * digit;
        }
        r /= 10;
    }
}

BigInteger::BigInteger(std::string initNum)
{
    num = initNum;
    this->regulize();
}

bool BigInteger::operator==(const BigInteger &b) const
{
    return (this->num == b.num);
}

bool BigInteger::operator>(const BigInteger b) const
{
    if (this->num[0] == '+' && b.num[0] == '-')
        return true;
    else if (this->num[0] == '-' && b.num[0] == '+')
        return false;
    else if (this->num[0] == '+' && b.num[0] == '+')
    {
        if (this->num.length() > b.num.length())
            return true;
        else if (this->num.length() < b.num.length())
            return false;
        else
        {
            for (int i = 1; i <= this->num.length(); ++i)
            {
                if (this->num[i] > b.num[i])
                    return true;
                else if (this->num[i] < b.num[i])
                    return false;
            }
        }
    }
    else
    {
        if (this->num.length() < b.num.length())
            return true;
        else if (this->num.length() > b.num.length())
            return false;
        else
        {
            for (int i = 1; i <= this->num.length(); ++i)
            {
                if (this->num[i] < b.num[i])
                    return true;
                else if (this->num[i] > b.num[i])
                    return false;
            }
        }
    }
    return false;
}

bool BigInteger::operator>=(const BigInteger b) const
{
    return (*this > b || *this == b);
}

bool BigInteger::operator<(const BigInteger b) const
{
    return !(*this >= b);
}

bool BigInteger::operator<=(const BigInteger b) const
{
    return !(*this > b);
}

bool BigInteger::operator!=(const BigInteger b) const
{
    return !(this->num == b.num);
}

BigInteger BigInteger::operator+(BigInteger b) const
{
    short c = 0;
    BigInteger a = *this;
    BigInteger r;
    if (this->num[0] == b.num[0])
    {
        r.num.erase(1);
        int c = 0;
        bool aIsLonger = a.num.length() >= b.num.length();
        if (aIsLonger)
            b.fixPosition(a.num.length() - 1);
        else
            a.fixPosition(b.num.length() - 1);
        for (int i = a.num.length() - 1; i >= 1; --i)
        {
            int oneBitSum = a.num[i] + b.num[i] - 96 + c;
            r.num.insert(1, std::to_string(oneBitSum % 10));
            c = oneBitSum / 10;
        }
        r.insertNum(c);
    }
    else
    {
        BigInteger t;
        if (a.absb() > b.absb())
            r.num[0] = a.num[0];
        else if (a.absb() < b.absb())
        {
            r.num[0] = b.num[0];
            t = b;
            b = a;
            a = t;
        }
        else
        {
            r.num = "+0";
            return r;
        }
        a = a.absb();
        b = b.absb();
        b.fixPosition(a.num.length() - 1);
        r.num.erase(1);
        for (int i = a.num.length() - 1; i >= 1; --i)
        {
            if (a.num[i] < b.num[i])
            {
                for (int j = i - 1; j >= 1; --j)
                {
                    if (a.num[j] == '0')
                        a.num[j] = '9';
                    else
                    {
                        a.num[j] -= 1;
                        break;
                    }
                }
                r.num.insert(1, std::to_string(a.num[i] - b.num[i] + 10));
            }
            else
                r.num.insert(1, std::to_string(a.num[i] - b.num[i]));
        }
        r.regulize();
    }
    return r;
}

BigInteger BigInteger::operator-(BigInteger b) const
{
    if (b.num[0] == '+')
        b.num[0] = '-';
    else
        b.num[0] = '+';
    return (*this + b);
}

BigInteger BigInteger::operator-() const
{
    return 0 - *this;
}

BigInteger BigInteger::operator*(BigInteger b) const
{
    BigInteger r;
    BigInteger itSelf = *this;
    BigInteger row;
    itSelf = itSelf.absb();
    b = b.absb();
    int l = b.num.length();
    for (int i = l - 1; i >= 1; --i)
    {
        row = itSelf.mulLowP(b.num[i] - 48);
        for (int j = 1; j < l - i; ++j)
            row.num.append("0");
        r = r + row;
    }
    if (this->num[0] != b.num[0])
        r.num[0] = '-';
    return r;
}

BigInteger BigInteger::operator/(BigInteger b) const
{
    if (b.absb() > this->absb())
        return BigInteger(0);
    BigInteger r;
    BigInteger itSelf = *this;
    if (itSelf.num[0] == b.num[0])
        r.num[0] = '+';
    else
        r.num[0] = '-';
    itSelf = itSelf.absb();
    b = b.absb();
    r.num.erase(1);
    BigInteger subNum;
    int modDigits = 0;
divCourse:
    if (itSelf < b)
    {
        int numOfZerosEnd = itSelf.num.length() - modDigits;
        for (int i = 1; i <= numOfZerosEnd; ++i)
            r.num.append("0");
        goto finish;
    }
    for (int i = 1; i <= itSelf.num.length() - 1; ++i)
    {
        subNum = itSelf.num.substr(1, i);
        if (subNum < b)
            continue;
        int testDiv = 0;
        for (testDiv = 1; testDiv <= 10; ++testDiv)
            if (b * testDiv > subNum)
                break;
        --testDiv;
        r.num.append(std::to_string(testDiv));
        itSelf.num.erase(1, i);
        itSelf.num.insert(1, (subNum - b * testDiv).num);
        itSelf.num.erase(0, 1);
        modDigits = (subNum - b * testDiv).num.length();
        goto divCourse;
    }
finish:
    return r;
}

BigInteger BigInteger::absb() const
{
    BigInteger x = *this;
    if (x.num[0] == '-')
        x.num[0] = '+';
    return x;
}

void BigInteger::regulize()
{
    if (num[0] != '+' && num[0] != '-')
        num.insert(0, "+");
    int numOfZeros = 0;
    for (int i = 1; num[i] == 48; ++i)
        ++numOfZeros;
    if (numOfZeros)
    {
        num.erase(1, numOfZeros - 1);
        if (num[1] == '0' && num.length() == 2)
        {
            if (num[0] == '-')
                num[0] == '+';
        }
        else
            num.erase(1, 1);
    }
}

void BigInteger::insertNum(int n)
{
    num.insert(1, std::to_string(n));
    regulize();
}

std::string BigInteger::getNum()
{
    return num;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &i)
{
    os << i.num;
    return os;
}

bool operator==(long long a, const BigInteger &b)
{
    return (b == a);
}

bool operator>(long long a, const BigInteger &b)
{
    return (b < a);
}

bool operator>=(long long a, const BigInteger &b)
{
    return (b <= a);
}

bool operator<(long long a, const BigInteger &b)
{
    return (b > a);
}

bool operator<=(long long a, const BigInteger &b)
{
    return (b >= a);
}

bool operator!=(long long a, const BigInteger &b)
{
    return (b != a);
}

BigInteger operator+(long long a, const BigInteger &b)
{
    return b + a;
}

BigInteger operator-(long long a, const BigInteger &b)
{
    return BigInteger(a) - b;
}

BigInteger operator*(long long a, const BigInteger &b)
{
    return b * a;
}

BigInteger operator/(long long a, const BigInteger &b)
{
    return BigInteger(a) / b;
}
