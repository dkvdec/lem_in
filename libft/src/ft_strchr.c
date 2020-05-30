/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:26:17 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:29 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p_s;
	char	cc;
	int		i;

	i = 0;
	p_s = (char*)s;
	cc = (char)c;
	while (*(p_s + i))
	{
		if (*(p_s + i) == cc)
			return (p_s + i);
		i++;
	}
	if (*(p_s + i) == cc)
		return (p_s + i);
	return (NULL);
}
