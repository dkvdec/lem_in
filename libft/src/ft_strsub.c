/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:28:29 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:15:00 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*newstr;
	size_t			i;

	if (!(s) || ft_strlen(s) < (size_t)start
			|| !(newstr = (char*)ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len && *(s + start + i))
	{
		*(newstr + i) = *(s + start + i);
		i++;
	}
	return (newstr);
}
