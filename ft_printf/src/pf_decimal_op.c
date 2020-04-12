/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:52:54 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:03:55 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

/*
** *************************** DEC_PROTO ****************************
** t_f.h = DO_DO_DO
** t_f.l = DO_DO_DO
** t_f.L = IGNORE
** t_f.sharp = IGNORE
** t_f.z = w sub parameter, works oly if w > pr pr and m is off
** t_f.m = pr sub parameter, works oly if w > pr
** t_f.pl = pr secret parameter,
**		always adds a sign before pr part(hidden +1 in w,kills sp)
** t_f.sp = w secret parameter, if there is sp for + and sp
**						| >= len | < len |
** t_f.w = 		| IGNORE | if w =< pr then ignored |
** t_f.pr =	| IGNORE | works always						  |
** t_f.quote = <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

int		ltoa_nbr_size(long long n, int b)
{
	int i;

	i = 1;
	while ((n = n / b) != 0)
		i++;
	return (i);
}

int		ltoa_prec_proc(int l, int g)
{
	int p;

	if (l < t_f.pr)
		p = t_f.pr - l;
	else
		p = 0;
	if (g < 0 || t_f.pl > 0 || t_f.sp > 0)
		p++;
	return (p);
}

void	ltoa_prec_fill(char **s, int g, int p)
{
	int i;

	i = 0;
	if (g < 0)
		**(s + i++) = '-';
	else if (t_f.pl > 0)
		**(s + i++) = '+';
	else if (t_f.sp > 0)
		**(s + i++) = ' ';
	while (i < p)
		*((*s) + i++) = '0';
}

char	*ltoa_dec_prec(long long n, int b)
{
	char	*s;
	int		l;
	int		p;
	int		g;

	ltoa_flag_proc(n);
	g = (n < 0) ? -1 : 1;
	l = ltoa_nbr_size(n, b);
	if (n == 0 && t_f.pr == 0 && t_f.pz > 0)
		l = 0;
	p = ltoa_prec_proc(l, g);
	if (p + l >= t_f.w)
		t_f.w = 0;
	if (!(s = ft_strnew(p + l)))
		return (NULL);
	if (p > 0)
		ltoa_prec_fill(&s, g, p);
	while (n / b != 0 && l > 0)
	{
		*(s + p + l-- - 1) = ((n % b) * g) + (((n % b) * g > 9) ? 55 : 48);
		n = n / b;
	}
	if (!(n == 0 && t_f.pr == 0 && t_f.pz > 0))
		*(s + p + l - 1) = ((n % b) * g) + (((n % b) * g > 9) ? 55 : 48);
	return (s);
}

char	*ltoa_width(char *s)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	len = ft_strlen(s);
	if (t_f.w > len)
	{
		if (!(new = ft_strnew(t_f.w)))
			return (NULL);
		i = 0;
		while (i < t_f.w)
			new[i++] = ' ';
		i = (t_f.m > 0) ? 0 : t_f.w - len;
		j = 0;
		while (i < t_f.w && s[j])
			new[i++] = s[j++];
		return (new);
	}
	return (NULL);
}
