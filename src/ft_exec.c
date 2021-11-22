/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:30:55 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/22 11:29:00 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include "../inc/minishell.h"

void	init_r_w(int *r, int *w, int i, int pipecount, int *pipes);
int		wexitstatus(int status);
void	close_pipes(int *pipes, size_t n);
void	*exec_perror(const char *str);
char	*find_command_wrapper(char *str, char **envp);
int		is_c_e_u(const char *s);
int		exec_c_e_u(t_comm comm, char ***envp, char ***locals);
void	open_pipes(int *pipes, size_t n);
void	close_files(t_file *files, int n);
int		open_files(t_file *files, int n);

static void	enter_child(int fd_r, int fd_w, t_comm comm, char **envp, int *pipes, size_t pipecount, t_main *main)
{
	char	*path;
	int		b;

	b = 1;
	if (comm.rin)
	{
		b = open_files(comm.file_in, comm.rin);
		close_files(comm.file_in, comm.rin - 1);
		fd_r = comm.file_in[comm.rin - 1].fd;
	}
	if (b && comm.rout)
	{
		open_files(comm.file_out, comm.rout);
		close_files(comm.file_out, comm.rout - 1);
		fd_w = comm.file_out[comm.rout - 1].fd;
	}
	if (!b || fd_r == -1 || fd_w == -1)
	{
		close_pipes(pipes, pipecount);
		free(pipes);
		ft_freeshell4(main);
		exit(1);
	}
	if (dup2(fd_r, 0) == -1)
		b = (int)exec_perror("dup2");
	if (b && dup2(fd_w, 1) == -1)
		b = (int)exec_perror("dup2");
	if (comm.rin)
		close(fd_r);
	if (comm.rout)
		close(fd_w);
	close_pipes(pipes, pipecount);
	free(pipes);
	path = find_command_wrapper(comm.argv[0], envp);
	if (!path)
	{
		ft_freeshell4(main);
		exit(1);
	}
	if (b)
		execve(path, comm.argv, envp);
	exec_perror(path);
	free(path);
	ft_freeshell4(main);
	exit(1);
}

int	ft_exec(t_main *main)
{
	const size_t	n = main->pipecount + 1;
	int				status;
	int				fd_r;
	int				fd_w;
	size_t			i;
	int				*pipes;

	if (n == 1 && is_c_e_u(main->cline[0].argv[0]))
		return (exec_c_e_u(main->cline[0], &main->envp, &main->locals));
	pipes = 0;
	if (main->pipecount)
	{
		pipes = malloc(sizeof(int) * main->pipecount * 2);
		if (!pipes)
			return (1 + (int)exec_perror("malloc"));
	}
	open_pipes(pipes, main->pipecount);
	i = -1;
	while (++i < n)
	{
		init_r_w(&fd_r, &fd_w, i, main->pipecount, pipes);
		main->cline[i].pid = fork();
		if (main->cline[i].pid == -1)
		{
			free(pipes);
			close_pipes(pipes, main->pipecount);
			ft_putstr_fd(ERROR, 2);
			ft_putstr_fd(": ", 2);
			perror("fork");
			return (1);
		}
		if (!main->cline[i].pid)
			enter_child(fd_r, fd_w, main->cline[i], main->envp, pipes, main->pipecount, main);
	}
	close_pipes(pipes, main->pipecount);
	free(pipes);
	waitpid(main->cline[i - 1].pid, &status, 0);
	return (wexitstatus(status));
}
