/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:55:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/20 17:15:45 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REPLACE_STR_HPP
#define FT_REPLACE_STR_HPP

#include <iostream>
#include <fstream>
#include <string>

void ft_replace_str(char *filename, char *s1, char *s2);
void ft_new_line(std::string &new_line, std::string buffer, std::string s1, std::string s2);

#endif