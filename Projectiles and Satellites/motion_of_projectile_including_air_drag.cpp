#include <cmath>
#include <iostream>
#include <iomanip>
#include "../utils.cpp"
#include "../gnuplot-iostream.h"
#include <array>
#include <vector>

class ProjectileMotion
{

    public:
    ProjectileMotion()
    {
        T.resize(n);
        X.resize(n);
        Y.resize(n);
        Vx.resize(n);
        Vy.resize(n);
        Ax.resize(n);
        Ay.resize(n);
    }

    std::array<std::vector<double>, 3>
        CalculateMotion()
        {
            TH = TH * PI / 180; // convert to radians
            T[0] = 0;
            X[0] = 0;
            Y[0] = 0;
            Vx[0] = v0 * std::cos(TH);
            Vy[0] = v0 * std::sin(TH);

            Ax[0] = FNX(Vx[0], Vy[0]);
            Ay[0] = FNY(Vx[0], Vy[0]);

            Vx[0] = Vx[0] + 0.5 * Ax[0] * h;
            Vy[0] = Vy[0] + 0.5 * Ay[0] * h;

            for(size_t i = 0; i < n; i++)
            {
                T[i] = h * i;
                Ax[i] = FNX(Vx[i], Vy[i]);
                Ay[i] = FNY(Vx[i], Vy[i]);

                Vx[i + 1] = Vx[i] + Ax[i] * h;
                Vy[i + 1] = Vy[i] + Ay[i] * h;
                X[i + 1] = X[i] + Vx[i] * h;
                Y[i + 1] = Y[i] + Vy[i] * h;
            }

            return { X, Y };
        }

    private:

    double g = -9.8f;
    double PI = 3.1415926f;
    double DC = 0.46f;
    double rho = 1.2;
    double r = 2;
    double m = 1;
    double v0 = 9.8;
    double TH = 45; // degrees
    double t_max = 10;
    double h = 0.01; // time step in seconds
    uint n = t_max / h;
    std::vector<double> T, X, Y, Vx, Vy, Ax, Ay;
    double DEC = 0.5 * DC * rho * PI * r * r / m;


    double FNX(double x, double y)
    {
        return -DEC * x * 1 / std::sqrt(x * x + y * y);
    }

    double FNY(double x, double y)
    {
        return g - DEC * y * 1 / std::sqrt(x * x + y * y);
    }

};

int main()
{

    Gnuplot gp;
    ProjectileMotion p;
    std::ofstream file("output.dat");
    auto data = p.CalculateMotion();
    auto x = data[0];
    auto y = data[1];

    for(size_t i = 0; i < x.size(); i++)
        file << std::setprecision(17) << x[i] << std::setw(40)
            << std::setprecision(17) << y[i] << std::endl;
    
    file.close();

    gp << "plot 'output.dat' with lines\n";

    return 0;
}
