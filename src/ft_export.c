/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:05:55 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/11 11:50:42 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*ft_substr(const char *str, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	get_envp_size(char **envp);
char	*ft_strdup(const char *s1);
void	ft_freetab(char **tab);
char	*ft_replace_str(const char *s, size_t start, size_t n, const char *sub);
char	*ft_strjoin(const char *s1, const char *s2);

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

static char	*get_value(const char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str != '=')
		return (0);
	str += (*str == '=');
	return (ft_substr(str, 0, ft_strlen(str)));
}

static int	is_in_envp(const char *name, char **envp)
{
	const size_t	l = ft_strlen(name);

	envp--;
	while (*++envp)
		if (!ft_strncmp(name, *envp, l) && (*envp)[l] == '=')
			return (1);
	return (0);
}

static int	check_and_free(char **tab, size_t l)
{
	int		b;
	size_t	i;

	b = 1;
	i = -1;
	while (++i < l)
		b *= tab[i] != 0;
	if (b)
		return (1);
	i = -1;
	while (++i < l)
		free(tab[i]);
	free(tab);
	return (0);
}

static int	copy_to_envp(const char *name, char **locals, char ***envp_p)
{
	size_t			i;
	char			**envp;
	const size_t	l = ft_strlen(name);

	locals--;
	while (*++locals)
		if (!ft_strncmp(name, *locals, l) && (*locals)[l] == '=')
			break ;
	if (!*locals)
		return (0);
	envp = malloc(sizeof(char *) * (get_envp_size(*envp_p) + 2));
	if (!envp)
		return (0);
	i = -1;
	while ((*envp_p)[++i])
		envp[i] = ft_strdup((*envp_p)[i]);
	envp[i + 1] = ft_strdup(*locals);
	envp[i + 2] = 0;
	if (!check_and_free(envp, get_envp_size(*envp_p) + 1))
		return (0);
	ft_freetab(*envp_p);
	*envp_p = envp;
	return (1);
}

static int	del_in_envp(const char *name, char ***envp)
{
	char			**tmp;
	size_t			i;
	const size_t	l = get_envp_size(*envp);
	const size_t	l2 = ft_strlen(name);

	tmp = malloc(sizeof(char *) * l);
	if (!tmp)
		return (0);
	i = 0;
	while (i < l - 1)
		if (!(!ft_strncmp(name, (*envp)[i], l2) && (*envp)[i][l2] == '='))
		{
			tmp[i] = ft_strdup((*envp)[i]);
			i++;
		}
	tmp[i] = 0;
	if (!check_and_free(tmp, l - 1))
		return (0);
	ft_freetab(*envp);
	*envp = tmp;
	return (1);
}

static int	envp_append(char *name, char *value, char ***envp)
{
	char			**tmp;
	char			*str;
	char			*str2;
	size_t			i;
	const size_t	l = get_envp_size(*envp);

	str = ft_strjoin(name, "=");
	if (!str)
		return (0);
	str2 = ft_strjoin(str, value);
	free(str);
	if (!str2)
		return (0);
	tmp = malloc(sizeof(char *) * (l + 2));
	if (!tmp)
		return (0);
	i = -1;
	while (++i < l)
		tmp[i] = ft_strdup((*envp)[i]);
	tmp[i] = str2;
	tmp[i + 1] = 0;
	if (!check_and_free(tmp, l + 1))
		return (0);
	ft_freetab(*envp);
	*envp = tmp;
	return (1);
}

static int	envp_assign(char *name, char *value, char ***envp_p)
{
	char			**envp;
	char			*tmp;
	const size_t	l = ft_strlen(name);
	const int		b = is_in_envp(name, *envp_p);

	if (!b)
		return (envp_append(name, value, envp_p));
	envp = *envp_p;
	envp--;
	while (*++envp)
		if (!ft_strncmp(name, *envp, l) && (*envp)[l] == '=')
			break ;
	tmp = ft_replace_str(*envp, l + 1, ft_strlen(*envp) - l - 1, value);
	if (!tmp)
		return (0);
	free(*envp);
	*envp = tmp;
	return (1);
}

int	ft_export(char ***envp, char ***locals, char **argv)
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
		if (!value && !is_in_envp(name, *locals))
		{
			free(name);
			return (1);
		}
		if (is_in_envp(name, *locals) && (!copy_to_envp(name, *locals, envp)
				|| !del_in_envp(name, locals)))
		{
			free(name);
			free(value);
			return (0);
		}
		if (value && !envp_assign(name, value, envp))
		{
			free(name);
			free(value);
			return (0);
		}
		free(name);
		free(value);
	}
	return (1);
}
