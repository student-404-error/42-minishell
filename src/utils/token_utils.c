/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:16:29 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 18:17:32 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*ft_new_token(char *value, t_tokenizer *state)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = check_token_type(value, state);
	state->is_first_token = 0;
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_tklast(t_token *tklst)
{
	t_token	*list_ptr;

	if (!tklst)
		return (NULL);
	list_ptr = tklst;
	while (list_ptr->next)
		list_ptr = list_ptr->next;
	return (list_ptr);
}

void	ft_token_add_back(t_token **tklst, t_token *new)
{
	t_token	*last_token;

	last_token = ft_tklast(*tklst);
	if (!new)
		return ;
	if (last_token)
	{
		new->prev = last_token;
		last_token->next = new;
	}
	else
	{
		new->prev = NULL;
		*tklst = new;
	}
	new->next = NULL;
}
