/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:54:17 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/03 15:34:08 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_printf_strlen(const char *str);
int	ft_printf_putchar_fd(char c, int fd);
int	ft_printf_putstr_fd(char *s, int fd);
int	ft_printf_putnbr_fd(long long int n, int fd, int cpt);
int	ft_printf_putnbr_uns_fd(unsigned int n, int fd, int cpt);
int	ft_printf_putnbr_adr_base(unsigned long n, char *base, unsigned int len, int cpt);
int	ft_printf_putnbr_base(int nbr, char *base, unsigned int len, int cpt);
int	ft_printf_address(unsigned long ptr, int cpt);
int	ft_printf_check(long n, int cpt);

#endif