/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:11:24 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/10 16:24:56 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

/* 
** алгоритм содержит в себе несколько частей
** 1. Дейкстра для разведки и пометки комнат
**		1) комнаты в порядке удаления от старта
**		2) хвосты не ведущие к финишу минусятся
**		3) если алгоритм достигает финиша хотя бы раз,
**			то возвращает положительное значение,
**			если нет, отрицательное
**		? возможно стоит занулять мёртвые пути
** 2. Глубокая фильтрация карты, удаление всех петель
*/


void change_value()
{
	int i;
	int j;

	i = 0;
	while (i < t_links.max_size)
	{
		j = 0;
		while (j < t_links.max_size)
		{
			if (t_links.room_links[i][j] != 0)
				t_links.room_links[i][j] = 99;
			j++;
		}
		i++;
	}
	test_links_matrix();
}

void deixtra_proto(int i, int price)
{
	int j;

	price++;
	j = 0;
	while(j < t_links.max_size)
	{
		if (t_links.room_links[i][j] != 0
		&& t_links.room_links[i][j] > price)
		{
			t_links.room_links[i][j] = price;
			t_links.room_links[j][i] = price;
			if (i != t_rooms.end_room_nbr
			&& j != t_rooms.end_room_nbr)
				deixtra_proto(j, price);
		}
		j++;
	}
}

/*
**	map_mark
**
**	functions:
**		-valuation of ways cost
**	return options:
**		1 - if end reached
**		0 - if blocked by cost
**		-1 - if end's unreached
*/

int map_mark(int i, int price)
{
	int j;
	int flag;

	price++;
	j = 0;
	flag = -1;
	while(j < t_links.max_size)
	{
		if (t_links.room_links[i][j] != 0
		&& t_links.room_links[i][j] > price)
		{
			t_links.room_links[i][j] = price;
			t_links.room_links[j][i] = price;
			if (i != t_rooms.end_room_nbr
			&& j != t_rooms.end_room_nbr)
				flag = (map_mark(j, price) > 0) ? 1 : flag;
			else
				flag = 1;			
		}
		j++;
	}
	return (flag);
}

// void set_link_price(int i, int j, int price)
// {
// 	t_links.room_links[i][j] = price;
// 	t_links.room_links[j][i] = price;
// }
//переработать для зануления в случае отсуствия конца и более дешёвых линков
// int map_mark(int i, int price)
// {
// 	int j;
// 	int flag;
// 	int swap;

// 	price++;
// 	j = 0;
// 	flag = -1;
// 	while(j < t_links.max_size)
// 	{
// 		if (t_links.room_links[i][j] != 0)
// 		{
// 			if (t_links.room_links[i][j] > price)
// 			{
				
// 				if (i != t_rooms.end_room_nbr
// 				&& j != t_rooms.end_room_nbr)
// 				{
// 					set_link_price(i, j, -1);// useless
// 					if ((swap = map_mark(j, price)) > flag)
// 						flag = swap;
// 					if (swap >= 0)
// 						set_link_price(i, j, price);
// 				}
// 				else
// 					flag = 1;
// 			}
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)
// 	// 	remove_link(i);
// 	return (flag);
// }
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)

// int deixtra_proto2(int i, int price)
// {
// 	int j;
// 	int flag;

// 	price++;
// 			else
// 				flag = (flag >= 0) ? flag : 0;
// 		}
// 		j++;
// 	}
// 	// if (flag < 0)
// 		{
// 			t_links.room_links[i][j] = price;
// 			t_links.room_links[j][i] = price;
// 			if (i != t_rooms.end_room_nbr
// 			&& j != t_rooms.end_room_nbr)
// 			{
// 				if ((deixtra_proto2(j, price)) > 0)
// 					flag++;
// 				else
// 				{
// 					t_links.room_links[i][j] = -1;
// 					t_links.room_links[j][i] = -1;
// 				}
// 			}
// 			else
// 				flag++;
			
// 		}
// 		else if (t_links.room_links[i][j] > 0 && t_links.room_links[i][j] < price)
// 			flag++;
// 		j++;
// 	}
// 	return (flag);
// }

void show_ways()
{
	t_way *curr;
	t_room *room;

	curr = t_move.head;
	while (curr != NULL)
	{
		ft_printf("______________________\nway_nbr = %d\nway_length = %d\n", curr->way_nbr, curr->lenght);
		room = curr->start_room;
		ft_printf("|%d|->", t_rooms.start_room_nbr);
		while (room != NULL)
		{
			ft_printf("|%d|", room->room_nbr);
			if (room->room_nbr != t_rooms.end_room_nbr)
				ft_printf("->");
			room = room->next_room;
		}
		ft_printf("\n");
		curr = curr->next;
	}
}

void test_deixtra_alg()
{
	form_ways();
	ft_printf("start = %d\nend = %d\n", t_rooms.start_room_nbr, t_rooms.end_room_nbr);
	test_links_matrix();
	show_ways();
	get_ways_len();
}