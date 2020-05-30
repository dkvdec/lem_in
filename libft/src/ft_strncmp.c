/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:29:13 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:48 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	p_s1 = (unsigned char*)s1;
	p_s2 = (unsigned char*)s2;
	i = 0;
	if (!n)
		return (0);
	while (*(p_s1 + i) == *(p_s2 + i) && i < n)
	{
		if ((*(p_s1 + i) == '\0' && *(p_s2 + i) == '\0')
				|| ++i == n)
			return (0);
	}
	return ((int)(*(p_s1 + i) - *(p_s2 + i)));
}
