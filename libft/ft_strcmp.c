/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:37:36 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:45:55 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	int				i;

	p_s1 = (unsigned char*)s1;
	p_s2 = (unsigned char*)s2;
	i = 0;
	while (*(p_s1 + i) == *(p_s2 + i))
	{
		if (*(p_s1 + i) == '\0' && *(p_s2 + i) == '\0')
			return (0);
		i++;
	}
	return ((int)(*(p_s1 + i) - *(p_s2 + i)));
}
