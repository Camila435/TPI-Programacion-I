/*Control de Asistencia Escolar
1- Registro de estudiantes y asistencias por día.
2- Marcar asistencia por fecha, editar si fue incorrecta.
3- Ver historial de asistencias por alumno.
4- Mostrar alumnos con más inasistencias.
5- Archivos para almacenar los registros diarios.
6- Listas para manejar registros de asistencia diarios.

*/

#include <stdio.h>
#include "funciones.h"

int main(){
    struct Alumno* alumnos = NULL;
    struct Asistencia* asistencias = NULL;
    cargarAsistencias(&asistencias);
    cargarAlumnos(&alumnos);
    int op=0;

    do{
        printf("| SISTEMA DE ASISTENCIA |\n");
        printf("1 - Tomar asistencia\n");
        printf("2 - Gestion de alumnos\n");
        printf("3 - Informes\n");
        printf("0 - Salir\n>");
        scanf("%d", &op);
        getchar();
        switch (op){
        case 1:
            tomarAsistencia(alumnos);
            // Recarga la lista para que lo recien cargado se muestre en el historial de asistencias.
            liberarAsistencias(asistencias);        
            asistencias = NULL;
            cargarAsistencias(&asistencias);           
            break;
        case 2:
            do{
                printf("| GESTION DE ALUMNOS |\n");
                ordenarAlumnosPorApellido(alumnos);
                mostrarAlumnos(alumnos);
                printf("1 - Registrar nuevo alumno\n");
                printf("2 - Editar alumno\n");
                printf("3 - Ver historial de asistencias\n");
                printf("4 - Editar asistencia\n");
                printf("0 - Volver\n>");
                scanf("%d", &op);
                switch (op){
                case 1:
                    struct Datos datoAlumno = pedirDatos(alumnos);
                    registrarNuevoAlumno(&alumnos, datoAlumno.legajo, datoAlumno.apellido, datoAlumno.nombre);
                    break;
                case 2:
                    editarAlumno(alumnos);
                    break;
                case 3:
                    verHistorialAsistencias(alumnos, asistencias);
                    break;
                case 4:
                   editarAsistencia(asistencias);
                    break;
                case 0:
                    break;
                default:
                    break;
                }
            }while(op != 0);
            op = 2; 
            break;
                case 3: {
            int opInforme;
            do {
                printf("| INFORMES |\n");
                printf("1 - Ver asistencias de un dia en particular\n");
                printf("2 - Ver lista de inasitencias\n");
                printf("0 - Volver\n");
                scanf("%d", &opInforme);
                switch (opInforme) {
                    case 1:
                        mostrarAsistenciasPorFecha(asistencias);
                        break;
                    case 2:
                        listaInasistencias(alumnos, asistencias);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opción no válida. Intente de nuevo.\n");
                        break;
                }
            } while (opInforme != 0);
            break;
        }
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        } // <-- Cierra el switch principal
    } while(op != 0); // <-- Cierra el do-while principal
    return 0;
}