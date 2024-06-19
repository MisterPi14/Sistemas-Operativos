#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
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
void manejadorInter(void);

struct nodo_TT{
	int NoTarea, tamanio, LocPMT, totalP, Sec[Arr];
	struct nodo_TT*sig;
};

struct nodo_MPT{
	int NoPag, NoT, Celex, ContS;
	struct nodo_MPT*sig;
};

struct nodo_BdC{
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, CicloSC, IniSC, DuracionSC, masc, VectorInt;
	struct nodo_BdC*sig;
};

struct nodo_sem{
	int ProcJ, ProcP, Tiempo, Ciclo, Edo, Mem, TipoP, Tipo, CicloSC, IniSC, DuracionSC, masc, Wsem, Ssig, VectorInt;
	struct nodo_sem*sig;
};

nodo_TT *Pt, *Qt, *Nuevot, *Auxt;
nodo_MPT *Pp, *Qp, *Nuevop, *Auxp;
nodo_BdC *Pc, *Qc, *Nuevoc, *Auxc, *Pivotec, *ImpresionPCB;
nodo_sem *Ps, *Qs, *Nuevos, *Auxs, *Pivotes, *ImpresionSem;
bool sem=1;

const char* TablaVecInt[] = {
        "Error de División",                      // 0
        "Excepción de Depuración",                // 1
        "Interrupción No Mascable",               // 2
        "Excepción de Punto de Interrupción",     // 3
        "Excepción de Desbordamiento",            // 4
        "Excepción de Rango Excedido",            // 5
        "Excepción de Código de Operación Inválido", // 6
        "Excepción de Dispositivo No Disponible", // 7
        "Excepción de Doble Falla",               // 8
        "Excepción de Segmento de Coprocesador",  // 9
        "Excepción de TSS Inválida",              // 10
        "Excepción de Segmento No Presente",      // 11
        "Excepción de Falla de Segmento de Pila", // 12
        "Excepción de Protección General",        // 13
        "Excepción de Falla de Página",           // 14
        "Reservado",                              // 15
        "Excepción de Punto Flotante x87",        // 16
        "Excepción de Chequeo de Alineación",     // 17
        "Excepción de Chequeo de Máquina",        // 18
        "Excepción de Punto Flotante SIMD",       // 19
        "Excepción de Virtualización",            // 20
        "Reservado",                              // 21
        "Reservado",                              // 22
        "Reservado",                              // 23
        "Reservado",                              // 24
        "Reservado",                              // 25
        "Reservado",                              // 26
        "Reservado",                              // 27
        "Reservado",                              // 28
        "Reservado",                              // 29
        "Reservado",                              // 30
        "Reservado",                              // 31
        "IRQ0 - Temporizador del Sistema",        // 32 AQUI ACABAN LAS EXCEPCIONES Y ERRORES
        "IRQ1 - Teclado",                         // 33
        "IRQ2 - Cascada para Controlador Esclavo 8259A", // 34
        "IRQ3 - COM2",                            // 35
        "IRQ4 - COM1",                            // 36
        "IRQ5 - LPT2",                            // 37
        "IRQ6 - Disquete",                        // 38
        "IRQ7 - LPT1",                            // 39
        "IRQ8 - Reloj en Tiempo Real CMOS",       // 40
        "IRQ9 - Libre para periféricos",          // 41
        "IRQ10 - Libre para periféricos",         // 42
        "IRQ11 - Libre para periféricos",         // 43
        "IRQ12 - Ratón PS/2",                     // 44
        "IRQ13 - FPU / Coprocesador",             // 45
        "IRQ14 - Disco Duro ATA Primario",        // 46
        "IRQ15 - Disco Duro ATA Secundario",      // 47
        "Asignado dinámicamente para dispositivos PCI", // 48-223
        "Reservado para vectores de alta prioridad", // 224-254
        "Interrupciones Definidas por el Usuario (para uso de hardware y software)" // 255
    };
const int InterrSel[] = {0, 4, 20, 10, 12, 33, 43, 40, 47, 44};//Las primeras 5 son ex o errores, las ultimas 5 son interrupciones de e/s

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
				Pt->Sec[k]=1+rand()%Pt->totalP;
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
				Nuevot->Sec[k]=1+rand()%Nuevot->totalP;
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
				//Asignando codigo de interrupcion y haciendo que no tenga nada en inicio de sc ni en duracion sc
				(Pc->TipoP == 0)?Pc->VectorInt=InterrSel[0+rand()%5]:Pc->VectorInt=InterrSel[0+rand()%10];
				(Pc->VectorInt<32)?Pc->IniSC=0:Pc->IniSC=1+rand()%Pc->Ciclo;
				////////////
				if(Pc->IniSC==0){
					Pc->DuracionSC=0;
				}else if(Pc->IniSC==Pc->Ciclo){
					Pc->DuracionSC=1;
				}else if(Pc->IniSC==Pc->Ciclo-1){
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
				Nuevoc->CicloSC=0;
				//Asignando codigo de interrupcion y haciendo que no tenga nada en inicio de sc ni en duracion sc
				(Nuevoc->TipoP == 0)?Nuevoc->VectorInt=InterrSel[0+rand()%5]:Nuevoc->VectorInt=InterrSel[0+rand()%10];
				(Nuevoc->VectorInt<32)?Nuevoc->IniSC=0:Nuevoc->IniSC=1+rand()%Nuevoc->Ciclo;
				////////////
				if(Nuevoc->IniSC==0){
					Nuevoc->DuracionSC=0;
				}else if(Nuevoc->IniSC==Nuevoc->Ciclo){
					Nuevoc->DuracionSC=1;
				}else if(Nuevoc->IniSC==Nuevoc->Ciclo-1){
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


void Ver_Bloc_de_Cont(bool ImpSem){
	system("cls");
    printf("\n-----(PCB) BLOQUE DE CONTROL DE PROCESOS-----");
    ImpresionPCB=Pc;	char Tipo[20];
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------");
    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%3s|%s%0s|%s%2s|%s%2s|\n","Proceso","","T-Llegada","",
	"Ciclos","","Estados","","Memoria","","CPU o E/s","","Ciclos SC","","Inicio inter","","DuracionSC","","Cod Interr","");
    printf("-----------------------------------------------------------------------------------------------------------------------------------");
    while(ImpresionPCB != NULL){
    	if(ImpresionPCB->masc==0){
	    	if(ImpresionPCB->TipoP == 0){
	            snprintf(Tipo, sizeof(Tipo), "CPU");
	        } else if(ImpresionPCB->TipoP == 1){
	            snprintf(Tipo, sizeof(Tipo), "E");
	        } else if(ImpresionPCB->TipoP == 2){
	            snprintf(Tipo, sizeof(Tipo), "S");
	        }
	        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6d%6s|%6d%6s|","",ImpresionPCB->ProcJ,
			ImpresionPCB->ProcP,(ImpresionPCB->ProcP>=10||ImpresionPCB->ProcJ>=10)?"  ":"   ",ImpresionPCB->Tiempo,"",ImpresionPCB->Ciclo,"",
			ImpresionPCB->Edo,"",ImpresionPCB->Mem,"",Tipo,"",ImpresionPCB->CicloSC,"",ImpresionPCB->IniSC,"",ImpresionPCB->DuracionSC,"",ImpresionPCB->VectorInt,"");
		}
		ImpresionPCB=ImpresionPCB->sig;
    }
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------\n");	
	cout<<"\n";
	if(ImpSem)
	Ver_Bloc_de_Cont_sem();
}
void Ver_Bloc_de_Cont_sem(void){
    printf("\n-----(PCB) Semaforo-----");
    ImpresionSem=Ps;	char Tipo[20];
    printf("\n\t\t\t\t\t\t\t\t\tSemaforo: %d",sem);
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%3s|%s%0s|%s%2s|%s%2s|%s%2s|\n","Proceso","","T-Llegada","",
	"Ciclos","","Estados","","Memoria","","CPU o E/s","","Ciclos SC","","Inicio inter","","DuracionSC","","Wait(S)","","Signal(S)","");
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
			Ps->VectorInt=Auxc->VectorInt;
			Ps->Wsem=1;
			Ps->Ssig=0;
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
			Nuevos->VectorInt=Auxc->VectorInt;
			Nuevos->sig=NULL;
			Qs->sig=Nuevos;
			Qs=Nuevos;	
		}
	} 
}  
   
void RR(void){
	int contadorsem=0;
	int quantum;
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
		quantum=Quan;
		Ver_Bloc_de_Cont();	//Mostrar tablas
		while(Auxc->Ciclo>0 && quantum>0 && Auxc->masc==0){
			manejadorInter();
			Auxc->CicloSC++;
			Auxc->Ciclo--;
			if(Auxc->CicloSC==Auxc->IniSC && Auxc->DuracionSC!=0){
				Ver_Bloc_de_Cont();	//Mostrar tablas
				confirm=1;
				Auxc->Edo=4;
				Auxc->masc=1;
				Auxc->DuracionSC--;
				Bloc_de_Cont_sem();
				quantum=0;
			}
			Ver_Bloc_de_Cont();	//Mostrar tablas
			quantum--;
		}
		if(Auxc->Ciclo>0 && Auxc->masc==0){
			Auxc->Edo=4;
			Ver_Bloc_de_Cont();	//Mostrar tablas
		}
		if(Auxc->Ciclo==0){
			if(Auxc->Edo!=5){
				Auxc->Edo=5;
				Ver_Bloc_de_Cont();	//Mostrar tablas
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
				sem=1;
				Ver_Bloc_de_Cont();	//Mostrar la tablas
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
				Auxs->Ciclo--;
				Auxs->CicloSC++;
				Auxs->DuracionSC--;
				sem=0;
			}
		}
	}
}

void devolucion(void){
	Pivotec=Pc;
	do{
		if(Pivotec->Tiempo==Auxs->Tiempo){
			Pivotec->masc=Auxs->masc;
			Pivotec->CicloSC=Auxs->CicloSC;
			Pivotec->IniSC=Auxs->IniSC;
			Pivotec->DuracionSC=Auxs->DuracionSC;
			Pivotec->Edo=Auxs->Edo;
			Pivotec->Ciclo=Auxs->Ciclo;
		}
		Pivotec=Pivotec->sig;
	}while(Pivotec!=NULL);
}

void manejadorInter(void){
	if(Auxc->VectorInt<32){
		system("cls");	
		printf("------------------------------------------------------------------------\n");
		printf("|\t\tEl programa genero una interrupcion\n|\tDescripcion: %s\n",TablaVecInt[Auxc->VectorInt]);
		printf("------------------------------------------------------------------------\n\n");
		printf("Aceptar -> <enter>\n\n");
		Auxc->masc=2;
		system("pause");	
	}
	else if(Auxc->TipoP!=0){
		semaforo();
	}
}