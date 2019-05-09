#include "../inc/Parser.h"

#include <regex>
#include <cmath>
#include <iostream>

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
		std::cout << match.str() << std::endl;
        ParseMonomial(match[3].str(), isInverse, qEquation);
    }
}

mQuadraticEquation Parser::Parse(const std::string& equation)
{
	std::string 		output;
	mQuadraticEquation	qEquation;
	FormOfEquation		formOfEquation = _errorManager->EquationAnalyse(equation);

	ParseMonomials(equation, formOfEquation, qEquation);
	for (const auto& qEquationPair : qEquation)
	{
		std::cout << "X : " << qEquationPair.first << " value : " << qEquationPair.second << std::endl; 
	}
	std::cout << "Reduced form : ";
	for (const auto& qEquationPair : qEquation)
	{
		if (qEquationPair != *(qEquation.begin()))
			std::cout << ((qEquationPair.second > 0) ? "+ " : "- ");
		if (!(formOfEquation == NaturalForm && fabs(qEquationPair.second) == 1))
			std::cout << fabs(qEquationPair.second) << " ";
		if (!(formOfEquation == NaturalForm && (qEquationPair.first == 0 || fabs(qEquationPair.second) == 1)))
			std::cout << "* ";
		if (!(formOfEquation == NaturalForm && qEquationPair.first == 0))
			std::cout << "X" << (!(formOfEquation == NaturalForm && qEquationPair.first < 2)
						? "^" + std::to_string(qEquationPair.first) : "") << " ";
	}
	std::cout << "= 0" << std::endl;
	return qEquation;
}
