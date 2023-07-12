#include "../utils.cpp"
#include "../gnuplot-iostream.h"
#include <array>
#include <fstream>
#include <vector>

std::array<std::vector<double>, 3>
SHM()
{
    double k     = 1;
    double m     = 10;
    double x0    = 0;
    double v0    = 1;
    double h     = 0.01;
    double t_max = 20;
    size_t n     = t_max / h;
    std::vector<double> T(n), X(n), V(n), A(n);

    T[0] = 0;
    X[0] = x0;
    V[0] = v0;
    A[0] = 0;

    for(size_t i=0; i < n; i++)
    {
        T[i]     = h * i;
        A[i]     = -k * X[i] / m;
        V[i + 1] = V[i] + A[i] * h;
        X[i + 1] = X[i] + V[i] * h;
    }

    return { T, X };
}

int main()
{
    Gnuplot gp;
    std::ofstream file("output.dat");
    auto data = SHM();
    auto t = data[0];
    auto x = data[1];

    for(size_t i = 0; i < x.size(); i++)
        file << _setp << t[i] << _setw << x[i] << std::endl;

    gp << "set grid\n";
    gp << "set title 'SHM using Euler method'\n";
    gp << "set xlabel 't (s)\n";
    gp << "set ylabel 'x (s)\n";
    gp << "plot 'output.dat' with lines notitle \n";
    return 0;
}
