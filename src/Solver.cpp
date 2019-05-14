#include "../inc/Solver.h"

#include <cmath>
#include <iostream>

Solver::Solver() {}

Solver::~Solver() {}

Solver* Solver::get()
{
    static Solver self;
    return &self;
}

inline double CalculateDiscriminate(mQuadraticEquation& qEquation)
{
    return (std::pow(qEquation[1], 2) - 4 * qEquation[0] * qEquation[2]);
}

void Solver::CalculateRoots(double discriminate, mQuadraticEquation& qEquation)
{
    double x1;
    double x2;

    if (qEquation[2] == 0)
    {
        std::cout << "X = " << - qEquation[0] / qEquation[1] << std::endl;
        return;
    }
    x1 = ((-qEquation[1]) + std::sqrt(discriminate)) / (2 * qEquation[2]);
    x2 = ((-qEquation[1]) - std::sqrt(discriminate)) / (2 * qEquation[2]);
    if (x1 != x2)
    {
        std::cout << "X1 = " << x1 << std::endl;
        std::cout << "X2 = " << x2 << std::endl;
    }
    else
        std::cout << "X = " << x1 << std::endl;
}

void Solver::Resolve(const std::string& equation)
{
	double 	discriminate;
	mQuadraticEquation qEquation = Parser::get()->Parse(equation);

    if (qEquation.size() > 3)
    {
        std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
        return;     
    }
    discriminate = CalculateDiscriminate(qEquation);
    std::cout << "Discriminate = " << discriminate << std::endl;
    if (discriminate >= 0)
        CalculateRoots(discriminate, qEquation);
    else
        std::cout << "Discriminant is strictly negative, there are no solutions." << std::endl;
}
