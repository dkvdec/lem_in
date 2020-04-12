/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:15:51 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 21:28:24 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

int			cs_check(char c)
{
	if (c == 'c' || c == 's' || c == 'p'
	|| c == 'd' || c == 'i' || c == 'o'
	|| c == 'u' || c == 'U' || c == 'x'
	|| c == 'X' || c == 'f' || c == 'F'
	|| c == '%')
	{
		return (1);
	}
	return (0);
}

int			skipable(char c)
{
	if (c == 'L')
		t_type.lb++;
	if (c == 'h' || c == 'l' || c == '$'
	|| c == '\'' || c == '#' || c == '+'
	|| c == '-' || c == ' ' || c == '0'
	|| c == 'z' || c == 'j' || c == 'L')
	{
		return (1);
	}
	return (0);
}

int			skip_able(char c)
{
	if (c == 'h' || c == 'l' || c == 'L'
	|| c == '\'' || c == '#' || c == '+'
	|| c == '-' || c == ' ' || c == '0'
	|| c == '$' || c == 'z' || c == 'j'
	|| c == '.' || c == '\'' || c == '*'
	|| ft_isdigit(c))
	{
		return (1);
	}
	return (0);
}

void		safe_join(char **str, size_t len)
{
	char	*tmp;

	tmp = ft_memjoin(t_line.out, t_line.len, *str, len);
	free(t_line.out);
	t_line.out = NULL;
	free(*str);
	*str = NULL;
	t_line.len += len;
	t_line.out = tmp;
	tmp = NULL;
}

void		safe_sub_join(char *str, size_t len)
{
	char	*sub;
	char	*tmp;

	sub = ft_memsub(str, 0, len);
	tmp = ft_memjoin(t_line.out, t_line.len, sub, len);
	free(t_line.out);
	t_line.out = NULL;
	free(sub);
	sub = NULL;
	t_line.len += len;
	t_line.out = tmp;
	tmp = NULL;
}
