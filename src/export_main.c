/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:37:26 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/11 15:47:50 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_freetab(char **tab);
int		ft_export(char ***envp, char ***locals, char **argv);
char	**init_envp(char **envp);
char	**init_locals(void);
void	ft_showtab(char **tab);

 static int	myperror(const char *str)
{
	perror(str);
	return (1);
} 

char *ft_strdup(const char *s);
static char **init_locals_to_erase(void)
{
	char **r = malloc(sizeof(char *) * 5);

	r[0] = ft_strdup("cool=oui");
	r[1] = ft_strdup("empty=");
	r[3] = ft_strdup("name=martin");
	r[2] = ft_strdup("name2=martin");
	r[4] = 0;
	return (r);
}

#include <unistd.h>
 int	main(int argc, char **argv, char **envp)
{
	char	**locals;

	(void)argc;
	locals = init_locals_to_erase();
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
		return (1);
	}
	write(1, "///////////////\n", 16);
	ft_showtab(envp);
	write(1, "///////////////\n", 16);
	ft_showtab(locals);
	write(1, "///////////////\n", 16);
	ft_freetab(envp);
	ft_freetab(locals);
	return (0);
}
