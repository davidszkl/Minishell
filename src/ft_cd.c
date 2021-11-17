/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:51:08 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/17 13:16:23 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>

void	*exec_perror(const char *str);
int		envp_assign(char *name, char *value, char ***envp_p);

int	ft_cd(char ***envp, char **argv)
{
	char	pwd[MAXPATHLEN + 1];
	char	old_pwd[MAXPATHLEN + 1];
	int		r;

	getcwd(old_pwd, MAXPATHLEN + 1);
	if (argv[1])
		r = chdir(argv[1]);
	else
		r = chdir(getenv("HOME"));
	if (r == -1)
		return ((int)exec_perror(argv[1]) + 1);
	getcwd(pwd, MAXPATHLEN + 1);
	if (!envp_assign("OLD_PWD", old_pwd, envp))
		return ((int)exec_perror("envp_assign") + 1);
	if (!envp_assign("PWD", pwd, envp))
		return ((int)exec_perror("envp_assign") + 1);
	return (0);
}
