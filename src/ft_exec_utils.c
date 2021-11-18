/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefevre <mlefevre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:11:15 by mlefevre          #+#    #+#             */
/*   Updated: 2021/11/18 11:41:54 by mlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>//
void	init_r_w(int *r, int *w, int i, int pipecount, int *pipes)
{
#ifdef DEBUG
	printf("in init_r_w\n");
#endif
	if ((i - 1) * 2 < 0)
		*r = 0;
	else
		*r = pipes[(i - 1) * 2];
	if ((i - 1) * 2 + 3 > pipecount * 2 - 1)
		*w = 1;
	else
		*w = pipes[(i - 1) * 2 + 3];
#ifdef DEBUG
	printf("r: %i\n", *r);
	printf("w: %i\n", *w);
	printf("out init_r_w\n");
#endif
}

int	wexitstatus(int status)
{
	return (((*(int *)&(status)) >> 8) & 0x000000ff);
}
