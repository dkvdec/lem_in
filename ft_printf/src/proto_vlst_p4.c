/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_p4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:50:05 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/25 22:58:28 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void	get_dargs(va_list vl)
{
	double			f;
	double			*ff;
	long double		l;
	long double		*ll;

	if (t_connect.current->type == 5)
	{
		f = va_arg(vl, double);
		ff = malloc(sizeof(double));
		*ff = f;
		t_connect.current->value = ff;
	}
	else if (t_connect.current->type == 6)
	{
		l = va_arg(vl, long double);
		ll = malloc(sizeof(long double));
		*ll = l;
		t_connect.current->value = ll;
	}
}

void	get_args(va_list vl)
{
	vlst_walk(1);
	while (t_connect.current != NULL)
	{
		if (t_connect.current->type == 1)
			t_connect.current->value = (void*)va_arg(vl, unsigned long long);
		else if (t_connect.current->type == 2)
			t_connect.current->value = (void*)va_arg(vl, long long);
		else if (t_connect.current->type == 3)
			t_connect.current->value = (void*)va_arg(vl, int*);
		else if (t_connect.current->type == 4)
			t_connect.current->value = (void*)va_arg(vl, char*);
		else if (t_connect.current->type == 5 || t_connect.current->type == 6)
			get_dargs(vl);
		else if (t_connect.current->type == 7)
			t_connect.current->value = (void*)va_arg(vl, void*);
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
		else
			break ;
	}
}
