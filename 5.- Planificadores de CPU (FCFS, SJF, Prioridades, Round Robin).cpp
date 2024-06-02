#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>

#define nTareas 5
#define LineasPorPagina 100

using namespace std;

struct PMT;

struct JT{
	int nTarea;
	int nLineas;
	int LocPMT;
	int Secuencia;
	PMT *VinculoPMT;
	JT *sig;
};

struct PMT{
	int nPagina;
	int ciclosCPU;
	bool ejecutar;
	PMT *sig;
};

struct PCB{
	int nTarea;//para identificador de proceso
	int nPagina;// para identificador de proceso
	int TiempoLlegada;
	int CiclosCPU;
	int Estado;
	int Memoria;
	int TipoProceso;//1->CPU, 2->E, 3->S
	int nDispositivos;
	int nArchivos;
	bool TipoSolicitud;//Usuario o sistema
	PCB *sig;
};
//Paginacion Simple
void Crear_JT();
void Crear_PMT();
//Administrador CPU
void CrearPCB();
void Montar();
//Planificadores de procesos
void FCFS();
void SJF();
void porPrioridades();
void RoundRobin();
//Impresion
void Imprimir(int);
//Variables Globales
int contProcesos=0;

JT *PJT, *QJT, *NuevoJT, *AuxJT;
PMT *PPMT[nTareas], *QPMT[nTareas], *NuevoPMT, *AuxPMT;
PCB *PPCB, *QPCB, *AuxPCB; 

int main(){
	Crear_JT();
	Crear_PMT();
	CrearPCB();
	AuxPCB=PPCB;
	Imprimir(2);
	while(1){
		char tecla;	tecla = _getch();	
		if(tecla == 13){system("cls");Imprimir(3);}
		RoundRobin();
	}

}

/*
	printf("\n\t-> Que tarea se desea ejecutar?: ");
	scanf("%d",&tareaEjecucion);
*/

void Crear_JT(){
	for(int i=1; i<=nTareas; i++){
		if(PJT==NULL){
			PJT = (JT*)malloc(sizeof(JT));
			PJT->nTarea=1;
			PJT->nLineas=100+rand()%901;
			PJT->LocPMT=1010;
			PJT->sig=NULL;
			QJT=PJT;
		}
		else{
			NuevoJT = (JT*)malloc(sizeof(JT));
			NuevoJT->nTarea=i;
			NuevoJT->nLineas=100+rand()%901;
			NuevoJT->LocPMT=1010+i-1;
			NuevoJT->sig=NULL;
			QJT->sig=NuevoJT;
			QJT=NuevoJT;
		}
	}
}

void Crear_PMT(){
	AuxJT=PJT;
	for(int i=0; i<nTareas; i++){
		int nPaginas = AuxJT->nLineas/LineasPorPagina;//el n paginas es la / de lineas sobre l00 en este ejemplo
		AuxJT->nLineas%LineasPorPagina==0?:nPaginas++;//si la division no es exacta añade un espacio extra
		for(int j=0; j<nPaginas; j++){
			if(PPMT[i]==NULL){
				PPMT[i] = (PMT*)malloc(sizeof(PMT));
				PPMT[i]->nPagina=j;
				PPMT[i]->ciclosCPU=1+rand()%15;
				PPMT[i]->ejecutar=0+rand()%2;
				(PPMT[i]->ejecutar==0)?:contProcesos++;
				PPMT[i]->sig=NULL;
				QPMT[i]=PPMT[i];
				AuxJT->VinculoPMT=PPMT[i];
			}
			else{
				NuevoPMT = (PMT*)malloc(sizeof(PMT));
				NuevoPMT->nPagina=j;
				NuevoPMT->ciclosCPU=1+rand()%15;
				NuevoPMT->ejecutar=0+rand()%2;
				(NuevoPMT->ejecutar==0)?:contProcesos++;
				NuevoPMT->sig=NULL;
				QPMT[i]->sig=NuevoPMT;
				QPMT[i]=NuevoPMT;
			}
		}
		AuxJT=AuxJT->sig;
	}
}

void CrearPCB(){
	int j=0;
	for(int i=0; i<nTareas; i++){
		AuxPMT=PPMT[i];
		while(AuxPMT!=NULL){
			if(AuxPMT->ejecutar==true)
			{
				if(PPCB==NULL){
					PPCB = (PCB*)malloc(sizeof(PCB));
					
					PPCB->nTarea=i+1;
					PPCB->nPagina=AuxPMT->nPagina;
					PPCB->TiempoLlegada=j;
					PPCB->CiclosCPU=1+rand()%15;
					PPCB->Estado=1;
					PPCB->Memoria=1+rand()%50;
					PPCB->TipoProceso=1+rand()%3;
					PPCB->nDispositivos=1+rand()%5;
					PPCB->nArchivos=0+rand()%11;
					PPCB->TipoSolicitud=0+rand()%2;
					
					PPCB->sig=NULL;
					QPCB=PPCB;
				}
				else{
					AuxPCB = (PCB*)malloc(sizeof(PCB));
					
					AuxPCB->nTarea=i+1;
					AuxPCB->nPagina=AuxPMT->nPagina;
					AuxPCB->TiempoLlegada=j;
					AuxPCB->CiclosCPU=1+rand()%15;
					AuxPCB->Estado=1;
					AuxPCB->Memoria=1+rand()%50;
					AuxPCB->TipoProceso=1+rand()%3;
					AuxPCB->nDispositivos=1+rand()%5;
					AuxPCB->nArchivos=0+rand()%11;
					AuxPCB->TipoSolicitud=0+rand()%2;
					
					AuxPCB->sig=NULL;
					QPCB->sig=AuxPCB;
					QPCB=AuxPCB;
				}
				j++;
			}
			AuxPMT=AuxPMT->sig;
		}
	}
}

void Montar(){
	AuxPCB=PPCB;
	while(AuxPCB!=NULL){
		AuxPCB->Estado=2;
		AuxPCB=AuxPCB->sig;
	}
}

void RoundRobin(){
	Montar();
}

void Imprimir(int tabla){
	switch(tabla){
		case 1:
			printf("-----TABLA DE TAREAS-----\n\n");
			AuxJT = (JT*)malloc(sizeof(JT));
			AuxJT = PJT;
			printf("|%-12s | %-12s | %-12s|\n","No.Tarea","No.Lineas","Loc.PMT");
			printf("--------------------------------------------\n");
			while(AuxJT!=NULL){
				printf("|%-12d | %-12d | %-12d| \n",AuxJT->nTarea,AuxJT->nLineas,AuxJT->LocPMT);
				AuxJT=AuxJT->sig;
			}
			break;
		case 2:
			printf("\n-----(PMT)TABLA DE MAPA DE PAGINAS-----");
			for(int i=0; i<nTareas; i++){
				printf("\n\n---Mapa de pagina de J%d---%s\n",i+1,i>8?"":"-");
				printf("|   Pagina   | Seleccion  |\n");
				AuxPMT=PPMT[i];
				while(AuxPMT!=NULL){
					printf("|%6d%6s|%6d%6s|\n",AuxPMT->nPagina,"",AuxPMT->ejecutar,"");
					AuxPMT=AuxPMT->sig;
				}
				printf("---------------------------");
			}
			printf("\n\n Numero de procesos: %d",contProcesos);
			break;
		case 3:
			printf("\n-----(PCB) BLOQUE DE CONTROL DE PROCESOS-----");
			AuxPCB = PPCB;
			printf("\n----------------------------------------------------------------------------------------------------------------------");
			printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%7s|%s%7s|%s%5s|\n","Proceso","","T-Llegada","","Ciclos","","Estados","","Memoria","","CPU o E/s","","nDisp","","nArch","","TipoSol","");
			printf("----------------------------------------------------------------------------------------------------------------------");
			while(AuxPCB!=NULL){
				printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6d%8s|%6d%6s|%6d%6s|%6d%6s|","",AuxPCB->nTarea,AuxPCB->nPagina,(AuxPCB->nTarea>=10)?"  ":"   ",AuxPCB->TiempoLlegada,"",AuxPCB->CiclosCPU,"",AuxPCB->Estado,"",AuxPCB->Memoria,"",AuxPCB->TipoProceso,"",AuxPCB->nDispositivos,"",AuxPCB->nArchivos,"",AuxPCB->TipoSolicitud,"");
				AuxPCB=AuxPCB->sig;
			}
			printf("\n----------------------------------------------------------------------------------------------------------------------");
			break;
	}
}

