/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheredat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:55:10 by dheredat          #+#    #+#             */
/*   Updated: 2019/04/23 14:26:13 by dheredat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordcounter(char const *s, char c)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	while (*(s + i))
	{
		if ((i == 0 && *(s + i) != c)
				|| (*(s + i + 1) && *(s + i + 1) != c && *(s + i) == c))
			counter++;
		i++;
	}
	return (counter);
}

static void		ft_black_hawk_down(char **prey, int j)
{
	if (j > 0)
	{
		while (--j >= 0)
			ft_strdel(&prey[j]);
	}
	ft_strdel(prey);
}

static void		ft_splitcore(char const *s, char c, char **nstra, int var)
{
	int ws;
	int i;
	int j;

	i = 0;
	j = -1;
	while (++j < var)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ws = 0;
			while (s[i + ws] && s[i + ws] != c)
				ws++;
			if (ws <= 0 || !(nstra[j] = (char*)ft_strnew(ws)))
			{
				ft_black_hawk_down(nstra, j);
				break ;
			}
			ws = 0;
			while (s[i] && s[i] != c)
				nstra[j][ws++] = s[i++];
		}
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**nstra;
	int		var;

	if (!s)
		return (NULL);
	nstra = NULL;
	var = ft_wordcounter(s, c);
	if ((nstra = (char**)malloc(sizeof(char*) * (var + 1))))
	{
		nstra[var] = NULL;
		if (var > 0)
			ft_splitcore(s, c, nstra, var);
	}
	return (nstra);
}
