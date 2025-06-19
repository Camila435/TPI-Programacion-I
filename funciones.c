#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include <ctype.h>


// Funcion para tomar asistencia
void tomarAsistencia(struct Alumno* alumnos, struct Asistencia* asistencias) {
    if (!alumnos) return;

    char fecha[11];
    fechaActual(fecha);

    struct Alumno* alumno = alumnos;
    char op, estado;

    printf("\n%-8s | %-15s | %-15s | %-8s\n", "Legajo", "Apellido", "Nombre", "Asistencia");
    printf("---------------------------------------------------------------\n");
    while (alumno) {
        printf("%-8d | %-15s | %-15s | [P/A]? ", alumno->legajo, alumno->apellido, alumno->nombre);
        scanf(" %c", &estado);
        estado = toupper(estado)=='P' ? 'P' : 'A';

        // Busca un nodo de asistencia existente 
        struct Asistencia* actual = asistencias;
        while (actual && !(actual->legajo==alumno->legajo && strcmp(actual->fecha, fecha)==0))
            actual = actual->siguiente;

        if (actual) {
            // Si existe, pregunta si se quiere sobrescribir
            printf("Ya existe asistencia de %s %s en %s (estado=%c). Sobrescribir? (S/N): ",
                   alumno->apellido, alumno->nombre, fecha, actual->estado);
            scanf(" %c", &op);
            if (toupper(op)=='S')
                actual->estado = estado;
        } else {
            // Si no, crea un nodo de asistencia
            struct Asistencia* nuevo = malloc(sizeof(*nuevo));
            strcpy(nuevo->fecha, fecha);
            nuevo->legajo = alumno->legajo;
            strcpy(nuevo->apellido, alumno->apellido);
            strcpy(nuevo->nombre, alumno->nombre);
            nuevo->estado = estado;
            nuevo->siguiente = asistencias;
            asistencias = nuevo;
        }
        alumno = alumno->siguiente;
    }

    FILE* f = fopen("data/asistencias.txt","w");
    for (struct Asistencia* iter = asistencias; iter; iter = iter->siguiente)
        fprintf(f,"%s;%d;%s;%s;%c\n",
                iter->fecha, iter->legajo, iter->apellido, iter->nombre, iter->estado);
    fclose(f);

    printf("Asistencia procesada.\n");
}

// GESTION DE ALUMNOS //

// Esta funcion agrega un nodo de alumno al final de la lista, luego guarda sus datos en alumnos.txt.
void registrarNuevoAlumno(struct Alumno** cabeza, int legajo, char apellido[50],  char nombre[50]) {
   
    struct Alumno* nuevo = (struct Alumno*)malloc(sizeof(struct Alumno));
    nuevo->legajo = legajo;
    strcpy(nuevo->apellido, apellido); 
    strcpy(nuevo->nombre, nombre); 
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
        fprintf(archivo, "%d;%s;%s\n", legajo, apellido, nombre);
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

void verHistorialAsistencias(struct Alumno* alumnos, struct Asistencia* asistencias) {
    int legajo;
    printf("Ingrese el legajo del alumno: ");
    scanf("%d", &legajo);
    struct Alumno* alumno = alumnos;

    while (alumno != NULL && alumno->legajo != legajo) {
        alumno = alumno->siguiente;
    }
    if (alumno == NULL) {
        printf("No se encontró ningún alumno con legajo %d.\n", legajo);
        return;
    }

    printf("\n==================================\n");
    printf("     HISTORIAL DE ASISTENCIAS\n");
    printf("==================================\n");
    printf("Alumno: %s %s (Legajo: %d)\n", alumno->apellido, alumno->nombre, alumno->legajo);
    printf("+------------+---------+\n");
    printf("| Fecha      | Estado  |\n");
    printf("+------------+---------+\n");

    struct Asistencia* actual = asistencias;
    int encontrado = 0;

    while (actual != NULL) {
        if (actual->legajo == legajo) {
            printf("| %-10s | %-7s |\n", actual->fecha, (actual->estado == 'P') ? "Presente" : "Ausente");
            encontrado = 1;
        }
        actual = actual->siguiente;
    }
    printf("+------------+---------+\n");

    if (!encontrado) {
        printf("No hay asistencias registradas para este alumno.\n");
    }
}

void editarAsistencia(struct Asistencia* cabeza) {
    if (cabeza == NULL) {
        printf("No hay registros de asistencia.\n");
        return;
    }

    int legajo;
    char fecha[11];
    printf("Ingrese el legajo del alumno para modificar asistencia: ");
    scanf("%d", &legajo);
    printf("Ingrese la fecha de la asistencia (formato AAAA-MM-DD): ");
    scanf("%10s", fecha);

    struct Asistencia* actual = cabeza;
    int encontrado = 0;
    while (actual != NULL) {
        if (actual->legajo == legajo && strcmp(actual->fecha, fecha) == 0) {
            printf("Fecha: %s | Alumno: %s %s | Estado actual: %c\n", actual->fecha, actual->apellido, actual->nombre, actual->estado);
            printf("Ingrese el nuevo estado de asistencia (P=Presente, A=Ausente, J=Justificado): ");
            scanf(" %c", &actual->estado); 
            encontrado = 1;
            break; 
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No se encontró asistencia para ese legajo y fecha.\n");
        return;
    }

    FILE* archivo = fopen("data/asistencias.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para actualizar.\n");
        return;
    }

    actual = cabeza;
    while (actual != NULL) {
        fprintf(archivo, "%s;%d;%s;%s;%c\n", actual->fecha, actual->legajo, actual->nombre, actual->apellido, actual->estado);
        actual = actual->siguiente;
    }

    fclose(archivo);
    printf("Asistencia del alumno actualizada correctamente.\n");
}
void mostrarAsistenciasPorFecha(struct Asistencia* asistencias) {
    char fecha[11];
    printf("Ingrese la fecha a consultar (formato AAAA-MM-DD): ");
    scanf("%10s", fecha);

    struct Asistencia* actual = asistencias;
    int encontrado = 0;

    printf("\n==================================\n");
    printf("   ASISTENCIAS DEL DÍA %s\n", fecha);
    printf("==================================\n");
    printf("+--------+----------------+--------------+--------+\n");
    printf("| Legajo | Apellido       | Nombre       | Estado |\n");
    printf("+--------+----------------+--------------+--------+\n");
    while (actual != NULL) {
        if (strcmp(actual->fecha, fecha) == 0) {
            printf(" %6d | %-14s | %-12s | %c\n", actual->legajo, actual->apellido, actual->nombre, actual->estado);
            encontrado = 1;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No hay asistencias registradas para esa fecha.\n");
    }
}



void listaInasistencias(struct Alumno* alumnos, struct Asistencia* asistencias) {
    if (alumnos == NULL || asistencias == NULL) {
        printf("\nNo hay datos suficientes para mostrar inasistencias.\n\n");
        return;
    }

    struct {
        int legajo;
        char nombre[50];
        char apellido[50];
        int faltas;
    } resumen[500];
    
    int totalAlumnos = 0;
    int maxFaltas = 0;
    struct Alumno* actualAlumno = alumnos;

    // Procesar datos
    while (actualAlumno != NULL) {
        int faltas = 0;
        struct Asistencia* actualAsistencia = asistencias;
        
        while (actualAsistencia != NULL) {
            if (actualAsistencia->legajo == actualAlumno->legajo && 
                actualAsistencia->estado == 'A') {
                faltas++;
            }
            actualAsistencia = actualAsistencia->siguiente;
        }

        resumen[totalAlumnos].legajo = actualAlumno->legajo;
        strcpy(resumen[totalAlumnos].nombre, actualAlumno->nombre);
        strcpy(resumen[totalAlumnos].apellido, actualAlumno->apellido);
        resumen[totalAlumnos].faltas = faltas;

        if (faltas > maxFaltas) maxFaltas = faltas;
        totalAlumnos++;
        actualAlumno = actualAlumno->siguiente;
    }

    // Mostrar tabla
    printf("\n");
    printf("+--------+----------------+--------------+---------+\n");
    printf("| Legajo | Apellido       | Nombre       | Faltas  |\n");
    printf("+--------+----------------+--------------+---------+\n");

    for (int i = 0; i < totalAlumnos; i++) {
        printf("| %-6d | %-14s | %-12s | %-7d |\n", 
               resumen[i].legajo,
               resumen[i].apellido,
               resumen[i].nombre,
               resumen[i].faltas);
    }
    printf("+--------+----------------+--------------+---------+\n");

    // Mostrar resumen
    if (maxFaltas > 0) {
        printf("\n[!] Alumnos con mas inasistencias (%d faltas):\n", maxFaltas);
        for (int i = 0; i < totalAlumnos; i++) {
            if (resumen[i].faltas == maxFaltas) {
                printf("- %s %s (Legajo: %d)\n", 
                       resumen[i].apellido, resumen[i].nombre, resumen[i].legajo);
            }
        }
    } else {
        printf("\nTodos los alumnos tienen asistencia perfecta.\n");
    }
    printf("\n");
}
