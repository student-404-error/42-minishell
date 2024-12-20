#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "parsing.h"

// 메모리 정리 함수
void free_tokens(t_token *tokens) {
    t_token *temp;
    while (tokens) {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

// 테스트 1: 간단한 명령어 처리
static void test_simple_command(void **state) {
	t_data *data = *state;

	char *input = "echo hello";
    t_token *tokens = tokenize(data, input);

    // 첫 번째 토큰 확인
    assert_non_null(tokens);
    // assert_int_equal(tokens->type, TOKEN_COMMAND);
    assert_string_equal(tokens->value, "echo");

	// 두 번째 토큰 확인
    assert_non_null(tokens->next);
    // assert_int_equal(tokens->type, TOKEN_SPACE);
    assert_string_equal(tokens->next->value, " ");
    
	// 세 번째 토큰 확인
    assert_non_null(tokens->next->next);
    // assert_int_equal(tokens->next->type, TOKEN_STRING);
    assert_string_equal(tokens->next->next->value, "hello");

    // 마지막 토큰이 NULL인지 확인
    assert_null(tokens->next->next->next);

    free_tokens(tokens); // 메모리 해제
}

// 테스트 2: 따옴표 처리
static void test_quoted_string(void **state) {
	t_data *data = *state;

    char *input = "echo 'hello world'";
    t_token *tokens = tokenize(data, input);

    // 첫 번째 토큰 확인
    assert_non_null(tokens);
    // assert_int_equal(tokens->type, TOKEN_COMMAND);
    assert_string_equal(tokens->value, "echo");

	// 두 번째 토큰 확인
    assert_non_null(tokens->next);
    // assert_int_equal(tokens->type, TOKEN_SPACE);
    assert_string_equal(tokens->next->value, " ");

    // 두 번째 토큰 확인
    assert_non_null(tokens->next->next);
    // assert_int_equal(tokens->next->type, TOKEN_STRING);
    assert_string_equal(tokens->next->next->value, "'hello world'");

    // 마지막 토큰이 NULL인지 확인
    assert_null(tokens->next->next->next);

    free_tokens(tokens);
}

// 테스트 3: 특수 문자 처리
static void test_special_operators(void **state) {
    t_data *data = *state;

    char *input = "echo hello && ls";
    t_token *tokens = tokenize(data, input);

    // 첫 번째 토큰
    assert_non_null(tokens);
    assert_string_equal(tokens->value, "echo");

	// 두 번째 토큰 확인
    assert_non_null(tokens->next);
    // assert_int_equal(tokens->type, TOKEN_SPACE);
    assert_string_equal(tokens->next->value, " ");

    // 두 번째 토큰
    assert_non_null(tokens->next->next);
    assert_string_equal(tokens->next->next->value, "hello");
	// 두 번째 토큰 확인
    assert_non_null(tokens->next->next->next);
    // assert_int_equal(tokens->type, TOKEN_SPACE);
    assert_string_equal(tokens->next->next->next->value, " ");

    // 세 번째 토큰 (&&)
    assert_non_null(tokens->next->next->next->next);
    assert_string_equal(tokens->next->next->next->next->value, "&&");
	// 두 번째 토큰 확인
    assert_non_null(tokens->next->next->next->next->next);
    // assert_int_equal(tokens->type, TOKEN_SPACE);
    assert_string_equal(tokens->next->next->next->next->next->value, " ");

    // 네 번째 토큰
    assert_non_null(tokens->next->next->next->next->next->next);
    assert_string_equal(tokens->next->next->next->next->next->next->value, "ls");

    // 마지막 토큰이 NULL인지 확인
    assert_null(tokens->next->next->next->next->next->next->next);

    free_tokens(tokens);
}

// 테스트 그룹
int main(int ac, char *av[], char **env) {
	t_data	data;

	init_env(&data, env);
	(void)ac;
	(void)av;
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_prestate(test_simple_command, &data),
        cmocka_unit_test_prestate(test_quoted_string, &data),
        cmocka_unit_test_prestate(test_special_operators, &data),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
//
// // 테스트 1: NULL 입력 처리
// static void test_null_input(void **state) {
//     (void)state;  // Unused parameter
//
//     char **tokens = tokenize(NULL);
//     assert_null(tokens);
// }
//
// // 테스트 2: 빈 문자열 처리
// static void test_empty_string(void **state) {
//     (void)state;  // Unused parameter
//
//     char **tokens = tokenize("");
//     assert_null(tokens);
// }
