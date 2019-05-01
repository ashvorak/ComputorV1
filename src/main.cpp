#include <iostream>

#include "../inc/Solver.h"

static void ft_usage( void )
{
	std::cout << "USAGE : ./computor \"Expression\"" << std::endl;
	std::cout << "Expression example : \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		try
		{
			Solver::get()->Resolve(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}	
	}
	else
		ft_usage();
	return (0);
}
