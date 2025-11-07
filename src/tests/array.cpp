#include "../include/array.h"
#include <gtest/gtest.h>
#include "../include/octagon.h"
#include "../include/triangle.h"
#include "../include/square.h"

template <Scalar T>
shared_ptr<Octagon<T>> makeOctagon() {
    return make_shared<Octagon<T>>(Point<T>(0, 0), Point<T>(1, 0), Point<T>(2, 1), Point<T>(3, 2),
                                   Point<T>(2, 3), Point<T>(1, 4), Point<T>(0, 4), Point<T>(-1, 3));
}
template <Scalar T>
shared_ptr<Square<T>> makeSquare() {
    return make_shared<Square<T>>(Point<T>(0, 0), Point<T>(2, 0), Point<T>(2, 2), Point<T>(0, 2));
}
template <Scalar T>
shared_ptr<Triangle<T>> makeTriangle() {
    return make_shared<Triangle<T>>(Point<T>(0, 0), Point<T>(2, 0), Point<T>(1, 2));
}

TEST(ArrayTest, AddAndGetFigures) {
    Array<int> array;
    auto octagon = makeOctagon<int>();
    auto square = makeSquare<int>();
    auto triangle = makeTriangle<int>();
    
    array.addFigure(octagon);
    array.addFigure(square);
    array.addFigure(triangle);
    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getFigure(0), octagon);
    EXPECT_EQ(array.getFigure(1), square);
    EXPECT_EQ(array.getFigure(2), triangle);
    EXPECT_EQ(array[0], octagon);
    EXPECT_EQ(array[1], square);
    EXPECT_EQ(array[2], triangle);
}

TEST(ArrayTest, TotalArea) {
    Array<int> array;
    auto octagon = makeOctagon<int>();
    auto square = makeSquare<int>();
    auto triangle = makeTriangle<int>();
    array.addFigure(octagon);
    array.addFigure(square);
    array.addFigure(triangle);
    double expected_area = static_cast<double>(*octagon) + static_cast<double>(*square) +
                           static_cast<double>(*triangle);
    EXPECT_DOUBLE_EQ(array.getAllArea(), expected_area);
}

TEST(ArrayTest, RemoveFigure) {
    Array<int> array;
    auto octagon = makeOctagon<int>();
    auto square = makeSquare<int>();
    auto triangle = makeTriangle<int>();

    array.addFigure(octagon);
    array.addFigure(square);
    array.addFigure(triangle);

    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getFigure(0), octagon);
    EXPECT_EQ(array.getFigure(1), triangle);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array.getFigure(0), triangle);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, CopyArray) {
    Array<int> array1;
    auto square = makeSquare<int>();
    array1.addFigure(square);
    Array<int> array2 = array1;
    EXPECT_EQ(array2.getSize(), array1.getSize());
    EXPECT_NE(array2.getFigure(0), array1.getFigure(0));
    EXPECT_EQ(static_cast<double>(*array2.getFigure(0)), static_cast<double>(*array1.getFigure(0)));
}

TEST(ArrayTest, MoveArray) {
    Array<int> array1;
    auto square = makeSquare<int>();
    array1.addFigure(square);
    Array<int> array2 = std::move(array1);
    EXPECT_EQ(array2.getSize(), 1);
    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, ResizeArray) {
    Array<int> array(2);
    auto octagon = makeOctagon<int>();
    auto square = makeSquare<int>();
    auto triangle = makeTriangle<int>();
    array.addFigure(octagon);
    array.addFigure(square);
    EXPECT_EQ(array.getCapacity(), 2);
    array.addFigure(triangle);
    EXPECT_GE(array.getCapacity(), 3);
    EXPECT_EQ(array.getSize(), 3);
}

TEST(ArrayTest, IndexOutOfBounds) {
    Array<int> array;
    auto square = makeSquare<int>();
    array.addFigure(square);
    EXPECT_EQ(array.getFigure(10), nullptr);
    EXPECT_EQ(array[10], nullptr);
}

TEST(ArrayTest, PrintFigures) {
    Array<int> array;
    auto square = makeSquare<int>();
    array.addFigure(square);
    EXPECT_NO_THROW(array.printFigures());
}
