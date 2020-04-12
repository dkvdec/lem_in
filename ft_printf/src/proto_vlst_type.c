/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:51:56 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:20:38 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int		type_star_check(const char *str, int i)
{
	int j;

	j = 1;
	if (ft_isdigit(*(str + i + j)))
	{
		while (*(str + i + j) && ft_isdigit(*(str + i + j)))
			j++;
		if (*(str + i + j) == '$')
		{
			t_type.s = 0;
			t_type.snb = ft_atoi(str + i + 1);
			i += j;
		}
	}
	else
	{
		t_type.snb = 0;
		t_type.s = (t_type.ds > 0) ? t_type.ds + 1 : 1;
	}
	return (i + 1);
}

int		type_bucks_check(const char *str, int i)
{
	int j;

	j = 0;
	while (*(str + i + j) && ft_isdigit(*(str + i + j)))
	{
		j++;
	}
	if (*(str + i + j) == '$')
	{
		t_type.nb = ft_atoi(str + i);
		i++;
	}
	i += j;
	return (i);
}

void	type_resulter(const char *str, int i)
{
	if (t_type.snb > 0)
		vlst_starbucks(t_type.snb);
	if (t_type.dsnb > 0)
		vlst_starbucks(t_type.dsnb);
	if (t_type.s > 0)
	{
		t_connect.current->type = 1;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
	if (t_type.ds > 0)
	{
		t_connect.current->type = 1;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
	if (t_type.nb != 0)
		vlst_walk(t_type.nb);
	t_connect.current->type = type_catcher(*(str + i));
	if (t_connect.current->next != NULL && *(str + i) != '%')
		t_connect.current = t_connect.current->next;
}

int		type_get(const char *str, int i)
{
	type_reset();
	while (*(str + i) && cs_check(*(str + i)) != 1)
	{
		if (!(skip_able(*(str + i))))
			return (i);
		else if (skipable(*(str + i)))
			i++;
		else if (*(str + i) == '.')
			i = type_dot_check(str, i);
		else if (*(str + i) == '*')
			i = type_star_check(str, i);
		else if (ft_isdigit(*(str + i)))
			i = type_bucks_check(str, i);
		else
			i++;
	}
	type_resulter(str, i);
	return (i + 1);
}

void	type_cs_runner(const char *str)
{
	int	i;

	i = 0;
	if (t_connect.current == NULL)
		return ;
	while (*(str + i))
	{
		if (*(str + i) == '%' && *(str + i + 1) != '\0')
		{
			if (*(str + i + 1) == '%')
				i++;
			else
			{
				i = type_get(str, i + 1);
				continue ;
			}
		}
		i++;
	}
}
