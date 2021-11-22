/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:11:15 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/22 11:29:15 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include "../inc/minishell.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	close_pipes(int *pipes, size_t n)
{
	n = n * 2;
	while (n--)
		close(*pipes++);
}

void	*exec_perror(const char *str)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(": ", 2);
	perror(str);
	return (0);
}

int	is_abs_path(const char *str)
{
	return (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3));
}

void	init_r_w(int *r, int *w, int i, int pipecount, int *pipes)
{
	if ((i - 1) * 2 < 0)
		*r = 0;
	else
		*r = pipes[(i - 1) * 2];
	if ((i - 1) * 2 + 3 > pipecount * 2 - 1)
		*w = 1;
	else
		*w = pipes[(i - 1) * 2 + 3];
}

int	wexitstatus(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}
