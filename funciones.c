#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

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

    FILE* archivo = fopen("data/alumnos.txt", "a"); // abrir en modo append
    if (archivo != NULL) {
        fprintf(archivo, "%d;%s;%s\n", legajo, nombre, apellido);
        fclose(archivo);
    } 
    else{
        printf("Error al abrir el archivo para guardar el alumno.\n");
    }

}

