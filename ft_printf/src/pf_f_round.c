/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_round.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:10:27 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:10:52 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		heavy_round(void)
{
	int		len;
	char	*str;

	len = t_result.inter_len + t_result.fract_len + 2;
	if (!(str = ft_strnew(len)))
		return ;
	str[0] = '1';
	t_result.inter_len++;
	while (len >= 1)
	{
		str[len] = t_result.full_nbr[len - 1];
		len--;
	}
	free(t_result.full_nbr);
	t_result.full_nbr = str;
}

int			long_round(int i, int rest)
{
	while (i >= 0 && t_result.full_nbr[i] == '9')
	{
		t_result.full_nbr[i] = '0';
		if (i - 1 >= 0 && t_result.full_nbr[i - 1] == '.')
			i--;
		i--;
	}
	if (i < 0)
		heavy_round();
	else if (rest)
		t_result.full_nbr[i]++;
	return (i);
}

int			deep_explore(int j)
{
	while (t_result.full_nbr[++j])
	{
		if (t_result.full_nbr[j] > '0')
			return (1);
	}
	return (0);
}

void		dbl_round(void)
{
	int i;
	int rest;
	int j;

	i = t_result.inter_len + ((t_f.pr > 0) ? t_f.pr : -1);
	rest = t_result.full_nbr[i] % 2;
	j = (t_result.full_nbr[i + 1] == '.') ? i + 2 : i + 1;
	if (t_result.full_nbr[j] >= '5')
	{
		if (t_result.full_nbr[i] == '9')
			j = long_round(i, rest);
		else if (t_result.full_nbr[j] >= '6')
			t_result.full_nbr[i]++;
		else if (((rest || t_recon.sign) &&
		t_result.full_nbr[j] == '5') || deep_explore(j))
			t_result.full_nbr[i]++;
	}
	i += ((j < 0) ? 1 : 0) + ((t_result.fract_len > 0) ? 1 : 0);
	i += ((t_f.pr == 0 && t_f.pz > 0 && t_f.sh > 0) ? 1 : 0);
	while (t_result.full_nbr[i])
		t_result.full_nbr[i++] = 0;
	t_result.fract_len = t_f.pr;
}
