/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:04:33 by dheredat          #+#    #+#             */
/*   Updated: 2020/04/13 11:37:33 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *newstr;

	if ((size + 1 == 0) || !(newstr = (char*)ft_memalloc(size + 1)))
		return (NULL);
	// while (size)
	// {
	// 	*(newstr + size) = '\0';
	// 	size--;
	// }
	return (newstr);
}
