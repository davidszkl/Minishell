/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:44 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/18 13:28:48 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static int	ft_free(t_main *main)
{
	free(main->chev.nbrs);
	free(main->chev.path);
	return (1);
}

static void	ft_get(t_main *main, int n)
{
	char	*nbr;
	char	*term;

	nbr = ft_itoas(main->chev.nbr);
	if (!nbr)
		return ;
	term = ft_getword(main->line, n);
	if (!term)
		return (free(nbr));
	main->chev.nbrs = ft_strjoin("/tmp/", nbr);
	if (!main->chev.nbrs)
	{
		free(nbr);
		return (free(term));
	}
	main->chev.path = ft_strjoin(main->chev.nbrs, term);
	if (!main->chev.path)
	{
		free(nbr);
		return (free(term));
	}
	free(nbr);
	free(term);
}

static int	ft_read_chev2(t_main *main, char *str)
{
	int		fd;

	str = ft_remquotestr(str);
	if (!str[0])
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
token `newline'\n", 2);
		main->error = 1;
		ft_myfree(str);
		return (0);
	}
	fd = open(main->chev.path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (ft_myfree(str));
	printf("string to enter: %s\n", str);
	main->temp = readline("> ");
	while (ft_strncmp(main->temp, str, ft_strlen(main->temp)))
	{
		ft_putendl_fd(main->temp, fd);
		free(main->temp);
		main->temp = readline("> ");
	}
	close(fd);
	free(main->temp);
	free(str);
	return (0);
}

static int	ft_read_chev1(t_main *main, char *temp, int n, int j)
{
	while (main->line[n])
	{
		if (main->line[n] == '|' && !ft_isinquote_now(main->line, n))
			main->chev.nbr++;
		if (ft_is_chev(main->line, n) == 1 && !ft_isinquote_now(main->line, n))
		{
			n += 2;
			ft_get(main, n);
			if (ft_read_chev2(main, ft_getword(main->line, n)))
				return (1);
			j = ft_spwordcount(main->line, n);
			temp = ft_replace_str(main->line, n - 1, j + 1, main->chev.path);
			if (!temp)
				return (1);
			free(main->line);
			main->line = ft_strdup(temp);
			free(temp);
			if (!main->line)
				return (1);
			ft_free(main);
		}
		n++;
	}
	return (0);
}

int	ft_read_chev(t_main *main)
{
	char	*temp;
	int		n;
	int		j;

	temp = NULL;
	n = 0;
	j = 0;
	main->chev.nbr = 0;
	if (ft_read_chev1(main, temp, n, j))
		return (ft_free(main));
	return (0);
}
