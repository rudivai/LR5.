#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// Прототипи функцій
void task_geom32();
void task_algo12();
void calculateSeries(double x, int n, double epsilon, double g, int variant);
double factorial(int k);

int main() {
    int menu;
    cout << "Task number:";
    cin >> menu;
    // Перемикання між завданнями
    switch (menu) {
    case 1: task_geom32(); break; // Завдання 1
    case 2: task_algo12(); break; // Завдання 2
    case 3: {
        // Вхідні дані для обчислення ряду
        double x = 2.5;
        int n = 15;
        double epsilon = 1e-10;
        double g = 1e3;
        int variant = 2; // Варіант: кожен третій елемент
        calculateSeries(x, n, epsilon, g, variant);
        break;
    }
    default: cout << "Wrong task! (Only 1, 2, 3)" << endl; // Повідомлення про помилку
    }
    return 0;
}

// Завдання 1
void task_geom32() {
    struct Point {
        double x, y;
    };

    // Функція для перевірки, чи знаходиться точка в помаранчевій зоні
    bool isInOrangeRegion(double x, double y, double r) {
        return (x >= 0) && (y >= 0) && (y <= x) && (x * x + y * y <= r * r);
    }

    int n;
    double r;
    cout << "Enter the number of points (n): ";
    cin >> n;
    cout << "Enter the radius of the circle (r): ";
    cin >> r;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter coordinates for point " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;
    }

    int orangeCount = 0;
    for (const auto& point : points) {
        if (isInOrangeRegion(point.x, point.y, r)) {
            orangeCount++;
        }
    }

    cout << "Number of points in the orange region: " << orangeCount << endl;
}

// Завдання 2
void task_algo12() {
    double x;
    double epsilon = 1e-10;
    double g = 1e3;
    int maxIterations = 1e6;

    cout << "Enter value of x: ";
    cin >> x;

    double sum = 0.0;
    int k = 1;
    while (true) {
        double term = pow(x - k, k + 1) / factorial(k);

        if (fabs(term) < epsilon) {
            cout << "Series converges. Precision achieved: " << epsilon << endl;
            break;
        }
        if (fabs(term) > g) {
            cout << "Series diverges. Term exceeds: " << g << endl;
            break;
        }

        sum += term;
        ++k;

        if (k > maxIterations) {
            cout << "Exceeded maximum number of iterations." << endl;
            break;
        }
    }

    cout << "Sum of series: " << sum << endl;
}

// Обчислення факторіала
double factorial(int k) {
    if (k == 0 || k == 1) return 1.0;
    double fact = 1.0;
    for (int i = 2; i <= k; ++i) {
        fact *= i;
    }
    return fact;
}

// Завдання 3
void calculateSeries(double x, int n, double epsilon, double g, int variant) {
    double totalSum = 0.0;
    bool diverges = false;

    cout << setw(6) << "Index" << setw(25) << "Term" << setw(25) << "Cumulative Sum" << endl;
    for (int k = 1; k <= n; ++k) {
        double term = pow(x - k, k + 1) / factorial(k);
        totalSum += term;

        cout << setw(6) << k << setw(25) << setprecision(15) << term << setw(25) << totalSum << endl;

        if (abs(term) < epsilon) {
            cout << "\nSeries converges (|u_n| < ε)." << endl;
            break;
        }
        if (abs(term) > g) {
            cout << "\nSeries diverges (|u_n| > g)." << endl;
            diverges = true;
            break;
        }

        if ((variant % 2 == 0 && k % 3 == 0) || (variant % 2 != 0 && k % 4 == 0)) {
            cout << "Special element " << k << ": " << term << endl;
        }
    }

    cout << "\nFinal sum: " << setprecision(15) << totalSum << endl;
    if (diverges) {
        cout << "The series diverges." << endl;
    }
    else {
        cout << "The series converges." << endl;
    }
}
