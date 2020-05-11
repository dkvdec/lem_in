/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:23:46 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:21:31 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	cc;
	size_t			i;

	i = 0;
	p_s = (unsigned char*)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (*(p_s + i) == cc)
			return (p_s + i);
		i++;
	}
	return (NULL);
}
