#ifndef __SORTING_H   // "if not defined" e viene utilizzato per evitare di includere più volte lo stesso file di intestazione.
#define __SORTING_H    // Se __SORTING_H non è stato definito in precedenza, il codice fino alla fine del file verrà incluso. #define __SORTING_H definisce la macro __SORTING_H con un valore arbitrario.

#include "iostream"    //inclusione librerie
#include "list"
#include "Eigen/Eigen"
#include "map"

using namespace std;        //nomi per definire libreirei
using namespace Eigen;

namespace SortLibrary {   //definisce un nuovo nampespace per fare ordinamento


struct DecreasingInt   //classe
{
    int value;
    DecreasingInt() = default;
    DecreasingInt(const int& value): value(value){}   //costruttori uno lo prende di default crea memoria e poi gli passa il valore value

};

inline ostream &operator<<(ostream &os, const DecreasingInt &obj)
{
    os << obj.value;
    return os;                            //con interi possiamo lavorare con le operazioni normali con i dato che abbiamo noi no quindi modifichiamo gli operatori affinche capiscano cosa fare e come agire nel momento in cui bisogna fare delle operazioni
}

inline bool operator==(const DecreasingInt &obj1, const DecreasingInt &obj2)
{
    return obj1.value == obj2.value;
}

inline bool operator!=(const DecreasingInt &obj1, const DecreasingInt &obj2)
{
    return !(obj1 == obj2);            //non so che cazzo fanno
}

inline bool operator<(const DecreasingInt &obj1, const DecreasingInt &obj2)
{
    return obj1.value > obj2.value;
}

inline bool operator>(const DecreasingInt &obj1, const DecreasingInt &obj2)
{
    return obj1.value < obj2.value;
}


//ordino vettore e vedo se abbiamo un albero heap
template<typename T>     //cosa generica per calcolarsi ogni volta la stessa cosa per un vettore di tipo generico t
vector<T> HeapSort(const vector<T>& v){   //funzione heapsort gli diamo in input vettore v di tipo t
    unsigned int n = v.size();
    vector<T> vectorHeap = v;   //diamo a vector heap di tipo vettore generico t il valore v
    for (unsigned int i = 0; i < n; i++)   //scorre all'interno del vettore
    {
        int j = 1;
        int k = i;
        while (j > 0)
        {
            j = (k-1)*0.5;   //o. In particolare, il genitore di un nodo nell'albero viene calcolato come:genitore = (indice_del_nodo - 1) / 2 Questa formula deriva dal fatto che nell'albero binario, se un nodo ha indice k, allora il suo figlio sinistro ha indice 2k+1 e il figlio destro ha indice 2k+2. Quindi per trovare il genitore di un nodo, possiamo invertire la formula per l'indice del figlio sinistro:      k = (indice_del_figlio_sinistro - 1) / 2 e otteniamo la formula per il genitore.
            if (vectorHeap[k] > vectorHeap[j])
            {
                T temp = vectorHeap[k];   //valore temporaneo da dare poi  a j
                vectorHeap[k] = vectorHeap[j];     //Questo blocco if controlla se il valore del nodo "k" è maggiore del valore del suo genitore "j". Se questa condizione è vera, i due valori vengono scambiati e l'indice "k" viene aggiornato con quello del genitore "j". In caso contrario, il ciclo viene interrotto.
                vectorHeap[j] = temp;
                k = j;
            }
            else {break;}

        }
    }

    vector<T> vectorSorted = vectorHeap;   //input il vettore sortizzato dal piu grande al piu piccolo
    int id_end = n-1;  //indice ultimo elemento vettore
    for (unsigned int t = 0; t < n; t++)
    {   //ora dobbiamo verificare sia rispettata struttura heap

        T vectorInit = vectorHeap[0];   //vettore temporaneo vectorinit
        vectorHeap[0] = vectorHeap[id_end];    //Queste righe scambiano l'elemento massimo del vettore con l'ultimo elemento, quindi lo rimuovono dal vettore ordinato e lo aggiungono alla fine del vettore non ordinato. L'indice "id_end" viene aggiornato di conseguenza.
        vectorSorted[id_end] = vectorInit;     //sostanzialmente avremo il vector sorted dal piu piccolo al piu grande
        id_end--;  //indice finale scala di -1

        int id_cfr = 0;  //indice nodo corrente albero binario
        for (unsigned int i = 0; i < log2(n-(t+1)) ;i++) //scendo dell'altezza dell'albero
        {
            if(vectorHeap[2*id_cfr+1] > vectorHeap[2*id_cfr+2] || vectorHeap[2*id_cfr+1] == vectorHeap[2*id_cfr+2])// Viene eseguito un ciclo for che itera tante volte quanti sono i livelli dell'albero binario, partendo dal livello radice e scendendo man mano. La condizione del ciclo for è i < log2(n-(t+1)), dove n è la dimensione del vettore vectorHeap, t è il parametro di template t e log2() è la funzione che calcola il logaritmo in base 2 di un numero.Questo ci dà il numero di nodi nell'albero che dobbiamo controllare per verificare che la struttura di heap sia ancora rispettata.
            { // Il termine n-(t+1) indica il numero di foglie dell'albero binario completo di altezza h, dove h è il numero di livelli dell'albero (ricordiamo che un albero binario completo ha 2^h-1 nodi totali). Sottraendo t+1 da n si ottiene il numero di foglie nell'albero parziale di altezza h-t, dove t è il numero di livelli di cui si vuole preservare la struttura di heap.
                //Dentro il ciclo for, viene eseguita una condizione if per determinare se il nodo corrente ha un figlio destro e sinistro e in quale ramo ci si deve muovere per mantenere la struttura di heap. Se il figlio sinistro ha valore maggiore del figlio destro o se hanno lo stesso valore, si va nel ramo sinistro.


                if (vectorHeap[2*id_cfr+1] > vectorHeap[id_cfr] && (2*id_cfr+1 < id_end || 2*id_cfr+1 == id_end)) //Viene eseguita una condizione if per controllare se lo scambio deve essere effettuato con il figlio sinistro. La condizione verifica se il valore del figlio sinistro è maggiore del valore del nodo corrente e se il figlio sinistro si trova all'interno del sottoalbero corrente, ovvero se il suo indice è inferiore a id_end.

                {                                                         //aggiuntiva legata al fatto se la foglia c'è o meno
                    T swap = vectorHeap[2*id_cfr+1];
                    vectorHeap[2*id_cfr+1] = vectorHeap[id_cfr];    // Se la condizione precedente è vera, viene effettuato lo scambio tra il valore del figlio sinistro e il valore del nodo corrente. Viene poi aggiornato l'indice del nodo corrente con il valore del figlio sinistro.
                    vectorHeap[id_cfr] = swap;
                    id_cfr = 2*id_cfr+1;
                }

            }

            else   //qui se non va il primo if ossia se il figlio destro ha valore maggiore del sinistro si va qui
            {
                if (vectorHeap[2*id_cfr+2] > vectorHeap[id_cfr] && (2*id_cfr+2 < id_end || 2*id_cfr+2 == id_end)) //viene controllato se il valore del figlio destro del nodo corrente è maggiore del valore del nodo corrente stesso e se è necessario effettuare lo scambio tra i due valori.
                {                                                          //aggiuntiva legata al fatto se sono già alla conclusione del mio sottoalbero al passo n
                    T swap = vectorHeap[2*id_cfr+2];
                    vectorHeap[2*id_cfr+2] = vectorHeap[id_cfr];     //se è vera viene effettuato lo scambio tra il valore del nodo corrente e il valore del figlio destro. Viene utilizzata una variabile temporanea "swap" per effettuare lo scambio.
                    vectorHeap[id_cfr] = swap;
                    id_cfr = 2*id_cfr+2;
                }
            }
        }
    }

    return vectorSorted;
}


/// ... and other

}




#endif // __SORTING_H

