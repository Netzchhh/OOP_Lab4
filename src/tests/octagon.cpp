#include "../include/octagon.h"
#include <gtest/gtest.h>
#include <sstream>
TEST(OctagonTest, DefaultConstructor) {
    Octagon<int> octagon;
    EXPECT_EQ(octagon.getSize(), 0);
}

TEST(OctagonTest, ParameterConstructor) {
    Point<int> point1{0, 0}, point2{1, 0}, point3{2, 1}, point4{3, 2}, point5{2, 3}, point6{1, 4}, point7{0, 4}, point8{-1, 3};
    Octagon<int> octagon(point1, point2, point3, point4, point5, point6, point7, point8);
    EXPECT_EQ(octagon.getSize(), 8); 
    const Point<int>* points = octagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
    EXPECT_EQ(points[5], point6);
    EXPECT_EQ(points[6], point7);
    EXPECT_EQ(points[7], point8);
}

TEST(OctagonTest, CopyConstructor) {
    Point<int> point1{0, 0}, point2{1, 0}, point3{2, 1}, point4{3, 2}, point5{2, 3}, point6{1, 4}, point7{0, 4}, point8{-1, 3};
    Octagon<int> octagon1(point1, point2, point3, point4, point5, point6, point7, point8);
    Octagon<int> octagon2(octagon1);

    EXPECT_EQ(octagon1.getSize(), octagon2.getSize());
    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonTest, GetCenter) {
    Octagon<double> octagon(Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1),
                            Point<double>(3, 2), Point<double>(2, 3), Point<double>(1, 4),
                            Point<double>(0, 4), Point<double>(-1, 3));
    Point<double> center = octagon.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 2.125);
}

TEST(OctagonTest, GetArea) {
    Octagon<int> octagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(3, 2),
                         Point<int>(2, 3), Point<int>(1, 4), Point<int>(0, 4), Point<int>(-1, 3));

    double area = octagon.getArea();
    EXPECT_NEAR(area, 10.0, 1e-6);
}

TEST(OctagonTest, Print) {
    Octagon<int> octagon(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(1, 2),
                         Point<int>(0, 2), Point<int>(-1, 2), Point<int>(-1, 1), Point<int>(0, 1));
    ostringstream os;

    octagon.print(os);
    string output = os.str();

    EXPECT_NE(output.find("Area"), string::npos);
    EXPECT_NE(output.find("(0,0)"), string::npos);
}

TEST(OctagonTest, Read) {
    Octagon<int> octagon;

    istringstream is("0 0 1 0 2 1 3 2 2 3 1 4 0 4 -1 3");
    octagon.read(is);

    Point<int> point1{0, 0}, point2{1, 0}, point3{2, 1}, point4{3, 2}, point5{2, 3}, point6{1, 4}, point7{0, 4}, point8{-1, 3};
    const Point<int>* points = octagon.getPoints();
    EXPECT_EQ(points[0], point1);
    EXPECT_EQ(points[1], point2);
    EXPECT_EQ(points[2], point3);
    EXPECT_EQ(points[3], point4);
    EXPECT_EQ(points[4], point5);
    EXPECT_EQ(points[5], point6);
    EXPECT_EQ(points[6], point7);
    EXPECT_EQ(points[7], point8);
}

TEST(OctagonTest, OperatorEquals) {
    Octagon<int> octagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(3, 2),
                          Point<int>(2, 3), Point<int>(1, 4), Point<int>(0, 4), Point<int>(-1, 3));
    Octagon<int> octagon2(octagon1);
    Octagon<int> octagon3(Point<int>(1, 1), Point<int>(2, 1), Point<int>(3, 2), Point<int>(4, 3),
                          Point<int>(3, 4), Point<int>(2, 5), Point<int>(1, 5), Point<int>(0, 4));

    EXPECT_TRUE(octagon1 == octagon2);
    EXPECT_FALSE(octagon1 == octagon3);
}

TEST(OctagonTest, Clone) {
    Octagon<int> octagon1(Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 1), Point<int>(3, 2),
                          Point<int>(2, 3), Point<int>(1, 4), Point<int>(0, 4), Point<int>(-1, 3));

    auto octagon2 = octagon1.clone();
    EXPECT_TRUE(dynamic_cast<Octagon<int>*>(octagon2.get()) != nullptr);
    EXPECT_TRUE(octagon1 == *octagon2);
}
