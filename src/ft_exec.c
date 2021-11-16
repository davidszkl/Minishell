/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:30:55 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/15 18:10:51 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static size_t	get_comm_num(t_comm *cline)
{
	size_t	i;

	i = 0;
	while (cline[i].line)
		i++;
	return (i);
}

void	ft_exec(t_main *main)
{
	const size_t	n = get_comm_num(main->cline);

	(void)n;
}
