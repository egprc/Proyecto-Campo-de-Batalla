#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE !FALSE

#ifndef _PARAMETROS_H_
#define _PARAMETROS_H_


int Parametros(int *procesos, int*hilos, int *cantidad, int argc, char **argv);

#endif
