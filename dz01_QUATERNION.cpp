#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>

class Quaternion {
private:
    double a, b, c, d; // Коэффициенты кватерниона (a + bi + cj + dk)

public:
    // Конструкторы
    Quaternion() : a(1), b(0), c(0), d(0) {}
    Quaternion(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
    Quaternion(const Quaternion &q) : a(q.a), b(q.b), c(q.c), d(q.d) {}

    // Сеттеры и геттеры
    void setValues(double a, double b, double c, double d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getD() const { return d; }

    // Вывод кватерниона
    void printQuaternion() const {
        std::cout << a << " + " << b << "i + " << c << "j + " << d << "k" << std::endl;
    }

    // Вычисление нормы
    double norm() const {
        return sqrt(a * a + b * b + c * c + d * d);
    }

    // Сопряженный кватернион
    Quaternion conjugate() const {
        return Quaternion(a, -b, -c, -d);
    }

    // Нормализация
    Quaternion normalize() const {
        double n = norm();
        return Quaternion(a / n, b / n, c / n, d / n);
    }

    // Инверсия
    Quaternion inverse() const {
        double n2 = norm() * norm();
        return conjugate() * (1 / n2);
    }

    // Операции над кватернионами
    Quaternion operator+(const Quaternion &q) const {
        return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d);
    }
    Quaternion operator-(const Quaternion &q) const {
        return Quaternion(a - q.a, b - q.b, c - q.c, d - q.d);
    }
    Quaternion operator*(const Quaternion &q) const {
        return Quaternion(
            a * q.a - b * q.b - c * q.c - d * q.d,
            a * q.b + b * q.a + c * q.d - d * q.c,
            a * q.c - b * q.d + c * q.a + d * q.b,
            a * q.d + b * q.c - c * q.b + d * q.a
        );
    }
    Quaternion operator/(const Quaternion &q) const {
        return (*this) * q.inverse();
    }

    // Скалярное произведение
    double dotProduct(const Quaternion &q) const {
        return a * q.a + b * q.b + c * q.c + d * q.d;
    }

    // Евклидово расстояние
    double euclideanDistance(const Quaternion &q) const {
        return sqrt(pow(a - q.a, 2) + pow(b - q.b, 2) + pow(c - q.c, 2) + pow(d - q.d, 2));
    }

    // Норма Чебышева
    double chebyshevNorm(const Quaternion &q) const {
        return std::max({fabs(a - q.a), fabs(b - q.b), fabs(c - q.c), fabs(d - q.d)});
    }
};

#endif
