#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<time.h>
#include "forca.h"

//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA]; char chutes[26];
int chutesDados = 0;

void abertura() {
    printf("***************\n");
    printf(" Jogo da Forca \n");
    printf("***************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra) {
    int achou = 0;

    for(int j = 0; j < chutesDados; j++) { //chute
        if(chutes[j] == letra) {
            achou = 1; //chute correto
            break;
        }
    }
    return achou;
}

void desenhaForca() {
    int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) { //estou vendo a letra secreta

        int achou = jaChutou(palavrasecreta[i]);

        if(achou) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
        printf("\n");
}

void adicionaPalavra() {
    char quer;
    printf("Você desenha adicionar uma nova palavra no jogo? (S/N) ");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("forca.txt", "r+"); //r+ significa ler e escrever
        if (f == 0) {
            printf("Desculpe, banco de dados não disponível");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd); //le a quantidade de palavras no começo do arquivo
        qtd++;

        fseek(f, 0, SEEK_SET); //coloca o ponteiro no começo do arquivo e escreve em cima
        fprintf(f, "%d", qtd); //como ali em cima salvamos na variavel e nao no arquivo, agora fazemos isso

        fseek(f, 0, SEEK_END); //coloca o ponteiro no final do arquivo
        fprintf(f, "%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra() {
    FILE* f;

    f = fopen("forca.txt", "r"); //abre arquivo
    if (f == 0) {
        printf("Desculpe, banco de dados não disponível");
        exit(1);
    }

    int qtdDePalavras;
    fscanf(f, "%d", &qtdDePalavras); //descobre quantas palavras tem no arquivo

    srand(time(0));
    int randomico = rand() % qtdDePalavras; //calcula um numero aleatorio

    for(int i = 0; i <= randomico; i++) { //vai lendo o arquivo ate chegar na posição aleatoria
        fscanf(f, "%s", palavrasecreta); //le o arquivo
    }
    fclose(f);
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jaChutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}
int chutesErrados() {
    int erros = 0;
    for(int i = 0; i < chutesDados; i++) {
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou() {
    return chutesErrados() >= 5;
}

// ! O PROGRAMA COMEÇA AQUI !

int main() {
    setlocale(LC_ALL,"PORTUGUESE");

    escolhePalavra();
    abertura();

    do {
        desenhaForca();
        chuta();
    } while(!acertou() && !enforcou());

    if(acertou()) {
        printf("Parabéns, você ganhou!\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("Puxa, você foi enforcado!\n");
        printf("A palavra certa era %s.\n",palavrasecreta);
        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionaPalavra();

    system("PAUSE");
    return 0;
}
