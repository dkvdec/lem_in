/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:21:23 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:19:41 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	unsigned char	cc;
	size_t			i;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(p_dst + i) = *(p_src + i);
		if (*(p_src + i++) == cc)
			return (dst + i);
	}
	return (NULL);
}
