#include "usuarios.h"
#include "estruturas.h"
#include "suporte.h"
#include "exercicios.h"
#include "menuInicial.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*

Aqui ficam as funções que exibem o menu de cadastrar
usuário e a funcionalidade de cadastrar usuário,
junto com menu de efetuar login e da funcionalidade
de efetuar login.

As descrições de cada função se encontram no arquivo
'usuarios.h' para não poluir visualmente (mais do
que já está poluído) este arquivo.

*/

void cadastrar_usuario(){
    system("clear");
    cout << "Bem-vindo a tela de cadastro de novos usuarios!(Tecle enter se nada aparecer)\n" << endl;
    login usuario; // Struct que receberá o login (nome + senha)
    fstream arquivo;
    char opcao;

    // Criando/acessando o arquivo de login
    arquivo.open("database/logins.txt", ios::out|ios::app);
    arquivo.close();

    // Adquirindo o nome de usuário
    while (true){
        cout << "Digite um nome de usuario que voce queira.\nPode usar qualquer simbolo exceto o '*' ou '/': ";
        cin >> usuario.nome;

        // Verificando se o nome é válido, e irá continuar nesse loop até que o usuário digite corretamente.
        if( ( buscaCaractere(usuario.nome, '*') + buscaCaractere(usuario.nome, '/')  ) != 0){
            cout << "Nome de usuario invalido. Digite novamente.\n";
            esperar(1.5);
            system("clear");
         }
         else break;
    }

    cout << "\n";

    // Adquirindo a senha do usuário
    while (true){
        cout << "Digite uma senha.\nEla tambem nao pode conter '*' ou '/': ";
        cin >> usuario.senha;
        //cin >> usuario.senha;

        // Verificando se a senha é válida, do mesmo jeitinho
        if( ( buscaCaractere(usuario.senha, '*') + buscaCaractere(usuario.senha, '/') ) != 0){
            cout << "Senha invalida. Digite novamente.\n";
            esperar(1.5);
            system("clear");
         }
         else break;
    }

    // Checando se o usuário quer cadastrar com um nome de usuário que já está cadastrado
    arquivo.open("database/logins.txt", ios::in);
    unsigned posBusca1 = 0, posBusca2 = 0;
    string linha;
    char *buffer, *stringLinha, *stringNome;

    // "Convertendo" a string para um tipo mais "palpável", char
    getline(arquivo, linha);
    buffer = new char[linha.length()];
    strcpy(buffer, linha.c_str());

    while (posBusca1 < strlen(buffer)){ // Enquanto não chegar ao final da linha
        // Extraindo um login (nome e senha juntos)
        stringLinha = split(buffer, '/', &posBusca1);

        // Extraindo apenas o nome do login
        stringNome = split(stringLinha, '*', &posBusca2);

        // Comparando se nome digitado está no arquivo
        if ( (strcmp(usuario.nome, stringNome) == 0) || (strcmp(usuario.nome, "admin") == 0) ){
            system("clear");
            cout << "O nome de usuario " << usuario.nome << " ja esta cadastrado ou não pode ser usado.\n";
            // Um swtichzinho só para facilitar o erro do nosso querido usuário
            cout << "Tentar novamente?(S para sim, qualquer outra tecla para voltar ao menu principal)\nDigite: ";
            cin >> opcao;
            switch (opcao){
                case 'S':
                case 's':
                    system("clear");
                    cadastrar_usuario();
                    break;
                default:
                    system("clear");
                    menu_principal();
            }
            esperar(2);
            system("clear");
            cadastrar_usuario();
        }
        posBusca2 = 0; // Faz com que a procura sempre seja desde o inicio da substring a cada interação.
    }

    arquivo.close();
    // Se ele escapar desse while, então podemos gravar no arquivo
    arquivo.open("database/logins.txt", ios::out|ios::app);
    arquivo << usuario.nome << "*";         // O * é o delimitador que separa o nome de usuário de sua senha
    arquivo << usuario.senha << "/";        // O / é o delimitador que separa cada LOGIN (nome + senha) do outro
    arquivo.close();

    // Confirmando pro usuário as informações digitadas
    cout << "\nLogin: " << usuario.nome << endl;
    cout << "Senha: " << usuario.senha << endl;
    cout << "Cadastrado com sucesso!\n";
    esperar(2); // Delay de leve para dar tempo do usuário ver
    system("clear");

    // Chamando o menu principal novamente, saindo da tela de cadastro
    menu_principal();
}

void login_usuario(){
    system("clear");
    login usuario; // Novo login
    string linha; // String que guarda os dados do arquivo de texto
    fstream arquivo;
    bool achou = false; // Flag pra saber se o login foi valido ou nao
    char *stringLinha, *stringNome, *stringSenha, *buffer, opcao; // Strings que guardarão cada parte do login e outros
    unsigned posBusca1 = 0, posBusca2 = 0; /* preciso de dois posBuscas e dois strings porque vou dividir
    minha string duas vezes atraves dois delimitadores diferentes */

    // Ficará no loop até digitar corretamente ou voltar ao menu inicial
    while (achou == false){

        cout << "Bem-vindo a tela de login!\nDigite suas informacoes para acessar o Proximo Exercicio!\n";
        cout << "Digite o seu nome de usuario: ";
        cin >> usuario.nome;
        cout << "Digite a sua senha: ";
        cin >> usuario.senha;

        // Retirando do arquivo de texto os logins e salvando em buffer
        arquivo.open("database/logins.txt", ios::in);
        getline(arquivo, linha);

        // "Convertendo" a string para um tipo mais "palpável", char
        buffer = new char[linha.length()];
        strcpy(buffer, linha.c_str());

        /* posBusca1 e posBusca2 são modificados na função toda vez que um delimitador novo é encontrado
        portanto, ao chamar a função mais de uma vez, ele irá procurar a partir
        do novo valor de posBuscaX */

        // Separando os logins e fazendo a checagem
        // Fazendo a checagem inicial se o usuario é o queridissimo administrador
        if ( (strcmp(usuario.nome, "admin") == 0) && (strcmp(usuario.senha, "admin") == 0) ) {
            cadastrar_exercicio(); // Chama o menu de cadastrar exercício para o administrador
        }
        else {
            while (posBusca1 < strlen(buffer)){ // Enquanto não chegar ao final da linha
                // Extraindo um login (nome e senha juntos)
                stringLinha = split(buffer, '/', &posBusca1);

                // Extraindo o nome do login
                stringNome = split(stringLinha, '*', &posBusca2);

                // Extraindo a senha do login
                stringSenha = split(stringLinha, '*', &posBusca2);

                // Comparando se a senha e o nome batem com os dados digitados pelo usuário
                if ( (strcmp(usuario.nome, stringNome) == 0) && (strcmp(usuario.senha, stringSenha) == 0) ) {
                    achou = true;
                    break;
                }
                posBusca2 = 0; // Faz com que a procura sempre seja desde o inicio da substring a cada interação.
            }
        }


        // Mostrando pro usuario se ele conseguiu logar ou não
        if (achou) menu_exercicios(usuario); // Retornando o usuário atual para a função do menu de exercícios.
        else {
            system("clear");
            cout << "Usuario e/ou senha invalidos. \n";

            // Um swtichzinho só para facilitar o erro do nosso querido usuário
            cout << "Tentar novamente?(S para sim, qualquer outra tecla para voltar ao menu principal)\nDigite: ";
            cin >> opcao;
            switch (opcao){
                case 'S':
                case 's':
                    system("clear");
                    login_usuario();
                    break;
                default:
                    system("clear");
                    menu_principal();
            }
        }

    }

}
