/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 08:34:32 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/14 08:34:33 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

char	*ft_remquotestr(char *str)
{
	char	*new;
	int		count;
	int		n;

	count = 0;
	n = 0;
	while (str[n])
		if (!ft_isquote(str[n++]))
			count++;
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	count = 0;
	n = 0;
	while (str[n])
	{
		if (!ft_isquote(str[n]))
			new[count++] = str[n++];
		else
			n++;
	}
	new[count] = 0;
	free(str);
	return (new);
}

int	ft_remquote1(t_main *main, char *str, int n1, int j)
{
	char	*new;
	int		count;
	int		n;

	count = 0;
	n = 0;
	while (str[n])
		if (!ft_isquote(str[n++]))
			count++;
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (1);
	count = 0;
	n = 0;
	while (str[n])
	{
		if (!ft_isquote(str[n]))
			new[count++] = str[n++];
		else
			n++;
	}
	new[count] = 0;
	free(main->cline[n1].argv[j]);
	main->cline[n1].argv[j] = new;
	return (0);
}

int	ft_remquote(t_main *main)
{
	int	n;
	int	j;

	n = 0;
	while (main->cline[n].line)
	{
		j = 0;
		while (main->cline[n].argv[j])
		{
			if (ft_remquote1(main, main->cline[n].argv[j], n, j))
				return (1);
			j++;
		}
		ft_showtab(main->cline[n].argv);
		n++;
	}
	return (0);
}
