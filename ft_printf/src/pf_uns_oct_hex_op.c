/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_uns_oct_hex_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 00:30:49 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:06:06 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

/*
** **************************** UNS_OCT_HEX_PROTO ***************************
** t_f.h = DO_DO_DO <<<
** t_f.l = DO_DO_DO <<<
** t_f.L = IGNORE
** t_f.sh = IGNORE
** t_f.z = DO_DO_DO <<<
** t_f.m = DO_DO_DO <<<
** t_f.plus = IGNORE
** t_f.space = IGNORE
** t_f.pr = DO_DO_DO <<<
** t_f.w = DO_DO_DO <<<
** t_f.quote = IGNORE
*/

int		ltoa_base_nbr_size(unsigned long long int nb, int base)
{
	int i;

	i = 1;
	while ((nb = nb / base) != 0)
		i++;
	return (i);
}

int		ltoa_base_prec_proc(unsigned long long int nb, int nbl, int base)
{
	int pre;

	if (nbl < t_f.pr)
		pre = t_f.pr - nbl;
	else
		pre = 0;
	if ((t_f.sh > 0 && base == 16 && nb > 0) || t_f.sh == 978)
		pre += 2;
	else if (t_f.sh > 0 && base == 8
		&& pre == 0 && ((t_f.pr == 0 && t_f.pz > 0) || (nb > 0)))
		pre = 1;
	return (pre);
}

void	ltoa_base_prec_fill(char **str, int base, int pre)
{
	int i;

	i = 0;
	if (t_f.sh > 0 && base == 16)
	{
		*(*(str) + i++) = '0';
		*(*(str) + i++) = 'X';
	}
	while (i < pre)
		*(*(str) + i++) = '0';
}

char	*ltoa_base_prec(unsigned long long int nb, int base)
{
	char	*str;
	int		nbl;
	int		pre;

	nbl = ltoa_base_nbr_size(nb, base);
	if (nb == 0 && t_f.pr == 0 && t_f.pz > 0)
		nbl = 0;
	pre = ltoa_base_prec_proc(nb, nbl, base);
	if (pre + nbl >= t_f.w)
		t_f.w = 0;
	if (!(str = ft_strnew(pre + nbl)))
		return (NULL);
	if (pre > 0)
		ltoa_base_prec_fill(&str, base, pre);
	while (nb / base != 0 && nbl > 0)
	{
		*(str + pre + nbl-- - 1) = (nb % base) + ((nb % base > 9) ? 55 : 48);
		nb = nb / base;
	}
	if (!(nb == 0 && t_f.pr == 0 && t_f.pz > 0))
		*(str + pre + nbl - 1) = (nb % base) + ((nb % base > 9) ? 55 : 48);
	return (str);
}

void	ltoa_base_flag_proc(unsigned long long int nb, int base)
{
	if (nb == 0 && t_f.sh > 0 && base == 16 && t_f.sh != 978)
		t_f.sh = 0;
	if (t_f.pr == 0 && t_f.m == 0
		&& t_f.z > 0 && t_f.w > 1
		&& t_f.pz == 0)
	{
		t_f.pr = t_f.w + ((base == 16 && t_f.sh > 0) ? -2 : 0);
		t_f.w = 0;
	}
}
