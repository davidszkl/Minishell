/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:17:23 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/04 12:17:27 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static int	ft_getpipecount(char *line)
{
	int	count;
	int	n;

	count = 0;
	n = 0;
	while (line[n])
		if (line[n++] == '|')
			count++;
	return (count);
}

int	ft_insert_space3(char *str, int index, int t, int mod)
{
	if (mod == 1)
	{
		str[index] = ' ';
		str[index + 1] = t;
		str[index + 2] = ' ';
		return (3);
	}
	else if (mod == 2)
	{
		str[index] = ' ';
		str[index + 1] = t;
		str[index + 2] = t;
		str[index + 3] = ' ';
		return (4);
	}
	return (-1);
}

static char	*ft_insert_space2(char *new, char *str)
{
	int		n;
	int		t;
	int		j;

	n = 0;
	j = 0;
	while (str[n])
	{
		if (str[n] == '<' && str[n - 1] != '<' && str[n + 1] != '<')
			j += ft_insert_space3(new, j, str[n], 1);
		else if (str[n] == '<' && str[n - 1] != '<' && str[n + 1] == '<')
		{
			j += ft_insert_space3(new, j, str[n], 2);
			n++;
		}
		else if (str[n] == '>' && str[n - 1] != '>' && str[n + 1] != '>')
		{
			j += ft_insert_space3(new, j, str[n], 1);
		}
		else if (str[n] == '>' && str[n - 1] != '>' && str[n + 1] == '>')
		{
			j += ft_insert_space3(new, j, str[n], 2);
			n++;
		}
		else if (str[n] == '|')
			j += ft_insert_space3(new, j, str[n], 1);
		else
			new[j++] = str[n];
		n++;
	}
	new[j] = 0;
	n = 0;
	return (new);
}

static char	*ft_insert_space(char *str)
{
	int		n;
	int		count;
	char	*new;

	n = 0;
	count = 0;
	while (str[n])
	{
		if (str[n] == '<' && str[n - 1] != '<')
			count += 2;
		else if (str[n] == '>' && str[n - 1] != '>')
			count += 2;
		else if (str[n] == '|')
			count += 2;
		n++;
	}
	new = malloc(sizeof(char) * (ft_strlen(str) + count + 1));
	if (!new)
		return (NULL);
	new = ft_insert_space2(new, str);
	return (new);
}

int	ft_parser(char *line, t_main *main)
{
	char	**tab;
	int		n;

	main->pipecount = ft_getpipecount(line);
	tab = malloc(sizeof(char *) * (main->pipecount + 1));
	if (!tab)
		return (-1);
	main->cline = malloc(sizeof(t_comm) * main->pipecount);
	if (!main->cline)
		return (-1);
	tab = ft_split(line, '|');
	ft_showtab(tab);
	n = 0;
	while (n < main->pipecount)
	{
		main->cline[n].line = ft_insert_space(tab[n]);
		//main->cline[n].argv = ft_split(main->cline[n].line, ' ');
		n++;
	}
	ft_freetab(tab);
	return (1);
}
