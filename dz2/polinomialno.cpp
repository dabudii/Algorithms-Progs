#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class Polynomial {
private:
    vector<double> coefficients;
    vector<int> exponents;

public:
    // Конструкторы
    Polynomial() = default;

    Polynomial(const vector<double>& coeffs, const vector<int>& exps) {
        if (coeffs.size() != exps.size()) {
            throw invalid_argument("Коэффициенты и экспоненты должны иметь одинаковый размер");
        }
        coefficients = coeffs;
        exponents = exps;
    }

    // Конструктор копирования
    Polynomial(const Polynomial& other) {
        coefficients = other.coefficients;
        exponents = other.exponents;
    }

    // Деструктор
    ~Polynomial() = default;

    // Сеттеры
    void setCoefficients(const vector<double>& coeffs) {
        coefficients = coeffs;
    }

    void setExponents(const vector<int>& exps) {
        exponents = exps;
    }

    // Геттеры
    vector<double> getCoefficients() const {
        return coefficients;
    }

    vector<int> getExponents() const {
        return exponents;
    }

    // Определение степени полинома
    int degree() const {
        if (exponents.empty()) return 0;
        return *max_element(exponents.begin(), exponents.end());
    }

    // Вычисление значения полинома для заданного x
    double evaluate(double x) const {
        double result = 0.0;
        for (size_t i = 0; i < coefficients.size(); ++i) {
            result += coefficients[i] * pow(x, exponents[i]);
        }
        return result;
    }

    // Печать полинома
    void print() const {
        if (coefficients.empty()) {
            cout << "0";
            return;
        }

        for (size_t i = 0; i < coefficients.size(); ++i) {
            if (i != 0 && coefficients[i] >= 0) {
                cout << " + ";
            }
            else if (i != 0) {
                cout << " - ";
            }

            if (exponents[i] == 0) {
                cout << abs(coefficients[i]);
            }
            else {
                cout << abs(coefficients[i]) << "x^" << exponents[i];
            }
        }
        cout << endl;
    }

    // Оператор сложения полиномов
    Polynomial operator+(const Polynomial& other) const {
        vector<double> newCoeffs = coefficients;
        vector<int> newExps = exponents;

        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            bool found = false;
            for (size_t j = 0; j < newExps.size(); ++j) {
                if (other.exponents[i] == newExps[j]) {
                    newCoeffs[j] += other.coefficients[i];
                    found = true;
                    break;
                }
            }
            if (!found) {
                newCoeffs.push_back(other.coefficients[i]);
                newExps.push_back(other.exponents[i]);
            }
        }

        return Polynomial(newCoeffs, newExps);
    }

    // Оператор вычитания полиномов
    Polynomial operator-(const Polynomial& other) const {
        vector<double> newCoeffs = coefficients;
        vector<int> newExps = exponents;

        for (size_t i = 0; i < other.coefficients.size(); ++i) {
            bool found = false;
            for (size_t j = 0; j < newExps.size(); ++j) {
                if (other.exponents[i] == newExps[j]) {
                    newCoeffs[j] -= other.coefficients[i];
                    found = true;
                    break;
                }
            }
            if (!found) {
                newCoeffs.push_back(-other.coefficients[i]);
                newExps.push_back(other.exponents[i]);
            }
        }

        return Polynomial(newCoeffs, newExps);
    }
};

class VectPolynomial {
private:
    vector<Polynomial> polynomials;

public:
    // Добавление полинома в вектор
    void addPolynomial(const Polynomial& p) {
        polynomials.push_back(p);
    }

    // Получение полинома по индексу
    Polynomial getPolynomial(size_t index) const {
        if (index >= polynomials.size()) {
            throw out_of_range("Индекс выходит за границы вектора");
        }
        return polynomials[index];
    }

    // Количество полиномов в векторе
    size_t size() const {
        return polynomials.size();
    }

    // Обработка полиномов согласно условию задачи
    static vector<Polynomial> processPolynomials(const VectPolynomial& v1, const VectPolynomial& v2) {
        if (v1.size() != v2.size()) {
            throw invalid_argument("Векторы должны быть одинакового размера");
        }

        vector<Polynomial> result;

        // Обработка нечетных полиномов v1 с четными v2
        for (size_t i = 0; i < v1.size(); i += 2) {
            if (i < v1.size() && i + 1 < v2.size()) {
                result.push_back(v1.getPolynomial(i) + v2.getPolynomial(i + 1));
            }
        }

        // Обработка четных полиномов v1 с нечетными v2
        for (size_t i = 1; i < v1.size(); i += 2) {
            if (i < v1.size() && i - 1 < v2.size()) {
                result.push_back(v1.getPolynomial(i) - v2.getPolynomial(i - 1));
            }
        }

        return result;
    }
};

// Функция для создания полинома с вводом от пользователя
Polynomial createPolynomial() {
    int degree;
    cout << "Введите степень полинома: ";
    cin >> degree;

    vector<double> coeffs;
    vector<int> exps;

    for (int i = 0; i <= degree; ++i) {
        double coeff;
        cout << "Введите коэффициент для x^" << i << ": ";
        cin >> coeff;
        coeffs.push_back(coeff);
        exps.push_back(i);
    }

    return Polynomial(coeffs, exps);
}

int main() {
    setlocale(LC_ALL, "rus");

    VectPolynomial v1, v2;
    int n;

    cout << "Введите количество полиномов в векторах: ";
    cin >> n;

    // Заполнение векторов полиномов
    cout << "\nЗаполнение вектора V1:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Полином " << i + 1 << ":\n";
        v1.addPolynomial(createPolynomial());
    }

    cout << "\nЗаполнение вектора V2:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Полином " << i + 1 << ":\n";
        v2.addPolynomial(createPolynomial());
    }

    // Обработка полиномов
    vector<Polynomial> vout = VectPolynomial::processPolynomials(v1, v2);

    // Вывод результатов
    cout << "\nРезультаты операций (Vout):\n";
    for (size_t i = 0; i < vout.size(); ++i) {
        cout << "Полином " << i + 1 << ": ";
        vout[i].print();
    }

    // Вычисление значений полиномов для конкретного x
    double x;
    cout << "\nВведите значение x для вычисления полиномов: ";
    cin >> x;

    cout << "\nЗначения полиномов Vout при x = " << x << ":\n";
    for (size_t i = 0; i < vout.size(); ++i) {
        cout << "Полином " << i + 1 << ": ";
        vout[i].print();
        cout << " = " << vout[i].evaluate(x) << endl;
    }

    return 0;
}
