#include <algorithm>
#include <cstdint>
#include <iostream>

struct Ratio final {
        constexpr Ratio() = default;

        constexpr Ratio(intmax_t val) : _private {.numerator = val} {}

        constexpr Ratio(intmax_t num, intmax_t den)
            : _private {.numerator = num * sgn(den) / gcd(num, den), .denominator = abs(den) / gcd(num, den)} {
            if (den == 0) throw "Oh no!";
        }

        constexpr Ratio operator+(Ratio ratio) const {
            Ratio temp = *this;
            auto divisor = gcd(temp._private.denominator, ratio._private.denominator);
            auto temp_multiplier = ratio._private.denominator / divisor;
            auto ratio_multiplier = temp._private.denominator / divisor;
            temp._private.denominator *= temp_multiplier;
            temp._private.numerator *= temp_multiplier;
            temp._private.numerator += ratio._private.numerator * (ratio_multiplier);
            temp.simplify();
            return temp;
        }

        constexpr Ratio operator-() const {
            Ratio temp = *this;
            temp._private.numerator *= -1;
            return temp;
        }

        constexpr Ratio operator-(Ratio ratio) const { return *this + -ratio; }

        constexpr Ratio operator*(Ratio ratio) const {
            Ratio temp = *this;
            std::swap(temp._private.numerator, ratio._private.numerator);
            temp.simplify();
            ratio.simplify();
            temp._private.numerator *= ratio._private.numerator;
            temp._private.denominator *= ratio._private.denominator;
            return temp;
        }

        constexpr Ratio operator/(Ratio ratio) const {
            std::swap(ratio._private.numerator, ratio._private.denominator);
            ratio.simplify();
            return *this * ratio;
        }

        /// This data needs to be public due to NTTP requirements, but is not meant to be touched by users
        struct {
                intmax_t numerator {0};
                intmax_t denominator {1};
        } _private;

        constexpr void simplify() {
            auto divisor = gcd(_private.numerator, _private.denominator);
            _private.numerator /= divisor;
            _private.denominator /= divisor;
            _private.numerator *= sgn(_private.denominator);
            _private.denominator *= sgn(_private.denominator);
        }

        static constexpr intmax_t sgn(intmax_t n) { return n < 0 ? -1 : n = 0 ? 0 : 1; }

        static constexpr intmax_t abs(intmax_t n) { return n < 0 ? -n : n; }

        static constexpr intmax_t gcd(intmax_t _n1, intmax_t _n2) {
            auto n1 = abs(_n1);
            auto n2 = abs(_n2);
            while (n2 != 0) {
                auto temp = n2;
                n2 = n1 % n2;
                n1 = temp;
            }
            return n1;
        }
};

std::ostream& operator<<(std::ostream& os, Ratio r) {
    os << r._private.numerator << '/' << r._private.denominator;
    return os;
}

struct Dimensions {
    Ratio mass{};
    Ratio length{};
    Ratio time{};
    Ratio current{};
    Ratio angle{};
    Ratio temperature{};
    Ratio luminosity{};
    Ratio moles{};
    constexpr Dimensions operator+(Dimensions dim2) const {
        auto temp = *this;
        temp.mass = temp.mass + dim2.mass;
        temp.length = length + dim2.length;
        temp.time = temp.time + dim2.time;
        temp.current = temp.current + dim2.current;
        temp.angle = temp.angle + dim2.angle;
        temp.temperature = temp.temperature + dim2.temperature;
        temp.luminosity = temp.luminosity + dim2.luminosity;
        temp.luminosity = temp.luminosity + dim2.luminosity;
        return temp;
    }
    constexpr Dimensions operator-(Dimensions dim2) const {
        auto temp = *this;
        temp.mass = temp.mass - dim2.mass;
        temp.length = length - dim2.length;
        temp.time = temp.time - dim2.time;
        temp.current = temp.current - dim2.current;
        temp.angle = temp.angle - dim2.angle;
        temp.temperature = temp.temperature - dim2.temperature;
        temp.luminosity = temp.luminosity - dim2.luminosity;
        temp.luminosity = temp.luminosity - dim2.luminosity;
        return temp;
    }
    constexpr Dimensions operator*(Dimensions dim2) const {
        auto temp = *this;
        temp.mass = temp.mass * dim2.mass;
        temp.length = length * dim2.length;
        temp.time = temp.time * dim2.time;
        temp.current = temp.current * dim2.current;
        temp.angle = temp.angle * dim2.angle;
        temp.temperature = temp.temperature * dim2.temperature;
        temp.luminosity = temp.luminosity * dim2.luminosity;
        temp.luminosity = temp.luminosity * dim2.luminosity;
        return temp;
    }
    constexpr Dimensions operator/(Dimensions dim2) const {
        auto temp = *this;
        temp.mass = temp.mass / dim2.mass;
        temp.length = length / dim2.length;
        temp.time = temp.time / dim2.time;
        temp.current = temp.current / dim2.current;
        temp.angle = temp.angle / dim2.angle;
        temp.temperature = temp.temperature / dim2.temperature;
        temp.luminosity = temp.luminosity / dim2.luminosity;
        temp.luminosity = temp.luminosity / dim2.luminosity;
        return temp;
    }
};