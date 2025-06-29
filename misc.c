//Este archivo existe para que funciones.c no tenga 500 lineas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include <time.h>

void fechaActual(char* fecha) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(fecha, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    // Año-Mes-Día (formato estándar ISO)
}


int legajoValido(struct Alumno* alumnos, int legajo) {
    if (legajo <= 0) return 0;

    struct Alumno* actual = alumnos;
    while (actual != NULL) {
        if (actual->legajo == legajo)
            return 1; // legajo duplicado
        actual = actual->siguiente;
    }
    return 2; // legajo válido
}

// Pide datos al ingresar un nuevo alumno.
struct Datos pedirDatos(struct Alumno* alumnos) {
    struct Datos datos;
    int estado;
    do {
        printf("Ingrese el legajo: ");
        if (scanf("%d", &datos.legajo) != 1) {
            printf("Entrada inválida. Intente nuevamente.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); 

        estado = legajoValido(alumnos, datos.legajo);

        if (estado == 0)
            printf("Legajo inválido. Debe ser mayor que 0.\n");
        else if (estado == 1)
            printf("Ese legajo ya está registrado.\n");
    } while (estado != 2); 

    printf("Ingrese el apellido: ");
    fgets(datos.apellido, sizeof(datos.apellido), stdin);
    datos.apellido[strcspn(datos.apellido, "\n")] = 0;

    printf("Ingrese el nombre: ");
    fgets(datos.nombre, sizeof(datos.nombre), stdin);
    datos.nombre[strcspn(datos.nombre, "\n")] = 0;

    return datos;
}


// Esta funcion carga las asistencias de asistencias.txt a la memoria al inicio del programa.
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

void mostrarAlumnos(struct Alumno* cabeza) {
    struct Alumno* actual = cabeza;
    printf("\n+--------+----------------+----------------+\n");
    printf("| Legajo | Apellido       | Nombre         |\n");
    printf("+--------+----------------+----------------+\n");
    while (actual != NULL) {
        printf("| %-6d | %-14s | %-14s |\n", actual->legajo, actual->apellido, actual->nombre);
        actual = actual->siguiente;
    }
    printf("+--------+----------------+----------------+\n");
}

void ordenarAlumnosPorApellido(struct Alumno* cabeza) {
    if (cabeza == NULL) return;

    int cambiado;
    struct Alumno* ptr1;
    struct Alumno* lptr = NULL;

    do {
        cambiado = 0;
        ptr1 = cabeza;

        while (ptr1->siguiente != lptr) {
            if (strcmp(ptr1->apellido, ptr1->siguiente->apellido) > 0) {
                // Intercambiar todos los datos del nodo
                int tempLegajo = ptr1->legajo;
                char tempNombre[50], tempApellido[50];
                strcpy(tempNombre, ptr1->nombre);
                strcpy(tempApellido, ptr1->apellido);

                ptr1->legajo = ptr1->siguiente->legajo;
                strcpy(ptr1->nombre, ptr1->siguiente->nombre);
                strcpy(ptr1->apellido, ptr1->siguiente->apellido);

                ptr1->siguiente->legajo = tempLegajo;
                strcpy(ptr1->siguiente->nombre, tempNombre);
                strcpy(ptr1->siguiente->apellido, tempApellido);

                cambiado = 1;
            }
            ptr1 = ptr1->siguiente;
        }
        lptr = ptr1;
    } while (cambiado);
}