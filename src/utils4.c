/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:13:23 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/09 15:13:25 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

// 1 -> "<<"
// 2 -> ">>"
// 3 -> "<"
// 4 -> ">"

int	ft_is_chev(char *str, int n)
{
	if (n == 0 && str[n] == '<' && str[n + 1] == '<')
		return (1);
	else if (n == 0 && str[n] == '>' && str[n + 1] == '>')
		return (2);
	else if (n == 0 && str[n] == '<' && str[n + 1] != '<')
		return (3);
	else if (n == 0 && str[n] == '>' && str[n + 1] != '>')
		return (4);
	if (n > 0 && str[n - 1] != '<' && str[n] == '<' && str[n + 1] == '<')
		return (1);
	else if (n > 0 && str[n - 1] != '>' && str[n] == '>' && str[n + 1] == '>')
		return (2);
	else if (n > 0 && str[n - 1] != '<' && str[n] == '<' && str[n + 1] != '<')
		return (3);
	else if (n > 0 && str[n - 1] != '>' && str[n] == '>' && str[n + 1] != '>')
		return (4);
	return (0);
}

void	ft_putendl_fd(char	*str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	ft_check_chevpipe(char	*str)
{
	int	n;

	n = 0;
	while (str[n])
		if (ft_is_chev(str, n++))
			return (1);
	n--;
	while (ft_isspace(str[n]) == 1)
		n--;
	if (str[n] == '|')
		return (1);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d2;
	const unsigned char	*s2;

	s2 = src;
	d2 = dst;
	if (!dst && !src)
		return (dst);
	while (n--)
		*d2++ = *s2++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;

	if (!s1 || !s2)
		return (0);
	r = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r)
		return (0);
	ft_memcpy(r, s1, ft_strlen(s1));
	ft_memcpy(r + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (r);
}
