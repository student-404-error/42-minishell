/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:23:25 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 23:54:41 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# define ER STDERR_FILENO
# define AD_SIZE 16
# define HEX_SIZE 16
# define DEC_TAB "0123456789"
# define HEX_TAB "0123456789abcdef"
# define HEX_TAB_U "0123456789ABCDEF"

int			ft_print_spec(char c, va_list *ap);
int			ft_print_char(char c);
int			ft_print_str(char *s);
int			ft_print_mem(void *addr);
int			ft_print_digit(long nbr, char *base);
int			ft_printf(const char *fmt, ...);
int			ft_is_spec(char c);

#endif