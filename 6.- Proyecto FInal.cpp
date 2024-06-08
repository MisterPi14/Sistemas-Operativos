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
void Ver_Bloc_de_Cont(void);
void Ver_Bloc_de_Cont_Sem(void);
void RR(void);

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
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, Tipo, CicloSC, IniSC, DuracionSC, masc;
	struct nodo_BdC*sig;
};

nodo_TT *Pt, *Qt, *Nuevot, *Auxt;
nodo_MPT *Pp, *Qp, *Nuevop, *Auxp;
nodo_BdC *Pc, *Qc, *Nuevoc, *Auxc, *Pivotec;

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
				Pc->Tipo=0+rand()%2;
				Pc->CicloSC=0;
				aux=Pc->Ciclo+1;
				Pc->IniSC=0+rand()%aux;
				if(Pc->IniSC==0){
					Pc->DuracionSC=0;
				}else if(Pc->IniSC==aux-1){
					Pc->DuracionSC=1;
				}else if(Pc->IniSC==aux-2){
					Pc->DuracionSC=1+rand()%2;
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
				Nuevoc->Tipo=0+rand()%2;
				Nuevoc->CicloSC=0;
				aux=Nuevoc->Ciclo+1;
				Nuevoc->IniSC=0+rand()%aux;
				if(Nuevoc->IniSC==0){
					Nuevoc->DuracionSC=0;
				}else if(Nuevoc->IniSC==aux-1){
					Nuevoc->DuracionSC=1;
				}else if(Nuevoc->IniSC==aux-2){
					Nuevoc->DuracionSC=1+rand()%2;
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

void Ver_Bloc_de_Cont(void){
	system("cls");
	cout<<"\nBloque de control de procesos (PCB)\n";
	cout<<"\nProceso | T.Llegada | Ciclos | Edo | Memoria | CPU/E/S | Tipo     | CicSC | IniSC | DuracionSC\n";
	Auxc=Pc;
	do{
		if(Auxc->masc==0){
			cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<"    | ";
			cout<<setw(9)<<left<<Auxc->Tiempo<<"| ";
			cout<<setw(6)<<left<<Auxc->Ciclo<<"| ";
			cout<<setw(4)<<left<<Auxc->Edo<<"| ";
			cout<<setw(8)<<left<<Auxc->Mem<<"| ";
			if(Auxc->TipoP==0){
				cout<<setw(7)<<left<<"CPU | ";
			}else if(Auxc->TipoP==1){
				cout<<setw(7)<<left<<"S   | ";
			}else if(Auxc->TipoP==2){
				cout<<setw(7)<<left<<"E   | ";
			}
			if(Auxc->Tipo==0){
				cout<<setw(8)<<left<<"Usuario | ";
			}else if(Auxc->Tipo==1){
				cout<<setw(8)<<left<<"Sistema | ";
			}
			cout<<setw(5)<<left<<Auxc->CicloSC<<"| ";
			cout<<setw(5)<<left<<Auxc->IniSC<<"| ";
			cout<<Auxc->DuracionSC<<"\n";
		}
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	
	cout<<"\n";
	Ver_Bloc_de_Cont_Sem();

void Ver_Bloc_de_Cont_Sem(void){
	cout<<"\nPCB semaforo\n";
	cout<<"\nProceso|T.Llegada|Ciclos|Edo|Memoria|CPU/E/S|Tipo     |CicSC|IniSC|DuracionSC\n";
	Auxc=Pc;
	do{
		if(Auxc->masc==1){
			cout<<"J"<<Auxc->ProcJ<<"P"<<Auxc->ProcP<<"    | ";
			cout<<setw(9)<<left<<Auxc->Tiempo<<"| ";
			cout<<setw(6)<<left<<Auxc->Ciclo<<"| ";
			cout<<setw(4)<<left<<Auxc->Edo<<"| ";
			cout<<setw(8)<<left<<Auxc->Mem<<"| ";
			if(Auxc->TipoP==0){
				cout<<setw(7)<<left<<"CPU | ";
			}else if(Auxc->TipoP==1){
				cout<<setw(7)<<left<<"S   | ";
			}else if(Auxc->TipoP==2){
				cout<<setw(7)<<left<<"E   | ";
			}
			if(Auxc->Tipo==0){
				cout<<setw(8)<<left<<"Usuario | ";
			}else if(Auxc->Tipo==1){
				cout<<setw(8)<<left<<"Sistema | ";
			}
			cout<<setw(5)<<left<<Auxc->CicloSC<<"| ";
			cout<<setw(5)<<left<<Auxc->IniSC<<"| ";
			cout<<Auxc->DuracionSC<<"\n";
		}
		Auxc=Auxc->sig;
	}while(Auxc!=NULL);
	
	cout<<"\n";
	system("pause");
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
			Auxc->CicloSC=Auxc->CicloSC+1;
			if(Auxc->CicloSC==Auxc->IniSC){
				Auxc->Edo=4;
				Auxc->masc=1;
				//////////////////////////////////////////
				Pivotec=Auxc;
				Ver_Bloc_de_Cont();	//Mostrar la tabla
				Auxc=Pivotec;
				//////////////////////////////////////////
			}else{
				Auxc->Ciclo=(Auxc->Ciclo)-1;
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
				contadorsem++;
				//////////////////////////////////////////
				Pivotec=Auxc;
				Ver_Bloc_de_Cont();	//Mostrar la tabla
				Auxc=Pivotec;
				//////////////////////////////////////////
			}
			if(contadorsem==ContadorGlobal){
				cout<<"\n";
				break;
			}
		}
		Auxc=Auxc->sig;
		if(Auxc==NULL){
			Auxc=Pc;
		}
	}
}
