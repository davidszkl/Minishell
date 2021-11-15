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

	(void)argc;
	(void)argv;
	while (1)
	{
		main.line = readline(PROMPT);
		if (ft_isinquote_now(main.line, 0))
			return (ft_myfree(main.line));
		ft_getcount(&main);
		while (ft_check_chevpipe(main.line) == 1)
		{
			if (ft_read_chev(&main) == 1)
				return (ft_myfree(main.line));
			if (main.line[ft_strlen(main.line) - 1] == '|')
				if (ft_read_lpipe(&main) == 1)
					return (ft_myfree(main.line));
		}
		ft_getcount(&main);
		//expand_variables(line);
		ft_parser(&main);
		ft_remquote(&main);
		//ft_exec(&main);
		ft_freeshell(&main);
	}
	return (0);
}
