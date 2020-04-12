/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:25:55 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 20:17:45 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			l_dst;
	size_t			l_src;
	size_t			i;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	i = 0;
	l_dst = ft_strnlen(dst, size);
	l_src = ft_strlen(src);
	if (size > l_dst)
	{
		while (i < size - l_dst - 1 && i < l_src)
		{
			*(p_dst + l_dst + i) = *(p_src + i);
			i++;
		}
		*(p_dst + l_dst + i) = '\0';
	}
	return (l_dst + l_src);
}
