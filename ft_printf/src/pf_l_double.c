/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_l_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:41:16 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 17:47:48 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		get_lpositive(int len)
{
	int cpower;
	int lpower;
	int i;

	t_comp.int_len = len;
	if (!(t_comp.integ = malloc(sizeof(int) * len--)))
		return ;
	t_comp.integ[len--] = t_comp.exp;
	cpower = t_comp.exp - 1;
	lpower = cpower - 62;
	i = 62;
	while (cpower >= lpower && i > -1 && len > -1)
	{
		if (t_recon.mant >> i & 1)
			t_comp.integ[len--] = cpower;
		i--;
		cpower--;
	}
}

void		get_lnegative(int len)
{
	int cpower;
	int lpower;
	int limit;
	int i;

	if ((limit = t_comp.int_len) == 0)
		t_comp.frc_len = len;
	if (!(t_comp.fract = malloc(sizeof(int) * len--)))
		return ;
	if (t_comp.int_len == 0)
		t_comp.fract[0] = t_comp.exp;
	cpower = t_comp.exp - 1;
	lpower = cpower - 62;
	i = 62;
	len = (t_comp.int_len == 0) ? 1 : 0;
	while (cpower >= lpower && i > -1)
	{
		if (t_recon.mant >> i & 1 && --limit <= 0)
			t_comp.fract[len++] = cpower;
		i--;
		cpower--;
	}
}

void		get_lhybrid(int dif)
{
	int int_len;
	int frc_len;

	int_len = dif * (-1);
	frc_len = 64 + dif;
	t_comp.int_len = ft_bitlen(t_recon.mant >> int_len);
	t_comp.frc_len = ft_bitlen(t_recon.mant << frc_len);
	get_lpositive(t_comp.int_len);
	get_lnegative(t_comp.frc_len);
}

void		get_lpowers(void)
{
	int dif;
	int len;

	t_comp.exp = t_recon.exp - 16383;
	dif = t_comp.exp - 63;
	len = ft_bitlen(t_recon.mant);
	t_comp.int_len = 0;
	t_comp.frc_len = 0;
	if (dif < 0)
	{
		if (t_comp.exp < 0)
			get_lnegative(len);
		else
			get_lhybrid(dif);
	}
	else
	{
		get_lpositive(len);
	}
}

void		get_ldouble(void)
{
	t_result.inter = NULL;
	t_result.fract = NULL;
	t_result.inter_len = 0;
	t_result.fract_len = 0;
	if (t_comp.int_len > 0)
	{
		buff_zero();
		t_buff.lim = 549;
		int_start();
		int_arr_size();
	}
	if (t_comp.frc_len > 0)
	{
		buff_zero();
		t_buff.lim = 1821;
		frc_start();
		frc_arr_size();
	}
	double_collector_full();
	clean_double();
}
