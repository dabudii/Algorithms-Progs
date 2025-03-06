#ifndef ELLIPSIS_H
#define ELLIPSIS_H

#include <iostream>
#include <cmath>
#include <utility>

class Ellipsis {
private:
    double h, k; // Центр эллипса
    double a, b; // Большая и малая полуоси

public:
    // Конструкторы
    Ellipsis() : h(0), k(0), a(1), b(1) {}
    Ellipsis(double h, double k, double a, double b) {
        this->h = h;
        this->k = k;
        if (a >= b) {
            this->a = a;
            this->b = b;
        } else {
            this->a = b;
            this->b = a;
        }
    }
    Ellipsis(const Ellipsis &other) : h(other.h), k(other.k), a(other.a), b(other.b) {}

    // Сеттер с проверкой
    void setValues(double h, double k, double a, double b) {
        this->h = h;
        this->k = k;
        if (a >= b) {
            this->a = a;
            this->b = b;
        } else {
            this->a = b;
            this->b = a;
        }
    }
    
    // Вычисление гиперпараметра c
    double getC() const {
        return sqrt(a * a - b * b);
    }

    // Координаты вершин
    std::pair<double, double> getVertices() const {
        return {h - a, h + a};
    }

    // Координаты фокусов
    std::pair<double, double> getFoci() const {
        double c = getC();
        return {h - c, h + c};
    }

    // Длина фокальной хорды
    double getLR() const {
        return (2 * b * b) / a;
    }

    // Эксцентриситет
    double getEccentricity() const {
        return getC() / a;
    }

    // Вывод уравнения эллипса
    void printEquation() const {
        std::cout << "(x - " << h << ")^2 / " << a * a << " + (y - " << k << ")^2 / " << b * b << " = 1" << std::endl;
    }

    // Проверка, принадлежит ли точка эллипсу
    bool isPointInside(double x, double y) const {
        return ((x - h) * (x - h)) / (a * a) + ((y - k) * (y - k)) / (b * b) <= 1;
    }

    // Приближенный периметр
    double getPerimeter() const {
        return M_PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    // Площадь эллипса
    double getArea() const {
        return M_PI * a * b;
    }

    // Вычисление второй координаты точки на эллипсе
    double computeSecondCoordinate(double x_or_y, bool isXGiven) const {
        if (isXGiven) {
            return k + sqrt(b * b * (1 - ((x_or_y - h) * (x_or_y - h)) / (a * a)));
        } else {
            return h + sqrt(a * a * (1 - ((x_or_y - k) * (x_or_y - k)) / (b * b)));
        }
    }
};

#endif
