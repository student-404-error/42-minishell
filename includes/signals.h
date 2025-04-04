/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:40:52 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/10 17:24:27 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sg_input_handler(int status);
void	ft_init_signal(void);
void	sg_heredoc_handler(int status);
void	sg_exec_handler(int status);
int		sg_readline_event(void);

#endif