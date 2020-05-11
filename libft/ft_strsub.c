/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:28:29 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/23 14:38:11 by dheredat         ###   ########.fr       */
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
