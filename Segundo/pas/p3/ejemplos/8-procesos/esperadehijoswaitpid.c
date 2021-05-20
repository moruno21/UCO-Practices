/*

Lógica para esperar a hijos con waitpid().

Faltaría el resto del programa en cuestión.

*/

/*Espera del padre a los hijos*/
while ( (flag=waitpid(-1,&status,WUNTRACED | WCONTINUED)) > 0 ) 
{
    if (WIFEXITED(status)) 
    {
	    printf("Proceso Padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)flag, WEXITSTATUS(status));
    } 
    else if (WIFSIGNALED(status))  
    {
	    printf("Proceso Padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)flag, WTERMSIG(status));
    } 
    else if (WIFSTOPPED(status))  //Para cuando se para un proceso. Con wait() no nos serviria.
    {
	    printf("Proceso Padre %d, hijo con PID %ld parado al recibir la señal %d\n", getpid(), (long int)flag,WSTOPSIG(status));
    } 
    else if (WIFCONTINUED(status))  //Para cuando se reanuda un proceso parado. Con wait() no nos serviria.
    {
	    printf("Proceso Padre %d, hijo con PID %ld reanudado\n", getpid(), (long int) flag);		  
    }
}//while

if (flag==(pid_t)-1 && errno==ECHILD)
{
    printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
}
else
{
    printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
}	 
