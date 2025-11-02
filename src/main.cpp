#include <iostream>
#include "include/array.h"
#include "include/octagon.h"
#include "include/triangle.h"
#include "include/square.h"

int main() {
    Octagon<int> Octagon({0, 0}, {1, 0}, {2, 1}, {3, 2}, {2, 3}, {1, 4}, {0, 4}, {-1, 3});
    Triangle<int> triangle({0, 0}, {2, 0}, {1, 2});
    Square<int> square({0, 0}, {2, 0}, {2, 2}, {0, 2});

    std::cout << "Octagon: ";
    octagon.print(std::cout);

    std::cout << "Traingle: ";
    triangle.print(std::cout);

    std::cout << "Square: ";
    square.print(std::cout);

    std::cout << std::endl;

    Array<int> array(3);
    array.addFigure(std::make_shared<Octagon<int>>(octagon));
    array.addFigure(std::make_shared<Triangle<int>>(triangle));
    array.addFigure(std::make_shared<Square<int>>(square));
    array.printFigures();
    std::cout << "Total area: " << array.getAllArea() << std::endl;
    std::cout << std::endl;
    std::shared_ptr<Figure<int>> figure = array[1];
    std::cout << "Figure at index 1: ";
    figure->print(std::cout);
    std::cout << "Area: " << static_cast<double>(*figure) << std::endl;
    return 0;
}
