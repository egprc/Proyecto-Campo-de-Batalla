#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Parametros.h"
#include <sys/wait.h>
/*#include "Atacar3.h"*/
#define max 1024

                         // Estructuras globales //
                        // -------------------- //

// Designar la estructura de una yarda del campo de batalla
struct yarda {
	int posX;  // Coordenada x de la yarda
	int posY;  // Coordenada y de la yarda
	int valor; // Valor que tiene la yarda, según sea OM, OC o sin interés
};

// Designar la estructura de una bomba que será lanzada
struct bomba {
	int posX;  // Coordenada x del objetivo
	int posY;  // Coordenada y del objetivo
	int R;     // Radio de alcance de la bomba
	int P;     // Potencia de la bomba
};

                          // Programa principal //
                         // ------------------ //
                        
int main(int argc, char *argv[])
{
    // Leer datos de entrada
    FILE *f; 
    int N;   // Dimensión del campo de batalla
    char linea[max];
    char *tok;
    int token;
    int T;   // Cantidad de objetivos (yardas)
    int B;   // Cantidad de bombas
    int i,j; // Iteradores
    char nombre_archivo[20];
    extern char* optarg;
    extern int optind;
    
    // Pasaje de parametros
    int procesos, hilos, cantidad;
    Parametros(&procesos,&hilos,&cantidad,argc,argv);
  
    struct yarda *yar = NULL;
    struct bomba *bom = NULL;
    
    for (i = optind; i < argc; i++) {
        if (strlen(argv[i]) >= sizeof(nombre_archivo)) {
            printf("Nombre de archivo muy grande:");
  	};
	strcpy(nombre_archivo,argv[i]);
    };
    
    f = fopen(nombre_archivo, "r");
    
    if (f == NULL) {
        printf("Error al abrir el archivo.");
    }

    // Caso en que no hay errores al abrir el archivo
    else { 
    
        // Leer la cabecera 
	fscanf(f,"%d\n",&N);
	fscanf(f,"%d\n",&T);

	
	// Reservar memoria para las yardas
	yar = malloc( T * sizeof(struct yarda));
	
 	// Error al reservar memoria
	if (yar == NULL) {
	    printf("No reservaste memoria para los blancos\n");
            exit(1);
	};
	
	// Lee las yardas
	int **listaYardas; 
    
        listaYardas = (int **) malloc(T * sizeof(int *)); 
        for (i=0; i<T; ++i)
            listaYardas[i] = (int *) malloc(3 *sizeof(int));
            
        for (i=0; i<T; ++i){
            fscanf(f,"%d %d %d \n", &yar[i].posX, &yar[i].posY, &yar[i].valor);
            listaYardas[i][0] = yar[i].posX;
            listaYardas[i][1] = yar[i].posY;
            listaYardas[i][2] = yar[i].valor;
        };
        free(yar);
        
	fscanf(f,"%d\n",&B);
	
	// Reservar memoria para las bombas
	bom = malloc( B * sizeof(struct bomba));
	
	// Error al reservar memoria
	if (bom == NULL){
            printf("No reservaste memoria apara las bombas\n");
            exit(1);
	};
	
	// Lee las bombas 
	int **listaBombas; 
    
        listaBombas = (int **) malloc(B *sizeof(int *)); 
        for (i=0; i<B; ++i)
            listaBombas[i] = (int *) malloc(4 *sizeof(int));
            
        for (i=0; i<B; ++i){
            fscanf(f,"%d %d %d %d \n", &bom[i].posX, &bom[i].posY, &bom[i].R, &bom[i].P);
            listaBombas[i][0] = bom[i].posX;
            listaBombas[i][1] = bom[i].posY;
            listaBombas[i][2] = bom[i].R;
            listaBombas[i][3] = bom[i].P;
        };
        free(bom);
              
        fclose(f);

        // Creación del campo de batalla
        int **campoInicial; 
        campoInicial = (int **) malloc(N*sizeof(int *)); 
        
        for (i=0; i<N; ++i)
            campoInicial[i] = (int *) malloc(N*sizeof(int));

        for (i=0; i<N; ++i){
            for (j=0; j<N; ++j)
                campoInicial[i][j] = 0; // Se inicializa el campo con puros ceros
        };
    
        // Asignación de valores al campo de batalla
        for (i=0; i<T; ++i){
            int posX, posY, valor;
            posX  = listaYardas[i][0];
            posY  = listaYardas[i][1];
            valor = listaYardas[i][2];
            if ((0<=posX<=N-1) && (0<=posY<=N-1))
                campoInicial[posX][posY] = valor;         
        }; 
    
        int **campoFinal;

        // Ejecución usando procesos 
        //campoFinal = lanzar_bombas_procesos(B, campoInicial, listaBombas, N, cantProcesos);

        // Ejecución usando hilos
        //campoFinal = lanzar_bombas_hilos(B, campoInicial, listaBombas, N, cantHilos);

        // Salida
        int 
        objMilTotDest=0, // Número de objetivos militares totalmente destruidos
        objMilParDest=0, // Número de objetivos militares parcialmente destruidos
        objMilNoAfect=0, // Número de objetivos militares no afectados
        objCivTotDest=0, // Número de objetivos civiles totalmente destruidos
        objCivParDest=0, // Número de objetivos civiles parcialmente destruidos
        objCivNoAfect=0; // Número de objetivos civiles no afectados

        /* --------------------------------------------------------------------
        for (i=0; i<N; ++i){
            for (j=0; j<N; ++j){
                if(campoInicial[i][j] < 0){ // Si es un objetivo militar
                    if (campoFinal[i][j] == 0) // Fue totalmente destruido
                        objMilTotDest +=1;
                    else {
                        if (campoFinal[i][j] > campoInicial[i][j]) // Fue parcialmente destruido
                            objMilParDest +=1;
                        else  // No se vio afectado
                            objMilNoAfect +=1;
                    };
                }
                else {
                    if (campoInicial[i][j] > 0) { // Si es un objetivo civil
                        if (campoFinal[i][j] == 0) // Fue totalmente destruido
                            objCivTotDest +=1;
                        else {
                            if (campoFinal[i][j] < campoInicial[i][j]) // Fue parcialmente
                                                                 // destruido
                                objCivParDest +=1;
                            else  // No se vio afectado
                                objCivNoAfect +=1;
                        };
                    };
                };
            };
        };
        ---------------------------------------------------------------------- */

        printf("Objetivos Militares totalmente destruidos: %d\n", objMilTotDest);
        printf("Objetivos Militares parcialmente destruidos: %d\n", objMilParDest);
        printf("Objetivos Militares no afectados: %d\n", objMilNoAfect);
        printf("Objetivos Civiles totalmente destruidos: %d\n", objCivTotDest);
        printf("Objetivos Civiles parcialmente destruidos: %d\n", objCivParDest);
        printf("Objetivos Civiles no afectados: %d\n", objCivNoAfect);
    
    }; 
    return 0;
};



