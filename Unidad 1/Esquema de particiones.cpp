#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define espacioSO 20 /** 1024*/// 1kb = 1024 bytes
#define maxMemoria 250 /** 1024*/
#define ntareas 20

void Crear_MT(void);
void Crear_JT(void);
void Imprimir_Tabla_Memoria(void);
void Imprimir_Tabla_Tareas(void);

void primerAjuste();
void mejorAjuste();
void peorAjuste();

void Ordenamiento_Y_Ajuste(char);

struct nodo_MT//Memory table
{
	int noBloque, capacidad, locIncial, locFinal, estado, acceso, frag;// en nbloque poner B y el contador concatenado;
	nodo_MT *sig;
};

void intercambiarNodos(nodo_MT *, nodo_MT *);
int nBloques;

struct nodo_JT//job table
{
	int ntarea;//imprimir J y el numero contador concatenado
	int nespacio;//aleatorio de 5 a 15 para las kb 5+rand()%15
	nodo_JT *sig;
};

//Aleatorio de 5 a 15 con 10 o 20 tareas

nodo_MT *P_MT, *Q_MT, *Nuevo_MT, *Aux_MT, *Aux2_MT, *Pivote;
nodo_JT *P_JT, *Q_JT, *Nuevo_JT, *Aux_JT;

int main()
{
	P_MT = NULL;
	Q_MT = NULL;
	Crear_MT();
	Crear_JT();
	nBloques=Q_MT->noBloque;
	primerAjuste();
	//mejorAjuste();
	//peorAjuste();
	Imprimir_Tabla_Memoria();
	Imprimir_Tabla_Tareas();
	getch();
}

void Crear_MT(void)
{
	int espacioSolicitado, r=1, cont=1;
	do
	{
		if (P_MT == NULL)
		{
			P_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
			P_MT -> noBloque = 0;
			P_MT -> capacidad = espacioSO;
			P_MT -> locIncial = 0;
			P_MT -> locFinal = P_MT -> capacidad - 1;
			P_MT -> estado = 0;//ocupado
			P_MT -> acceso = NULL;
			P_MT -> frag = 0;
			
			P_MT -> sig = NULL;
			Q_MT = P_MT;
		}
		else
		{
			printf("\nDesea crear una nueva particion? (1=si 0=no): ");
			scanf("%d",&r); 
			if(r==0)
			{
				Nuevo_MT = (nodo_MT *) malloc(sizeof(nodo_MT));

				int espacioOcupado=0;
				Aux_MT=P_MT;
				while(Aux_MT!=NULL){
					espacioOcupado+=Aux_MT->capacidad;
					Aux_MT=Aux_MT->sig;
				}
				
				Nuevo_MT -> noBloque = cont;
				Nuevo_MT -> capacidad = maxMemoria-espacioOcupado;
				Nuevo_MT -> locIncial = Q_MT->locFinal+1;
				Nuevo_MT -> locFinal = maxMemoria;
				Nuevo_MT -> estado = 1;
				Nuevo_MT -> acceso = 0;
				Nuevo_MT -> frag = 0;
				
				Nuevo_MT->sig=NULL;
				Q_MT->sig=Nuevo_MT;
				Q_MT=Nuevo_MT;
				cont++;
				break;break;
			}
			
			
			Nuevo_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
			
			printf("\nIngresa la capacidad (en kilobytes) de la particion %d: ",cont);
			scanf ("%d", &espacioSolicitado);
			
			int espacioOcupado=0;
			Aux_MT=P_MT;
			while(Aux_MT!=NULL){
				espacioOcupado+=Aux_MT->capacidad;
				Aux_MT=Aux_MT->sig;
			}
			
			if(maxMemoria-espacioOcupado>=espacioSolicitado/**1024*/){
				printf("\n\tParticion creada con exito, quedan: %d KiloBytes libres\n",maxMemoria-(espacioOcupado+espacioSolicitado/**1024*/));
				Nuevo_MT -> noBloque = cont;
				Nuevo_MT -> capacidad = espacioSolicitado/**1024*/;
				Nuevo_MT -> locIncial = Q_MT->locFinal+1;
				Nuevo_MT -> locFinal = Nuevo_MT -> locIncial + espacioSolicitado/**1024*/;
				Nuevo_MT -> estado = 1;
				Nuevo_MT -> acceso = 0;
				Nuevo_MT -> frag = 0;
				
				Nuevo_MT->sig=NULL;
				Q_MT->sig=Nuevo_MT;
				Q_MT=Nuevo_MT;
				cont++;
			}
			else{
				printf("\n\tError: No se pudo crear la particion, quedan: %d KiloBytes libres\n",maxMemoria-(espacioOcupado+espacioSolicitado));
			}
		}
	}while(r==1);
}

void Crear_JT(void){
	int i=ntareas,cont=2;
	do
	{
		if (P_JT == NULL)
		{
			P_JT = (nodo_JT *) malloc(sizeof(nodo_JT));
			P_JT -> ntarea = 1;
			P_JT -> nespacio = /*1024**/(15+rand()%36);
			P_JT -> sig = NULL;
			Q_JT = P_JT;
		}
		else
		{			
			Nuevo_JT = (nodo_JT *) malloc(sizeof(nodo_JT));
			
			Nuevo_JT -> ntarea = cont;
			Nuevo_JT -> nespacio = /*1024**/(15+rand()%36);//de 15 a 50

			Nuevo_JT->sig=NULL;
			Q_JT->sig=Nuevo_JT;
			Q_JT=Nuevo_JT;
			cont++;
		}
		i--;
	}while(i>=0);
}
//nodo_MT *P_MT, *Q_MT, *Nuevo_MT, *Aux_MT;
//nodo_JT *P_JT, *Q_JT, *Nuevo_JT, *Aux_JT;

void intercambiarNodos(nodo_MT *A, nodo_MT *B){
	nodo_MT *Temp;
	Temp = (nodo_MT *) malloc(sizeof(nodo_MT));
	//De A a Temp
	Temp->acceso = A->acceso;Temp->capacidad = A->capacidad;Temp->estado = A->estado;
	Temp->frag = A->frag;Temp->locFinal = A->locFinal;Temp->locIncial = A->locIncial;Temp->noBloque = A->noBloque;
	//De B para A
	A->acceso = B->acceso;A->capacidad = B->capacidad;A->estado = B->estado;
	A->frag = B->frag;A->locFinal = B->locFinal;A->locIncial = B->locIncial;A->noBloque = B->noBloque;
	//De Temp a B
	B->acceso = Temp->acceso;B->capacidad = Temp->capacidad;B->estado = Temp->estado;
	B->frag = Temp->frag;B->locFinal = Temp->locFinal;B->locIncial = Temp->locIncial;B->noBloque = Temp->noBloque;
	free(Temp);//se elimina la memoria de Temp
}

void primerAjuste(){
	Aux_JT=P_JT;
	int bloquesDisponibles=nBloques;
	Pivote = (nodo_MT *) malloc(sizeof(nodo_MT));
	Pivote = P_MT;
	while(bloquesDisponibles>0 && Aux_JT!=NULL){
		Aux_MT=Pivote->sig;
		while(Aux_MT!=Pivote){
			if(Aux_JT->nespacio <= Aux_MT->capacidad && Aux_MT->estado==1){
				Aux_MT->acceso = Aux_JT->ntarea;
				Aux_MT->estado = 0;
				Aux_MT->frag = Aux_MT->capacidad -  Aux_JT->nespacio;
				bloquesDisponibles--;
				Pivote = Aux_MT;
				break;
			}
			if(Aux_MT==Q_MT){
				Aux_MT=P_MT->sig;
			}
			else{
				Aux_MT=Aux_MT->sig;
			}
		}
		Aux_JT=Aux_JT->sig;
	}

}

void mejorAjuste(){
	Ordenamiento_Y_Ajuste('C');//Creciente
}
/*
void mejorAjuste(void){
	int particionesLibres = Q_MT -> noBloque;
	int capUltimoBloque=0;
	Aux_JT = P_JT;
	Pivote = (nodo_MT *) malloc(sizeof(nodo_MT));
	Aux_MT = P_MT -> sig;
	Pivote = Aux_MT;
	while(Aux_MT->sig!=NULL){
		if(Aux_MT->capacidad < Pivote->capacidad && Aux_MT->estado == 0 && Aux_MT->capacidad > capUltimoBloque){
			Pivote = Aux_MT;
			capUltimoBloque = Aux_MT->capacidad;
		}
	}
	
	if(Aux_JT->nespacio <= Pivote->capacidad){
		Pivote->acceso=Aux_JT->ntarea;
		Pivote->estado=1;
		Aux_JT=Aux_JT->sig;
	}
}
*/
void peorAjuste(){
	Ordenamiento_Y_Ajuste('D');//Decreciente
}
void Ordenamiento_Y_Ajuste(char op){
	int inter;
	Aux2_MT = (nodo_MT *) malloc(sizeof(nodo_MT));
	//Ordenamiento mediante el metodo de intercambio
	do{ 
		inter=0;
		Aux_MT=P_MT->sig; 
		while (Aux_MT->sig != NULL) {
            Aux2_MT = Aux_MT->sig;
            if (Aux_MT->capacidad  > Aux2_MT->capacidad && op=='C') {
                // Intercambiar los valores de los nodos
				intercambiarNodos(Aux_MT, Aux2_MT);
                inter = 1; // Se realizó un intercambio, por lo tanto, la lista aún no está ordenada completamente
            }
            else if (Aux_MT->capacidad  < Aux2_MT->capacidad && op=='D') {
                // Intercambiar los valores de los nodos
				intercambiarNodos(Aux_MT, Aux2_MT);
                inter = 1; // Se realizó un intercambio, por lo tanto, la lista aún no está ordenada completamente
            }
            Aux_MT = Aux2_MT;
        }
	}while (inter);
	
	Aux_JT=P_JT;
	int bloquesDisponibles=nBloques;
	while(bloquesDisponibles>0 && Aux_JT!=NULL){
		Aux_MT=P_MT->sig;
		while(Aux_MT!=NULL){
			if(Aux_JT->nespacio <= Aux_MT->capacidad && Aux_MT->estado==1){
				Aux_MT->acceso = Aux_JT->ntarea;
				Aux_MT->estado = 0;
				Aux_MT->frag = Aux_MT->capacidad -  Aux_JT->nespacio;
				bloquesDisponibles--;
				break;
			}
			Aux_MT=Aux_MT->sig;
		}
		Aux_JT=Aux_JT->sig;
	}
}

//IMPRESION DE LA TABLA SIN EL ORDENAMIENTO INTERNO
void Imprimir_Tabla_Memoria(void){
	printf("\n\n--------------------------------------------------------------------------------------------\n|%-90s|\n--------------------------------------------------------------------------------------------","TABLA DE MEMORIA");
	printf("\n|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|", "NoBloque","Capacidad","locInicial","locFinal","Estado","Acceso","FI");
	for(int i=0; i<=nBloques; i++){
		Aux_MT=P_MT;
		while(Aux_MT!=NULL){
			if(i==Aux_MT->noBloque){
				printf("\n--------------------------------------------------------------------------------------------");
				printf("\n|B%-11d|%-3d KB|%-12d|%-12d|%-12d|%-12d|%-12d|",Aux_MT->noBloque,Aux_MT->capacidad,Aux_MT->locIncial,Aux_MT->locFinal,Aux_MT->estado,Aux_MT->acceso,Aux_MT->frag);
			}
			Aux_MT=Aux_MT->sig;
		}
	}
	printf("\n--------------------------------------------------------------------------------------------");	
}

/*
//IMPRESION DEL ORDENAMIENTO INTERNO DE LA TABLA 
void Imprimir_Tabla_Memoria(void){
	Aux_MT=P_MT;
	printf("\n\n--------------------------------------------------------------------------------------------\n|%-90s|\n--------------------------------------------------------------------------------------------","TABLA DE MEMORIA");
	printf("\n|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|%-12s|", "NoBloque","Capacidad","locInicial","locFinal","Estado","Acceso","FI");
	while(Aux_MT!=NULL){
		printf("\n--------------------------------------------------------------------------------------------");
		printf("\n|B%-11d|%-6d bytes|%-12d|%-12d|%-12d|%-12d|%-12d|",Aux_MT->noBloque,Aux_MT->capacidad,Aux_MT->locIncial,Aux_MT->locFinal,Aux_MT->estado,Aux_MT->acceso,Aux_MT->frag);
		Aux_MT=Aux_MT->sig;
	}
	printf("\n--------------------------------------------------------------------------------------------");
}*/

void Imprimir_Tabla_Tareas(void){
	Aux_JT=P_JT;
	printf("\n\n-------------------------\n|%-23s|\n-------------------------","TABLA DE TAREAS");
	printf("\n|%-10s|%-12s|","Numero","Espacio");
	while(Aux_JT->sig!=NULL){
		printf("\n-------------------------");
		printf("\n|J%-9d|%-9d KB|",Aux_JT->ntarea,Aux_JT->nespacio);
		Aux_JT=Aux_JT->sig;
	}
	printf("\n-------------------------");
	/*Aux_MT=P_MT;
	while(Aux_MT->sig!=NULL){
	printf("Dato %d, ",&P_MT->capacidad);
	Aux_MT=Aux_MT->sig;}*/
}
