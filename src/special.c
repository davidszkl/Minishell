/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:45:11 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/19 10:45:12 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

/* int	ft_special(t_main *main)
{
	if (!ft_strncmp(main->cline[0].argv[0], "cat",
		ft_strlen(main->cline[0].argv[0])))
	{
		tcsetattr(0, TCSANOW, &main->old);
		ft_exec(main);
		ft_freeshell3(main);
		tcsetattr(0, TCSANOW, &main->new);
		return (1);
	}
	return (0);
}
 */