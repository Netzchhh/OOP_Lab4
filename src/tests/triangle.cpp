#include "../include/triangle.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(TriangleTest, DefaultConstructor) {
    Triangle<int> triangle;
    EXPECT_EQ(triangle.getSize(), 0);
}

TEST(TriangleTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{1, 2};
    Triangle<int> triangle(point1, point2, point3);

    EXPECT_EQ(triangle.getSize(), 3);

    const Point<int>* points = triangle.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
}

TEST(TriangleTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{2, 0}, point3{1, 2};
    Triangle<int> triangle1(point1, point2, point3);
    Triangle<int> triangle2(triangle1);

    EXPECT_EQ(triangle1.getSize(), triangle2.getSize());
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, GetCenter) {
    Triangle<double> triangle(Point<double>(0, 0), Point<double>(2, 0), Point<double>(1, 2));
    Point<double> center = triangle.getCenter();

    EXPECT_DOUBLE_EQ(center.x, (0 + 2 + 1) / 3.0);
    EXPECT_DOUBLE_EQ(center.y, (0 + 0 + 2) / 3.0);
}

TEST(TriangleTest, GetArea) {
    Triangle<int> triangle(Point<int>(0, 0), Point<int>(2, 0), Point<int>(1, 2));

    double area = triangle.getArea();
    EXPECT_NEAR(area, 2.0, 1e-6);
}

TEST(TriangleTest, Print) {
    Triangle<int> triangle(Point<int>(0, 0), Point<int>(1, 0), Point<int>(0, 1));
    ostringstream os;

    triangle.print(os);
    string output = os.str();

    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(TriangleTest, Read) {
    Triangle<int> triangle;

    istringstream is("0 0 2 0 1 2");
    triangle.read(is);

    Point<int> point1{0, 0}, point2{2, 0}, point3{1, 2};
    const Point<int>* points = triangle.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
}

TEST(TriangleTest, OperatorEquals) {
    Triangle<int> triangle1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(1, 2));
    Triangle<int> triangle2(triangle1);
    Triangle<int> triangle3(Point<int>(1, 1), Point<int>(3, 1), Point<int>(2, 3));

    EXPECT_TRUE(triangle1 == triangle2);
    EXPECT_FALSE(triangle1 == triangle3);
}

TEST(TriangleTest, Clone) {
    Triangle<int> triangle1(Point<int>(0, 0), Point<int>(2, 0), Point<int>(1, 2));

    auto triangle2 = triangle1.clone();
    EXPECT_TRUE(dynamic_cast<Triangle<int>*>(triangle2.get()) != nullptr);
    EXPECT_TRUE(triangle1 == *triangle2);
}
