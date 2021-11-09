/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:15 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/04 12:10:28 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	t_main		main;
	char		*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline(PROMPT);
		ft_read_chev(line, &main);
		//expand_variables(line);
		//pipe_de_fin();
		ft_parser(main.line, &main);
		//ft_exec(&main);
		ft_freeshell(&main);
	}
	return (1);
}

/* void	ft(void)
{
	while (str)
		if << truc
		{
			makestring (truc + index);
		 	fd = open("temp/string", O_CREAT | O_TRUNC | O_WRONLY, 0644);
			check fd
			line = readline();
			while(line != truc)
				line = readline("> ");
				check readline
				ft_putendl_fd(line, fd);
			close(fd);
			remplacer << truc par < temp/fichier
		}
} */

void	ft_read_chev(char *line, t_main *main)
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
			main->chev.nbrs = ft_strjoin("/tmp/", ft_itoas(main->chev.nbr));
			main->chev.term = ft_strjoin(main->chev.nbrs, ft_getword(&line[n]));
			j = ft_spwordcount(&line[n]);
			main->line = ft_replace_str(line, n - 1, j + 1, main->chev.term);
			line = main->line;
		}
		n++;
	}
}
