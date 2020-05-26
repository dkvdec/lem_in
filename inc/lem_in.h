/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 23:07:09 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:08:50 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define BUFFSIZE 300000

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>

struct				s_valid{
	int				ants_flag;
	int				room_flag;
	int				start_flag;
	int				end_flag;
	int				room_counter;
	int				link_counter;
}					t_valid;

typedef struct		s_link{
	struct s_link	*room;
	int				status;
	struct s_room	*home;
	struct s_link	*next;
}					t_link;

typedef struct		s_room{
	struct s_room	*next;
	int				status;
	int				room_nbr;
	int				mark;
	int				price;
	char			*name;
	struct s_link	*links;
}					t_room;

struct				s_map{
	int				ants_nbr;
	int				mark_sts;
	int				coll_lvl;
	char			**lines;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
}					t_map;

/*
** WAY_CONTROL_SYSTEM
*/

struct				s_wcs{
	int				mark_lst;
	int				stop;
	struct s_ws		*base_min;
	struct s_ws		*coll_min;
	struct s_ws		*coll_cur;
	struct s_ws		*deep_min;
	struct s_ws		*deep_cur;
	struct s_ws		*deep_smp;
}					t_wcs;

/*
** WAY_SYSTEM
*/

typedef struct		s_ws{
	int				turn_nbr;
	int				ways_nbr;
	int				ants_in_rooms;
	int				ant_nbr;
	struct s_wh		*ways;
}					t_ws;

/*
** WAY_HEAD
*/

typedef struct		s_wh{
	int				way_nbr;
	int				way_len;
	int				ants_in_rooms;
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
	t_wh			*home;
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

/*
**	ALGO_BASE_C
*/

int					base_deixtra(t_room *room, int price);
t_link				*min_price_next_room(t_room *room);
t_w					*make_new_path(t_w **end, t_wh *home);
void				new_base_path(void);
void				algo_base(void);

/*
**	ALGO_COLL_C
*/

int					coll_deixtra_coll_dcd(t_link *link,
					int price, int lvl, int step);
int					coll_deixtra_coll(t_room *room,
					int price, int lvl, int step);
int					coll_deixtra_base_dcd(t_link *link, int price, int lvl);
int					coll_deixtra_base(t_room *room, int price, int lvl);
void				algo_coll(void);

/*
**	ALGO_CORE_C
*/

void				wcs_reset(void);
int					way_control_system(t_ws **min, t_ws *cur, t_ws *org);
int					way_status_resulter(t_ws **min, t_ws *cur);
void				algo_deep(void);
void				algo_core(void);

/*
**	ALGO_DEEP_C
*/

int					deep_deixtra_coll_dcd(t_link *link,
					int price, int lvl, int step);
int					deep_deixtra_coll(t_room *room,
					int price, int lvl, int step);
int					deep_deixtra_base_dcd(t_link *link, int price, int lvl);
int					deep_deixtra_base(t_room *room, int price, int lvl);
void				way_deep_select(void);

/*
**	COLL_CORE_C
*/

void				find_coll_way1(t_wh *way);
void				find_coll_way2(t_ws *wcs);
void				handle_collision(void);
void				claim_rooms(t_wh *home);
void				way_collision_handler(t_ws *wcs, t_wh *way);

/*
**	COLL_FNCS_C
*/

void				open_links(t_room *room);
void				reconnect_ways(t_w *start, t_w *end, t_w *stop);
void				reconnect_home(t_wh *home);
void				claim_tail(t_w *curr);

/*
**	COLL_SORT_C
*/

int					check_ways_sort(t_ws *wcs);
void				sort_swap(t_wh *prev, t_wh *curr, t_wh *next);
void				sort_operation(t_ws *wcs);
void				get_ways_nbr(t_ws *wcs);
void				resort_ways_by_len(t_ws *wcs);

/*
**	FREE_FNCS_C
*/

void				free_links(t_room *room);
void				free_map(void);
void				free_ways(void);
int					free_strsplit(char **str);
void				error_func(char *str);

/*
**	MAIN_CORE_C
*/

void				room_connector(char *name1, char *name2, char **names);
void				transport_core(char *buff, t_ws *wcs);
void				best_way_selector(char *buff);
void				lem_in_core(void);

/*
**	MAP_BUILD_C
*/

t_room				*make_room(char *name, int nbr);
t_room				*add_room(char *name);
t_link				*make_link(t_room *home);
t_link				*add_link(t_room *room, int check_nbr, char **names);
void				link_connector(t_room *room1, t_room *room2, char **names);

/*
**	MAP_CHECK_C
*/

int					exception_check(char *line);
int					room_check(char *line);
int					is_room(char *line);
int					is_link(char *line);
void				empty_lines_check(char *buff);

/*
**	MAP_GET_C
*/

void				get_ants_nbr(char *line);
void				get_command(char *line);
void				get_room(char *line);
void				get_link(char *line);
void				get_map(char **lines);

/*
**	MAP_RESET_C
*/

void				map_reset(void);
void				full_map_reset(void);
void				full_reset(void);
void				find_reset_link(t_room *prev, t_room *curr,
					int p_nbr, int c_nbr);
void				map_reclaim(t_ws *wcs);

/*
**	NEXT_COLL_C
*/

t_link				*way_next_coll_entr_frcd(t_room *room);
t_link				*way_next_coll_entr(t_room *room);
t_link				*way_next_coll_cont(t_room *room);
t_link				*way_next_coll_escp(t_room *room);

/*
**	NEXT_NORM_C
*/

t_link				*way_first_room(t_room *room);
t_link				*way_next_norm(t_room *room);
t_link				*way_next_room(t_room *room);

/*
**	TRANSPORT_C
*/

int					acess_giver(t_ws *wcs, t_wh *cur, int ants_nbr);
void				ants_launcher(t_ws *wcs);
void				ants_mover(t_ws *wcs);
void				writer(int i, t_w *room);
void				display_status(t_ws *wcs);

/*
**	WAY_BUILD_C
*/

t_w					*make_w(t_room *room, t_w *next, t_wh *home);
t_wh				*make_wh(int way_nbr, t_wh *orig);
t_ws				*make_ws(t_ws *orig);
t_w					*make_new_coll_path(t_w **end, t_wh *home);
void				add_new_path(t_ws *wcs);

/*
**	WAY_DSTR_C
*/

void				dstr_path(t_w *curr);
void				dstr_way(t_ws **prey);

/*
**	WAY_COPY_C
*/

void				copy_path(t_wh *dst, t_wh *src);
void				copy_way(t_ws **dst, t_ws *src);

/*
**	WAY_FNCS_C
*/

void				way_collision_reset();
void				open_ways_links(t_wh *way);
void				get_way_len(t_wh *way);
void				recount_ways_len(t_ws *wcs);
void				get_turn_nbr(t_ws *head);

#endif
