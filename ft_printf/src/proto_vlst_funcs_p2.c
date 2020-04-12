/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst_funcs_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:16:30 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 18:09:35 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

void			*silent_grep(int nbr)
{
	void	*value;
	t_vlst	*savepos;

	savepos = t_connect.current;
	vlst_walk(nbr);
	value = t_connect.current->value;
	t_connect.current = savepos;
	return (value);
}

void			type_equlizer_tail(t_vlst **seer)
{
	(*seer) = t_connect.current->prev;
	t_connect.current->type = (*seer)->type;
}

void			type_equalizer(void)
{
	t_vlst	*seer;

	vlst_walk(1);
	while (t_connect.current != NULL)
	{
		if (t_connect.current->type == 0)
		{
			if (t_connect.current->nbr == 1)
			{
				seer = t_connect.current->next;
				while (seer != NULL && seer->type == 0)
					seer = seer->next;
				if (seer == NULL)
					t_connect.current->type = 2;
				else
					t_connect.current->type = seer->type;
			}
			else
				type_equlizer_tail(&seer);
		}
		if (t_connect.current->next != NULL)
			t_connect.current = t_connect.current->next;
		else
			break ;
	}
}

void			vlst_dstr(void)
{
	t_vlst	*tmp;

	vlst_walk(1);
	while (t_connect.current != NULL)
	{
		tmp = t_connect.current->next;
		free(t_connect.current);
		t_connect.current = tmp;
	}
}
