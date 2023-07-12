#include "../utils.cpp"
#include "../gnuplot-iostream.h"
#include <iostream>
#include <array>
#include <vector>

/*
    Program describing the motion of driver oscillator using Feynman-Newton Method
*/

class DrivenOscillation
{
    private:
        double h = 0.01;
        double v0 = 1;
        double x0 = 0;
        double t_max = 25;
        double Fo = 1.5; // Driving force
        double w = 1.01; // Frequency of driver(omega)
        double k = 1; // spring constant
        double C = 0.2; // Damping Coeffecient
        double m = 1;
        double n = t_max/h;
        std::vector<double> T, X, A, V;

    public:

    DrivenOscillation()
    {
        T.resize(n);
        X.resize(n);
        A.resize(n);
        V.resize(n);
    }

    std::array<std::vector<double>, 4>
        Calculate()
        {
            // F = -kx - cv + Fo cos(wt)

            T[0] = 0;
            X[0] = x0;
            V[0] = v0;
            A[0] = FNA(X[0], V[0], T[0]);
            V[0] = V[0] + 0.5 * A[0] * h;

            for(size_t i = 0; i < n; i++)
            {
                T[i + 1] = (i + 1) * h;
                X[i + 1] = X[i] + V[i] * h;
                A[i + 1] = FNA(X[i + 1], V[i], T[i + 1]);
                V[i + 1] = V[i] + A[i + 1] * h;
            }
            return { T, X, V, A };
        }

    double FNA(double x, double v, double t)
    {
        return (-k * x - C * v + Fo * std::cos(w * t))/m;
    }
};

int main()
{
    Gnuplot gp;
    DrivenOscillation d;
    auto data = d.Calculate();
    std::ofstream file("output.dat");

    auto t = data[0];
    auto x = data[1];
    auto v = data[2];
    auto a = data[3];

    for(size_t i = 0; i < t.size(); i++)
        file << _setp << t[i] << _setw << _setp << x[i] << _setw << _setp << v[i] << _setw << _setp << a[i] << std::endl;
    
    gp << "set title 'Forced Oscillations'\n";
    gp << "set grid\n";
    gp << "set xlabel 't (s)'\n";

    // Uncomment the following for x vs t
    gp << "set ylabel 'x (m)'\n";
    gp << "plot 'output.dat' using 1:2 with lines notitle\n";

    // Or Uncomment this for x, v, a vs t curves
    // gp << "set key left top\n";
    // gp << "plot 'output.dat' using 1:2 with lines title 'X(m)', 'output.dat' using 1:3 with lines title 'V (m/s)', 'output.dat' using 1:4 with lines title 'A (m/s^2)'\n";

    return 0;
}
