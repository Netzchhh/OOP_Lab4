#include "../include/square.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(SquareTest, DefaultConstructor) {
    Square<int> square;
    EXPECT_EQ(square.getSize(), 0);
}

TEST(SquareTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    Square<int> square(point1, point2, point3, point4);
    EXPECT_EQ(square.getSize(), 4);
    const Point<int>* points = square.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
}

TEST(SquareTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    Square<int> square1(point1, point2, point3, point4);
    Square<int> square2(square1);
    EXPECT_EQ(square1.getSize(), square2.getSize());
    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, GetCenter) {
    Square<double> square(Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2),
                          Point<double>(0, 2));
    Point<double> center = square.getCenter();
    EXPECT_DOUBLE_EQ(center.x, (0 + 2 + 2 + 0) / 4.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 2 + 2) / 4.0);
}

TEST(SquareTest, GetArea) {
    Square<int> square(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2),
                       Point<int>(0, 2));
    double area = square.getArea();
    EXPECT_NEAR(area, 4.0, 1e-6);
}

TEST(SquareTest, Print) {
    Square<int> square(Point<int>(0, 0), Point<int>(1, 0), Point<int>(1, 1), Point<int>(0, 1));
    ostringstream os;
    square.print(os);
    string output = os.str();
    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(SquareTest, Read) {
    Square<int> square;
    istringstream is("0 0 2 0 2 2 0 2");
    square.read(is);
    Point<int> point1{0, 0}, point2{2, 0}, point3{2, 2}, point4{0, 2};
    const Point<int>* points = square.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
}

TEST(SquareTest, OperatorEquals) {
    Square<int> square1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2),
                        Point<int>(0, 2));
    Square<int> square2(square1);
    Square<int> square3(Point<int>(1, 1), Point<int>(3, 1), Point<int>(3, 3),
                        Point<int>(1, 3));
    EXPECT_TRUE(square1 == square2);
    EXPECT_FALSE(square1 == square3);
}

TEST(SquareTest, Clone) {
    Square<int> square1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(2, 2),
                        Point<int>(0, 2));
    auto square2 = square1.clone();
    EXPECT_TRUE(dynamic_cast<Square<int>*>(square2.get()) != nullptr);
    EXPECT_TRUE(square1 == *square2);
}
