/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:44:14 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 00:59:09 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void error_func(char *str)
{
    printf("%s\n", str);
    exit(0);
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

t_room *make_room(char *name, int nbr)
{
    t_room  *room;

    if (!(room = (t_room*)malloc(sizeof(t_room))))
        error_func("Malloc  error!");
    room->next = NULL;
    room->room_nbr = nbr;
    room->price = 2147483647;
    room->name = name;
    room->links = NULL;
    return (room);
}

t_room    *add_room(char *name)
{
    t_room  *room;
    int     nbr;

    nbr = 0;
    if (t_map.rooms == NULL)
    {
        room = make_room(name, nbr);
        t_map.rooms = room;
        return (room);
    }
    room = t_map.rooms;
    while (room)
    {
        if (!(ft_strcmp(room->name, name)))
			error_func("Map Error! Map contains room duplicates.");
        nbr++;
        if (room->next == NULL)
            break;
        room = room->next;
    }
    room->next = make_room(name, nbr);
    room = room->next;
    return (room);
}

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

t_link* make_link(t_room *home)
{
    t_link *link;

    if (!(link = (t_link*)malloc(sizeof(t_link))))
        error_func("Malloc  error!");
    link->next = NULL;
    link->home = home;
    link->room = NULL;
    link->status = 0;
    return (link);
}

t_link* add_link(t_room *room, int check_nbr)
{
    t_link *curr;

    if (room->links == NULL)
    {
        curr = make_link(room);
        room->links = curr;
        return (curr);
    }
    curr = room->links;
    while (curr)
    {
        if (check_nbr == curr->room->home->room_nbr)
            error_func("Map Error! Map contains room relinks.");
        if (curr->next == NULL)
            break;
        curr = curr->next;
    }
    curr->next = make_link(room);
    curr = curr->next;
    return (curr);
}

void    room_connector(t_room *room1,t_room *room2)
{
    t_link *link1;
    t_link *link2;

    link1 = add_link(room1, room2->room_nbr);
    link2 = add_link(room2, room1->room_nbr);
    link1->room = link2;
    link2->room = link1;
    link1->status = 1;
    link2->status = 1;
}
// *************************************room searcher + checker
void base_connections()
{
    int i = 0;

    printf("--->base_connections working\n");
    while (i + 1 < t_rooms.size)
    {
        room_connector(&t_rooms.array[i], &t_rooms.array[i + 1]);
        i++;
    }
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

void room_checker_low()
{
    t_room *room;
    int i = 0;

    printf("--->room_checker_low working\n");
    room = &t_rooms.array[0];
    while (room)
    {
        room->price = i++;
        printf("room nbr |%d| contains char |%c|\n", room->room_nbr, room->name);
        room = get_next_room(room->links, i);
    }
}

void price_check_up()
{
    int i = 0;

    while (i < t_rooms.size)
    {
        printf("room nbr |%d| contains char |%c| and price |%d|\n", t_rooms.array[i].room_nbr, t_rooms.array[i].name, t_rooms.array[i].price);
        i++;
    }
}

int main()
{
    room_generator();
    room_checker_up();
    base_connections();
    room_checker_low();
    price_check_up();
    return (0);
}