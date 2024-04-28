#pragma once

#include <limits>

namespace td
{
inline bool LessThan(double left, double right)
{
    return left < (right - std::numeric_limits<double>::epsilon());
}

inline bool LessThanOrEqualTo(double left, double right)
{
    return !LessThan(right, left);
}

inline bool GreaterThan(double left, double right)
{
    return LessThan(right, left);
}

inline bool GreaterThanOrEqualTo(double left, double right)
{
    return !LessThan(left, right);
}

inline bool EqualTo(double left, double right)
{
    return !LessThan(left, right) && !LessThan(right, left);
}

inline bool NotEqualTo(double left, double right)
{
    return LessThan(left, right) || LessThan(right, left);
}

inline bool IsZero(double value)
{
    return EqualTo(value, 0);
}

inline bool IsPositive(double value)
{
    return GreaterThan(value, 0);
}

inline bool IsNegative(double value)
{
    return LessThan(value, 0);
}
}
