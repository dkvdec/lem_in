/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_type_p2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:20:10 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:29:41 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void	type_reset(void)
{
	t_type.dsnb = 0;
	t_type.ds = 0;
	t_type.snb = 0;
	t_type.s = 0;
	t_type.nb = 0;
	t_type.lb = 0;
}

int		type_catcher(char c)
{
	if (c == 'b' || c == 'o' || c == 'u'
	|| c == 'U' || c == 'x' || c == 'X')
		return (1);
	if (c == 'd' || c == 'i')
		return (2);
	if (c == 'c')
		return (3);
	if (c == 's')
		return (4);
	if ((c == 'f' || c == 'F') && t_type.lb == 0)
		return (5);
	if ((c == 'f' || c == 'F') && t_type.lb > 0)
		return (6);
	if (c == 'p')
		return (7);
	return (0);
}

int		type_dot_check(const char *str, int i)
{
	int j;

	j = 1;
	if (*(str + i + j) == '*')
	{
		if (ft_isdigit(*(str + i + ++j)))
		{
			while (*(str + i + j) && ft_isdigit(*(str + i + j)))
				j++;
			if (*(str + i + j) == '$')
			{
				t_type.ds = 0;
				t_type.dsnb = ft_atoi(str + i + 1);
				i += j;
			}
		}
		else
		{
			t_type.dsnb = 0;
			t_type.ds = (t_type.s > 0) ? t_type.s + 1 : 1;
			i++;
		}
	}
	return (i + 1);
}
