/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:18:40 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:15:03 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90) ? 1 : 0;
}

int			ft_tolower(int c)
{
	return (ft_isupper(c)) ? (c + 32) : c;
}
