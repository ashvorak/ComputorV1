#include "../inc/Parser.h"

#include <regex>
#include <cmath>
#include <iostream>
#include <algorithm>

Parser::Parser() : _errorManager(new ErrorManager())
{}

Parser::~Parser()
{}

Parser* Parser::get()
{
    static Parser self;
    return &self;
}

void Parser::ParseMonomial(const std::string& addend, bool isInverse, mQuadraticEquation& qEquation)
{
	int		x;
	double	value;

	//refactor
	if (addend != "X")
    	x = std::stod(&addend[6]);//if > than 1 digit
	else
		x = 1;
	if (addend.front() != 'X')
	value = std::stoi(&addend.front());
	if (isInverse)
		value = -value;
    if (qEquation.find(x) == qEquation.end())
        qEquation.insert(std::pair<int, double>(x, value));
    else
        qEquation[x] += value;
}

void Parser::ParseMonomials(const std::string& equation, FormOfEquation formOfEquation, mQuadraticEquation& qEquation)
{
	u_int32_t	equal = equation.find("=");
	std::regex	rx;

	if (formOfEquation == StandartForm)
		rx.assign(sign + "?" + monomial_standart);
	else
		rx.assign(sign + "?" + monomial_natural);	
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

mQuadraticEquation Parser::Parse(const std::string& equation)
{
	FormOfEquation		formOfEquation = _errorManager->EquationAnalyse(equation);
	mQuadraticEquation	qEquation;

	ParseMonomials(equation, formOfEquation, qEquation);
	std::cout << "Reduced form: ";
	for (const auto& qEquationPair : qEquation)
	{
		//all to out string 
		if (qEquationPair != *(qEquation.begin()))
			std::cout << ((qEquationPair.second > 0) ? "+ " : "- ");
		if (formOfEquation != NaturalForm && fabs(qEquationPair.second) > 1)//error! separate condition (1 in standart form)
			std::cout << fabs(qEquationPair.second) << " * ";
		std::cout << "X" << (formOfEquation == NaturalForm && (qEquationPair.first < 2) ? "" : "^" + std::to_string(qEquationPair.first)) << " ";
	}
	std::cout << "= 0" << std::endl;
	return qEquation;
}
