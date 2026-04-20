#include <stdio.h>
#include <limits.h> //INT_MAX
 
#define MAXN 50 //quantidade de elementos
#define MAXK 20 //quantidade de partições
#define MAXINT INT_MAX
 
int max(int, int); //acha maior número
void mostrar(int s[], int start, int end); //mostra os elementos da lista
void reconstrucao(int[], int[MAXN+1][MAXK+1], int, int); //faz a reconstrução das partições
void particionar(int[], int, int); //particiona a lista
 
int max(int a, int b) {
    int maior;
    if(a>b){
        maior = a;
    } else {
        maior = b;
    }
    return maior;
}
 
void particionar(int s[], int n, int k) {
    int m[MAXN+1][MAXK+1]; /* tabela DP para valores */
    int d[MAXN+1][MAXK+1]; /* tabela DP para as divisórias */
    int p[MAXN+1];         /* lista de somas prefixadas */
    int cost;
    int i, j, x;

    //calculando somas prefixadas
    p[0] = 0;
    for (i=1; i<=n; i++)
        p[i] = p[i-1] + s[i];

    //casos base
    for (i=1; i<=n; i++)
        m[i][1] = p[i]; // caso base: 1 partição
    for (j=1; j<=k; j++)
        m[1][j] = s[1]; // caso base: só 1 elemento

    //construindo tabela DP
    for (i=2; i<=n; i++) {
        for (j=2; j<=k; j++) {
            m[i][j] = MAXINT;
            for (x=1; x<=(i-1); x++) {
                cost = max(m[x][j-1], p[i]-p[x]);
                if (cost < m[i][j]) { // se o custo achado for menor que o ultimo calculado
                    m[i][j] = cost;
                    d[i][j] = x; // lugar de corte
                }
            }
        }
    }
    reconstrucao(s, d, n, k); // acha as partições
}

 
void reconstrucao(int s[], int d[MAXN+1][MAXK+1], int n, int k) {
    if (k == 1) {
        mostrar(s, 1, n);
    } else { 
        reconstrucao(s, d, d[n][k], k-1); // índice d[n][k] é onde a partição k-1 termina
        mostrar(s, d[n][k]+1, n);
    }
}

 
void mostrar(int s[], int start, int end) {
    int i;
    for (i=start; i<=end; i++) {
        printf(" %d ", s[i]);
    }
    printf("\n");
}
 
 
int main() {

    //usar posiçoes a partir do índice 1
    int s[] = {0, 15, 30, 10, 15, 45, 6, 13, 40, 60};

    int n = 9;// quantidade de elementos na lista
    int k = 3; //número de partições

    printf("\nPROGRAMA DE SEPARAÇÃO DE LISTA EM PARTIÇÕES\n");
    printf("\nSeparar lista: ");

    for(int i = 1; i <= n; i++){
        printf("\t%d", s[i]);
    }

    printf("\nElementos: %d\nPartes: %d", n, k);
    printf("\n\n");
    particionar(s, n, k);
    printf("\n\n");
    return 0;
}