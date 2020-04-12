/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:12:03 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:19:36 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int		size_star_count(const char *str, int i)
{
	int j;
	int tmp;

	t_lres.star_flag++;
	i++;
	j = 0;
	if (ft_isdigit(*(str + i)))
	{
		while (*(str + i + j) && ft_isdigit(*(str + i + j)))
			j++;
		if (*(str + i + j) == '$')
		{
			tmp = ft_atoi(str + i);
			t_lres.sb_c = (tmp > t_lres.sb_c) ? tmp : t_lres.sb_c;
			j++;
			t_lres.star_flag = 0;
		}
	}
	i += j;
	return (i);
}

int		size_bucks_count(const char *str, int i)
{
	int j;
	int tmp;

	j = 0;
	while (*(str + i + j) && ft_isdigit(*(str + i + j)))
		j++;
	if (*(str + i + j) == '$')
	{
		t_lres.bucks_flag++;
		tmp = ft_atoi(str + i);
		if (t_lres.mb_counter > t_lres.sb_c)
			t_lres.sb_c = t_lres.mb_counter;
		t_lres.mb_counter = tmp;
		j++;
	}
	i += j;
	return (i);
}

void	size_count_resulter(const char *str, int i)
{
	if (t_lres.dot_flag > 0)
	{
		t_lres.l_counter++;
		if (t_lres.mb_counter > 0 && t_lres.bucks_flag == 0)
			t_lres.mb_counter++;
	}
	if (t_lres.star_flag > 0)
	{
		t_lres.l_counter++;
		if (t_lres.mb_counter > 0 && t_lres.bucks_flag == 0)
			t_lres.mb_counter++;
	}
	if (*(str + i) && cs_check(*(str + i)))
	{
		t_lres.l_counter += (*(str + i) == '%') ? 0 : 1;
		if (t_lres.mb_counter > 0 && t_lres.bucks_flag == 0)
			t_lres.mb_counter++;
	}
	else
		t_lres.error_counter++;
}

int		size_cs_runner(const char *str, int i)
{
	size_flag_reset();
	while (*(str + i) && cs_check(*(str + i)) != 1)
	{
		if (!(skip_able(*(str + i))))
			return (i);
		else if (skipable(*(str + i)))
			i++;
		else if (*(str + i) == '.')
			i = size_dot_count(str, i);
		else if (*(str + i) == '*')
			i = size_star_count(str, i);
		else if (ft_isdigit(*(str + i)))
			i = size_bucks_count(str, i);
		else
		{
			t_lres.error_counter++;
			i++;
		}
	}
	size_count_resulter(str, i);
	if (cs_check(*(str + i)) == 1)
		return (i + 1);
	return (i);
}

void	size_count(const char *str)
{
	int i;

	i = 0;
	size_counter_reset();
	while (*(str + i))
	{
		if (*(str + i) == '%' && *(str + i + 1) != '\0')
			i = size_cs_runner(str, i + 1);
		else
			i++;
	}
}
