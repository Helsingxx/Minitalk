/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:24 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/25 18:31:56 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "ft_printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>
# include <stdint.h>
# define TIME 1000000000
# define RESET "\033[m"

extern int	g_rec;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	detour(char *c, int *inner, int *a, pid_t pid);
void	detour_time(uint64_t *time);

#endif