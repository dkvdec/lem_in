/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:01:56 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:15:01 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	i;
	char	*newstr;

	if (!(s))
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while ((*(s + i) == ' ' || *(s + i) == '\n' || *(s + i) == '\t'))
		i++;
	if (i < len)
		while ((*(s + len - 1) == ' ' || *(s + len - 1) == '\n'
					|| *(s + len - 1) == '\t'))
			len--;
	newstr = ft_strsub(s, i, len - i);
	return (newstr);
}
