/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:46:22 by eamrati           #+#    #+#             */
/*   Updated: 2022/11/23 17:07:05 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	determine_print(const char *string, size_t arg)
{
	if (string[1] == 'c')
		return (ft_putchar_fd(arg, 1));
	else if (string[1] == 's')
		return (ft_putstr_fd((char *) arg, 1));
	else if (string[1] == 'p')
		return (ft_oxhex(arg, 1));
	else if (string[1] == 'i' || string[1] == 'd')
		return (ft_putnbr_fd(arg, 1));
	else if (string[1] == 'u')
		return (ft_udec(arg, 1));
	else if (string[1] == 'x')
		return (ft_hexlowcase(arg, 1));
	else if (string[1] == 'X')
		return (ft_hexupcase(arg, 1));
	else
		return (ft_putchar_fd(string[1], 1));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	va_list	list;
	int		counter;
	int		true_counter;

	va_start(list, string);
	true_counter = 0;
	counter = 0;
	while (string[counter] != '\0')
	{
		if (string[counter] == '%' && string[counter + 1] == '%')
		{
			true_counter += ft_putchar_fd('%', 1);
			counter++;
		}
		else if (string[counter] == '%')
			true_counter += determine_print(&string[counter++],
					va_arg(list, long long));
		else
			true_counter += ft_putchar_fd(string[counter], 1);
		counter++;
	}
	va_end(list);
	return (true_counter);
}
