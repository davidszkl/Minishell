/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:16:39 by dszklarz          #+#    #+#             */
/*   Updated: 2021/11/15 12:16:40 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

extern t_comm *g_glb;

static int	ft_getrdircount(t_main *main, int n)
{
	int	incount;
	int	outcount;
	int	j;

	incount = 0;
	outcount = 0;
	j = 0;
	while (main->cline[n].argv[j])
	{
		if (ft_strncmp(main->cline[n].argv[j], "<",
				ft_strlen(main->cline[n].argv[j])))
			incount++;
		else if (ft_strncmp(main->cline[n].argv[j], ">",
				ft_strlen(main->cline[n].argv[j])))
			outcount++;
		else if (ft_strncmp(main->cline[n].argv[j], ">>",
				ft_strlen(main->cline[n].argv[j])))
			outcount++;
		j++;
	}
	main->cline[n].rin = incount;
	main->cline[n].rout = outcount;
	return (0);
}

static int	ft_fillstruct2(t_comm *comm, int n, int j)
{
	if (!ft_strncmp(comm->argv[n], "<", ft_strlen(comm->argv[n])))
	{
		comm->file_in[j].flags = O_RDONLY;
		comm->file_in[j].name = comm->argv[n + 1];
		return (1);
	}
	if (!ft_strncmp(comm->argv[n], ">", ft_strlen(comm->argv[n])))
	{
		comm->file_out[j].flags = O_CREAT | O_TRUNC | O_WRONLY;
		comm->file_out[j].name = comm->argv[n + 1];
		return (1);
	}
	if (!ft_strncmp(comm->argv[n], ">>", ft_strlen(comm->argv[n])))
	{
		comm->file_out[j].flags = O_CREAT | O_APPEND | O_WRONLY;
		comm->file_out[j].name = comm->argv[n + 1];
		return (1);
	}
	return (0);
}

static int	ft_fillstruct1(t_comm *comm)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	comm->file_in[j].fd = 0;
	comm->file_out[j].fd = 1;
	while (comm->argv[n])
	{
		j = 0;
		if (ft_fillstruct2(comm, n++, j))
			j++;
	}
	return (0);
}

int	ft_fillstruct(t_main *main)
{
	int	n;

	n = 0;
	while (main->cline[n].line)
	{
		main->cline[n].pid = 0;
		ft_getrdircount(main, n);
		main->cline[n].file_in
			= malloc(sizeof(t_file) * (main->cline[n].rin + 1));
		if (!main->cline[n].file_in)
			return (1);
		main->cline[n].file_out
			= malloc(sizeof(t_file) * (main->cline[n].rout + 1));
		if (!main->cline[n].file_out)
			return (1);
		ft_fillstruct1(&main->cline[n]);
		n++;
	}
	g_glb = main->cline;
	return (0);
}
