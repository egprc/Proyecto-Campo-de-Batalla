#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE !FALSE

#ifndef PARAMETROS_H
#define PARAMETROS_H


int Parametros(int *procesos, int*hilos, int *cantidad, int argc, char **argv);

#endif
