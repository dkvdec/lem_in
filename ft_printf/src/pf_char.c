/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:16:18 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 22:45:50 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

/*
** ***************************** CHAR_PROTO *******************************
**
** t_f.h = DO_DO_DO
** t_f.l = DO_DO_DO
** t_f.L = IGNORE
** t_f.sh = IGNORE
** t_f.z = DO_DO_DO
** t_f.m = DO_DO_DO
** t_f.plus = DO_DO_DO
** t_f.space = DO_DO_DO
** t_f.pr = DO_DO_DO
** t_f.w = DO_DO_DO
** t_f.quote = DO_DO_DO
*/

void		pf_char(int c)
{
	char	*res;
	int		i;

	t_f.w = (t_f.w > 0) ? t_f.w : 1;
	i = t_f.w;
	if (!(res = ft_strnew(t_f.w)))
		return ;
	if (t_f.z > 0 && t_f.m == 0)
		while (--i >= 0)
			res[i] = '0';
	else
		while (--i >= 0)
			res[i] = ' ';
	if (t_f.m > 0)
		res[0] = c;
	else
		res[t_f.w - 1] = c;
	safe_join(&res, t_f.w);
}

/*
** **************************** STR_PROTO *****************************
**
** t_f.h = IGNORE
** t_f.l = IGNORE
** t_f.L = IGNORE
** t_f.sh = IGNORE
** t_f.z = DO_DO_DO <<<
** t_f.m = DO_DO_DO <<<
** t_f.plus = IGNORE
** t_f.space = IGNORE
** t_f.pr =  if larger then strlen, then strlen,
**						 if smaller then strlen, then pr<<<
** t_f.w = minimal w, if str is lager, then ignored <<<
** t_f.quote = IGNORE
*/

void		pf_str(char *str)
{
	char	*res;
	int		i;

	if (str == NULL)
		str = "(null)";
	i = ft_strlen(str);
	t_f.pr = ((t_f.pz > 0 || t_f.pr > 0) && t_f.pr < i) ? t_f.pr : i;
	t_f.w = (t_f.w > 0 && t_f.w > t_f.pr) ? t_f.w : t_f.pr;
	if (!(res = ft_strnew(t_f.w)))
		return ;
	i = t_f.w;
	if (t_f.z > 0 && t_f.m == 0)
		while (--i >= 0)
			res[i] = '0';
	else
		while (--i >= 0)
			res[i] = ' ';
	if (t_f.m > 0)
		res = ft_strncpy(res, str, t_f.pr);
	else
	{
		res = ft_strncpy((res + (t_f.w - t_f.pr)), str, t_f.pr);
		res -= (t_f.w - t_f.pr);
	}
	safe_join(&res, t_f.w);
}

/*
****************************** PTR_PROTO *****************************
**
** t_f.h = IGNORE
** t_f.l = IGNORE
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

void		pf_ptr(unsigned long long int nbr, int base, int tl)
{
	t_f.sh = 978;
	t_f.h = 0;
	t_f.l = 1;
	pf_uns_oct_hex(nbr, base, tl);
}
