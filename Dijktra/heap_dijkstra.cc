#include<stdlib.h>
#include<iostream>
#include<cmath>
#include <fstream>
#include <string>

using namespace std;

#define INT_MAX 10000
void printarray(int* d,int n);

/* bisogna cotruire la classe min_heap di modo che sia sensata per l'algoritmo di Dijsktra 
 la heap però deve contenere sia il vertice che la distanza)

La mia classe heap sarà formata:
    -da una variabile int size = numero di min_heap_nodes presenti nella heap al momento
    -int capacity = capacità della heap (data all'inizio)
    -un array di interi int* pos -> salva le posizioni dei nodi nella heap (serve per il decrease key)
    -u narray di min_heap_node dove si salvano i veri e propri nodi della heap 

Si sfrutta quindi una struct ausiliaria che rappresenta il singolo nodo--> questa struct si chiama min_heap_node  e ha come variabili:
    -int vert -> indica il vertice salvato del nodo 
    -int dist -> indica la distanza dall'eventuale sorgente

 */

 // struct che rappresenta un nodo della minheap

 struct min_heap_node{

     int vert; // indica il vertice
     int dist; //indica la distanza

     min_heap_node(int v,int d): vert{v} , dist{d} { }   // semplice costruttore del nodo (riceve in input due interi -->vertice e distanza)

     void print_node(){
         cout<<"vertice: "<<vert<<"  valore: "<<dist<<endl;
     }  




};

//  **************************** STRUCT MIN_HEAP ****************************************


struct min_heap{
    int capacity; // capacità della heap
    int size; // numero di min_heap_nodes presenti al momento
    int* pos; // serve per il decrease key 
    struct min_heap_node *array; 

    // costruttore del min_heap
    min_heap(int cap,int dim, struct min_heap_node* a,int* o): capacity{cap} ,size{dim}, pos{o}{
        this->array = (struct min_heap_node*) malloc(capacity * sizeof(struct min_heap_node)); // array di nodi di min-heap
        this->array = a;
        this->build_heap();
        
    }

// function of my struct

// funzioni helper--> restituiscono indici, non nodi della heap

    int get_dim(){return this->size;}
    
    int left_son(int i){return 2*i+1;}  
    int right_son(int i){return 2*i +2;}
    int parent(int i){return i/2;}
    int length(){return this->capacity;}
    struct min_heap_node* get_array(){return this->array;}


//in output abbiamo i due indici che rappresentano i nodi della heap da swappare  --> SI SWAPPA L'INTERO NODO 
void swap(int i,int j){
    struct min_heap_node t = (this->array[i]); 
    (this->array[i]) = (this->array[j]); 
    (this->array[j]) = t;
}

bool isEmpty() { 
    return this->size == 0; 
} 

bool is_valid_node(int j){return this->size>j;}

void minheapify(int i){
    int smallest,left,right;
    left = left_son(i);
    right = right_son(i);
    smallest = i; 
    if(is_valid_node(left) and this->array[left].dist < this->array[smallest].dist){smallest = left;}
    if(is_valid_node(right) and this->array[right].dist < this->array[smallest].dist){smallest = right;}
    if(smallest!=i){
        min_heap_node smallestnode = this->array[smallest];
        min_heap_node idxnode = this->array[i];
        // scambiare le posizioni
        this->pos[smallestnode.vert] = i;  
        this->pos[idxnode.vert] = smallest;
        swap(i,smallest);
        this->minheapify(smallest);
    }
}





void build_heap(){
    
    int i = this->size-1; // size della heap (equivalente al numero di nodi che ci sono al momento)
    while(i>=0){
        minheapify(i);
        i--;
    }
}

bool is_in_minheap(int v){
    if (this->pos[v] < this->size){return true;} 
   return false; 
} 

// funzione che serve per estrarre il minimo dalla heap 
struct min_heap_node extractmin(){
    if (this->isEmpty()==true){
        struct min_heap_node null{0,0};
        return null; 
    } 
    struct min_heap_node root = this->array[0];
    swap(0,this->size-1); // swap the root node with the last position of minheap
    // reduce heap size and heapify the root
    this->size = this->size -1;
    minheapify(0);
    return root;
}


// helper function per stampare la nostra heap 
void print_heap(){
    for(int i=0;i<this->size; i++){
         cout<<"vertice: "<<this->array[i].vert<<" distanza "<<this->array[i].dist<<" pos "<<this->pos[i]<<endl; 
        
    }
}

// verifica che la heap rispetti sempre la condizione di min_heap
bool ver(){
for(int i =0;i<this->size;i++){
    if(this->array[parent(i)].dist >  this->array[i].dist) return false;
}
return true;

}

void decreaseKey(int v,int dist){
    // Get the index of v in  heap array 
    int i = this->pos[v];
    // prendere il nodo e aggiornare la sua dist value
    this->array[i].dist = dist;
    // preservare la struttura della heap
    while(i>0 && this->array[i].dist < this->array[(i-1)/2].dist){
        // fare lo swap tra il nodo e il suo genitore
        this->pos[this->array[i].vert] = (i-1)/2;
        this->pos[this->array[(i-1)/2].vert] = i;
        this->swap(i,(i-1)/2);
        
        // andare nell'indice del genitore
        i = (i-1)/2;
    }
}

};
    


 //*********************** RAPPRESENTAZIONE DEL GRAFO *************************************************

 /*
il nostro grafo avrà come variabili:
    - un intero int v che rappresenta il numero di vertici 
    - una lista di adiacenza, la quale è rappresentata da un pointer alla testa di questa lista 
    -ogni nodo della lista è rappresentato dalla struct adjlistnode, la quale ha le seguenti variabili:
            -int dest ->prossimo vertice
            -int weight -> peso dell+arco
            -pointer al porssimo nodo 




 */   

  

// questa struct rappresenta un nodo nella lista di adiacenza
struct adjlistnode {
    int dest; // vertice prossimo
    int weight; // peso dell'edge
    struct adjlistnode* next;
};

// una funzione che mi crei un nuovo nodo della lista di adiacenza
struct adjlistnode* newadjlistnode(int dest,int weight){
    struct adjlistnode* newnode = (struct adjlistnode*) malloc(sizeof(struct adjlistnode)); 
    newnode->dest = dest;
    newnode->weight = weight;
    newnode->next = NULL;
    return newnode;
}













// questa struct rappresenta la lista
struct adjlist 
{ 
    struct adjlistnode *head;  // pointer to head node of list 
}; 

// vera e propria struct graph, con il metodo addedge 

struct graph{

    int v; // numeber of vertices
    struct adjlist*  array; // la nostra lista di adiacenza 
    bool direct; // se è true---> grafo è diretto, altrimento è indiretto
    graph(int v,bool b): v{v}, direct{b}{
        // allochiamo memoria per l'array di liste di adiacenza
        this->array = (struct adjlist*) malloc(v*sizeof(struct adjlist));
        // inizializziamo tutt le liste di adiacenza vuote
        for(int i=0;i<v;i++){this->array[i].head = nullptr;}
    }
    
    void addedge(int src,int dest,int weight){
        // aggiungiamo un arco da src a dest. un nodo viene aggiunto alla lista di adiacenza of src
        // il nodo viene aggiunto all'inizio
        struct adjlistnode* newnode = newadjlistnode(dest,weight);
        newnode->next = this->array[src].head;
        this->array[src].head = newnode;

        // creiamo un grafo indiretto per ora
        if(this->direct==false){
            struct adjlistnode* newnode2 = newadjlistnode(src,weight);
            newnode2->next = this->array[dest].head;
            this->array[dest].head = newnode2;
        }
    }

    

    
    
};



void dijkstra(struct graph graph,int src){

    int V = graph.v;
    int* dist{new int[V]}; // questo sarà il nostro vettore di output
    //for (int i =0;i<v;i++){dist[i] = INT_MAX;} 
    //dist[src]=0;
    // creare la minheap con gli elementi del grafo 
    //per prima cosa creiamo un vettore di nodi della min-heap
    min_heap_node* ar =(min_heap_node*)malloc(V*sizeof(min_heap_node));
    //riempiamo l'array ar dei nodi del grafo 
    int *pos = (int*)malloc(7*sizeof(int));
        for(int i =0;i<7;i++){pos[i]=0;}
    min_heap hp{V,V,ar,pos};
    for(int v =0;v<V;v++){
        dist[v]=INT_MAX;
        min_heap_node temp{v,dist[v]};
        hp.array[v] = temp;
        hp.pos[v]=v;
    }

    dist[src]=0;
    min_heap_node sou{src,dist[src]};
    hp.array[src]=sou;
    hp.decreaseKey(src,dist[src]);
    // ora abbiamo il vettore con i nodi della heap---> creare una min-heap
    //min_heap hp{v,v,ar};

    // ora iniziamo con il while loop che finirà quando tutti i nodi saranno stati raggiunti
    // all'inizio ,la nostra minheap contiene tutti i nodi
    while(!hp.isEmpty()){
        //estraiamo il vertice con la distanza minima (la prima volta sarà sempre la sorgente)
        min_heap_node minode = hp.extractmin();
        int u = minode.vert; // estraiamo il vertice relativo 
        // attraversiamo la lista di adiacenza relativa al nostro vertice u e facciamo l'update delle distanze
        struct adjlistnode* p = graph.array[u].head;
        
        while(p!=nullptr){
            int v = p->dest;
            // se la distanza di v non è ancora stata finalizzata e inoltre 
            // la distanza tra v e u è minore dalla distanza calcolata in precedenza, la cambiamo 
           
            if((hp.is_in_minheap(v)) && dist[u]!=INT_MAX && p->weight + dist[u] < dist[v]){
                
                dist[v]=dist[u] + p->weight;
                //ora bisogna cambiare anche la minheap
                hp.decreaseKey(v,dist[v]); // vediamo cosa fa 
                
            }
            p = p->next;
        }
    }
    //printarray(dist,V);

}



void printarray(int* d,int n){

    cout<<"Vertex    Distance from Source"<<endl;
    for(int i=0;i<n;++i){
        cout<<"  "<<i<<"           "<<d[i]<<endl;
    }
}

bool equal_edges(adjlistnode* a,adjlistnode* b){
    if(a->dest==b->dest & a->next==b->next){return true;}
    else return false;
}

// questo crea un multigrafo
graph* create_graph(int V,int E,bool b){
     graph* gr = new graph(V,b);
     int div;
     int i = 0;
     
    while(i<V-1){
        if (i ==0){div =  E/V + E/V;}
        else{div = E/V;}
        for(int u=0;u<div;u++){
            int arr = i + rand()%(V-i);
            if(arr==i & i<V-1){arr++;};
            int peso = rand()%100 +1;
            gr->addedge(i,arr,peso);
            
        }
        i = i+1;
    }
    
    return gr;
}


























int main(){
// provo a creare random un grafo

graph* prova = create_graph(10,20,false);
dijkstra(*prova,0);


struct graph  gr{9,false}; 
gr.addedge(0,1,4);
gr.addedge(0,7,8);
gr.addedge(1,2,8);
gr.addedge(1, 7, 11); 
gr.addedge(2, 3, 7); 
gr.addedge(2, 8, 2); 
gr.addedge(2, 5, 4); 
gr.addedge(3, 4, 9); 
gr.addedge(3, 5, 14); 
gr.addedge(4, 5, 10); 
gr.addedge(5, 6, 2); 
gr.addedge(6, 7, 1); 
gr.addedge(6, 8, 6); 
gr.addedge(7, 8, 7);
 
clock_t begin = clock();
 dijkstra(gr,0);
clock_t end = clock();
cout<<"computed time for a graph of dimension "<<9<<"  is  "<<double(end - begin) / CLOCKS_PER_SEC<<endl;

/*
	clock_t begin_1 = clock();
	dijkstra(*graph_big, 0);
	clock_t end_1 = clock();
cout<<"computed time for a graph of dimension "<<30<<"  is  "<<double(end_1 - begin_1) / CLOCKS_PER_SEC<<endl;

*/
// timing 
string dij = "dij.txt";
std::fstream f{dij,f.app};
f.close();

for(int i{1};i<4;i++){
        for(int h{1};h<10;h = h+1){

            int size =h*pow(10,i);
            cout<<size<<endl;
            graph* gr = create_graph(size,10*size,false);
            clock_t begin_1 = clock();
            dijkstra(*gr,0);
            clock_t end_1 = clock();
            f.open(dij,f.app);
            f<<((float)(end_1-begin_1))/CLOCKS_PER_SEC<<endl;
            f.close();
        }
}




return 0;
}
