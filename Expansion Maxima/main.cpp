#include <iostream>
using namespace std;

#define maxn 110
#define INF 0xffffff
int w[maxn][maxn] ; // fila columna
bool check[maxn] ;
int nNodos ; // numero de vertices
int nAristas ; // numero de Aristas

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

int main(int argc, char** argv) {
	
	int menor, pos, newPos ;
	int camino[maxn] ; 
	int tocados = 0 , llegada = 0 ;
	
	printf ( "iniciando ...\n" ) ;

	LeerEntrada() ;
	
	//inicializar checks
	for ( int i = 0; i < nNodos; i++ ) {
		check[i] = false ;
	}
	
	
	// primer paso busco el menor de la primer columna
	menor = INF ;
	for ( int i = 1; i < nNodos; i ++ ) {
		//menor = EsMenor( w[0][i], menor ) ;
		if ( w[0][i] < menor ) {
			menor = w[0][i] ;
			newPos = i ;
		}
	}
	pos = newPos ;
	camino[tocados] = pos ; tocados++ ;
	check[pos] = true ;
	printf ( "en la primer columna el menor es %d correspondiente a la fila %d\n", menor, pos+1 ) ;
	
	//segundo paso voy a la columna que me indicaba era el menor en el paso uno
	//le sumo a toda la columna el peso del menor
	while ( pos < nNodos -1 ) {
		
		printf ( "ahora en la columna %d los valores son:\n", pos+1 ) ;
		for (int i = 1; i < nNodos; i ++ ) {
			w[pos][i] += menor ;
			printf ("%d\n", w[pos][i] ) ;
			/*if ( nNodos-1 == i ) {
				printf ( "el peso %d es de la fila %d en columna %d\n",w[pos][i] ,i, pos ) ; 
			}*/			
		}
		
		menor = INF ;
		for ( int i = 1; i < nNodos ; i ++ ) {
			if ( w[pos][i] < menor ) {
				if ( check[i] == false ) {
					menor = w[pos][i] ;
					newPos = i ;
				}
			}	
		}
		pos = newPos ;
		printf ( "ahora el menor es %d de la fila %d\n", menor, pos+1) ;		
		check[pos] = true ;
		camino[tocados] = pos ;
		llegada = camino[tocados-1] ;
		tocados++ ;
	}	
	
	//nuevo: verifico si no había otro camino mas corto en la fila nNodos-1 (final)
	//de los que ya hallan sido checkeados 
	for ( int i = 0 ; i < nNodos-1; i ++ ) {
		if ( w[i][nNodos-1] < menor  && check[i] == true ) {
			menor = w[i][nNodos-1] ;
			llegada = i ;
		}
	}
	
	printf ( "el menor de los recorridos es: %d\n", menor ) ;
	//for ( int i = 0 ; i <= tocados ; i++ ) {
	int i = 0 ; bool fin = false ;
	printf ( "recorrido: " ) ;
	while ( i <= tocados && fin == false ) {
		printf ( "%d ", camino[i] ) ;
		if ( llegada == camino[i] ) fin = true ;
		i++ ;	
	}
	printf ( "%d\n", nNodos-1 ) ;
	system ( "pause" ) ;
	return 0;
}

void LeerEntrada () {
	printf ( "Leyendo datos...\n" ) ;
	
	printf ( "ingrese el numero de nodos: " ) ;
	scanf ( "%d", &nNodos ) ;
	
	printf ( "ingrese el numero de aristas: " ) ;
	scanf ( "%d", &nAristas ) ;
	
	//inicializo la matriz a 0 ( porque 0 será el menor )
	for ( int i = 0; i < nAristas; i++ ) {
		for ( int j = 0; j < nAristas; j++ ) {
			w[i][j] = 99 ;
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
