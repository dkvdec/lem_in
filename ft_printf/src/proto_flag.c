/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:23:06 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 20:53:45 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

/*
** === ALL_FLAGS ===
**
** hh\h === counter ++ while reads, if it reads again it sets counter to 0
** l\ll === counter ++ while reads, if it reads again it sets counter to 0
** L
** #0-+_
** w === greps number starting with non z character
** pr === greps number starting with . folowing by non z character
*/

void		grep_dot_star(char **str, int *i, int *j)
{
	(*j)++;
	while (*((*str) + (*i) + (*j)) && ft_isdigit(*((*str) + (*i) + (*j))))
		(*j)++;
	if (*((*str) + (*i) + (*j)) == '$')
	{
		t_f.pr = (int)silent_grep(ft_atoi((*str) + (*i) + 2));
		(*i) += (*j);
	}
	else
	{
		t_type.ds++;
		t_f.pr = (t_f.w < 0) ? t_f.w - 1 : -1;
		(*i) += 1;
	}
}

int			grep_dot(char *str, int i)
{
	int j;

	j = 1;
	t_f.pz++;
	t_f.pr = 0;
	if (ft_isdigit(*(str + i + j)))
	{
		while (*(str + i + j) && ft_isdigit(*(str + i + j)))
			j++;
		t_f.pr = ft_atoi(str + i + 1);
		i += j - 1;
	}
	else if (*(str + i + j) == '*')
		grep_dot_star(&str, &i, &j);
	return (i);
}

int			grep_star(char *str, int i)
{
	int j;

	j = 1;
	if (ft_isdigit(*(str + i + j)))
	{
		while (*(str + i + j) && ft_isdigit(*(str + i + j)))
			j++;
		if (*(str + i + j) == '$')
		{
			t_f.w = (int)silent_grep(ft_atoi(str + i + 1));
			i += j;
		}
		else
		{
			t_type.s++;
			t_f.w = (t_f.pr < 0) ? t_f.pr - 1 : -1;
		}
	}
	else
	{
		t_type.s++;
		t_f.w = (t_f.pr < 0) ? t_f.pr - 1 : -1;
	}
	return (i);
}

void		flag_passer_u(void)
{
	t_f.h = 0;
	t_f.l = 1;
}

int			flag_passer(char *str, int i)
{
	reset_f();
	while (*(str + i) && !(cs_check(*(str + i))))
	{
		if (!(skip_able(*(str + i))))
			return ((-1) * i);
		else if (easy_flags(*(str + i)))
			flag_recognition(*(str + i));
		else if (*(str + i) == 'h' || *(str + i) == 'l'
		|| *(str + i) == 'z' || *(str + i) == 'j')
			hl_recognition(str, i);
		else if (ft_isdigit(*(str + i)))
			i = grep_nbr(str, i);
		else if (*(str + i) == '.')
			i = grep_dot(str, i);
		else if (*(str + i) == '*')
			i = grep_star(str, i);
		i++;
	}
	if (*(str + i) == 'U')
		flag_passer_u();
	if (cs_check(*(str + i)))
		return (i);
	return (-i);
}
