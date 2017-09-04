#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>


#define maxn 110
#define INF 0
int w[maxn][maxn] ; // fila columna
bool check[maxn] ;
int nNodos ; // numero de vertices
int nAristas ; // numero de Aristas
int partida ; // nodo de partida

int a, b, peso ;
void LeerEntrada () ;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/* todo
   cargar toda la información
   seleccionar el punto de partida
   agregar el punto de partida a los puntos de salida
   elegir de los puntos de salida disponibles las aristas de mayor peso
   agregar el nodo a los puntos de de salida
   continuar hasta completar todos los nodos
*/


 int _tmain(int argc, _TCHAR* argv[]) 
{
	int mayor, pos, newPos ;
	int camino[maxn] ;
	int tocados = 0 , llegada = 0 ;

	printf ( "iniciando ...\n" ) ;

	LeerEntrada() ;

	printf ( "indica el nodo de partida:\n" ) ;
	scanf ( "%d", &partida ) ;

	//inicializar checks
	for ( int i = 0; i < nNodos; i++ ) {
		check[i] = false ;
	}

	check[partida -1 ] = true ;

	// primer paso busco el mayor de la primer columna
	mayor = INF ;
	for ( int i = 0; i < nNodos; i ++ ) {
		//mayor = Esmayor( w[0][i], mayor ) ;
		if ( w[partida -1][i] > mayor ) {
			mayor = w[partida -1][i] ;
			newPos = i ;
		}
	}
	pos = newPos ;
	camino[tocados] = pos ; tocados++ ;
	check[pos] = true ;
	printf ( "en la primer columna el mayor es %d correspondiente a la fila %d\n", mayor, pos+1 ) ;

	//segundo paso voy a la columna que me indicaba era el mayor en el paso uno
	//le sumo a toda la columna el peso del mayor
	while ( pos < nNodos -1 ) {

		printf ( "ahora en la columna %d los valores son:\n", pos+1 ) ;
		for (int i = 1; i < nNodos; i ++ ) {
			w[pos][i] += mayor ;
			printf ("%d\n", w[pos][i] ) ;
			/*if ( nNodos-1 == i ) {
				printf ( "el peso %d es de la fila %d en columna %d\n",w[pos][i] ,i, pos ) ;
			}*/
		}

		mayor = INF ;
		for ( int i = 1; i < nNodos ; i ++ ) {
			if ( w[pos][i] < mayor ) {
				if ( check[i] == false ) {
					mayor = w[pos][i] ;
					newPos = i ;
				}
			}
		}
		pos = newPos ;
		printf ( "ahora el mayor es %d de la fila %d\n", mayor, pos+1) ;
		check[pos] = true ;
		camino[tocados] = pos ;
		llegada = camino[tocados-1] ;
		tocados++ ;
	}

	//nuevo: verifico si no había otro camino mas corto en la fila nNodos-1 (final)
	//de los que ya hallan sido checkeados
	for ( int i = 0 ; i < nNodos-1; i ++ ) {
		if ( w[i][nNodos-1] < mayor  && check[i] == true ) {
			mayor = w[i][nNodos-1] ;
			llegada = i ;
		}
	}

	printf ( "el mayor de los recorridos es: %d\n", mayor ) ;
	//for ( int i = 0 ; i <= tocados ; i++ ) {
	int i = 0 ; bool fin = false ;
	printf ( "recorrido: " ) ;
	while ( i <= tocados && fin == false ) {
		printf ( "%d ", camino[i] ) ;
		if ( llegada == camino[i] ) fin = true ;
		i++ ;
	}
	printf ( "%d\n", nNodos-1 ) ;
	return 0;
}

void LeerEntrada () {
	printf ( "Leyendo datos...\n" ) ;

	printf ( "ingrese el numero de nodos: " ) ;
	scanf ( "%d", &nNodos ) ;

	printf ( "ingrese el numero de aristas: " ) ;
	scanf ( "%d", &nAristas ) ;

	//inicializo la matriz a 0 ( porque 0 será el mayor )
	for ( int i = 0; i < nAristas; i++ ) {
		for ( int j = 0; j < nAristas; j++ ) {
			w[i][j] = 0 ;
		}
	}

	for ( int i = 0; i < nAristas; i++ ) {
		printf ( "ingrese nodo a, b y peso: " ) ;  // ingreso por archivo
		scanf ( "%d%d%d", &a, &b, &peso) ;
		//w[a-1][b-1] = peso ;
		w[a - 1][b - 1] = peso ;
		w[b - 1][a - 1] = peso ;
	}
}
