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

void	ft_freetab(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	free(tab[n]);
	free(tab);
}

static int	ft_getcount(char *str, char c)
{
	int	count;
	int	n;

	count = 0;
	n = 0;
	while (str[n])
	{
		while (str[n] && str[n] == c)
			n++;
		if (str[n])
			count++;
		while (str[n] && str[n] != c)
			n++;
		if (str[n] && str[n] != c)
			return (-1);
	}
	return (count);
}

static char	*ft_getword(char *str, int index, char c)
{
	char	*word;
	int		n;

	n = 0;
	while (str[index] && str[index] != c)
	{
		index++;
		n++;
	}
	index -= n;
	word = malloc(sizeof(char) * n + 1);
	if (!word)
		return (NULL);
	n = 0;
	while (str[index] && str[index] != c)
		word[n++] = str[index++];
	word[n] = '\0';
	return (word);
}

static int	ft_fill(char **tab, char *str, int index, int argc, char c)
{
	char	*word;
	int		size;

	size = 0;
	while (str[index] == c && size++ >= 0)
		index++;
	word = ft_getword(str, index, c);
	size += ft_strlen(word);
	tab[argc] = (char *)malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!tab[argc])
		return (-1);
	ft_strcpy(tab[argc], word);
	free(word);
	return (size);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		count;
	int		n;
	int		j;

	count = ft_getcount(str, c);
	n = 0;
	j = 0;
	if (count < 0)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (str[j] && n < count)
	{
		j += ft_fill(tab, str, j, n, c);
		n++;
	}
	tab[count] = 0;
	return (tab);
}
