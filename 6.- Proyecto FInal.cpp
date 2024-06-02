#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>

#define nTareas 5
#define LineasPorPagina 100

#define Tquantum 3

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
	int TipoProceso;//1->CPU, 2->E, 3->S "los que tengan CPU no llevaran llevar nada en iniSC"
	int nDispositivos;
	int nArchivos;
	bool TipoSolicitud;//Usuario o sistema
	int CicSC;//ciclos de seccion critica
	int IniSC;//Inicio de la seccion critica
	int DuracionSC;//Duracion de seccion critica randon de 1 a 3 ste random debe estar en el rango de donde esta INISC hasta el final
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
PCB *PPCB, *QPCB, *Impresion, *AuxPCB; 
PCB *PPCB2, *QPCB2, *Impresion2, *AuxPCB2; 

int main(){
	Crear_JT();
	Crear_PMT();
	CrearPCB();
	AuxPCB=PPCB;
	Imprimir(2);
	char tecla;	tecla = _getch();	
	if(tecla == 13){Imprimir(3);RoundRobin();}
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
					PPCB->CicSC=0;
					PPCB->IniSC=0;
					PPCB->DuracionSC=0;
					
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
					AuxPCB->CicSC=0;
					AuxPCB->IniSC=0;
					AuxPCB->DuracionSC=0;
					
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

void tranferirDatos(){
	if(PPCB2==NULL){
    	PPCB2 = (PCB*)malloc(sizeof(PCB));
        PPCB2->CiclosCPU = AuxPCB->CiclosCPU;
        PPCB2->CicSC = AuxPCB->CicSC;
        PPCB2->DuracionSC = AuxPCB->DuracionSC;
        PPCB2->Estado = AuxPCB->Estado;
        PPCB2->IniSC = AuxPCB->IniSC;
        PPCB2->Memoria = AuxPCB->Memoria;
        PPCB2->nArchivos = AuxPCB->nArchivos;
        PPCB2->nDispositivos = AuxPCB->nDispositivos;
        PPCB2->nPagina = AuxPCB->nPagina;
        PPCB2->nTarea = AuxPCB->nTarea;
        PPCB2->TiempoLlegada = AuxPCB->TiempoLlegada;
        PPCB2->TipoProceso = AuxPCB->TipoProceso;
        PPCB2->TipoSolicitud = AuxPCB->TipoSolicitud;
        PPCB2->sig = NULL;
        QPCB2 = PPCB2;
	}
	else{
		AuxPCB2 = (PCB*)malloc(sizeof(PCB));
		AuxPCB2->CiclosCPU = AuxPCB->CiclosCPU;
        AuxPCB2->CicSC = AuxPCB->CicSC;
        AuxPCB2->DuracionSC = AuxPCB->DuracionSC;
        AuxPCB2->Estado = AuxPCB->Estado;
        AuxPCB2->IniSC = AuxPCB->IniSC;
        AuxPCB2->Memoria = AuxPCB->Memoria;
        AuxPCB2->nArchivos = AuxPCB->nArchivos;
        AuxPCB2->nDispositivos = AuxPCB->nDispositivos;
        AuxPCB2->nPagina = AuxPCB->nPagina;
        AuxPCB2->nTarea = AuxPCB->nTarea;
        AuxPCB2->TiempoLlegada = AuxPCB->TiempoLlegada;
        AuxPCB2->TipoProceso = AuxPCB->TipoProceso;
        AuxPCB2->TipoSolicitud = AuxPCB->TipoSolicitud;
		AuxPCB2->sig = NULL;
		QPCB2->sig = AuxPCB2;
		QPCB2 = AuxPCB2;
	}
}

void RoundRobin(){
	Montar();
	AuxPCB=PPCB;
	while(AuxPCB!=NULL){
		Imprimir(3);
		int quantum = Tquantum;
		AuxPCB->Estado=3;
		while(AuxPCB->CiclosCPU>0 && quantum>0){
			Imprimir(3);
			AuxPCB->CiclosCPU--;
			quantum--;
		}
		if(AuxPCB->CiclosCPU>0){
			Imprimir(3);
			AuxPCB->Estado=4;
			Imprimir(3);
	        tranferirDatos();
			Imprimir(4);
		}
		else{
			
		}
		AuxPCB=AuxPCB->sig;
	}
}
/*
void RoundRobin() {
    int quantum = 3; // Definir el quantum de tiempo para el Round Robin.
    Montar();
    AuxPCB = PPCB;

    while (AuxPCB != NULL) {
        if (AuxPCB->Estado == 2) { // Verificar que el proceso está en estado listo.
            Imprimir(3);
            AuxPCB->Estado = 3; // Cambiar el estado a en ejecución.
            int quantumActual = quantum;
            
            while (quantumActual > 0 && AuxPCB->CiclosCPU > 0) {
                Imprimir(3);
                AuxPCB->CiclosCPU--;
                quantumActual--;
            }

            if (AuxPCB->CiclosCPU > 0) {
                AuxPCB->Estado = 4; // Volver a poner el proceso en estado listo si aún tiene ciclos de CPU.
                // Mover el proceso al final de la cola.
                if (AuxPCB->sig != NULL) {
                    QPCB->sig = AuxPCB;
                    QPCB = AuxPCB;
                    AuxPCB = AuxPCB->sig;
                    QPCB->sig = NULL;
                } else {
                    break; // Si es el último proceso, salir del bucle.
                }
            } else {
                AuxPCB->Estado = 5; // Cambiar el estado a terminado si no tiene más ciclos de CPU.
                AuxPCB = AuxPCB->sig;
            }
        } else {
            AuxPCB = AuxPCB->sig; // Pasar al siguiente proceso.
        }
    }
}*/

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
			    system("cls");
			    printf("\n-----(PCB) BLOQUE DE CONTROL DE PROCESOS-----");
			    Impresion = PPCB;	char Tipo[20];
			    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------");
			    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%7s|%s%7s|%s%6s|%s%3s|%s%3s|%s%2s|\n","Proceso","","T-Llegada","",
				"Ciclos","","Estados","","Memoria","","CPU o E/s","","nDisp","","nArch","","TipoSol","","Ciclos SC","","Inicio SC","","DuracionSC","");
			    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------");
			    while(Impresion != NULL){
			        if(Impresion->TipoProceso == 1){
			            snprintf(Tipo, sizeof(Tipo), "CPU");
			        } else if(Impresion->TipoProceso == 2){
			            snprintf(Tipo, sizeof(Tipo), "E");
			        } else if(Impresion->TipoProceso == 3){
			            snprintf(Tipo, sizeof(Tipo), "S");
			        }
			        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6s%6s|%6d%6s|%6d%6s|%6d%6s|","",Impresion->nTarea,
					Impresion->nPagina,(Impresion->nTarea>=10)?"  ":"   ",Impresion->TiempoLlegada,"",Impresion->CiclosCPU,"",
					Impresion->Estado,"",Impresion->Memoria,"",Tipo,"",Impresion->nDispositivos,"",Impresion->nArchivos,"",
					(Impresion->TipoSolicitud==0)?"Usuario":"Sistema","",Impresion->CicSC,"",Impresion->IniSC,"",Impresion->DuracionSC,"");
			        Impresion = Impresion->sig;
			    }
			    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			    system("pause");
			break;
		case 4:
			    //system("cls");
			    printf("\n-----(PCB peq) BLOQUE DE CONTROL DE PROCESOS-----");
			    Impresion = PPCB2;
			    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------");
			    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%7s|%s%7s|%s%6s|%s%3s|%s%3s|%s%2s|\n","Proceso","","T-Llegada","",
				"Ciclos","","Estados","","Memoria","","CPU o E/s","","nDisp","","nArch","","TipoSol","","Ciclos SC","","Inicio SC","","DuracionSC","");
			    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------");
			    while(Impresion != NULL){
			        if(Impresion->TipoProceso == 1){
			            snprintf(Tipo, sizeof(Tipo), "CPU");
			        } else if(Impresion->TipoProceso == 2){
			            snprintf(Tipo, sizeof(Tipo), "E");
			        } else if(Impresion->TipoProceso == 3){
			            snprintf(Tipo, sizeof(Tipo), "S");
			        }
			        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6s%6s|%6d%6s|%6d%6s|%6d%6s|","",Impresion->nTarea,
					Impresion->nPagina,(Impresion->nTarea>=10)?"  ":"   ",Impresion->TiempoLlegada,"",Impresion->CiclosCPU,"",
					Impresion->Estado,"",Impresion->Memoria,"",Tipo,"",Impresion->nDispositivos,"",Impresion->nArchivos,"",
					(Impresion->TipoSolicitud==0)?"Usuario":"Sistema","",Impresion->CicSC,"",Impresion->IniSC,"",Impresion->DuracionSC,"");
			        Impresion = Impresion->sig;
			    }
			    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			    system("pause");
			break;
	}
}

