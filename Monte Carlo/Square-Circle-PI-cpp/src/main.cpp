#include "gnuplot-iostream.hpp"
#include "../../../utils.hpp"
#include <iostream>
#include <random>
#include <array>
#include <fmt/format.h>

using namespace std;
using namespace dj;

float MonteCarloPI(float radius, int iter)
{
    float x, y;
    int Ncircle, Nsquare;
    Ncircle = Nsquare = 0;

    for(int i=0; i < iter; i++)
    {
        x = Random::random_number_f(-radius, radius);
        y = Random::random_number_f(-radius, radius);

        if (x * x + y * y <= radius * radius)
            Ncircle++;
        else
            Nsquare++;
    }

    return radius * ((float)Ncircle / Nsquare);
}

int main(int argc, char *argv[])
{
    Gnuplot gp;
    float pi;
    int N = 300;
    std::vector<float> ys;
    std::string fstr = "plot '-' with lines, [1:{}] {} with lines\n";
    fstr = fmt::format(fstr, N, PI);
    std::cout << fstr;
    ys.resize(N);

    for(int i=0; i < N; i++)
    {
        pi = MonteCarloPI(1, i);
        std::cout << i << " = " << pi << std::endl;
        ys[i] = pi;
    }

    gp << "set xlabel 'N'\n";
    gp << "set ylabel 'PI'\n";
    gp << fstr;
    gp.send1d(ys);
}
