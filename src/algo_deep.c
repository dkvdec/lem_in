/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_deep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:14:20 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 08:18:01 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int way_control_system(t_ws **min, t_ws *cur, t_ws *org)
{
	if (*(min) == NULL
	|| (*min)->turn_nbr > cur->turn_nbr)
		copy_way(min, cur);
	if (cur->turn_nbr > org->turn_nbr)
		return (1);
	return (0);
}

void deep_recursion(t_ws *org, int lvl)
{
	t_ws *cur;
	int stop;

	cur = NULL;
	stop = 0;
	t_wcs.stop = stop;
	copy_way(&cur, org);
	map_reset();
	coll_deixtra_base(t_map.start, 0, 0);
	if (t_map.coll_lvl > 0)
	{
		map_reset();
		while (deep_deixtra_base(t_map.start, 0, 0) > stop)
		{
			add_new_path(cur);
			if (way_control_system(&t_wcs.deep_min, cur, org))
				break ;
			deep_recursion(cur, lvl + 1);
			full_map_reset();
			map_reclaim(org);
			copy_way(&cur, org);
			stop++;
			t_wcs.stop = stop;
		}
	}
	else
	{
		add_new_path(cur);
		way_control_system(&t_wcs.deep_min, cur, org);
		deep_recursion(cur, lvl + 1);
	}
	dstr_way(&cur);
}

void	way_deep_select()
{
	if (t_wcs.deep_smp)
		dstr_way(&(t_wcs.deep_smp));
	full_map_reset();
	map_reclaim(t_wcs.deep_min);
	t_wcs.stop = 0;
	while(deep_deixtra_base(t_map.start, 0, 0) > t_wcs.stop)
	{
		add_new_path(t_wcs.deep_cur);
		if (t_wcs.deep_smp == NULL
		|| t_wcs.deep_cur->turn_nbr <= t_wcs.deep_smp->turn_nbr)
			copy_way(&(t_wcs.deep_smp), t_wcs.deep_cur);
		full_map_reset();
		map_reclaim(t_wcs.deep_min);
		copy_way(&(t_wcs.deep_cur), t_wcs.deep_min);
		t_wcs.stop++;
	}
}

void algo_deep()
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
				break;
			copy_way(&(t_wcs.deep_min), t_wcs.deep_cur);
			map_reset();
		}
	}
}