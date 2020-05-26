/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:30:07 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:13:39 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	return (c >= 65 && c <= 90) ? 1 : 0;
}

static int	ft_islower(int c)
{
	return (c >= 97 && c <= 122) ? 1 : 0;
}

int			ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c)) ? 1 : 0;
}
