/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:04:06 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/18 13:21:09 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

void	ft_freetab(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	free(tab[n]);
	free(tab);
}

int	ft_freeshell(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
		ft_freetab(main->cline[n++].argv);
	free(main->line);
	free(main->cline);
	ft_freetab(main->envp);
	ft_freetab(main->locals);
	return (0);
}

int	ft_freeshell2(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
	{
		free(main->cline[n].file_in);
		free(main->cline[n].file_out);
		ft_freetab(main->cline[n++].argv);
	}
	free(main->line);
	free(main->cline);
	ft_freetab(main->envp);
	ft_freetab(main->locals);
	return (1);
}

int	ft_freeshell3(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
	{
		free(main->cline[n].file_in);
		free(main->cline[n].file_out);
		ft_freetab(main->cline[n++].argv);
	}
	free(main->line);
	free(main->cline);
	return (0);
}

int	ft_freeshell4(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
	{
		free(main->cline[n].file_in);
		free(main->cline[n].file_out);
		ft_freetab(main->cline[n++].argv);
	}
	free(main->line);
	free(main->cline);
	ft_freetab(main->envp);
	ft_freetab(main->locals);
	return (0);
}

int	ft_tabcheck(t_main *main)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (main->cline[n].argv[j])
	{
		if (ft_is_chev(main->cline[n].argv[j], 0) && (!main->cline[n].argv[j + 1] || ft_is_chev(main->cline[n].argv[j + 1], 0)))
		{
			write(1, "ok\n", 3);
			return (1);
		}
		j++;
	}
	return (0);
}
