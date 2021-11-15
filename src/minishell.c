/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:15 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/15 17:30:26 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main		main;

	(void)argv;
	(void)argc;
	//ajouter le free de envp et locals dans freeshell ou jsp mais il faut.
	main.envp = init_envp(envp);
	if (!envp)
		return (1);
	main.locals = init_locals();
	if (!main.locals)
	{
		ft_freetab(main.envp);
		return (1);
	}
	while (1)
	{
		main.line = readline(PROMPT);
		if (!*main.line)
		{
			free(main.line);
			continue ;
		}
		if (ft_isinquote_now(main.line, ft_strlen(main.line)))
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
		//expand_variables(main.line, main.envp, main.locals);
		//la fonction ne modifie pas main.line mais retourne le resultat. faut assigner cette
		//valeur de retour a main.line + free ancien main.line et checker si c'est pas null
		if (ft_parser(&main))
			return (ft_freeshell(&main));
		if (ft_remquote(&main))
			return (ft_freeshell(&main));
		if (ft_fillstruct(&main))
			return (ft_freeshell2(&main));
		//ft_exec(&main);
		ft_freeshell2(&main);
	}
	return (0);
}
