#include "../utils.hpp"
#include "../gnuplot-iostream.h"
#include <array>
#include <cmath>
#include <vector>

class YoungsDoubleSlit
{
    public:
        YoungsDoubleSlit()
        {
            lambda = 4000e-10;
            amp    = 100;
            sl     = 40e-3;
            D      = 300e-3;
            d      = 0.01e-3;
            np     = 64;
            nt     = 8;
            
            h = sl/np;
            
            k = 2 * PI/lambda;
            w = CL * k;
            x1 = 0;
            y1 = 0.5 * (sl - d);
            x2 = x1;
            y2 = 0.5 * (sl + d);
            x = D + x1;
            // TODO: draw slit arrangement function()

            for(size_t i=0; i < np; i++)
            {
                X[i] = x;
                y = i * h;
                r1 = (x - x1) * (x - x1) + (y - y1) * (y - y1);
                r2 = (x - x2) * (x - x2) + (y - y2) * (y - y2);
                r1 = std::sqrt(r1);
                r2 = std::sqrt(r2);
                I = 0;

                for(size_t t = 0; t < nt; t++)
                {
                    amp = SuperimposedAmplitude(r1, r2, t);
                    I = I + amp * amp;
                }

                I = I/nt;
                Is[i] = I;
            }
        }

    private:
        double lambda; // wavelength
        double k; // wave vector
        double amp; // amplitude
        double D; // distance to screen
        double d; // slit spacing
        double w; // omega
        double sl; // Screen Length
        double np; // no. of points on the screen
        double nt; // time step for one cycle
        double h;
        double I; // intensity
        double x1, y1, x2, y2, x, y, r1, r2;
        std::vector<double> X, Y, Is;

        std::array<std::vector<double>, 2>
            Calculate()
            {


            }

        double SuperimposedAmplitude(double x, double y, double t)
        {
            return amp * (std::cos(k * x - w * t)/x + std::cos(k * y - w * t)/y);
        }
};

int main()
{


}
