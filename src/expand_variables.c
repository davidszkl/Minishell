/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:58:35 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/06 20:58:59 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*get_envp_val(const char *name, char **envp)
{
	int	l;

	if (!envp || !name)
		return (0);
	l = ft_strlen(name);
	while (*envp)
	{
		if (!ft_strncmp(name, *envp, l) && (*envp)[l] == '=')
			return (ft_substr(*envp, l + 1, ft_strlen(*envp + l + 1));
		*envp++;
	}
	return (0);
}

char	*expand_variables(const char *s, char **envp, char **locals)
{
	if (!s)
		return (0);
	
}
