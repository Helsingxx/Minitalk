/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oxhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:47:06 by eamrati           #+#    #+#             */
/*   Updated: 2022/11/28 21:05:23 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	recursive(size_t n, int fd, const char *hexset)
{
	char	character;
	int		a;

	a = 0;
	if (n > 0)
	{
		a += recursive(n / 16, fd, hexset);
		character = hexset[n % 16];
		if (write(fd, &character, 1) == -1)
			return (-1);
		a++;
		return (a);
	}
	return (a);
}

int	ft_oxhex(size_t n, int fd)
{
	if (write (fd, "0x", 2) == -1)
		return (-1);
	if (n == 0)
	{
		if (write (fd, "0", 1) == -1)
			return (-1);
		return (3);
	}
	else
		return (2 + recursive(n, fd, "0123456789abcdef"));
}

int	ft_hexlowcase(unsigned int n, int fd)
{
	if (n == 0)
	{
		if (write (fd, "0", 1) == -1)
			return (-1);
		return (1);
	}
	else
		return (recursive(n, fd, "0123456789abcdef"));
}

int	ft_hexupcase(unsigned int n, int fd)
{
	if (n == 0)
	{
		if (write (fd, "0", 1) == -1)
			return (-1);
		return (1);
	}
	else
		return (recursive(n, fd, "0123456789ABCDEF"));
}
