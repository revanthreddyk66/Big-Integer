// Big Integer Library C++ 

#include <iostream>
#include <string>
#include <algorithm>

class BigInteger {
private:
    std::string value;

public:
    BigInteger(const std::string& num) : value(num) {}

    BigInteger operator+(const BigInteger& other) const {
        std::string result;
        int carry = 0;
        int i = value.size() - 1;
        int j = other.value.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += value[i] - '0';
            if (j >= 0) sum += other.value[j] - '0';

            result += std::to_string(sum % 10);
            carry = sum / 10;

            if (i >= 0) i--;
            if (j >= 0) j--;
        }

        std::reverse(result.begin(), result.end());
        return BigInteger(result);
    }

    BigInteger operator-(const BigInteger& other) const {
        std::string result;
        int borrow = 0;
        int i = value.size() - 1;
        int j = other.value.size() - 1;

        while (i >= 0 || j >= 0) {
            int sub = borrow;
            if (i >= 0) sub += value[i] - '0';
            if (j >= 0) sub -= other.value[j] - '0';

            if (sub < 0) {
                sub += 10;
                borrow = -1;
            } else {
                borrow = 0;
            }

            result += std::to_string(sub);
            i--;
            j--;
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == '0')
            result.pop_back();

        std::reverse(result.begin(), result.end());
        return BigInteger(result);
    }

    BigInteger operator*(const BigInteger& other) const {
        std::string result(value.size() + other.value.size(), '0');

        for (int i = value.size() - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = other.value.size() - 1; j >= 0; j--) {
                int product = (value[i] - '0') * (other.value[j] - '0') + (result[i + j + 1] - '0') + carry;
                carry = product / 10;
                result[i + j + 1] = '0' + (product % 10);
            }
            result[i] = '0' + carry;
        }

        // Remove leading zeros
        while (result.size() > 1 && result.front() == '0')
            result.erase(result.begin());

        return BigInteger(result);
    }

    BigInteger operator/(const BigInteger& other) const {
        // Implementation of division
        // ...
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
        os << num.value;
        return os;
    }
};

int main() {
    BigInteger num1("12345678901234567890");
    BigInteger num2("98765432109876543210");

    BigInteger sum = num1 + num2;
    std::cout << "Sum: " << sum << std::endl;

    // Similar implementations for subtraction, multiplication, and division

    return 0;
}
