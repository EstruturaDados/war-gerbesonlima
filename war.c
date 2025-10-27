
#include <stdio.h>
#include <string.h>

//Criação da STRUCT
struct Territorio
{
    char nome [30];
    char cor [10];
    int tropas;
};

//Função principal do programa
int main(){
    const int TOTAL_TERRITORIOS = 5;
    struct  Territorio territorios [TOTAL_TERRITORIOS];
    int i;
    //ENTRADA DE DADOS
    {
        printf("---CADASTRO DE TERRITORIOS DO JOGO WAR ---\n \n");
        for (int i = 0; i < TOTAL_TERRITORIOS; i++)
        {
            printf("---Dados do Territorio %d ---\n", i + 1);
            printf("Digite o nome do territorio: ");
            scanf("%s", territorios[i].nome);

            printf("Digite a cor do exercito: ");
            scanf("%s",territorios[i].cor);

            printf("Digite a quantidade de tropas: ");
            scanf("%d", &territorios[i].tropas );

            printf("\n");
        }

        //Exibição de dados

        printf("\n --- TERRITORIOS CADASTRADOS --- \n\n");

        for (int i = 0; i < TOTAL_TERRITORIOS; i++)
        {
            printf("Territorios %d: \n", i + 1);//Erro aqui
            printf ("Nome: %s\n:", territorios[i].nome);
            printf("Cor do Exercito: %s\n", territorios[i].cor);
            printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
            printf("------------------------------------");
        }     


    };
    
    return 0;
}