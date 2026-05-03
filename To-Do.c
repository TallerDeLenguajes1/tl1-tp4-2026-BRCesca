#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Tarea{
    int tareaId;
    char *descripcion;
    int duracion;
}Tarea;

typedef struct Nodo{
    Tarea t;
    struct Nodo *siguiente;
}Nodo;

typedef struct Lista{
    int cant;
    Nodo *siguiente;
}Lista;


Lista *CrearListaVacia(){
    Lista *nuevaLista=(Lista *)malloc(sizeof(Lista));
    nuevaLista->cant=0;
    nuevaLista->siguiente=NULL;
    return nuevaLista;
}


Tarea *CrearTarea(char *info,int *ident, int duracion){
    Tarea *nuevaTarea= (Tarea *)malloc(sizeof(Tarea));
    nuevaTarea->tareaId=(*ident);
    (*ident)= *ident + 1;
    nuevaTarea->descripcion=(char *)malloc((strlen(info)+1)*(sizeof(char)));
    strcpy(nuevaTarea->descripcion, info);
    nuevaTarea->duracion=duracion;
    return nuevaTarea;
}


Nodo *CrearNodo(Tarea *nuevaTarea){
    Nodo *nuevoNodo=(Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->t=(*nuevaTarea);
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}

void InsertarNodo(Lista **lista,Nodo *elNodo){
    elNodo->siguiente=(*lista)->siguiente;
    (*lista)->siguiente=elNodo;
    (*lista)->cant += 1;
}

Nodo *TareaParaTransferir(int identificacion, Lista **lista){// me devuelve la direccion de memoria que necesito transferir de una lista a otra
    Nodo *aux;
    aux=(*lista)->siguiente;
    while(aux && aux->t.tareaId!=identificacion){
        aux=aux->siguiente;
    }
    return aux;
}

void EliminarNodo(Lista **lista, int id){
    Nodo *nodoAux=(*lista)->siguiente;
    Nodo *nodoAnt=NULL;
    while(nodoAux!=NULL && nodoAux->t.tareaId!=id){
        nodoAnt=nodoAux;
        nodoAux=nodoAux->siguiente;
    }
    if(nodoAux==(*lista)->siguiente){
        (*lista)->siguiente=nodoAux->siguiente;
    }
    else
    {
        nodoAnt->siguiente=nodoAux->siguiente;
    }
    nodoAux->siguiente = NULL;
}

void TrasladarNodo(Lista **origen,Lista **destino,int id){
    Nodo *aux=(*origen)->siguiente;
    Nodo *ant=NULL;
    while(aux!=NULL && aux->t.tareaId!=id){
        ant=aux;
        aux=aux->siguiente;
    }
    if(aux!=NULL){
        if(aux==(*origen)->siguiente){
            (*origen)->siguiente = aux->siguiente;
        }else{
            ant->siguiente = aux->siguiente;
        }
        aux->siguiente = NULL;
        (*origen)->cant--;
        InsertarNodo(destino, aux);
        printf("\nTarea trasladada con exito");
    }else{
        printf("\nTarea no encontrada");
    }

}

void MostrarLista(Lista **lista){
    int i=1;
    Nodo *aux=(*lista)->siguiente;
    printf("\n\n======TAREAS======");
    while(aux!=NULL){
        printf("\n%d)TAREA ID: %d ", i, aux->t.tareaId);
        printf("\nDESCRIPCION DE LA TAREA: %s",aux->t.descripcion);
        printf("\nDURACION: %d", aux->t.duracion);
        printf("\n====================");
        i++;
        aux=aux->siguiente;
    }
}

void ListaPorPalabra(Lista **lista, char *palabra){
    Nodo *aux=(*lista)->siguiente;
    int coincidencias=0;
    printf("\n=====RESULTADO DE LA BUSQUEDA======");
    while(aux!=NULL){
        if(strstr(aux->t.descripcion,palabra)){
            printf("\n====================");
            printf("\nTAREA ID: %d ", aux->t.tareaId);
            printf("\nDESCRIPCION DE LA TAREA: %s",aux->t.descripcion);
            printf("\nDURACION: %d", aux->t.duracion);
            printf("\n====================");
            coincidencias++;
        }
        aux=aux->siguiente;
    }
    printf("\nSE ENCONTRARON %d COINCIDENCIAS", coincidencias);
}

void LiberarLista(Lista **lista) {
    if (lista == NULL || *lista == NULL) return;

    Nodo *actual = (*lista)->siguiente;
    Nodo *proximo;

    while (actual != NULL) {
        proximo = actual->siguiente;

        if (actual->t.descripcion != NULL) {
            free(actual->t.descripcion);
        }
        free(actual);

        actual = proximo;
    }
    free(*lista);
    *lista = NULL;   
    printf("\nMemoria de la lista liberada con exito.");
}

void ListaPorId(Lista **lista, int identificacion){
    Nodo *aux=(*lista)->siguiente;
    int coincidencias=0;
    printf("\n=====RESULTADO DE LA BUSQUEDA======");
    while(aux!=NULL){
        if(aux->t.tareaId==identificacion){
            printf("\n====================");
            printf("\nTAREA ID: %d ", aux->t.tareaId);
            printf("\nDESCRIPCION DE LA TAREA: %s",aux->t.descripcion);
            printf("\nDURACION: %d", aux->t.duracion);
            printf("\n====================");
            coincidencias++;
        }
        aux=aux->siguiente;
    }
    printf("\nSE ENCONTRARON %d COINCIDENCIAS", coincidencias);
}


int main(){
int tarea_id=1000;
int op=0, duracion,b=0,ident=0;
char *buff=(char *)malloc(100*sizeof(char));
Lista *TareasPendientes=CrearListaVacia();
Lista *TareasRealizadas=CrearListaVacia();
srand(time(NULL));
printf("\n=============MENU==============");
printf("\n1)Agregar Tarea pendiente");
printf("\n2)Pasar Tarea pendiente a Tarea realizada");
printf("\n3)Mostrar tareas");
printf("\n4)Terminar");
printf("\nElija una opcion: ");
scanf(" %d", &op);
    while(op!=4){
        if(op==1){
            printf("\n\n=====DESCRIPCION DE LA TAREA=====");
            printf("\nIngrese la descripcion de la tarea: ");
            fflush(stdin);
            gets(buff);
            duracion=rand()%(91)+10;
            printf("\nDuracion: %d hs", duracion);
            Tarea *tareaPendiente=CrearTarea(buff, &tarea_id, duracion);
            Nodo *nuevoNodo=CrearNodo(tareaPendiente);
            free(tareaPendiente);
            InsertarNodo(&TareasPendientes,nuevoNodo);
            printf("\n\n=====TAREA AGREGADA CON EXITO=====");
        }
        if(op==2){
            printf("\n\n=====PASAJE DE TAREA PENDIENTE A REALIZADA=====");
            printf("\nIngrese el ID de la tarea: ");
            fflush(stdin);
            scanf(" %d", &ident);
            TrasladarNodo(&TareasPendientes, &TareasRealizadas, ident);
        }
        if(op==3){
            printf("\n\nINDIQUE QUE DESEA VER:");
            printf("\n1)Tareas Pendientes");
            printf("\n2)Tareas Realizadas");
            printf("\n3)Buscar Tareas Por Palabra");
            printf("\n4)Buscar Tareas Por ID");
            fflush(stdin);
            printf("\n ingrese su opcion: ");
            scanf(" %d", &op);
            switch (op)
            {
            case 1:
                MostrarLista(&TareasPendientes);
                break;
            case 2:
                MostrarLista(&TareasRealizadas);
                break;
            case 3:
                printf("\n Ingrese la palabra clave: ");
                fflush(stdin);
                gets(buff);
                printf("\n==TAREAS PENDIENTES==");
                ListaPorPalabra(&TareasPendientes,buff);
                printf("\n==TAREAS REALIZADAS==");
                ListaPorPalabra(&TareasRealizadas,buff);
                break;
            case 4:
                printf("\n Ingrese la palabra clave: ");
                fflush(stdin);
                scanf(" %d", &op);
                printf("\n==TAREAS PENDIENTES==");
                ListaPorId(&TareasPendientes,op);
                printf("\n==TAREAS REALIZADAS==");
                ListaPorId(&TareasRealizadas,op);
                break;
            default:
                printf("\nEleccion no valida.");
                break;
            }
        }
        printf("\n\n=====COMO DESEA CONTINUAR====");
        printf("\n1)Agregar tarea");
        printf("\n2)Pasar Tarea pendiente a Tarea realizada");
        printf("\n3)Mostrar tareas");
        printf("\n4)Terminar");
        fflush(stdin);
        printf("\nIngrese la opcion: ");
        scanf(" %d", &op);
    }
    LiberarLista(&TareasPendientes);
    LiberarLista(&TareasRealizadas);
    free(buff);
    return 0;
}