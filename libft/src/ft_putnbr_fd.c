/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <dheredat@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 17:17:25 by dheredat          #+#    #+#             */
/*   Updated: 2020/05/26 10:14:22 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int step;

	step = 1;
	if (n != 0)
	{
		step = 1000000000;
		while (n / step == 0)
			step /= 10;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (step != 0)
	{
		ft_putchar_fd((n < 0) ? n / step * (-1) + '0' : n / step + '0', fd);
		n %= step;
		step /= 10;
	}
}
