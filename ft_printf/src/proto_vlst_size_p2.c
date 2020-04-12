/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_size_p2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:17:52 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:19:33 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int		size_max_finder(void)
{
	int i;

	i = t_lres.l_counter;
	i = (i < t_lres.mb_counter) ? t_lres.mb_counter : i;
	i = (i < t_lres.sb_c) ? t_lres.sb_c : i;
	return (i);
}

void	size_counter_reset(void)
{
	t_lres.l_counter = 0;
	t_lres.mb_counter = 0;
	t_lres.sb_c = 0;
	t_lres.error_counter = 0;
}

void	size_flag_reset(void)
{
	t_lres.dot_flag = 0;
	t_lres.star_flag = 0;
	t_lres.bucks_flag = 0;
}

int		size_dot_count(const char *str, int i)
{
	int j;
	int tmp;

	i++;
	j = 0;
	if (*(str + i) == '*')
	{
		t_lres.dot_flag++;
		i++;
		if (ft_isdigit(*(str + i)))
		{
			while (*(str + i + j) && ft_isdigit(*(str + i + j)))
				j++;
			if (*(str + i + j) == '$')
			{
				tmp = ft_atoi(str + i);
				t_lres.sb_c = (tmp > t_lres.sb_c) ? tmp : t_lres.sb_c;
				j++;
				t_lres.dot_flag = 0;
			}
		}
	}
	i += j;
	return (i);
}
