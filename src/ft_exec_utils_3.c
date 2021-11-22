/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:05:28 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/22 12:48:20 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include "../inc/minishell.h"

void	*exec_perror(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_export(char ***envp, char ***locals, char **argv);
int		ft_unset(char ***envp, char ***locals, char **argv);
int		ft_cd(char ***envp, char **argv);
void	close_pipes(int *pipes, size_t n);

int	open_files(t_file *files, int n)
{
	int	b;
	int	i;

	b = 1;
	i = -1;
	while (++i < n)
	{
		files[i].fd = open(files[i].name, files[i].flags, 0644);
		if (files[i].fd == -1)
			b = (int)exec_perror(files[i].name);
	}
	return (b);
}

void	close_files(t_file *files, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (files[i].fd != -1)
			if (close(files[i].fd) == -1)
				exec_perror("close");
}

void	open_pipes(int *pipes, size_t n)
{
	size_t	i;

	i = 0;
	while (i / 2 < n)
	{
		if (pipe(pipes + i) == -1)
		{
			exec_perror("pipe");
			close_pipes(pipes, i / 2);
		}
		i += 2;
	}
}

int	is_c_e_u(const char *s)
{
	return (!ft_strncmp(s, "cd", -1)
		|| !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1));
}

int	exec_c_e_u(t_comm comm, char ***envp, char ***locals)
{
	open_files(comm.file_in, comm.rin);
	close_files(comm.file_in, comm.rin);
	open_files(comm.file_out, comm.rout);
	close_files(comm.file_out, comm.rout);
	if (!ft_strncmp(comm.argv[0], "cd", -1))
		return (ft_cd(envp, comm.argv));
	if (!ft_strncmp(comm.argv[0], "export", -1))
		return (ft_export(envp, locals, comm.argv));
	return (ft_unset(envp, locals, comm.argv));
}
