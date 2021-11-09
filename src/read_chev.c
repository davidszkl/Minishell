/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:44 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/09 11:02:46 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

/* static void	ft_free(t_main *main)
{
	free(main->chev.nbrs);
	free(main->chev.term);
} */

static void	ft_read_chev1(char *line, t_main *main)
{
	int		n;
	int		j;

	n = 0;
	main->chev.nbr = 0;
	while (line[n])
	{
		if (line[n] == '|')
			main->chev.nbr++;
		if (line[n] == '<' && line[n + 1] == '<' && line[n - 1] != '<')
		{
			n += 2;
			//ft_free(main);
			main->chev.nbrs = ft_strjoin("/tmp/", ft_itoas(main->chev.nbr));
			main->chev.term = ft_strjoin(main->chev.nbrs, ft_getword(&line[n]));
			j = ft_spwordcount(&line[n]);
			line = ft_replace_str(line, n - 1, j + 1, main->chev.term);
		}
		n++;
	}
	main->line = line;
	printf("line after read chev = %s\n", main->line);
}

void	ft_read_chev(char *line, t_main *main)
{
	ft_read_chev1(line, main);
}
