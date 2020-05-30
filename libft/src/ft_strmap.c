/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:52:15 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:44 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*newstr;
	int		i;

	if (!(s) || !(newstr = (char*)ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(newstr + i) = (char)(*f)(*(s + i));
		i++;
	}
	return (newstr);
}
