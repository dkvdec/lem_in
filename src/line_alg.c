/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 23:09:40 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/16 00:01:34 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void kill_tails()
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		flag;
	unsigned int        mflag;

	i = 0;
	mflag = 0;
	//ft_putendl("->searching for tails");
	while (i < t_links.max_size)
	{
		j = 0;
		flag = 0;
		if (i != t_rooms.start_room_nbr
		&& i != t_rooms.end_room_nbr)
			while (j < t_links.max_size)
			{
				if (t_links.room_links[i][j] != 0)
					flag++;
				j++;
			}
		if (flag == 1)
		{
			mflag++;
			remove_link(i);
			//ft_putendl("tail killed");
		}
		i++;
		if (i == t_links.max_size && mflag > 0)
		{
			i = 0;
			mflag = 0;
		}
	}
}

int deixtra_next(int i, int *price, int *flag)
{
	//returns first > price && price++
	//returns min if we need to return && price

	int j;
	int m;

	j = 0;
	m = -1;
	(*price)++;
	while (j < t_links.max_size)
	{
		if (t_links.room_links[i][j] != 0)
		{
			if (j == t_rooms.end_room_nbr)
				(*flag)++;
			if (t_links.room_links[i][j] > (*price)
			&& i != t_rooms.end_room_nbr)
				return (j);
			if (t_links.room_links[i][j] < (*price) && (m < 0
			|| t_links.room_links[i][j] < t_links.room_links[i][m]))
				m = j;
		}
		j++;
	}
	(*price) -= 2;
	if (i == t_rooms.start_room_nbr)
		return (-1);
	return (m);
}

int deixtra_linear()
{
	int i;
	int j;
	int flag;
	int price;

	price = 0;
	flag = 0;
	j = t_rooms.start_room_nbr;
	while ((i = deixtra_next(j, &price, &flag)) >= 0)
	{
		if (i == t_rooms.start_room_nbr)
			test_links_matrix();
		if (t_links.room_links[i][j] > price)
		{
			t_links.room_links[i][j] = price;
			t_links.room_links[j][i] = price;
		}
		j = i;
	}
	if (flag == 0)
		return (-1);
	return (flag);
}
////////////////////

void make_room_tail()
{
	int i;

	if (!(t_links.room_tail = (int*)malloc(sizeof(int) * t_links.max_size)))
		error_func("Malloc Error!");
	i = 0;
	while (i < t_links.max_size)
		t_links.room_tail[i++] = -1;
	// while (i < t_links.max_size)
	// {
	// 	if (!(t_links.room_tail[i] = (int*)malloc(sizeof(int) * 2)))
	// 		error_func("Malloc Error!");
	// 	t_links.room_tail[i][0] = -1;
	// 	t_links.room_tail[i][1] = 0;
	// }
	t_links.room_tail[0] = t_rooms.start_room_nbr;
}

int deixtra_linear_2()
{
	int i;
	int j;
	int price;
	int flag;

	i = t_rooms.start_room_nbr;
	price = 0;
	flag = 0;
	j = 0;
	while (j < t_links.max_size)
	{
		if (i == t_rooms.end_room_nbr && j == 0)
			flag++;
		if (i != t_rooms.end_room_nbr
		&& t_links.room_links[i][j] != 0
		&& t_links.room_links[i][j] > price + 1)
		{
			price++;
			t_links.room_tail[price] = j;
			t_links.room_links[i][j] = price;
			t_links.room_links[j][i] = price;
			i = j;
			j = 0;
			continue;
		}
		j++;
		if (j == t_links.max_size && price > 0)
		{
			j = i + 1;
			t_links.room_tail[price--] = -1;
			i = t_links.room_tail[price];
		}
	}
	return (flag);
}
