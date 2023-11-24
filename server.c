/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:47 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/24 17:17:03 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>

void	handler2(pid_t pid, int *count, char *res)
{
	if (*count == 8)
	{
		write(1, res, 1);
		if (*res == 0)
		{
			kill(pid, SIGUSR2);
			return ;
		}
		*res = 0;
		*count = 0;
	}
	kill(pid, SIGUSR1);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		count;
	static char		res;
	static pid_t	pid;

	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid && info->si_pid != 0)
	{
		pid = info->si_pid;
		res = 0;
		count = 0;
	}
	(void) ucontext;
	if (sig == SIGUSR2)
		res |= (0x01 << count);
	count += 1;
	if (count == 8)
		handler2(pid, &count, &res);
	else
		kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	info;
	struct sigaction	info2;

	ft_memset(&info, 0, sizeof(struct sigaction));
	ft_memset(&info2, 0, sizeof(struct sigaction));
	info.__sigaction_u.__sa_sigaction = handler;
	info.sa_flags = SA_SIGINFO;
	info2.__sigaction_u.__sa_sigaction = handler;
	info2.sa_flags = SA_SIGINFO;
	ft_printf("PID: %d\n", getpid());
	if (-1 == sigaction(SIGUSR1, &info, NULL))
		exit(0);
	if (-1 == sigaction(SIGUSR2, &info2, NULL))
		exit(0);
	while (1)
		;
	return (0);
}
