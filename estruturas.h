#include <string>

/*

Aqui ficam as structs utilizadas pelo código. Só isso mesmo.

*/

typedef struct _login_ {
    char nome[100], senha[100];
} login;


typedef struct _exercicio_ {
    char *caminho;
    const char *categoria, *dificuldade;
    std::string titulo, descricao;
    bool resolvido;
} exercicio;
