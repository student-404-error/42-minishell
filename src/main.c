/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:17:26 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/10 14:49:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "parsing.h"

int main(int argc, char *argv[], char **env)
{
	t_data	data;
	char	*input;

	init_env(&data, env);
	while (1)
	{
		input = readline("input: ");
		data.tklst = tokenize(&data, input);
		if (ft_strncmp(input, "env", 3) == 0)
			builtin_env(data);
		else if (ft_strncmp(input, "unset", 5) == 0)
		{
			builtin_unset(&data, input + 6);
		}
		free(input);
	}
	(void) argc;
	(void) argv;
	return 0;
}
//
// int main(int argc, char *argv[])
// {
// 	char	*str1 = "11<22>33|44";
// 	char	*str2 = "1 1    <22\'3 45\'<< 44\"5 6 > 7\"|88>33|44";
// 	char	*str3 = "e\'\'\"\"11<22>33|44";
// printf("========================\n");
// 	count_special_character("ls -l");
// printf("========================\n");
//     count_special_character("echo Hello World");
// printf("========================\n");
//     count_special_character("cat file.txt");
// printf("========================\n");
//     count_special_character("pwd");
// printf("========================\n");
//     count_special_character("grep 'pattern' file.txt");
//
// printf("========================\n");
//     // 테스트 케이스 6 ~ 10: 리다이렉션과 파이프
//     count_special_character("cat file.txt > output.txt");
// printf("========================\n");
//     count_special_character("ls -l | grep \"test\" > result.txt");
// printf("========================\n");
//     count_special_character("echo \"some text\" >> log.txt");
// printf("========================\n");
//     count_special_character("cat < input.txt | grep \"pattern\"");
// printf("========================\n");
//     count_special_character("echo \"line1\" > file1 | echo \"line2\" >> file1");
// printf("============1===========\n");
//
//     // 테스트 케이스 11 ~ 15: 따옴표 및 환경변수
//     count_special_character("echo \"Hello $USER\"");
// printf("============2===========\n");
//     count_special_character("echo 'Hello $USER'");
// printf("========================\n");
//     count_special_character("echo \"A 'single quote' inside\"");
// printf("========================\n");
//     count_special_character("echo 'A \"double quote\" inside'");
// printf("========================\n");
//     count_special_character("echo '' > empty.txt");
// printf("========================\n");
//
//     // 테스트 케이스 16 ~ 20: 복합 케이스
//     count_special_character("cat << EOF > file.txt");
// printf("========================\n");
//     count_special_character("echo \"Multiple commands\" | grep \"commands\" | sort > sorted.txt");
// printf("========================\n");
//     count_special_character("ls | grep \"txt\" | wc -l");
// printf("============3===========\n");
//     count_special_character("echo $PATH | tr \":\" \"\\n\"");
// printf("========================\n");
//     count_special_character("echo 'First part' && echo \"Second part\" | cat > final_output.txt");
// printf("========================\n");
// count_special_character("ls-l|grep.txt>output.txt"); // (수정 전) bash에서 실행 불가한 형태
// printf("========================\n");
//     count_special_character("ls -l|grep.txt>output.txt"); // (수정 후)
// printf("========================\n");
//     count_special_character("echo\"HelloWorld\"|cat>file.txt");
// printf("========================\n");
//     count_special_character("cat<file1|grep\"test\"|wc-l");
// printf("============4===========\n");
//     count_special_character("echo\"$HOME$PATH$PATH$WOW$YES$FUCK/test\"|cut-d'/'-f2");
// printf("========================\n");
//     count_special_character("echo\"Hello\"&&echo\"World\"|cat>log.txt");
// printf("========================\n");
// 	return EXIT_SUCCESS;
// }
