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
		ft_getcount(line, &main);
		/* while(y a << || y a | de fin)
		{
			if (y a <<)
				trucmush;
			if (y a | de fin)
				truc pour ca

		} */
		if (ft_read_chev(line, &main) == 1)
		{
			//ft_exit(&main);
			return (1);
		}
		//pipe_de_fin();
		//expand_variables(line);
		ft_parser(&main);
		//ft_exec(&main);
		ft_freeshell(&main);
	}
	return (0);
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
