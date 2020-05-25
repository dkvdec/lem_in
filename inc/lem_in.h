/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 23:07:09 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/25 02:57:39 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# define BUFFSIZE 300000

# include "../libft/libft.h"
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
	int				status;
	int             room_nbr;
	int				mark;
	int             price;
	char            *name;
	struct s_link   *links;
}                   t_room;

struct              s_map{
	int             ants_nbr;
	int				mark_sts;
	int				coll_lvl;
	char			**lines;
	t_room          *rooms;
	t_room          *start;
	t_room          *end;
}                   t_map;
////////////////////_UNDER_REFACTOR_////////////////////
typedef struct		s_wroom{
	int				room_nbr;
	char			*name;
	int				ant_nbr;
	struct s_wroom	*next_room;
	struct s_wroom	*prev_room;
}					t_wroom;

typedef struct		s_way{
	int				way_nbr;
	int				lenght;
	t_wroom			*start;
	t_wroom			*end;
	struct s_way	*next;
}					t_way;

struct				s_move{
	t_way			*head;
	int				*ways_len;
	int				ant_nbr;
	int				ants_in_rooms;
	int				ways;
}					t_move;
//////////////////////////////////////////////////////////
////////////////////_EXPERIMENTAL_WAY_////////////////////
/*
** WAY_CONTROL_SYSTEM
*/
struct				s_wcs{
	int				mark_lst;
	int				stop;
	int				brdr;
	struct s_ws		*min;
	struct s_ws		*cur;
	struct s_ws		*smp;
	//
	struct s_ws		*base_min;
	//
	struct s_ws		*coll_min;
	struct s_ws		*coll_cur;
	//
	struct s_ws		*deep_min;
	struct s_ws		*deep_cur;
	struct s_ws		*deep_smp;
}					t_wcs;

/*
** WAY_SUMMARY
*/
typedef struct		s_ws{
	int				turn_nbr;
	int				ways_nbr;
	int				ants_in_rooms; //
	int				ant_nbr; //
	struct s_wh		*ways;
}					t_ws;

/*
** WAY_HEAD
*/
typedef struct		s_wh{
	int				way_nbr;
	int				way_len;
	int				ants_in_rooms; //
	struct s_wh		*next;
	struct s_w		*start;
	struct s_w		*end;
}					t_wh;

/*
** WAY_POINTER
*/
typedef struct		s_w{
	struct s_w		*prev;
	struct s_w		*next;
	int				ant_nbr;
	t_room			*room;
	t_wh			*home; //mb delete later
}					t_w;

/*
** WAY_COLLISION_MANAGER
*/
struct				s_col{
	int				col_flg;
	int				col_stp;
	int				col_sts;
	t_wh			*wh1;
	t_w				*w1_col_s;
	t_w				*w1_col_e;
	t_wh			*wh2;
	t_w				*w2_col_s;
	t_w				*w2_col_e;
}					t_col;

//////////////////////////////////////////////////////////
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
t_link				*add_link(t_room *room, int check_nbr, char **names);
void				link_connector(t_room *room1, t_room *room2, char **names);

/*
**
*/

void				error_func(char *str);
void				full_reset();
void				room_connector(char *name1, char *name2, char **names);
int					free_strsplit(char **str);

////////////////////_EXPERIMENTAL_BLOCK_///////////////////

int					base_deixtra(t_room *room, int price);
int					base_deixtra_rec(t_room *room, int price, int lvl);
void				base_way_former();
void				transport_core(char *buff, t_ws *wcs);

////////////////////_NEW_WAY_FUNCTIONS_////////////////////

t_w*    make_w(t_room *room, t_w *next, t_wh* home);
t_wh*   make_wh(int way_nbr, t_wh *orig);
t_ws*   make_ws(t_ws* orig);
//t_w		*make_new_path(t_w** end, t_wh* home);
void	add_new_path(t_ws *wcs);
void	make_wcs();
//t_link	*min_price_next_room(t_room *room, t_wh *home);
t_link	*next_room_norm_case(t_room *room);

int acess_giver(t_ws *ws, t_wh *cur, int ants_nbr);
void get_way_len(t_wh *way);
void get_turn_nbr(t_ws *head);

void	way_collision_handler(t_ws *wcs, t_wh *way);
t_w		*make_new_coll_path(t_w** end, t_wh* home);
t_link	*next_room_decider(t_room *room);
void way_deep_select();
void full_map_reset();
void map_reclaim();

////////////////////_WAY_COPY_OR_DSTR_////////////////////

void copy_path(t_wh* dst, t_wh* src);
void copy_way(t_ws **dst, t_ws *src);
void dstr_path(t_w *curr);
void dstr_way(t_ws **prey);
void	recount_ways_len(t_ws *wcs);
void	resort_ways_by_len(t_ws *wcs);

////////////////////_TEST_SHOW_FUNCS_////////////////////

void    current_status(t_room* room, t_wh* home);
void test_show_room_status();
void test_show_paths();
void test_show_trouble_situation(t_room *room, int step);
void test_show_end(t_wh *head);
void test_show_way(t_wh *head);
void test_show_collision();

void algo_base();
void algo_core();
void algo_coll();
void algo_deep();
void map_reset();
int coll_deixtra_coll(t_room *room, int price, int lvl, int step);
int coll_deixtra_base(t_room *room, int price, int lvl);
int deep_deixtra_base(t_room *room, int price, int lvl);

#endif