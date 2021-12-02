#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

// funcao mostrar tabuleiro do jogo
void mostrarJogo(char jogo[3][3], int pontos){
    system("cls");
    printf("sua pontuação: %d\n\n", pontos);
        for(int i = 0; i < 3; i++){
            if(i == 0)
                printf(" 1   2   3\n\n");
            for(int j = 0; j < 3; j++){
                printf(" %c ", jogo[i][j]);
                if(j != 2)
                    printf("│");
            }
            printf("  %d", i+1);
            if(i != 2){
                printf("\n───┼───┼───\n");
            }
        }
    }

//funcao verificar se alguem ganhou por linha, coluna ou diagonal
int verificar(char jogo[3][3]){
    int j;
    for(int i = 0; i < 3; i++){// verifica se ganhou pela linha
        j = 0;
        if(jogo[i][j] != ' '){
            if(jogo[i][j] == jogo[i][j+1] && jogo[i][j+1] == jogo[i][j+2]){
                return 1;
            }
        }
    }

    for(int i = 0; i < 3; i++){// verifica se ganhou pela coluna
        j = 0;
        if(jogo[j][i] != ' '){   
            if(jogo[j][i] == jogo[j+1][i] && jogo[j+1][i] == jogo[j+2][i]){
                return 1;
            }
        }  
    }

    if(jogo[1][1] != ' '){//verifica se ganhou na diagonal
        if(jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2]){
            return 1;
        }
        if(jogo[0][2] == jogo[1][1] && jogo[1][1] == jogo[2][0]){
            return 1;
        }
    }
    

    return 0;
}

//funcao verifica se ainda existem espaços em branco para jogar
int partida(char jogo[3][3]){
    for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(jogo[i][j] == ' '){
                    return 1;
                }
            }
        }
    printf("            EMPATOU!\n\n");
    return 0;
}

//funcao realiza cada jogada
void jogada(int p, int l, int c, char jogo[3][3]){
    do{ 
        if(p== 0){
            printf("linha: ");
            scanf("%d", &l);
            printf("coluna: ");
            scanf("%d", &c);
        }else{
            srand(time(NULL));
            l = (rand() % 3) + 1;
            c =  (rand() % 3) + 1;
            //se o numero aleatorio caiu em uma casa com valor, procura a primeira casa vazia e joga nela
            if(jogo[l-1][c-1] != ' '){
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        if(jogo[i][j] == ' '){
                            l = i+1;
                            c = j+1;
                            i = 3;
                            break;
                        }
                    }
                }
            }
        }

    }while(l <= 0 || l > 3 || c <= 0 || c > 3 || jogo[l-1][c-1] != ' ');

    if(p == 0){ // player 1
        jogo[l-1][c-1] = 'O';    
    }else{ // player 2
        jogo[l-1][c-1] = 'X';
    }
    system("cls");
}


struct Jogador{
    char nome[10];
    int pontos;
};


//ordenação bubble sort dos array com o ranking
void bubble_sort(int* pontuacao, char jogadores[5][10], int tamanho){

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho - 1; j++){
            //verifica se o adjacente é maior e faz a contra entre eles
            if(pontuacao[j] < pontuacao[j+1]){
                int auxp = pontuacao[j];
                pontuacao[j] = pontuacao[j+1];
                pontuacao[j+1] = auxp;
                char auxj[10];
                strcpy(auxj, jogadores[j+1]);
                strcpy(jogadores[j+1], jogadores[j]);
                strcpy(jogadores[j], auxj);

            }
        }
    } 


}



int main(){
    int l = -1, c = -1, opcao = -1, tamanho, vida;
    char matrix[3][3];
    FILE *rank;
    struct Jogador j;
    int pontuacoes[10];
    char jogadores[10][10];
    int pontuacao;
    char jogador[10];
    char continuar;



    while (opcao != 4){
        system("cls");
        tamanho = 0;
        continuar = 's';
        vida = 2;
        j.pontos = 0;

        // menu
        printf("|1 - JOGAR    |\n|2 - RANKING  |\n|3 - CREDITOS |\n|4 - SAIR     |\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
                system("cls");
                printf("Digite seu nome: ");
                fflush(stdin);
                fgets(j.nome,10,stdin);
                j.nome[strlen(j.nome) - 1] = '\0';

            while(vida > 0){
                //preencher a matrix do jogo com espaços em branco
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        matrix[i][j] = ' ';
                    }
                }

                mostrarJogo(matrix, j.pontos);

                for(int i = 0; i < 9; i++){
                    if(i%2 == 0){
                        printf("\n\nVez de %s:\n", j.nome);
                        jogada(0,l,c,matrix);
                    }else{
                        printf("\n\nJOGADOR 2 (COM)...''pensando''\n");
                        Sleep(2000);
                        jogada(1,l,c,matrix);
                    }
                    
                    mostrarJogo(matrix, j.pontos);

                    if(verificar(matrix) == 1){
                        if(i%2==0){
                            printf("            -- %s VENCEU --\n\n", j.nome);
                            j.pontos++;
                        }else{
                            printf("            -- COMPUTADOR VENCEU --\n\n");
                            vida--;
                            if(vida > 0){
                                printf("Você possui %d vida\n", vida);
                            }else{
                                printf("Game over!\n");
                                printf("Sua pontução final: %d\n", j.pontos);
                                rank = fopen("ranking.txt","a");
                                fprintf(rank, "%s %d\n", j.nome, j.pontos);
                                fclose(rank);
                            }
                        }
                        break;
                    }
                    partida(matrix);
                }
                system("pause");
            }
            break;
        case 2:
            system("cls");
            rank = fopen("ranking.txt", "r");
            printf("    OS 5 MELHORES\nNOME     |    PONTUAÇÃO\n");
            //adiciona a um array o nome e em outro os pontos de cada linha do txt
            while(fscanf(rank,"%s %d",  jogador, &pontuacao) != EOF){
                strcpy(jogadores[tamanho], jogador);
                pontuacoes[tamanho] = pontuacao;
                tamanho++;
            }

            bubble_sort(pontuacoes, jogadores, tamanho);

            //mostra na tela os 5 primeiros com mais pontos
            for(int i = 0; i < 5; i++){
                printf("%s.......... %d\n", jogadores[i], pontuacoes[i]);
            }

            fclose(rank);
            
            
            system("pause");
            break;
        case 3:
            // creditos do desenvolvedor do prejeto
            system("cls");
            printf("Desenvolvido por Daniel Oliveira\nAluno da Unipê - Ciência da Computação\n2021\n\n");
            system("pause");
            break;
        case 4:
            // sair do jogo
            printf("FIM DE JOGO");
            break;
        default:
            printf("Opção inválida");
            break;
        }
    }
    

    return 0;

}