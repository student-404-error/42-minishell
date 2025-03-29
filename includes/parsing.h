/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:33:08 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/24 16:30:46 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_token	t_token;
typedef struct s_data	t_data;

typedef struct s_tokenizer
{
	int		idx;
	int		start;
	int		is_first_token;
	int		after_operator;
	t_token	*tklst;
}	t_tokenizer;

void	ft_print_tokens(t_token *tklst);
t_token	*ft_new_token(char *value, t_tokenizer *state);
t_token	*ft_tklast(t_token *tklst);
void	ft_token_add_back(t_token **tklst, t_token *new);

int		ft_init_here_doc(int fd, char *eof);
void	ft_unlink_err(t_token *token);
int		ft_handle_heredoc(t_token *token);
char	*ft_gen_random_name(char *str);

#endif // !PARSING.15:33:20
