#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void PARTICIONADO(void);
void CREAR_LISTA(void);
void VER_LISTA(void);

struct nodo_lista
{
	int noBloque, capacidad, locIncial, locFinal, estado, acceso;
	nodo_lista *sig;
};

nodo_lista *Plista, *Qlista, *Nuevolista, *Aux;

int main()
{
	Plista = NULL;
	Qlista = NULL;
	CREAR_LISTA();
	VER_LISTA();
	getch();
}

void PARTICIONADO(void){
	
}

void CREAR_LISTA(void)
{
	int nuevo_elemento, r;
	do
	{
		if (Plista == NULL)
		{
			Plista = (nodo_lista *) malloc(sizeof(nodo_lista));
			printf("Ingresa el No bloque: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> noBloque = nuevo_elemento;
			printf("Ingresa capacidad: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> capacidad = nuevo_elemento;
			printf("Ingresa locIncial: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> locIncial = nuevo_elemento;
			printf("Ingresa locFinal: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> locFinal = nuevo_elemento;
			printf("Ingresa el estado: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> estado = nuevo_elemento;
			printf("Ingresa acceso: ");
			scanf ("%d", &nuevo_elemento);
			Plista -> acceso = nuevo_elemento;
			
			Plista -> sig = NULL;
			Qlista = Plista;
		}
		else
		{
			Nuevolista = (nodo_lista *) malloc(sizeof(nodo_lista));
			
			printf("Ingresa el bloque: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> noBloque = nuevo_elemento;
			printf("Ingresa capacidad: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> capacidad = nuevo_elemento;
			printf("Ingresa locIncial: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> locIncial = nuevo_elemento;
			printf("Ingresa locFinal: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> locFinal = nuevo_elemento;
			printf("Ingresa el estado: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> estado = nuevo_elemento;
			printf("Ingresa acceso: ");
			scanf ("%d", &nuevo_elemento);
			Nuevolista -> acceso = nuevo_elemento;
			
			Nuevolista->sig=NULL;
			Qlista->sig=Nuevolista;
			Qlista=Nuevolista;
		}
	printf("\nDesea ingresar otro elemento (1=si/0=no)");
	scanf("%d",&r);
	}while(r==1);
}

void VER_LISTA(void){
	Aux=Plista;
	printf("\n|%-10s| |%-10s| |%-10s| |%-10s| |%-10s| |%-10s|", "NoBloque","Capacidad","locInicial","locFinal","Estado","Acceso");
	while(Aux!=NULL){
		printf("\n-----------------------------------------------------------------------------");
		printf("\n|%-10d| |%-10d| |%-10d| |%-10d| |%-10d| |%-10d|",Aux->noBloque,Aux->capacidad,Aux->locIncial,Aux->locFinal,Aux->estado,Aux->acceso);
		Aux=Aux->sig;
	}	
}

