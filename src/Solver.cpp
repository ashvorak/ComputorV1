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

inline void ExitWithMessage(const std::string& message)
{
	std::cout << message << std::endl;
    exit(1);
}

void Solver::Resolve(const std::string& equation)
{
	double 	discriminate = 0.0;
	mQuadraticEquation qEquation = Parser::get()->Parse(equation);

    if ((discriminate = CalculateDiscriminate(qEquation)) < 0.0)
		ExitWithMessage("Discriminant is strictly negative, there is no solutions.");

    std::cout << "Discriminate = " << discriminate << std::endl;

    double x1 = ((-qEquation[1]) + std::sqrt(discriminate)) / (2 * qEquation[2]);
    double x2 = ((-qEquation[1]) - std::sqrt(discriminate)) / (2 * qEquation[2]);

    std::cout << "X1 = " << x1 << std::endl;
    std::cout << "X2 = " << x2 << std::endl;
}