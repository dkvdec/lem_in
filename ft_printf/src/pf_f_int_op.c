/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_int_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:16:19 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 16:47:16 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		int_pwr(void)
{
	int i;
	int add;

	i = 0;
	add = 0;
	while (i < t_buff.lim)
	{
		t_buff.pwr[i] *= 2;
		if (add > 0)
		{
			t_buff.pwr[i] += add;
			add = 0;
		}
		if (t_buff.pwr[i] > 999999999)
		{
			add = t_buff.pwr[i] / 1000000000;
			t_buff.pwr[i] %= 1000000000;
		}
		i++;
	}
}

void		int_add(void)
{
	int i;
	int add;

	i = 0;
	add = 0;
	while (i < t_buff.lim)
	{
		t_buff.nbr[i] += t_buff.pwr[i];
		if (add > 0)
		{
			t_buff.nbr[i] += add;
			add = 0;
		}
		if (t_buff.nbr[i] > 999999999)
		{
			add = t_buff.nbr[i] / 1000000000;
			t_buff.nbr[i] %= 1000000000;
		}
		i++;
	}
}

void		int_start(void)
{
	int pwr;
	int i;

	pwr = 0;
	i = 0;
	t_buff.pwr[0] = 1;
	while (i < t_comp.int_len)
	{
		if (pwr == t_comp.integ[i])
		{
			int_add();
			i++;
		}
		int_pwr();
		pwr++;
	}
}
