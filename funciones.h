#ifndef FUNCIONES_H
#define FUNCIONES_H

    struct Alumno{
        int legajo;            
        char nombre[50];        
        char apellido[50];      
        struct Alumno* siguiente; 
    };
    struct Datos{
        int legajo;         
        char nombre[50]; 
        char apellido[50];
    };

    struct Datos pedirDatos();
    void registrarNuevoAlumno(struct Alumno** cabeza, int legajo,  char nombre[50], char apellido[50]);
    void tomarAsistencia();
    void editarAsistencia();
    void verHistorialAsistencias();
    void listaInasistencias();


#endif