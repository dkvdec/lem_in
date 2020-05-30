/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 20:09:31 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:23 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	step;

	step = 1;
	if (n != 0)
	{
		step = 1000000000;
		while (n / step == 0)
			step /= 10;
	}
	if (n < 0)
		ft_putchar('-');
	while (step != 0)
	{
		ft_putchar((n < 0) ? n / step * (-1) + '0' : n / step + '0');
		n %= step;
		step /= 10;
	}
}
