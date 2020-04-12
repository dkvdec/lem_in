/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_f_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:13:03 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 21:22:24 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		dbl_flag_preproc(int zero)
{
	char	*str;
	int		i;

	if (zero)
	{
		if (!(t_result.full_nbr = ft_strnew(8)))
			return ;
		str = "0.000000";
		i = -1;
		while (str[++i])
			t_result.full_nbr[i] = str[i];
		t_result.inter_len = 1;
		t_result.fract_len = 6;
	}
	if (t_f.pr == 0 && t_f.pz == 0)
		t_f.pr = 6;
}

void		dbl_flag_aftproc(void)
{
	int		rlen;

	rlen = t_result.inter_len + t_f.pr;
	rlen += ((t_recon.sign || t_f.pl || t_f.sp) ? 1 : 0);
	rlen += ((t_f.pz > 0 && t_f.pr == 0 && t_f.sh == 0) ? 0 : 1);
	if (t_f.w < rlen)
		t_f.w = rlen;
}

void		tail_extender(char c)
{
	int		len;
	int		i;
	char	*str;

	if (c == '0')
		len = t_result.inter_len + t_f.pr + 1;
	else
		len = t_f.w;
	if (!(str = ft_strnew(len--)))
		return ;
	i = t_result.inter_len + t_result.fract_len + ((t_f.pr > 0) ? 1 : 0);
	i += ((c != '0' && (t_recon.sign || t_f.pl || t_f.sp)) ? 1 : 0);
	i += ((t_f.pz && t_f.pr == 0 && t_f.sh > 0) ? 1 : 0);
	while (len >= i)
		str[len--] = c;
	while (--i >= 0)
		str[i] = t_result.full_nbr[i];
	if (c == '0')
		t_result.fract_len = t_f.pr;
	free(t_result.full_nbr);
	t_result.full_nbr = str;
}

int			head_helper(char **str, char c, int dif)
{
	int		i;
	char	sg;

	i = 0;
	sg = get_sign();
	if (c != ' ' && dif && sg)
	{
		dif--;
		(*str)[i++] = sg;
		sg = 0;
	}
	while (c != 0 && dif > 0)
	{
		(*str)[i++] = c;
		dif--;
	}
	if (c == ' ' && sg)
		(*str)[i - 1] = sg;
	return (i);
}

void		head_extender(char c)
{
	int		len;
	int		dif;
	char	*str;
	int		i;

	if (c == 0)
	{
		len = t_result.inter_len + ((get_sign() > 0) ? 1 : 0);
		len += ((t_result.fract_len > 0) ? t_result.fract_len + 1 : 0);
		len += ((t_f.pz > 0 && t_f.pr == 0 && t_f.sh > 0) ? 1 : 0);
	}
	else
		len = t_f.w;
	if (!(str = ft_strnew(len)))
		return ;
	i = t_result.inter_len;
	i += ((t_result.fract_len > 0) ? t_result.fract_len + 1 : 0);
	i += ((t_f.pr == 0 && t_f.pz > 0 && t_f.sh > 0) ? 1 : 0);
	dif = len - i;
	i = head_helper(&str, c, dif);
	dif = 0;
	while (i < len)
		str[i++] = t_result.full_nbr[dif++];
	free(t_result.full_nbr);
	t_result.full_nbr = str;
}
