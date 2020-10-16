
/* Big Integer Class
*/

#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

#include <string>
#include <iostream>

#define LLONG_MAX_DIGITS 19
#define LLONG_MAX_R 1000000000000000000

class BigInteger
{
private:
    std::string num;

    void fixPosition(int p);               //Won't check if p is valid!
    BigInteger mulLowP(long long t) const; // Low performance mul.
public:
    BigInteger();
    BigInteger(long long initNum);
    BigInteger(std::string initNum);

    bool operator==(const BigInteger &b) const;
    bool operator>(const BigInteger b) const;
    bool operator>=(const BigInteger b) const;
    bool operator<(const BigInteger b) const;
    bool operator<=(const BigInteger b) const;
    bool operator!=(const BigInteger b) const;

    BigInteger operator+(const BigInteger b) const;
    BigInteger operator-(BigInteger b) const;
    BigInteger operator-() const;
    BigInteger operator*(BigInteger b) const;
    BigInteger operator/(BigInteger b) const;

    BigInteger absb() const;

    void regulize();
    void insertNum(int n);
    std::string getNum();

    friend std::ostream &operator<<(std::ostream &os, const BigInteger &i);
    friend bool operator==(long long a, const BigInteger &b);
    friend bool operator>(long long a, const BigInteger &b);
    friend bool operator>=(long long a, const BigInteger &b);
    friend bool operator<(long long a, const BigInteger &b);
    friend bool operator<=(long long a, const BigInteger &b);
    friend bool operator!=(long long a, const BigInteger &b);

    friend BigInteger operator+(long long a, const BigInteger &b);
    friend BigInteger operator-(long long a, const BigInteger &b);
    friend BigInteger operator*(long long a, const BigInteger &b);
    friend BigInteger operator/(long long a, const BigInteger &b);
};

#endif