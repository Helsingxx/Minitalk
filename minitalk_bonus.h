/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamrati <eamrati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:33:24 by eamrati           #+#    #+#             */
/*   Updated: 2023/11/24 18:48:07 by eamrati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "ft_printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdint.h>
# define TIME 1000000000


typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);

#endif