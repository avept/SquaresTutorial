#pragma once

#include <cstdint>
#include <utility>

class Square 
{
public:
    using Point = std::pair<int64_t, int64_t>;

public:
    Square(const Point& point, const uint64_t length);

    bool contains(const Point& p) const;
    bool isDiagonalIntersecting(const Point& p1, const Point& p2) const;

    std::pair<Point, Point> getDiagonalPoints() const;

public:
    Point m_point; // Top-left point
    uint64_t m_length; // Side length of the square
};

namespace FigureOperations
{
    // Check if two squares intersect
    bool intersect(const Square& sq1, const Square& sq2);
}

