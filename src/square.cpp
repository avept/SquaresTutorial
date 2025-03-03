#include "square.h"
#include <stdexcept>

Square::Square(const Point& point, const uint64_t length) :
    m_point(point),
    m_length(length)
{
    if (static_cast<int64_t>(length) <= 0) 
    {
        throw std::invalid_argument("Square length must be greater than zero.");
    }
}

bool Square::contains(const Point& p) const 
{
    return (m_point.x < p.x && p.x < m_point.x + m_length) &&
           (m_point.y < p.y && p.y < m_point.y + m_length);
}

bool Square::isDiagonalIntersecting(const Point& p1, const Point& p2) const 
{
    return (contains(p1) && !contains(p2)) || (contains(p2) && !contains(p1));
}

std::pair<Square::Point, Square::Point> Square::getDiagonalPoints() const 
{
    return {Square::Point(m_point.x + m_length, m_point.y + m_length),  // Bottom-right
            Square::Point(m_point.x, m_point.y + m_length)};            // Bottom-left
}

///
bool FigureOperations::intersect(const Square& sq1, const Square& sq2)
{
    auto [sq1_diag1, sq1_diag2] = sq1.getDiagonalPoints();
    auto [sq2_diag1, sq2_diag2] = sq2.getDiagonalPoints();

    // Direct containment check (identical squares)
    if ((sq1.m_point.x == sq2.m_point.x) && 
        (sq1.m_point.y == sq2.m_point.y) && 
        (sq1.m_length == sq2.m_length))
        {
            return true;
        }

    return sq1.isDiagonalIntersecting(sq2.m_point, sq2_diag1) ||
           sq1.isDiagonalIntersecting(sq2_diag2, {sq2_diag1.x, sq2.m_point.y}) ||
           sq2.isDiagonalIntersecting(sq1.m_point, sq1_diag1) ||
           sq2.isDiagonalIntersecting(sq1_diag2, {sq1_diag1.x, sq1.m_point.y});
}