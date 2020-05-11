/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:27:18 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 20:39:13 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*p_hays;
	char	*p_need;
	int		i;
	int		j;

	p_hays = (char*)haystack;
	p_need = (char*)needle;
	if (!(*(p_need)))
		return (p_hays);
	i = 0;
	while (*(p_hays + i))
	{
		j = 0;
		while (*(p_hays + i + j) == *(p_need + j))
		{
			if (!(*(p_need + ++j)))
				return (p_hays + i);
		}
		i++;
	}
	return (NULL);
}
