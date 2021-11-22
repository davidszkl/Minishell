/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:04:18 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/22 12:48:45 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include "../inc/minishell.h"

int		is_abs_path(const char *str);
char	*find_command(const char *command, char *envp[]);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	*exec_perror(const char *str);

char	*p_comm_no_found(const char *s)
{
	ft_putstr_fd(ERROR, 2);
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
		ft_putstr_fd(ERROR, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (0);
	}
	return (1);
}

int	is_builtins(const char *s)
{
	return (!ft_strncmp(s, "cd", -1)
		|| !ft_strncmp(s, "export", -1)
		|| !ft_strncmp(s, "unset", -1)
		|| !ft_strncmp(s, "exit", -1)
		|| !ft_strncmp(s, "echo", -1)
		|| !ft_strncmp(s, "pwd", -1)
		|| !ft_strncmp(s, "env", -1));
}

char	*check_builtins(const char *str)
{
	if (!is_builtins(str))
		return (0);
	return (ft_strjoin(BINDIR, str));
}

char	*find_command_wrapper(char *str, char **envp)
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
