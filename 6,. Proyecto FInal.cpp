#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define NT 10
#define LinCod 100
#define Arr 8
using namespace std;
void crear_TT(void);
void crear_MPT(void);
void ver_MPT(void);
void Bloc_de_Cont(void);
void Ver_Bloc_de_Cont(void);
//void FCFS(void);
//void Prioridades(void);
void SJF(void);
void CambioMem(void);
void CambioTiem(void);
void CambioCiclo(void);
void Op(void);

string espaciar(int tamanio, int valor){
	int espacio = 0;
	string texto="";
	
	espacio = valor - tamanio;
	
	for(int i=0; i< espacio; i++){
		texto = texto + " ";
	}
	return texto;
}

struct nodo_TT{
	int NoTarea, tamanio, LocPMT, totalP, Sec[Arr];
	struct nodo_TT*sig;
};

struct nodo_MPT{
	int NoPag, NoT, Celex, ContS;
	struct nodo_MPT*sig;
};

struct nodo_BdC{
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, Disp, Archi, Tipo, acumula, espera;
	struct nodo_BdC*sig;
};

nodo_TT *Pt, *Qt, *Nuevot, *Auxt;
nodo_MPT *Pp, *Qp, *Nuevop, *Auxp;
nodo_BdC *Pc, *Qc, *Nuevoc, *Auxc, *Pivotec, *nodo_i, *nodo_j;

int main(){
	Pt=NULL;
	Qt=NULL;
	

	crear_TT();
	crear_MPT();
	ver_MPT();
	Bloc_de_Cont();
	//FCFS();
	//Prioridades();
	SJF();
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
	Auxt=Pt;
	Auxp=Pp;
	for(int i=1;i<=NT;i++){
		cout<<"Tarea ["<<Auxt->NoTarea<<"]\n";
		for(int j=0;j<Auxt->totalP;j++){
			cout<<"J"<<Auxp->NoT<<"P"<<Auxp->NoPag<<" |   ";
			cout<<Auxp->Celex<<"\n";
			if(j==(Auxt->totalP)-1){
				cout<<"Seleccion: "<<Auxp->ContS<<"\n\n";
			}
			Auxp=Auxp->sig;
		}
		Auxt=Auxt->sig;		
	}
	system("pause");
}

float ContadorGlobal=0;
void Bloc_de_Cont(void){
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
				Pc->Ciclo=2+rand()%10;
				Pc->Edo=1;
				Pc->Mem=10+rand()%111;
				Pc->TipoP=0+rand()%3;
				Pc->Disp=0+rand()%6;
				Pc->Archi=1+rand()%10;
				Pc->Tipo=0+rand()%2;
				Pc->acumula=0;
				Pc->espera=0;
				ContadorGlobal++;
				Pc->sig=NULL;
				Qc=Pc;
			}else{
				Nuevoc=(nodo_BdC *)malloc(sizeof(nodo_BdC));
				Nuevoc->ProcJ=Auxp->NoT;
				Nuevoc->ProcP=Auxp->NoPag;
				Nuevoc->Tiempo=T;
				Nuevoc->Ciclo=2+rand()%10;
				Nuevoc->Edo=1;
				Nuevoc->Mem=10+rand()%111;
				Nuevoc->TipoP=0+rand()%3;
				Nuevoc->Disp=0+rand()%6;
				Nuevoc->Archi=1+rand()%10;
				Nuevoc->Tipo=0+rand()%2;
				Nuevoc->acumula=0;
				Nuevoc->espera=0;
				ContadorGlobal++;
				Nuevoc->sig=NULL;
				Qc->sig=Nuevoc;
				Qc=Nuevoc;	
			}
			T++;	
		}
		Auxp=Auxp->sig;
	}while(Auxp!=NULL);
	cout<<"\nBLOQUE DE CONTROL DE PROCESOS PCB\n";
	Ver_Bloc_de_Cont();
}

void Ver_Bloc_de_Cont(void){
	cout<<"\nProceso|T.Llegada|Ciclos|Edo|Memoria|CPU/E/S|#Disp|#Archivo|Tipo\n";
	Auxc=Pc;
	do{
		cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<"   |";
		cout<<Auxc->Tiempo<<"t"<<espaciar(2, 9)<<"|";
		cout<<Auxc->Ciclo<<"ms"<<espaciar(2, 5)<<"|";
		cout<<Auxc->Edo<<espaciar(2, 3)<<"|";
		cout<<Auxc->Mem<<"KB"<<espaciar(2, 5)<<"|";
		if(Auxc->TipoP==0){
			cout<<"CPU"<<espaciar(2, 6)<<"|";;
		}else if(Auxc->TipoP==1){
			cout<<"S"<<espaciar(2, 8)<<"|";
		}else if(Auxc->TipoP==2){
			cout<<"E"<<espaciar(2, 8)<<"|";
		}
		cout<<Auxc->Disp<<espaciar(2, 6)<<"|";
		cout<<Auxc->Archi<<espaciar(2, 9)<<"|";
		if(Auxc->Tipo==0){
			cout<<"Usuario\n"	;
		}else if(Auxc->Tipo==1){
			cout<<"Sistema\n"	;
		}
		//cout<<"|  "<<Auxc->acumula<<"\n";
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	cout<<"\n";
	system("pause");
}

int Denisse=0;
/*void FCFS(void){
	cout<<"\n\n\nAlgoritmo Planificacion FCFS\n";
	int flagTiempo=0;
	Auxc=Pc;
	do{
		Auxc->Edo=2;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	Ver_Bloc_de_Cont();
	Auxc=Pc;
	do{
		Auxc->Edo=3;
		flagTiempo=Auxc->Ciclo;
		while(Auxc->Ciclo>0){
			if(flagTiempo==Auxc->Ciclo){
				Auxc->espera=Denisse;
			}
			Auxc->Ciclo=(Auxc->Ciclo)-1;
			Pivotec=Auxc;
			//Ver_Bloc_de_Cont();
			//Auxc=Pivotec;
			//Denisse++;
		}
		Auxc->Edo=5;
		Auxc->acumula=Denisse;
		Pivotec=Auxc;
		Ver_Bloc_de_Cont();
		Auxc=Pivotec;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	Op();
}*/

/*void Prioridades(void){
	cout<<"\n\n\nAlgoritmo Planificacion X Prioridades\n";
	CambioMem();
	//Ver_Bloc_de_Cont();
	int flagTiempo=0;
	Auxc=Pc;
	do{
		Auxc->Edo=2;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	cout<<"\nPriorizar Memoria\n";
	Ver_Bloc_de_Cont();
	Auxc=Pc;
	do{
		Auxc->Edo=3;
		flagTiempo=Auxc->Ciclo;
		while(Auxc->Ciclo>0){
			if(flagTiempo==Auxc->Ciclo){
				Auxc->espera=Denisse;
			}
			Auxc->Ciclo=(Auxc->Ciclo)-1;
			//Pivotec=Auxc;
			//Ver_Bloc_de_Cont();
			//Auxc=Pivotec;
			Denisse++;
		}
		Auxc->Edo=5;
		Auxc->acumula=Denisse;
		Pivotec=Auxc;
		Ver_Bloc_de_Cont();
		Auxc=Pivotec;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	cout<<"\nReordenar\n";
	CambioTiem();
	Ver_Bloc_de_Cont();
	Op();
}*/

void SJF(void){
	cout<<"\n\n\nAlgoritmo Planificacion SJF\n";
	CambioCiclo();
	//Ver_Bloc_de_Cont();
	int flagTiempo=0;
	Auxc=Pc;
	do{
		Auxc->Edo=2;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	cout<<"\nPriorizar cICLO\n";
	Ver_Bloc_de_Cont();
	Auxc=Pc;
	do{
		Auxc->Edo=3;
		flagTiempo=Auxc->Ciclo;
		while(Auxc->Ciclo>0){
			if(flagTiempo==Auxc->Ciclo){
				Auxc->espera=Denisse;
			}
			Auxc->Ciclo=(Auxc->Ciclo)-1;
			//Pivotec=Auxc;
			//Ver_Bloc_de_Cont();
			//Auxc=Pivotec;
			Denisse++;
		}
		Auxc->Edo=5;
		Auxc->acumula=Denisse;
		Pivotec=Auxc;
		Ver_Bloc_de_Cont();
		Auxc=Pivotec;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	cout<<"\nReordenar\n";
	CambioTiem();
	Ver_Bloc_de_Cont();
	Op();	
}

void Op(void){
	float aux=0;
	float TPRS;
	Auxc=Pc;
	cout<<"\n\nTiempo de Retono de Proceso\n";
	do{
		cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<" = ";
		cout<<Auxc->acumula<<"ms\n";
		aux=aux+Auxc->acumula;
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	
	cout<<"\n\nTiempo Promedio TPRS\n";
	TPRS=aux/ContadorGlobal;
	cout<<"TPRS = "<<aux<<"/"<<ContadorGlobal<<" = "<<TPRS<<"ms\n";
	
	Auxc=Pc;
	cout<<"\nTiempo de espera\n";
	do{
		cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<" = ";
		cout<<Auxc->espera<<"ms\n";
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	
	cout<<"\nTiempo total de ejecucion\n";
	cout<<"  "<<Denisse<<"ms\n";
}

void CambioMem(void){
	int ProcJalt, ProcPalt, Tiempoalt, Cicloalt, Edoalt, Memalt, TipoPalt, Dispalt, Archialt, Tipoalt, acumulaalt, esperaalt;
	nodo_i=Pc;
	for(nodo_i=nodo_i;nodo_i->sig!=NULL;nodo_i=nodo_i->sig){
		for(nodo_j=nodo_i->sig;nodo_j!=NULL;nodo_j=nodo_j->sig){
			if(nodo_i->Mem > nodo_j->Mem){
				//MENOR A MAYOR ----> ">"
				ProcJalt=nodo_i->ProcJ;
				ProcPalt=nodo_i->ProcP;
				Tiempoalt=nodo_i->Tiempo;
				Cicloalt=nodo_i->Ciclo;
				Edoalt=nodo_i->Edo;
				Memalt=nodo_i->Mem;
				TipoPalt=nodo_i->TipoP;
				Dispalt=nodo_i->Disp;
				Archialt=nodo_i->Archi;
				Tipoalt=nodo_i->Tipo;
				acumulaalt=nodo_i->acumula;
				esperaalt=nodo_i->espera;
				
				nodo_i->ProcJ=nodo_j->ProcJ;
				nodo_i->ProcP=nodo_j->ProcP ;
				nodo_i->Tiempo=nodo_j->Tiempo;
				nodo_i->Ciclo=nodo_j->Ciclo;
				nodo_i->Edo=nodo_j->Edo;
				nodo_i->Mem=nodo_j->Mem;  
				nodo_i->TipoP=nodo_j->TipoP; 
				nodo_i->Disp=nodo_j->Disp;
				nodo_i->Archi=nodo_j->Archi;
				nodo_i->Tipo=nodo_j->Tipo;
				nodo_i->acumula=nodo_j->acumula;
				nodo_i->espera=nodo_j->espera;
				
				nodo_j->ProcJ=ProcJalt;
				nodo_j->ProcP=ProcPalt;
				nodo_j->Tiempo=Tiempoalt;
				nodo_j->Ciclo=Cicloalt;
				nodo_j->Edo=Edoalt;
				nodo_j->Mem=Memalt;
				nodo_j->TipoP=TipoPalt;
				nodo_j->Disp=Dispalt;
				nodo_j->Archi=Archialt;
				nodo_j->Tipo=Tipoalt;
				nodo_j->acumula=acumulaalt;
				nodo_j->espera=esperaalt;
			}
		} 
	}  
} 

void CambioTiem(void){
	int ProcJalt, ProcPalt, Tiempoalt, Cicloalt, Edoalt, Memalt, TipoPalt, Dispalt, Archialt, Tipoalt, acumulaalt, esperaalt;
	nodo_i=Pc;
	for(nodo_i=nodo_i;nodo_i->sig!=NULL;nodo_i=nodo_i->sig){
		for(nodo_j=nodo_i->sig;nodo_j!=NULL;nodo_j=nodo_j->sig){
			if(nodo_i->Tiempo > nodo_j->Tiempo){
				//MENOR A MAYOR ----> ">"
				ProcJalt=nodo_i->ProcJ;
				ProcPalt=nodo_i->ProcP;
				Tiempoalt=nodo_i->Tiempo;
				Cicloalt=nodo_i->Ciclo;
				Edoalt=nodo_i->Edo;
				Memalt=nodo_i->Mem;
				TipoPalt=nodo_i->TipoP;
				Dispalt=nodo_i->Disp;
				Archialt=nodo_i->Archi;
				Tipoalt=nodo_i->Tipo;
				acumulaalt=nodo_i->acumula;
				esperaalt=nodo_i->espera;
				
				nodo_i->ProcJ=nodo_j->ProcJ;
				nodo_i->ProcP=nodo_j->ProcP ;
				nodo_i->Tiempo=nodo_j->Tiempo;
				nodo_i->Ciclo=nodo_j->Ciclo;
				nodo_i->Edo=nodo_j->Edo;
				nodo_i->Mem=nodo_j->Mem;  
				nodo_i->TipoP=nodo_j->TipoP; 
				nodo_i->Disp=nodo_j->Disp;
				nodo_i->Archi=nodo_j->Archi;
				nodo_i->Tipo=nodo_j->Tipo;
				nodo_i->acumula=nodo_j->acumula;
				nodo_i->espera=nodo_j->espera;
				
				nodo_j->ProcJ=ProcJalt;
				nodo_j->ProcP=ProcPalt;
				nodo_j->Tiempo=Tiempoalt;
				nodo_j->Ciclo=Cicloalt;
				nodo_j->Edo=Edoalt;
				nodo_j->Mem=Memalt;
				nodo_j->TipoP=TipoPalt;
				nodo_j->Disp=Dispalt;
				nodo_j->Archi=Archialt;
				nodo_j->Tipo=Tipoalt;
				nodo_j->acumula=acumulaalt;
				nodo_j->espera=esperaalt;
			}
		} 
	}  
}

void CambioCiclo(void){
	int ProcJalt, ProcPalt, Tiempoalt, Cicloalt, Edoalt, Memalt, TipoPalt, Dispalt, Archialt, Tipoalt, acumulaalt, esperaalt;
	nodo_i=Pc;
	for(nodo_i=nodo_i;nodo_i->sig!=NULL;nodo_i=nodo_i->sig){
		for(nodo_j=nodo_i->sig;nodo_j!=NULL;nodo_j=nodo_j->sig){
			if(nodo_i->Ciclo > nodo_j->Ciclo){
				//MENOR A MAYOR ----> ">"
				ProcJalt=nodo_i->ProcJ;
				ProcPalt=nodo_i->ProcP;
				Tiempoalt=nodo_i->Tiempo;
				Cicloalt=nodo_i->Ciclo;
				Edoalt=nodo_i->Edo;
				Memalt=nodo_i->Mem;
				TipoPalt=nodo_i->TipoP;
				Dispalt=nodo_i->Disp;
				Archialt=nodo_i->Archi;
				Tipoalt=nodo_i->Tipo;
				acumulaalt=nodo_i->acumula;
				esperaalt=nodo_i->espera;
				
				nodo_i->ProcJ=nodo_j->ProcJ;
				nodo_i->ProcP=nodo_j->ProcP ;
				nodo_i->Tiempo=nodo_j->Tiempo;
				nodo_i->Ciclo=nodo_j->Ciclo;
				nodo_i->Edo=nodo_j->Edo;
				nodo_i->Mem=nodo_j->Mem;  
				nodo_i->TipoP=nodo_j->TipoP; 
				nodo_i->Disp=nodo_j->Disp;
				nodo_i->Archi=nodo_j->Archi;
				nodo_i->Tipo=nodo_j->Tipo;
				nodo_i->acumula=nodo_j->acumula;
				nodo_i->espera=nodo_j->espera;
				
				nodo_j->ProcJ=ProcJalt;
				nodo_j->ProcP=ProcPalt;
				nodo_j->Tiempo=Tiempoalt;
				nodo_j->Ciclo=Cicloalt;
				nodo_j->Edo=Edoalt;
				nodo_j->Mem=Memalt;
				nodo_j->TipoP=TipoPalt;
				nodo_j->Disp=Dispalt;
				nodo_j->Archi=Archialt;
				nodo_j->Tipo=Tipoalt;
				nodo_j->acumula=acumulaalt;
				nodo_j->espera=esperaalt;
			}
		} 
	}  
}
