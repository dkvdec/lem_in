/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:32:10 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:12:11 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		pf_core_helper(char **str, int *i)
{
	if (*i > 0)
		safe_sub_join(*str, *i);
	(*i) = flag_passer(*str, ++(*i));
	if ((*i) < 0)
		(*str) += (-1) * (*i);
	else
	{
		pre_get_value(*((*str) + (*i)));
		(*str) += ++(*i);
	}
	(*i) = 0;
}

void		pf_core(char *str)
{
	int i;

	i = 0;
	t_line.out = ft_strnew(0);
	while (*(str + i))
	{
		if (*(str + i) == '{' && colour_check(str, i))
		{
			safe_sub_join(str, i);
			colour_join(*(str + i + 1), *(str + i + 2));
			str += (i + 4);
			i = 0;
		}
		else if (*(str + i) == '%')
			pf_core_helper(&str, &i);
		else if (!(*(str + i + 1)))
		{
			safe_sub_join(str, i + 1);
			break ;
		}
		else
			i++;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list	vl;
	int		i;
	char	*str;

	size_count(format);
	if ((i = size_max_finder()) > 0)
		t_connect.current = vlst_make(i);
	else
		t_connect.current = NULL;
	type_cs_runner(format);
	type_equalizer();
	va_start(vl, format);
	get_args(vl);
	va_end(vl);
	vlst_walk(1);
	t_line.len = 0;
	str = (char *)format;
	pf_core(str);
	write(1, t_line.out, t_line.len);
	vlst_dstr();
	free(t_line.out);
	t_line.out = NULL;
	return (t_line.len);
}
