/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:27:39 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 20:32:40 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p_hays;
	char	*p_need;
	size_t	len_need;
	size_t	i;

	p_hays = (char *)haystack;
	p_need = (char *)needle;
	if (!(*(p_need)))
		return (p_hays);
	i = 0;
	len_need = ft_strlen(p_need);
	while (*(p_hays + i) && len)
	{
		if (len_need > len)
			break ;
		if (*(p_hays + i) == *p_need)
		{
			if (!(ft_strncmp((p_hays + i), p_need, len_need)))
				return (p_hays + i);
		}
		len--;
		i++;
	}
	return (NULL);
}
