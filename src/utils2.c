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
	while(str[n] && ft_isspace(str[n]) == 1)
	{
		j++;
		n++;
	}
	while(str[n] && ft_isalnumx(str[n] == 1))
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

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_isalnumx(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 0)
		return (0);
	else if ((c >= 0 && c <= 32) || c == 127)
		return (0);
	return (1);
}

char    *ft_replace_str(char *s, int start, int n, char *sub)
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

/* int main(int argc, char *argv[])
{
	printf("%s\n", ft_getword(argv[1]));
} */