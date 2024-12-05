/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 03:00:06 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/30 03:21:30 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
 * error가 나는 경우 (return 값이 1인 경우)
 * 1. 잘못된 옵션이 들어오는 경우
 * 2. 올바른 변수 이름이 아닌경우
 *		1. 이름에 특수문자가 들어간 경우
 *		2. 이름이 숫자로 시작하는 경우
 *		3. 이름에 공백이 들어가는 경우
 * 3. -f 옵션일 때, 유효한 쉘 함수 이름이 아닌 경우
 *
 *
 *
 * */

void	builtin_export(t_data *data, char *str)
{
	t_list	*new_node;
	t_list	*list;
	int		idx;

	// export 할 때 [env_name]만 입력하면 생성 x -> error 아님
	// 이상한 이름 입력들어오면 에러
	// bash: export: `.': not a valid identifier
	// export에서 env_name=까지만 있어도 생성 o
	//
	new_node = ft_lstnew(str);
	list = data->env;
	idx = search_env(data->env, str);
	if (idx == -1)
		ft_lstadd_back(&data->env, new_node);
	else
	{
		while (idx--)
			list = list->next;
		free(list->str);
		list->str = ft_strdup(str);
	}
}
