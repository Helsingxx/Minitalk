/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:04 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/25 18:28:44 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_rec;

static void	ack(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	target;

	if (!target)
		target = info->si_pid;
	if (target != info->si_pid)
		return ;
	(void) sig;
	(void) ucontext;
	g_rec = 1;
}

static void	send_null(pid_t pid)
{
	int	inner;

	inner = 0;
	while (inner < 8 && g_rec)
	{
		g_rec = 0;
		inner++;
		kill(pid, SIGUSR1);
		while (!g_rec && inner < 8)
			;
	}
}

static void	send(pid_t pid, char *buffer)
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
			detour (&c, &inner, &a, pid);
			detour_time(&time);
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
	struct sigaction	info2;
	int					i;

	i = 0;
	info.__sigaction_u.__sa_sigaction = ack;
	info.sa_flags = SA_SIGINFO;
	ft_memset(&info, 0, sizeof(struct sigaction));
	ft_memset(&info2, 0, sizeof(struct sigaction));
	info.__sigaction_u.__sa_sigaction = ack;
	info.sa_flags = SA_SIGINFO;
	info2.__sigaction_u.__sa_sigaction = ack;
	info2.sa_flags = SA_SIGINFO;
	if (argc != 3)
		return (ft_printf("You need to enter 2 arguments only\n"), 1);
	if (!isnumber(argv[1]))
		return (ft_printf("pid is not a number"), 1);
	if (ft_atoi(argv[1]) < 1 && ft_atoi(argv[1]) != getpid())
		return (ft_printf("Don't ruin the session!\n"), 1);
	if (-1 == sigaction(SIGUSR1, &info, NULL))
		return (-1);
	if (-1 == sigaction(SIGUSR2, &info2, NULL))
		return (-1);
	send(ft_atoi(argv[1]), argv[2]);
	return (0);
}
