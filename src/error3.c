/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:48:24 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/21 12:48:27 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	ft_freeshell_continue(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
		ft_freetab(main->cline[n++].argv);
	free(main->line);
	free(main->cline);
	return (1);
}

int	ft_single_pipe(t_main *main)
{
	int	n;

	n = -1;
	while (main->line[++n])
	{
		while (ft_isspace(main->line[n]))
			n++;
		if (main->line[n] && main->line[n] == '|')
		{
			n++;
			while (ft_isspace(main->line[n]))
				n++;
			if (!main->line[n])
				return (1);
		}
	}
	return (0);
}
