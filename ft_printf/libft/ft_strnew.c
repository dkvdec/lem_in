/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:04:33 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 20:29:08 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *newstr;

	if ((size + 1 == 0) || !(newstr = (char*)ft_memalloc(size + 1)))
		return (NULL);
	while (size)
	{
		*(newstr + size) = '\0';
		size--;
	}
	return (newstr);
}
