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
//Paginacion por demanda
#define nTiempos 5
#define marcosPorPagina 3
#define tareaEjecucion 4

using namespace std;

struct PMT;

int Prefijos(string);
int Calculos();
void Crear_MMT();
void Crear_JT();
void Crear_PMT();
void Seleccion();
void imprimir(int);
void asignacionDelSo();
//Paginacion simple
void paginacionSimple();
//Paginacion por demanda
void paginacionPorDemanda();
void algoritmoAdminMem();
void swappingFIFO(PMT*);

int cola[marcosPorPagina]={0};
int fin=-1;

struct MMT{
	int nMarco;
	int LocInicio;
	bool Estado;
	MMT *sig;
};

struct JT{
	int nTarea;
	int nLineas;
	int LocPMT;
	int Secuencia[nTiempos];
	PMT *VinculoPMT;
	int nPaginas;
	JT *sig;
};

struct PMT{
	int nPagina;
	int LocMarco;
	bool estado;
	bool referencia;
	bool modificacion;
	JT *VinculoJT;
	PMT *sig;
};

struct PMTE{//PMTExecute -> pagina en ejecucion
	int nPagina;
	int LocMarco;
	bool estado;
	bool referencia;
	bool modificacion;
	JT *VinculoJT;
	PMT *sig;};

MMT *PMMT, *QMMT, *NuevoMMT, *AuxMMT;
JT *PJT, *QJT, *NuevoJT, *AuxJT;
PMT *PPMT[nTareas], *QPMT[nTareas], *NuevoPMT, *AuxPMT;

int main(){
	Crear_MMT();
	Crear_JT();
	Crear_PMT();
	asignacionDelSo();
	paginacionPorDemanda();
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
		}
	}
}

void Crear_JT(){
	for(int i=1; i<=nTareas; i++){
		if(PJT==NULL){
			PJT = (JT*)malloc(sizeof(JT));
			PJT->nTarea=1;
			PJT->nLineas=100+rand()%901;
			PJT->LocPMT=1010;
			PJT->nPaginas = PJT->nLineas/LineasPorPagina;//el n paginas es la / de lineas sobre l00 en este ejemplo
			PJT->nLineas%LineasPorPagina==0?:PJT->nPaginas++;//si la division no es exacta añade un espacio extra
			for(int i=1; i<nTiempos; i++){
				PJT->Secuencia[i]=0+rand()%PJT->nPaginas;
			}
			PJT->Secuencia[0]=0;
			PJT->sig=NULL;
			QJT=PJT;
		}
		else{
			NuevoJT = (JT*)malloc(sizeof(JT));
			NuevoJT->nTarea=i;
			NuevoJT->nLineas=100+rand()%901;
			NuevoJT->LocPMT=1010+i-1;
			NuevoJT->nPaginas = NuevoJT->nLineas/LineasPorPagina;//el n paginas es la / de lineas sobre l00 en este ejemplo
			NuevoJT->nLineas%LineasPorPagina==0?:NuevoJT->nPaginas++;//si la division no es exacta añade un espacio extra
			for(int i=1; i<nTiempos; i++){
				NuevoJT->Secuencia[i]=0+rand()%NuevoJT->nPaginas;
			}
			NuevoJT->Secuencia[0]=0;
			NuevoJT->sig=NULL;
			QJT->sig=NuevoJT;
			QJT=NuevoJT;
		}
	}
}

void Crear_PMT(){
	AuxJT=PJT;
	for(int i=1; i<nTareas+1; i++){
		for(int j=0; j<AuxJT->nPaginas; j++){
			if(PPMT[i]==NULL){
				PPMT[i] = (PMT*)malloc(sizeof(PMT));
				PPMT[i]->nPagina=j;
				PPMT[i]->LocMarco=0;
				PPMT[i]->VinculoJT=AuxJT;
				PPMT[i]->estado=0;
				PPMT[i]->referencia=0;
				PPMT[i]->modificacion=0;
				PPMT[i]->sig=NULL;
				QPMT[i]=PPMT[i];
				AuxJT->VinculoPMT=PPMT[i];
			}
			else{
				NuevoPMT = (PMT*)malloc(sizeof(PMT));
				NuevoPMT->nPagina=j;
				NuevoPMT->LocMarco=0;	
				NuevoPMT->VinculoJT=AuxJT;	
				NuevoPMT->estado=0;
				NuevoPMT->referencia=0;
				NuevoPMT->modificacion=0;
				NuevoPMT->sig=NULL;		
				QPMT[i]->sig=NuevoPMT;
				QPMT[i]=NuevoPMT;
			}
		}
		AuxJT=AuxJT->sig;
	}
}

void asignacionDelSo(){
	int marcosLibres = QMMT->nMarco + 1;
	//Asignacion So
	int cMarco = CapMarco * Prefijos(PrefijoMarco);
	int cSo = CapSO * Prefijos(PrefijoCapSO);
	AuxMMT = PMMT;
	int nBloquesParaSo = cSo/cMarco;
	cSo%cMarco==0?:nBloquesParaSo++;
	for(int i=0; i<nBloquesParaSo; i++){
		!(AuxMMT->Estado==0)?:AuxMMT->Estado=1;
		AuxMMT=AuxMMT->sig;
		marcosLibres--;
	}
}
/*
void paginacionSimple(){

	
	//Asignacion de los demas programas
	AuxJT=PJT;
	AuxPMT=AuxJT->VinculoPMT;
	
	for(int j=0; j<nTareas; j++){//Se deben ocupar 101 marcos 
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
				AuxPMT=AuxJT->VinculoPMT;
			}Si esta condicion ve que ya no existe tarea alguna, no programa el frenado 
			del ciclo pues en el for nTareas coincide con el numero de nodos en JT
		}
		else{//solo se ejecuta si ya no hay espacio para la tarea actual
			break;
		}
	}
}*/

void Fifo(int,int);
void eliminarHuecos();

void paginacionPorDemanda(){
	AuxPMT = PPMT[tareaEjecucion];//AuxPMT se queda con la tarea que le pedimos
	algoritmoAdminMem();
	//algoritmoFIFO(int cola[])
	Seleccion();
}

void algoritmoAdminMem(){
	int marcosLibres = marcosPorPagina;
	for(int i=0; i<nTiempos; i++){
		AuxPMT = PPMT[tareaEjecucion];//iniciando el el primer nodo
		int paginaActual = AuxPMT->VinculoJT->Secuencia[i];//obteniendo las paginas de la secuencia
		while(AuxPMT->sig!=NULL){//Legando a la pagina que deseamos consultar
			if(AuxPMT->nPagina==paginaActual){break;}
			AuxPMT=AuxPMT->sig;
		}
		//Leyendo el estado
		if(AuxPMT->estado==1){//si esta cargada en memoria fisica
			AuxPMT->estado=1;
			AuxPMT->referencia=1;
			//Imprimir
			AuxPMT->referencia=0;
		}
		else{//Si esta en memoria virtual
			if(marcosLibres>0){//Si aun quedan marcos
				AuxPMT->estado=1;
				AuxPMT->referencia=1;
				//Imprimir
				AuxPMT->referencia=0;
				AuxPMT->LocMarco=AuxMMT->LocInicio;
				AuxMMT=AuxMMT->sig;
				marcosLibres--;
				Fifo(1,paginaActual);
			}
			else{
				swappingFIFO(AuxPMT);
			}
		}
	}
	/*
	Fifo(1,6);
	Fifo(1,8);
	Fifo(1,5);
	Fifo(2,0);*/
}

void swappingFIFO(PMT *AuxPMT){
	int Candidata = cola[0];
	NuevoPMT = PPMT[tareaEjecucion];
	while(NuevoPMT->sig!=NULL){//Legando a la pagina que deseamos remplazar
		if(NuevoPMT->nPagina==Candidata){break;}
		NuevoPMT=NuevoPMT->sig;
	}
	//Tarea en transito
	AuxPMT->LocMarco=NuevoPMT->LocMarco;
	AuxPMT->estado=1;
	AuxPMT->referencia=1;
	AuxPMT->referencia=0;
	//Tarea con mas tiempo en memoria
	NuevoPMT->LocMarco=0;
	NuevoPMT->estado=0;
	NuevoPMT->referencia=0;
	//Entrada y salida en la cola 
	Fifo(2,0);//elinamos la vieja tarea
	Fifo(1,AuxPMT->nPagina);//actualizamos con la nueva
}


void Fifo(int ope,int pagina)
{
	switch(ope)
	{
		case 1://Entrada
			if(fin<7)
			{
				fin++;
				cola[fin]=pagina;
			}
			else
			{//Aqui se debera sacar la pagina candidata
				
			}

			break;
		case 2://salida
			if(fin>=0)
			{
				cola[0]=0;
				eliminarHuecos();
				fin--;
			}
			else//en teoria este no se hace pues nunca se vaciara
			{
				
			}
			break;
	}
}

void eliminarHuecos()
{
	int array_aux[marcosPorPagina]={0};
	int j=0;
	
	for (int i=0;i<=fin;i++)
	{
		if(cola[i]!=0)
		{
			array_aux[j]=cola[i];
			j++;
		}		
	}
	
	for (int i=0;i<=fin;i++)
	{
		cola[i]=0;
	}
	for (int i=0;i<=fin;i++)
	{
		cola[i]=array_aux[i];
	}
}


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
				printf("|%-12d | %-12d | %-12d| %-12d|",AuxJT->nTarea,AuxJT->nLineas,AuxJT->LocPMT,AuxJT->nPaginas);
				for(int i=0; i<nTiempos; i++){
					printf("%d",AuxJT->Secuencia[i]);
				}
				printf("\n");
				AuxJT=AuxJT->sig;
			}
			break;
		case 2:
			printf("-----TABLA DE MAPA DE PAGINAS-----\n\n");
				AuxPMT=PPMT[tareaEjecucion];
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				printf("           ");for(int i=0; i<nTiempos; i++){printf("-----");}
				printf("-\nSecuencia: ");
				for(int i=0; i<nTiempos; i++){
					printf("|%2c%d%1s",'P',AuxPMT->VinculoJT->Secuencia[i],"");
				}
				printf("|\n           -");for(int i=0; i<nTiempos; i++){printf("-----");}
				////////////////////////////////////////////////////////////////////////////////////////////////////////
				printf("\n\n-----------------------Mapa de pagina de J%d---------------------%s\n",tareaEjecucion,tareaEjecucion>8?"":"-");
				printf("|   Pagina   |   Marco   |   Estado   | Referencia |Modificacion|\n");
				while(AuxPMT!=NULL){
					printf("|%6d%6s|%-9d%s|%6d%6s|%6d%6s|%6d%6s|\n",AuxPMT->nPagina,"",AuxPMT->LocMarco,PrefijoMarco,AuxPMT->estado,"",AuxPMT->referencia,"",AuxPMT->modificacion,"");
					AuxPMT=AuxPMT->sig;
				}
				printf("-----------------------------------------------------------------\n\n");
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				printf("      -");for(int i=0; i<marcosPorPagina; i++){printf("-----");}
				printf("\nCola: ");
				for(int i=0; i<marcosPorPagina; i++){
					printf("|%2c%d%1s",'P',cola[i],"");
				}
				printf("|\n      -");for(int i=0; i<marcosPorPagina; i++){printf("-----");}
			break;
	}
}

