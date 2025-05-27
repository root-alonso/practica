/* Simulacion del juego Bingo! */ 
/* Elaborado por SeRdNaH */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 8
#define MAX_APUESTA 429496729
#define MAX_SEMILLA 429496729

int tirarDados(int [], int [], int);
int validaDados(int [], int const, int const);			
void imprimeMenu(void);
void imprimeSumasDados(int const [], int const);
void determinaSumaPremios(int const [], int const, int const);

int main() {
	
	unsigned int montoApuesta;
	
	int dados[SIZE] = {0};
	int semillas[SIZE] = {0};
	
	do {		
		printf("Ingrese su apuesta, por favor: ");
		scanf("%d", &montoApuesta);
		
		if (montoApuesta <= 0 || montoApuesta > MAX_APUESTA) {
			printf("\nMonto de apuesta no valido. Intentalo otra vez.\n\n");
			
		} else {	
			imprimeMenu();
		}
		
	} while (montoApuesta <= 0 || montoApuesta > MAX_APUESTA);
	
	tirarDados(dados, semillas, SIZE);
	determinaSumaPremios(dados, SIZE, montoApuesta);
	
	return 0;
}

void imprimeMenu(void)
{
	printf("\n*** Bienvenido al juego de Bingo! ***\n");
	printf("** Las reglas son las siguientes: **\n");
	printf("** 1. Los dados siempre se tiran en orden. **\n");
	printf("** 2. Los tiros (semillas) no pueden repetirse. **\n");
	printf("** 3. Si el tiro se repite (la semilla), no se podra tirar el dado. **\n");
	printf("** 4. Se podra tirar el dado hasta que sea un tiro (semilla) sin repetir. **\n");
}

int tirarDados(int cDados[], int cSemillas[], int size)
{
	int dado, validador;
	unsigned int semilla;
	
	for (dado = 0; dado <= size - 1; dado++) {
		
		do {	
			printf("\n\nIngresa un numero entre 0 y 429496729 para tirar el dado %d: ", dado + 1);
			scanf("%d", &semilla);
			
			srand(semilla);
			
			if (semilla < 0 || semilla > MAX_SEMILLA) {
				printf("\nSemilla ingresada no valida. Intentelo de nuevo.\n");
				
			} else {
				validador = validaDados(cSemillas, semilla, dado);
				
				if (validador == 0) {
					cDados[dado] = 1 + (rand () % 6);
					imprimeSumasDados(cDados, size);
					
				} else {
					printf("\nLa semilla introducida ya ha sido utilizada. Ingresa otra.\n");
				}
			}
			
		} while (semilla < 0 || semilla > MAX_SEMILLA || validador != 0);
	}
}

int validaDados(int cSemillas[], int const cSemilla, int const numeroDado)
{
	int dado, contador = 0;
	
	cSemillas[numeroDado] = cSemilla;
	
	if (numeroDado == 0) {
		return 0;
		
	} else {
		
		for (dado = numeroDado; dado >= 1; dado--) {
			
			if (cSemillas[numeroDado] == cSemillas[dado - 1]) {
				contador++;
			}
		}
	}
	
	if (contador == 0) {
		return 0;
		
	} else if (contador != 0) {
		return 1;
	}
}

void imprimeSumasDados(int const cDados[], int const size)
{
	int dado;
	int suma = 0;
	
	printf("\n");
	
	printf("Dado 1\tDado 2\tDato 3\tDado 4\tDado 5\tDado 6\tDado 7\tDado 8\n");
	
	for (dado = 0; dado <= size - 1; dado++) {
		
		printf(" [%d]\t", cDados[dado]);
		suma = suma + cDados[dado];
	}
	
	printf("\n\nLa suma actual es: %d\n", suma);
}

void determinaSumaPremios(int const cDados[], int const size, int const apuesta)
{
	int dado, sumaDados;
	long long premio;
	
	for (dado = 0; dado <= size - 1; dado++) {
		sumaDados += cDados[dado];
	}
	
	switch (sumaDados) {
		case 8:
			premio = apuesta * 4;
			printf("\nFelicidades!\nHa ganado su premio x4: %d", premio);
		break;
		case 15:
			premio = apuesta * 3;
			printf("\nFelicidades!\nHa ganado su premio x3: %d", premio);
		break;
		case 22:
			premio = apuesta * 3;
			printf("\nFelicidades!\nHa ganado su premio x3: %d", premio);
		break;
		case 29:
			premio = apuesta * 3;
			printf("\nFelicidades!\nHa ganado su premio x3: %d", premio);
		break;
		case 35:
			premio = apuesta * 2;
			printf("\nFelicidades!\nHa ganado su premio x2: %d", premio);
		break;
		case 42:
			premio = apuesta * 2;
			printf("\nFelicidades!\nHa ganado su premio x2: %d", premio);
		break;
		case 50:
			premio = apuesta * 2;
			printf("\nFelicidades!\nHa ganado su premio x2: %d", premio);
		break;
		case 56:
			premio = apuesta * 4;
			printf("\nFelicidades!\nHa ganado su premio x4: %d", premio);
		break;
		
		default:
			printf("\nLo sentimos, ha perdido.\n");
	}
}