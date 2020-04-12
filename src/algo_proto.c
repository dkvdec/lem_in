/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:11:24 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/12 11:17:38 by dheredat         ###   ########.fr       */
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

void remove_link(int i)
{
	int j;

	j = 0;
	while(j < t_links.max_size)
	{
		t_links.room_links[i][j] = 0;
		t_links.room_links[j][i] = 0;
		j++;
	}
}

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
				t_links.room_links[i][j] = 2147483647;
			j++;
		}
		i++;
	}
	//test_links_matrix();
}

// void deixtra_proto(int i, int price)
// {
// 	int j;

// 	price++;
// 	j = 0;
// 	while(j < t_links.max_size)
// 	{
// 		if (t_links.room_links[i][j] != 0
// 		&& t_links.room_links[i][j] > price)
// 		{
// 			t_links.room_links[i][j] = price;
// 			t_links.room_links[j][i] = price;
// 			if (i != t_rooms.end_room_nbr
// 			&& j != t_rooms.end_room_nbr)
// 				deixtra_proto(j, price);
// 		}
// 		j++;
// 	}
// }

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

void test_deixtra_alg()
{
	form_ways();
	//ft_printf("start = %d\nend = %d\n", t_rooms.start_room_nbr, t_rooms.end_room_nbr);
	//test_links_matrix();
	//show_ways();
	get_ways_len();
}
