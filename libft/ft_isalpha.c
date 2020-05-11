/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:30:07 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:01:06 by dheredat         ###   ########.fr       */
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
