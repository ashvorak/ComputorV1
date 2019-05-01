#include "../inc/ErrorManager.h"

#include <regex>
#include <iostream>

ErrorManager::ErrorManager() {}

ErrorManager::~ErrorManager() {}

bool ErrorManager::SyntaxAnalyse(const std::string& equation)
{
	const std::string valid_characters = "X+-*/^.= ";

	for(uint32_t i = 0; i < equation.length(); i++)
	{
		if ((valid_characters.find(equation[i]) == std::string::npos) && !isdigit(equation[i]))
			return false;
	}
	return true;
}

inline std::string generateRegex(const std::string& monomial)
{
	return ("^(" + sign + "?" + monomial + "( " + sign + monomial 
			+ ")* = (0|(" + sign + "?" + monomial + "( " + sign + monomial + ")*)))$");
}

FormOfEquation ErrorManager::LexicalAnalyse(const std::string& equation)
{
    std::smatch match;
    std::regex	rx_standart(generateRegex(monomial_standart));
	std::regex	rx_natural(generateRegex(monomial_natural));

    if (std::regex_search(equation, match, rx_standart))
		return StandartForm;
	if (std::regex_search(equation, match, rx_natural))
		return NaturalForm;
	return ErrorForm;
}

FormOfEquation ErrorManager::EquationAnalyse(const std::string& equation)
{
	FormOfEquation formOfEquation;

	if (!SyntaxAnalyse(equation))
		throw SyntaxException();
	std::cout << "Syntax Analyse : OK." << std::endl;
	if ((formOfEquation = LexicalAnalyse(equation)) == ErrorForm)
		throw LexicalException();
	std::cout << "Lexical Analyse : OK." << std::endl;
	std::cout << "Equation is valid." << std::endl;
	return formOfEquation;
}

ErrorManager::LexicalException::LexicalException() {}

ErrorManager::LexicalException::~LexicalException() noexcept {}

const char* ErrorManager::LexicalException::what() const noexcept
{
	return "Lexical Error.";
}

ErrorManager::SyntaxException::SyntaxException() {}

ErrorManager::SyntaxException::~SyntaxException() noexcept {}

const char* ErrorManager::SyntaxException::what() const noexcept
{
	return "Syntax Error.";
}