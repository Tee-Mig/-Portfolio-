#include "scalar.hpp"

void	print_conversions(std::string input)
{
	//print char
	try
	{
		if (input == "nan" || input == "nanf" || input == "+inf" || input == "+inff"
			|| input == "-inf" || input == "-inff")
			throw 1;
		else if (atoi(input.c_str()) >= 32 && atoi(input.c_str()) < 127)
			std::cout << "char: '" << static_cast<char>(atoi(input.c_str())) << "'" << std::endl;
		else if ((atoi(input.c_str()) >= 0 && atoi(input.c_str()) < 32)  || atoi(input.c_str()) == 127)
		{
			if (input.length() == 1 && static_cast<int>(input[0]) >= 32 && static_cast<int>(input[0]) < 127
				&& !(input[0] >= '0' && input[0] <= '9'))
				std::cout << "char: '" << input[0] << "'" << std::endl;
			else
				std::cout << "char: Non displayable" << std::endl;
		}
		else if (input.length() == 1 && static_cast<int>(input[0]) >= 32 && static_cast<int>(input[0]) < 127)
			std::cout << "char: '" << input[0] << "'" << std::endl;
		else
			throw 1;
	}
	catch(...)
	{
			std::cout << "char: impossible" << std::endl;
	}

	//print int
	try
	{
		if (input[0] == '-' && (input.length() > 11 || atof(input.c_str()) < -2147483648))
			throw 1;
		else if (input[0] != '-' && (input.length() > 10 || atof(input.c_str()) > 2147483647))
			throw 1;
		else if (input == "nan" || input == "nanf")
			throw 1;
		std::cout << "int: " << static_cast<int>(atoi(input.c_str())) << std::endl;
	}
	catch(...)
	{
		std::cout << "int: impossible" << std::endl;
	}

	//print float
	try
	{
		if (input == "nan" || input == "nanf")
			std::cout << "float: nanf" << std::endl;
		else if (input == "-inf" || input == "-inff")
			std::cout << "float: -inff" << std::endl;
		else if (input == "+inf" || input == "+inff")
			std::cout << "float: +inff" << std::endl;
		else if (input[0] == '-' && (input.length() > 40 || atof(input.c_str()) < -FLT_MAX))
			throw 1;
		else if (input[0] != '-' && (input.length() > 39 || atof(input.c_str()) > FLT_MAX))
			throw 1;
		else
			std::cout << "float: " << std::fixed << std::setprecision(input.length()) << static_cast<float>(std::atof(input.c_str())) << "f" << std::endl;
	}
	catch(...)
	{
		std::cout << "float: impossible" << std::endl;
	}
	//print double
	try
	{
		if (input == "nan" || input == "nanf")
			std::cout << "double: nan" << std::endl;
		else if (input == "-inf" || input == "-inff")
			std::cout << "double: -inf" << std::endl;
		else if (input == "+inf" || input == "+inff")
			std::cout << "double: +inf" << std::endl;
		else if (input[0] == '-' && (input.length() > 310 || atof(input.c_str()) < -DBL_MAX))
			throw 1;
		else if (input[0] != '-' && (input.length() > 309 || atof(input.c_str()) > DBL_MAX))
			throw 1;
		else
			std::cout << "double: " << std::fixed << std::setprecision(input.length()) << static_cast<double>(std::strtod(input.c_str(), NULL)) << std::endl;
	}
	catch(...)
	{
		std::cout << "double: impossible" << std::endl;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::string input = av[1];
		if (parsing(input))
		{
			print_conversions(input);
		}
		else
			std::cout << "Error: format" << std::endl;
	}
	else
		std::cout << "Error: number of argument" << std::endl;
	return 0;
}