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

int	ft_getcount(t_main *main)
{
	int	n;

	n = 0;
	main->pipecount = 0;
	main->dchevcount = 0;
	main->chev.nbr = 0;
	main->error = 0;
	while (main->line[n])
	{
		if (main->line[n] == '|')
			main->pipecount++;
		if (ft_is_chev(main->line, n) == 1)
			main->dchevcount++;
		n++;
	}
	return (0);
}

static int	ft_insert_space3(char *str, int index, int t, int mod)
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
	int		j;

	n = 0;
	j = 0;
	while (str[n])
	{
		if (ft_is_chev(str, n) == 3 || ft_is_chev(str, n) == 4 || str[n] == '|')
			j += ft_insert_space3(new, j, str[n], 1);
		else if (ft_is_chev(str, n) == 1 || ft_is_chev(str, n) == 2)
			j += ft_insert_space3(new, j, str[n++], 2);
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
	if (!str)
		return (ft_strdup(""));
	while (str[n])
	{
		if (ft_is_chev(str, n) || str[n] == '|')
			count += 2;
		n++;
	}
	new = malloc(sizeof(char) * (ft_strlen(str) + count + 1));
	if (!new)
		return (NULL);
	new = ft_insert_space2(new, str);
	free(str);
	return (new);
}

int	ft_parser(t_main *main)
{
	char	**tab;
	int		n;

	n = 0;
	main->cline = malloc(sizeof(t_comm) * (main->pipecount + 2));
	if (!main->cline)
		return (1);
	main->line = ft_insert_space(main->line);
	if (!main->line)
		return (1);
	tab = ft_split(main->line, '|');
	if (!tab)
		return (1);
	while (n < main->pipecount + 1)
	{
		main->cline[n].line = tab[n];
		main->cline[n].argv = ft_split(main->cline[n].line, ' ');
		if (!main->cline[n].argv)
			return (1);
		ft_showtab(main->cline[n].argv);
		n++;
	}
	main->cline[n].line = NULL;
	ft_freetab(tab);
	return (0);
}
