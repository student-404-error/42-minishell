#include <stdio.h>
#include <stdlib.h>

char	*ret_char(int n)
{
	char	*str = "hello world nice meet you";

	return (str + n);
}


int main(int argc, char *argv[])
{
	printf("%s\n", ret_char(6));
	return EXIT_SUCCESS;
}
