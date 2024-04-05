#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//#define tamSistema 20000
#define maxMemoria 80 * 1024
#define tareas 20

//void Particionado(void);
void Crear_MT(void);
void Crear_JT(void);
void Imprimir_Tablas(void);

struct nodo_MT//Memory table
{
	int noBloque, capacidad, locIncial, locFinal, estado, acceso;// en nbloque poner B y el contador concatenado;
	nodo_MT *sig;
};

struct nodo_JT//job table
{
	int ntarea;//imprimir J y el numero contador concatenado
	int nespacio;//aleatorio de 5 a 15 para las kb 5+rand()%15
	nodo_JT *sig;
};

//Aleatorio de 5 a 15 con 10 o 20 tareas

nodo_MT *P_MT, *Q_MT, *Nuevo_MT, *Aux_MT;
nodo_JT *P_JT, *Q_JT, *Nuevo_JT, *Aux_JT;

int main()
{
	P_MT = NULL;
	Q_MT = NULL;
	Crear_MT();
	Crear_JT();
	Imprimir_Tablas();
	getch();
}

/*void Particionado(void){
	
}*/

void Crear_MT(void)
{
	int espacioSolicitado, r=1, cont=1;
	do
	{
		if (P_MT == NULL)
		{
			P_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
			P_MT -> noBloque = 0;
			P_MT -> capacidad = 20*1024/*1kbytes*/;
			P_MT -> locIncial = 0;
			P_MT -> locFinal = P_MT -> capacidad - 1;
			P_MT -> estado = 0;//ocupado
			P_MT -> acceso = NULL;
			
			P_MT -> sig = NULL;
			Q_MT = P_MT;
		}
		else
		{
			printf("\nDesea crear una nueva particion? (1=si 0=no): ");
			scanf("%d",&r); if(r==0){break;}
			
			Nuevo_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
			
			printf("\nIngresa la capacidad (en kilobytes) de la particion %d: ",cont);
			scanf ("%d", &espacioSolicitado);
			
			int espacioOcupado=0;
			Aux_MT=P_MT;
			while(Aux_MT!=NULL){
				espacioOcupado+=Aux_MT->capacidad;
				Aux_MT=Aux_MT->sig;
			}
			
			if(maxMemoria-espacioOcupado>=espacioSolicitado*1024){
				printf("\nParticion creada con exito, quedan: %d KiloBytes libres",maxMemoria-(espacioOcupado+espacioSolicitado*1024));
				Nuevo_MT -> noBloque = cont;
				Nuevo_MT -> capacidad = espacioSolicitado*1024;
				Nuevo_MT -> locIncial = Q_MT->locFinal+1;
				Nuevo_MT -> locFinal = Nuevo_MT -> locIncial + espacioSolicitado*1024;
				Nuevo_MT -> estado = 1;
				Nuevo_MT -> acceso = 0;
				
				Nuevo_MT->sig=NULL;
				Q_MT->sig=Nuevo_MT;
				Q_MT=Nuevo_MT;
				cont++;
			}
			else{
				printf("\nError: No se pudo crear la particion, quedan: %d KiloBytes libres",maxMemoria-(espacioOcupado+espacioSolicitado));
			}
		}
	}while(r==1);
}

void Crear_JT(void){
	int espacioSolicitado, r=1, cont=1;
	do
	{
		if (P_JT == NULL)
		{
			P_JT = (nodo_JT *) malloc(sizeof(nodo_JT));
			P_JT -> noBloque = 0;
			P_JT -> capacidad = 20*1024/*1kbytes*/;
			P_JT -> locIncial = 0;
			P_JT -> locFinal = P_JT -> capacidad - 1;
			P_JT -> estado = 0;//ocupado
			P_JT -> acceso = NULL;
			
			P_JT -> sig = NULL;
			Q_JT = P_JT;
		}
		else
		{
			printf("\nDesea crear una nueva particion? (1=si 0=no): ");
			scanf("%d",&r); if(r==0){break;}
			
			Nuevo_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
			
			printf("\nIngresa la capacidad (en kilobytes) de la particion %d: ",cont);
			scanf ("%d", &espacioSolicitado);
			
			int espacioOcupado=0;
			Aux_MT=P_MT;
			while(Aux_MT!=NULL){
				espacioOcupado+=Aux_MT->capacidad;
				Aux_MT=Aux_MT->sig;
			}
			
			if(maxMemoria-espacioOcupado>=espacioSolicitado*1024){
				printf("\nParticion creada con exito, quedan: %d KiloBytes libres",maxMemoria-(espacioOcupado+espacioSolicitado*1024));
				Nuevo_MT -> noBloque = cont;
				Nuevo_MT -> capacidad = espacioSolicitado*1024;
				Nuevo_MT -> locIncial = Q_MT->locFinal+1;
				Nuevo_MT -> locFinal = Nuevo_MT -> locIncial + espacioSolicitado*1024;
				Nuevo_MT -> estado = 1;
				Nuevo_MT -> acceso = 0;
				
				Nuevo_MT->sig=NULL;
				Q_MT->sig=Nuevo_MT;
				Q_MT=Nuevo_MT;
				cont++;
			}
			else{
				printf("\nError: No se pudo crear la particion, quedan: %d KiloBytes libres",maxMemoria-(espacioOcupado+espacioSolicitado));
			}
		}
	}while(r==1);
}

void Imprimir_Tablas(void){
	Aux_MT=P_MT;
	printf("\n|%-10s| |%-10s| |%-10s| |%-10s| |%-10s| |%-10s|", "NoBloque","Capacidad","locInicial","locFinal","Estado","Acceso");
	while(Aux_MT!=NULL){
		printf("\n-----------------------------------------------------------------------------");
		printf("\n|B%-10d| |%-8dBytes| |%-8dBytes| |%-8dBytes| |%-10d| |%-10d|",Aux_MT->noBloque,Aux_MT->capacidad,Aux_MT->locIncial,Aux_MT->locFinal,Aux_MT->estado,Aux_MT->acceso);
		Aux_MT=Aux_MT->sig;
	}	
}

