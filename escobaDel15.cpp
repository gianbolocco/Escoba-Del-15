#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
typedef char str10[11];

struct Carta{
    int num;
    str10 palo; 
    char ubi;// T: Table, H: Hand p1, h: Hand p2, A: acumuladoP1,X: Hand p3,x: acumuladoP3 a: acumuladoP2, D: Deck,
};

struct Jugador{
    
    short puntos=0;
    int id;
    char mano;
    char acum;
    short cantCartas=0;
    bool  sieteOro;
    short cantOro=0;
    short cantSiete=0;
    short escobas=0;
};

struct Nodo{
    int id;
    Nodo * sgte;    
};

void repartir(Carta[],int,char); //Reparte las cartas
void mostrarCartas(Carta[],char); //Muestra las cartas
int cartaAleatoria(); //Genera un numero aleatorio del 0 al 39
short cantCartasT(Carta[]); //Cuenta las cartas que hay en la mesa
void ronda(Jugador&,Carta[],short&); //Cada turno
void jugada(Jugador&, Carta[],short,short&); //Cada jugada
void calcularPuntaje(Jugador&,Jugador&,Jugador&); //Calcula el puntaje de cada jugador
void mostrarPuntaje(Carta[],Jugador);//Muestra el puntaje de cada jugador
void limpiarMesa(Carta [],Jugador&);

void push(Nodo*&,int);//Pila para jugada de 15
int pop(Nodo*&);

int main(){

    srand(time(nullptr)); // Inicializar la semilla del generador de números pseudoaleatorios

    Carta mazo[40] = {{10,"Oro",'D'},{10,"Espada",'D'},{10,"Copa",'D'},{10,"Basto",'D'},
                      {9,"Oro",'D'},{9,"Espada",'D'},{9,"Copa",'D'},{9,"Basto",'D'},
                      {8,"Oro",'D'},{8,"Espada",'D'},{8,"Copa",'D'},{8,"Basto",'D'},
                      {7,"Oro",'D'},{7,"Espada",'D'},{7,"Copa",'D'},{7,"Basto",'D'},
                      {6,"Oro",'D'},{6,"Espada",'D'},{6,"Copa",'D'},{6,"Basto",'D'},
                      {5,"Oro",'D'},{5,"Espada",'D'},{5,"Copa",'D'},{5,"Basto",'D'},
                      {4,"Oro",'D'},{4,"Espada",'D'},{4,"Copa",'D'},{4,"Basto",'D'},
                      {3,"Oro",'D'},{3,"Espada",'D'},{3,"Copa",'D'},{3,"Basto",'D'},
                      {2,"Oro",'D'},{2,"Espada",'D'},{2,"Copa",'D'},{2,"Basto",'D'},
                      {1,"Oro",'D'},{1,"Espada",'D'},{1,"Copa",'D'},{1,"Basto",'D'}
                    };

    Jugador jug1={0,1,'H','A',0,false,0,0,0};
    Jugador jug2={0,2,'h','a',0,false,0,0,0};
    Jugador jug3={0,3,'X','x',0,false,0,0,0};


    int cantJug;
    cout<<"[-] Ingrese la cantidad de jugadores (2 o 3): ";cin>>cantJug;
    while(cantJug != 2 && cantJug != 3){
        cout<<"[-] Error, ingrese un numero valido."<<endl;
        cout<<"[-] Ingrese la cantidad de jugadores (2 o 3): ";cin>>cantJug;
    }

    if(cantJug == 2){ // PARTIDA 2 Jugadores

        while(jug1.puntos < 15 && jug2.puntos < 15){
            
            short jugador15=0;//Indica Id del ultimo jugador que sumo 15
            repartir(mazo,4,'T'); // Se le reparte a la mesa.
            int cantCartasRepartidas = 4;

            while (cantCartasRepartidas < 40){

                repartir(mazo,3,jug1.mano); // Se le reparte al j1
                repartir(mazo,3,jug2.mano); // Se le reparte al j2

                for(int i=1; i<=3;i++){

                    cout<<"==============["<<i<<"]=============="<<endl;
                    ronda(jug1,mazo,jugador15);
                    cout<<"==============["<<i<<"]=============="<<endl;
                    ronda(jug2,mazo,jugador15);                    
                }

                cantCartasRepartidas += 6;

            }
            cout<<"[-] Fin de la ronda"<<endl;
            if(jugador15 == 1){
                limpiarMesa(mazo,jug1);
            }
            else{
                limpiarMesa(mazo,jug2);
            }

            // Calculamos puntaje
            calcularPuntaje(jug1,jug2,jug3);
            
            // Mostramos cartas acumuladas y puntuacion
            mostrarPuntaje(mazo,jug1);
            mostrarPuntaje(mazo,jug2);

            // Devolvemos las cartas al mazo
            for(int i=0;i<40;i++){
                mazo[i].ubi = 'D';
            }

            // Reseteamos los puntos para comenzar una nueva ronda
            jug1={jug1.puntos,1,'H','A',0,false,0,0,0};
            jug2={jug2.puntos,2,'h','a',0,false,0,0,0};
        }
        if(jug1.puntos <jug2.puntos){
            cout<<"GANO JUGADOR 2!!"<<endl;
        }else{
            cout<<"GANO JUGADOR 1!!"<<endl;
        } 
    }

    else{ // PARTIDA 3 JUGADORES

        while((jug1.puntos < 15) && (jug2.puntos < 15) && (jug3.puntos < 15)){

            short jugador15=0;//Indica Id del ultimo jugador que sumo 15            
            repartir(mazo,4,'T'); // Se le reparte a la mesa.
            int cantCartasRepartidas = 4;

            while (cantCartasRepartidas < 40){

                repartir(mazo,3,jug1.mano); // Se le reparte al j1
                repartir(mazo,3,jug2.mano); // Se le reparte al j2
                repartir(mazo,3,jug3.mano); // Se le reparte al j3
                
                for(int i=1;i<=3;i++){

                    cout<<"==============["<<i<<"]=============="<<endl;
                    ronda(jug1,mazo,jugador15);
                    cout<<"==============["<<i<<"]=============="<<endl;
                    ronda(jug2,mazo,jugador15);
                    cout<<"==============["<<i<<"]=============="<<endl;
                    ronda(jug3,mazo,jugador15);
                }
                
                cantCartasRepartidas += 9;

            }

            cout<<"[-] Fin de la ronda"<<endl;
            if(jugador15 == 1){
                limpiarMesa(mazo,jug1);
            }
            else if(jugador15 == 2){
                limpiarMesa(mazo,jug2);
            }
            else{
                limpiarMesa(mazo,jug3);
            }

            // Calculamos puntaje
            calcularPuntaje(jug1,jug2,jug3);

            // Mostramos cartas acumuladas y puntuacion
            mostrarPuntaje(mazo,jug1);
            mostrarPuntaje(mazo,jug2);
            mostrarPuntaje(mazo,jug3);

            // Devolvemos las cartas al mazo
            for(int i=0;i<40;i++){
                mazo[i].ubi = 'D';
            }

            // Reseteamos los puntos para comenzar una nueva ronda
            jug1={jug1.puntos,1,'H','A',0,false,0,0,0};
            jug2={jug2.puntos,2,'h','a',0,false,0,0,0};
            jug3={jug3.puntos,3,'X','x',0,false,0,0,0};
        }
        if(jug1.puntos >jug2.puntos && jug1.puntos >jug2.puntos){
            cout<<"GANO JUGADOR 1!!"<<endl;
        }else if(jug2.puntos>jug1.puntos &&jug2.puntos >jug3.puntos){
            cout<<"GANO JUGADOR 2!!"<<endl;
        }else{
            cout<<"GANO JUGADOR 3!!"<<endl;
        }
    }   

    getch(); 
    return 0;
};

void ronda(Jugador& jug, Carta m[],short &jug15){
    
    
    int card = 0;
    cout<<"============ MESA ============"<<endl;
    mostrarCartas(m,'T');
    if(cantCartasT(m) == 0){
        cout<<"[-] Mesa vacia, descarte una carta!"<<endl;
    }
    cout<<"========= Jugador "<<jug.id<<" =========="<<endl;
    mostrarCartas(m,jug.mano);

    cout<<"[-] Seleccione una carta de su mano (por id): ";cin>>card; //Selecciona la carta de la mano que desea jugar.
    while(((card > 39) || m[card].ubi != jug.mano)){
        cout<<"[-] Ingresar una carta valida que este en su mano: ";cin>>card;
    }
    
    cout<<"[-] Carta jugada: "<<m[card].num<<" de "<<m[card].palo<<endl;
    jugada(jug,m,card,jug15);
}

void jugada(Jugador &jug, Carta m[],short card, short &jug15){ //id de carta elegida
    
    Nodo * pila = NULL; //pila para los acumuladores de 15
    short cantT = cantCartasT(m);
    
    int idsTable[cantT];    //Vector con los ids de las cartas de la mesa;
    int j=0;

    for(int i=0;i<40;i++){ //Se guardan los ids de las cartas de la mesa
        if(m[i].ubi == 'T'){
            idsTable[j] = i;
            j++;
        }
    }

    int quince = m[card].num; //acumulador
    int k=0;

    if(cantT != 0){ // Revisa que hayan cartas en la mesa

        while(quince != 15){ // Combinatoria de cartas hasta encontrar una combinacion que sume 15.

            for(int i = k ; i<cantT ; i++){

                if((quince + m[idsTable[i]].num) <= 15){
                    quince += m[idsTable[i]].num;
                    m[idsTable[i]].ubi = jug.acum;
                    push(pila,idsTable[i]); // Una pila con los ids de las cartas que suman 15
                }

                if(quince==15){
                    cout<<"[-] Usted sumo 15!"<<endl;
                    break;
                }
            }
            
            k++;

            if(quince != 15){
                quince = m[card].num; // Acumulador 
                while(pila != NULL){ // Vaciamos la pila
                    m[pop(pila)].ubi = 'T';
                }
            }
            if(k==cantT)break; // Itera tantas veces como cartas hay en la mesa
        }
    }

    
    if(quince != 15){
        cout<<"[-] No hay manera de sumar 15, su carta se descarto."<<endl;
        m[card].ubi = 'T';
    }
    else{

        jug15 = jug.id;

        short nCantT = cantCartasT(m);
        if(nCantT == 0){
            cout<<"[-] Jugador "<<jug.id<<" hizo escoba!"<<endl;
            jug.escobas++;
        } 

        m[card].ubi = jug.acum; //Carta de la mano a acumuladas
        push(pila,card);

        while(pila != NULL){ //vaciamos la pila

            int idC = pop(pila);

            Carta C = m[idC];

            cout<<"[-] El "<<C.num<<" de "<<C.palo<<" se agrego a las cartas acumuladas del jugador "<<jug.id<<endl;
            
            jug.cantCartas++; // Acumula cantidad de cartas del jugador

            if(strcmp(C.palo,"Oro") == 0){ // Acumula oros
                jug.cantOro++;
            }
            if(C.num == 7){ // Acumula 7
                jug.cantSiete++;
            }
            if(idC == 12){ // Siete de oro
                jug.sieteOro = true;
            }
        }
    }
};

void repartir(Carta mazo[],int n, char u){

    for (int i = 0; i < n; ++i) {
        int indice = cartaAleatoria();
        while (!(mazo[indice].ubi == 'D')) {
            indice = cartaAleatoria();
        }
        mazo[indice].ubi = u;
    }
}

// Función para generar un número aleatorio en el rango de 0 a 39
int cartaAleatoria() {
    return rand() % 40;
}

void mostrarCartas(Carta m[],char u){ //Muestra las cartas y cuenta cuantas cartas hay en la mesa
   
    cout<<"-Id- ==== CARTA ==== "<<endl;
    for(int i=0;i<40;i++){
        
        if(m[i].ubi == u){
            cout<<"["<<setw(2)<<i<<"] ----"<<setw(2)<<m[i].num<<" de "<<m[i].palo<<endl;  
        }
    }
};

short cantCartasT(Carta m[]){

    short n = 0;

    for(int i=0;i<40;i++){
        if(m[i].ubi == 'T'){
            n++;
        }
    }
    return n;
}

void calcularPuntaje(Jugador &jug1,Jugador &jug2, Jugador &jug3){

    // Suma las escobas

    jug1.puntos += jug1.escobas;
    jug2.puntos += jug2.escobas;
    jug3.puntos += jug3.escobas;

    // Consulta por el siete de oro

    if(jug1.sieteOro){
        jug1.puntos++;
    }

    if(jug2.sieteOro){
        jug2.puntos++;
    }

    if(jug3.sieteOro){
        jug3.puntos++;
    }

    // Compara cantidad de oros

    if(jug1.cantOro > jug2.cantOro && jug1.cantOro > jug3.cantOro){
        jug1.puntos++;
    }

    if(jug2.cantOro > jug1.cantOro && jug2.cantOro > jug3.cantOro){
        jug2.puntos++;
    }

    if(jug3.cantOro > jug1.cantOro && jug3.cantOro > jug2.cantOro){
        jug3.puntos++;
    }

    // Compara cantidad de cartas

    if(jug1.cantCartas > jug2.cantCartas && jug1.cantCartas > jug3.cantCartas){
        jug1.puntos++;
    }

    if(jug2.cantCartas > jug1.cantCartas && jug2.cantCartas > jug3.cantCartas){
        jug2.puntos++;
    }

    if(jug3.cantCartas > jug1.cantCartas && jug3.cantCartas > jug2.cantCartas){
        jug3.puntos++;
    }

    // Compara cantidad de 7

    if(jug1.cantSiete > jug2.cantSiete && jug1.cantSiete > jug3.cantSiete){
        jug1.puntos++;
    }

    if(jug2.cantSiete > jug1.cantSiete && jug2.cantSiete > jug3.cantSiete){
        jug2.puntos++;
    }

    if(jug3.cantSiete > jug1.cantSiete && jug3.cantSiete > jug2.cantSiete){
        jug3.puntos++;
    }
};

void push(Nodo*& pila,int id){   //    La pila va por referencia porque no se puede perder la posicion de la pila.

    Nodo * p = new Nodo();  //  Reservo espacio
    p->id=id;           //  Guardo la info
    p->sgte=pila;           //  Enlaze
    pila = p;               //Pila siempre apunta al ultimo que agregue
    return;
}

int pop(Nodo*& pila){

    int x;         //  Auxiliar
    Nodo* p = pila; //   Auxiliar para poder borrar
    x=p->id;      //  Recupera info
    pila = p->sgte; //  Reapunta la pila
    delete p;       //    Borra
    return x;
}

void mostrarPuntaje(Carta m[],Jugador jug){

    cout<<"====== JUGADOR "<<jug.id<<" ======"<<endl;
    cout<<"[-] Puntos: "<<jug.puntos<<endl;
    cout<<"[-] Cantidad de cartas: "<<jug.cantCartas<<endl;
    cout<<"[-] Cantidad de Oros: "<<jug.cantOro<<endl;
    cout<<"[-] Cantidad de 7: "<<jug.cantSiete<<endl;
    cout<<"[-] Escobas: "<<jug.escobas<<endl;
    if(jug.sieteOro){
        cout<<"[-] Posee el siete de oro."<<endl;
    }
    cout<<"[-] Acumulado:"<<endl;
    mostrarCartas(m,jug.acum);
};

void limpiarMesa(Carta m[],Jugador &jug){

    for(int i=0;i<40;i++){
        if(m[i].ubi == 'T'){

            Carta C = m[i];
            m[i].ubi = jug.acum;
            
            cout<<"[-] El "<<C.num<<" de "<<C.palo<<" se agrego a las cartas acumuladas del jugador "<<jug.id<<endl;
            
            jug.cantCartas++; // Acumula cantidad de cartas del jugador

            if(strcmp(C.palo,"Oro") == 0){ // Acumula oros
                jug.cantOro++;
            }
            if(C.num == 7){ // Acumula 7
                jug.cantSiete++;
            }
            if(i == 12){ // Siete de oro
                jug.sieteOro = true;
            }
        }
    }
};