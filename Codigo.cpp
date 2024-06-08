#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include <iomanip>

#define nTareas 10
#define LineasPorPagina 100
#define Arr 8
#define Tquantum 5

using namespace std;

void Crear_JT();
void Crear_PMT();
void Imprimir(int tabla);
void CrearPCB();
void RoundRobin();

string espaciar(int tamanio, int valor){
    int espacio = 0;
    string texto = "";
    
    espacio = valor - tamanio;
    
    for(int i = 0; i < espacio; i++){
        texto = texto + " ";
    }
    return texto;
}

struct JT {
    int nTarea, nLineas, LocPMT, totalP, Sec[Arr];
    struct JT* sig;
};

struct PMT {
    int nPagina, nTarea, ejecutar, ContS;
    struct PMT* sig;
};

struct PCB {
    int nTarea, nPagina, TiempoLlegada, CiclosCPU, Estado, Memoria, TipoProceso, TipoSolicitud, CicSC, IniSC, DuracionSC, masc;
    struct PCB* sig;
};

JT *PJT, *QJT, *NuevoJT, *AuxJT;
PMT *PPMT, *QPMT, *NuevoPMT, *AuxPMT;
PCB *PPCB, *QPCB, *NuevoPCB, *AuxPCB, *PPCB2;

int main(){
    PJT = NULL;
    QJT = NULL;

    Crear_JT();
    Crear_PMT();
    Imprimir(2);
    CrearPCB();
    RoundRobin();
    getch();
    return 0;
}

void Crear_JT() {
    int coeficiente, residuo;
    int puntero = 10;
    srand(time(NULL));
    for(int i = 1; i <= nTareas; i++) {
        if(PJT == NULL) {
            PJT = (JT*)malloc(sizeof(JT));
            PJT->nTarea = i;
            PJT->nLineas = 100 + rand()%500;
            PJT->LocPMT = puntero;
            puntero++;
            coeficiente = PJT->nLineas / LineasPorPagina;
            residuo = PJT->nLineas % LineasPorPagina;
            PJT->totalP = residuo > 0 ? coeficiente + 1 : coeficiente;
            PJT->Sec[0] = 0;
            for(int k = 1; k < Arr; k++) {
                PJT->Sec[k] = 0 + rand()%PJT->totalP;
            }
            PJT->sig = NULL;
            QJT = PJT;
        } else {
            NuevoJT = (JT*)malloc(sizeof(JT));
            NuevoJT->nTarea = i;
            NuevoJT->nLineas = 100 + rand()%500;
            NuevoJT->LocPMT = puntero;
            puntero++;
            coeficiente = NuevoJT->nLineas / LineasPorPagina;
            residuo = NuevoJT->nLineas % LineasPorPagina;
            NuevoJT->totalP = residuo > 0 ? coeficiente + 1 : coeficiente;
            NuevoJT->Sec[0] = 0;
            for(int k = 1; k < Arr; k++) {
                NuevoJT->Sec[k] = 0 + rand()%NuevoJT->totalP;
            }
            NuevoJT->sig = NULL;
            QJT->sig = NuevoJT;
            QJT = NuevoJT;
        }
    }
}

void Crear_PMT() {
    AuxJT = PJT;
    int contador = 0;
    srand(time(NULL));
    for(int i = 1; i <= nTareas; i++) {
        for(int j = 0; j < AuxJT->totalP; j++) {
            if(PPMT == NULL) {
                PPMT = (PMT*)malloc(sizeof(PMT));
                PPMT->nTarea = AuxJT->nTarea;
                PPMT->nPagina = j;
                PPMT->ejecutar = 0 + rand()%2;
                if(PPMT->ejecutar == 1) {
                    contador++;
                }
                PPMT->sig = NULL;
                QPMT = PPMT;
            } else {
                NuevoPMT = (PMT*)malloc(sizeof(PMT));
                NuevoPMT->nTarea = AuxJT->nTarea;
                NuevoPMT->nPagina = j;
                NuevoPMT->ejecutar = 0 + rand()%2;
                if(NuevoPMT->ejecutar == 1) {
                    contador++;
                }
                if(j == (AuxJT->totalP) - 1) {
                    NuevoPMT->ContS = contador;
                }
                NuevoPMT->sig = NULL;
                QPMT->sig = NuevoPMT;
                QPMT = NuevoPMT;
            }
        }
        contador = 0;
        AuxJT = AuxJT->sig;
    }
    cout << "\nTABLAS DE MAPA DE PAGINAS\n";
}

void Imprimir(int tabla) {
    switch(tabla) {
        case 1:
            cout << "-----TABLA DE TAREAS-----\n\n";
            AuxJT = (JT*)malloc(sizeof(JT));
            AuxJT = PJT;
            cout << "|No.Tarea    | No.Lineas  | Loc.PMT    |\n";
            cout << "----------------------------------------\n";
            while(AuxJT != NULL) {
                cout << "|" << setw(10) << AuxJT->nTarea << " | " << setw(10) << AuxJT->nLineas << " | " << setw(10) << AuxJT->LocPMT << " |\n";
                AuxJT = AuxJT->sig;
            }
            break;
        case 2:
            cout << "\n-----(PMT)TABLA DE MAPA DE PAGINAS-----\n";
            AuxJT = PJT;
            AuxPMT = PPMT;
            for(int i = 1; i <= nTareas; i++) {
                cout << "\n\n---Mapa de pagina de J" << AuxJT->nTarea << "---\n";
                cout << "|   Pagina   | Seleccion  |\n";
                while(AuxPMT != NULL) {
                    if(AuxPMT->nTarea == AuxJT->nTarea) {
                        cout << "|" << setw(10) << AuxPMT->nPagina << " | " << setw(10) << AuxPMT->ejecutar << " |\n";
                        AuxPMT = AuxPMT->sig;
                    } else {
                        break;
                    }
                }
                AuxJT = AuxJT->sig;
            }
            cout << "---------------------------\n";
            break;
    }
}

void CrearPCB() {
    int aux;
    srand(time(NULL));
    int T = 0;
    AuxPMT = PPMT;
    do {
        if(AuxPMT->ejecutar == 1) {
            if(PPCB == NULL) {
                PPCB = (PCB*)malloc(sizeof(PCB));
                PPCB->nTarea = AuxPMT->nTarea;
                PPCB->nPagina = AuxPMT->nPagina;
                PPCB->TiempoLlegada = T;
                PPCB->CiclosCPU = 2 + rand()%18;
                PPCB->Estado = 1;
                PPCB->Memoria = 10 + rand()%111;
                PPCB->TipoProceso = 0 + rand()%3;
                PPCB->TipoSolicitud = 0 + rand()%2;
                PPCB->CicSC = 0;
                aux = PPCB->CiclosCPU + 1;
                PPCB->IniSC = 0 + rand()%aux;
                if(PPCB->IniSC == 0) {
                    PPCB->DuracionSC = 0;
                } else if(PPCB->IniSC == aux-1) {
                    PPCB->DuracionSC = 1;
                } else if(PPCB->IniSC == aux-2) {
                    PPCB->DuracionSC = 1 + rand()%2;
                } else {
                    PPCB->DuracionSC = 1 + rand()%3;
                }
                PPCB->masc = 0;
                PPCB->sig = NULL;
                QPCB = PPCB;
            } else {
                NuevoPCB = (PCB*)malloc(sizeof(PCB));
                NuevoPCB->nTarea = AuxPMT->nTarea;
                NuevoPCB->nPagina = AuxPMT->nPagina;
                NuevoPCB->TiempoLlegada = T;
                NuevoPCB->CiclosCPU = 2 + rand()%18;
                NuevoPCB->Estado = 1;
                NuevoPCB->Memoria = 10 + rand()%111;
                NuevoPCB->TipoProceso = 0 + rand()%3;
                NuevoPCB->TipoSolicitud = 0 + rand()%2;
                NuevoPCB->CicSC = 0;
                aux = NuevoPCB->CiclosCPU + 1;
                NuevoPCB->IniSC = 0 + rand()%aux;
                if(NuevoPCB->IniSC == 0) {
                    NuevoPCB->DuracionSC = 0;
                } else if(NuevoPCB->IniSC == aux-1) {
                    NuevoPCB->DuracionSC = 1;
                } else if(NuevoPCB->IniSC == aux-2) {
                    NuevoPCB->DuracionSC = 1 + rand()%2;
                } else {
                    NuevoPCB->DuracionSC = 1 + rand()%3;
                }
                NuevoPCB->masc = 0;
                QPCB->sig = NuevoPCB;
                QPCB = NuevoPCB;
            }
            T++;
        }
        AuxPMT = AuxPMT->sig;
    } while(AuxPMT != NULL);
    Imprimir(3);
}  

void Ver_Bloc_de_Cont() {
    system("cls");
    cout << "\nBloque de control de procesos (PCB)\n";
    cout << "\nProceso | T.Llegada | Ciclos | Edo | Memoria | CPU/E/S | Tipo     | CicSC | IniSC | DuracionSC\n";
    AuxPCB = PPCB;
    do {
        if(AuxPCB->masc == 0) {
            cout << "J" << AuxPCB->nTarea << "P" << AuxPCB->nPagina << "    | ";
            cout << setw(9) << left << AuxPCB->TiempoLlegada << "| ";
            cout << setw(6) << left << AuxPCB->CiclosCPU << "| ";
            cout << setw(4) << left << AuxPCB->Estado << "| ";
            cout << setw(8) << left << AuxPCB->Memoria << "| ";
            if(AuxPCB->TipoProceso == 0) {
                cout << setw(7) << left << "CPU | ";
            } else if(AuxPCB->TipoProceso == 1) {
                cout << setw(7) << left << "S   | ";
            } else if(AuxPCB->TipoProceso == 2) {
                cout << setw(7) << left << "E   | ";
            }
            if(AuxPCB->TipoSolicitud == 0) {
                cout << setw(8) << left << "Usuario | ";
            } else if(AuxPCB->TipoSolicitud == 1) {
                cout << setw(8) << left << "Sistema | ";
            }
            cout << setw(5) << left << AuxPCB->CicSC << "| ";
            cout << setw(5) << left << AuxPCB->IniSC << "| ";
            cout << AuxPCB->DuracionSC << "\n";
        }
        AuxPCB = AuxPCB->sig;
    } while(AuxPCB != NULL);
    
    cout << "\n";
    Ver_Bloc_de_Cont_Sem();
}

void Ver_Bloc_de_Cont_Sem() {
    cout << "\nPCB semaforo\n";
    cout << "\nProceso|T.Llegada|Ciclos|Edo|Memoria|CPU/E/S|Tipo     |CicSC|IniSC|DuracionSC\n";
    AuxPCB = PPCB;
    do {
        if(AuxPCB->masc == 1) {
            cout << "J" << AuxPCB->nTarea << "P" << AuxPCB->nPagina << "    | ";
            cout << setw(9) << left << AuxPCB->TiempoLlegada << "| ";
            cout << setw(6) << left << AuxPCB->CiclosCPU << "| ";
            cout << setw(4) << left << AuxPCB->Estado << "| ";
            cout << setw(8) << left << AuxPCB->Memoria << "| ";
            if(AuxPCB->TipoProceso == 0) {
                cout << setw(7) << left << "CPU | ";
            } else if(AuxPCB->TipoProceso == 1) {
                cout << setw(7) << left << "S   | ";
            } else if(AuxPCB->TipoProceso == 2) {
                cout << setw(7) << left << "E   | ";
            }
            if(AuxPCB->TipoSolicitud == 0) {
                cout << setw(8) << left << "Usuario | ";
            } else if(AuxPCB->TipoSolicitud == 1) {
                cout << setw(8) << left << "Sistema | ";
            }
            cout << setw(5) << left << AuxPCB->CicSC << "| ";
            cout << setw(5) << left << AuxPCB->IniSC << "| ";
            cout << AuxPCB->DuracionSC << "\n";
        }
        AuxPCB = AuxPCB->sig;
    } while(AuxPCB != NULL);
    
    cout << "\n";
    system("pause");
}

void RoundRobin() {
    int contadorsem = 0;
    int a;
    cout << "\n\n";
    AuxPCB = PPCB;
    do {
        AuxPCB->Estado = 2;
        AuxPCB = AuxPCB->sig;
    } while(AuxPCB != NULL);
    Ver_Bloc_de_Cont();
    AuxPCB = PPCB;
    while(true) {
        if(AuxPCB->Estado != 5) {
            AuxPCB->Estado = 3;
        }
        a = Tquantum;
        while(AuxPCB->CiclosCPU > 0 && a > 0 && AuxPCB->masc == 0) {
            AuxPCB->CicSC = AuxPCB->CicSC + 1;
            if(AuxPCB->CicSC == AuxPCB->IniSC) {
                AuxPCB->Estado = 4;
                AuxPCB->masc = 1;
                PPCB2 = AuxPCB;
                Ver_Bloc_de_Cont();
                AuxPCB = PPCB2;
            } else {
                AuxPCB->CiclosCPU = (AuxPCB->CiclosCPU) - 1;
                PPCB2 = AuxPCB;
                Ver_Bloc_de_Cont();
                AuxPCB = PPCB2;
            }            
            a--;
        }
        if(AuxPCB->CiclosCPU > 0 && AuxPCB->masc == 0) {
            AuxPCB->Estado = 4;
            PPCB2 = AuxPCB;
            Ver_Bloc_de_Cont();
            AuxPCB = PPCB2;
        }
        if(AuxPCB->CiclosCPU == 0) {
            if(AuxPCB->Estado != 5) {
                AuxPCB->Estado = 5;
                contadorsem++;
                PPCB2 = AuxPCB;
                Ver_Bloc_de_Cont();
                AuxPCB = PPCB2;
            }
            if(contadorsem == nTareas) {
                cout << "\n";
                break;
            }
        }
        AuxPCB = AuxPCB->sig;
        if(AuxPCB == NULL) {
            AuxPCB = PPCB;
        }
    }
}
