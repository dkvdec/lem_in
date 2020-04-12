/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_frc_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:20:02 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 17:54:01 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int			frc_arr_fill(char **str, int k, int i, int lim)
{
	int j;

	j = 100000000;
	if (lim == 0)
	{
		while (j > 0)
		{
			*((*str) + k++) = (t_buff.nbr[i] / j) + 48;
			t_buff.nbr[i] %= j;
			j /= 10;
		}
	}
	else
		while (j > 0 && lim-- > 0)
		{
			*((*str) + k++) = (t_buff.nbr[i] / j) + 48;
			t_buff.nbr[i] %= j;
			j /= 10;
		}
	return (k);
}

void		frc_arr_make(int i, int j)
{
	int		len;
	char	*str;
	int		k;
	int		c;

	len = i * 9 + j;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return ;
	t_result.fract_len = len;
	str[len] = 0;
	len -= j;
	k = 0;
	c = 0;
	while (k < len && c < i)
		k = frc_arr_fill(&str, k, c++, 0);
	k = frc_arr_fill(&str, k, c, j);
	t_result.fract = str;
}

void		frc_arr_size(void)
{
	int i;
	int j;
	int size;

	i = t_buff.lim;
	while (t_buff.nbr[i] == 0)
		i--;
	size = 10;
	j = 9;
	while (t_buff.nbr[i] % size == 0)
	{
		size *= 10;
		j--;
	}
	frc_arr_make(i, j);
}
