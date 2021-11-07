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

/* int	ft_error(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
	}
} */

void	ft_freeshell(t_main *main)
{
	int	n;

	n = 0;
	while (n < main->pipecount + 1)
	{
		ft_freetab(main->cline[n].argv);
		n++;
	}
	free(main->line);
	free(main->cline);
}
