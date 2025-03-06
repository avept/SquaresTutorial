#pragma once

#include <opencv2/core.hpp>

class Square 
{
public:
    Square(const cv::Point& topLeft, int length);

    bool contains(const cv::Point& p) const;
    bool isDiagonalIntersecting(const cv::Point& p1, const cv::Point& p2) const;

    std::pair<cv::Point, cv::Point> getDiagonalPoints() const;

    const cv::Rect& getRect() const { return m_rect; }

private:
    cv::Rect m_rect; // Rectangle representing the square
};

namespace FigureOperations
{
    bool intersect(const Square& sq1, const Square& sq2);
}
