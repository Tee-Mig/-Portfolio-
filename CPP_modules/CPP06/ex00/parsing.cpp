#include "scalar.hpp"

int parsing(std::string input)
{
	int i = 0;
	int	sign = 0;

	if (input == "nan" || input == "nanf"
		|| input == "-inff" || input == "+inff"
		|| input == "-inf" || input == "+inf")
		return 1;
	if (input[0] == '-')
		sign = 1;
	if (input[0] == '+')
		i++;
	while (input[i + sign] >= '0' && input[i + sign] <= '9')
		i++;
	if (input[i + sign] == '.')
		i++;
	while (input[i + sign] >= '0' && input[i + sign] <= '9')
		i++;
	if (input[i + sign] == '\0')
		return 1;
	if (i == 0)
	{
		while ((input[i] >= 'A' && input[i] < 'Z') || (input[i] >= 'a' && input[i] < 'z'))
			i++;
		if (i > 1)
			return 0;
		if ((input[i] >= '0' && input[i] <= '9') && i > 0)
			return 0;
		if (sign == 1)
			return 0;
	}
	else if (i > 0 && input[i + sign] == 'f' && input[i + sign + 1] == '\0')
		return 1;
	else
		return 0;
	return 1;
}