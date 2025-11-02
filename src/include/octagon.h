#pragma once
#include <cmath>
#include <iostream>

#include "figure.h"

template <Scalar T>
class Octagon : public Figure<T> {
   public:
    Octagon(const Point<T>& point1, const Point<T>& point2, const Point<T>& point3,
            const Point<T>& point4, const Point<T>& point5, const Point<T>& point6,
            const Point<T>& point7, const Point<T>& point8) {
        this->size_ = 8;
        this->points_ = std::make_unique<Point<T>[]>(8);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
        this->points_[4] = point5;
        this->points_[5] = point6;
        this->points_[6] = point7;
        this->points_[7] = point8;
    }

    Octagon() = default;

    Octagon(const Octagon& other) {
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
        this->size_ = 8;
        this->points_ = std::make_unique<Point<T>[]>(8);

        for (size_t i = 0; i < this->size_; ++i)
            is >> this->points_[i].x >> this->points_[i].y;
    }

    bool operator==(const Octagon<T>& other) const {
        for (size_t i = 0; i < 8; ++i)
            if (!(this->points_[i] == other.points_[i]))
                return false;
        return true;
    }

    bool operator==(const Figure<T>& other) const override {
        const Octagon<T>* octagon = dynamic_cast<const Octagon<T>*>(&other);
        if (!octagon)
            return false;
        return *this == *octagon;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon<T>>(*this);
    }
};
