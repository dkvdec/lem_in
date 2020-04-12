/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_flag_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:14:33 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:29:08 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		reset_f(void)
{
	t_f.h = 0;
	t_f.l = 0;
	t_f.jz = 0;
	t_f.lb = 0;
	t_f.sh = 0;
	t_f.z = 0;
	t_f.m = 0;
	t_f.pl = 0;
	t_f.sp = 0;
	t_f.w = 0;
	t_f.pz = 0;
	t_f.pr = 0;
	t_f.b = 0;
	t_type.s = 0;
	t_type.ds = 0;
}

int			easy_flags(char c)
{
	if (c == 'L' || c == '#' || c == '0'
	|| c == '-' || c == '+' || c == ' '
	|| c == '\'')
	{
		return (1);
	}
	return (0);
}

void		flag_recognition(char c)
{
	t_f.lb = (c == 'L') ? t_f.lb + 1 : t_f.lb;
	t_f.sh = (c == '#') ? t_f.sh + 1 : t_f.sh;
	t_f.z = (c == '0') ? t_f.z + 1 : t_f.z;
	t_f.m = (c == '-') ? t_f.m + 1 : t_f.m;
	t_f.pl = (c == '+') ? t_f.pl + 1 : t_f.pl;
	t_f.sp = (c == ' ') ? t_f.sp + 1 : t_f.sp;
}

void		hl_recognition(char *str, int i)
{
	if (*(str + i) == 'h' && t_f.jz == 0 && t_f.l == 0)
	{
		t_f.h = (*(str + i - 1) == 'h') ? t_f.h + 1 : 1;
	}
	else if (*(str + i) == 'l' && t_f.jz == 0)
	{
		t_f.h = 0;
		t_f.l = (*(str + i - 1) == 'l') ? t_f.l + 1 : 1;
	}
	else if (*(str + i) == 'j' || *(str + i) == 'z')
	{
		t_f.h = 0;
		t_f.l = 2;
		t_f.jz++;
	}
}

int			grep_nbr(char *str, int i)
{
	int j;

	j = 0;
	while (*(str + i + j) && ft_isdigit(*(str + i + j)))
		j++;
	if (*(str + i + j) == '$')
	{
		t_f.b = ft_atoi(str + i);
		i += j;
	}
	else
	{
		t_f.w = ft_atoi(str + i);
		i += j - 1;
	}
	return (i);
}
