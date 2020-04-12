/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_vlst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:54:51 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:30:20 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_VLST_H
# define PROTO_VLST_H

# include <stdarg.h>
# include <stdio.h>
# include "./../libft/libft.h"

typedef	struct			s_vlst{
	int					nbr;
	int					type;
	void				*value;
	void				*next;
	void				*prev;
}						t_vlst;

struct					s_connect{
	t_vlst				*current;
}						t_connect;

struct					s_line{
	char				*out;
	size_t				len;
}						t_line;

struct					s_type{
	int					dsnb;
	int					ds;
	int					snb;
	int					s;
	int					nb;
	int					lb;
}						t_type;

struct					s_lres{
	int					l_counter;
	int					mb_counter;
	int					sb_c;
	int					dot_flag;
	int					star_flag;
	int					bucks_flag;
	int					error_counter;
}						t_lres;

struct					s_f {
	int					h;
	int					l;
	int					jz;
	int					lb;
	int					sh;
	int					z;
	int					m;
	int					pl;
	int					sp;
	int					w;
	int					pz;
	int					pr;
	int					b;
}						t_f;

struct					s_recon{
	short				sign;
	unsigned int		exp;
	unsigned long int	mant;
}						t_recon;

struct					s_comp{
	int					exp;
	int					*integ;
	int					int_len;
	int					*fract;
	int					frc_len;
}						t_comp;

struct					s_buff{
	int					lim;
	int					pwr[1821];
	int					nbr[1821];
}						t_buff;

/*
** lim d(35.114) ld(549.1821)
*/

struct					s_result{
	char				*inter;
	int					inter_len;
	char				*fract;
	int					fract_len;
	char				*full_nbr;
}						t_result;

/*
** COMMON_FUNCTIONS
*/

int						skipable(char c);
int						skip_able(char c);
int						cs_check(char c);
void					safe_join(char **str, size_t len);
void					safe_sub_join(char *str, size_t len);
char					*ft_memjoin(char const *s1, size_t l1,
						char const *s2, size_t l2);
char					*ft_memsub(char const *s,
						unsigned int start, size_t len);

/*
** PROTO_CORE_FUNCTIONS
*/

void					pre_get_vhelper(void);
void					pre_get_vtail(void);
void					pre_get_turn(void);
void					pre_get_value(char c);
void					get_value(char c);
void					pf_core_helper(char **str, int *i);
void					pf_core(char *str);
int						ft_printf(const char *format, ...);

/*
** PROTO_FLAGS_FUNCTIONS
*/

void					reset_f(void);
int						easy_flags(char c);
void					flag_recognition(char c);
void					hl_recognition(char *str, int i);
int						grep_nbr(char *str, int i);
void					grep_dot_star(char **str, int *i, int *j);
int						grep_dot(char *str, int i);
int						grep_star(char *str, int i);
void					flag_passer_u(void);
int						flag_passer(char *str, int i);

/*
** SIGNED_INT
*/

int						ltoa_nbr_size(long long n, int b);
int						ltoa_prec_proc(int l, int g);
void					ltoa_prec_fill(char **result, int g, int p);
char					*ltoa_dec_prec(long long n, int b);
char					*ltoa_width(char *s);
void					ltoa_flag_proc(long long n);
void					pf_dec(long long n, int b);

/*
** UNS_OCT_HEX
*/

int						ltoa_base_nbr_size(unsigned long long int nb, int base);
int						ltoa_base_prec_proc(unsigned long long int nb,
						int nbl, int base);
void					ltoa_base_prec_fill(char **str, int base, int pre);
char					*ltoa_base_prec(unsigned long long int nb, int base);
void					ltoa_base_flag_proc(unsigned long long int nb,
						int base);
void					set_to_lower(char **str);
void					pf_uns_oct_hex(unsigned long long int nb,
						int base, int tl);

/*
** CHAR_STR_PTR
*/

void					pf_char(int c);
void					pf_str(char *str);
void					pf_ptr(unsigned long long int nbr, int base, int tl);

/*
** COLOUR
*/

int						colour_check(char *str, int i);
void					colour_join(char c, char s);
void					colour_bold(char c);
void					colour_tall(char c);

/*
** VLST_GET_TYPE_FUNCTIONS
*/

void					type_equlizer_tail(t_vlst **seer);
void					type_equalizer(void);
int						type_catcher(char c);
void					type_cs_runner(const char *str);
int						type_get(const char *str, int i);
void					type_resulter(const char *str, int i);
int						type_bucks_check(const char *str, int i);
int						type_star_check(const char *str, int i);
int						type_dot_check(const char *str, int i);
void					type_reset(void);

/*
** VLST_SIZE_COUNT_FUNCTIONS
*/

void					size_count(const char *str);
void					size_counter_reset(void);
int						size_cs_runner(const char *str, int i);
int						size_dot_count(const char *str, int i);
int						size_star_count(const char *str, int i);
int						size_bucks_count(const char *str, int i);
void					size_flag_reset(void);
int						size_type_catcher(char c);
void					size_counter_reset(void);
void					size_count_resulter(const char *str, int i);
int						size_max_finder(void);

/*
** VLST_MANAGE_FUNCTIONS
*/

void					*silent_grep(int nbr);
void					get_args(va_list vl);
void					get_dargs(va_list vl);
t_vlst					*vlst_new(int nbr);
t_vlst					*vlst_make(int nbr);
void					vlst_walk(int nbr);
void					vlst_starbucks(int nbr);
void					vlst_dstr(void);

/*
** FLOAT_FUNCTIONS
*/

int						ft_bitlen(unsigned long mant);
void					buff_zero(void);
void					clean_double(void);
char					get_sign(void);
void					inf_nan(void);
void					frc_pwr(void);
void					frc_add(void);
void					frc_start(void);
int						frc_arr_fill(char **str, int k, int i, int lim);
void					frc_arr_make(int i, int j);
void					frc_arr_size(void);
void					int_pwr(void);
void					int_add(void);
void					int_start(void);
int						int_arr_fill(char **str, int k, int i, int lim);
void					int_arr_make(int i, int j);
void					int_arr_size(void);
void					dbl_flag_preproc(int zero);
void					dbl_flag_aftproc(void);
void					tail_extender(char c);
int						head_helper(char **str, char c, int dif);
void					head_extender(char c);
void					get_positive(int len);
void					get_negative(int len);
void					get_hybrid(int dif);
void					get_powers(void);
void					l_inf_nan(void);
void					heavy_round(void);
int						long_round(int i, int rest);
int						deep_explore(int j);
void					dbl_round(void);
void					double_collector_full(void);
void					get_double(void);
void					dbl_flag_proc(int zero);
void					pf_double(void);
void					pf_ldouble(void);
void					get_lpositive(int len);
void					get_lnegative(int len);
void					get_lhybrid(int dif);
void					get_lpowers(void);
void					get_ldouble(void);

#endif

/*
** ===================== TYPES_FOR_vlst->type =====================
**
** 0 - none
** 1 - long
** 2 - int
** 3 - char *
** 4 - float
** 5 - void *
**
** ===================== MY_BONUSES =====================
**
** 1) *
** 2) $
** 3) *$ jz
** 4) bold
** 5) colour
**
** ===================== ALL_FLAGS =====================
**
** hh\h === counter ++ while reads, if it reads again it sets counter to 0
** l\ll === counter ++ while reads, if it reads again it sets counter to 0
** L
** #0-+_
** precision === greps number starting with non zero character
** width === greps number starting with . folowing by non zero character
**
** ===================== ALL_COLOURS =====================
**
** [0;31m	Red				{r-}
** [1;31m	Bold Red		{r+}
** [0;32m	Green			{g-}
** [1;32m	Bold Green		{g+}
** [0;33m	Yellow			{y-}
** [01;33m	Bold Yellow		{y+}
** [0;34m	Blue			{b-}
** [1;34m	Bold Blue		{b+}
** [0;35m	Magenta			{m-}
** [1;35m	Bold Magenta	{m+}
** [0;36m	Cyan			{c-}
** [1;36m	Bold Cyan		{c+}
** [0m		Reset			{w-}/{w+}
*/
