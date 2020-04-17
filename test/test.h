/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 23:07:09 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/17 23:44:44 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# define BUFFSIZE 200000

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

struct              s_valid{
	int             ants_flag;
	int             room_flag;
	int             start_flag;
	int             end_flag;
	int             room_counter;
}                   t_valid;

typedef struct      s_link{
    struct s_link   *room;
    int             status;
    struct s_room   *home;
    struct s_link   *next;
}                   t_link;

typedef struct		s_room{
    struct s_soom   *next;
    int             room_nbr;
    int             price;
    char            *name;
    struct s_link   *links;
}                   t_room;

// struct              s_rooms{
//     t_room          *array;
//     int             size;
// }                   t_rooms;

struct              s_map{
    int             ants_nbr;
    t_room          *rooms;
    t_room          *start;
    t_room          *end;
}                   t_map;

#endif