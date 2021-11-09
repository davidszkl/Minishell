/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:39:25 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/09 09:11:24 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	get_envp_size(const char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	sort_envp(const char **envp)
{
	size_t		i;
	size_t		j;
	const char	*tmp;

	j = -1;
	while (envp[++j])
	{
		i = -1;
		while (envp[++i] && envp[i + 1])
		{
			if (ft_strncmp(envp[i], envp[i + 1], -1) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = tmp;
			}
		}
	}
	return (1);
}

static int	check_r(char **r, size_t l)
{
	int		b;
	size_t	i;

	i = -1;
	b = 1;
	while (++i < l)
		b *= r[i] != 0;
	if (b)
		return (1);
	i = -1;
	while (++i < l)
		free(r[i]);
	free(r);
	return (0);
}

char	**init_locals(void)
{
	char	**r;

	r = malloc(sizeof(char *));
	if (!r)
		return (0);
	r[0] = 0;
	return (r);
}

char	**init_envp(const char **envp)
{
	const size_t	l = get_envp_size(envp);
	size_t			i;
	char			**r;

	r = malloc((l + 1) * sizeof(char *));
	if (!r)
		return (0);
	i = -1;
	while (++i < l)
		r[i] = ft_strdup(envp[i]);
	r[i] = 0;
	if (!check_r(r, l))
		return (0);
	return (r);
}
