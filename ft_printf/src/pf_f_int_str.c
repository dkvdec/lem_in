/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_int_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:20:15 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 16:47:20 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int			int_arr_fill(char **str, int k, int i, int lim)
{
	int j;

	j = 100000000;
	if (lim != 0)
		while (lim-- != 0)
			j /= 10;
	while (j > 0 && (t_buff.nbr[i] / j == 0))
	{
		*((*str) + k++) = 48;
		j /= 10;
	}
	while (j > 0)
	{
		*((*str) + k++) = (t_buff.nbr[i] / j) + 48;
		t_buff.nbr[i] %= j;
		j /= 10;
	}
	return (k);
}

void		int_arr_make(int i, int j)
{
	int		len;
	char	*str;
	int		k;

	len = i * 9 + j;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return ;
	t_result.inter_len = len;
	str[len] = 0;
	k = int_arr_fill(&str, 0, i--, 9 - j);
	while (k < len && i >= 0)
		k = int_arr_fill(&str, k, i--, 0);
	t_result.inter = str;
}

void		int_arr_size(void)
{
	int		i;
	int		j;
	int		size;

	i = t_buff.lim;
	while (t_buff.nbr[i] == 0)
		i--;
	size = 1000000000;
	j = 10;
	while (t_buff.nbr[i] / size == 0)
	{
		size /= 10;
		j--;
	}
	int_arr_make(i, j);
}
