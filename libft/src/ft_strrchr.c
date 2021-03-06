/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:26:44 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:57 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p_s;
	char	cc;
	char	*p_last;
	int		i;

	i = 0;
	p_s = (char*)s;
	cc = (char)c;
	p_last = NULL;
	while (*(p_s + i))
	{
		if (*(p_s + i) == cc)
			p_last = p_s + i;
		i++;
	}
	if (*(p_s + i) == cc)
		p_last = p_s + i;
	return (p_last) ? p_last : NULL;
}
