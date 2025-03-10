#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================================
    1. 토큰 관련 정의 및 유틸리티
   ============================================================ */

typedef enum e_token_type
{
    TOKEN_CMD,
    TOKEN_STRING,
    TOKEN_FILENAME,
    TOKEN_SPACE,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VARI,
    TOKEN_EOF
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
    struct s_token *prev;
} t_token;

t_token *current_token(t_token **tokens)
{
    return (*tokens);
}

void advance_token(t_token **tokens)
{
    if (*tokens != NULL)
        *tokens = (*tokens)->next;
}

/* ============================================================
    2. AST 관련 정의 및 유틸리티
   ============================================================ */

typedef enum e_ast_node_type
{
    AST_COMMAND,
    AST_PIPE,
    AST_REDIRECTION_IN,
    AST_REDIRECTION_OUT,
    AST_REDIRECTION_APPEND,
    AST_HEREDOC,
    AST_SIMPLE_COMMAND,
    AST_WORD
} t_ast_node_type;

typedef struct s_ast_node
{
    t_ast_node_type type;
    char *value;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

t_ast_node *new_ast_node(t_ast_node_type type, const char *value,
                         t_ast_node *left, t_ast_node *right)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
    {
        fprintf(stderr, "Memory allocation error in new_ast_node\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    if (value)
        node->value = strdup(value);
    else
        node->value = NULL;

    node->left = left;
    node->right = right;
    return (node);
}

void print_ast(t_ast_node *node, int level)
{
    int i;

    if (!node)
        return;
    for (i = 0; i < level; i++)
        printf("  ");
    printf("Type: %d, Value: %s\n", node->type,
           node->value ? node->value : "NULL");
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

/* ============================================================
    3. 재귀 하향 파서 구현
   ============================================================ */

/* parse_cmd_word: 첫 단어, TOKEN_CMD 또는 TOKEN_STRING 허용 */
t_ast_node *parse_cmd_word(t_token **tokens)
{
    t_token *tok;
    t_ast_node *node;

    tok = current_token(tokens);
    if (!tok || (tok->type != TOKEN_CMD && tok->type != TOKEN_STRING))
        return (NULL);
    node = new_ast_node(AST_WORD, tok->value, NULL, NULL);
    advance_token(tokens);
    return (node);
}

/* parse_arg_word: 인자는 TOKEN_STRING 또는 TOKEN_ENV_VARI 허용 */
t_ast_node *parse_arg_word(t_token **tokens)
{
    t_token *tok;
    t_ast_node *node;

    tok = current_token(tokens);
    if (!tok || (tok->type != TOKEN_STRING && tok->type != TOKEN_ENV_VARI))
        return (NULL);
    node = new_ast_node(AST_WORD, tok->value, NULL, NULL);
    advance_token(tokens);
    return (node);
}

/* parse_filename: redirection 대상은 TOKEN_FILENAME 또는 TOKEN_ENV_VARI */
t_ast_node *parse_filename(t_token **tokens)
{
    t_token *tok;
    t_ast_node *node;

    tok = current_token(tokens);
    if (!tok || (tok->type != TOKEN_FILENAME && tok->type != TOKEN_ENV_VARI))
        return (NULL);
    node = new_ast_node(AST_WORD, tok->value, NULL, NULL);
    advance_token(tokens);
    return (node);
}

/* parse_heredoc: HEREDOC 대상은 TOKEN_EOF, TOKEN_ENV_VARI 또는 TOKEN_STRING */
t_ast_node *parse_heredoc(t_token **tokens)
{
    t_token *tok;
    t_ast_node *node;

    tok = current_token(tokens);
    if (!tok || (tok->type != TOKEN_EOF &&
                 tok->type != TOKEN_ENV_VARI &&
                 tok->type != TOKEN_STRING))
        return (NULL);
    node = new_ast_node(AST_WORD, tok->value, NULL, NULL);
    advance_token(tokens);
    return (node);
}

/* <simple_command> ::= <word> { <word> }
   첫 단어는 parse_cmd_word, 이후는 parse_arg_word */
t_ast_node *parse_simple_command(t_token **tokens)
{
    t_ast_node *first;
    t_ast_node *curr;
    t_ast_node *next;

    first = parse_cmd_word(tokens);
    if (!first)
        return (NULL);
    curr = first;
    while (current_token(tokens) &&
           (current_token(tokens)->type == TOKEN_STRING ||
            current_token(tokens)->type == TOKEN_ENV_VARI))
    {
        next = parse_arg_word(tokens);
        curr->right = next;
        curr = next;
    }
    return (new_ast_node(AST_SIMPLE_COMMAND, NULL, first, NULL));
}

/* <redirection> ::= (<redir_in>|<redir_out>|<redir_append>|<heredoc>) <word>
   redirection 대상은 parse_filename() 또는 parse_heredoc() */
t_ast_node *parse_redirection(t_token **tokens)
{
    t_token *tok;
    char *op;
    t_token_type opType;
    t_ast_node *target;
    t_ast_node_type redirType;

    tok = current_token(tokens);
    if (!tok)
        return (NULL);
    if (tok->type == TOKEN_REDIR_IN ||
        tok->type == TOKEN_REDIR_OUT ||
        tok->type == TOKEN_REDIR_APPEND ||
        tok->type == TOKEN_HEREDOC)
    {
        op = tok->value;
        opType = tok->type;
        advance_token(tokens);

        if (opType == TOKEN_HEREDOC)
        {
            if (!current_token(tokens) ||
                (current_token(tokens)->type != TOKEN_EOF &&
                 current_token(tokens)->type != TOKEN_ENV_VARI &&
                 current_token(tokens)->type != TOKEN_STRING))
            {
                fprintf(stderr,
                        "Syntax error: expected heredoc end after '%s'\n",
                        op);
                exit(EXIT_FAILURE);
            }
            target = parse_heredoc(tokens);
        }
        else
        {
            if (!current_token(tokens) ||
                (current_token(tokens)->type != TOKEN_FILENAME &&
                 current_token(tokens)->type != TOKEN_ENV_VARI))
            {
                fprintf(stderr,
                        "Syntax error: expected filename after '%s'\n",
                        op);
                exit(EXIT_FAILURE);
            }
            target = parse_filename(tokens);
        }
        if (opType == TOKEN_REDIR_IN)
            redirType = AST_REDIRECTION_IN;
        else if (opType == TOKEN_REDIR_OUT)
            redirType = AST_REDIRECTION_OUT;
        else if (opType == TOKEN_REDIR_APPEND)
            redirType = AST_REDIRECTION_APPEND;
        else
            redirType = AST_HEREDOC;
        return (new_ast_node(redirType, op, target, NULL));
    }
    return (NULL);
}

/* <pre_redirs> ::= { <redirection> } */
t_ast_node *parse_pre_redirs(t_token **tokens)
{
    t_ast_node *pre;
    t_ast_node *last;
    t_ast_node *r;

    pre = NULL;
    last = NULL;
    while (current_token(tokens) &&
           (current_token(tokens)->type == TOKEN_REDIR_IN ||
            current_token(tokens)->type == TOKEN_REDIR_OUT ||
            current_token(tokens)->type == TOKEN_REDIR_APPEND ||
            current_token(tokens)->type == TOKEN_HEREDOC))
    {
        r = parse_redirection(tokens);
        if (!pre)
        {
            pre = r;
            last = r;
        }
        else
        {
            last->right = r;
            last = r;
        }
    }
    return (pre);
}

/* <post_redirs> ::= { <redirection> } */
t_ast_node *parse_post_redirs(t_token **tokens)
{
    t_ast_node *post;
    t_ast_node *last;
    t_ast_node *r;

    post = NULL;
    last = NULL;
    while (current_token(tokens) &&
           (current_token(tokens)->type == TOKEN_REDIR_IN ||
            current_token(tokens)->type == TOKEN_REDIR_OUT ||
            current_token(tokens)->type == TOKEN_REDIR_APPEND ||
            current_token(tokens)->type == TOKEN_HEREDOC))
    {
        r = parse_redirection(tokens);
        if (!post)
        {
            post = r;
            last = r;
        }
        else
        {
            last->right = r;
            last = r;
        }
    }
    return (post);
}

/* <command> ::= { <redirection> } <simple_command> { <redirection> } */
t_ast_node *parse_command(t_token **tokens)
{
    t_ast_node *pre;
    t_ast_node *simple;
    t_ast_node *post;
    t_ast_node *cmd;
    t_ast_node *tmp;

    pre = parse_pre_redirs(tokens);
    simple = parse_simple_command(tokens);
    if (!simple)
    {
        fprintf(stderr, "Syntax error: expected simple command\n");
        exit(EXIT_FAILURE);
    }
    post = parse_post_redirs(tokens);
    cmd = new_ast_node(AST_COMMAND, NULL, simple, NULL);
    if (pre)
    {
        tmp = pre;
        while (tmp->right)
            tmp = tmp->right;
        tmp->right = simple;
        cmd->left = pre;
    }
    if (post)
        cmd->right = post;
    return (cmd);
}

/* <command_line> ::= <command> { "|" <command> } */
t_ast_node *parse_command_line(t_token **tokens)
{
    t_ast_node *cmd;
    t_ast_node *node;
    t_ast_node *next;

    cmd = parse_command(tokens);
    if (!cmd)
        return (NULL);
    node = cmd;
    while (current_token(tokens) &&
           current_token(tokens)->type == TOKEN_PIPE)
    {
        advance_token(tokens);
        next = parse_command(tokens);
        node = new_ast_node(AST_PIPE, "|", node, next);
    }
    return (node);
}

/* ============================================================
    4. 예제: 토큰 리스트 구성 및 파서 실행
   ============================================================ */

t_token *create_token(t_token_type type, const char *lexeme)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        fprintf(stderr, "Memory allocation error in create_token\n");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->value = strdup(lexeme);
    token->next = NULL;
    token->prev = NULL;
    return (token);
}

void free_tokens(t_token *head)
{
    t_token *cur;
    t_token *tmp;

    cur = head;
    while (cur)
    {
        tmp = cur;
        cur = cur->next;
        free(tmp->value);
        free(tmp);
    }
}

int main(void)
{
    t_token *t1;
    t_token *t2;
    t_token *t3;
    t_token *t4;
    t_token *t5;
    t_token *t6;
    t_token *t7;
    t_token *t8;
    t_token *t9;
    t_token *t10;
    t_token *t11;
    t_token *t12;
    t_ast_node *ast;
    t_token *token_copy;

    /* 빈 줄 */

    t1 = create_token(TOKEN_CMD, "cat");
    t2 = create_token(TOKEN_STRING, "test.txt");
    t3 = create_token(TOKEN_PIPE, "|");
    t4 = create_token(TOKEN_CMD, "grep");
    t5 = create_token(TOKEN_STRING, "hello");
    t6 = create_token(TOKEN_HEREDOC, "<<");
    t7 = create_token(TOKEN_EOF, "END_OF_STRING");
    t8 = create_token(TOKEN_PIPE, "|");
    t9 = create_token(TOKEN_CMD, "grep");
    t10 = create_token(TOKEN_STRING, "my");
    t11 = create_token(TOKEN_REDIR_APPEND, ">>");
    t12 = create_token(TOKEN_FILENAME, "test.txt");

    t1->next = t2;
    t2->next = t3;
    t3->next = t4;
    t4->next = t5;
    t5->next = t6;
    t6->next = t7;
    t7->next = t8;
    t8->next = t9;
    t9->next = t10;
    t10->next = t11;
    t11->next = t12;
    t12->next = NULL;

    /* 원본 토큰 리스트는 t1이고, 복제 포인터(token_copy)는 t1을 가리키게 함 */
    token_copy = t1;

    ast = parse_command_line(&token_copy);

    printf("=== AST ===\n");
    print_ast(ast, 0);

    free_tokens(t1);
    return (0);
}

// 에러가 발생했을 때 free해줘야하는것들이 뭐가 있을까.
// 우선은 tokenlist를 해제해줘야하고
// 만약 ast를 만드는 도중 에러가 ㅁ발생했다면 ast를 헤재해주는 함수를 만들어야하고
//     env도 free해줘야하고
//         근데 free해주면서 각 char *value도 다 free해줘야하고,
//     일단 그정도를 free해줘야하는데
//         그러면 어떻게 만들어야하지.만약 구문트리를 만들다가 에러가 났어.그러면 그냥 toekn리스트 부터 구문트리까지 다 지워버려야하는거고
//             렉싱을 하다가 따옴표가 닫히지 않았다거나 하는 에러가 발생했으면 토큰리스트만 프리해주면 되는거고
//                 대신 환경변수리스트는 항상 어떤 에러가 발생하더라도 프리를 해줘야하는거고
//                     나머지 프리를 뭘 해줘야할지는 실행부인 재원이형과 이야기를 해봐야할것같고
//                         일단 그럼 지금 남은게
//                             에러처리해주기
//                                 환경변수 확장처리해주기
//                                     정도인것같은데
//                                         오케이 거의 다 되어가는 것 같구만
