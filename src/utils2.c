/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:09:45 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/08 09:09:46 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

char	*ft_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str || !buff)
			return (NULL);
		str[0] = '\0';
	}
	line = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (line == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (str)
		while (str[++i] != '\0')
			line[i] = str[i];
	while (buff[j] != '\0')
		line[i++] = buff[j++];
	line[ft_strlen(str) + ft_strlen(buff)] = '\0';
	return (line);
}

char	*ft_replace_str(char *s, int start, int n, char *sub)
{
	int		i;
	int		sl;
	int		l;
	char	*tmp;

	sl = ft_strlen(sub);
	l = ft_strlen(s) - n + sl;
	tmp = malloc(sizeof(char) * (l + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < start)
		tmp[i] = s[i];
	i--;
	while (++i < start + sl)
		tmp[i] = sub[i - start];
	i--;
	while (++i < l)
		tmp[i] = s[i - sl + n];
	tmp[i] = 0;
	return (tmp);
}

char	*ft_tolower(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (str[n] >= 'A' && str[n] <= 'Z')
			str[n] += 32;
		n++;
	}
	return (str);
}

char	*ft_getword(char *str)
{
	char	*new;
	int		n;
	int		j;

	n = 0;
	j = 0;
	while (str[n] && ft_isspace(str[n]) == 1)
	{
		j++;
		n++;
	}
	while (str[n] && ft_isalnumx(str[n] == 1))
		n++;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	n = 0;
	while (str[j] && ft_isalnumx(str[j]) == 1)
		new[n++] = str[j++];
	new[n] = 0;
	return (new);
}

char	*ft_itoas(int nbr)
{
	char	*new;
	int		n;
	int		j;

	if (nbr < 0)
		return (NULL);
	n = nbr;
	j = 1;
	while (n > 9 && j++ >= 0)
		n /= 10;
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	n = 0;
	while (nbr > 9)
	{
		new[j - n - 1] = nbr % 10 + '0';
		nbr /= 10;
		n++;
	}
	new[j - n - 1] = nbr % 10 + '0';
	new[j] = 0;
	return (new);
}
