/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:04 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/11 17:52:16 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

int	g_rec;

void	ack(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) info;
	(void) ucontext;
	g_rec = 1;
	if (sig == SIGUSR2)
	{
		ft_printf("Message received!");
		exit(0);
	}
}

void	send(int pid, char *buffer)
{
	int		a;
	int		inner;
	char	c;

	a = 0;
	while (buffer)
	{
		c = buffer[a];
		inner = 0;
		while (inner < 8)
		{
			usleep(50);
			g_rec = 0;
			if (c & 0x01)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!g_rec)
				pause();
			c >>= 1;
			inner++;
		}
		a++;
	}
}

static t_bool	isnumber(char *arg1)
{
	while (arg1 && *arg1 && (*arg1 == ' ' || *arg1 == '\n'
			|| *arg1 == '\t' || *arg1 == '\v'
			|| *arg1 == '\f' || *arg1 == '\r'))
		arg1++;
	if (*arg1 == '-' || *arg1 == '+')
		arg1++;
	if (*arg1 == 0 || !(*arg1 >= '0' && *arg1 <= '9'))
		return (FALSE);
	while (*arg1 >= '0' && *arg1 <= '9')
		arg1++;
	while (arg1 && *arg1 && (*arg1 == ' ' || *arg1 == '\n'
			|| *arg1 == '\t' || *arg1 == '\v'
			|| *arg1 == '\f' || *arg1 == '\r'))
		arg1++;
	if (*arg1)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	struct sigaction	info;

	ft_memset(&info, 0, sizeof(struct sigaction));
	info.__sigaction_u.__sa_sigaction = ack;
	info.sa_flags = SA_SIGINFO;
	if (argc != 3)
	{
		ft_printf("You need to enter 2 arguments only\n");
		return (1);
	}
	if (!isnumber(argv[1]))
	{
		ft_printf("pid is not a number");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_printf("Don't ruin the session!\n");
		return (1);
	}
	sigaction(SIGUSR1, &info, NULL);
	sigaction(SIGUSR2, &info, NULL);
	send(ft_atoi(argv[1]), argv[2]);
	return (0);
}
