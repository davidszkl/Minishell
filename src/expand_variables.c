/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:58:35 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/06 21:36:28 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"
/*
Returns value of environment
variable name in envp NULL in
case of error.
*/
char	*get_envp_val(const char *name, char **envp)
{
	int	l;

	if (!envp || !name)
		return (0);
	l = ft_strlen(name);
	while (*envp)
	{
		if (!ft_strncmp(name, *envp, l) && (*envp)[l] == '=')
			return (ft_substr(*envp, l + 1, ft_strlen(*envp + l + 1)));
		envp++;
	}
	return (0);
}

/*
Note to self:
$VAR shall expand to value of VAR.
$VAR shall be removed if VAR not found.
$ followed by a space shall NOT be removed.
*/
/*
Returns new string with all variables
in s expanded. NULL in case of error.
(envp for exported variables, locals for the rest)
*/
char	*expand_variables(const char *s, char **envp, char **locals)
{
	(void)envp;
	(void)locals;
	if (!s)
		return (0);
	return (0);
}
