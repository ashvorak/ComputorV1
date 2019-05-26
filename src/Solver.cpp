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

static inline double CalculateDiscriminate(mQuadraticEquation& qEquation)
{
    return (std::pow(qEquation[1], 2) - 4 * qEquation[0] * qEquation[2]);
}

void Solver::CalculateRoots(double discriminate, mQuadraticEquation& qEquation)
{
    double a;
    double b;

    if (qEquation[2] == 0)
    {
        if (qEquation[1] == 0)
		{
			if (qEquation[0] == 0)
				std::cout << "All roots are solutions." << std::endl;
			else
				std::cout << "There are no solutions. Try to enter real quadrantic equation :)." << std::endl;
		}
        else
        {
            std::cout << "The solution is:" << std::endl;
            std::cout << "X = " << (- qEquation[0]) / qEquation[1] << std::endl;
        }
    }
	else
	{
		std::cout << "Discriminate = " << discriminate << std::endl;
		a = (-qEquation[1]) / (2 * qEquation[2]);
		b = std::sqrt(fabs(discriminate)) / (2 * qEquation[2]);
		if (discriminate >= 0)
		{
			if ((a + b) != (a - b))
			{
				std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
				std::cout << "X1 = " << a + b << std::endl;
				std::cout << "X2 = " << a - b << std::endl;
			}
			else
			{
				std::cout << "Discriminant is 0, the solution is:" << std::endl;
				std::cout << "X = " << a + b << std::endl;
			}
		}
		else
		{
			std::string sB = b < 0 ? "(" + std::to_string(b) + ")" : std::to_string(b);
			std::cout << "Discriminant is strictly negative, the two solutions are:" << std::endl;
			std::cout << "X1 = " << a << " - " << sB << " * i" << std::endl;
			std::cout << "X2 = " << a << " + " << sB << " * i" << std::endl;
		}
	}
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
    std::cout << "Discriminant = b^2 - 4 * a * c" << std::endl;
    std::cout << "c = " << qEquation[0] << std::endl
              << "b = " << qEquation[1] << std::endl 
              << "a = " << qEquation[2] << std::endl;
    discriminate = CalculateDiscriminate(qEquation);
    CalculateRoots(discriminate, qEquation);
}
