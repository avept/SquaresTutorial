#include <iostream>
#include "square.h"

bool intersect(const Square& sq1, const Square& sq2)
{
    // check whether one of the points belongs to the square and the other does not, or vice versa
    // that is, we literally check whether one of the diagonals of the square crosses the side of another square
    auto isDiagonalIntersectSquare = [](const Square& square, const Square::Point p, const Square::Point b) -> bool 
    {
        auto isPointInSquare = [](const Square& square, const Square::Point p)
        {
            return (square.m_point.first < p.first && p.first < square.m_point.first + square.m_length) &&
                   (square.m_point.second < p.second && p.second < square.m_point.second + square.m_length);
        };

        return (isPointInSquare(square, p) && !isPointInSquare(square, b)) || 
               (isPointInSquare(square, b) && !isPointInSquare(square, p));
    };

    return isDiagonalIntersectSquare(sq1, sq2.m_point, {sq2.m_point.first + sq2.m_length, sq2.m_point.second + sq2.m_length})                             ||
           isDiagonalIntersectSquare(sq1, {sq2.m_point.first + sq2.m_length, sq2.m_point.second}, {sq2.m_point.first, sq2.m_point.second + sq2.m_length}) || 
           isDiagonalIntersectSquare(sq2, sq1.m_point, {sq1.m_point.first + sq1.m_length, sq1.m_point.second + sq1.m_length})                             ||
           isDiagonalIntersectSquare(sq2, {sq1.m_point.first + sq1.m_length, sq1.m_point.second}, {sq1.m_point.first, sq1.m_point.second + sq1.m_length});
}

int main()
{
    Square sq1 = {{1,1}, 7};
    Square sq2 = {{3,5}, 7};

    std::cout << intersect(sq1, sq2) << std::endl;
    return 0;
}