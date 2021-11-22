/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:15 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/22 10:59:11 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

t_main	*g_glb;

static int	ft_envpinit(t_main *main, char **envp, char **argv, int argc)
{
	(void)argv;
	(void)argc;
 	tcgetattr(0, &main->old);
 	tcgetattr(0, &main->new);
 	main->new.c_lflag &= ~(ECHOCTL);
 	tcsetattr(0, TCSANOW, &main->new);
	main->rval = 0;
	main->cline = NULL;
	g_glb = main;
	main->envp = init_envp(envp);
	if (!envp)
		return (1);
	main->locals = init_locals();
	if (!main->locals)
	{
		ft_freetab(main->envp);
		return (1);
	}
	ft_signal_main();
	main->error = 0;
	return (0);
}

static int	ft_first_check(t_main *main)
{
	if (!main->line)
	{
		ft_freetab(main->envp);
		ft_freetab(main->locals);
		free(main->line);
		exit(0);
	}
	if (!*main->line)
		return (ft_myfree(main->line));
	if (ft_dpipe_check(main))
		return (ft_myfree(main->line));
	if (ft_isinquote_now(main->line, ft_strlen(main->line)))
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (ft_myfree(main->line));
	}
	if (ft_parse_error(main) || ft_single_pipe(main))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \
`|'\n", 2);
		return (ft_myfree(main->line));
	}
	return (0);
}

static int	ft_chevpipe_loop(t_main *main)
{
	if (main->error == 1)
		return (0);
	if (ft_read_chev(main) == 1)
		return (ft_myfreemain(main));
	if (main->error == 1)
		return (0);
	if (main->line[ft_strlen(main->line) - 1] == '|')
		if (ft_read_lpipe(main) == 1)
			return (ft_myfreemain(main));
	return (0);
}

static int	ft_parse(t_main *main)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	main->line = expand_variables(main->line, main->envp, main->locals, main->rval);
	if (!main->line)
		return (ft_freeshell(main));
	if (ft_parser(main))
		return (ft_freeshell(main));
	if (ft_syntax_check(main, n, j))
		return (ft_freeshell_continue(main));
	if (ft_remquote(main))
		return (ft_freeshell(main));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main			main;

	if (ft_envpinit(&main, envp, argv, argc))
		return (1);
	while (1)
	{
		main.error = 0;
		main.line = readline(PROMPT);
		if (main.line && main.line[0])
			add_history(main.line);
		if (ft_first_check(&main))
			continue ;
		ft_getcount(&main);
		while (ft_check_chevpipe(main.line) == 1)
			if (ft_chevpipe_loop(&main))
				return (1);
		if (main.error && ft_myfree(main.line))
			continue ;
		if (ft_parse(&main))
		{
			if (main.error)
				continue ;
			return (1);
		}
		if (ft_fillstruct(&main))
			return (ft_freeshell2(&main));
		if (!main.pipecount && !ft_strncmp(main.cline[0].argv[0], "exit", -1))
		{
			write(1, "exit\n", 5);
			main.rval = ft_exit(main.cline[0].argv);
			ft_freeshell3(&main);
			if (main.rval != -1)
				exit(main.rval);
			else
			{
				main.rval = 1;
				continue;
			}
		}
		signal(SIGINT, ft_sigint_exec);
		if (!main.error)
			main.rval = ft_exec(&main);
		ft_signal_main();
		ft_freeshell3(&main);
	}
	return (0);
}
