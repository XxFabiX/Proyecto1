#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Estructura de un guardián
struct Guardian {
    char nombre[50];
    char tipo[20];
    int PV;
    int PA;
    int PD;
};

// Estructura de un jugador
struct Jugador {
    int puntosVida;
    struct Guardian mano[3];
};

// Función para cargar datos desde un archivo
void cargarCartas(struct Guardian cartas[], int* numCartas){
    FILE* archivo = fopen("cartas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de cartas.\n");
        exit(1);
    }

    *numCartas = 0;
    while (*numCartas < 100 && fscanf(archivo, "%s %s %d %d %d",
        cartas[*numCartas].nombre, cartas[*numCartas].tipo, &cartas[*numCartas].PV, &cartas[*numCartas].PA, &cartas[*numCartas].PD) == 5) {
        (*numCartas)++;
    }
    fclose(archivo);
}

// Guardar Datos
void guardarCartas(struct Guardian cartas[], int numCartas){
    FILE* archivo = fopen("cartas.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de cartas.\n");
        exit(1);
    }
    int i;
    for (i = 0; i < numCartas; i++){
        fprintf(archivo, "%s %s %d %d %d\n", cartas[i].nombre, cartas[i].tipo, cartas[i].PV, cartas[i].PA, cartas[i].PD);
    }
    fclose(archivo);
}

// Función para crear una nueva carta
void crearCarta(struct Guardian cartas[], int* numCartas){
    if (*numCartas >= 100) {
        printf("No puedes agregar más cartas, has alcanzado el límite.\n");
        return;
    }

    struct Guardian nuevaCarta;
    printf("Ingrese el nombre de la carta: ");
    scanf("%s", nuevaCarta.nombre);
    printf("Ingrese el tipo de la carta (magos, vikingos, nigromantes o bestias): ");
    scanf("%s", nuevaCarta.tipo);
    printf("Ingrese los Puntos de Vida (PV): ");
    scanf("%d", &nuevaCarta.PV);
    printf("Ingrese los Puntos de Ataque (PA): ");
    scanf("%d", &nuevaCarta.PA);
    printf("Ingrese los Puntos de Defensa (PD): ");
    scanf("%d", &nuevaCarta.PD);

    cartas[*numCartas] = nuevaCarta;
    (*numCartas)++;

    guardarCartas(cartas, *numCartas);
}

// Función para mostrar las cartas existentes
void mostrarCartas(struct Guardian cartas[], int numCartas){
    printf("Cartas existentes:\n");
    int i;
    for (i = 0; i < numCartas; i++) {
        printf("Nombre: %s, Tipo: %s, PV: %d, PA: %d, PD: %d\n", cartas[i].nombre, cartas[i].tipo, cartas[i].PV, cartas[i].PA, cartas[i].PD);
    }
}

// Función para que la IA realice una acción
void accionIA(struct Jugador* jugador, struct Jugador* ia, struct Guardian cartas[], int numCartas, FILE* historial) {
    // La IA elige una carta al azar de su mano que no se haya utilizado antes
    int cartaIA;
    int cartasUtilizadas[3] = {0};  // Arreglo para rastrear las cartas utilizadas por la IA
    int cartasDerrotadas[3] = {0};  // Por el jugador

    do {
        cartaIA = rand() % 3;
    } while (cartasUtilizadas[cartaIA]);  // Evitar carta repetida

    // La IA elige un objetivo al azar del jugador
    int objetivo = rand() % 3;

    // Realizar el ataque
    int dano = ia->mano[cartaIA].PA - jugador->mano[objetivo].PD;
    if (dano > 0) {
        jugador->mano[objetivo].PV -= dano;
    }

    fprintf(historial, "La IA ataca con %s a %s. %s tiene %d PV restantes.\n", ia->mano[cartaIA].nombre, jugador->mano[objetivo].nombre, jugador->mano[objetivo].nombre, jugador->mano[objetivo].PV);

    // Mostrar el mensaje de ataque de la IA
    printf("La IA ataca con %s a %s. %s tiene %d PV restantes.\n", ia->mano[cartaIA].nombre, jugador->mano[objetivo].nombre, jugador->mano[objetivo].nombre, jugador->mano[objetivo].PV);

    // Si el objetivo se queda sin puntos de vida, se descarta la carta
    if (jugador->mano[objetivo].PV <= 0) {
        fprintf(historial, "%s ha sido derrotado.\n", jugador->mano[objetivo].nombre);
        // Descartar la carta del jugador
        jugador->mano[objetivo] = cartas[rand() % numCartas];
        // Restar un punto de vida al Jugador
        if (jugador->puntosVida > 0) {
            jugador->puntosVida -= 1;
        }
        // Marcar la carta como derrotada por el jugador
        cartasDerrotadas[objetivo] = 1;
    }
    int i;
    // Verificar si alguna carta de la IA ha sido derrotada por el jugador
    for (i = 0; i < 3; i++) {
        if (cartasDerrotadas[i]) {
            // Descartar la carta de la IA
            ia->mano[i] = cartas[rand() % numCartas];
            // Restar un punto de vida a la IA
            if (ia->puntosVida > 0) {
                ia->puntosVida -= 1;
            }
            fprintf(historial, "%s ha sido derrotado por el jugador.\n", ia->mano[i].nombre);
            cartasDerrotadas[i] = 0;  // Restablecer el estado de la carta derrotada
        }
    }

    // Marcar la carta como utilizada
    cartasUtilizadas[cartaIA] = 1;
}


// Función para iniciar una partida
void iniciarPartida(struct Guardian cartas[], int numCartas){
    struct Jugador jugador;
    struct Jugador ia;

    // Inicializar jugadores
    jugador.puntosVida = 5;
    ia.puntosVida = 5;
    int i;

    // Repartir cartas
    bool cartasUtilizadas[100] = {false}; // Arreglo para rastrear las cartas utilizadas
    for (i = 0; i < 3; i++) {
        do {
            int cartaJugador = rand() % numCartas;
            if (!cartasUtilizadas[cartaJugador]) {
                jugador.mano[i] = cartas[cartaJugador];
                cartasUtilizadas[cartaJugador] = true;
                break;
            }
        } while (1);

        do {
            int cartaIA = rand() % numCartas;
            if (!cartasUtilizadas[cartaIA]) {
                ia.mano[i] = cartas[cartaIA];
                cartasUtilizadas[cartaIA] = true;
                break;
            }
        } while (1);
    }

    // Bucle del juego
    int turno = 0;
    FILE* historial = fopen("historial.txt", "w");
    while (jugador.puntosVida > 0 && ia.puntosVida > 0) {
        printf("Estado actual:\n");
        printf("Jugador - PV: %d\n", jugador.puntosVida);
        printf("IA - PV: %d\n", ia.puntosVida);
        printf("Mano del jugador:\n");
        for (i = 0; i < 3; i++) {
            printf("%d. %s (PV: %d, PA: %d, PD: %d)\n", i + 1, jugador.mano[i].nombre, jugador.mano[i].PV, jugador.mano[i].PA, jugador.mano[i].PD);
        }

        printf("Turno de jugador %d\n", turno % 2 + 1);

        if (turno % 2 == 0) {
            // Turno del jugador
            int eleccion;
            printf("Seleccione una carta (1-3) o 0 para retirarse: ");
            scanf("%d", &eleccion);

            if (eleccion == 0) {
                printf("El jugador se retira de la partida.\n");
                fprintf(historial, "El jugador se retira de la partida.\n");
                break;
            }

            eleccion--; // Ajustar al índice del array

            // Validar la elección del jugador
            if (eleccion < 0 || eleccion >= 3 || jugador.mano[eleccion].PV <= 0) {
                printf("Selección no válida. Intente de nuevo.\n");
                continue;
            }

            // Turno de ataque del jugador
            int objetivo;
            printf("Seleccione un objetivo (1-3): ");
            scanf("%d", &objetivo);
            objetivo--; // Ajustar al índice del array

            // Validar la elección del objetivo
            if (objetivo < 0 || objetivo >= 3 || ia.mano[objetivo].PV <= 0) {
                printf("Selección no válida. Intente de nuevo.\n");
                continue;
            }

            // Realizar el ataque del jugador
            int dano = jugador.mano[eleccion].PA - ia.mano[objetivo].PD;
            if (dano > 0) {
                ia.mano[objetivo].PV -= dano;
            }

            printf("El jugador ataca con %s a %s. %s tiene %d PV restantes.\n", jugador.mano[eleccion].nombre, ia.mano[objetivo].nombre, ia.mano[objetivo].nombre, ia.mano[objetivo].PV);

            // Verificar si el objetivo era de la IA y ha sido derrotado
            if (ia.mano[objetivo].PV <= 0) {
                printf("%s ha sido derrotado por el jugador.\n", ia.mano[objetivo].nombre);
                fprintf(historial, "%s ha sido derrotado por el jugador.\n", ia.mano[objetivo].nombre);

                // Restar un punto de vida a la IA
                if (ia.puntosVida > 0) {
                    ia.puntosVida -= 1;
                }

                // Descartar la carta de la IA
                ia.mano[objetivo] = cartas[rand() % numCartas];
            }

            // Verificar si el objetivo del jugador ha sido derrotado
            if (jugador.mano[eleccion].PV <= 0) {
                printf("%s ha sido derrotado por la IA.\n", jugador.mano[eleccion].nombre);
                fprintf(historial, "%s ha sido derrotado por la IA.\n", jugador.mano[eleccion].nombre);

                // Restar un punto de vida al jugador
                if (jugador.puntosVida > 0) {
                    jugador.puntosVida -= 1;
                }

                // Descartar la carta del jugador
                do {
                    int cartaJugador = rand() % numCartas;
                    if (!cartasUtilizadas[cartaJugador]) {
                        jugador.mano[eleccion] = cartas[cartaJugador];
                        cartasUtilizadas[cartaJugador] = true;
                        break;
                    }
                } while (1);
            }
        } else {
            // Turno de la IA
            accionIA(&jugador, &ia, cartas, numCartas, historial);
        }

        turno++;
    }

    // Determinar el ganador
    if (jugador.puntosVida <= 0) {
        printf("¡La IA gana!\n");
        fprintf(historial, "¡La IA gana!\n");
    } else {
        printf("¡El jugador gana!\n");
        fprintf(historial, "¡El jugador gana!\n");
    }

    fclose(historial);
}


void mostrarHistorial() {
    FILE* historial = fopen("historial.txt", "r");
    if (historial == NULL) {
        printf("No hay registros en el historial.\n");
        return;
    }

    char linea[1000]; // Tamaño suficientemente grande para leer una línea completa del historial
    while (fgets(linea, sizeof(linea), historial) != NULL) {
        printf("%s", linea);
    }

    fclose(historial);

    // Abre el archivo de historial en modo escritura (borrará su contenido)
    historial = fopen("historial.txt", "w");
    if (historial == NULL) {
        printf("Error al borrar el historial.\n");
        return;
    }
    fclose(historial); // Cierra el archivo para borrar su contenido

    printf("El historial se ha limpiado.\n");
}

int main() {
    struct Guardian cartas[100];
    int numCartas = 0;
    int opcion;

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Cargar cartas desde un archivo al inicio
    cargarCartas(cartas, &numCartas);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Crear una nueva carta\n");
        printf("2. Comenzar el juego\n");
        printf("3. Mostrar las cartas existentes\n");
        printf("4. Mostrar historial\n"); // Nueva opción para mostrar el historial
        printf("5. Salir\n");
        printf("Ingrese su eleccion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearCarta(cartas, &numCartas);
                break;
            case 2:
                if (numCartas < 6) {
                    printf("Necesitas al menos 6 cartas para comenzar el juego.\n");
                } else {
                    iniciarPartida(cartas, numCartas);
                }
                break;
            case 3:
                mostrarCartas(cartas, numCartas);
                break;
            case 4:
                mostrarHistorial(); // Llama a la función para mostrar el historial
                break;
            case 5:
                // Salir del juego
                return 0;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

        // Consumir el carácter de nueva línea pendiente en el búfer
        while (getchar() != '\n');
    }

    return 0;
}

