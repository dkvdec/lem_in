/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 15:54:01 by dheredat          #+#    #+#             */
/*   Updated: 2019/05/01 16:53:27 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int					minflag;
	long				nbr;
	int					i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	nbr = 0;
	minflag = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		minflag = str[i] == '-' ? -1 : 1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr * 10 + (str[i] - '0')) / 10 != nbr)
			return ((minflag == -1) ? 0 : -1);
		nbr = nbr * 10 + (str[i++] - '0');
	}
	return ((int)((minflag == -1) ? -nbr : nbr));
}
