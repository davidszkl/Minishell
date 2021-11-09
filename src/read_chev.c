/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:44 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/09 11:02:46 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

/* static void	ft_free(t_main *main)
{
	if (!main->chev.nbrs)
		free(main->chev.nbrs);
	if (!main->chev.path)
		free(main->chev.path);
} */

static char	*ft_read_chev1(char *line, t_main *main)
{
	int		n;
	int		j;

	n = 0;
	main->chev.nbr = 0;
	while (line[n])
	{
		if (line[n] == '|')
			main->chev.nbr++;
		if (ft_is_dchev(line, n) == 1)
		{
			n += 2;
			main->chev.nbrs = ft_strjoin("/tmp/", ft_itoas(main->chev.nbr));
			main->chev.path = ft_strjoin(main->chev.nbrs, ft_getword(&line[n]));
			j = ft_spwordcount(&line[n]);
			line = ft_replace_str(line, n - 1, j + 1, main->chev.path);
		}
		n++;
	}
	return (line);
}

/* static char	*ft_read_chev2(char *line, t_main *main)
{
} */

void	ft_read_chev(char *line, t_main *main)
{
	char	*temp;
	
	temp = line;
	main->line = ft_read_chev1(line, main);
	//ft_read_chev2(line, main);
}
