#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

unsigned int randaux() {
    static long seed = 1;
    return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

void GerarMapa(int mapa[TAMANHO][TAMANHO], int tamanho, int prob) {
    int i, j;
    for (i = 0; i < tamanho; i++)
        for (j = 0; j < tamanho; j++) {
            mapa[i][j] = 0;
            if (prob > 1 && randaux() % prob == 0)
                mapa[i][j] = 1;
        }
}

void Inicializar(int mapa[TAMANHO][TAMANHO], int *tamanho) {
    int semente, prob;
	// inicializar gerador de números aleatórios e ler probabilidade
    printf("Introduza (semente, probabilidade (1 em N), tamanho ate 10): ");
    scanf("%d %d %d", &semente, &prob, tamanho);
    while (semente-- > 0)
        randaux();
	
	// limitar tamanho permitido
    if (*tamanho > TAMANHO)
        *tamanho = TAMANHO;
    else if (*tamanho < 2)
        *tamanho = 2;
	
    GerarMapa(mapa, *tamanho, prob);
}

int Posicao(char* str, int tamanho) {
	 int linha, coluna;
	 // ler coordenada letra/número
	 coluna = str[0] - 'A';
	 if (coluna < 0 || coluna >= tamanho)
		return -1;
	 linha = atoi(str + 1);
	 if (linha<1 || linha>tamanho)
		return -1;
	 return (linha - 1) * tamanho + coluna;
}

/* Mostra o mapa de informação: 0 -> ?, 1 -> ., 2 -> ! */
void MostrarMapaInfo(int mapa[TAMANHO][TAMANHO], int tamanho) {
    int i, j;
    
    printf("\n ");
    for (j = 0; j < tamanho; j++)
        printf(" %c", 'A' + j);
    printf("\n");
    
    for (i = 0; i < tamanho; i++) {
        printf("%2d", i + 1);
        for (j = 0; j < tamanho; j++) {
            if (mapa[i][j] == 0)
                printf(" ?");  // Desconhecido
            else if (mapa[i][j] == 1)
                printf(" .");  // Seguro
            else
                printf(" !");  // Inseguro
        }
        printf("\n");
    }
}


void MostrarMapaPecas(int mapa[TAMANHO][TAMANHO], int tamanho) {
    int i, j;
    printf("\n ");
    for (j = 0; j < tamanho; j++)
        printf(" %c", 'A' + j);
    printf("\n");
    for (i = 0; i < tamanho; i++) {
        printf("%2d", i + 1);
        for (j = 0; j < tamanho; j++) {
            printf(" %c", mapa[i][j] == 1 ? '#' : '.');
        }
        printf("\n");
    }
}

// processar drones abatidos
int DroneAbatido(int mapaPecas[TAMANHO][TAMANHO], int tamanho, int pos) {
    int linha = pos / tamanho;
    int coluna = pos % tamanho;
    int i, j;
    for (i = linha - 1; i <= linha + 1; i++) {
        for (j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < tamanho && j >= 0 && j < tamanho) {
                if (mapaPecas[i][j] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

// contar drones , verificar 3 lançados
int ContarDrones(int drones[], int numDrones, int pos) {
    int count = 0;
    int i;
    for (i = 0; i < numDrones; i++) {
        if (drones[i] == pos)
            count++;
    }
    return count;
}

// verificar casas seguras
int TodasSeguras(int mapaInfo[TAMANHO][TAMANHO], int tamanho) {
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (mapaInfo[i][j] != 1)
                return 0;
        }
    }
    return 1;
}

// verificar balanço diario
int ProcessarDia(int mapaPecas[TAMANHO][TAMANHO], 
                 int mapaInfo[TAMANHO][TAMANHO],
                 int tamanho, int drones[], int numDrones) {
    int abatidos[TAMANHO];
    int d, i, j;
    int dronesAbatidos = 0;
    
    // Primeiro destruir peças onde há 3 drones
    for (d = 0; d < numDrones; d++) {
        int count = ContarDrones(drones, numDrones, drones[d]);
        if (count >= 3) {
            int linha = drones[d] / tamanho;
            int coluna = drones[d] % tamanho;
            mapaPecas[linha][coluna] = 0;
        }
    }
    
    // Verificar quais drones foram abatidos
    for (d = 0; d < numDrones; d++) {
        abatidos[d] = DroneAbatido(mapaPecas, tamanho, drones[d]);
        if (abatidos[d]) {
            printf("Drone %d abatido.\n", d + 1);
            dronesAbatidos++;
        }
    }
    
    // Processar drones abatidos
    for (d = 0; d < numDrones; d++) {
        if (abatidos[d]) {
            int linha = drones[d] / tamanho;
            int coluna = drones[d] % tamanho;
            for (i = linha - 1; i <= linha + 1; i++) {
                for (j = coluna - 1; j <= coluna + 1; j++) {
                    if (i >= 0 && i < tamanho && j >= 0 && j < tamanho) {
                        if (mapaInfo[i][j] == 0)
                            mapaInfo[i][j] = 2;
                    }
                }
            }
        }
    }
    
    // Processar drones não abatidos
    for (d = 0; d < numDrones; d++) {
        if (!abatidos[d]) {
            int linha = drones[d] / tamanho;
            int coluna = drones[d] % tamanho;
            for (i = linha - 1; i <= linha + 1; i++) {
                for (j = coluna - 1; j <= coluna + 1; j++) {
                    if (i >= 0 && i < tamanho && j >= 0 && j < tamanho) {
                        mapaInfo[i][j] = 1;
                    }
                }
            }
        }
    }
    
    // Marcar casas com 3 drones como seguras
    for (d = 0; d < numDrones; d++) {
        int count = ContarDrones(drones, numDrones, drones[d]);
        if (count >= 3) {
            int linha = drones[d] / tamanho;
            int coluna = drones[d] % tamanho;
            mapaInfo[linha][coluna] = 1;
        }
    }
    
    return dronesAbatidos;
}

int main() {
    int tamanho, numDronesIniciais, dronesDisponiveis;
    int mapaPecas[TAMANHO][TAMANHO];
    int mapaInfo[TAMANHO][TAMANHO];
    int drones[TAMANHO];
    int dia, i;
    char str[100];
    int semente, prob;
    
    // Ler dados iniciais com número de drones
    printf("Introduza (semente, probabilidade (1 em N), tamanho ate 10, numero de drones): ");
    scanf("%d %d %d %d", &semente, &prob, &tamanho, &numDronesIniciais);
    
    // Inicializar gerador
    while (semente-- > 0)
        randaux();
    
    // Limitar tamanho
    if (tamanho > TAMANHO)
        tamanho = TAMANHO;
    else if (tamanho < 2)
        tamanho = 2;
    
    GerarMapa(mapaPecas, tamanho, prob);
    GerarMapa(mapaInfo, tamanho, 0);
    
    dronesDisponiveis = numDronesIniciais;
    
    printf("\nMapa inicial de informacao:");
    MostrarMapaInfo(mapaInfo, tamanho);
    
    // Campanha de até 10 dias
    for (dia = 1; dia <= 10; dia++) {
        if (TodasSeguras(mapaInfo, tamanho)) {
            break;
        }
        
        printf("\nDia %d, lancar drones (#%d): ", dia, dronesDisponiveis);
        
        // Ler posições dos drones
        i = -1;
        do {
            i++;
            scanf("%s", str);
            drones[i] = Posicao(str, tamanho);
        } while (drones[i] >= 0 && i < TAMANHO - 1 && i < dronesDisponiveis - 1);
        
        // Se lemos exatamente o número de drones disponíveis
        if (drones[i] >= 0 && i == dronesDisponiveis - 1) {
            i++;
        }
        
        // Processar o dia
        int dronesAbatidos = ProcessarDia(mapaPecas, mapaInfo, tamanho, drones, i);
        
        // Mostrar mapa
        MostrarMapaInfo(mapaInfo, tamanho);
        
        // Atualizar drones disponíveis
        dronesDisponiveis = dronesDisponiveis - dronesAbatidos + 1;
    }
    
    printf("\nDuracao da campanha: %d dias\n", dia - 1);
    
    return 0;
}
