#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programa.h"

int main()
{
    Lista *l;
    Lista *l2;
    int r;
    int b;
    char a[100];
    int i;
    int op = 10;
    int x;
    char y;
    int linha, linha1, linha2;

    printf("Informativo: \n os operadores sao {e,o,n,s,S} \n {e,ou,nso,se entao,se somente se} respectivamente\n");
    // criar um menu
    while (op != 0)
    {
        printf("Digite a opçao: \n");
        printf("1 - Operaçao logica\n");
        printf("2 - Validar formula logica\n");
        printf("3 - Juntar formulas\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            l = cria_lista();
            printf("Digite uma string: ");
            scanf("%s", a);
            for (i = 0; i < strlen(a); i++)
            {
                insere_lista(l, 0, a[i]);
            }

            printf("Digite os valores logicos de\n");
            for (i = 0; i < strlen(a); i++)
            {
                if (a[i] == 'e' || a[i] == 'o' || a[i] == 'n' || a[i] == 's' || a[i] == 'S' || a[i] == '(' || a[i] == ')')
                    valor_logico(l, i, 2);
                else
                {
                    printf("%c :", a[i]);
                    scanf("%d", &b);
                    valor_logico(l, i, b);
                }
            }

            imprime_lista(l);
            printf("\n");
            operacao_final(l, &r);
            printf("Resultado: %d\n", r);

            // coloca a operação e seu resultado em um arquivo de texto 'operacoes.txt' e sua posição de acordo com a linha no formato 'linha - operacao = resultado'
            FILE *arq;
            arq = fopen("operacoes.txt", "a");
            if (arq == NULL)
            {
                printf("Erro ao abrir arquivo\n");
                exit(1);
            }
            // imprime a linha no arquivo
            fprintf(arq, "%d - ", captura_ultima_linha("operacoes.txt"));
            // imprime a operação no arquivo
            fprintf(arq, "(", a);
            for (i = 0; i < strlen(a); i++)
            {
                fprintf(arq, "%c", a[i]);
            }
            fprintf(arq, ") ");
            // imprime o resultado no arquivo
            fprintf(arq, " = %d\n", r);
            fclose(arq);
            libera_lista(l);
            break;

        case 2: // validar fórmula lógica
            l = cria_lista();
            printf("Digite uma string: ");
            scanf("%s", a);
            for (i = 0; i < strlen(a); i++)
            {
                insere_lista(l, 0, a[i]);
            }
            if (validar_formula(l) == 0)
                printf("Formula valida\n");
            else
                printf("Formula invalida\n");
            libera_lista(l);
            break;

        case 3: // juntar fórmulas
            l = cria_lista();
            l2 = cria_lista();
            // imprime as operações do arquivo de texto 'operacoes.txt' para que possam ser escolhidas
            FILE *arq1;
            arq1 = fopen("operacoes.txt", "r");
            if (arq1 == NULL)
            {
                printf("Erro ao abrir arquivo\n");
                exit(1);
            }
            char c;
            printf("Operacoes no histórico:\n");
            while ((c = fgetc(arq1)) != EOF)
            {
                printf("%c", c);
            }
            // coloca uma operação do histórico em l1 e outra em l2
            printf("Digite a linha da primeira operacao: ");
            scanf("%d", &linha1);
            printf("Digite a linha da segunda operacao: ");
            scanf("%d", &linha2);
            rewind(arq1);
            while (linha < linha1)
            {
                if (fgetc(arq1) == '\n')
                    linha++;
            }
            while ((c = fgetc(arq1)) != '\n')
            {
                // começando pelo parenteses (parenteses incluso) esquerdo começa a inserir na lista até o parenteses direito
                if (c == '(')
                {
                    insere_lista(l, 0, '(');
                    while ((c = fgetc(arq1)) != ')')
                    {

                        insere_lista(l, 0, c);
                    }
                    insere_lista(l, 0, c);
                }
            }
            linha = 1;
            rewind(arq1);
            while (linha < linha2)
            {
                if (fgetc(arq1) == '\n')
                    linha++;
            }

            while ((c = fgetc(arq1)) != '\n')
            {
                if (c == '(')
                {
                    insere_lista(l2, 0, '(');
                    while ((c = fgetc(arq1)) != ')')
                    {
                        insere_lista(l2, 0, c);
                    }
                    insere_lista(l2, 0, c);
                }
            }
            fclose(arq1);
            // toda parte do case 3 daq pra cima serve para pegar as operações do arquivo de texto e colocar em duas listas, se quiser verificar o resultado das listas basta imprimir e ver que estão corretas

            printf("Digite:\n1- para adicionar antes\n2- para adicionar depois\n");
            scanf("%d", &x);
            printf("Digite o operador logico que ira interligar as funcoes\n");
            fflush(stdin);
            scanf("%c", &y);
            if (x == 1)
            {
                juntar_listas_antes(l, l2, y);
                imprime_lista(l);
                printf("\n");
            }

            else if (x == 2)
            {
                juntar_listas_depois(l, l2, y);
                imprime_lista(l);
                printf("\n");
            }

            break;
        }
    }
}
