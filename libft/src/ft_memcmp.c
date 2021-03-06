/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:09:01 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:10 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	int				i;

	p_s1 = (unsigned char*)s1;
	p_s2 = (unsigned char*)s2;
	i = 0;
	while (n--)
	{
		if (*(p_s1 + i) != *(p_s2 + i))
			return (*(p_s1 + i) - *(p_s2 + i));
		i++;
	}
	return (0);
}
