/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 23:07:09 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/18 13:01:03 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# define BUFFSIZE 200000

# include "../ft_printf/inc/proto_vlst.h"
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
	int             link_counter;
}                   t_valid;

typedef struct      s_link{
	struct s_link   *room;
	int             status;
	struct s_room   *home;
	struct s_link   *next;
}                   t_link;

typedef struct		s_room{
	struct s_room   *next;
	int             room_nbr;
	int             price;
	char            *name;
	struct s_link   *links;
}                   t_room;

struct              s_map{
	int             ants_nbr;
	t_room          *rooms;
	t_room          *start;
	t_room          *end;
}                   t_map;

/*
**	CHECK_MAP_C
*/

int					exception_check(char *line);
int					room_check(char *line);
int					is_room(char *line);
int					is_link(char *line);
void				empty_lines_check(char *buff);

/*
**	GET_MAP_C
*/

void				get_ants_nbr(char *line);
void				get_command(char *line);
void				get_room(char *line);
void				get_link(char *line);
void				get_map(char **lines);

/*
**	BUILD_MAP_C
*/

t_room				*make_room(char *name, int nbr);
t_room				*add_room(char *name);
t_link				*make_link(t_room *home);
t_link				*add_link(t_room *room, int check_nbr);
void				link_connector(t_room *room1, t_room *room2);

/*
**
*/

void	error_func(char *str);
void	full_reset();
void	room_connector(char *name1, char *name2);
void	free_strsplit(char **str);

#endif