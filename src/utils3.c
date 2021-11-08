/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:39:00 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/08 14:39:02 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

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
	// free(str);
	// free(buff);
	return (line);
}

int	ft_spwordcount(char *str)
{
	int	n;

	n = 0;
	while (ft_isspace(str[n]) == 1)
		n++;
	while (ft_isalnumx(str[n]) == 1)
		n++;
	return (n);
}

/* int main(int argc, char *argv[])
{
	printf("%s\n", ft_itoas(1234));
} */