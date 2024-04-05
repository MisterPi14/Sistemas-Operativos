#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>

#define CapMemoria 5
#define PrefijoMemoria "MB"
#define CapMarco 10
#define PrefijoMarco "KB"
#define CapSO 20
#define PrefijoCapSO "KB"

#define nTareas 20
#define LineasPorPagina 100

using namespace std;

int Prefijos(string);
int Calculos();
void Crear_MMT();
void Crear_JT();
void Crear_PMT();
void paginacionSimple();
void Seleccion();
void imprimir(int);

struct MMT{
	int nMarco;
	int LocInicio;
	bool Estado;
	MMT *sig;
};

struct PMT;

struct JT{
	int nTarea;
	int nLineas;
	PMT *LocPMT;
	JT *sig;
};

struct PMT{
	int nPagina;
	int LocMarco;
	PMT *sig;
};

MMT *PMMT, *QMMT, *NuevoMMT, *AuxMMT;
JT *PJT, *QJT, *NuevoJT, *AuxJT;
PMT *PPMT[nTareas], *QPMT[nTareas], *NuevoPMT, *AuxPMT;

int main(){
	Crear_MMT();
	Crear_JT();
	Crear_PMT();
	paginacionSimple();
	Seleccion();
}

void Seleccion(){
	int op=0;
	imprimir(op);
	char tecla;
    do {
        tecla = _getch(); // Espera a que se presione una tecla sin esperar por Enter
        if (tecla == 77) { // Flecha derecha (código ASCII)
            (op==2)?:op++;
        } else if (tecla == 75 && op>=0 && op<3) { // Flecha izquierda (código ASCII)
            (op==0)?:op--;
        }
        system("cls");
        imprimir(op);
    }while (tecla != 27); // Sale del bucle cuando se presiona la tecla Esc (27 es el código ASCII de Esc)
}

int Prefijos(string cadena){
	if(cadena=="MB"){
		return 1048576;
	}
	else if(cadena=="KB"){
		return 1024;
	}
	else if(cadena=="B"){
		return 1;
	}
	else{
		return 0;
	}
}

int Calculos(){
	int capacidadMemoria = CapMemoria * Prefijos(PrefijoMemoria);
	int capacidadMarco = CapMarco * Prefijos(PrefijoMarco);
	return capacidadMemoria/capacidadMarco;
}

void Crear_MMT(){
	int nMarcos = Calculos();
	for(int i=0; i<nMarcos; i++){
		if(PMMT==NULL){
			PMMT = (MMT*)malloc(sizeof(MMT));
			PMMT->Estado=0;
			PMMT->nMarco=0;
			PMMT->LocInicio=0;
			PMMT->sig = NULL;
			QMMT = PMMT;
		}	
		else{
			NuevoMMT = (MMT*)malloc(sizeof(MMT));
			NuevoMMT->Estado=0;//0 libre, 1 ocupado
			NuevoMMT->LocInicio=CapMarco*i;
			NuevoMMT->nMarco=i;
			NuevoMMT->sig = NULL;
			
			QMMT->sig = NuevoMMT;
			QMMT = NuevoMMT;
			//free(NuevoMMT);
		}
	}
}

void Crear_JT(){
	for(int i=1; i<=nTareas; i++){
		if(PJT==NULL){
			PJT = (JT*)malloc(sizeof(JT));
			PJT->nTarea=1;
			PJT->nLineas=100+rand()%901;
			PJT->LocPMT=0;
			PJT->sig=NULL;
			QJT=PJT;
		}
		else{
			NuevoJT = (JT*)malloc(sizeof(JT));
			NuevoJT->nTarea=i;
			NuevoJT->nLineas=100+rand()%901;
			NuevoJT->LocPMT=0;
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
				PPMT[i]->LocMarco=0;
				PPMT[i]->sig=NULL;
				QPMT[i]=PPMT[i];
				AuxJT->LocPMT=PPMT[i];
			}
			else{
				NuevoPMT = (PMT*)malloc(sizeof(PMT));
				NuevoPMT->nPagina=j;
				NuevoPMT->LocMarco=0;
				NuevoPMT->sig=NULL;
				QPMT[i]->sig=NuevoPMT;
				QPMT[i]=NuevoPMT;
			}
		}
		AuxJT=AuxJT->sig;
	}
}

void paginacionSimple(){
	int marcosLibres = QMMT->nMarco + 1;
	//Asignacion So
	int cMarco = CapMarco * Prefijos(PrefijoMarco);
	int cSo = CapSO * Prefijos(PrefijoCapSO);
	AuxMMT = PMMT;
	AuxJT=PJT;
	for(int i=0; i<cSo/cMarco; i++){
		!(AuxMMT->Estado==0)?:AuxMMT->Estado=1;
		AuxMMT=AuxMMT->sig;
		AuxJT=AuxJT->sig;
		marcosLibres--;
	}
	//Asignacion de los demas programas
	
	AuxPMT=AuxJT->LocPMT;
	
	for(int j=cSo/cMarco; j<nTareas; j++){
		int nPaginas = AuxJT->nLineas/LineasPorPagina;
		AuxJT->nLineas%LineasPorPagina==0?:nPaginas++;
		if(marcosLibres>=nPaginas){//si quedan suficientes marcos para la tarea entrante?
			while(AuxPMT!=NULL){
				AuxMMT->Estado=1;
				AuxPMT->LocMarco=AuxMMT->LocInicio;
				AuxMMT=AuxMMT->sig;
				AuxPMT=AuxPMT->sig;
				marcosLibres--;
			}
			if(AuxJT->sig!=NULL){//si viene otra tarea, trae la lista de mapa de paginas que le corresponde
				AuxJT=AuxJT->sig;
				AuxPMT=AuxJT->LocPMT;
			}
		}
		else{
			break;
		}
	}
} 

/*
void crearTablaMT(void)
{
    aux = Plista;
    temp = Tlista;
    int contadorMarcos = 0;
    nodoTM *contador = Plista;
    while (contador != NULL)
    {
        contadorMarcos++;
        contador = contador->sig;
    }
    contadorMarcos = contadorMarcos - so;
    int i = 0;
    while (i < nTareas)
    {
        if (contadorMarcos >= temp->nPaginas)
        {
            if (aux->estado == 0)
            {
                for (int j = 0; j < temp->nPaginas; j++)
                {
                    if (PMTlista[i] == NULL)
                    {
                        PMTlista[i] = (nodoMMT *)malloc(sizeof(nodoMMT));
                        PMTlista[i]->npagina = j;
                        PMTlista[i]->locMarco = aux->locInicio;
                        contadorMarcos--;
                        PMTlista[i]->sig = NULL;
                        QPTM[i] = PMTlista[i];
                        aux->estado = 1;
                        aux = aux->sig;
                    }
                    else
                    {
                        NuevoPTM[i] = (nodoMMT *)malloc(sizeof(nodoMMT));
                        NuevoPTM[i]->npagina = j;
                        NuevoPTM[i]->locMarco = aux->locInicio;
                        contadorMarcos--;
                        NuevoPTM[i]->sig = NULL;
                        QPTM[i]->sig = NuevoPTM[i];
                        QPTM[i] = NuevoPTM[i];
                        aux->estado = 1;
                        aux = aux->sig;
                    }
                }
                temp = temp->sig;
                i++;
            }
            else
            {
                aux = aux->sig;
            }
        }
        else
        {
            for (int j = 0; j < temp->nPaginas; j++)
                {
                    if (PMTlista[i] == NULL)
                    {
                        PMTlista[i] = (nodoMMT *)malloc(sizeof(nodoMMT));
                        PMTlista[i]->npagina = j;
                        PMTlista[i]->locMarco = 0;
                        PMTlista[i]->sig = NULL;
                        QPTM[i] = PMTlista[i];
                    }
                    else
                    {
                        NuevoPTM[i] = (nodoMMT *)malloc(sizeof(nodoMMT));
                        NuevoPTM[i]->npagina = j;
                        NuevoPTM[i]->locMarco = 0;
                        NuevoPTM[i]->sig = NULL;
                        QPTM[i]->sig = NuevoPTM[i];
                        QPTM[i] = NuevoPTM[i];
                    }
                }
            temp = temp->sig;
            i++;
        }
        if(aux == NULL)
        {
            aux = Plista;
        }
    }
}
*/

void imprimir(int tabla){
	switch(tabla){
		case 0:
			printf("-----TABLA DE MAPA DE MEMORIA-----\n");
			AuxMMT = (MMT*)malloc(sizeof(MMT));
			AuxMMT = PMMT;
			printf("|%-12s | %-12s | %-12s|\n","No.Marco","Loc.Inicio","Estado");
			printf("--------------------------------------------\n");
			while(AuxMMT!=NULL){
				printf("|%-12d | %-10d%s | %-12d| \n",AuxMMT->nMarco,AuxMMT->LocInicio,PrefijoMarco,AuxMMT->Estado);
				AuxMMT=AuxMMT->sig;
			}
			break;
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
			printf("-----TABLA DE MAPA DE PAGINAS-----\n");
			for(int k=0; k<nTareas; k++){
				AuxPMT=PPMT[k];
				while(AuxPMT!=NULL){
					printf("\n%d\n",AuxPMT->nPagina);
					AuxPMT=AuxPMT->sig;
				}
				printf("-------------------------------");
			}
			break;
	}
}

