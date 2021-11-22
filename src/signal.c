/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:47:34 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/17 12:47:36 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

extern t_main	*g_glb;

void	ft_sigint_main(int signbr)
{
	(void)signbr;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int signbr)
{
	(void)signbr;
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_exec(int signbr)
{
	(void)signbr;
	write(1, "^C\n", 3);
	rl_on_new_line();
}

int	ft_signal_main(void)
{
	signal(SIGINT, ft_sigint_main);
	signal(SIGQUIT, ft_sigquit);
	return (0);
}

void	ft_sigint_heredoc(int signbr)
{
	(void)signbr;
	kill(g_glb->r, 9);
	tcsetattr(0, TCSANOW, &g_glb->new);
	write(1, "\n", 1);
	g_glb->error = 1;
}
