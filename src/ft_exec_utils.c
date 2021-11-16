/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:11:15 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/16 17:11:35 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_r_w(int *r, int *w, int i, int pipecount, int *pipes)
{
	if ((i - 1) * 2 < 0)
		*r = 0;
	else
		*r = pipes[(i - 1) * 2];
	if ((i - 1) * 2 + 3 > pipecount * 2 - 1)
		*w = 0;
	else
		*w = pipes[(i - 1) * 2 + 3];
}

int	wexitstatus(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}
