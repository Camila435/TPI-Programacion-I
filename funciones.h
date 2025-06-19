#ifndef FUNCIONES_H
#define FUNCIONES_H

void fechaActual(char* fecha);

    struct Alumno{
        int legajo;            
        char nombre[50];        
        char apellido[50];      
        struct Alumno* siguiente; 
    };
    struct Asistencia{
        char fecha[11];
        int legajo;            
        char nombre[50];        
        char apellido[50];      
        char estado;
        struct Asistencia* siguiente; 
    };
    struct Datos{
        int legajo;         
        char nombre[50]; 
        char apellido[50];
    };

    void tomarAsistencia(struct Alumno* cabeza);

    // GESTION DE ALUMNOS
    void registrarNuevoAlumno(struct Alumno** cabeza, int legajo,  char nombre[50], char apellido[50]);
    void editarAlumno(struct Alumno* cabeza);
    void editarAsistencia(struct Asistencia* cabeza);
    void verHistorialAsistencias(struct Alumno* alumnos, struct Asistencia* asistencias);

    // INFORMES
    void listaInasistencias();
    void mostrarAsistenciasPorFecha(struct Asistencia* asistencias);
    void mostrarInasistenciasPorFecha(struct Asistencia* asistencias);


    //Archivo misc.c
    struct Datos pedirDatos();
    void cargarAlumnos(struct Alumno** cabeza);
    void mostrarAlumnos(struct Alumno* cabeza);
    void cargarAsistencias(struct Asistencia** cabeza);
    void liberarAsistencias(struct Asistencia* cabeza);
    void ordenarAlumnosPorApellido(struct Alumno* cabeza);


#endif