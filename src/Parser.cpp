#include "../inc/Parser.h"

#include <regex>
#include <cmath>
#include <iostream>
#include <sstream>

Parser::Parser() : _errorManager(new ErrorManager())
{}

Parser::~Parser()
{}

Parser* Parser::get()
{
    static Parser self;
    return &self;
}

static inline std::string generateRegex(const std::string& monomial)
{
	return (sign + "?" + monomial);
}

void Parser::ParseMonomial(const std::string& addend, bool isInverse, mQuadraticEquation& qEquation)
{
	size_t	pos_x;
	size_t	pos_dig;
	size_t	x;
	double value = (isdigit(addend.front())) ? std::stod(&addend.front()) : 1;

	if ((pos_x = addend.find("X")) != std::string::npos)
	{
		if ((pos_dig = addend.find_first_of("0123456789", pos_x)) != std::string::npos)
			x = std::stoi(&addend[pos_dig]);
		else
			x = 1;
	}
	else
		x = 0;
	if (isInverse)
		value = -value;
	if (value != 0)
	{
		if (qEquation.find(x) == qEquation.end())
			qEquation.insert(std::pair<int, double>(x, value));
		else
		{
			qEquation[x] += value;
			if (qEquation[x] == 0)
				qEquation.erase(x);
		}
	}
}

void Parser::ParseMonomials(const std::string& equation, FormOfEquation formOfEquation, mQuadraticEquation& qEquation)
{
	std::regex	rx;
	u_int32_t	equal = equation.find("=");

	rx.assign(generateRegex(formOfEquation == StandartForm ? monomial_standart : monomial_natural));	
    auto begin = std::sregex_iterator(equation.begin(), equation.end(), rx);
    auto end = std::sregex_iterator();
	for (std::sregex_iterator it = begin; it != end; ++it) 
    {
        std::smatch match = *it;
		bool isInverse = (equal < match.position()) ? true : false;
		if (!match[1].str().empty() && match[1].str().front() == '-')
			isInverse = !isInverse;
        ParseMonomial(match[3].str(), isInverse, qEquation);
    }
}

void Parser::ShowReducedForm(FormOfEquation formOfEquation, mQuadraticEquation& qEquation)
{
	std::ostringstream ssOutput;

	std::cout << "Reduced form: ";
	for (const auto& qEquationPair : qEquation)
	{
		if (qEquationPair.second != 0)
		{
			if (ssOutput.tellp() || qEquationPair.second < 0)
				ssOutput << ((qEquationPair.second >= 0) ? "+ " : "- ");
			if (!(formOfEquation == NaturalForm && (fabs(qEquationPair.second) == 1)))
				ssOutput << fabs(qEquationPair.second);
			if (!(formOfEquation == NaturalForm && qEquationPair.first == 0))
			{
				if (!(formOfEquation == NaturalForm && (fabs(qEquationPair.second) == 1)))
					ssOutput << " * ";
				ssOutput << "X";
				if (!(formOfEquation == NaturalForm && qEquationPair.first < 2))
					ssOutput << "^" << qEquationPair.first;			
			}
			ssOutput << " ";
		}
	}
	if (!ssOutput.tellp())
		ssOutput << "0 ";
	ssOutput << "= 0" << std::endl;
	std::cout << ssOutput.str();
}

mQuadraticEquation Parser::Parse(const std::string& equation)
{
	mQuadraticEquation	qEquation = {{0, 0.0}, {1, 0.0}, {2, 0.0}};
	FormOfEquation		formOfEquation = _errorManager->EquationAnalyse(equation);

	std::cout << "Quadrantic Equation: c * X^0 + b * X^1 + a * X^2 = 0" << std::endl;
	ParseMonomials(equation, formOfEquation, qEquation);
	ShowReducedForm(formOfEquation, qEquation);
	if (!qEquation.empty())
		std::cout << "Polynomial degree: " << (--qEquation.cend())->first << std::endl;
	return qEquation;
}
