/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:57:44 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 02:21:36 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			way_control_system(t_ws **min, t_ws *cur, t_ws *org)
{
	if (*(min) == NULL
	|| (*min)->turn_nbr > cur->turn_nbr)
		copy_way(min, cur);
	if (cur->turn_nbr > org->turn_nbr)
		return (1);
	return (0);
}

int			way_status_resulter(t_ws **min, t_ws *cur)
{
	if (*(min) == NULL
	|| (*min)->turn_nbr > cur->turn_nbr)
		copy_way(min, cur);
	else
		return (1);
	return (0);
}

void		algo_core(void)
{
	wcs_reset();
	algo_base();
	full_map_reset();
	algo_coll();
	full_map_reset();
	algo_deep();
}
