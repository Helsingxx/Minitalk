/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:48:52 by eamrati           #+#    #+#             */
/*   Updated: 2022/11/23 17:09:20 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_putnbr_fd(int n, int fd);
int		ft_oxhex(size_t n, int fd);
int		ft_udec(unsigned int n, int fd);
int		ft_hexupcase(unsigned int n, int fd);
int		ft_hexlowcase(unsigned int n, int fd);
int		ft_printf(const char *string, ...);

#endif