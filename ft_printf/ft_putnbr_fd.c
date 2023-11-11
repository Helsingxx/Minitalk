/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:48:16 by eamrati           #+#    #+#             */
/*   Updated: 2022/11/28 21:04:47 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	recursive(long n, int fd)
{
	char	character;
	int		a;

	a = 0;
	if (n > 0)
	{
		a += recursive(n / 10, fd);
		character = n % 10 + '0';
		if (write(fd, &character, 1) == -1)
			return (-1);
		a++;
		return (a);
	}
	return (a);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	longnum;
	int		a;

	a = 0;
	longnum = n;
	if (longnum < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		longnum *= -1;
		a++;
	}
	if (longnum == 0)
	{
		if (write (fd, "0", 1) == -1)
			return (-1);
		return (++a);
	}
	return (a + recursive(longnum, fd));
}

int	recursive_unsigned(unsigned int n, int fd)
{
	char	character;
	int		a;

	a = 0;
	if (n > 0)
	{
		a += recursive_unsigned(n / 10, fd);
		character = n % 10 + '0';
		if (write(fd, &character, 1) == -1)
			return (-1);
		a++;
		return (a);
	}
	return (a);
}

int	ft_udec(unsigned int n, int fd)
{
	if (n == 0)
	{
		if (write (fd, "0", 1) == -1)
			return (-1);
		return (1);
	}
	return (recursive_unsigned(n, fd));
}
