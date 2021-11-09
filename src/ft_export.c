/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:05:55 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/09 17:21:01 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_substr(const char *str, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

static int	my_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

static int	is_valid_export_arg(const char *s)
{
	if (!(ft_isalpha(*s) || *s == '_'))
		return (0);
	while (*++s && *s != '=')
		if (!(*s == '_' || ft_isalpha(*s) || ft_isdigit(*s)))
			return (0);
	return (1);
}

static char *get_name(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

static char	get_value(const char *str)
{
	while (*str && *str != '=')
		str++;
	return (ft_substr(str, 0, ft_strlen(str)));
}

int	ft_export(char ***envp, char ***locals, const char **argv)
{
	char	*name;
	char	*value;

	while (*++argv)
	{
		if (!is_valid_export_arg(*argv))
		{
			my_putstr_fd("minishell: export: `", 2);
			my_putstr_fd(*argv, 2);
			return (0 * my_putstr_fd("': not a valid identifier", 2));
		}
		name = get_name(*argv);
		if (!name)
			return (0);
		value = get_value(*argv);
		if (!value && !is_in_envp(name, locals))
		{
			free(name);
			return (1);
		}
		if (is_in_envp(name, locals))
			move_to_envp(name, locals, envp);
		if (value)
			envp_assign(name, value, envp)
		free(name);
		free(value);
	}
	return (1);
}
