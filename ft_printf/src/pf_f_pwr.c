/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_pwr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:08:06 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 16:59:47 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		get_positive(int len)
{
	int cpower;
	int lpower;
	int i;

	t_comp.int_len = len;
	if (!(t_comp.integ = malloc(sizeof(int) * len--)))
		return ;
	t_comp.integ[len--] = t_comp.exp;
	cpower = t_comp.exp - 1;
	lpower = cpower - 51;
	i = 51;
	while (cpower >= lpower && i > -1 && len > -1)
	{
		if (t_recon.mant >> i & 1)
			t_comp.integ[len--] = cpower;
		i--;
		cpower--;
	}
}

void		get_negative(int len)
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
	lpower = cpower - 51;
	i = 51;
	len = (t_comp.int_len == 0) ? 1 : 0;
	while (cpower >= lpower && i > -1)
	{
		if (t_recon.mant >> i & 1 && --limit <= 0)
			t_comp.fract[len++] = cpower;
		i--;
		cpower--;
	}
}

void		get_hybrid(int dif)
{
	int int_len;
	int frc_len;

	int_len = dif * (-1);
	frc_len = 52 + dif + 12;
	t_comp.int_len = ft_bitlen(t_recon.mant >> int_len) + 1;
	t_comp.frc_len = ft_bitlen(t_recon.mant << frc_len);
	get_positive(t_comp.int_len);
	get_negative(t_comp.frc_len);
}

void		get_powers(void)
{
	int dif;
	int len;

	t_comp.exp = t_recon.exp - 1023;
	dif = t_comp.exp - 52;
	len = ft_bitlen(t_recon.mant) + 1;
	t_comp.int_len = 0;
	t_comp.frc_len = 0;
	if (dif < 0)
	{
		if (t_comp.exp < 0)
			get_negative(len);
		else
			get_hybrid(dif);
	}
	else
	{
		get_positive(len);
	}
}

void		l_inf_nan(void)
{
	t_f.z = 0;
	if ((t_recon.mant << 1) == 0)
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
