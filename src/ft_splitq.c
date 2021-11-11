/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:12:32 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/04 15:19:36 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static size_t	ft_nextc(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c && !ft_isquote_now(s, i))
		i++;
	return (i);
}

static size_t	ft_nextnotc(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == c && !ft_isquote_now(s, i))
		i++;
	return (i);
}

static size_t	ft_getnum(char *s, char c)
{
	int		onword;
	size_t	count;
	size_t	i;

	count = 0;
	onword = 1;
	i = -1;
	if (*s != c)
		onword = 0;
	while (s[++i])
	{
		if (onword == 0 && s[i] != c)
			count++;
		printf("quote = %d\n", ft_isquote_now(s, i));
		if (s[i] == c && !ft_isquote_now(s, i))
			onword = 0;
		else
			onword = 1;
	}
	//printf("count = %zu\n", count);
	return (count);
}

static int	ft_myfrees(char **r, size_t n)
{
	size_t	i;
	int		b;

	i = -1;
	b = 1;
	while (++i < n)
		b *= r[i] != 0;
	if (b)
		return (1);
	i = -1;
	while (++i < n)
		if (r[i])
			free(r[i]);
	free(r);
	return (0);
}

char	**ft_splitq(char *s, char c)
{
	char			**r;
	size_t			i;
	size_t			j;
	size_t			n;
	size_t			n2;

	if (!s)
		return (0);
	n2 = ft_getnum(s, c);
	n = n2;
	r = malloc((n + 1) * sizeof(char *));
	if (!r)
		return (0);
	r[n] = 0;
	while (n--)
	{
		i = ft_nextnotc(s, c);
		j = ft_nextc(s + i, c);
		*r++ = ft_substr(s, i, j);
		s = s + j + i;
	}
	if (!ft_myfrees(r - n2, n2))
		return (0);
	return (r - n2);
}
