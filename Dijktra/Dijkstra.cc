#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<stdio.h>
#include <fstream>
#include <string>
#include<cmath>

using std::cout;
using std::endl;
using std::string;


// ARRAY BASED IMPLEMENTATION OF DIJKSTRA 
#define MAX 10000  // initial distance 
#define V 5

// this is a function used in Dijkstra's Algorith that finds  the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minimum_distance(int* dist, bool* s,int n){
	int min = MAX;
	int min_index; // this will be the index represented the vertix
	for (int v = 0; v<n; v++){
		if(s[v]==false && dist[v]<=min){
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}

void print(int* dist,int n ){
	for (int i=0; i<n; i++){
		cout<<"Vertex: "<<i<<" distance from source: "<<dist[i]<<endl;
	}
}
void print_predecessor(int* dist,int n){
	for (int i=0; i<n; i++){
		cout<<"predecessor of "<<i<<": "<<dist[i]<<endl;
	}
}

// it receives in input the adjacency matrix and the source 
int** Dijkstra(int* graph, int src,int n){
	int** output{new int*[2]};
	int* ancestor{new int[n]}; // ancestor[i]= predecessor of i 
	for (int i = 0; i<n;i++){ancestor[i]=0;}
	ancestor[src]= -1; // we set acestor of the source as -1, ideed it has no predecessors 
	int* dist{new int[n]}; // the output dist[i] = distance of the vertex i from the source
	bool* s{new bool[n]}; //true if  distance from src to i is finalized (if we have yet discovered the minumu distance) 
	//initialization part--> we set all vertex undiscovered and with distance equal to inifinity 
	for(int i = 0;i<n;i++){
		dist[i]=MAX;
		s[i]=false;
	}
	// distance from source to itself is always zero
	dist[src] = 0;
	// Find shortest path for all vertices
	for (int i=0; i<n;i++){
		// Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minimum_distance(dist,s,n); 
		s[u]=true;
		// now we hace to update the distance vector
		for (int v = 0; v < V; v++){

			// dist[v] has to be updated only if v is s[v]=false, if there is an edge from u to v
			// and if we improve the actuale situation 
			if(s[v]==false && graph[u*n+v]!=0 && dist[u]!=MAX && dist[u] + graph[u*n+v]<dist[v]){
					dist[v] = dist[u] + graph[u*n + v];
					ancestor[v] = u;
			}
		}
	
	}
	output[0]=dist;
	output[1]=ancestor;
	return output;	

}





// function which create automatically graphs



int* create_graph(int Ve,int prob){
	int* res{new int[Ve*Ve]};
	for (int i=0;i<Ve;i++){
		for(int j = 0; j<Ve;j++){
			if(i==j){res[i*Ve + j ]=0;};
			int moneta = rand()%100;
			if(moneta > prob/2 && moneta< 100 - prob/2){
				res[i*Ve+j]=rand()%100 + 1;
			}
			else{res[i*Ve+j]=0;}
		}
	}
	return res;
}


















int main(){
	int* graph{new int[V*V]};
	for (int i = 0;i<V*V;i++){graph[i]=0;}
	graph[1]=5;
	graph[4]=10;
	graph[7]=2;
	graph[8]=9;
	graph[9]=3;
	graph[13]=6;
	graph[17]=4;
	graph[21]=2;
	graph[23]=1;

	int** distanze = Dijkstra(graph,0,5);
	print(distanze[0],V);
	cout<<"ora il vettore dei predecessori"<<endl;
	print_predecessor(distanze[1],V);
	cout<<endl;

	


	// timing 
	
	string array_dij = "array_dij.txt";
	std::fstream f{array_dij,f.app};
	f.close();
	for(int i{1};i<4;i++){
        for(int h{1};h<10;h = h+1){

            int size =h*pow(10,i);
            int* gr = create_graph(size,60);
            clock_t begin_1 = clock();
            Dijkstra(gr,0,size);
            clock_t end_1 = clock();
            f.open(array_dij,f.app);
            f<<((float)(end_1-begin_1))/CLOCKS_PER_SEC<<endl;
            f.close();
        }
}


	return 0;
}