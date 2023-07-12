#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include "../gnuplot-iostream.h"
#include "../utils.cpp"

// NOT DONE

/*
    Program to visualize 2d projectile motion along an arbitrary direction with angle theta
*/

std::array<std::vector<double>, 5> TwoDimMotion(double v0, double theta, double t_max, double h, double g)
{
    uint n = t_max/h;
    std::vector<double> T, Vx, Vy, Y, X;
    T.resize(n);
    Vx.resize(n);
    Vy.resize(n);
    Y.resize(n);
    X.resize(n);

    double vx = v0 * std::cos(theta);
    double vy = v0 * std::sin(theta);


    for(size_t i=0; i < n; i++)
    {
        if(Y[i] <= 0)
            break;

        T[i] = i * h;

        if(T[i] >= t_max)
            break;

        Vx[i] = vx;
        Vy[i] = vy - g * T[i];
        
        X[i] = vx * T[i];
        Y[i] = vy * T[i] - 0.5 * g * T[i] * T[i];

    }
    
    return { T, X, Y, Vx, Vy };
}

int main()
{
    Gnuplot gp;

    auto data = TwoDimMotion(10, 45, 30, 0.5, 9.8);
    auto t = data[0];
    auto x = data[1];
    auto y = data[2];
    auto vx = data[3];
    auto vy = data[4];

    std::ofstream file("output.dat");
    
    for(size_t i = 0; i < x.size(); i++)
        file << _setp << t[i]  << _setw
             << _setp << x[i]  << _setw
             << _setp << y[i]  << _setw
             << _setp << vx[i] << _setw
             << _setp << vy[i] << _setw << std::endl;
    
    gp << "set title '2d Projectile Motion'\n";
    gp << "set xlabel 'x (m)'\n";
    gp << "set ylabel 'y (m)'\n";
    gp << "plot 'output.dat' using 1:3 with lines\n";

    return 0;

}
