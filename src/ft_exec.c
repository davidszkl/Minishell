/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:30:55 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/17 13:06:50 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <dirent.h>
#include <sys/wait.h>
#include "../inc/minishell.h"

void	init_r_w(int *r, int *w, int i, int pipecount, int *pipes);
int		wexitstatus(int status);
char	*find_command(const char *command, char *envp[]);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(const char *s, int fd);
int		ft_export(char ***envp, char ***locals, char **argv);
int		ft_unset(char ***envp, char ***locals, char **argv);
int		ft_cd(char ***envp, char **argv);

static void	close_pipes(int *pipes, size_t n)
{
	while (n--)
		close(*pipes++);
}

void	*exec_perror(const char *str)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd(": ", 2);
	perror(str);
	return (0);
}

static int	is_abs_path(const char *str)
{
	return (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3));
}

static char	*p_comm_no_found(const char *s)
{
	ft_putstr_fd(PROMPT, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (0);
}

int	handle_dir(const char *str)
{
	DIR	*p;

	if (str[ft_strlen(str) - 1] == '/')
	{
		p = opendir(str);
		if (!p)
			exec_perror(str);
		closedir(p);
		ft_putstr_fd(PROMPT, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (0);
	}
	return (1);
}

static int	is_builtins(const char *s)
{
	return (!ft_strncmp(s, "cd", -1)
			|| !ft_strncmp(s, "export", -1)
			|| !ft_strncmp(s, "unset", -1)
			|| !ft_strncmp(s, "exit", -1)
			|| !ft_strncmp(s, "echo", -1)
			|| !ft_strncmp(s, "pwd", -1)
			|| !ft_strncmp(s, "env", -1));
}


static char	*check_builtins(const char *str)
{
	if (!is_builtins(str))
		return (0);
	return (ft_strjoin(BINDIR, str));
}

static char	*find_command_wrapper(char *str, char **envp)
{
	char	*comm;

	comm = check_builtins(str);
	if (!handle_dir(str))
		exit(1);
	if (is_abs_path(str))
	{
		if (access(str, X_OK) == -1)
			return (exec_perror(str));
		else
			return (ft_strdup(str));
	}
	comm = find_command(str, envp);
	if (!comm)
		return (p_comm_no_found(str));
	if (access(comm, X_OK) == -1)
		return (exec_perror(comm));
	return (comm);
}

static int	open_files(t_file *files, int n)
{
	int	b;
	int	i;

	b = 1;
	i = -1;
	while (++i < n)
	{
		files[n].fd = open(files[n].name, files[n].flags, 0644);
		if (files[n].fd == -1)
			b = (int)exec_perror(files[n].name);
	}
	return (b);
}

static void	close_files(t_file *files, int n)
{
	int i;

	i = -1;
	while (++i < n)
		if (files[i].fd != -1)
			close(files[i].fd);
}

static void	enter_child(int fd_r, int fd_w, t_comm comm, char **envp, int *pipes, size_t n)
{
	char	*path;
	//free tout et close tout si error avant execve
	if (comm.rin)
	{
		open_files(comm.file_in, comm.rin);
		close_files(comm.file_in, comm.rin - 1);
		fd_r = comm.file_in[comm.rin - 1].fd;
	}
	if (comm.rout)
	{
		open_files(comm.file_out, comm.rout);
		close_files(comm.file_out, comm.rout - 1);
		fd_w = comm.file_out[comm.rout - 1].fd;
	}
	dup2(fd_r, 0);
	dup2(fd_w, 1);
	if (comm.rin)
		close(fd_r);
	if (comm.rout)
		close(fd_w);
	close_pipes(pipes, n);
	path = find_command_wrapper(comm.argv[0], envp);
	if (!path)
		exit(1);
	execve(path, comm.argv, envp);
	free(path);
	exit((int)exec_perror(path) + 1);
}

static void	open_pipes(int *pipes, size_t n)
{
	size_t	i;

	i = 0;
	while (i / 2 < n)
	{
		pipe(pipes + i);
		i += 2;
	}
}

static int	is_c_e_u(const char *s)
{
	return (!ft_strncmp(s, "cd", -1)
			|| !ft_strncmp(s, "export", -1)
			|| !ft_strncmp(s, "unset", -1));
}

static int	exec_c_e_u(t_comm comm, char ***envp, char ***locals)
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
	pipes = malloc(sizeof(int) * n * 2);
	open_pipes(pipes, n);
	i = -1;
	while (++i < n)
	{
		init_r_w(&fd_r, &fd_w, i, main->pipecount, pipes);
		main->cline[i].pid = fork();
		if (!main->cline[i].pid)
			enter_child(fd_r, fd_w, main->cline[i], main->envp, pipes, n);
	}
	close_pipes(pipes, n);
	free(pipes);
	waitpid(main->cline[i - 1].pid, &status, 0);
	return (wexitstatus(status));
}
