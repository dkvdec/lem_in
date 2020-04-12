/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_uns_oct_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:05:24 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:05:56 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void	set_to_lower(char **str)
{
	int i;

	i = -1;
	while ((*str)[++i])
		(*str)[i] = ft_tolower((*str)[i]);
}

void	pf_uns_oct_hex(unsigned long long int nb, int base, int tl)
{
	char *str;
	char *tmp;

	ltoa_base_flag_proc(nb, base);
	if (t_f.h > 0 && t_f.h % 2 == 0)
		str = ltoa_base_prec((unsigned char)nb, base);
	else if (t_f.h > 0 && t_f.h % 2 == 1)
		str = ltoa_base_prec((unsigned short)nb, base);
	else if (t_f.l > 0 && t_f.l % 2 == 1)
		str = ltoa_base_prec((unsigned long)nb, base);
	else if (t_f.l > 0 && t_f.l % 2 == 0)
		str = ltoa_base_prec((unsigned long long)nb, base);
	else
		str = ltoa_base_prec((unsigned int)nb, base);
	if (tl == 1)
		set_to_lower(&str);
	if (t_f.w > 0)
	{
		tmp = ltoa_width(str);
		free(str);
		str = tmp;
	}
	safe_join(&str, ft_strlen(str));
}
