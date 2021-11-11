/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:44 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/11 12:46:32 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static void	ft_free(t_main *main)
{
	free(main->chev.nbrs);
	free(main->chev.path);
}

static void	ft_get(t_main *main, int n)
{
	char	*nbr;
	char	*term;

	nbr = ft_itoas(main->chev.nbr);
	if (!nbr)
		return ;
	term = ft_getword(&main->line[n]);
	if (!nbr)
		return (free(nbr));
	main->chev.nbrs = ft_strjoin("/tmp/", nbr);
	if (!main->chev.nbrs)
	{
		free(nbr);
		free(term);
		return (ft_free(main));
	}
	main->chev.path = ft_strjoin(main->chev.nbrs, term);
	if (!main->chev.path)
		return (ft_free(main));
	free(nbr);
	free(term);
}

static void	ft_read_chev2(t_main *main, char *str)
{
	int	fd;

	fd = open(main->chev.path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0 && main->error++)
		return ;
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
}

static int	ft_read_chev1(t_main *main, int n, int j)
{
	char	*temp;

	while (main->line[n])
	{
		if (main->line[n] == '|')
			main->chev.nbr++;
		if (ft_is_chev(main->line, n) == 1)
		{
			n += 2;
			ft_get(main, n);
			ft_read_chev2(main, ft_getword(&main->line[n]));
			j = ft_spwordcount(&main->line[n]);
			temp = ft_replace_str(main->line, n - 1, j + 1, main->chev.path);
			if (!temp)
				return (1);
			free(main->line);
			main->line = ft_strdup(temp);
			free(temp);
			ft_free(main);
		}
		n++;
	}
	return (0);
}

int	ft_read_chev(t_main *main)
{
	int	j;
	int	n;

	n = 0;
	j = 0;
	if (ft_read_chev1(main, n, j) == 1)
		return (1);
	return (0);
}
