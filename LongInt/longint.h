#ifndef LONGINT_H
#define LONGINT_H

#include <vector>
#include <string>
#include <iostream>

struct LongInt {

private:
    std::vector<int> digits;
    int sign;    

public:
    LongInt();
    LongInt(std::string s);

    std::string toString() const;

    LongInt operator +(LongInt const& x) const;
    LongInt operator -(LongInt const& x) const;
    LongInt operator *(LongInt const& x) const;
    LongInt operator /(LongInt const& x) const;

    LongInt& operator +=(LongInt const& x);
    LongInt& operator -=(LongInt const& x);
    LongInt& operator *=(LongInt const& x);
    LongInt& operator /=(LongInt const& x);

private:
    LongInt(size_t);

    static LongInt plusHelper(LongInt const* a, LongInt const* b);
    static LongInt minusHelper(LongInt const* a, LongInt const* b);
    static LongInt timesHelper(LongInt const* a, LongInt const* b);
    static LongInt divHelper(LongInt const* a, LongInt const* b);


    static int compareAsModules(const LongInt *a, const LongInt *b);
};

#endif // LONGINT_H
