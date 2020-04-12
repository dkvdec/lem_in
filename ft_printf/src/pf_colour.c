/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_colour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:44:21 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/09 16:50:16 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		colour_bold(char c)
{
	if (c == 'r')
		safe_sub_join("\033[1;31m", 8);
	else if (c == 'g')
		safe_sub_join("\033[1;32m", 8);
	else if (c == 'y')
		safe_sub_join("\033[1;33m", 8);
	else if (c == 'b')
		safe_sub_join("\033[1;34m", 8);
	else if (c == 'm')
		safe_sub_join("\033[1;35m", 8);
	else if (c == 'c')
		safe_sub_join("\033[1;36m", 8);
	else if (c == 'w')
		safe_sub_join("\033[0m", 5);
}

void		colour_tall(char c)
{
	if (c == 'r')
		safe_sub_join("\033[0;31m", 8);
	else if (c == 'g')
		safe_sub_join("\033[0;32m", 8);
	else if (c == 'y')
		safe_sub_join("\033[0;33m", 8);
	else if (c == 'b')
		safe_sub_join("\033[0;34m", 8);
	else if (c == 'm')
		safe_sub_join("\033[0;35m", 8);
	else if (c == 'c')
		safe_sub_join("\033[0;36m", 8);
	else if (c == 'w')
		safe_sub_join("\033[0m", 5);
}

void		colour_join(char c, char s)
{
	if (s == '+')
	{
		colour_bold(c);
	}
	else if (s == '-')
	{
		colour_tall(c);
	}
}

int			colour_check(char *str, int i)
{
	char c;
	char s;

	c = *(str + i + 1);
	s = *(str + i + 2);
	if ((c == 'r' || c == 'g' || c == 'y'
	|| c == 'b' || c == 'm' || c == 'c'
	|| c == 'w') && (s == '+' || s == '-')
	&& (*(str + i + 3) == '}'))
	{
		return (1);
	}
	return (0);
}
