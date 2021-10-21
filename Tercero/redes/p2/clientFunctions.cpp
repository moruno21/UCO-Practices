#include "./include/clientFunctions.h"

void LogInInfoMessage()
{
    cout << "\n-----------------------------------------------------------------" << endl;
    cout << "|           ¡Bienvenido al juego de averigua el refrán!            |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| Seleccione una de las siguiente opciones:                        |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| *Si ya estas registrado:                                         |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| - USUARIO (nombre)      -> Para acceder con tu nombre de usuario |" << endl;
    cout << "| - PASSWORD (contraseña) -> Para acceder con tu contraseña        |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| *Si no estas registrado:                                         |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "| -REGISTRO -u (nombre) -p (contraseña)                            |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "-------------------------------------------------------------------\n"
         << endl;
}

void OptionsInfoMessage()
{
    cout << "\n------------------------------------------------------------------" << endl;
    cout << "|                           Bienvenido                             |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|  Seleccione una de las siguiente opciones:                       |" << endl;
    cout << "|                                                                  |" << endl;
    cout << "|      - INICIAR-PARTIDA   ->  Para empezar una partida            |" << endl;
    cout << "|      - SALIR -> Para salir en cualquier momento                  |" << endl;
    cout << "-------------------------------------------------------------------\n";
}

void startingGameInterface()
{
    cout << "\n-----------------------------------------------------------------" << endl;
    cout << "| Opciones:                                                        |" << endl;
    cout << "| - VOCAL     ->  Resolver vocal (-50 puntos)                      |" << endl;
    cout << "| - CONSONANTE->  Resolver consonante (+50 puntos cada ocurrencia) |" << endl;
    cout << "| - PUNTUACION->  Puntos del jugador                               |" << endl;
    cout << "| - RESOLVER  ->  Resolver la frase                                |" << endl;
    cout << "--------------------------------------------------------------------\n"
         << endl;
}