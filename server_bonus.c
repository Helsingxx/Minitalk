/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:31:47 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/25 18:07:06 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	handler2(pid_t pid, int *count, unsigned int *res, int coc)
{
	int	x;

	x = 0;
	while (x < coc)
	{
		write(1, &(((unsigned char *)res)[x]), 1);
		x++;
	}
	if (*res == 0)
	{
		kill(pid, SIGUSR2);
		return ;
	}
	*res = 0;
	*count = 0;
	kill(pid, SIGUSR1);
}

static int	handler1(unsigned char a)
{
	if (a >> 5 == 6)
		return (2);
	else if (a >> 4 == 14)
		return (3);
	else if (a >> 3 == 0x1E)
		return (4);
	return (1);
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int			count;
	static unsigned int	res;
	static pid_t		pid;
	static int			coc;

	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid && info->si_pid != 0)
	{
		coc = 0;
		pid = info->si_pid;
		res ^= res;
		count = 0;
		write(1, RESET, sizeof(RESET));
	}
	(void) ucontext;
	if (sig == SIGUSR2)
		res |= (0x01 << count);
	count += 1;
	if (count == 8)
		coc = handler1((&res)[0]);
	if (count && !(count % 8) && count / 8 == coc)
		handler2(pid, &count, &res, coc);
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
		return (-1);
	if (-1 == sigaction(SIGUSR2, &info2, NULL))
		return (-1);
	while (1)
		;
	return (0);
}
