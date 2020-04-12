/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:32:08 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/22 19:08:14 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_itoacpy(int n, int step, char *str)
{
	int i;

	i = 0;
	if (n < 0)
		str[i++] = '-';
	while (step != 0)
	{
		str[i++] = (n < 0) ? n / step * (-1) + '0' : n / step + '0';
		n %= step;
		step /= 10;
	}
}

char			*ft_itoa(int n)
{
	char	*str;
	int		step;
	int		counter;

	counter = 1;
	step = 1;
	if (n != 0)
	{
		counter = 0;
		step = 1000000000;
		while (n / step == 0 && step != 0)
		{
			step /= 10;
			counter++;
		}
		counter = 10 - counter;
		if (n < 0)
			counter++;
	}
	if ((str = (char*)ft_strnew(counter)))
		ft_itoacpy(n, step, str);
	else
		return (NULL);
	return (str);
}
