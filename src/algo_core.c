/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:57:44 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 09:57:46 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void		wcs_reset(void)
{
	t_wcs.base_min = NULL;
	t_wcs.coll_cur = NULL;
	t_wcs.coll_min = NULL;
	t_wcs.deep_cur = NULL;
	t_wcs.deep_min = NULL;
	t_wcs.deep_smp = NULL;
}

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

void		algo_deep(void)
{
	t_wcs.deep_cur = make_ws(NULL);
	while (coll_deixtra_base(t_map.start, 0, 0) > 0)
	{
		if (t_map.coll_lvl > 0)
		{
			way_deep_select();
			if (t_wcs.deep_smp == NULL
			|| t_wcs.deep_min->turn_nbr < t_wcs.deep_smp->turn_nbr)
				break ;
			copy_way(&(t_wcs.deep_min), t_wcs.deep_smp);
			copy_way(&(t_wcs.deep_cur), t_wcs.deep_smp);
			full_map_reset();
			map_reclaim(t_wcs.deep_min);
		}
		else
		{
			add_new_path(t_wcs.deep_cur);
			if (t_wcs.deep_min
			&& t_wcs.deep_cur->turn_nbr > t_wcs.deep_min->turn_nbr)
				break ;
			copy_way(&(t_wcs.deep_min), t_wcs.deep_cur);
			map_reset();
		}
	}
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
