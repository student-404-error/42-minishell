#include <stdio.h>
#include <stdlib.h>
#include <string.h>
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	printf("%s\n", dst);
	return (len);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*get_env_key(char *str)
{
	int	len;
	char	*env_name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	env_name = malloc(sizeof(char) * len + 1);
	if (env_name == NULL)
		return (NULL);
	ft_strlcpy(env_name, str, len + 1);
	return (env_name);
}

int	get_dollar_idx(char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	count_total_length(char *token)
{
	int	length;
	int	idx;
	char	*key;

	idx = -1;
	length = 0;
	while (get_dollar_idx(token + idx + 1) != -1)
	{
		printf("%d\n", get_dollar_idx(token + idx + 1)); 
		idx += get_dollar_idx(token + idx + 1);
		printf("idx: %d\n", idx);
		length += idx;
		printf("length: %d\n", length);
		key = get_env_key(token + idx + 1);
		idx += strlen(key);
		printf("idx + strlen(key): %d = %d + %s\n", idx, idx - strlen(key), key);
		length +=/* get_env_value_len(env, key)*/8 - strlen(key);
		printf("length: %d\n", length);
		free(key);
	}
	return (length);
}
int	main(void)
{
	char	*str;

	str = malloc(30 * sizeof(char));
	str = "hello $USER HELLO $USER $USER";
	printf("%d\n", count_total_length(str));
	return (0);
}
