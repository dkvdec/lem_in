/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:39:30 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:45 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;

	if (!(s) || !(newstr = (char*)ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (*(s + ++i))
		*(newstr + i) = (char)(*f)(i, *(s + i));
	return (newstr);
}
