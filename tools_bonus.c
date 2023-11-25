/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:13:45 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/25 20:38:27 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	detour(char *c, int *inner, int *a, pid_t pid)
{
	if (*c & 0x01)
	{
		*c >>= 1;
		(*inner)++;
		if (!(*inner < 8))
			(*a)++;
		kill(pid, SIGUSR2);
	}
	else
	{
		*c >>= 1;
		(*inner)++;
		if (!(*inner < 8))
			(*a)++;
		kill(pid, SIGUSR1);
	}
}

void	detour_time(uint64_t *time)
{
	while (!g_rec)
	{
		if (!((*time)++ < TIME))
		{
			ft_printf("Server is unavailable!\n");
			exit(0);
		}
	}
}
