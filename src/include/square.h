#pragma once
#include <cmath>
#include <iostream>
#include "figure.h"
template <Scalar T>
class Square : public Figure<T> {
   public:
    Square(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
           const Point<T>& point4) {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);
        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
    }

    Square() = default;
    Square(const Square& other) {
        this->size_ = other.size_;
        this->points_ = std::make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i)
            this->points_[i] = other.points_[i];
    }

    Point<T> getCenter() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < this->size_; ++i) {
            cx += this->points_[i].x;
            cy += this->points_[i].y;
        }
        return Point<T>(cx / this->size_, cy / this->size_);
    }

    double getArea() const override {
        double area = 0.0;
        for (size_t i = 0; i < this->size_; ++i) {
            const Point<T>& p1 = this->points_[i];
            const Point<T>& p2 = this->points_[(i + 1) % this->size_];
            area += (p1.x * p2.y - p2.x * p1.y);
        }

        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        for (size_t i = 0; i < this->size_; ++i)
            os << "(" << this->points_[i].x << "," << this->points_[i].y << ") ";
        os << "Area = " << getArea() << " ";
        os << "Center: (" << getCenter().x << "," << getCenter().y << ")" << std::endl;
    }

    void read(std::istream& is) override {
        this->size_ = 4;
        this->points_ = std::make_unique<Point<T>[]>(4);
        for (size_t i = 0; i < this->size_; ++i)
            is >> this->points_[i].x >> this->points_[i].y;
    }

    bool operator==(const Square<T>& other) const {
        for (size_t i = 0; i < 4; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Square<T>* square = dynamic_cast<const Square<T>*>(&other);
        if (!square)
            return false;
        return *this == *square;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Square<T>>(*this);
    }
};
