#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include <ctype.h>

// Funcion para tomar asistencia **||Actualizar para que use <time.h>||**
void tomarAsistencia(struct Alumno* cabeza) {
    FILE* asistencias = fopen("data/asistencias.txt", "a");
    if (asistencias == NULL) {
        printf("Error al abrir el archivo de asistencias.\n");
        return;
    }

    char fecha[11];
    printf("Ingrese la fecha (dd-mm-aaaa): ");
    scanf("%10s", fecha);

    struct Alumno* actual = cabeza;
    char estado;

    while (actual != NULL) {
        printf("Alumno: %s %s (Legajo: %d) - Presente (P) o Ausente (A)? ", actual->nombre, actual->apellido, actual->legajo);
        scanf(" %c", &estado);
        estado = (estado == 'p' || estado == 'P') ? 'P' : 'A';

        fprintf(asistencias, "%s;%d;%s;%s;%c\n", fecha, actual->legajo, actual->apellido, actual->nombre, estado);

        actual = actual->siguiente;
    }

    fclose(asistencias);
    printf("Asistencia registrada correctamente.\n");
}


// GESTION DE ALUMNOS //

// Esta funcion agrega un nodo de alumno al final de la lista, luego guarda sus datos en alumnos.txt.
void registrarNuevoAlumno(struct Alumno** cabeza, int legajo,  char nombre[50], char apellido[50]) {
   
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

    FILE* archivo = fopen("data/alumnos.txt", "a"); 
    if (archivo != NULL) {
        fprintf(archivo, "%d;%s;%s\n", legajo, nombre, apellido);
        fclose(archivo);
    } 
    else{
        printf("Error al abrir el archivo para guardar el alumno.\n");
    }

}

// Edita Nombre/Apellido de un alumno, editar legajo podria generar problemas de busqueda.
void editarAlumno(struct Alumno* cabeza) {
    if (cabeza == NULL) {
        printf("No hay alumnos registrados.\n");
        return;
    }

    int legajo;
    printf("Ingrese el legajo del alumno a editar: ");
    scanf("%d", &legajo);

    struct Alumno* actual = cabeza;
    while (actual != NULL && actual->legajo != legajo) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("No se encontró un alumno con ese legajo.\n");
        return;
    }

    printf("Alumno encontrado: %s %s\n", actual->apellido, actual->nombre);
    printf("Ingrese el nuevo apellido: ");
    scanf("%s", actual->apellido);
    printf("Ingrese el nuevo nombre: ");
    scanf("%s", actual->nombre);


    FILE* archivo = fopen("data/alumnos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para actualizar.\n");
        return;
    }

    struct Alumno* temp = cabeza;
    while (temp != NULL) {
        fprintf(archivo, "%d;%s;%s\n", temp->legajo, temp->apellido, temp->nombre);
        temp = temp->siguiente;
    }

    fclose(archivo);
    printf("Datos del alumno actualizados correctamente.\n");
}

void verHistorialAsistencias(struct Alumno* alumnos, struct Asistencia* asistencias, int legajoBuscado) {
    struct Alumno* alumno = alumnos;
    while (alumno != NULL && alumno->legajo != legajoBuscado) {
        alumno = alumno->siguiente;
    }

    if (alumno == NULL) {
        printf("No se encontró ningún alumno con legajo %d.\n", legajoBuscado);
        return;
    }

    printf("\n--- Historial de asistencias ---\n");
    printf("Alumno: %s %s (Legajo: %d)\n", alumno->apellido, alumno->nombre, alumno->legajo);
    printf("Fecha        | Estado\n");
    printf("----------------------\n");

    struct Asistencia* actual = asistencias;
    int encontrado = 0;

    while (actual != NULL) {
        if (actual->legajo == legajoBuscado) {
            printf("%s | %s\n", actual->fecha, (actual->estado == 'P') ? "Presente" : "Ausente");
            encontrado = 1;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No hay asistencias registradas para este alumno.\n");
    }
}



