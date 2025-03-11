#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > strlen(s))
		return (malloc(1));
	if (len > strlen(s + start))
		len = strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

