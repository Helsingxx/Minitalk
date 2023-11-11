/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:47 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/11 17:51:57 by eamrati          ###   ########.fr       */
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
			usleep(50);
			kill(pid, SIGUSR2);
			return ;
		}
		*res = 0;
		*count = 0;
	}
	usleep(50);
	kill(pid, SIGUSR1);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		count;
	static char		res;
	static pid_t	pid;

	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		res = 0;
		count = 0;
	}
	(void) info;
	(void) ucontext;
	if (sig == SIGUSR2)
		res |= (0x01 << count);
	count += 1;
	handler2(pid, &count, &res);
}

int	main(void)
{
	struct sigaction	info;

	ft_memset(&info, 0, sizeof(struct sigaction));
	info.__sigaction_u.__sa_sigaction = handler;
	info.sa_flags = SA_SIGINFO;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &info, NULL);
	sigaction(SIGUSR2, &info, NULL);
	while (1)
		pause();
	return (0);
}