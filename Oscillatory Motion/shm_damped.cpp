#include "../utils.cpp"
#include "../gnuplot-iostream.h"
#include <iostream>
#include <array>
#include <vector>

std::array<std::vector<double>, 4>
DampedSHM()
{
    double h = 0.01;
    double v0 = 1;
    double x0 = 0;
    double t_max = 20;
    double k = 1;
    double C = 0.5; // Damping Coeffecient
    double m = 1;
    double n = t_max/h;
    std::vector<double> T(n), X(n), A(n), V(n);
    double E_tot;

    T[0] = 0;
    X[0] = x0;
    V[0] = v0;
    A[0] = -(k * X[0] + C * V[0]) / m;
    V[0] = V[0] + 0.5 * A[0] * h;

    for(size_t i = 0; i < n; i++)
    {
        T[i] = i * h;
        X[i + 1] = X[i] + V[i] * h;
        E_tot = 0.5 * (m * V[i] * V[i] + k * X[i] * X[i]);
        A[i + 1] = -(k * X[i + 1] + C * V[i])/m;
        V[i + 1] = V[i] + A[i + 1] * h;
    }

    return { T, X, V, A };
}

int main()
{
    Gnuplot gp;
    auto data = DampedSHM();
    std::ofstream file("output.dat");

    auto t = data[0];
    auto x = data[1];
    auto v = data[2];
    auto a = data[3];

    for(size_t i = 0; i < t.size(); i++)
        file << _setp << t[i] << _setw << _setp << x[i] << _setw << _setp << v[i] << _setw << _setp << a[i] << std::endl;
    
    gp << "set title 'Damped SHM'\n";
    gp << "set xlabel 't (s)'\n";
    // gp << "set ylabel 'v (m/s)'\n";
    gp << "set grid\n";
    gp << "plot 'output.dat' using 1:2 with lines title 'X(m)', 'output.dat' using 1:3 with lines title 'V (m/s)', 'output.dat' using 1:4 with lines title 'A (m/s^2)'\n";
    // gp << "plot 'output.dat' using 2:3 with lines\n";

    return 0;
}
