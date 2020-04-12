/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:29:41 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/30 20:15:36 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	freepeerautismtest(const char *str, int minflag)
{
	int		n;
	char	*min;
	char	*max;

	min = "9223372036854775808";
	max = "9223372036854775807";
	n = 0;
	while (ft_isdigit(str[n]) && n < 20)
		n++;
	if (n > 19)
		return (1);
	if (n < 19)
		return (0);
	if (minflag == -1)
		return (ft_strncmp(str, min, 19));
	else
		return (ft_strncmp(str, max, 19));
}

int			ft_atoi(const char *str)
{
	int					minflag;
	unsigned long long	nbr;
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
	while (str[i] == '0')
		i++;
	if (freepeerautismtest(str + i, minflag) > 0)
		return ((minflag == -1) ? 0 : -1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	return ((int)(nbr * minflag));
}

int			main(int argc, char **argv)
{
	printf("%d\n%d\n", ft_atoi(argv[1]), atoi(argv[1]));
	return (0);
}
