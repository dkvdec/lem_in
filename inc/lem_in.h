/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:55:00 by dheredat          #+#    #+#             */
/*   Updated: 2020/03/16 19:58:27 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define BUFFSIZE 5000000

# include "../ft_printf/inc/proto_vlst.h"
# include <fcntl.h>

struct		s_valid{
	int		ants_nbr;
	int		ants_flg;
	int		rooms_begin;
	int		rooms_counter;
	int		links_begin;
	int		links_counter;
	int		start_line;
	int		start_counter;
	int		end_line;
	int		end_counter;
}			t_valid;

struct		s_room_proto{
	char	*name;
	int		nbr;
	int		*connected_to_nbr;
	int		max_connect;
	int		cur_connect;
	//list of connections
}			t_room_proto;

struct		s_rooms{
	char	**room_list;
	int		start_room_nbr;
	int		end_room_nbr;
}			t_rooms;

struct		s_links{
	int		**room_links;
	int		max_size;
}			t_links;


void error_func(char *str);
void parse_rooms(char **lines);
void check_room_duplicates();
void parse_links(char **lines);

#endif