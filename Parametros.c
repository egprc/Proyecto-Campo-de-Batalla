#include "Parametros.h"
#include <stdbool.h>
#define TRUE !FALSE



/* Función: Parametros
   Entrada: 
            *procesos 
            *hilos
            *cantidad
            argc: Nro. de parámetros de main 
            **argv: Arreglo de entrada de Main
   Salida: 
            *procesos
            *hilos
            *cantidad
            TRUE: Éxito
            Errores: Finaliza el programa
            
Descripción: Procesa el pasaje de parámetros por línea de comandos
             según la convencion de los sistemas Linux
*/ 

int Parametros(int *procesos, int *hilos, int *cantidad, int argc, char **argv) {
    int opciones;   
    char *parametros = "p::h::n::";
    *cantidad = 0;
    *procesos = 1;

    while (-1!=(opciones=getopt(argc, argv, parametros))) {
        switch (opciones) {	
            /* "-p " indica si el programa usa procesos */
            case 'p' :
            *procesos=1;
	    printf("valor de p %d",*procesos);
            /* printf("Valor: %d", *nro_tiradas); */
            continue;
            
            /* "h", indica si el programa usó hilos */
            case 'h' :
            *hilos=1;
	    printf("valor de p %d",*procesos);
            continue;
            
            /* "n" indica la cantidad de hilos y/o procesos a usar.  */
            case 'n' :			
            *cantidad=atoi(optarg);
            continue;

            /* Parámetros no reconocidos*/
            default : 
            printf("Opción incorrecta\n"); 
            exit(1);
        };
    };

    if ((*procesos == 1) &&( *hilos == 1)){
        printf("Debe elegir entre procesos o hilos; NO se permiten ambos\n");
        exit(1);
    };
    return true;
}
