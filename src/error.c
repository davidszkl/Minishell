/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:04:06 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/07 12:04:08 by dszklarz         ###   ########.fr       */
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

void	ft_freeshell(t_main *main)
{
	int	n;

	n = 0;
	while(main->cline[n].line)
		ft_freetab(main->cline[n++].argv);
	free(main->line);
	free(main->cline);
	//free(main->chev.nbrs);
	//free(main->chev.term);
}
