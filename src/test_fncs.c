/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 00:06:45 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/13 00:09:08 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/* ************************_REMOVE_SAME_PRICE_LINKS_************************ */

void remove_connect(t_room *room1, t_room *room2, t_link *prev1, t_link *prev2)
{
	t_link *curr;

	// test_show_trouble_situation(room1, 2);
	if (prev1 == NULL)
	{
		curr = room1->links;
		room1->links = (curr->next);
	}
	else
	{
		curr = prev1->next;
		prev1->next = (curr->next);
	}
	free(curr);
	// test_show_trouble_situation(room1, 2);
	// printf("=============================================================================\n");
	// test_show_trouble_situation(room2, 2);
	if (prev2 == NULL)
	{
		curr = room2->links;
		room2->links = (curr->next);
	}
	else
	{
		curr = prev2->next;
		prev2->next = (curr->next);
	}
	// test_show_trouble_situation(room2, 2);
	free(curr);
}

void find_connect(t_room *room1, t_room *room2)
{
	t_link *prev1;
	t_link *prev2;
	t_link *curr;

	prev1 = NULL;
	curr = room1->links;
	while (curr && curr->room->home->room_nbr != room2->room_nbr)
	{
		prev1 = curr;
		curr = curr->next;
	}
	prev2 = NULL;
	curr = room2->links;
	while (curr && curr->room->home->room_nbr != room1->room_nbr)
	{
		prev2 = curr;
		curr = curr->next;
	}
	printf("removing link between |%s| and |%s|\n", room1->name, room2->name);
	remove_connect(room1, room2, prev1, prev2);
	printf("LINK_REMOVED\n");
}

void test_optimizer()
{
	t_room *room;
	t_link *link;

	room = t_map.rooms;
	while (room)
	{
		link = room->links;
		while (link)
		{
			if (room->price == link->room->home->price)
			{
				find_connect(room, link->room->home);
				link = room->links;
			}
			else
				link = link->next;
		}
		room = room->next;
	}
}

/* */