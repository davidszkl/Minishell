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

extern t_main *g_glb;

static void ft_sigint(int signbr)
{
    int n;

    n = 0;
    if (!g_glb->cline)
    {
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
        return ;
    }
    while (g_glb->cline[n].line)
    {
        if (g_glb->cline[n].pid)
            kill(g_glb->cline[n].pid, signbr);
        n++;
    }
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

static void ft_sigabrt(int signbr)
{
    int n;

    n = 0;
    if (!g_glb->cline)
        return ;
    while (g_glb->cline[n].line)
    {
        if (g_glb->cline[n].pid)
            kill(g_glb->cline[n].pid, signbr);
        n++;
    }
}

int ft_signal_handler(void)
{
    signal(SIGINT, ft_sigint);
    signal(SIGABRT, ft_sigabrt);
    return (0);
}
