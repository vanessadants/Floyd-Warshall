//author:Vanessa Dantas de Souto Costa
//n é o número de vertices do grafo
//D nxn matriz representando os pesos do grafo

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cfloat> 
#include <cstring> 
#include <iomanip>

#define MAX 100
using namespace std;


void print(double D[][MAX], int n){
	int i,j;
	cout<<"n = "<<n<<endl;
	cout<<"D = \n";
	for (i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(D[i][j]==DBL_MAX){
				cout<<setw(15)<<"INF";
			}else{
				cout<<setw(15)<<D[i][j];
			}
		}
		cout<<endl;
	}

}

void read(char *fileName, double D[][MAX], int & n){
	int i,j;
	ifstream arq;
	arq.open(fileName);
	if (arq.is_open()){
		cout<<"reading file "<<fileName<<"...\n";
		arq>>n;
		char aux[MAX];
		for (i=0;i<n;i++){
			for(j=0;j<n;j++){
				arq>>aux;
				if(strcasecmp(aux,"INF")==0){
					D[i][j]=DBL_MAX;
				}else{
					D[i][j]=atof(aux);
				}

			}
		}
		arq.close();
		cout << "Done\n";
	}else{
		cout << "Unable to open file "<<fileName<<"\n";
		exit(0);
	}
	

}

void write(char *fileName, double D[][MAX], int n, bool negCycle){
	int i,j;
	ofstream arq;
	arq.open(fileName);
	if (arq.is_open()){
		cout<<"writing file "<<fileName<<"...\n";
		//salvando o número de vertices
		arq<<"n = "<<n<<endl;
		//salvando a matriz com as distâncias D
		arq<<"D = \n";
		for (i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(D[i][j]==DBL_MAX){
					arq<<setw(15)<<"INF";
				}else{
					arq<<setw(15)<<D[i][j];
				}
			}
			arq<<endl;
		}
		if(negCycle){
			arq<<"This graph contains negative cycles.\n";
		}else{
			arq<<"This graph doesn't contain negative cycles.\n";
		}
		arq.close();
		cout << "Done\n";
	}else{
		cout << "Unable to open file "<<fileName<<"\n";
		exit(0);
	}
}


void floydWarshall(double D[][MAX], int n){
	int i,j,k;
	for(k=0;k<n;k++){
		for (i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(D[i][j]>D[i][k]+D[k][j]){
					D[i][j]=D[i][k]+D[k][j];
				}
			}
		}
	}
}

bool negCyclefloydWarshall(double D[][MAX], int n) 
{ 
    // Se a distancia para qualquer vertice 
    // para ele mesmo se tornar negativa
    // contém ciclo negativo
    int i;
    for (i = 0; i < n; i++){ 
        if (D[i][i] < 0){ 
            return true; 
        }
    }
    return false;  
} 

int main(int argc, char **argv){
	int n;
	double D[MAX][MAX]={};
	bool negCycle;

	read(argv[1],D,n);
	cout<<"Before Floyd Warshall\n";
	print(D,n);
	floydWarshall(D,n);
	cout<<"After Floyd Warshall\n";
	print(D,n);

	negCycle=negCyclefloydWarshall(D,n);
	if(negCycle){
		cout<<"This graph contains negative cycles.\n";
	}else{
		cout<<"This graph doesn't contain negative cycles.\n";
	}
	write("saida.txt", D, n,negCycle);
	exit(0);
}