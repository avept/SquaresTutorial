#include "square.h"
#include <stdexcept>

Square::Square(const cv::Point& topLeft, int length) :
    m_rect(topLeft, cv::Size(length, length))
{
    if (length <= 0)
    {
        throw std::invalid_argument("Square length must be greater than zero.");
    }
}

bool Square::contains(const cv::Point& p) const 
{
    return m_rect.contains(p);
}

bool Square::isDiagonalIntersecting(const cv::Point& p1, const cv::Point& p2) const 
{
    return (contains(p1) && !contains(p2)) || (contains(p2) && !contains(p1));
}

std::pair<cv::Point, cv::Point> Square::getDiagonalPoints() const 
{
    return {cv::Point(m_rect.x + m_rect.width, m_rect.y + m_rect.height), // Bottom-right
            cv::Point(m_rect.x, m_rect.y + m_rect.height)};               // Bottom-left
}

bool FigureOperations::intersect(const Square& sq1, const Square& sq2)
{
    return (sq1.getRect() & sq2.getRect()).area() > 0;
}
