/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_core_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:11:48 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:28:39 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void		pre_get_vhelper(void)
{
	if (t_f.w < t_f.pr)
	{
		t_f.pr = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
		t_f.w = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
	else
	{
		t_f.w = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
		t_f.pr = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
}

void		pre_get_vtail(void)
{
	if (t_f.b > 0)
		vlst_walk(t_f.b);
	if (t_f.w < 0)
	{
		t_f.w *= (-1);
		t_f.m++;
	}
	if (t_f.pr < 0)
	{
		t_f.pr = 0;
		t_f.pz = 0;
	}
}

void		pre_get_turn(void)
{
	if (t_f.w >= 0 && t_type.s)
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	if (t_f.pr >= 0 && t_type.ds)
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
}

void		pre_get_value(char c)
{
	if (c == '\0')
		return ;
	if ((t_f.w >= 0 && t_type.s) || (t_f.pr >= 0 && t_type.ds))
		pre_get_turn();
	if (t_f.w < 0 && t_f.pr < 0)
		pre_get_vhelper();
	else if (t_f.w < 0)
	{
		t_f.w = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
	else if (t_f.pr < 0)
	{
		t_f.pr = (int)t_connect.current->value;
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
	}
	pre_get_vtail();
	get_value(c);
}

void		get_value(char c)
{
	if (c == '%')
		pf_char('%');
	else if (c == 'c')
		pf_char(((int)t_connect.current->value));
	else if (c == 's')
		pf_str((char *)t_connect.current->value);
	else if (c == 'p')
		pf_ptr((unsigned long long int)t_connect.current->value, 16, 1);
	else if (c == 'd' || c == 'i')
		pf_dec((long long)t_connect.current->value, 10);
	else if (c == 'o')
		pf_uns_oct_hex((unsigned long long int)t_connect.current->value, 8, 0);
	else if (c == 'u' || c == 'U')
		pf_uns_oct_hex((unsigned long long int)t_connect.current->value, 10, 0);
	else if (c == 'x')
		pf_uns_oct_hex((unsigned long long int)t_connect.current->value, 16, 1);
	else if (c == 'X')
		pf_uns_oct_hex((unsigned long long int)t_connect.current->value, 16, 0);
	else if ((c == 'f' || c == 'F') && t_f.lb == 0)
		pf_double();
	else if ((c == 'f' || c == 'F') && t_f.lb > 0)
		pf_ldouble();
	if (t_connect.current && t_connect.current->next != NULL && c != '%')
		t_connect.current = t_connect.current->next;
}
