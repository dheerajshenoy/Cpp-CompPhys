#include "../utils.cpp"
#include "../gnuplot-iostream.h"
#include <array>
#include <fstream>
#include <vector>

class FourierAnalyis
{
    private:
        std::array<std::vector<double>, 2> _data;
        std::vector<double> amp;

    public:
        
        FourierAnalyis()
        {
            _data = Calculate();
        }

        std::array<std::vector<double>, 2>
            Calculate()
            {
                std::vector<double> X, Y;


                return { X, Y };
            }


        double f(size_t i, double t)
        {
            return 
        }

        void Plot()
        {
            auto x = _data[0];
            auto y = _data[1];
            Gnuplot gp;

            std::ofstream file("output.dat");

            for(size_t i = 0; i < x.size(); i++)
                file << _setp << x[i] << _setw << _setp << y[i] << std::endl;

            gp << "set title 'Fourier Analyis'\n";
            gp << "plot 'output.dat' with lines\n";
        }

};

int main()
{
    FourierAnalyis f;
    return 0;
}
