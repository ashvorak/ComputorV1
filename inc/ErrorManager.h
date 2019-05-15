#pragma once

#include <string>

const std::string sign = "((\\+|\\-) *)";
const std::string monomial_standart = "(\\d+(.?\\d+)?( )*\\*( )*X\\^(0|[1-9][0-9]*))";
const std::string monomial_natural = "((\\d+(.?\\d+)?(( )*\\*( )*X(\\^([1-9][0-9]*))?)?)|X((\\^([1-9][0-9]*))?)?)";

enum FormOfEquation 
{
	StandartForm,
	NaturalForm,
	ErrorForm
};

class ErrorManager
{

	bool 			SyntaxAnalyse(const std::string& equation);
	FormOfEquation	LexicalAnalyse(const std::string& equation);

public:

    ErrorManager();
    ~ErrorManager();

    FormOfEquation	EquationAnalyse(const std::string& expression);

    class SyntaxException : public std::exception {

		public:
			SyntaxException();
			~SyntaxException() noexcept;
			
			virtual const char *what() const noexcept;

	};

    class LexicalException : public std::exception {

		public:
			LexicalException();
			~LexicalException() noexcept;
			
			virtual const char *what() const noexcept;

	};
};