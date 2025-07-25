/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:31:11 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/20 17:18:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_replace_str.hpp"

void ft_new_line(std::string &new_line, std::string buffer, std::string s1, std::string s2)
{
	int i = 0;
	int j;

	while (buffer[i])
	{
		j = 0;
		while (buffer[i + j] == s1[j] && buffer[i + j])
			j++;
		if (s1[j] == '\0')
		{
			j = 0;
			while (s2[j])
			{
				new_line.push_back(s2[j]);
				j++;
			}
			i += s1.size();
		}
		else
		{
			new_line.push_back(buffer[i]);
			i++;
		}
	}
}

void ft_replace_str(char *filename, char *s1, char *s2)
{
	std::string buffer = "";
	std::string line;
	std::string new_line;
	(std::string)filename;
	(std::string)s1;
	(std::string)s2;

	if (s1[0] == '\0')
	{
		std::cout << "Error: second argument can't be empty" << std::endl;
		return ;
	}
	std::ifstream in_file(filename);
	if (!in_file.is_open())
	{
		std::cout << "Error: can't open file" << std::endl;
		return ;
	}
	while (getline(in_file, line))
	{
		ft_new_line(new_line, line, s1, s2);
		buffer += new_line + "\n";
		new_line.erase();
	}
	in_file.close();
	std::ofstream out_file((std::string(filename) + ".replace").c_str());
	if (!out_file.is_open())
	{
		std::cout << "Error: can't open file" << std::endl;
		return ;
	}
	out_file << buffer;
	out_file.close();
}