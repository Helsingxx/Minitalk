/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:04 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/24 18:48:34 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"


int	g_rec;

void	ack(int sig, siginfo_t *info, void *ucontext)
{
	static int target;
	
	if (!target)
		target = info->si_pid;
	if (target != info->si_pid)
		return ;
	(void) sig;
	(void) ucontext;
	g_rec = 1;
	if (sig == SIGUSR2)
	{
		ft_printf("Message received!\n");
		exit(0);
	}
}

void send_null(int pid)
{
	int inner;

	inner = 0;
	while (inner < 8 && g_rec)
	{
		g_rec = 0;
		inner++;
		kill(pid, SIGUSR1);
		while (!g_rec)
		;
	}
}

void	send(int pid, char *buffer)
{
	int			a;
	int			inner;
	char		c;
	uint64_t	time;

	a = 0;
	g_rec = 1;
	while (buffer && buffer[a])
	{
		c = buffer[a];
		inner = 0;
		time = 0;
		while (inner < 8)
		{
			*(&g_rec) = 0;
			if (c & 0x01)
			{
				c >>= 1;
				inner++;
				if (!(inner < 8))
					a++;
				kill(pid, SIGUSR2);
			}
			else
			{
				c >>= 1;
				inner++;
				if (!(inner < 8))
					a++;
				kill(pid, SIGUSR1);
			}
			while (!g_rec)
			{
				if (!(time++ < TIME))
				{
					ft_printf("Server is unavailable!\n");
					exit(0);
				}
			}
		}
	}
	if (!buffer[a])
		send_null(pid);
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
	int					i;

	i = 0;
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
