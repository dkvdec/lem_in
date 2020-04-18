/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:44:14 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 18:09:21 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void error_func(char *str)
{
    printf("%s\n", str);
    exit(0);
}

void free_strsplit(char **str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		ft_strdel(&str[i++]);
	free(str);
	str = NULL;
}

void full_reset()
{
	t_valid.ants_flag = 0;
	t_valid.room_flag = 0;
	t_valid.start_flag = 0;
	t_valid.end_flag = 0;
	t_valid.room_counter = 0;
	t_valid.link_counter = 0;
	t_map.ants_nbr = 0;
	t_map.rooms = NULL;
	t_map.start = NULL;
	t_map.end = NULL;
}

void    room_connector(char *name1, char *name2)
{
    t_room  *room1;
    t_room  *room2;
    t_room  *curr;

    if (!(ft_strcmp(name1, name2)))
        error_func("Map Error! Same room relinks not allowed.");
    room1 = NULL;
    room2 = NULL;
    curr = t_map.rooms;
    while (curr)
    {
        if (room1 == NULL && (!(ft_strcmp(name1, curr->name))))
            room1 = curr;
        else if (room2 == NULL && (!(ft_strcmp(name2, curr->name))))
            room2 = curr;
        if ((room1 != NULL && room2 != NULL) || curr->next == NULL)
            break;
        curr = curr->next;
    }
    if (room1 == NULL || room2 == NULL)
        error_func("Map Error! Link contains unknown room.");
    link_connector(room1, room2);
}

t_room* get_next_room(t_link *curr, int price)
{
    while (curr)
    {
        if (curr->room->status == 1
        && curr->room->home->price > price)
            return (curr->room->home);
        curr = curr->next;
    }
    return (NULL);
}

void test_map_quality(void)
{
    t_room *room;
    t_link *link;

    room = t_map.rooms;
    while (room)
    {
        printf("Room |%s| is connected to:\n", room->name);
        link = room->links;
        while (link)
        {
            printf("--->|%s|\n", link->room->home->name);
            link = link->next;
        }
        room = room->next;
    }
}

void lem_in_core(int fd)
{
	int data;
	int i;
	char **lines;
	char buff[BUFFSIZE + 1];

	if ((data = read(fd, buff, BUFFSIZE)) < 32)
		error_func("Map Error!");
	buff[data] = '\0';
	empty_lines_check(buff);
	if (!(lines = ft_strsplit(buff, '\n')))
		error_func("Split malloc error!");
	get_map(lines);
	free_strsplit(lines);
    // test_map_quality();// TEST_DELETE_LATER
    base_way_former();
    transport_core(buff);
	//find_ways
	//move_ants
}

int main(int argc, char **argv)
{    
	int fd;
	char pnt;

	if (argc < 2)
		error_func("No arguments!");
	else if (argc == 2)
	{
		if (((fd = open(argv[1], O_RDONLY)) > 0) && ((read(fd, &pnt,0) == 0)))
		{
			lem_in_core(fd);
			close(fd);
		}
		else
			error_func("Incorrect format or unreadable file!");
	}
	else
		error_func("Too many arguments!");
	return (0);
}

// void room_generator()
// {
//     printf("--->room_generator working\n");
//     t_rooms.size = 5;
//     if (!(t_rooms.array = (t_room*)malloc(sizeof(t_room)*t_rooms.size)))
//         error_func("Malloc  error!");
//     int i = 0;
//     char c = 'a';
//     while (i < t_rooms.size)
//     {
//         t_rooms.array[i].room_nbr = i;
//         t_rooms.array[i].price = 2147483647;
//         t_rooms.array[i].name = c++;
//         t_rooms.array[i].links = NULL;
//         i++;
//     }
// }



// void room_checker_up()
// {
//     int i = 0;

//     printf("--->room_checker_up working\n");
//     while (i < t_rooms.size)
//     {
//         printf("room nbr |%d| contains char |%c|\n", t_rooms.array[i].room_nbr, t_rooms.array[i].name);
//         i++;
//     }
// }

// void link_generator()
// {
//     int i = 0;

//     printf("--->link_generator working\n");
//     while (i < t_rooms.size)
//     {
//         if (!(t_rooms.array[i].head_link = (t_link*)malloc(sizeof(t_link))))
//             error_func("Malloc  error!");
//         t_rooms.array[i].head_link->home = &t_rooms.array[i];
//         t_rooms.array[i].head_link->status = 1;
//         t_rooms.array[i].head_link->room = NULL;
//         t_rooms.array[i].head_link->next = NULL;
//         i++;
//     }
// }

// void room_checker_low()
// {
//     t_room *room;
//     int i = 0;

//     printf("--->room_checker_low working\n");
//     room = &t_rooms.array[0];
//     while (room)
//     {
//         room->price = i++;
//         printf("room nbr |%d| contains char |%c|\n", room->room_nbr, room->name);
//         room = get_next_room(room->links, i);
//     }
// }

// void price_check_up()
// {
//     int i = 0;

//     while (i < t_rooms.size)
//     {
//         printf("room nbr |%d| contains char |%c| and price |%d|\n", t_rooms.array[i].room_nbr, t_rooms.array[i].name, t_rooms.array[i].price);
//         i++;
//     }
// }

// void base_connections()
// {
//     int i = 0;

//     printf("--->base_connections working\n");
//     while (i + 1 < t_rooms.size)
//     {
//         room_connector(&t_rooms.array[i], &t_rooms.array[i + 1]);
//         i++;
//     }
// }