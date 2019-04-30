#include "../inc/Solver.h"

#include <iostream>
#include <cmath>

Solver::Solver() {}

Solver::~Solver() {}

Solver* Solver::get()
{
    static Solver self;
    return &self;
}

inline double calculateDiscriminate(mQuadraticEquation& qEquation)
{
    return (std::pow(qEquation[1], 2) - 4 * qEquation[0] * qEquation[2]);
}

void Solver::resolve(mQuadraticEquation& qEquation)
{
    double discriminate = 0.0;

    if ((discriminate = calculateDiscriminate(qEquation)) < 0.0)
    {
        std::cout << "Discriminant is strictly negative, there is no solutions." << std::endl;
        exit(1);
    }

    std::cout << "Discriminate = " << discriminate << std::endl;

    double x1 = ((-qEquation[1]) + std::sqrt(discriminate)) / 2 * qEquation[2];
    double x2 = ((-qEquation[1]) - std::sqrt(discriminate)) / 2 * qEquation[2];

    std::cout << "X1 = " << x1 << std::endl;
    std::cout << "X2 = " << x2 << std::endl;
}