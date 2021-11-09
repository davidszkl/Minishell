/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:37:26 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/09 15:07:07 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_freetab(char **tab);
int		ft_export(char ***envp, char ***locals, char **argv);
char	**init_envp(const char **envp);
char	**init_locals(void);

static int	myperror(const char *str)
{
	perror(str);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char **const	locals = init_locals();

	if (!locals)
		return (myperror(argv[0]));
	envp = init_envp(envp);
	if (!envp)
	{
		ft_freetab(locals);
		return (myperror(argv[0]));
	}
	if (!ft_export(&envp, &locals, argv))
	{
		ft_freetab(locals);
		ft_freetab(envp);
		return (1)
	}
	ft_freetab(envp);
	ft_freetab(locals);
	return (0);
}
