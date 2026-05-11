<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct noCarta
{
    short num;
    char naipe;
    struct noCarta *prox;
} tCarta; // struct de carta

const char *naipeStr(char naipe)
{
    switch (naipe)
    {
    case 3:
        return "\xe2\x99\xa5"; // ♥
    case 4:
        return "\xe2\x99\xa6"; // ♦
    case 5:
        return "\xe2\x99\xa3"; // ♣
    case 6:
        return "\xe2\x99\xa0"; // ♠
    default:
        return "?";
    }
}

tCarta *primMesa[8];
tCarta *primNaipe[4];
tCarta *temp[4];
tCarta *primMonte = NULL;

void gerarBaralho()
{
    int i, j;
    tCarta *ult;
    for (i = 3; i < 7; i++)
    {
        for (j = 1; j < 14; j++)
        {
            if (primMonte == NULL)
            {                                                 // Verificando se a carta a ser gerada é a primeira do monte
                primMonte = (tCarta *)malloc(sizeof(tCarta)); // Gerando a primeira carta do monte
                ult = primMonte;
            }
            else
            {
                ult->prox = (tCarta *)malloc(sizeof(tCarta)); // Gerando as outras cartas do baralho e ajustando os ponteiros para apontar para a proxima carta do monte
                ult = ult->prox;
            }
            ult->naipe = i;   // Ajustando o naipe da carta gerada
            ult->num = j;     // Ajustando o número da carta gerada
            ult->prox = NULL; // Ajustando o ponteiro da ultima carta para nulo
        }
    }
}

void embaralhaBaralho()
{
    int i, j, sort;
    tCarta *atual, *ant;
    for (i = 0; i < 26; i++)
    {                       // Realizar o processo de embaralhar 26 vezes (metade de 52)
        sort = rand() % 52; // Sorteando uma carta para ser embaralhada
        ant = NULL;
        atual = primMonte;
        for (j = 0; j < sort; j++)
        { // Selecionando a carta a ser embaralhada
            ant = atual;
            atual = atual->prox;
        }
        if (sort > 0)
        { // Alterando o ponteiro do prox para "mudar a carta de lugar"
            ant->prox = atual->prox;
            atual->prox = primMonte; // Coloca a primeira carta do balho no lugar da carta sorteada
            primMonte = atual;       // Coloca a carta sorteada no lugar da primeira carta do baralho
        }
    }
}

void distribuirMesa()
{
    int i = 0;
    tCarta *auxMonte, *auxMesa;
    while (primMonte != NULL)
    {                                // Loop para percorer o baralho inteiro
        auxMonte = primMonte;        // Ajustando os ponteiros auxiliares
        primMonte = primMonte->prox; // Atualizando o monte apos a carta ter sido movida do monte
        if (primMesa[i] == NULL)
        {                             // Verificando se a primeira posição da mesa está vazia
            primMesa[i] = auxMonte;   // Passando a carta para a primeira posição da mesa
            primMesa[i]->prox = NULL; // Atualizando que a primeira carta vai apontar para nulo pois as outras cartas da pilha vao apontar para ela posteriormente
        }
        else
        {
            auxMesa = primMesa[i];       // Ponteiro auxiliar recebendo a ultima carta que foi adicionada na mesa
            primMesa[i] = auxMonte;      // Recebendo a proxima carta do monte
            primMesa[i]->prox = auxMesa; // Atualizando o ponteiro da carta na mesa para apontar para a ultima carta que foi adicionada
        }
        if (primMonte == NULL)
        {
            break;
        }
        i = (i + 1) % 8; // O inteiro i vai variar de 0 ate 7
    }
}

void imprime()
{
    int i;
    tCarta *atual;
    printf("[TEMP]= ");
    for (i = 0; i < 4; i++)
    {
        if (temp[i] != NULL)
        { // Como todos os espaços do temp foram iniciados como NULL, se tiver alguma carta no temp ele vai printar a carta se não ele vai printar um espaço em branco
            printf("%d-[%02d|%s] ", i, temp[i]->num, naipeStr(temp[i]->naipe));
        }
        else
        {
            printf("%d-[    ] ", i); // Printando um espaço vazio caso não tenha nenhuma carta no temp
        }
    }
    printf("\n\n");
    for (i = 0; i < 4; i++)
    {                         // For para realizar o print das 4 posições do naipe
        atual = primNaipe[i]; // Utilizando um ponteiro auxiliar para trabalhar com o primNaipe
        printf("[NAIPE %d]=", i);
        while (atual != NULL)
        { // Como todos os espaços do naipe foram iniciados como NULL, se tiver alguma carta no naipe ele vai printar a carta se não ele vai printar um espaço vazio ate enviarem uma carta para o naipe
            printf("[%02d|%s]", atual->num, naipeStr(atual->naipe));
            atual = atual->prox; // Ajustando o ponteiro para apontar para o proximo espaço vazio do primNaipe[i]
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < 8; i++)
    {                        // For para realizar o print das 8 posições da mesa
        atual = primMesa[i]; // Utilizando um ponteiro auxiliar para trabalhar com o primMesa
        printf("[MESA %d]=", i);
        while (atual != NULL)
        { // Como todos os espaços da mesa foram iniciados como NULL, se tiver alguma carta na mesa ele vai printar a carta se não ele vai printar um espaço vazio, porém apos a funcao
          // distribuirMesa for chamada ele vai printar 7 cartas nas posições 0,1,2,3 da mesa e 6 cartas nas posições 4,5,6,7
            printf("[%02d|%s]", atual->num, naipeStr(atual->naipe));
            atual = atual->prox; // Ajustando o ponteiro para apontar para o proximo espaço vazio do primMesa[i]
        }
        printf("\n");
    }
    printf("\n");
}

void moveMesaTemp()
{
    int posMesa, posTemp;
    tCarta *ant, *atual;
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posMesa >= 0) && (posMesa <= 7) && (primMesa[posMesa] != NULL))
    {                                   // Verificando se a posição selecionada é valida
        printf("Posicao Temp (0-3): "); // Selecionando a posição da temp para onde a carta selecionada vai
        scanf("%d", &posTemp);
        ant = NULL;                // Ajustando os ponteiros auxiliares
        atual = primMesa[posMesa]; // Ajustando os ponteiros auxiliares
        while (atual->prox != NULL)
        { // Selecionando a carta a ser movida
            ant = atual;
            atual = atual->prox;
        }
        if ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] == NULL))
        { // Verificando se a posição da temp selecionada é valida
            if (ant == NULL)
            {
                primMesa[posMesa] = NULL;
            }
            else
            {
                ant->prox = NULL;
            }
            temp[posTemp] = atual; // Passando a carta selecionada para a posição selecionada na temp
        }
        else
        {
            printf(" Nao é possivel mover a carta para o temp \n");
        }
    }
    else
    {
        printf(" Pilha e invalida ou esta vazia \n");
    }
}

void moveTempMesa()
{
    int posTemp, posMesa;
    tCarta *atual;
    printf("Posicao Temp (0-3): "); // Selecionando a posição da temp onde a carta está armazenada, para move-la para a mesa
    scanf("%d", &posTemp);
    if ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] != NULL))
    {                                         // Verificando se a posição da temp selecionada é valida
        printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa para onde a carta, selecionada na temp, vai ser enviada
        scanf("%d", &posMesa);
        if ((posMesa >= 0) && (posMesa <= 7))
        { // Verificando se a posição da mesa selecionada é valida
            if (primMesa[posMesa] == NULL)
            {                                      // Verificando se a pilha da mesa selecionada está vazia, se estiver ele vai passar a carta sem fazer a verificação de numero e naipe
                primMesa[posMesa] = temp[posTemp]; // Passando a carta selecionada da temp para a mesa na pilha selecionada anteriormente
                temp[posTemp] = NULL;              // Atualizando a posição da temp selecionada apos a carta ter sido retirada
            }
            else
            {
                atual = primMesa[posMesa]; // Ajustando o ponteiro auxiliar
                while (atual->prox != NULL)
                {
                    atual = atual->prox; // Buscando a posição livre dentro da pilha selecionada na mesa
                }
                if (atual->num - 1 == temp[posTemp]->num)
                {                                // Verificando se a jogada pode ser efetuada(verificando se o numero da carta que sai da temp pode ser posto na pilha (um exemplo de jogada que nao pode ocorrer e colocar uma carta de numero 4 em cima de uma carta de numero 2)
                    atual->prox = temp[posTemp]; // Passando a carta da temp para a posicao livre na pilha selecionada
                    temp[posTemp] = NULL;        // Atualizando a temp para vazia apos a carta ter sido movida
                }
                else
                {
                    printf(" Nao é possivel mover temp para mesa \n");
                }
            }
        }
        else
        {
            printf(" Nao é possivel mover temp para mesa \n");
        }
    }
    else
    {
        printf(" Temp está vazio \n");
    }
}

void moveMesaNaipe()
{
    int posMesa, posNaipe;
    tCarta *ant, *atual, *aux;
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posMesa >= 0) && (posMesa <= 7) && (primMesa[posMesa] != NULL))
    {                                    // Verificando se a posição selecionada é valida
        printf("Posicao Naipe (0-3): "); // Selecionando a posição do naipe para onde a carta selecionada vai
        scanf("%d", &posNaipe);
        ant = NULL;                // Ajustando o ponteiro auxiliar
        atual = primMesa[posMesa]; // Ajustando o ponteiro auxiliar
        while ((atual->prox != NULL) && (primMesa[posMesa] != NULL))
        { // Selecionando a carta que vai ser movida
            ant = atual;
            atual = atual->prox;
        }
        if ((posNaipe >= 0) && (posNaipe <= 3) && (((atual->num == 1) && (primNaipe[posNaipe] == NULL)) || ((primNaipe[posNaipe] != NULL) && (atual->naipe == primNaipe[posNaipe]->naipe) && (atual->num - 1 == primNaipe[posNaipe]->num))))
        {
            // Verificando se a jogada pode ser efetuada(esta verificando se é a primeira carta a ser adicionada, verificando se a primeira carta a ser adicionada é o numero 1, verificando se as proximas cartas a serem adicionadas são do mesmo naipe e se estão na ordem numerica)
            if (ant == NULL)
            {
                primMesa[posMesa] = NULL;
            }
            else
            {
                ant->prox = NULL;
            }
            if (primNaipe[posNaipe] == NULL)
            { // Verificando se a posição selecionada do naipe está vazia (Primeira carta a ser adicionada no naipe)
                primNaipe[posNaipe] = atual;
            }
            else
            {
                aux = primNaipe[posNaipe]; // Caso ja tenha uma carta na posição selecionada, ele adiciona a proxima carta e atualiza o ponteiro para que a carta que está sendo adicionada aponte para a carta anterior
                primNaipe[posNaipe] = atual;
                primNaipe[posNaipe]->prox = aux;
            }
        }
        else
        {
            printf(" Nao é possivel mover a carta selecionada para naipe \n");
        }
    }
    else
    {
        printf(" Pilha invalida ou vazia \n");
    }
}

void destroiPilha()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        tCarta *atual = primMesa[i];
        tCarta *apaga;
        while (atual != NULL)
        {
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }
    }
    for (i = 0; i < 4; i++)
    {
        tCarta *atual1 = primNaipe[i];
        tCarta *atual2 = temp[i];
        tCarta *apagar;
        while (atual1 != NULL)
        {
            apagar = atual1;
            atual1 = atual1->prox;
            free(apagar);
        }
        while (atual2 != NULL)
        {
            apagar = atual2;
            atual2 = atual2->prox;
            free(apagar);
        }
    }
}

void moveNaipeTemp()
{
    int posNaipe, posTemp;
    printf("digite a posicao pilha naipe (0-3): ");
    scanf("%d", &posNaipe);
    printf("digite a posicao temp(0-3): ");
    scanf("%d", &posTemp);
    if (temp[posTemp] == NULL)
    { // verificando se o temp esta vazio
        if (((posNaipe >= 0) && (posNaipe <= 3) && (primNaipe[posNaipe] != NULL)) && ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] == NULL)))
        { // Verifica se é um movimento valido
            if (primNaipe[posNaipe] != NULL)
            { // verificando se o naipe ta vazio
                if (primNaipe[posNaipe]->prox == NULL)
                {
                    temp[posTemp] = primNaipe[posNaipe];
                    primNaipe[posNaipe] = NULL;
                    temp[posTemp]->prox = NULL;
                }
                else
                {
                    temp[posTemp] = primNaipe[posNaipe];
                    primNaipe[posNaipe] = primNaipe[posNaipe]->prox;
                    temp[posTemp]->prox = NULL; // desconecta da cadeia do naipe
                }
            }
            else
            {
                printf("Movimento invalido pois Naipe esta vazio");
            }
        }
        else
        {
            printf("Movimento invalido!");
        }
    }
    else
    {
        printf("Posição invalida pois o Temp esta cheio");
    }
}

void moveTempNaipe()
{
    tCarta *aux;
    int posNaipe, posTemp;
    printf("Posicao Temp (0-3): ");
    scanf("%d", &posTemp);
    printf("Posicao Naipe (0-3): ");
    scanf("%d", &posNaipe);
    if ((posTemp >= 0) && (posTemp <= 3) && (posNaipe >= 0) && (posNaipe <= 3) && temp[posTemp] != NULL)
    {
        if (primNaipe[posNaipe] == NULL && temp[posTemp]->num == 1)
        {
            primNaipe[posNaipe] = temp[posTemp];
            primNaipe[posNaipe]->prox = NULL;
            temp[posTemp] = NULL;
        }
        else if (primNaipe[posNaipe] != NULL && temp[posTemp]->naipe == primNaipe[posNaipe]->naipe && temp[posTemp]->num == primNaipe[posNaipe]->num + 1)
        {
            aux = primNaipe[posNaipe];
            primNaipe[posNaipe] = temp[posTemp];
            primNaipe[posNaipe]->prox = aux;
            temp[posTemp] = NULL;
        }
        else
        {
            printf("Movimento invalido \n");
        }
    }
    else
    {
        printf("A posição selecionada é invalida \n");
    }
}

void moveNaipeMesa()
{
    tCarta *antMesa, *atualMesa, *antNaipe, *atualNaipe;
    int posNaipe, posMesa;
    printf("Posicao Naipe (0-3): ");
    scanf("%d", &posNaipe);
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posNaipe >= 0) && (posNaipe <= 3) && (primNaipe[posNaipe] != NULL) && ((posMesa >= 0) && (posMesa <= 7)))
    { // Verificando se a posição selecionada é valida
        // Ponteiros auxiliares do Naipe
        atualNaipe = primNaipe[posNaipe];
        antNaipe = NULL; // Caso haja 1 elemento no naipe
        while (atualNaipe->prox != NULL)
        {
            antNaipe = atualNaipe;
            atualNaipe = atualNaipe->prox; // Ultimo elemento
        }
        // Ponteiros auxiliares da Mesa
        atualMesa = primMesa[posMesa];
        antMesa = NULL; // Caso haja 1 elemento na mesa
        while ((primMesa[posMesa] != NULL) && (atualMesa->prox != NULL))
        {
            antMesa = atualMesa;
            atualMesa = atualMesa->prox;
        }
        bool moveValido = false;
        if (primMesa[posMesa] == NULL)
        {
            moveValido = true; // coluna vazia aceita qualquer carta
        }
        else if (((((atualMesa->naipe == 3) || (atualMesa->naipe == 4)) && ((atualNaipe->naipe == 5) || (atualNaipe->naipe == 6))) || (((atualMesa->naipe == 5) || (atualMesa->naipe == 6)) && ((atualNaipe->naipe == 3) || (atualNaipe->naipe == 4)))) && (atualMesa->num > atualNaipe->num))
        {
            moveValido = true;
        }
        if (moveValido)
        {
            if (primMesa[posMesa] == NULL)
            {
                primMesa[posMesa] = atualNaipe;
            }
            else
            {
                atualMesa->prox = atualNaipe;
            }
            atualNaipe->prox = NULL;
            if (antNaipe == NULL)
            {
                primNaipe[posNaipe] = NULL;
            }
            else
            {
                antNaipe->prox = NULL;
            }
        }
        else
        {
            printf("Movimento invalido \n");
        }
    }
    else
    {
        printf("Movimento invalido \n");
    }
}

int contaCarta(int inicial)
{
    int i = 0;
    tCarta *aux = primMesa[inicial];
    while (aux != NULL)
    {
        aux = aux->prox;
        i++;
    }
    return i;
}

int verificaFila(tCarta *aux1)
{
    tCarta *prox;
    while (aux1->prox != NULL)
    {
        prox = aux1->prox;
        if ((aux1->num == prox->num + 1) &&
            (((((aux1->naipe == 3) || (aux1->naipe == 4)) && ((prox->naipe == 5) || (prox->naipe == 6))) || (((aux1->naipe == 5) || (aux1->naipe == 6)) && ((prox->naipe == 3) || (prox->naipe == 4))))))
        {
            aux1 = aux1->prox;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void moveMesaMesa()
{
    int final, inicial, i, quant = 0;
    tCarta *auxI, *apaga, *auxF;
    printf("Digite de qual mesa as cartas serao retiradas (0-7): ");
    scanf("%d", &inicial);
    printf("Digite para qual mesa as cartas irao (0-7): ");
    scanf("%d", &final);
    printf("Digite a quantidade de cartas que serao movimentadas (1-7): ");
    scanf("%d", &quant);
    if (((inicial >= 0) && (inicial < 8)) && ((final >= 0) && (final < 8)) && (primMesa[inicial] != NULL) && (quant >= 1))
    { // Verifica os parametros passado
        if (primMesa[final] == NULL)
        {
            auxI = primMesa[inicial];
            if (quant <= contaCarta(inicial))
            {
                for (i = 0; i < contaCarta(inicial) - quant; i++)
                {
                    auxI = auxI->prox;
                }
                if (verificaFila(auxI) == 1)
                {
                    primMesa[final] = auxI;
                    if (auxI == primMesa[inicial])
                    {
                        primMesa[inicial] = NULL;
                    }
                    else
                    {
                        apaga = primMesa[inicial];
                        while (apaga->prox != auxI)
                        {
                            apaga = apaga->prox;
                        }
                        apaga->prox = NULL;
                    }
                }
                else
                {
                    printf("A sequencia de cartas nao pode ser movida \n");
                }
            }
            else
            {
                printf("A sequencia de cartas nao pode ser movida \n");
            }
        }
        else
        {
            auxI = primMesa[inicial];
            auxF = primMesa[final];
            while (auxF->prox != NULL)
            {
                auxF = auxF->prox;
            }
            if (quant <= contaCarta(inicial))
            {
                for (i = 0; i < contaCarta(inicial) - quant; i++)
                {
                    auxI = auxI->prox;
                }
                if (verificaFila(auxI) == 1)
                {
                    if ((auxF->num > auxI->num) && (((((auxF->naipe == 3) || (auxF->naipe == 4)) && ((auxI->naipe == 5) || (auxI->naipe == 6))) || (((auxF->naipe == 5) || (auxF->naipe == 6)) && ((auxI->naipe == 3) || (auxI->naipe == 4))))))
                    {
                        auxF->prox = auxI;
                        if (auxI == primMesa[inicial])
                        {
                            primMesa[inicial] = NULL;
                        }
                        else
                        {
                            apaga = primMesa[inicial];
                            while (apaga->prox != auxI)
                            {
                                apaga = apaga->prox;
                            }
                            apaga->prox = NULL;
                        }
                    }
                    else
                    {
                        printf("A sequencia de cartas nao pode ser movida \n");
                    }
                }
                else
                {
                    printf("A sequencia de cartas nao pode ser movida \n");
                }
            }
            else
            {
                printf("A sequencia de cartas nao pode ser movida \n");
            }
        }
    }
    else
    {
        printf("O movimento nao pode ser realizado \n");
    }
}

int main(int argc, char **argv)
{
    int op = 0;
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(NULL));
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();
    while (op != 8)
    {
        imprime();
        printf("(1) Move Mesa-Naipe \n");
        printf("(2) Move Mesa-Temp \n");
        printf("(3) Move Temp-Mesa \n");
        printf("(4) Move Naipe-Temp \n");
        printf("(5) Move Temp-Naipe \n");
        printf("(6) Move Naipe-Mesa \n");
        printf("(7) Move Mesa-Mesa \n");
        printf("(8) Sair \n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        case 1:
            moveMesaNaipe();
            break;
        case 2:
            moveMesaTemp();
            break;
        case 3:
            moveTempMesa();
            break;
        case 4:
            moveNaipeTemp();
            break;
        case 5:
            moveTempNaipe();
            break;
        case 6:
            moveNaipeMesa();
            break;
        case 7:
            moveMesaMesa();
            break;
        default:
            printf(" FIM DE JOGO \n");
            break;
        }
    }
    destroiPilha();
    return 0;
=======
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct noCarta
{
    short num;
    char naipe;
    struct noCarta *prox;
} tCarta; // struct de carta

const char *naipeStr(char naipe)
{
    switch (naipe)
    {
    case 3:
        return "\xe2\x99\xa5"; // ♥
    case 4:
        return "\xe2\x99\xa6"; // ♦
    case 5:
        return "\xe2\x99\xa3"; // ♣
    case 6:
        return "\xe2\x99\xa0"; // ♠
    default:
        return "?";
    }
}

tCarta *primMesa[8];
tCarta *primNaipe[4];
tCarta *temp[4];
tCarta *primMonte = NULL;

void gerarBaralho()
{
    int i, j;
    tCarta *ult;
    for (i = 3; i < 7; i++)
    {
        for (j = 1; j < 14; j++)
        {
            if (primMonte == NULL)
            {                                                 // Verificando se a carta a ser gerada é a primeira do monte
                primMonte = (tCarta *)malloc(sizeof(tCarta)); // Gerando a primeira carta do monte
                ult = primMonte;
            }
            else
            {
                ult->prox = (tCarta *)malloc(sizeof(tCarta)); // Gerando as outras cartas do baralho e ajustando os ponteiros para apontar para a proxima carta do monte
                ult = ult->prox;
            }
            ult->naipe = i;   // Ajustando o naipe da carta gerada
            ult->num = j;     // Ajustando o número da carta gerada
            ult->prox = NULL; // Ajustando o ponteiro da ultima carta para nulo
        }
    }
}

void embaralhaBaralho()
{
    int i, j, sort;
    tCarta *atual, *ant;
    for (i = 0; i < 26; i++)
    {                       // Realizar o processo de embaralhar 26 vezes (metade de 52)
        sort = rand() % 52; // Sorteando uma carta para ser embaralhada
        ant = NULL;
        atual = primMonte;
        for (j = 0; j < sort; j++)
        { // Selecionando a carta a ser embaralhada
            ant = atual;
            atual = atual->prox;
        }
        if (sort > 0)
        { // Alterando o ponteiro do prox para "mudar a carta de lugar"
            ant->prox = atual->prox;
            atual->prox = primMonte; // Coloca a primeira carta do balho no lugar da carta sorteada
            primMonte = atual;       // Coloca a carta sorteada no lugar da primeira carta do baralho
        }
    }
}

void distribuirMesa()
{
    int i = 0;
    tCarta *auxMonte, *auxMesa;
    while (primMonte != NULL)
    {                                // Loop para percorer o baralho inteiro
        auxMonte = primMonte;        // Ajustando os ponteiros auxiliares
        primMonte = primMonte->prox; // Atualizando o monte apos a carta ter sido movida do monte
        if (primMesa[i] == NULL)
        {                             // Verificando se a primeira posição da mesa está vazia
            primMesa[i] = auxMonte;   // Passando a carta para a primeira posição da mesa
            primMesa[i]->prox = NULL; // Atualizando que a primeira carta vai apontar para nulo pois as outras cartas da pilha vao apontar para ela posteriormente
        }
        else
        {
            auxMesa = primMesa[i];       // Ponteiro auxiliar recebendo a ultima carta que foi adicionada na mesa
            primMesa[i] = auxMonte;      // Recebendo a proxima carta do monte
            primMesa[i]->prox = auxMesa; // Atualizando o ponteiro da carta na mesa para apontar para a ultima carta que foi adicionada
        }
        if (primMonte == NULL)
        {
            break;
        }
        i = (i + 1) % 8; // O inteiro i vai variar de 0 ate 7
    }
}

void imprime()
{
    int i;
    tCarta *atual;
    printf("[TEMP]= ");
    for (i = 0; i < 4; i++)
    {
        if (temp[i] != NULL)
        { // Como todos os espaços do temp foram iniciados como NULL, se tiver alguma carta no temp ele vai printar a carta se não ele vai printar um espaço em branco
            printf("%d-[%02d|%s] ", i, temp[i]->num, naipeStr(temp[i]->naipe));
        }
        else
        {
            printf("%d-[    ] ", i); // Printando um espaço vazio caso não tenha nenhuma carta no temp
        }
    }
    printf("\n\n");
    for (i = 0; i < 4; i++)
    {                         // For para realizar o print das 4 posições do naipe
        atual = primNaipe[i]; // Utilizando um ponteiro auxiliar para trabalhar com o primNaipe
        printf("[NAIPE %d]=", i);
        while (atual != NULL)
        { // Como todos os espaços do naipe foram iniciados como NULL, se tiver alguma carta no naipe ele vai printar a carta se não ele vai printar um espaço vazio ate enviarem uma carta para o naipe
            printf("[%02d|%s]", atual->num, naipeStr(atual->naipe));
            atual = atual->prox; // Ajustando o ponteiro para apontar para o proximo espaço vazio do primNaipe[i]
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < 8; i++)
    {                        // For para realizar o print das 8 posições da mesa
        atual = primMesa[i]; // Utilizando um ponteiro auxiliar para trabalhar com o primMesa
        printf("[MESA %d]=", i);
        while (atual != NULL)
        { // Como todos os espaços da mesa foram iniciados como NULL, se tiver alguma carta na mesa ele vai printar a carta se não ele vai printar um espaço vazio, porém apos a funcao
          // distribuirMesa for chamada ele vai printar 7 cartas nas posições 0,1,2,3 da mesa e 6 cartas nas posições 4,5,6,7
            printf("[%02d|%s]", atual->num, naipeStr(atual->naipe));
            atual = atual->prox; // Ajustando o ponteiro para apontar para o proximo espaço vazio do primMesa[i]
        }
        printf("\n");
    }
    printf("\n");
}

void moveMesaTemp()
{
    int posMesa, posTemp;
    tCarta *ant, *atual;
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posMesa >= 0) && (posMesa <= 7) && (primMesa[posMesa] != NULL))
    {                                   // Verificando se a posição selecionada é valida
        printf("Posicao Temp (0-3): "); // Selecionando a posição da temp para onde a carta selecionada vai
        scanf("%d", &posTemp);
        ant = NULL;                // Ajustando os ponteiros auxiliares
        atual = primMesa[posMesa]; // Ajustando os ponteiros auxiliares
        while (atual->prox != NULL)
        { // Selecionando a carta a ser movida
            ant = atual;
            atual = atual->prox;
        }
        if ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] == NULL))
        { // Verificando se a posição da temp selecionada é valida
            if (ant == NULL)
            {
                primMesa[posMesa] = NULL;
            }
            else
            {
                ant->prox = NULL;
            }
            temp[posTemp] = atual; // Passando a carta selecionada para a posição selecionada na temp
        }
        else
        {
            printf(" Nao é possivel mover a carta para o temp \n");
        }
    }
    else
    {
        printf(" Pilha e invalida ou esta vazia \n");
    }
}

void moveTempMesa()
{
    int posTemp, posMesa;
    tCarta *atual;
    printf("Posicao Temp (0-3): "); // Selecionando a posição da temp onde a carta está armazenada, para move-la para a mesa
    scanf("%d", &posTemp);
    if ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] != NULL))
    {                                         // Verificando se a posição da temp selecionada é valida
        printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa para onde a carta, selecionada na temp, vai ser enviada
        scanf("%d", &posMesa);
        if ((posMesa >= 0) && (posMesa <= 7))
        { // Verificando se a posição da mesa selecionada é valida
            if (primMesa[posMesa] == NULL)
            {                                      // Verificando se a pilha da mesa selecionada está vazia, se estiver ele vai passar a carta sem fazer a verificação de numero e naipe
                primMesa[posMesa] = temp[posTemp]; // Passando a carta selecionada da temp para a mesa na pilha selecionada anteriormente
                temp[posTemp] = NULL;              // Atualizando a posição da temp selecionada apos a carta ter sido retirada
            }
            else
            {
                atual = primMesa[posMesa]; // Ajustando o ponteiro auxiliar
                while (atual->prox != NULL)
                {
                    atual = atual->prox; // Buscando a posição livre dentro da pilha selecionada na mesa
                }
                if (atual->num - 1 == temp[posTemp]->num)
                {                                // Verificando se a jogada pode ser efetuada(verificando se o numero da carta que sai da temp pode ser posto na pilha (um exemplo de jogada que nao pode ocorrer e colocar uma carta de numero 4 em cima de uma carta de numero 2)
                    atual->prox = temp[posTemp]; // Passando a carta da temp para a posicao livre na pilha selecionada
                    temp[posTemp] = NULL;        // Atualizando a temp para vazia apos a carta ter sido movida
                }
                else
                {
                    printf(" Nao é possivel mover temp para mesa \n");
                }
            }
        }
        else
        {
            printf(" Nao é possivel mover temp para mesa \n");
        }
    }
    else
    {
        printf(" Temp está vazio \n");
    }
}

void moveMesaNaipe()
{
    int posMesa, posNaipe;
    tCarta *ant, *atual, *aux;
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posMesa >= 0) && (posMesa <= 7) && (primMesa[posMesa] != NULL))
    {                                    // Verificando se a posição selecionada é valida
        printf("Posicao Naipe (0-3): "); // Selecionando a posição do naipe para onde a carta selecionada vai
        scanf("%d", &posNaipe);
        ant = NULL;                // Ajustando o ponteiro auxiliar
        atual = primMesa[posMesa]; // Ajustando o ponteiro auxiliar
        while ((atual->prox != NULL) && (primMesa[posMesa] != NULL))
        { // Selecionando a carta que vai ser movida
            ant = atual;
            atual = atual->prox;
        }
        if ((posNaipe >= 0) && (posNaipe <= 3) && (((atual->num == 1) && (primNaipe[posNaipe] == NULL)) || ((primNaipe[posNaipe] != NULL) && (atual->naipe == primNaipe[posNaipe]->naipe) && (atual->num - 1 == primNaipe[posNaipe]->num))))
        {
            // Verificando se a jogada pode ser efetuada(esta verificando se é a primeira carta a ser adicionada, verificando se a primeira carta a ser adicionada é o numero 1, verificando se as proximas cartas a serem adicionadas são do mesmo naipe e se estão na ordem numerica)
            if (ant == NULL)
            {
                primMesa[posMesa] = NULL;
            }
            else
            {
                ant->prox = NULL;
            }
            if (primNaipe[posNaipe] == NULL)
            { // Verificando se a posição selecionada do naipe está vazia (Primeira carta a ser adicionada no naipe)
                primNaipe[posNaipe] = atual;
            }
            else
            {
                aux = primNaipe[posNaipe]; // Caso ja tenha uma carta na posição selecionada, ele adiciona a proxima carta e atualiza o ponteiro para que a carta que está sendo adicionada aponte para a carta anterior
                primNaipe[posNaipe] = atual;
                primNaipe[posNaipe]->prox = aux;
            }
        }
        else
        {
            printf(" Nao é possivel mover a carta selecionada para naipe \n");
        }
    }
    else
    {
        printf(" Pilha invalida ou vazia \n");
    }
}

void destroiPilha()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        tCarta *atual = primMesa[i];
        tCarta *apaga;
        while (atual != NULL)
        {
            apaga = atual;
            atual = atual->prox;
            free(apaga);
        }
    }
    for (i = 0; i < 4; i++)
    {
        tCarta *atual1 = primNaipe[i];
        tCarta *atual2 = temp[i];
        tCarta *apagar;
        while (atual1 != NULL)
        {
            apagar = atual1;
            atual1 = atual1->prox;
            free(apagar);
        }
        while (atual2 != NULL)
        {
            apagar = atual2;
            atual2 = atual2->prox;
            free(apagar);
        }
    }
}

void moveNaipeTemp()
{
    int posNaipe, posTemp;
    printf("digite a posicao pilha naipe (0-3): ");
    scanf("%d", &posNaipe);
    printf("digite a posicao temp(0-3): ");
    scanf("%d", &posTemp);
    if (temp[posTemp] == NULL)
    { // verificando se o temp esta vazio
        if (((posNaipe >= 0) && (posNaipe <= 3) && (primNaipe[posNaipe] != NULL)) && ((posTemp >= 0) && (posTemp <= 3) && (temp[posTemp] == NULL)))
        { // Verifica se é um movimento valido
            if (primNaipe[posNaipe] != NULL)
            { // verificando se o naipe ta vazio
                if (primNaipe[posNaipe]->prox == NULL)
                {
                    temp[posTemp] = primNaipe[posNaipe];
                    primNaipe[posNaipe] = NULL;
                    temp[posTemp]->prox = NULL;
                }
                else
                {
                    temp[posTemp] = primNaipe[posNaipe];
                    primNaipe[posNaipe] = primNaipe[posNaipe]->prox;
                    temp[posTemp]->prox = NULL; // desconecta da cadeia do naipe
                }
            }
            else
            {
                printf("Movimento invalido pois Naipe esta vazio");
            }
        }
        else
        {
            printf("Movimento invalido!");
        }
    }
    else
    {
        printf("Posição invalida pois o Temp esta cheio");
    }
}

void moveTempNaipe()
{
    tCarta *aux;
    int posNaipe, posTemp;
    printf("Posicao Temp (0-3): ");
    scanf("%d", &posTemp);
    printf("Posicao Naipe (0-3): ");
    scanf("%d", &posNaipe);
    if ((posTemp >= 0) && (posTemp <= 3) && (posNaipe >= 0) && (posNaipe <= 3) && temp[posTemp] != NULL)
    {
        if (primNaipe[posNaipe] == NULL && temp[posTemp]->num == 1)
        {
            primNaipe[posNaipe] = temp[posTemp];
            primNaipe[posNaipe]->prox = NULL;
            temp[posTemp] = NULL;
        }
        else if (primNaipe[posNaipe] != NULL && temp[posTemp]->naipe == primNaipe[posNaipe]->naipe && temp[posTemp]->num == primNaipe[posNaipe]->num + 1)
        {
            aux = primNaipe[posNaipe];
            primNaipe[posNaipe] = temp[posTemp];
            primNaipe[posNaipe]->prox = aux;
            temp[posTemp] = NULL;
        }
        else
        {
            printf("Movimento invalido \n");
        }
    }
    else
    {
        printf("A posição selecionada é invalida \n");
    }
}

void moveNaipeMesa()
{
    tCarta *antMesa, *atualMesa, *antNaipe, *atualNaipe;
    int posNaipe, posMesa;
    printf("Posicao Naipe (0-3): ");
    scanf("%d", &posNaipe);
    printf("Posicao Pilha Mesa (0-7): "); // Selecionando a posição da mesa a ser movida(no caso a ultima carta dessa mesa vai ser movida)
    scanf("%d", &posMesa);
    if ((posNaipe >= 0) && (posNaipe <= 3) && (primNaipe[posNaipe] != NULL) && ((posMesa >= 0) && (posMesa <= 7)))
    { // Verificando se a posição selecionada é valida
        // Ponteiros auxiliares do Naipe
        atualNaipe = primNaipe[posNaipe];
        antNaipe = NULL; // Caso haja 1 elemento no naipe
        while (atualNaipe->prox != NULL)
        {
            antNaipe = atualNaipe;
            atualNaipe = atualNaipe->prox; // Ultimo elemento
        }
        // Ponteiros auxiliares da Mesa
        atualMesa = primMesa[posMesa];
        antMesa = NULL; // Caso haja 1 elemento na mesa
        while ((primMesa[posMesa] != NULL) && (atualMesa->prox != NULL))
        {
            antMesa = atualMesa;
            atualMesa = atualMesa->prox;
        }
        bool moveValido = false;
        if (primMesa[posMesa] == NULL)
        {
            moveValido = true; // coluna vazia aceita qualquer carta
        }
        else if (((((atualMesa->naipe == 3) || (atualMesa->naipe == 4)) && ((atualNaipe->naipe == 5) || (atualNaipe->naipe == 6))) || (((atualMesa->naipe == 5) || (atualMesa->naipe == 6)) && ((atualNaipe->naipe == 3) || (atualNaipe->naipe == 4)))) && (atualMesa->num > atualNaipe->num))
        {
            moveValido = true;
        }
        if (moveValido)
        {
            if (primMesa[posMesa] == NULL)
            {
                primMesa[posMesa] = atualNaipe;
            }
            else
            {
                atualMesa->prox = atualNaipe;
            }
            atualNaipe->prox = NULL;
            if (antNaipe == NULL)
            {
                primNaipe[posNaipe] = NULL;
            }
            else
            {
                antNaipe->prox = NULL;
            }
        }
        else
        {
            printf("Movimento invalido \n");
        }
    }
    else
    {
        printf("Movimento invalido \n");
    }
}

int contaCarta(int inicial)
{
    int i = 0;
    tCarta *aux = primMesa[inicial];
    while (aux != NULL)
    {
        aux = aux->prox;
        i++;
    }
    return i;
}

int verificaFila(tCarta *aux1)
{
    tCarta *prox;
    while (aux1->prox != NULL)
    {
        prox = aux1->prox;
        if ((aux1->num == prox->num + 1) &&
            (((((aux1->naipe == 3) || (aux1->naipe == 4)) && ((prox->naipe == 5) || (prox->naipe == 6))) || (((aux1->naipe == 5) || (aux1->naipe == 6)) && ((prox->naipe == 3) || (prox->naipe == 4))))))
        {
            aux1 = aux1->prox;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void moveMesaMesa()
{
    int final, inicial, i, quant = 0;
    tCarta *auxI, *apaga, *auxF;
    printf("Digite de qual mesa as cartas serao retiradas (0-7): ");
    scanf("%d", &inicial);
    printf("Digite para qual mesa as cartas irao (0-7): ");
    scanf("%d", &final);
    printf("Digite a quantidade de cartas que serao movimentadas (1-7): ");
    scanf("%d", &quant);
    if (((inicial >= 0) && (inicial < 8)) && ((final >= 0) && (final < 8)) && (primMesa[inicial] != NULL) && (quant >= 1))
    { // Verifica os parametros passado
        if (primMesa[final] == NULL)
        {
            auxI = primMesa[inicial];
            if (quant <= contaCarta(inicial))
            {
                for (i = 0; i < contaCarta(inicial) - quant; i++)
                {
                    auxI = auxI->prox;
                }
                if (verificaFila(auxI) == 1)
                {
                    primMesa[final] = auxI;
                    if (auxI == primMesa[inicial])
                    {
                        primMesa[inicial] = NULL;
                    }
                    else
                    {
                        apaga = primMesa[inicial];
                        while (apaga->prox != auxI)
                        {
                            apaga = apaga->prox;
                        }
                        apaga->prox = NULL;
                    }
                }
                else
                {
                    printf("A sequencia de cartas nao pode ser movida \n");
                }
            }
            else
            {
                printf("A sequencia de cartas nao pode ser movida \n");
            }
        }
        else
        {
            auxI = primMesa[inicial];
            auxF = primMesa[final];
            while (auxF->prox != NULL)
            {
                auxF = auxF->prox;
            }
            if (quant <= contaCarta(inicial))
            {
                for (i = 0; i < contaCarta(inicial) - quant; i++)
                {
                    auxI = auxI->prox;
                }
                if (verificaFila(auxI) == 1)
                {
                    if ((auxF->num > auxI->num) && (((((auxF->naipe == 3) || (auxF->naipe == 4)) && ((auxI->naipe == 5) || (auxI->naipe == 6))) || (((auxF->naipe == 5) || (auxF->naipe == 6)) && ((auxI->naipe == 3) || (auxI->naipe == 4))))))
                    {
                        auxF->prox = auxI;
                        if (auxI == primMesa[inicial])
                        {
                            primMesa[inicial] = NULL;
                        }
                        else
                        {
                            apaga = primMesa[inicial];
                            while (apaga->prox != auxI)
                            {
                                apaga = apaga->prox;
                            }
                            apaga->prox = NULL;
                        }
                    }
                    else
                    {
                        printf("A sequencia de cartas nao pode ser movida \n");
                    }
                }
                else
                {
                    printf("A sequencia de cartas nao pode ser movida \n");
                }
            }
            else
            {
                printf("A sequencia de cartas nao pode ser movida \n");
            }
        }
    }
    else
    {
        printf("O movimento nao pode ser realizado \n");
    }
}

int main(int argc, char **argv)
{
    int op = 0;
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(NULL));
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();
    while (op != 8)
    {
        imprime();
        printf("(1) Move Mesa-Naipe \n");
        printf("(2) Move Mesa-Temp \n");
        printf("(3) Move Temp-Mesa \n");
        printf("(4) Move Naipe-Temp \n");
        printf("(5) Move Temp-Naipe \n");
        printf("(6) Move Naipe-Mesa \n");
        printf("(7) Move Mesa-Mesa \n");
        printf("(8) Sair \n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        case 1:
            moveMesaNaipe();
            break;
        case 2:
            moveMesaTemp();
            break;
        case 3:
            moveTempMesa();
            break;
        case 4:
            moveNaipeTemp();
            break;
        case 5:
            moveTempNaipe();
            break;
        case 6:
            moveNaipeMesa();
            break;
        case 7:
            moveMesaMesa();
            break;
        default:
            printf(" FIM DE JOGO \n");
            break;
        }
    }
    destroiPilha();
    return 0;
>>>>>>> 6d5b1d7b6c2eadb61d525533fac7c00f88e9e3a3
}