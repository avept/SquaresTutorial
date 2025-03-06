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
    // Previous version
    
    // auto [sq1_diag1, sq1_diag2] = sq1.getDiagonalPoints();
    // auto [sq2_diag1, sq2_diag2] = sq2.getDiagonalPoints();

    // // Direct containment check (identical squares)
    // if ((sq1.getRect() == sq2.getRect()))
    //     return true;

    // return sq1.isDiagonalIntersecting(sq2.getRect().tl(), sq2_diag1) ||
    //        sq1.isDiagonalIntersecting(sq2_diag2, {sq2_diag1.x, sq2.getRect().y}) ||
    //        sq2.isDiagonalIntersecting(sq1.getRect().tl(), sq1_diag1) ||
    //        sq2.isDiagonalIntersecting(sq1_diag2, {sq1_diag1.x, sq1.getRect().y});

    // if((((sq1.getRect() & sq2.getRect()) == sq1.getRect()) || ((sq1.getRect() & sq2.getRect()) == sq2.getRect())) && sq1.getRect() != sq2.getRect())
    // {
    //     return false;
    // }

    return (sq1.getRect() & sq2.getRect()).area() > 0;
}
