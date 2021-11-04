/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:10:15 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/04 12:10:28 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	static char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline(PROMPT);
		ft_parser(line);
	}
	return (1);
}
