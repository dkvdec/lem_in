/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:16:51 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 16:59:52 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int			ft_bitlen(unsigned long mant)
{
	int i;

	i = 0;
	while (mant != 0)
	{
		mant = (mant - 1) & mant;
		i++;
	}
	return (i);
}

void		buff_zero(void)
{
	int i;

	i = 0;
	while (i < 1821)
	{
		t_buff.pwr[i] = 0;
		t_buff.nbr[i++] = 0;
	}
}

void		clean_double(void)
{
	if (t_comp.integ)
		free(t_comp.integ);
	t_comp.integ = NULL;
	if (t_comp.fract)
		free(t_comp.fract);
	t_comp.fract = NULL;
	if (t_result.inter)
		free(t_result.inter);
	t_result.inter = NULL;
	if (t_result.fract)
		free(t_result.fract);
	t_result.fract = NULL;
}

char		get_sign(void)
{
	if (t_recon.sign)
		return ('-');
	else if (t_f.pl)
		return ('+');
	else if (t_f.sp)
		return (' ');
	else
		return (0);
}

void		inf_nan(void)
{
	t_f.z = 0;
	if (t_recon.mant == 0)
	{
		if (t_recon.sign)
			pf_str("-inf");
		else if (t_f.pl > 0)
			pf_str("+inf");
		else if (t_f.sp > 0)
			pf_str(" inf");
		else
			pf_str("inf");
	}
	else
		pf_str("nan");
}
