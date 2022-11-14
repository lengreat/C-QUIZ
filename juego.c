#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define MAX 20
#define TAM 7
#define CAS 100//para cadena de preguntas

typedef enum{false,true,}bool;//necesario para los booleanos
void dibujaTablero(int n, int pos1, int pos2);
void menuPrincipal();
//void llenadoCasillas(char *cad);
void declararGanador(char * nombre);
void guardarJugadores(FILE *top, char jugador[30], int anio, int mes, int dia);
void empiezaJuego(char *primero, char *segundo, int *posicion1, int *posicion2, int tam, int *salir, bool unoSolo);
void obtenerPregunta(FILE *archPreg, int numJJugadoresAleatorio, char * pregunta, char * respuesta);
int  lanzarDado();
int  primerJugador(int a, int b);//
bool eleccionCasillas(void);
//void penitencias(int *posicion, int *posicion1, int *posicion2, int tamTablero, char *cad);
void penitencias(int *posicion, int *posicion1, int *posicion2, int tamTablero, char *nombreJugador);
void cambiaColor(int i, int j, int pos1, int pos2, int l, int tam);
int salirBarra();

void main(){
  int tam=20;//valor por default del tablero
  int band=0,lanzamiento1=0, lanzamiento2=0, temp=0, sorteoQuienVaPrimero=0, casillas[CAS]={0};//Declaracion de variables
  int pos1=1, pos2=1, numJugadores;
  int salir=0, cont1=0;
  bool unoSolo=false, pasoAEstadisticas=false;
  char nombre[MAX]="", jug1[MAX]="", jug2[MAX]="", op[TAM]="";
  char primero[MAX]="", segundo[MAX]="", ganadorFile[MAX]="", fechaFile[MAX]="";
  struct tm *tiempo;
  int dia, mes, anio;
  FILE *juego;
  srand(time(NULL));
    printf("Holdrfdddfda  m, mn\n");


  system("Pause");
  while (true){ 
    do{         
        system("cls");//limpia la pantalla
 		system("color 0e");//da color negro fondo y amarillo letra
        menuPrincipal();
      
        gets(op);//puede recibir caracteres incluso mayor a TAM, se adquiere un nuevo TAM
 		fflush(stdin);//flushall();//Para que no tome el enter como otro caracter
      
 	}while((op[0]<'1')||(op[0]>'3')||(strlen(op)>1));//se pone caracteres para q valide por caracteres y no solo numJJugadoreseros
    //se valida rango entre menor a 1 y mayor 3 para que vuelva al do-while, asi como podria ingresar numJJugadoreseros con mas de un digito ya que la validacion solo se da en el primer digito ingresado para las opciones

    switch (op[0])
    {
        case '1':
            printf("Juego Nuevo\n");
            salir=0;
			cont1=0;//inicializa el ingreso a la opcion 2 para volver a guardar ganadores
			do{
			  system("cls");
			  system("color 0b");
		      printf("\n\n\tDesea jugar con 1 o 2 jugadores: ");
		      scanf("%d",&numJugadores);
			} while((numJugadores!=1)&&(numJugadores!=2));
			fflush(stdin);//limpia el buffer
			printf("\n\n\t\t              !Espere!\n\n\n\n\tEl numero de casilleros puede ser cambiado");
			getch();//para dar paso a un enter
			if (eleccionCasillas()){//Si deseo cambiar el numJJugadoresero de casillas
	          printf("\n\tIngrese el numero de casillas: ");
		      scanf("%d", &tam);
			  fflush(stdin);
	        }
			if (numJugadores==2){//si numJJugadoresero de jugadores es igual a 2
			    fflush(stdin);
                printf("     \n\n        Ingrese nombre de jugador: ");
                gets(jug1);//obtiene un string
			    fflush(stdin);
			    printf("     \n\n        Ingrese nombre del otro jugador: ");
                gets(jug2);
			    while (sorteoQuienVaPrimero==0){
		          lanzamiento1=lanzarDado();//primer lanzamiento de dados
		          lanzamiento2=lanzarDado();//segundo lanzamiento de dados
			      sorteoQuienVaPrimero=primerJugador(lanzamiento1, lanzamiento2);//si jugador 1 es mayor entonces valor =1, de lo contrario valor = 2, en caso de empate es 0
                }
			    dibujaTablero(tam, pos1, pos2);//EN CADA LOOP DEBE REDIBUJAR TABLERO CON POSICIONES ACTUALIZADAS
			    printf("\n                                 SORTEO TURNOS");
		        printf("\n\n     Jugador %s obtuvo %d                     Jugador %s obtuvo %d ",jug1, lanzamiento1, jug2, lanzamiento2);
			    if (sorteoQuienVaPrimero==2){//JUGADOR 2 OBTUVO MAYOR NUMERO, VA PRIMERO
		          strcpy(primero, jug2);
			      strcpy(segundo, jug1);
                }
			     else if (sorteoQuienVaPrimero==1){
			      strcpy(primero, jug1);
			      strcpy(segundo, jug2);
                }
				 
			    getch();
			    system("cls");
			    dibujaTablero(tam, pos1, pos2);
			    printf("\n                                 SORTEO TURNOS");
			    printf("\n\n     El jugador que lanzara primero es %s", primero);
		        getch();
			    dibujaTablero(tam, pos1, pos2);
			    empiezaJuego(primero, segundo, &pos1, &pos2, tam, &salir, unoSolo);
			    system("cls");
			    if (salir==-1){
		  	      printf("\n\n\n\n                 No hay ganadores");
		  	      getch();
			    } else {
			        if (pos1>pos2)
			    	    strcpy(nombre, primero);
			        else
			    	    strcpy(nombre, segundo);
			        declararGanador(nombre);
                }
			  	system("cls");
			  	printf("\n\n\n\n                         GAME OVER");
			  	fflush(stdin);
			  	getch();
		         
			}//FIN DE IF NUMJugadores=2
			else//un jugador
			{
				pos2=0;//No hay posicion para el jugador 2
				dibujaTablero(tam, pos1, pos2);
				unoSolo=true;
				fflush(stdin);
                printf("     \n\n        Ingrese nombre del unico jugador: ");
                gets(primero);
				empiezaJuego(primero, segundo, &pos1, &pos2, tam, &salir, unoSolo);
				if (salir==-1){//indica q hubo juego pero no ganadores
					system("cls");
					printf("\n\n\n\n\n                      No hay ganadores");
					getch();
				} else {
                    if (pos1>pos2)
					    strcpy(nombre, primero);
				    else
					    strcpy(nombre, segundo);
				    declararGanador(nombre);
                }
				system("cls");
				printf("\n\n\n\n                            GAME OVER");
				fflush(stdin);
				getch();
			}//FIN DE ELSE
            //REINICIO DE VARIABLES PRIORITARIAS
			band=1;//
			pasoAEstadisticas=true;//Ya puede ingresar a estadisticas de juego
			tam=20;
			sorteoQuienVaPrimero=0;
			pos1=1;
			pos2=1;
			unoSolo=false;
      break;
      case '2':
        //printf("Estadisticas\n");
		//SOLO GUARDA CUANDO ENTRO A ESTA OPCION
		//ASI MISMO SOLO SE PUEDEN VER ESTADISTICAS LUEGO DE JUGAR debido a q primero hay q dar valor a nombre de ganador de juego
		//LA SOLUCION ES GUARDAR LA LISTA DE GANADORES EN LA OPCION 1, NO LA 2
		cont1++;//las veces que ingresa a consultar
	    system("cls");
	    if (!pasoAEstadisticas)//Esta es una bandera para no poder ingresar a esta opcion sin haber jugado
		    printf("\n\n\t!NI LO INTENTE!  aun no se ha jugado, vuelva al menu");
		else{
			time_t fecha;
	        time(&fecha);
	        tiempo=localtime(&fecha);

	        anio=tiempo->tm_year + 1900;
	        mes=tiempo->tm_mon + 1;
	        dia=tiempo->tm_mday;
		    juego=fopen("ganadores.txt", "a+");//abre o lee un fichero para lectura y escritura al final del mismo
			if ((salir!=-1)&&(cont1==1))//salir!=-1 significa q si hubo ganadores y cont1 para guardar ganadores solo la primera vez despues de jugar
				guardarJugadores(juego, nombre, anio, mes, dia);//nombre: nombre de ganador
            //luego cont1 se incrementa para ya no guardar y solo consultar

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("\n                       ****************************\n");
			printf("                       **   LISTA DE GANADORES   **\n");
			printf("                       ****************************\n\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			while (!feof(juego)){
				fscanf(juego,"%s %s\n", ganadorFile, fechaFile);
				printf(" *   %s   %s\n", ganadorFile, fechaFile);
			}
			fclose(juego);		 		
		}//FIN DE
	    getch();
      break;
      case '3':
        return;
      break;
    }

  }
}



/*
*  Procedimiento: menuPrincipal
*  Uso: menuPrincipal();
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Procedimiento q muestra las opciones en forma de menu
*/
void menuPrincipal(){

  printf("********************************************************************************\n");
  printf("********************************************************************************\n");
  printf("** *                                                                        * **\n");
  //printf("**   *             %c   %c   %c   %c   %c       %c   %c   %c   %c   %c              *   **\n", 69, 83, 80, 79, 76, 81, 85, 69, 83, 84);
  printf("**   *                 M  I  N  I        T  R  I  V  I  A                 *   **\n");
  printf("**     *                                                                *     **\n");
  printf("**       **************************************************************       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                  1) Juego Nuevo                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                  2) Ganadores                          ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                  3) Exit                               ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       ***                                                        ***       **\n");
  printf("**       **************************************************************       **\n");
  printf("**     *                                                                *     **\n");
  printf("**   *                      Ingrese una opcion                            *   **\n");
  printf("** *                                                                        * **\n");
  printf("********************************************************************************\n");
  printf("******************************************************************************\n");

}

/*
*  Funcion: eleccionCasillas
*  Uso: if(eleccionCasillas());
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Funcion booleana q permite saber si el usuario quiere cambiar el numJJugadoresero de casillas
*/
bool eleccionCasillas(void)
{
	int variarCasillas;
	do{
		system("cls");
		printf("\n\n\tDesea variar l numero d casillas  SI: Teclee 1    NO: Teclee 2   :");
	    scanf("%d", &variarCasillas);
	} while((variarCasillas!=1)&&(variarCasillas!=2));
	if (variarCasillas==1)
		return true;
	else 	return false;
}


/*
*  Funcion: lanzarDado
*  Uso: lanzo1=lanzarDado();
*       lanzo2=lanzarDado();
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Funcion q retorna un numJJugadoresero aleatorio simulando un lanzamiento de dados
*/
int lanzarDado()
{
	return ((rand()%6)+1);
}

/*
*  Funcion: primerJugador
*  Uso: valor=primerJugador(lanzo1, lanzo2);
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Funcion q retorna un numJJugadoresero aleatorio simulando un lanzamiento de dados
*/
int primerJugador(int a, int b)
{
	if (a>b)
		return 1;
	else if (a<b)
		return 2;
	else
		return 0;
}


/*
*  Procedimiento: dibujaTablero
*  Uso: dibujaTablero(tam);
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Procedimiento q muestra un tablero de forma agradable
*/
void dibujaTablero(int n, int pos1, int pos2)
{
	int i=0, idCasilla=1, l=0, col=10, fil;//Las columna seran de 10 por diseno
	bool filaRestante=true, ingresoSeccion=false;
	fil=n/col;//OBTENGO NUMERO DE FILAS A DIBUJAR A PARTIR DEL TAMANIO
    system("cls");
    printf("\n");
	while(filaRestante){
        for(int j=0; j<fil; j++){//IMPRESION DE FILAS
	        printf("\n     ");
	    	for (i=0; i<col; i++){//ESQUINAS Y PARTE SUPERIOR, IMPRIME TODAS LAS COLUMNAS DE LA FILA
	    		cambiaColor(i, j, pos1, pos2, idCasilla, n);//DECIDE SI CAMBIA DE COLOR  O NO
	    		printf("%c%c%c%c%c%c%c", 201,205,205,205,205,205,187);//╔═══╗
				idCasilla++;
			}
			//SE RESTA -COL PARA REINICIAR IDCASILLA YA QUE IMPRIMIRA EN LA MISMA FILA
			idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2
            printf("\n     ");
            for (i=0; i<col; i++){//PARTE MEDIA Y IDCASILLA
	    		cambiaColor(i, j, pos1, pos2, idCasilla, n);
	            printf("%c%2d%c  %c", 186,idCasilla,' ', 186);
                idCasilla++;
            }
			idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2
            printf("\n     ");
	    	for (i=0; i<col; i++){//PARTE MEDIA Y CASILLAS ESPECIALES
	    		cambiaColor(i, j, pos1, pos2, idCasilla, n);
	    		if ((((i==4)||(i==8)) && (j==0))||(((i==2)||(i==5)||(i==9))&&(j==1)))//Validando para ingresar contenido a las casillas especiales
	               printf("%c  %c  %c", 186, 219, 186);
	    		else 
	    		   printf("%c  %c  %c", 186,' ' , 186);
				idCasilla++;
            }
			idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2
            printf("\n     ");
			for (i=0; i<col; i++){//PARTE MEDIA Y CASILLAS ESPECIALES
				cambiaColor(i, j, pos1, pos2, idCasilla, n);
				if ((((i==4)||(i==8)) && (j==0))||(((i==2)||(i==5)||(i==9))&&(j==1)))//Validando para ingresar contenido a las casillas especiales
	         		printf("%c  %c  %c", 186, 219, 186);
				else
					printf("%c  %c  %c", 186,' ' , 186);
				idCasilla++;
    		}
			idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2
    		printf("\n     ");
			for (i=0; i<col; i++){
				cambiaColor(i, j, pos1, pos2, idCasilla,n);
				printf("%c  %c  %c", 186,' ' , 186);
				idCasilla++;
      		}
			idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2
      		printf("\n     ");
			for (i=0; i<col; i++){//PARTE INFERIOR Y ESQUINAS
        		cambiaColor(i, j, pos1, pos2, idCasilla, n);
				printf("%c%c%c%c%c%c%c%", 200,205,205,205,205,205,188);
      		    idCasilla++;
			}
			//idCasilla=idCasilla-col;//ESTE NUMERO TOMARA LA POSICION DE CADA CASILLA PARA COMPARACION CON POS1 Y POS2

    	}
		//SEGMENTO NECESARIO PARA IMPRIMIR EL RESTANTE DE CASILLAS
		if(((n%col)>0) && !ingresoSeccion){//SI NO HAY RESIDUO O EL RESTANTE DE FILA
	    	col=n%col;//VUELVE A IMPRIMIR LA FILA CON DIFERENTE TAMANO DE COLUMNAS
	    	fil=1;
			ingresoSeccion=true;//una vez ingresado a este segmento ya no es necesario volver a entrar aqui
    	//} else m=1;
		} else filaRestante=false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	}
    printf("\n\n     ");
    printf("\t\t\t     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,187);
    printf("\t\t\t     %c %c %c %c %c %c %c %c %c %c %c\n", 186,76,186,69,186,79,186,86,186,89,186);
    printf("\t\t\t     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,188);
}

void cambiaColor(int i, int j, int pos1, int pos2, int posicion, int tam){
	if (pos1>tam)
		pos1=tam;//PARA CUANDO LA POSICION 1 SOBREPASA EL TABLERO
	if (pos2>tam)
		pos2=tam;//PARA CUANDO LA POSICION 2 SOBREPASA EL TABLERO
	if (pos1!=pos2){
		
		if (posicion==pos1)//SI LA CASILLA ES IGUAL A LA POSICION
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    	else
	    	if (posicion==pos2)
		    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//color default
	}
	else//SI SE ENCUENTRAN EN LA MISMA POSICION
	{
	    if (posicion==pos1)//color en la misma poscion 59
	    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//se pinta blanco en la misma poscion
        else//se pinta color amarillo
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	
	}
}

void empiezaJuego(char *primero, char *segundo, int *posicion1, int *posicion2, int tam, int *salir, bool unoSolo)
{
	int avance1=0, avance2=0, turno1=0, turno2=0;
	do{
		//------------------ Jugador 1 ---------------------
		avance1=lanzarDado();
	    *posicion1=(*posicion1)+avance1;//avanza hacia la nueva posicion
	    turno1++;//se incrementa turno de primer jugador
	    system("cls");
        dibujaTablero(tam, *posicion1, *posicion2);//redibuja con las nuevas posiciones
	    printf("\n                                TURNO %d: %s ", turno1, primero);
	    printf("\n\n     Jugador azul %s obtuvo %d, ahora se encuentra en la casilla %d", primero, avance1, *posicion1);
		printf("\n\n     Puede terminar el juego con barra espaciadora o\n     presionar cualquier tecla para continuar jugando");
		penitencias(posicion1, posicion1, posicion2, tam, primero);
		if (*posicion1>=tam){//sobrepaso el tablero
			getch();
			return;//acaba el juego
		}
		if (salirBarra()==2){//BARRA ESPACIADORA PARA SALIR DEL JUEGO
			*salir=-1;
			return;//acaba el jjuego
		}
		//------------   Jugador 2 --------------------
		if (unoSolo==false){
	        avance2=lanzarDado();
	        *posicion2=(*posicion2)+avance2;
	        turno2++;
	        system("cls");
	        dibujaTablero(tam, *posicion1, *posicion2);
	        printf("\n                                TURNO %d: %s ", turno2, segundo);
	        printf("\n\n     Jugador gris %s obtuvo %d y ahora se encuentra en la casilla %d", segundo, avance2, *posicion2);
	        penitencias(posicion2, posicion1, posicion2, tam, segundo);
	        if (*posicion2>=tam){
		        getch();
		        return;
			}
	        if (salirBarra()==2){
		        *salir=-1;
		        return;
			}
		}
	}while ((*posicion1<tam)&&(*posicion2<tam));
	

}


void penitencias(int *posicion, int *posicion1, int *posicion2, int tamTablero, char *nombreJugador)
{
	int i=0, a=0;
	char pregunta[CAS]="", respuesta[MAX]="", respuestaJugador[MAX]="";
	FILE *pre;
	pre=fopen("preguntas.txt", "r");//debe de existir
    if (*posicion==5){
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA %d: %s",*posicion, nombreJugador);
		printf("\n\n     Responda correctamente la pregunta para avanzar a la casilla 10");
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		a=(rand()%9)+1;//pregunta del 1 al 9
		obtenerPregunta(pre, a, pregunta, respuesta);
		printf("\n                               PREGUNTA/QUESTION");
		printf("\n\n     %s      ", pregunta);
		gets(respuestaJugador);
		fflush(stdin);
		if ((strcmp(respuesta,respuestaJugador))==0)
		{
			*posicion=10;//Avanza a casilla 10
			printf("\n     Respuesta Correcta, avanza a la casilla %d", *posicion);
			getch();
			
		}
		else
		{
			printf("\n     Respuesta Incorrecta, permanecen casilla %d", *posicion);
		    getch();
		}
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA %d: %s",*posicion, nombreJugador);
		printf("\n\n     Ahora se encuentra en la casilla %d", *posicion);
		//getch();
		}
	if (*posicion==9){
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA 9: %s", nombreJugador);
		printf("\n\n     Responda correctamente si quiere permanecer en la casilla, sino retrocedera a la casilla 6");
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		a=(rand()%9)+1;
		obtenerPregunta(pre, a, pregunta, respuesta);
		printf("\n                            PREGUNTA/QUESTION");
		printf("\n\n     %s    ", pregunta);
		gets(respuestaJugador);
		fflush(stdin);
		if ((strcmp(respuesta,respuestaJugador))!=0)
		{
			*posicion=6;
			printf("\n     Respuesta incorrecta, retrocede a la casilla %d", *posicion);
			getch();
		}
		else{
			printf("\n     Respuesta Correcta, permanece en casilla %d", *posicion);
			getch();}
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA %d: %s", *posicion, nombreJugador);
		printf("\n\n     Ahora se encuentra en la casilla %d", *posicion);
	    }
	if (*posicion==13){
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA 13: %s", nombreJugador);
		*posicion=17;
		printf("\n\n     Jugador %s avanza a la casilla %d", nombreJugador, *posicion);
        getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA %d: %s", *posicion, nombreJugador);
		printf("\n\n     Ahora se encuentra en la casilla %d", *posicion);
	    }
	if (*posicion==16){
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA 16: %s", nombreJugador);
		printf("\n\n     Responda correctamente para permanecer en la casilla");
		getch();
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		a=(rand()%9)+1;
		obtenerPregunta(pre, a, pregunta, respuesta);
		printf("\n                                PREGUNTA/QUESTION");
		printf("\n\n     %s    ", pregunta);
		gets(respuestaJugador);
		fflush(stdin);
		if ((strcmp(respuesta,respuestaJugador))!=0)
		{
			*posicion=14;
			printf("\n     Respuesta Incorrecta, retrocede a la casilla %d", *posicion);
			getch();
		}
		else{
			printf("\n     Respuesta Correcta, permanece en casilla %d", *posicion);
			getch();}
		system("cls");
        dibujaTablero(tamTablero, *posicion1, *posicion2);
		printf("\n                              CASILLA %d: %s", *posicion, nombreJugador);
		printf("\n\n     Ahora se encuentra en la casilla %d", *posicion);
	    }
}

int salirBarra()
{
	char espacio;
	int seleccion=1;
	if ((espacio=getch())==' '){//SI PRESIONO BARRA ESPACIADORA
	    do{
	        printf("\n\n     Desea continuar SI:teclee 1  NO:teclee 2 :");
	        scanf("%d", &seleccion);
	    }while((seleccion!=1)&&(seleccion!=2));//MENSAJE SE REPITE SI SE TECLEA ALGO DIFERENTE
	}
	// if (seleccion==2)
	// 	return 2;//salir del juego
	// else
	//     return 1;
	return seleccion;

}

/*
*  Procedimiento: guardarJugadores
*  Uso: guardarJugadores(juego, nombre);
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Procedimiento q guarda en un archiivo de texto los nombres de los ganadores
*/
void guardarJugadores(FILE *top, char jugador[30], int anio, int mes, int dia)
{
	if(!(top)){
		system("cls");
		printf("\n\n\tError al abrir el archivo");
		getch();
	} else
	{ 
		fputs(jugador, top);//escribe un string en *top
	    fprintf(top, "    %d/%d/%d", dia, mes, anio);
	    fputc('\n', top);//escribe un caracter en *top
	}
	rewind(top);//ubicando puntero a inicio de archivo para una proxima lectura o escritura
}


/*
*  Procedimiento: declararGanador
*  Uso: declararGanador(nombre);
*  ----------------------------------------------------------------------------------------------------------------
*  Descripcion: Procedimiento q recibe la cadena que contiene el nombre dl ganador e imprime felicitaciones
*/
void declararGanador(char *nombre)
{
	system("cls");
	printf("\n\n\t  Felicitaciones %s por ganar el juego", nombre);
    getch();
}

void obtenerPregunta(FILE *archPreg, int numAleatorio, char * pregunta, char * respuesta)
{
	char punto[2]="";
	//char punto="";//warning debido a q hay dos caracteres dos comillas
	int i=0;
    if (archPreg==NULL)
		printf("Error al abrir el archivo");//en caso de que no exista
	else
	{
		for (i=0; i<numAleatorio; i++)
		      fscanf(archPreg, "%c%[^,], %s\n",&punto, pregunta, respuesta);
		fclose(archPreg);
	}
}