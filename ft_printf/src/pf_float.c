/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:27:14 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 16:54:38 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

/*
** **************************** UNS_OCT_HEX_PROTO ***************************
** t_f.L = DO_DO_DO <<< double / long double
** t_f.sh = DO_DO_DO <<< works only when pz > 0
** t_f.z = DO_DO_DO <<< works when width and  - = 0
** t_f.m = DO_DO_DO <<< works if width works
** t_f.plus = DO_DO_DO <<< works always, kills space
** t_f.space = DO_DO_DO <<< works if space = 0
** t_f.pr = DO_DO_DO <<<
** t_f.w = DO_DO_DO <<< works if > int len
*/

void		double_collector_full(void)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	len = t_result.fract_len + 1;
	len += ((t_result.inter_len == 0) ? 1 : t_result.inter_len);
	if (!(str = ft_strnew(len)))
		return ;
	i = 0;
	if (t_result.inter_len == 0)
		str[i++] = '0';
	else
		while (i < t_result.inter_len)
		{
			str[i] = t_result.inter[i];
			i++;
		}
	str[i++] = '.';
	j = 0;
	while (i < len)
		str[i++] = t_result.fract[j++];
	t_result.inter_len = (t_result.inter_len == 0) ? 1 : t_result.inter_len;
	t_result.full_nbr = str;
}

void		get_double(void)
{
	t_result.inter = NULL;
	t_result.fract = NULL;
	t_result.inter_len = 0;
	t_result.fract_len = 0;
	if (t_comp.int_len > 0)
	{
		buff_zero();
		t_buff.lim = 35;
		int_start();
		int_arr_size();
	}
	if (t_comp.frc_len > 0)
	{
		buff_zero();
		t_buff.lim = 114;
		frc_start();
		frc_arr_size();
	}
	double_collector_full();
	clean_double();
}

void		dbl_flag_proc(int zero)
{
	dbl_flag_preproc(zero);
	if (t_f.pr < t_result.fract_len)
		dbl_round();
	else if (t_f.pr > t_result.fract_len)
		tail_extender('0');
	dbl_flag_aftproc();
	if (t_f.w > (int)ft_strlen(t_result.full_nbr))
	{
		if (t_f.m > 0)
		{
			if (t_recon.sign || t_f.pl || t_f.sp)
				head_extender(0);
			tail_extender(' ');
		}
		else
			head_extender((t_f.z > 0) ? '0' : ' ');
	}
	else if (t_recon.sign || t_f.pl || t_f.sp)
		head_extender(0);
	safe_join(&t_result.full_nbr, t_f.w);
}

void		pf_double(void)
{
	double			d;
	unsigned long	nb;

	d = *(double*)t_connect.current->value;
	free(t_connect.current->value);
	ft_bzero(&nb, 8);
	ft_memcpy(&nb, &d, 8);
	t_recon.sign = nb >> 63 & 1;
	t_recon.exp = nb >> 52 & 0x7FF;
	t_recon.mant = nb & 0xFFFFFFFFFFFFF;
	if (d == 0.0)
	{
		dbl_flag_proc(1);
		return ;
	}
	if (t_recon.exp > 2046)
	{
		inf_nan();
		return ;
	}
	get_powers();
	get_double();
	dbl_flag_proc(0);
}

void		pf_ldouble(void)
{
	long double			ld;
	__uint128_t			nb;

	ld = *(long double*)t_connect.current->value;
	free(t_connect.current->value);
	ft_bzero(&nb, 16);
	ft_memcpy(&nb, &ld, 16);
	t_recon.sign = nb >> 79 & 1;
	t_recon.exp = nb >> 64 & 0x7FFF;
	t_recon.mant = nb & 0xFFFFFFFFFFFFFFFF;
	if (ld == 0.0)
	{
		dbl_flag_proc(1);
		return ;
	}
	if (t_recon.exp > 32766)
	{
		l_inf_nan();
		return ;
	}
	get_lpowers();
	get_ldouble();
	dbl_flag_proc(0);
}
