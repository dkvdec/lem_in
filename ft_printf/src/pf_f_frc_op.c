/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_frc_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:18:22 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 16:48:49 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		frc_pwr(void)
{
	int i;
	int add;

	i = 0;
	add = 0;
	while (i < t_buff.lim)
	{
		if (add > 0)
		{
			t_buff.pwr[i] += add * 1000000000;
			add = 0;
		}
		if (t_buff.pwr[i] % 2 > 0)
			add = t_buff.pwr[i] % 2;
		t_buff.pwr[i] /= 2;
		i++;
	}
}

void		frc_add(void)
{
	int i;
	int add;

	i = t_buff.lim - 1;
	add = 0;
	while (i >= 0)
	{
		if (add > 0)
		{
			t_buff.nbr[i] += add;
			add = 0;
		}
		t_buff.nbr[i] += t_buff.pwr[i];
		if (t_buff.nbr[i] > 999999999)
		{
			add = t_buff.nbr[i] / 1000000000;
			t_buff.nbr[i] %= 1000000000;
		}
		i--;
	}
}

void		frc_start(void)
{
	int pwr;
	int i;

	pwr = -1;
	i = 0;
	t_buff.pwr[0] = 500000000;
	while (i < t_comp.frc_len)
	{
		if (pwr == t_comp.fract[i])
		{
			frc_add();
			i++;
		}
		frc_pwr();
		pwr--;
	}
}
