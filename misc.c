//Este archivo existe para que funciones.c no tenga 500 lineas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Pide datos al ingresar un nuevo alumno.
struct Datos pedirDatos(){
    int legajo;
    char nombre[50];
    char apellido[50];
    printf("Ingrese el legajo: ");
    scanf("%d", &legajo);
    printf("Ingrese el apellido: ");
    scanf("%s", apellido);
    printf("Ingrese el nombre: ");
    scanf("%s", nombre);  
    struct Datos datos;
    datos.legajo = legajo;
    strcpy(datos.apellido, apellido);
    strcpy(datos.nombre, nombre);
    return datos;
}

// Esto carga las asistencias dentro de una lista dinamica, por alguna razon.
void cargarAsistencias(struct Asistencia** cabeza){
    FILE* archivo = fopen("data/asistencias.txt", "r");
    if (archivo == NULL){
        printf("No existen fechas registradas.");
        return;
    }

    char fecha[11];
    int legajo;
    char apellido[50];
    char nombre[50];
    char estado;

    while (fscanf(archivo, "%10[^;];%d;%49[^;];%49[^;];%c\n", fecha, &legajo, apellido, nombre, &estado) == 5) {
        struct Asistencia* nuevo = (struct Asistencia*)malloc(sizeof(struct Asistencia));
        strcpy(nuevo->fecha, fecha);
        nuevo->legajo = legajo;
        strcpy(nuevo->apellido, apellido);
        strcpy(nuevo->nombre, nombre);
        nuevo->estado = estado;
        nuevo->siguiente = NULL;

        if (*cabeza == NULL) {
            *cabeza = nuevo;
        } else {
            struct Asistencia* actual = *cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }
}

void liberarAsistencias(struct Asistencia* cabeza) {
    struct Asistencia* actual;
    while (cabeza != NULL) {
        actual = cabeza;
        cabeza = cabeza->siguiente;
        free(actual);
    }
}

// Esta funcion carga los alumnos de alumnos.txt a la memoria al inicio del programa.
void cargarAlumnos(struct Alumno** cabeza) {
    FILE* archivo = fopen("data/alumnos.txt", "r");
    if (archivo == NULL) {
        printf("No hay alumnos cargados.");
        return;
    }

    int legajo;
    char nombre[50];
    char apellido[50];

    //(fscanf(alumnos.txt, %nº de legajo, %49 caracteres o hasta encontrar ';', 49 caracteres o hasta encontrar '\n' ))
    //Solo quedará en el bucle cuando existan esas tres variables.
    while (fscanf(archivo, "%d;%49[^;];%49[^\n]\n", &legajo, apellido, nombre) == 3) {
        struct Alumno* nuevo = (struct Alumno*)malloc(sizeof(struct Alumno));
        nuevo->legajo = legajo;
        strcpy(nuevo->nombre, nombre);
        strcpy(nuevo->apellido, apellido);
        nuevo->siguiente = NULL;

        if (*cabeza == NULL) {
            *cabeza = nuevo;
        } else {
            struct Alumno* actual = *cabeza;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    fclose(archivo);
}

//Falta un algoritmo de ordenamiento 
void mostrarAlumnos(struct Alumno* cabeza) {
    struct Alumno* actual = cabeza;
    while (actual != NULL) {
        printf("%d - %s %s\n", actual->legajo, actual->nombre, actual->apellido);
        actual = actual->siguiente;
    }
}