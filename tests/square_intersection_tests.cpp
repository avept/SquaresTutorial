#include <gtest/gtest.h>
#include "../src/square.h"

// 1.1 Test: Squares Overlapping ( Bottom right )
TEST(SquareIntersectionTest, OverlappingSquaresBR) {
    Square sq1({1, 1}, 4);
    Square sq2({2, 2}, 4);
    EXPECT_TRUE(FigureOperations::intersect(sq1, sq2)); // Expect intersection
}

// 1.2 Test: Squares Overlapping ( Bottom left )
TEST(SquareIntersectionTest, OverlappingSquaresBL) {
    Square sq1({1, 1}, 4);
    Square sq2({0, 2}, 4);
    EXPECT_TRUE(FigureOperations::intersect(sq1, sq2)); // Expect intersection
}

// 2.1 Test: Touching at a Corner ( Bottom right )
TEST(SquareIntersectionTest, TouchingAtCornerBR) {
    Square sq1({1, 1}, 3);
    Square sq2({4, 4}, 3);
    EXPECT_FALSE(FigureOperations::intersect(sq1, sq2)); // Just touching, no real intersection
}

// 2.2 Test: Touching at a Corner ( Bottom left )
TEST(SquareIntersectionTest, TouchingAtCornerBL) {
    Square sq1({1, 1}, 3);
    Square sq2({-2, 4}, 3);
    EXPECT_FALSE(FigureOperations::intersect(sq1, sq2)); // Just touching, no real intersection
}

// 3.1 Test: Touching along an Edge
TEST(SquareIntersectionTest, TouchingAlongEdgeRS) {
    Square sq1({1, 1}, 3);
    Square sq2({4, 1}, 3);
    EXPECT_FALSE(FigureOperations::intersect(sq1, sq2)); // Sharing an edge but no intersection
}

// 3.2 Test: Touching along an Edge
TEST(SquareIntersectionTest, TouchingAlongEdgeBS) {
    Square sq1({1, 1}, 3);
    Square sq2({1, 4}, 3);
    EXPECT_FALSE(FigureOperations::intersect(sq1, sq2)); // Sharing an edge but no intersection
}

// 4.1 Test: Identical Squares (Fully Overlapping)
TEST(SquareIntersectionTest, IdenticalSquares) {
    Square sq1({2, 2}, 4);
    Square sq2({2, 2}, 4);
    EXPECT_TRUE(FigureOperations::intersect(sq1, sq2)); // Exact same position & size
}

// 5.1 Test: Completely Contained
TEST(SquareIntersectionTest, OneInsideAnother) {
    Square outer({0, 0}, 10);
    Square inner({2, 2}, 4);
    EXPECT_FALSE(FigureOperations::intersect(outer, inner)); // Inner square is fully inside outer
}

// 6.1 Test: No Intersection (Square surrounding positions)
TEST(SquareIntersectionTest, NoIntersectionAround) {
    Square center({5, 5}, 3); 

    std::vector<Square> surroundingSquares = {
        Square({1, 5}, 3),  // LEFT
        Square({9, 5}, 3),  // RIGHT
        Square({5, 1}, 3),  // TOP
        Square({5, 9}, 3),  // BOTTOM
        Square({1, 1}, 3),  // TOP-LEFT
        Square({9, 1}, 3),  // TOP-RIGHT
        Square({1, 9}, 3),  // BOTTOM-LEFT
        Square({9, 9}, 3)   // BOTTOM-RIGHT
    };

    for (const auto& sq : surroundingSquares) {
        EXPECT_FALSE(FigureOperations::intersect(center, sq));
    }
}

// 7.1 Test: Zero-Length Square
TEST(SquareIntersectionTest, ZeroLengthSquare) {
    EXPECT_THROW(Square({1, 1}, 0), std::invalid_argument);
}

// 8.1 Test: Negative Side Length (Edge Case Handling)
TEST(SquareIntersectionTest, NegativeSideLength) {
    EXPECT_THROW(Square({1, 1}, -3), std::invalid_argument);
}

// 9.1 Test: Large Squares (Performance Test)
TEST(SquareIntersectionTest, LargeSquares) {
    Square sq1({1, 1}, 1'000'000);
    Square sq2({500'000, 500'000}, 1'000'000);
    EXPECT_TRUE(FigureOperations::intersect(sq1, sq2)); // Should intersect in a large coordinate space
}

// 10.1 Test: Floating Point Precision Handling (If Using Floats)
TEST(SquareIntersectionTest, PrecisionTest) {
    Square sq1({1000001, 1000001}, 3);
    Square sq2({1000003, 1000003}, 3);
    EXPECT_TRUE(FigureOperations::intersect(sq1, sq2)); // Should still intersect despite large values
}

// 11.1 Test: Advanced overlapping
TEST(SquareIntersectionTest, AdvancedOverlapping) {
    Square mainSquare({5, 5}, 5);

    Square sq1({5, 5}, 3);
    Square sq2({7, 7}, 3);
    Square sq3({7, 3}, 3);

    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq1));
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq2)); 
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq3));
}

// 12.1 Test: Two points of intersection at corner
TEST(SquareIntersectionTest, TwoIntersectionPointsAtCorner) {
    Square mainSquare({5, 5}, 5);

    Square sq1({4, 4}, 3);
    Square sq2({8, 4}, 3);
    Square sq3({8, 8}, 3);
    Square sq4({7, 8}, 3);

    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq1));
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq2)); 
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq3)); 
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq4)); 
}

// 13.1 Test: Two points of intersection at side
TEST(SquareIntersectionTest, TwoIntersectionPointsAtSide) {
    Square mainSquare({5, 5}, 5);

    Square sq1({5, 7}, 2);
    Square sq2({6, 4}, 2);
    Square sq3({9, 7}, 2);
    Square sq4({6, 9}, 2);

    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq1));
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq2)); 
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq3)); 
    EXPECT_TRUE(FigureOperations::intersect(mainSquare, sq4)); 
}