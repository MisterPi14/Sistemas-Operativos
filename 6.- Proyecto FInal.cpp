#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include <iomanip>
#define NT 10
#define LinCod 100
#define Arr 8
#define Quan 5
using namespace std;
void crear_TT(void);
void crear_MPT(void);
void ver_MPT(void);
void Bloc_de_Cont(void);
void Bloc_de_Cont_sem(void);
void Ver_Bloc_de_Cont(void);
void Ver_Bloc_de_Cont_sem(void);
void RR(void);
void semaforo(void);
void devolucion(void);

struct nodo_TT{
	int NoTarea, tamanio, LocPMT, totalP, Sec[Arr];
	struct nodo_TT*sig;
};

struct nodo_MPT{
	int NoPag, NoT, Celex, ContS;
	struct nodo_MPT*sig;
};

struct nodo_BdC{
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, CicloSC, IniSC, DuracionSC, masc;
	struct nodo_BdC*sig;
};

struct nodo_sem{
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, Tipo, CicloSC, IniSC, DuracionSC, masc, Wsem, Ssig, semaforo;
	struct nodo_sem*sig;
};

nodo_TT *Pt, *Qt, *Nuevot, *Auxt;
nodo_MPT *Pp, *Qp, *Nuevop, *Auxp;
nodo_BdC *Pc, *Qc, *Nuevoc, *Auxc, *Pivotec, *ImpresionPCB;
nodo_sem *Ps, *Qs, *Nuevos, *Auxs, *Pivotes, *ImpresionSem;

int main(){
	Pt=NULL;
	Qt=NULL;
	

	crear_TT();
	crear_MPT();
	ver_MPT();
	Bloc_de_Cont();
	RR();
	getch();
	return 0;
}

void crear_TT(void){//TABLA DE TAREAS
	int coeficiente, residuo;
	int puntero=10;
	srand(time(NULL));
	for(int i=1;i<=NT;i++){
		if(Pt==NULL){
			Pt=(nodo_TT *)malloc(sizeof(nodo_TT));
			Pt->NoTarea=i;
			Pt->tamanio=100+rand()%500;
			Pt->LocPMT=puntero;
			puntero++;
			coeficiente=Pt->tamanio / LinCod;
			residuo=Pt->tamanio % LinCod;
			if(residuo>0){
				Pt->totalP=coeficiente+1;
			}else{
				Pt->totalP=coeficiente;
			}
			Pt->Sec[0]=0;
			for(int k=1;k<Arr;k++){
				Pt->Sec[k]=0+rand()%Pt->totalP;
			}
			Pt->sig=NULL;
			Qt=Pt;
		}else{
			Nuevot=(nodo_TT *)malloc(sizeof(nodo_TT));
			Nuevot->NoTarea=i;
			Nuevot->tamanio=100+rand()%500;
			Nuevot->LocPMT=puntero;
			puntero++;
			coeficiente=Nuevot->tamanio / LinCod;
			residuo=Nuevot->tamanio % LinCod;
			if(residuo>0){
				Nuevot->totalP=coeficiente+1;
			}else{
				Nuevot->totalP=coeficiente;
			}
			Nuevot->Sec[0]=0;
			for(int k=1;k<Arr;k++){
				Nuevot->Sec[k]=0+rand()%Nuevot->totalP;
			}
			Nuevot->sig=NULL;
			Qt->sig=Nuevot;
			Qt=Nuevot;
		}
	}
}

void crear_MPT(void){
	Auxt=Pt;
	int contador=0;
	srand(time(NULL));
	for(int i=1;i<=NT;i++){
		for(int j=0;j<Auxt->totalP;j++){
			if(Pp==NULL){
				Pp=(nodo_MPT *)malloc(sizeof(nodo_MPT));
				Pp->NoT=Auxt->NoTarea;
				Pp->NoPag=j;
				Pp->Celex=0+rand()%2;
				if(Pp->Celex==1){
					contador++;
				}
				Pp->sig=NULL;
				Qp=Pp;
			}else{
				Nuevop=(nodo_MPT *)malloc(sizeof(nodo_MPT));
				Nuevop->NoT=Auxt->NoTarea;
				Nuevop->NoPag=j;
				Nuevop->Celex=0+rand()%2;
				if(Nuevop->Celex==1){
					contador++;
				}
				if(j==(Auxt->totalP)-1){
					Nuevop->ContS=contador;
				}
				Nuevop->sig=NULL;
				Qp->sig=Nuevop;
				Qp=Nuevop;	
			}
		}
		contador=0;
		Auxt=Auxt->sig;
	}	
	cout<<"\nTABLAS DE MAPA DE PAGINAS\n";
}

void ver_MPT(void){
	int total=0;
	Auxt=Pt;
	Auxp=Pp;
	for(int i=1;i<=NT;i++){
		cout<<"Tarea ["<<Auxt->NoTarea<<"]\n";
		for(int j=0;j<Auxt->totalP;j++){
			cout<<"J"<<Auxp->NoT<<"P"<<Auxp->NoPag<<" |   ";
			cout<<Auxp->Celex<<"\n";
			if(j==(Auxt->totalP)-1){
				cout<<"Numero de Selecciones: "<<Auxp->ContS<<"\n\n";
			}
			total=total+Auxp->ContS;
			Auxp=Auxp->sig;
		}
		Auxt=Auxt->sig;		
	}
	cout<<"Total = "<<total<<"\n";
	system("pause");
}

float ContadorGlobal=0;
void Bloc_de_Cont(void){
	int aux;
	srand(time(NULL));
	int T=0;
	Auxp=Pp;
	do{
		if(Auxp->Celex==1){
			if(Pc==NULL){
				Pc=(nodo_BdC *)malloc(sizeof(nodo_BdC));
				Pc->ProcJ=Auxp->NoT;
				Pc->ProcP=Auxp->NoPag;
				Pc->Tiempo=T;
				Pc->Ciclo=2+rand()%18;
				Pc->Edo=1;
				Pc->Mem=10+rand()%111;
				Pc->TipoP=0+rand()%3;
				Pc->CicloSC=0;
				aux=Pc->Ciclo;
				if(Pc->TipoP==0){
					Pc->IniSC=0;
				}else{
					Pc->IniSC=rand()%aux+1;
				}
				if(Pc->IniSC==0){
					Pc->DuracionSC=0;
				}else if(Pc->IniSC==aux){
					Pc->DuracionSC=1;
				}else if(Pc->IniSC==aux-1){
					Pc->DuracionSC=rand()%2+1;
				}else{
					Pc->DuracionSC=1+rand()%3;
				}
				Pc->masc=0;
				ContadorGlobal++;
				Pc->sig=NULL;
				Qc=Pc;
			}else{
				Nuevoc=(nodo_BdC *)malloc(sizeof(nodo_BdC));
				Nuevoc->ProcJ=Auxp->NoT;
				Nuevoc->ProcP=Auxp->NoPag;
				Nuevoc->Tiempo=T;
				Nuevoc->Ciclo=2+rand()%18;
				Nuevoc->Edo=1;
				Nuevoc->Mem=10+rand()%111;
				Nuevoc->TipoP=0+rand()%3;
				Nuevoc->CicloSC=0;
				aux=Nuevoc->Ciclo;
				if(Nuevoc->TipoP==0){
					Nuevoc->IniSC=0;
				}else{
					Nuevoc->IniSC=rand()%aux+1;
				}
				if(Nuevoc->IniSC==0){
					Nuevoc->DuracionSC=0;
				}else if(Nuevoc->IniSC==aux){
					Nuevoc->DuracionSC=1;
				}else if(Nuevoc->IniSC==aux-1){
					Nuevoc->DuracionSC=rand()%2+1;
				}else{
					Nuevoc->DuracionSC=1+rand()%3;
				}
				Nuevoc->masc=0;
				ContadorGlobal++;
				Nuevoc->sig=NULL;
				Qc->sig=Nuevoc;
				Qc=Nuevoc;	
			}
			T++;	
		}
		Auxp=Auxp->sig;
	}while(Auxp!=NULL);
	Ver_Bloc_de_Cont();
}  

int confirm=0;


void Ver_Bloc_de_Cont(void){
	system("cls");
    printf("\n-----(PCB) BLOQUE DE CONTROL DE PROCESOS-----");
    ImpresionPCB=Pc;	char Tipo[20];
    printf("\n----------------------------------------------------------------------------------------------------------------------");
    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%3s|%s%3s|%s%2s|\n","Proceso","","T-Llegada","",
	"Ciclos","","Estados","","Memoria","","CPU o E/s","","Ciclos SC","","Inicio SC","","DuracionSC","");
    printf("----------------------------------------------------------------------------------------------------------------------");
    while(ImpresionPCB != NULL){
    	if(ImpresionPCB->masc==0){
	    	if(ImpresionPCB->TipoP == 0){
	            snprintf(Tipo, sizeof(Tipo), "CPU");
	        } else if(ImpresionPCB->TipoP == 1){
	            snprintf(Tipo, sizeof(Tipo), "E");
	        } else if(ImpresionPCB->TipoP == 2){
	            snprintf(Tipo, sizeof(Tipo), "S");
	        }
	        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6d%6s|","",ImpresionPCB->ProcJ,
			ImpresionPCB->ProcP,(ImpresionPCB->ProcP>=10||ImpresionPCB->ProcJ>=10)?"  ":"   ",ImpresionPCB->Tiempo,"",ImpresionPCB->Ciclo,"",
			ImpresionPCB->Edo,"",ImpresionPCB->Mem,"",Tipo,"",ImpresionPCB->CicloSC,"",ImpresionPCB->IniSC,"",ImpresionPCB->DuracionSC,"");
		}
		ImpresionPCB=ImpresionPCB->sig;
    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");	
	cout<<"\n";
	Ver_Bloc_de_Cont_sem();
}

void Ver_Bloc_de_Cont_sem(void){
    printf("\n-----(PCB) Semaforo-----");
    ImpresionSem=Ps;	char Tipo[20];
    printf("\n\t\t\t\t\t\t\t\t\tSemaforo: %d",semaforo);
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%3s|%s%3s|%s%2s|%s%2s|%s%2s|\n","Proceso","","T-Llegada","",
	"Ciclos","","Estados","","Memoria","","CPU o E/s","","Ciclos SC","","Inicio SC","","DuracionSC","","Wait(S)","","Signal(S)","");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------");
    while(ImpresionSem != NULL){
    	if(ImpresionSem->masc==1){
	    	if(ImpresionSem->TipoP == 0){
	            snprintf(Tipo, sizeof(Tipo), "CPU");
	        } else if(ImpresionSem->TipoP == 1){
	            snprintf(Tipo, sizeof(Tipo), "E");
	        } else if(ImpresionSem->TipoP == 2){
	            snprintf(Tipo, sizeof(Tipo), "S");
	        }
	        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6d%6s|%6d%3s|%6d%5s|","",ImpresionSem->ProcJ,
			ImpresionSem->ProcP,(ImpresionSem->ProcP>=10||ImpresionSem->ProcJ>=10)?"  ":"   ",ImpresionSem->Tiempo,"",ImpresionSem->Ciclo,"",
			ImpresionSem->Edo,"",ImpresionSem->Mem,"",Tipo,"",ImpresionSem->CicloSC,"",ImpresionSem->IniSC,"",
			ImpresionSem->DuracionSC,"",ImpresionSem->Wsem,"",ImpresionSem->Ssig,"");
		}
		ImpresionSem=ImpresionSem->sig;
    }
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------\n");	
	cout<<"\n";
	system("pause");
}

/*
void Ver_Bloc_de_Cont(void){
	int x=0;
	system("cls");
	cout<<"\nBloque de control de procesos (PCB)\n";
	cout<<"\nProceso | T.Llegada | Ciclos | Edo | Memoria | CPU/E/S | CicSC | IniSC | DuracionSC\n";
	Auxc=Pc;
	do{
		if(Auxc->masc==0){
			cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<"    | ";
			cout<<setw(10)<<left<<Auxc->Tiempo<<"| ";
			cout<<setw(7)<<left<<Auxc->Ciclo<<"| ";
			cout<<setw(4)<<left<<Auxc->Edo<<"| ";
			cout<<setw(8)<<left<<Auxc->Mem<<"| ";
			if(Auxc->TipoP==0){
				cout<<setw(9)<<left<<"CPU     | ";
			}else if(Auxc->TipoP==1){
				cout<<setw(9)<<left<<"S       | ";
			}else if(Auxc->TipoP==2){
				cout<<setw(9)<<left<<"E       | ";
			}
			cout<<setw(5)<<left<<Auxc->CicloSC<<"| ";
			cout<<setw(5)<<left<<Auxc->IniSC<<"| ";
			cout<<Auxc->DuracionSC<<"\n";
		}
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	x++;
	if(confirm>0){
		Ver_Bloc_de_Cont_sem();
	}else{
		system("pause");
	}
	cout<<"\n";
}

void Ver_Bloc_de_Cont_sem(void){
	cout<<"\nBloque de control de procesos (PCB)\n";
	cout<<"\nProceso | T.Llegada | Ciclos | Edo | Memoria | CPU/E/S | Tipo     | IniSC | DuracionSC | W(sem) | S(sig) | semaforo\n";
	Auxs=Ps;
	do{
		if(Auxs->masc==1){
			cout<<"J"<<Auxs->ProcJ<<"P"<<Auxs->ProcP<<"    | ";
			cout<<setw(10)<<left<<Auxs->Tiempo<<"| ";
			cout<<setw(7)<<left<<Auxs->Ciclo<<"| ";
			cout<<setw(4)<<left<<Auxs->Edo<<"| ";
			cout<<setw(8)<<left<<Auxs->Mem<<"| ";
			if(Auxs->TipoP==0){
				cout<<setw(9)<<left<<"CPU     | ";
			}else if(Auxs->TipoP==1){
				cout<<setw(9)<<left<<"S       | ";
			}else if(Auxs->TipoP==2){
				cout<<setw(9)<<left<<"E       | ";
			}
			cout<<setw(5)<<left<<Auxs->CicloSC<<"| ";
			cout<<setw(5)<<left<<Auxs->IniSC<<"| ";
			cout<<setw(10)<<Auxs->DuracionSC<<" |";
			cout<<setw(8)<<Auxs->Wsem<<"|";
			cout<<setw(8)<<Auxs->Ssig<<"|";
			cout<<Auxs->semaforo<<"\n";	
		}
		Auxs=Auxs->sig;
	}while(Auxs!=NULL);
	system("pause");
	cout<<"\n";
}*/

void Bloc_de_Cont_sem(void){
	if(Auxc->masc==1){
		if(Ps==NULL){
			Ps=(nodo_sem *)malloc(sizeof(nodo_sem));
			Ps->ProcJ=Auxc->ProcJ;
			Ps->ProcP=Auxc->ProcP;
			Ps->Tiempo=Auxc->Tiempo;
			Ps->Ciclo=Auxc->Ciclo;
			Ps->Edo=Auxc->Edo;
			Ps->Mem=Auxc->Mem;
			Ps->TipoP=Auxc->TipoP;
			Ps->CicloSC=Auxc->CicloSC;
			Ps->IniSC=Auxc->IniSC;
			Ps->DuracionSC=Auxc->DuracionSC;
			Ps->masc=Auxc->masc;
			Ps->Wsem=1;
			Ps->Ssig=0;
			Ps->semaforo=0;
			Ps->sig=NULL;
			Qs=Ps;
		}else{
			Nuevos=(nodo_sem *)malloc(sizeof(nodo_sem));
			Nuevos->ProcJ=Auxc->ProcJ;
			Nuevos->ProcP=Auxc->ProcP;
			Nuevos->Tiempo=Auxc->Tiempo;
			Nuevos->Ciclo=Auxc->Ciclo;
			Nuevos->Edo=Auxc->Edo;
			Nuevos->Mem=Auxc->Mem;
			Nuevos->TipoP=Auxc->TipoP;
			Nuevos->CicloSC=Auxc->CicloSC;
			Nuevos->IniSC=Auxc->IniSC;
			Nuevos->DuracionSC=Auxc->DuracionSC;
			Nuevos->masc=Auxc->masc;
			Nuevos->Wsem=1;
			Nuevos->Ssig=0;
			Nuevos->semaforo=0;
			Nuevos->sig=NULL;
			Qs->sig=Nuevos;
			Qs=Nuevos;	
		}
	} 
}  
   
void RR(void){
	int contadorsem=0;
	int a;
	cout<<"\n\n";
	Auxc=Pc;
	do{
		Auxc->Edo=2;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	Ver_Bloc_de_Cont();
	Auxc=Pc;
	while(true){
		if(Auxc->Edo!=5){
			Auxc->Edo=3;
		}
		a=Quan;
		while(Auxc->Ciclo>0 && a>0 && Auxc->masc==0){
			Pivotec=Auxc;
			semaforo();
			Auxc=Pivotec;
			if(Auxc->Ciclo>0){
				Auxc->CicloSC=Auxc->CicloSC+1;
				Auxc->Ciclo=(Auxc->Ciclo)-1;
			}
			if((Auxc->CicloSC)==Auxc->IniSC){
				confirm=1;	
				Auxc->Edo=4;
				Auxc->masc=1;
				Auxc->DuracionSC=Auxc->DuracionSC-1;
				Bloc_de_Cont_sem();	
				//////////////////////////////////////////
				Pivotec=Auxc;
				Ver_Bloc_de_Cont();	//Mostrar la tabla
				Auxc=Pivotec;
				//////////////////////////////////////////
				a=0;
			}else{
				//////////////////////////////////////////
				Pivotec=Auxc;
				Ver_Bloc_de_Cont();	//Mostrar la tabla
				Auxc=Pivotec;
				//////////////////////////////////////////
			}		
			a--;
		}
		if(Auxc->Ciclo>0 && Auxc->masc==0){
			Auxc->Edo=4;
			//////////////////////////////////////////
			Pivotec=Auxc;
			Ver_Bloc_de_Cont();	//Mostrar la tabla
			Auxc=Pivotec;
			//////////////////////////////////////////
		}
		if(Auxc->Ciclo==0){
			if(Auxc->Edo!=5){
				Auxc->Edo=5;
				//////////////////////////////////////////
				Pivotec=Auxc;
				Ver_Bloc_de_Cont();	//Mostrar la tabla
				Auxc=Pivotec;
				//////////////////////////////////////////
			}
			Pivotec=Auxc;
			Auxc=Pc;
			do{
				if(Auxc->Edo==5){
					contadorsem++;
				}
				Auxc=Auxc->sig;
			}while(Auxc!=NULL);
			if(contadorsem==ContadorGlobal){
				break;
			}
			contadorsem=0;
			Auxc=Pivotec;
		}
		Auxc=Auxc->sig;
		if(Auxc==NULL){
			Auxc=Pc;
		}
	}
}

void semaforo(void){
	if(confirm==1){
		Auxs=Ps;
		do{
			if(Auxs->masc==0){
				Auxs=Auxs->sig;
			}
		}while(Auxs->masc==0);
		if(Auxs->masc==1){
			if(Auxs->DuracionSC==0){
				Auxs->Wsem=0;
				Auxs->Ssig=1;
				Auxs->semaforo=1;
				//////////////////////////////////////////
				Pivotec=Auxc;
				Pivotes=Auxs;
				Ver_Bloc_de_Cont();	//Mostrar la tabla, incluyendo el semaforo
				Auxs=Pivotes;
				Auxc=Pivotec;
				//////////////////////////////////////////	
				Auxs->masc=0;
				if(Auxs->Ciclo==0){
					Auxs->Edo=5;
				}
				devolucion();
				Auxs=Auxs->sig;
				if(Auxs==NULL){
					confirm=0;
				}
			}else if(Auxs->DuracionSC>=1){
				Auxs->Ciclo=Auxs->Ciclo-1;
				Auxs->CicloSC=Auxs->CicloSC+1;
				Auxs->DuracionSC=Auxs->DuracionSC-1;
			}
		}
	}
}

void devolucion(void){
	Auxc=Pc;
	do{
		if(Auxc->Tiempo==Auxs->Tiempo){
			Auxc->masc=Auxs->masc;
			Auxc->CicloSC=Auxs->CicloSC;
			Auxc->IniSC=Auxs->IniSC;
			Auxc->DuracionSC=Auxs->DuracionSC;
			Auxc->Edo=Auxs->Edo;
			Auxc->Ciclo=Auxs->Ciclo;
		}
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
}
