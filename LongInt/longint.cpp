#include "longint.h"
#include <iostream>
LongInt::LongInt()
    : digits(1)
{
    sign = 1;
}

LongInt::LongInt(size_t n)
    : digits(n)
{
    sign = 1;
}

LongInt::LongInt(std::string s)
    : digits(s.size())
{
    if (s == "") {
        digits.resize(1);
        digits[0] = 0;
        sign = 1;
    } else {
        if (s[0] == '-') {
            sign = -1;
            s = s.substr(1);
        } else {
            sign = 1;
        }

        size_t size = s.size();
        this->digits.resize(size);

        for (size_t i = 0; i < size; i++) {
            digits[size - 1 - i] = (int) (s[i] - '0'); // char to integer
        }
    }
}

LongInt LongInt::operator +(LongInt const& x) const {
    int k = compareAsModules(this, &x);

    LongInt const* a;
    LongInt const* b;
    LongInt res;

    if (k != 2) {
        a = this;
        b = &x;
    } else {
        a = &x;
        b = this;
    }

    if (a->sign > 0 && b->sign > 0) {
        res = plusHelper(a, b);
    } else if (a->sign > 0 && b->sign < 0) {
        res = minusHelper(a, b);
    } else if (a->sign < 0 && b->sign > 0) {
        res = minusHelper(a, b);
        res.sign = -1;
    } else {
        res = plusHelper(a, b);
        res.sign = -1;
    }

    return res;
}

// supposed that a >= b
LongInt LongInt::plusHelper(LongInt const* a, LongInt const* b) {
    LongInt res(a->digits.size());

    for (size_t i = 0; i < b->digits.size(); i++) {
        res.digits[i] = a->digits[i] + b->digits[i];
        if (res.digits[i] >= 10) {
            if (i != (a->digits.size() - 1)) {
                res.digits[i + 1]++;
            } else {
                res.digits.push_back(1);
            }
            res.digits[i] %= 10;
        }
    }

    for (size_t i = b->digits.size(); i < a->digits.size(); i++) {
        res.digits[i] += a->digits[i];
    }

    return res;
}

LongInt LongInt::operator -(LongInt const& x) const {
    int k = compareAsModules(this, &x);

    LongInt const* a;
    LongInt const* b;
    LongInt res;

    if (k == 0) {
        return res;
    } else if (k == 1) {
        a = this;
        b = &x;
    } else {
        a = &x;
        b = this;
    }

    if (a->sign > 0 && b->sign > 0) {
        res = minusHelper(a, b);
        res.sign = 1;
    } else if (a->sign > 0 && b->sign < 0) {
        res = plusHelper(a, b);
    } else if (a->sign < 0 && b->sign > 0) {
        res = plusHelper(a, b);
        res.sign = -1;
    } else {
        res = minusHelper(a, b);
        res.sign = -1;
    }

    return res;
}

// supposed that a >= b
LongInt LongInt::minusHelper(LongInt const* a, LongInt const* b) {
    LongInt res(a->digits.size());
    int l = 0;
    for (size_t i = 0; i < b->digits.size(); i++) {
        // if (i != a->digits.size() - 1) - supposed that its true cos a > b
        if ((a->digits[i] - l) >= b->digits[i]) {
            res.digits[i] += (a->digits[i] - l) - b->digits[i];
            l = 0;
        } else {
            res.digits[i] = 10 + (a->digits[i] - l) - b->digits[i];
            l = 1;
        }
    }

    for (size_t i = b->digits.size(); i < a->digits.size(); i++) {
        if (l == 1) {
            if (a->digits[i] <= 0) {
                res.digits[i] += 10 + (a->digits[i] - l);
            } else {
                res.digits[i] += a->digits[i] - l;
                l = 0;
            }
        } else {
            res.digits[i] += a->digits[i];
        }
    }

    int length = res.digits.size();
    while (res.digits[length - 1] == 0) {
        res.digits.pop_back();
        length--;
    }

    return res;
}

LongInt LongInt::operator *(LongInt const& x) const {
    int k = compareAsModules(this, &x);

    LongInt const* a;
    LongInt const* b;
    LongInt res;

    if (k != 2) {
        a = this;
        b = &x;
    } else {
        a = &x;
        b = this;
    }

    res = timesHelper(a, b);
    res.sign = a->sign * b->sign;

    return res;
}

LongInt LongInt::timesHelper(LongInt const* a, LongInt const* b) {
    size_t length = a->digits.size() + b->digits.size() + 1;
    LongInt res(length);

    for (size_t i = 0; i < b->digits.size(); i++) {
        for (size_t j = 0; j < a->digits.size(); j++) {
            res.digits[i + j] += a->digits[j] * b->digits[i];
        }
    }

    for (size_t i = 0; i < length - 1; i++) {
        res.digits[i + 1] +=  res.digits[i] / 10;
        res.digits[i] %= 10;
    }

    while (res.digits[length - 1] == 0) {
        res.digits.pop_back();
        length--;
    }

    return res;
}

LongInt LongInt::operator /(LongInt const& x)  const{
    int k = compareAsModules(this, &x);

    LongInt const* a;
    LongInt const* b;
    LongInt res;

    if (k == 2) {
        return res;
    } else {
        a = this;
        b = &x;
    }

    res = divHelper(a, b);
    res.sign = a->sign * b->sign;

    return res;
}


LongInt LongInt::divHelper(LongInt const* a, LongInt const* b) {
    int k;
    LongInt x;
    LongInt res(a->digits.size());
    LongInt tmp(a->digits.size());
    for (int i = a->digits.size() - 1; i >= 0; i--) {
        for (size_t j = 1; j < 10; j++) {
            tmp.digits[i] = j;
            x = tmp * (*b);
            k = compareAsModules(a, &x);
            // a < x + res
            if (k == 2) break;
            res.digits[i] = j;
        }

        tmp.digits[i] = res.digits[i];
    }

    int length = res.digits.size();
    while (res.digits[length - 1] == 0) {
        res.digits.pop_back();
        length--;
    }

    return res;
}


// k = 1 - first larger
// k = 2 - second larger
// k = 0 - numbers are equal

int LongInt::compareAsModules(LongInt const* a, LongInt const* b) {
    int k = 0;
    if (a->digits.size() > b->digits.size()) {
        k = 1;
    } else if (a->digits.size() < b->digits.size()) {
        k = 2;
    } else {
        for (int i = a->digits.size() - 1; i >= 0; i--) {
            if (a->digits[i] > b->digits[i]) {
               k = 1;
               break;
            } else if (a->digits[i] < b->digits[i]){
               k = 2;
               break;
            }
        }
    }
    return k;
}





std::string LongInt::toString() const {
    std::string s;

    if (this->digits.size() == 1 && this->digits[0] == 0) {
        s.push_back('0');
        return s;
    }

    if (sign == -1) {
        s.push_back('-');
    }
    for (size_t i = 0; i < this->digits.size(); i++) {
       s.push_back((this->digits[digits.size() - 1 - i] + '0'));
    }

    return s;
}


LongInt &LongInt::operator +=(LongInt const& x) {
    *this = (*this + x);
    return *this;
}

LongInt& LongInt::operator -=(LongInt const& x) {
    *this = (*this - x);
    return *this;;
}

LongInt& LongInt::operator *=(LongInt const& x) {
    *this = (*this * x);
    return *this;
}

LongInt& LongInt::operator /=(LongInt const& x) {
    *this = (*this / x);
    return *this;
}

