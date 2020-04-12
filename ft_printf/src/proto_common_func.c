/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto_common_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:09:00 by dheredat          #+#    #+#             */
/*   Updated: 2019/10/26 17:09:58 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto_vlst.h"

char		*ft_memjoin(char const *s1, size_t l1, char const *s2, size_t l2)
{
	char	*newstr;

	if (!(s1) || !(s2))
		return (NULL);
	if (l1 + l2 < l1 || l1 + l2 < l2
	|| !(newstr = (char*)malloc(l1 + l2 + 1)))
		return (NULL);
	ft_memset(newstr, 0, l1 + l2);
	ft_memcpy(newstr, s1, l1);
	ft_memcpy(newstr + l1, s2, l2);
	return (newstr);
}

char		*ft_memsub(char const *s, unsigned int start, size_t len)
{
	char			*newstr;

	if (!(s) || len + 1 < len || !(newstr = (char*)malloc(len + 1)))
		return (NULL);
	ft_memset(newstr, 0, len);
	ft_memcpy(newstr, s + start, len);
	return (newstr);
}
