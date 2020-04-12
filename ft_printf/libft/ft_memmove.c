/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:23:25 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:28:32 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;

	if (!dst && !src)
		return (dst);
	tmp = (unsigned char*)malloc(sizeof(unsigned char) * (len));
	if (tmp)
	{
		ft_memcpy(tmp, src, len);
		ft_memcpy(dst, tmp, len);
		free(tmp);
		tmp = NULL;
	}
	return (dst);
}
