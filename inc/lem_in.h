/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:55:00 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/12 16:52:06 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define BUFFSIZE 5000

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

// struct		s_room_proto{
// 	char	*name;
// 	int		nbr;
// 	int		*connected_to_nbr;
// 	int		max_connect;
// 	int		cur_connect;
// 	//list of connections
// }			t_room_proto;

struct		s_rooms{
	char	**room_list;
	int		start_room_nbr;
	int		end_room_nbr;
}			t_rooms;

struct		s_links{
	int		**room_links;
	int		max_size;
}			t_links;

typedef struct		s_room{
	int				room_nbr;
	int				ant_nbr;
	struct s_room	*next_room;
	struct s_room	*prev_room;
}					t_room;


typedef struct		s_way{
	int				way_nbr;
	int				lenght;
	t_room			*start_room;
	t_room			*end_room;
	struct s_way	*next;
}					t_way;

struct				s_move{
	t_way			*head;
	t_way			*curr;
	int				*ways_len;
	int				ant_nbr;
	int				ants_in_rooms;
	int				ways;
}					t_move;




void	error_func(char *str);
void	parse_rooms(char **lines);
void	check_room_duplicates();
void	parse_links(char **lines);
void	free_strsplit(char ***str);

/*
**			ALGO_PROTO_C
*/

void	remove_link(int i);
void	reset_room_price();
void	change_value();
int		map_mark(int i, int price);
void	test_deixtra_alg();

/*
**			MAKE_WAY_PROTO_C
*/

int		min_price_next_room(int i, int **length);
t_room	*make_room(int room_nbr, t_room *prev);
t_room	*make_path(int room_nbr, t_room **end_room, int *length);
t_way	*make_way(int way_nbr);
void	form_ways();
void	get_ways_len();

/*
**			TRANSPORT_C
*/

int		acess_giver(int way_nbr);
void	ants_launcher();
void	ants_mover();
void	writer(int i, t_room* room);
void	display_status();
void	transport_core(char *buff);

#endif