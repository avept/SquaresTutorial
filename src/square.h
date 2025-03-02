#pragma once

#include <cstdint>
#include <utility>

class Square 
{
public:
    using Point = std::pair<uint64_t, uint64_t>;

    Square(const Point& point, const uint64_t length); 

public:
    Point m_point; // top-left point
    uint64_t m_length;
};