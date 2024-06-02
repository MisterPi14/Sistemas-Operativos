#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>

#define nTareas 5
#define LineasPorPagina 100

using namespace std;

struct PMT;

struct JT {
    int nTarea;
    int nLineas;
    int LocPMT;
    int Secuencia;
    PMT *VinculoPMT;
    JT *sig;
};

struct PMT {
    int nPagina;
    int ciclosCPU;
    bool ejecutar;
    PMT *sig;
};

struct PCB {
    int nTarea; // para identificador de proceso
    int nPagina; // para identificador de proceso
    int TiempoLlegada;
    int CiclosCPU;
    int Estado;
    int Memoria;
    int TipoProceso; // 1->CPU, 2->E, 3->S "los que tengan CPU no llevaran nada en iniSC"
    int nDispositivos;
    int nArchivos;
    bool TipoSolicitud; // Usuario o sistema
    int CicSC; // ciclos de seccion critica
    int IniSC; // Inicio de la seccion critica
    int DuracionSC; // Duracion de seccion critica randon de 1 a 3 ste random debe estar en el rango de donde esta INISC hasta el final
    PCB *sig;
};

// Paginacion Simple
void Crear_JT();
void Crear_PMT();
// Administrador CPU
void CrearPCB();
void Montar();
// Planificadores de procesos
void FCFS();
void SJF();
void porPrioridades();
void RoundRobin();
// Impresion
void Imprimir(int, PCB*);
void ImprimirListaPCB(PCB*); // Declaración de la función

// Variables Globales
int contProcesos = 0;

JT *PJT, *QJT, *NuevoJT, *AuxJT;
PMT *PPMT[nTareas], *QPMT[nTareas], *NuevoPMT, *AuxPMT;
PCB *PPCB, *QPCB, *Impresion, *AuxPCB;
PCB *PPCB2, *QPCB2, *Impresion2, *AuxPCB2;

int main() {
    Crear_JT();
    Crear_PMT();
    CrearPCB();
    AuxPCB = PPCB;
    Imprimir(2, PPCB);
    char tecla; tecla = _getch();
    if (tecla == 13) {
        Imprimir(3, PPCB);
        RoundRobin();
    }
}

void Crear_JT() {
    for (int i = 1; i <= nTareas; i++) {
        if (PJT == NULL) {
            PJT = (JT*)malloc(sizeof(JT));
            PJT->nTarea = 1;
            PJT->nLineas = 100 + rand() % 901;
            PJT->LocPMT = 1010;
            PJT->sig = NULL;
            QJT = PJT;
        } else {
            NuevoJT = (JT*)malloc(sizeof(JT));
            NuevoJT->nTarea = i;
            NuevoJT->nLineas = 100 + rand() % 901;
            NuevoJT->LocPMT = 1010 + i - 1;
            NuevoJT->sig = NULL;
            QJT->sig = NuevoJT;
            QJT = NuevoJT;
        }
    }
}

void Crear_PMT() {
    AuxJT = PJT;
    for (int i = 0; i < nTareas; i++) {
        int nPaginas = AuxJT->nLineas / LineasPorPagina; // el n paginas es la / de lineas sobre l00 en este ejemplo
        AuxJT->nLineas % LineasPorPagina == 0 ? : nPaginas++; // si la division no es exacta añade un espacio extra
        for (int j = 0; j < nPaginas; j++) {
            if (PPMT[i] == NULL) {
                PPMT[i] = (PMT*)malloc(sizeof(PMT));
                PPMT[i]->nPagina = j;
                PPMT[i]->ciclosCPU = 1 + rand() % 15;
                PPMT[i]->ejecutar = 0 + rand() % 2;
                (PPMT[i]->ejecutar == 0) ? : contProcesos++;
                PPMT[i]->sig = NULL;
                QPMT[i] = PPMT[i];
                AuxJT->VinculoPMT = PPMT[i];
            } else {
                NuevoPMT = (PMT*)malloc(sizeof(PMT));
                NuevoPMT->nPagina = j;
                NuevoPMT->ciclosCPU = 1 + rand() % 15;
                NuevoPMT->ejecutar = 0 + rand() % 2;
                (NuevoPMT->ejecutar == 0) ? : contProcesos++;
                NuevoPMT->sig = NULL;
                QPMT[i]->sig = NuevoPMT;
                QPMT[i] = NuevoPMT;
            }
        }
        AuxJT = AuxJT->sig;
    }
}

void CrearPCB() {
    int j = 0;
    for (int i = 0; i < nTareas; i++) {
        AuxPMT = PPMT[i];
        while (AuxPMT != NULL) {
            if (AuxPMT->ejecutar == true) {
                if (PPCB == NULL) {
                    PPCB = (PCB*)malloc(sizeof(PCB));

                    PPCB->nTarea = i + 1;
                    PPCB->nPagina = AuxPMT->nPagina;
                    PPCB->TiempoLlegada = j;
                    PPCB->CiclosCPU = 1 + rand() % 15;
                    PPCB->Estado = 1;
                    PPCB->Memoria = 1 + rand() % 50;
                    PPCB->TipoProceso = 1 + rand() % 3;
                    PPCB->nDispositivos = 1 + rand() % 5;
                    PPCB->nArchivos = 0 + rand() % 11;
                    PPCB->TipoSolicitud = 0 + rand() % 2;
                    PPCB->CicSC = 0;
                    PPCB->IniSC = 0;
                    PPCB->DuracionSC = 0;

                    PPCB->sig = NULL;
                    QPCB = PPCB;
                } else {
                    AuxPCB = (PCB*)malloc(sizeof(PCB));

                    AuxPCB->nTarea = i + 1;
                    AuxPCB->nPagina = AuxPMT->nPagina;
                    AuxPCB->TiempoLlegada = j;
                    AuxPCB->CiclosCPU = 1 + rand() % 15;
                    AuxPCB->Estado = 1;
                    AuxPCB->Memoria = 1 + rand() % 50;
                    AuxPCB->TipoProceso = 1 + rand() % 3;
                    AuxPCB->nDispositivos = 1 + rand() % 5;
                    AuxPCB->nArchivos = 0 + rand() % 11;
                    AuxPCB->TipoSolicitud = 0 + rand() % 2;
                    AuxPCB->CicSC = 0;
                    AuxPCB->IniSC = 0;
                    AuxPCB->DuracionSC = 0;

                    AuxPCB->sig = NULL;
                    QPCB->sig = AuxPCB;
                    QPCB = AuxPCB;
                }
                j++;
            }
            AuxPMT = AuxPMT->sig;
        }
    }
}

void Montar() {
    AuxPCB = PPCB;
    while (AuxPCB != NULL) {
        AuxPCB->Estado = 2;
        AuxPCB = AuxPCB->sig;
    }
}

void RoundRobin() {
    int quantum = 3; // Definir el quantum de tiempo para el Round Robin.
    Montar();
    PCB *PCBIteracion = NULL, *QPCBIteracion = NULL;
    AuxPCB = PPCB;

    while (AuxPCB != NULL) {
        if (AuxPCB->Estado == 2) { // Verificar que el proceso está en estado listo.
            if (PCBIteracion == NULL) {
                PCBIteracion = (PCB*)malloc(sizeof(PCB));
                *PCBIteracion = *AuxPCB;
                PCBIteracion->sig = NULL;
                QPCBIteracion = PCBIteracion;
            } else {
                QPCBIteracion->sig = (PCB*)malloc(sizeof(PCB));
                *QPCBIteracion->sig = *AuxPCB;
                QPCBIteracion = QPCBIteracion->sig;
                QPCBIteracion->sig = NULL;
            }
            AuxPCB->Estado = 3; // Cambiar el estado a en ejecución.
            int quantumActual = quantum;

            while (quantumActual > 0 && AuxPCB->CiclosCPU > 0) {
                AuxPCB->CiclosCPU--;
                quantumActual--;
            }

            if (AuxPCB->CiclosCPU > 0) {
                AuxPCB->Estado = 2; // Volver a poner el proceso en estado listo si aún tiene ciclos de CPU.
                if (AuxPCB->sig != NULL) {
                    QPCB->sig = AuxPCB;
                    QPCB = AuxPCB;
                    AuxPCB = AuxPCB->sig;
                    QPCB->sig = NULL;
                } else {
                    break; // Si es el último proceso, salir del bucle.
                }
            } else {
                AuxPCB->Estado = 4; // Cambiar el estado a terminado si no tiene más ciclos de CPU.
                AuxPCB = AuxPCB->sig;
            }
        } else {
            AuxPCB = AuxPCB->sig; // Pasar al siguiente proceso.
        }
    }
    Imprimir(3, PCBIteracion);
}

void Imprimir(int tabla, PCB *pcb) {
    switch (tabla) {
        case 1:
            printf("-----TABLA DE TAREAS-----\n\n");
            AuxJT = (JT*)malloc(sizeof(JT));
            AuxJT = PJT;
            printf("|%-12s | %-12s | %-12s|\n", "No.Tarea", "No.Lineas", "Loc.PMT");
            printf("--------------------------------------------\n");
            while (AuxJT != NULL) {
                printf("|%-12d | %-12d | %-12d| \n", AuxJT->nTarea, AuxJT->nLineas, AuxJT->LocPMT);
                AuxJT = AuxJT->sig;
            }
            break;
        case 2:
            printf("\n-----(PMT)TABLA DE MAPA DE PAGINAS-----");
            for (int i = 0; i < nTareas; i++) {
                printf("\n\n---Mapa de pagina de J%d---%s\n", i + 1, i > 8 ? "" : "-");
                printf("|   Pagina   | Seleccion  |\n");
                AuxPMT = PPMT[i];
                while (AuxPMT != NULL) {
                    printf("|%6d%6s|%6d%6s|\n", AuxPMT->nPagina, "", AuxPMT->ejecutar, "");
                    AuxPMT = AuxPMT->sig;
                }
                printf("---------------------------");
            }
            printf("\n\n Numero de procesos: %d", contProcesos);
            break;
        case 3:
            system("cls");
            printf("\n-----(PCB) BLOQUE DE CONTROL DE PROCESOS-----");
            printf("\nEstado inicial del PCB:\n");
            ImprimirListaPCB(PPCB);
            printf("\nEstado del PCB tras la iteración de Round Robin:\n");
            ImprimirListaPCB(pcb);
            break;
    }
}

void ImprimirListaPCB(PCB *pcb) {
    char Tipo[20];
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n|%s%3s|%s%3s|%s%6s|%s%5s|%s%5s|%s%5s|%s%7s|%s%7s|%s%6s|%s%3s|%s%3s|%s%2s|\n", "Proceso", "", "T-Llegada", "",
           "Ciclos", "", "Estados", "", "Memoria", "", "CPU o E/s", "", "nDisp", "", "nArch", "", "TipoSol", "", "Ciclos SC", "", "Inicio SC", "", "DuracionSC", "");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------");
    while (pcb != NULL) {
        if (pcb->TipoProceso == 1) {
            snprintf(Tipo, sizeof(Tipo), "CPU");
        } else if (pcb->TipoProceso == 2) {
            snprintf(Tipo, sizeof(Tipo), "E");
        } else if (pcb->TipoProceso == 3) {
            snprintf(Tipo, sizeof(Tipo), "S");
        }
        printf("\n|%3sJ%dP%d%s|%6d%6s|%6d%6s|%6d%6s|%6d%4sKB|%6s%8s|%6d%6s|%6d%6s|%6s%6s|%6d%6s|%6d%6s|%6d%6s|", "", pcb->nTarea,
               pcb->nPagina, (pcb->nTarea >= 10) ? "  " : "   ", pcb->TiempoLlegada, "", pcb->CiclosCPU, "",
               pcb->Estado, "", pcb->Memoria, "", Tipo, "", pcb->nDispositivos, "", pcb->nArchivos, "",
               (pcb->TipoSolicitud == 0) ? "Usuario" : "Sistema", "", pcb->CicSC, "", pcb->IniSC, "", pcb->DuracionSC, "");
        pcb = pcb->sig;
    }
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    system("pause");
}
