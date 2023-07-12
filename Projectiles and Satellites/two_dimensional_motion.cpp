#include <iomanip>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#include "../gnuplot-iostream.h"
#include "../utils.cpp"

/*
    Program to visualize the two dimensional projectile motion
*/

std::array<std::vector<double>, 5> TwoDimMotion(double vx, double height, double t_max, double h, double g)
{

    uint n = t_max/h;
    double ts = 0;
    std::vector<double> T, Ax, Ay, Vx, Vy, Y, X;
    T.resize(n);
    Ax.resize(n);
    Ay.resize(n);
    Vx.resize(n);
    Vy.resize(n);
    Y.resize(n);
    X.resize(n);

    Vx[0] = vx;
    Vy[0] = 0;
    T[0] = 0;
    X[0] = 0;
    Y[0] = height;
    Ax[0] = 0;
    Ay[0] = -9.8f;

    for(size_t i=0; i < n; i++)
    {
        if(T[i] >= t_max)
            break;

        T[i] = T[0] + h * i;

        Ax[i] = Ax[0];
        Ay[i] = Ay[0];

        Vx[i + 1] = Vx[i] + Ax[i] * h;
        Vy[i + 1] = Vy[i] + Ay[i] * h;

        if (Y[i] <= 0)
            break;

        X[i + 1] = X[i] + Vx[i] * h;
        Y[i + 1] = Y[i] + Vy[i] * h;
    }
    
    return { T, X, Y, Vx, Vy };
}

int main()
{
    Gnuplot gp;

    auto data = TwoDimMotion(1, 400, 10, 0.25, 9.8);
    auto t = data[0];
    auto x = data[1];
    auto y = data[2];
    auto vx = data[3];
    auto vy = data[4];

    std::ofstream file("output.dat");

    for(size_t i = 0; i < x.size(); i++)
        file << std::setprecision(17) << t[i]  << std::setw(40)
             << std::setprecision(17) << x[i]  << std::setw(40)
             << std::setprecision(17) << y[i]  << std::setw(40)
             << std::setprecision(17) << vx[i] << std::setw(40)
             << std::setprecision(17) << vy[i] << std::setw(40) << std::endl;

    gp << "set title '2d Projectile Motion'\n";
    gp << "set xlabel 'x (m)'\n";
    gp << "set ylabel 'y (m)'\n";
    gp << "plot 'output.dat' 2:3 with lines\n";

    return 0;

}
