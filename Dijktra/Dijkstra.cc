#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<stdio.h>


using std::cout;
using std::endl;



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

// it receives in input the adjacency matrix and the source 
int* Dijkstra(int* graph, int src,int n){
	int* dist{new int[n]}; // the output dist[i] = distance of the vertex i from the source
	bool* s{new bool[n]}; //true if vertex i is included in shortest path tree or shortest distance from src to i is finalized 
	//initialization part
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
        int u = minimum_distance(dist, s,n); 
		s[u]=true;
		// now we hace to update the distance vector
		for (int v = 0; v < V; v++){

			// dist[v] has to be updated only if v is s[v]=false, if there is an edge from u to v
			// and if we improve the actuale situation 
			if(s[v]==false && graph[u*n+v]!=0 && dist[u]!=MAX && dist[u] + graph[u*n+v]<dist[v]){
					dist[v] = dist[u] + graph[u*n + v];
			}
		}
	}
	return dist;	

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

	int* distanze = Dijkstra(graph,0,5);
	print(distanze,V);
	return 0;
}