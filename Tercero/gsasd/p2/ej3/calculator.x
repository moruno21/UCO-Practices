/* Define la estructura de parametros de entrada de las funciones */

struct operandos
{
	int a;
	int b;
};


program CALCULADORA_PROG {
    version CALCULADORA_VERS {
	int SUMA(operandos) = 1;
	int RESTA(operandos) = 2;
	int MULTIPLICACION(operandos) = 3;
	int DIVISION(operandos) = 4;
    } = 1;			
} = 0x20000001;		/* numero de programa = 0x20000001 */
			       /* 0x20000000 - 0x3fffffff para usuarios*/

