#include <stdio.h>
#include "funciones.h"

int main(){
    struct Alumno* lista = NULL;
    int op=0;

    do{
        printf("| SISTEMA DE ASISTENCIAS |\n");
        printf("1 - Registrar nuevo alumno\n");
        printf("2 - Marcar asistencias del día\n");
        printf("3 - Editar asistencia de un alumno\n");
        printf("4 - Ver historial de asistencias de un alumno\n");
        printf("5 - Ver lista de inasistencias\n");
        printf("0 - Salir\n>");
        scanf("%d", &op);
        getchar();
        switch (op){
        case 1:
            struct Datos datoAlumno = pedirDatos();
            registrarNuevoAlumno(&lista, datoAlumno.legajo, datoAlumno.apellido, datoAlumno.nombre);
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    }while(op != 0);


    return 0;
}