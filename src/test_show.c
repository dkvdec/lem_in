/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 08:57:07 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/07 22:28:17 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void test_show_mark_status();

void    current_status(t_room* room, t_wh* home)
{
	test_show_mark_status();
	test_show_end(home);
	test_show_trouble_situation(room, 2);
    printf("Program failed at forming way_nbr %d at room_nbr %d!\n", home->way_nbr, room->room_nbr);
	printf("col_flg = %d, col_stp = %d\n", t_col.col_flg, t_col.col_stp);
    exit(0);
}

void test_show_mark_status()
{
	t_room	*room;

	room = t_map.rooms;
	while (room)
	{
		if (room->mark + 1 == t_map.end->mark)
			printf("|%s| status = %d, price = %d, mark = %d.\n", room->name, room->status, room->price, room->mark);
		room = room->next;
	}
}

void test_show_room_status()
{
	t_room	*room;
	t_link	*link;

	room = t_map.rooms;
	while (room)
	{
		printf("|%s| status = %d, price = %d, mark = %d.\n", room->name, room->status, room->price, room->mark);
		link = room->links;
		while (link)
		{
			printf("   link status %d-%d\n      Linked room %s, status %d, mark %d, price %d.\n", link->status, link->room->status, link->room->home->name, link->room->home->status, link->room->home->mark, link->room->home->price);
			link = link->next;
		}
		room = room->next;
	}
}

void test_show_paths()
{
	t_wh	*head;
	t_w		*room;

	head = t_wcs.cur->ways;
	while (head)
	{
		room = head->start;
		printf("way nbr %d len %d\n|%s|", head->way_nbr, head->way_len, t_map.start->name);
		while (room)
		{
			printf("->|%s|", room->room->name);
			room = room->next;
		}
		printf("\n");
		head = head->next;
	}
}

void test_show_trouble_situation(t_room *room, int step)
{
	t_link	*link;

	step--;
	if (step <= 0)
		return ;
	printf("\nTroubles at room %s, status %d, mark %d, price %d.\n", room->name, room->status, room->mark, room->price);
	link = room->links;
	while (link)
	{
		printf("Link status %d-%d\n   Linked room %s, status %d, mark %d, price %d.\n", link->status, link->room->status, link->room->home->name, link->room->home->status, link->room->home->mark, link->room->home->price);
		test_show_trouble_situation(link->room->home, step);
		link = link->next;
	}
}

void test_show_end(t_wh *head)
{
	t_w		*room;

	room = head->end;
	while (room)
	{
		printf("->|%s|", room->room->name);
		room = room->prev;
	}
	printf("\n");
}

void test_show_way(t_wh *head)
{
	t_w		*room;

	room = head->start;
	printf("way nbr %d len %d\n|%s|", head->way_nbr, head->way_len, t_map.start->name);
	while (room)
	{
		printf("->|%s|", room->room->name);
		room = room->next;
	}
	printf("\n");
}

void test_show_collision()
{
	test_show_way(t_col.wh1);
	printf("collision |%s|->...->|%s|\n", t_col.w1_col_e->room->name, t_col.w1_col_s->room->name);
	test_show_way(t_col.wh2);
	printf("collision |%s|->...->|%s|\n", t_col.w2_col_e->room->name, t_col.w2_col_s->room->name);
	if (t_col.wh1 == NULL
	|| t_col.w1_col_s == NULL
	|| t_col.w1_col_e == NULL
	|| t_col.wh2 == NULL
	|| t_col.w2_col_s == NULL
	|| t_col.w2_col_e == NULL)
		error_func("Error! Collision not allocated correctly.");
}

// t_link *next_de_way(t_room *room)
// {
// }

// void show_de_way()
// {

// }