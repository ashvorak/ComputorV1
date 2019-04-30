#include "../inc/Parser.h"

#include <regex>
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

void Parser::parseMonomial(std::string& monomial, mQuadraticEquation& qEquation, bool isReverse)
{
    std::smatch match;
    std::regex rx("(\\d)");

    int x = std::stoi(&monomial.back());

    std::regex_search(monomial, match, rx);

    double value = std::stod(match.str()); 

    value = (isReverse) ? -value : value;

    if (qEquation.find(x) == qEquation.end())
    {
        qEquation.insert(std::pair<int, double>(x, value));
    }
    else
    {
        qEquation[x] += value;
    }
}

void Parser::parse(std::string expression, mQuadraticEquation& qEquation)
{
    std::smatch match;
    std::regex  rx("((\\+|\\-) )?\\d \\* X\\^\\d");
    auto expression_begin = std::sregex_iterator(expression.begin(), expression.end(), rx);
    auto expression_end = std::sregex_iterator();

    _errorManager->EquationAnalyse(expression);

    int equation = expression.find("=");
    std::cout << " = pos :" << equation << std::endl;

    for (std::sregex_iterator it = expression_begin; it != expression_end; ++it) 
    {
        std::smatch match = *it;
        std::string match_str = match.str();
        std::cout << match_str << " position" << match.position() << std::endl;
        parseMonomial(match_str, qEquation, (equation < match.position()) ? true : false);
    }

    std::cout << qEquation.x0 << std::endl;
    std::cout << qEquation.x1 << std::endl;
    std::cout << qEquation.x2 << std::endl;
}
