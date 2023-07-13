#include <cstdarg>
#include <iostream>
#include <list>
#include <string>

#define _setw std::setw(40)
#define _setp std::setprecision(17)
#define PI 3.1415926

namespace dj
{
    class Utils
    {

        public:

            // Function to print a list
            template <typename T>
                static void printarray(T a)
                {
                    for(uint i = 0; i < a.size(); i++)
                        std::cout << a.at(i) << " ";
                    std::cout << std::endl;
                }
    };

    template <typename T>
    class dsarray
    {
        public:
            dsarray(size_t size);
            dsarray(size_t size, T elem);
            ~dsarray();
            T& operator[](uint i);
            size_t size();
            bool isfull();
            void print(std::string sep = " ");

        private:
            T* _array;
            size_t _size;
    };

    template <typename T>
    dsarray<T>::dsarray(size_t size)
    {
        _size = size;
        _array = new T[size];
        for(size_t i = 0; i < size; i++)
            _array[i] = 0;
    }

    template <typename T>
    dsarray<T>::dsarray(size_t size, T elem)
    {
        _size = size;
        _array = new T[size];
        for(size_t i = 0; i < size; i++)
            _array[i] = elem;
    }

    template <typename T>
    dsarray<T>::~dsarray()
    {
        delete _array;
    }

    template <typename T>
    size_t dsarray<T>::size()
    {
        return _size;
    }

    template <typename T>
    T& dsarray<T>::operator[](uint i)
    {
        return _array[i];
    }

    template <typename T>
    void dsarray<T>::print(std::string sep)
    {
        for(size_t i = 0; i < _size; i++)
            std::cout << _array[i] << sep;
        std::cout << std::endl;
    }
}
