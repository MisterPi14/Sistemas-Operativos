#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>

#define nTiempos 8

using namespace std;

int Secuencia[nTiempos];
int tareaEjecucion;

struct PCB{
	//int nTarea;//para identificador de proceso
	int nPagina;// para identificador de proceso
	int TiempoLlegada;
	int CiclosCPU;
	int Memoria;
	bool TipoProceso;
	int Archivos;
	PCB *sig;
};

void Imprimir();
void CrearPCB();
void generarSecuencia();
//Planificadores de procesos
void FCFS();
void SJF();
void porPrioridades();

PCB *PPCB, *QPCB, *AuxPCB; 

int main(){
	generarSecuencia();
	printf("\n\t-> Que tarea se desea ejecutar?: ");
	scanf("%d",&tareaEjecucion);
	CrearPCB();
	Imprimir();
}

void generarSecuencia(){
	for(int i=0; i<nTiempos; i++){
		Secuencia[i]=0+rand()%10;
	}
}

void CrearPCB(){
	for(int i=0; i<nTiempos; i++){
		if(PPCB==NULL){
			PPCB = (PCB*)malloc(sizeof(PCB));
			
			PPCB->nPagina=Secuencia[0];
			PPCB->TiempoLlegada=0;
			PPCB->CiclosCPU=1+rand()%10;
			PPCB->Memoria=1+rand()%51;
			PPCB->TipoProceso=0+rand()%1;
			PPCB->Archivos=0+rand()%11;
			
			PPCB->sig=NULL;
			QPCB=PPCB;
		}
		else{
			AuxPCB = (PCB*)malloc(sizeof(PCB));
			
			AuxPCB->nPagina=Secuencia[i];
			AuxPCB->TiempoLlegada=i;
			AuxPCB->CiclosCPU=1+rand()%10;
			AuxPCB->Memoria=1+rand()%51;
			AuxPCB->TipoProceso=0+rand()%1;
			AuxPCB->Archivos=0+rand()%11;
			
			AuxPCB->sig=NULL;
			QPCB->sig=AuxPCB;
			QPCB=AuxPCB;
		}
	
	}
}

void Imprimir(){
	for(int i=0; i<nTiempos; i++){
		printf("%d,",Secuencia[i]);
	}	
}


