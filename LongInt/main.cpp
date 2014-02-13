#include "longint.h"

std::istream& operator >>(std::istream &in, LongInt& a) {
    std::string s;
    in >> s;
    a = LongInt(s);
    return in;
}

std::ostream& operator <<(std::ostream &out, LongInt const& a) {
    out << a.toString();
    return out;
}

int main() {
    LongInt x, y;
    std::cin >> x >> y;

    std::cout << x << " + " << y << " = " << x + y << "\n";
    std::cout << x << " - " << y << " = " << x - y << "\n";
    std::cout << x << " * " << y << " = " << x * y << "\n";
    std::cout << x << " / " << y << " = " << x / y << "\n";

    return 0;
}
