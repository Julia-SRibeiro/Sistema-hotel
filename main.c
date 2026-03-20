#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// STRUCTS
typedef struct {
    int codigo, quartosTotais, quartosDisponiveis;
    char nome[100], cidade[50];
    float diaria;
} Hotel;

typedef struct {
    char cliente[100], dataReserva[12], nomeHotel[100];
    int idHotel;
    float valorDiaria;
} Reserva;


// GLOBAL VARIABLES
FILE *arquivo_hoteis;
FILE *arquivo_reservas;
Hotel hotel, vet_hoteis[100];
Reserva reserva;


// FUNCTIONS
void cadastra_hotel() {
    // Cadastra Hotel
    printf("\n");

	printf("Codigo: ");
	scanf("%i", &hotel.codigo);
	while(getchar() != '\n');

	printf("Nome: ");
	gets(hotel.nome);

	printf("Cidade: ");
	gets(hotel.cidade);

	printf("Total de quartos: ");
	scanf("%i", &hotel.quartosTotais);
	while(getchar() != '\n');

	printf("Quartos disponiveis: ");
	scanf("%i", &hotel.quartosDisponiveis);
	while(getchar() != '\n');

	printf("Valor da diaria: ");
	scanf("%f", &hotel.diaria);
	while(getchar() != '\n');
	
	// Salva dados em hoteis.txt
    arquivo_hoteis = fopen("hoteis.txt", "a");
	if(arquivo_hoteis == NULL) {
		printf("Erro no arquivo!");
		return;
	}
	fprintf(arquivo_hoteis, "%i\t%s\t%s\t%i\t%i\t%.2f\n",
	        hotel.codigo,
	        hotel.nome,
	        hotel.cidade,
	        hotel.quartosTotais,
	        hotel.quartosDisponiveis,
	        hotel.diaria);
	fclose(arquivo_hoteis);
	
	printf("Hotel %s cadastrado!\n", hotel.nome);
}
int vet_hotel() {
    char linha[256];
    int nHoteis = 0;
    
    // Carrega todos os hotéis para a memória
    arquivo_hoteis = fopen("hoteis.txt", "r");
	if(arquivo_hoteis == NULL) {
		printf("Erro no arquivo!");
		return 0;
	}
    while (fgets(linha, sizeof(linha), arquivo_hoteis)) {
        sscanf(linha, "%i%s%s%i%i%f",
           &vet_hoteis[nHoteis].codigo,
           vet_hoteis[nHoteis].nome, 
           vet_hoteis[nHoteis].cidade,
           &vet_hoteis[nHoteis].quartosTotais, 
           &vet_hoteis[nHoteis].quartosDisponiveis,
           &vet_hoteis[nHoteis].diaria);
        nHoteis++;
    }
    fclose(arquivo_hoteis);
    return nHoteis;
}

void lista_hotel() {
	int nHoteis = vet_hotel();
	
	printf("%-6s | %-25s | %-20s | %s | %s | %s\n","ID","NOME",
	"CIDADE","QUANTIDADE DE QUARTOS","QUARTOS DISPONIVEIS","VALOR DA DIARIA");
    printf("-----------------------------------------------------------------\n");
    
	for (int i = 0; i < nHoteis; i++) {
        printf("%-6i | %-25s | %-20s | %-20i | %-20i | R$%-20.2f\n",
            vet_hoteis[i].codigo,
            vet_hoteis[i].nome,
            vet_hoteis[i].cidade,
            vet_hoteis[i].quartosTotais,
            vet_hoteis[i].quartosDisponiveis,
            vet_hoteis[i].diaria);
	}
}
void busca_nome() {
    char nome[100];
    int i, encontrado = -1, nHoteis = vet_hotel();
    
    printf("Insira o nome do hotel: ");
    gets(nome);
    
    for (i = 0; i < nHoteis; i++) {
        if ((strcmp(vet_hoteis[i].nome, nome)) == 0) {
            encontrado = i;
            
            printf("%i\t %s\t %s\t %i\t %i\t R$%.2f\n",
                vet_hoteis[i].codigo,
                vet_hoteis[i].nome,
                vet_hoteis[i].cidade,
                vet_hoteis[i].quartosTotais,
                vet_hoteis[i].quartosDisponiveis,
                vet_hoteis[i].diaria);
        }
    }
    if (encontrado == -1) {
        printf("Hotel nao encontrado.\n");
        return;
    }
}
void busca_cidade() {
    char cidade[100];
    int i, encontrado = -1, nHoteis = vet_hotel();
    
    printf("Insira a cidade de destino: ");
    gets(cidade);
    
    for (i = 0; i < nHoteis; i++) {
        if ((strcmp(vet_hoteis[i].cidade, cidade)) == 0) {
            encontrado = i;
            
            printf("%i\t %s\t %s\t %i\t %i\t R$%.2f\n",
                vet_hoteis[i].codigo,
                vet_hoteis[i].nome,
                vet_hoteis[i].cidade,
                vet_hoteis[i].quartosTotais,
                vet_hoteis[i].quartosDisponiveis,
                vet_hoteis[i].diaria);
        }
    }
    if (encontrado == -1) {
        printf("Hotel nao encontrado.\n");
        return;
    }
}
void busca_preco() {
    float preco1, preco2;
    int i, encontrado = -1, nHoteis = vet_hotel();
    
    printf("Insira o maior preco: ");
    scanf("%f", &preco1);
    printf("Insira o menor preco: ");
    scanf("%f", &preco2);
    while(getchar() != '\n');
    
    for (i = 0; i < nHoteis; i++) {
        if (vet_hoteis[i].diaria <= preco1 && vet_hoteis[i].diaria >= preco2) {
            encontrado = i;
            
            printf("%i\t %s\t %s\t %i\t %i\t R$%.2f\n",
                vet_hoteis[i].codigo,
                vet_hoteis[i].nome,
                vet_hoteis[i].cidade,
                vet_hoteis[i].quartosTotais,
                vet_hoteis[i].quartosDisponiveis,
                vet_hoteis[i].diaria);
        }
    }
    if (encontrado == -1) {
        printf("Nenhum hotel nessa faixa de preco\n");
        return;
    }
}
void busca() {
    int menu;
    
    do {
        printf("\nMENU\n");
        printf("1 - Listar todos hoteis\n");
        printf("2 - Buscar hotel por nome\n");
        printf("3 - Buscar hotel cidade\n");
        printf("4 - Buscar hotel por faixa de preco\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        while(getchar() != '\n');
        
        switch (menu) {
            case 1:
                lista_hotel();
                break;
            case 2:
                busca_nome();
                break;
            case 3:
                busca_cidade();
                break;
            case 4:
                busca_preco();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (menu != 0);
}

void reserva_quarto() {
    char nomeCliente[100];
    char dataReserva[12];
    int codigo, i, encontrado = -1, nHoteis = vet_hotel();
    
    // Solicita dados
    printf("\n");
    printf("Insira seu nome: ");
    gets(nomeCliente);
    
    printf("Data da reserva: ");
    gets(dataReserva);

    printf("Insira o codigo do hotel: ");
    scanf("%d", &codigo);
    while(getchar() != '\n');

    // Verifica existência e disponibilidade e realiza reserva
    for (i = 0; i < nHoteis; i++) {
        if (vet_hoteis[i].codigo == codigo) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Hotel nao encontrado.\n");
        return;
    } else if (vet_hoteis[encontrado].quartosDisponiveis <= 0) {
        printf("Desculpe, este hotel esta lotado.\n");
        return;
    } else {
        vet_hoteis[encontrado].quartosDisponiveis--;
    }

    // Reescreve arquivo hoteis.txt
    arquivo_hoteis = fopen("hoteis.txt", "w");
    if(arquivo_hoteis == NULL) {
		printf("Erro no arquivo!");
		return;
    }

    for (i = 0; i < nHoteis; i++) {
        fprintf(arquivo_hoteis, "%d\t%s\t%s\t%d\t%d\t%.2f\n",
                vet_hoteis[i].codigo,
                vet_hoteis[i].nome,
                vet_hoteis[i].cidade,
                vet_hoteis[i].quartosTotais,
                vet_hoteis[i].quartosDisponiveis,
                vet_hoteis[i].diaria);
    }
    fclose(arquivo_hoteis);

    // Salva no arquivo de reservas.txt
    arquivo_reservas = fopen("reservas.txt", "a");
    if(arquivo_reservas == NULL) {
		printf("Erro no arquivo!");
		return;
    }
    fprintf(arquivo_reservas, "%s\t%s\t%d\t%s\t%.2f\n",
            nomeCliente,
            dataReserva,
            vet_hoteis[encontrado].codigo, 
            vet_hoteis[encontrado].nome,
            vet_hoteis[encontrado].diaria);
    fclose(arquivo_reservas);

    printf("Reserva efetuada para %s em %s!\n", nomeCliente,dataReserva);
}

void relatorio_hotel() {
    int nHoteis = vet_hotel();

    printf("%-6s | %-25s | %-20s | %-12s\n", "ID", "NOME", "CIDADE", "STATUS");
    printf("-----------------------------------------------------------------\n");
    
	for (int i = 0; i < nHoteis; i++) {
        printf("%-6i | %-25s | %-20s | ",
            vet_hoteis[i].codigo,
            vet_hoteis[i].nome,
            vet_hoteis[i].cidade);
        if (quartosDisponiveis == 0) {
            printf("Lotado\n");
        } else {
            printf("Disponivel\n");
        }
	}
}
long converte_data(char *data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    return (ano * 10000) + (mes * 100) + dia;
}
void relatorio_reserva() {
    Reserva lista[100];
    char linha[256];
    int contador = 0;
    
    arquivo_reservas = fopen("reservas.txt", "r");
    if (arquivo_reservas == NULL) {
        printf("Nenhuma reserva encontrada.\n");
        return;
    }

    // Lê todas as reservas
    while (fgets(linha, sizeof(linha), arquivo_reservas)) {
        sscanf(linha, "%s%s%i%s%f",
               lista[contador].cliente,
               lista[contador].dataReserva,
               &lista[contador].idHotel,
               lista[contador].nomeHotel,
               &lista[contador].valorDiaria);
        contador++;
    }
    fclose(arquivo_reservas);

    // Bubble Sort para ordenação das datas
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            long data1 = converte_data(lista[j].dataReserva);
            long data2 = converte_data(lista[j+1].dataReserva);

            if (data1 > data2) {
                Reserva temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    // Exibe Relatório
    printf("\nTotal de reservas: %d\n", contador);
    printf("%-20s | %-12s | %-25s | %-10s\n", "CLIENTE", "DATA", "HOTEL", "VALOR");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("%-20s | %-12s | %-25s | R$ %-10.2f\n", 
           lista[i].cliente,
           lista[i].dataReserva,
           lista[i].nomeHotel,
           lista[i].valorDiaria);
    }
    
}
void relatorios() {
    int menu;
    
    do {
        printf("\nMENU\n");
        printf("1 - Relatorio de hoteis\n");
        printf("2 - Relatorio de reservas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        while(getchar() != '\n');
        
        switch (menu) {
            case 1:
                relatorio_hotel();
                break;
            case 2:
                relatorio_reserva();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (menu != 0);
}


// MAIN
int main() {
    int menu;

    do {
        printf("\nMENU\n");
        printf("1 - Cadastrar Hotel\n");
        printf("2 - Busca Hoteis\n");
        printf("3 - Reservar Quarto\n");
        printf("4 - Gerar Relatorios \n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);
        while(getchar() != '\n');

        switch (menu) {
            case 1:
                cadastra_hotel();
                break;
            case 2:
                busca();
                break;
            case 3:
                reserva_quarto();
                break;
            case 4:
                relatorios();
                break;
            case 0:
                printf("Sistema encerrado\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (menu != 0);

    return 0;
}