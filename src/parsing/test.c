#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char *input = "e\'\'cho hello'\"helo;'";
    char *parsed = process_quotes(input);
    printf("Result: %s\n", parsed); // Outputs: hellohelo
    free(parsed);
    return 0;
}

