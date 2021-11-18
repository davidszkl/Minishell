/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:15 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/18 13:27:29 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

t_main	*g_glb;

static int	ft_envpinit(t_main *main, char **envp)
{
	main->envp = init_envp(envp);
	if (!envp)
		return (1);
	main->locals = init_locals();
	if (!main->locals)
	{
		ft_freetab(main->envp);
		return (1);
	}
	ft_signal_handler();
	return (0);
}

static int	ft_first_check(t_main *main)
{
	if (!main->line)
	{
		ft_freetab(main->envp);
		ft_freetab(main->locals);
		exit(0);
	}
	if (!*main->line)
		return (ft_myfree(main->line));
	if (ft_isinquote_now(main->line, ft_strlen(main->line)))
		return (write(1, "unclosed quote\n", 15));
	return (0);
}

static int	ft_chevpipe_loop(t_main *main)
{
	if (ft_read_chev(main) == 1)
		return (ft_myfreemain(main));
	if (main->line[ft_strlen(main->line) - 1] == '|')
		if (ft_read_lpipe(main) == 1)
			return (ft_myfreemain(main));
	return (0);
}

static int	ft_parse(t_main *main)
{
	main->line = expand_variables(main->line, main->envp, main->locals);
	if (!main->line)
	{
		ft_freeshell(main);
		return (1);
	}
	if (ft_parser(main))
	{
		ft_freeshell(main);
		return (1);
	}
	if (ft_remquote(main))
	{
		ft_freeshell(main);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main			main;
	struct termios	old;
	struct termios	new;

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &new);
	g_glb = &main;
	g_glb->cline = NULL;
	(void)argv;
	(void)argc;
	if (ft_envpinit(&main, envp))
		return (1);
	while (1)
	{
		main.line = readline(PROMPT);
		if (ft_first_check(&main))
			continue ;
		if (ft_parse_error(&main))
			return (ft_myfreemain(&main));
		ft_getcount(&main);
		while (ft_check_chevpipe(main.line) == 1)
			if (ft_chevpipe_loop(&main))
				return (1);
		if (ft_parse(&main))
			return (1);
		if (ft_fillstruct(&main))
			return (ft_freeshell2(&main));
		if (ft_tabcheck(&main))
			return (ft_freeshell2(&main));
		ft_exec(&main);
		ft_freeshell3(&main);
	}
	return (0);
}
