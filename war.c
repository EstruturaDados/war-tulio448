// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TAM_STRING 100
#define MAX_TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numeroTropas;
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// limpaBufferEntrada()
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
struct Territorio * alocarMapa(){
    struct Territorio *territorios = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

    if(territorios == NULL){
        printf("Erro: Falha ao alocar memória.\n");
    }

    return territorios;
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(struct Territorio * territorios){
    printf("======================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("======================================\n\n");
    printf("Vamos cadastrar os %d territórios iniciais do nosso mundo...\n", MAX_TERRITORIOS);
    
    for(int i = 0; i < MAX_TERRITORIOS; i++){
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do território: ");
        fgets(territorios[i].nome, TAM_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        printf("Cor do exército (ex: Azul, Verde): ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        limpaBufferEntrada();
    }

    printf("\nCadastro inicial conluído com sucesso!\n\n");
};

void mockarTerritorios(struct Territorio * territorios){
    strcpy(territorios[0].nome,"América");
    strcpy(territorios[0].corExercito,"Azul");
    territorios[0].numeroTropas = 3;

    strcpy(territorios[1].nome,"Europa");
    strcpy(territorios[1].corExercito,"Verde");
    territorios[1].numeroTropas = 3;

    strcpy(territorios[2].nome,"Asia");
    strcpy(territorios[2].corExercito,"Vermelho");
    territorios[2].numeroTropas = 3;

    strcpy(territorios[3].nome,"África");
    strcpy(territorios[3].corExercito,"Branco");
    territorios[3].numeroTropas = 2;

    strcpy(territorios[4].nome,"Oceania");
    strcpy(territorios[4].corExercito,"Amarelo");
    territorios[4].numeroTropas = 2;
}
// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(const struct Territorio * territorios){
    printf("\n====================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n\n");

    for (int i = 0; i < MAX_TERRITORIOS; i++){
        printf("%d. %s, exército: %s, tropas: %d\n", i+1, territorios[i].nome, territorios[i].corExercito, territorios[i].numeroTropas);
    }
}

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
int* faseDeAtaque(const struct Territorio * territorios){
    int* retorno = (int*) malloc(2 * sizeof(int));

    do{
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha um território atacante (1 a 5): ");
        scanf("%d", &retorno[0]);
        limpaBufferEntrada();
        retorno[0]--;
        if(retorno[0] >= 0 && retorno[0] <= MAX_TERRITORIOS && territorios[retorno[0]].numeroTropas > 0)
            break;
        else
            printf("\nTerritório inválido!\n");
    }while(1==1);
    
    do{
        printf("Escolha um território defensor (1 a 5): ");
        scanf("%d", &retorno[1]);
        limpaBufferEntrada();
        retorno[1]--;
        if(retorno[1] >= 0 && retorno[1] <= MAX_TERRITORIOS && territorios[retorno[1]].numeroTropas > 0 && retorno[0] != retorno[1])
            break;
        else
            printf("\nTerritório inválido!\n");
    }while(1==1);

    return retorno;
}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(struct Territorio * territorios, int* dadosBatalha){
    int dadoAtaque = rand() % 5;
    int dadoDefesa = rand() % 5;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", territorios[dadosBatalha[0]].nome, dadoAtaque);
    printf("O defensor %s rolou um dado e tirou: %d\n", territorios[dadosBatalha[1]].nome, dadoDefesa);

    if(dadoAtaque > dadoDefesa){
        printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n\n");
        territorios[dadosBatalha[1]].numeroTropas--;
    }else if(dadoDefesa > dadoAtaque){
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n\n");
        territorios[dadosBatalha[0]].numeroTropas--;
    }else{
        printf("EMPATE! Nenhum território perde tropas.\n\n");
    }

    if(territorios[dadosBatalha[0]].numeroTropas == 0){
        printf("CONQUISTA! O território %s foi dominado pelo exército %s!\n\n",territorios[dadosBatalha[0]].nome,territorios[dadosBatalha[1]].corExercito);
        strcpy(territorios[dadosBatalha[0]].corExercito,territorios[dadosBatalha[1]].corExercito);
    }else if(territorios[dadosBatalha[1]].numeroTropas == 0){
        printf("CONQUISTA! O território %s foi dominado pelo exército %s!\n\n",territorios[dadosBatalha[1]].nome,territorios[dadosBatalha[0]].corExercito);
        strcpy(territorios[dadosBatalha[1]].corExercito,territorios[dadosBatalha[0]].corExercito);
    }
}

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.
int verificarVitoria(const struct Territorio * territorios, int territorioAlvo){
    if(territorios[territorioAlvo].numeroTropas == 0){
        printf("Você já cumpriu sua missão, pode sair do jogo.\n");
        return 1;
    }
    printf("Você ainda não cumpriu sua missão, continue a lutar!\n");
    return 0;
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(struct Territorio * territorios){
    printf("\nJogo encerrado e memória liberada, até a próxima!\n\n");
    free(territorios);
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
int exibirMenuPrincipal(){
    int opcao;

    do{
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar missão\n");
        printf("0 - Sair\n\n");
        printf("Escolha sua ação: ");
        scanf("%d", &opcao);
        limpaBufferEntrada();

        if(opcao >= 0 && opcao <= 2)
            break;

        printf("Opção inválida!");
    }while(1==1);

    return opcao;
}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
int sortearMissao(){
    return rand() % MAX_TERRITORIOS;
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
void exibirMissao(const struct Territorio * territorios, int territorioAlvo){
    printf("\n--- SUA MISSÃO ---\n");
    printf("Destruir o território %s\n", territorios[territorioAlvo].nome);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    struct Territorio *territorios = alocarMapa();

    //inicializarTerritorios(territorios);
    mockarTerritorios(territorios);
    int territorioAlvo = sortearMissao();

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    int opcao = exibirMenuPrincipal();
    int cumpriuMissao = 0;

    while(cumpriuMissao != 1){
        switch(opcao){
            case 0:
                cumpriuMissao = 1;
                break;
            case 1:
                cumpriuMissao = verificarVitoria(territorios,territorioAlvo);
                if(cumpriuMissao != 1){
                    exibirMapa(territorios);
                    exibirMissao(territorios,territorioAlvo);

                    int* indicesBatalha = faseDeAtaque(territorios);

                    simularAtaque(territorios,indicesBatalha);

                    printf("Pressione Enter para voltar ao menu de ações...\n");
                    char qualquer_coisa[TAM_STRING];
                    scanf("%[^\n]", qualquer_coisa);
                    limpaBufferEntrada();
                }
                break;
            case 2:
                exibirMissao(territorios,territorioAlvo);
                cumpriuMissao = verificarVitoria(territorios,territorioAlvo);
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
        }

        if(cumpriuMissao != 1)
            opcao = exibirMenuPrincipal();
    };

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    liberarMemoria(territorios);

    return 0;
}

