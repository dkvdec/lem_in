/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:03:27 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:03:53 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void	ltoa_flag_proc(long long n)
{
	long i;

	if (t_f.pr == 0 && t_f.m == 0
		&& t_f.z > 0 && t_f.w > 1
		&& t_f.pz == 0)
	{
		i = (n < 0 || t_f.pl > 0 || t_f.sp > 0) ? 1 : 0;
		t_f.pr = t_f.w - i;
		t_f.w = 0;
	}
}

void	pf_dec(long long n, int b)
{
	char *s;
	char *tmp;

	s = NULL;
	if (t_f.h > 0 && t_f.h % 2 == 0)
		s = ltoa_dec_prec((char)n, b);
	else if (t_f.h > 0 && t_f.h % 2 == 1)
		s = ltoa_dec_prec((short)n, b);
	else if (t_f.l > 0 && t_f.l % 2 == 1)
		s = ltoa_dec_prec((signed long)n, b);
	else if (t_f.l > 0 && t_f.l % 2 == 0)
		s = ltoa_dec_prec((signed long long)n, b);
	else
		s = ltoa_dec_prec((signed int)n, b);
	if (t_f.w > 0)
	{
		tmp = ltoa_width(s);
		if (tmp != NULL)
		{
			free(s);
			s = tmp;
		}
	}
	safe_join(&s, ft_strlen(s));
}
