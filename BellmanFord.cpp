// All pairs shortest path Bellman-Ford serial and omp parallel
#include <bits/stdc++.h>
#include "omp.h"
using namespace std;


//parallel bellman ford
void BellmanFord(int graph[][3], int V, int E, int src)
{
	// Initialize distance of all vertices as infinite.
	int dist[V];
//#pragma omp parallel for if(V > 40)	
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;

	// initialize distance of source as 0
	dist[src] = 0;

	// Relax all edges |V| - 1 times. 
//#pragma omp parallel for	//parallelize the first loop.
	for (int i = 0; i < V - 2; i++) {
		for (int j = 0; j < E; j++) {
			if (dist[graph[j][0]] != INT_MAX && dist[graph[j][0]] + graph[j][2] < dist[graph[j][1]]){
				dist[graph[j][1]] =dist[graph[j][0]] + graph[j][2];
			}
		}
	}

	// check for negative-weight cycles.
//#pragma omp parallel for	
	for (int i = 0; i < E; i++) {
		int x = graph[i][0];
		int y = graph[i][1];
		int weight = graph[i][2];
		if (dist[x] != INT_MAX && dist[x] + weight < dist[y])
			cout << "Graph contains negative weight cycle" << endl;
	}

	cout << "Vertex Distance from "<< src << endl;
	for (int i = 0; i < V; i++)
		cout << i << "\t\t" << dist[i] << endl;
}

// serial bellman ford
void BellmanFordSerial(int graph[][3], int V, int E,int src)
{
	// Initialize distance of all vertices as infinite.
	int dist[V];	
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;

	// initialize distance of source as 0
	dist[src] = 0;

	// Relax all edges |V| - 1 times. 
	for (int i = 0; i < V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int a = graph[i][0];
			int b = graph[i][1];
			int w = graph[i][2];
			if(dist[a] != INT_MAX
                && dist[a] + w < dist[b])
                {
                	dist[b] = dist[a] + w;
				}
                
		}
	}

	// check for negative-weight cycles.
	for (int i = 0; i < E; i++) {
		int x = graph[i][0];
		int y = graph[i][1];
		int weight = graph[i][2];
		if (dist[x] != INT_MAX
            && dist[x] + weight < dist[y]) 
            {
            	printf("Graph contains negative weight cycle");
                return; // If negative cycle is detected, simply
                    // return
			}
            
		
}

	cout << "Vertex Distance from "<< src << endl;
	for (int i = 0; i < V; i++)
		cout << i << "\t\t" << dist[i] << endl;

 
    return;	
		
}


int main()
{
	int V; // Number of vertices in graph
	int E ; //Number of edges in graph
	cout<< "input number of vertices"<<endl;
	cin >> V ;
	cout<< "input number of edges"<<endl;
	cin >> E ;
	int graph[E][3];
	int graph2[E][3];
	cout<<"input each edge as source vertix, dest vertix, weight"<<endl;
	cout<<"note: vertices go from 0 to " << V-1 <<endl;
	for(int i=0;i<E;i++){
		for(int j=0;j<3;j++){
			cin>> graph[i][j];
		}
	}
//	double st=omp_get_wtime();
//#pragma omp parallel for
    int vertex_num=V;
    graph2[E][3] = graph[E][3];
    int edge_num=E;
//	for(int i=0;i<V;i++){
////		#pragma omp critical
//	    BellmanFord(graph2, vertex_num,edge_num, i);
//	}
//	double en=omp_get_wtime();
//	double parallelTime = en - st;
	
	
	double st2=omp_get_wtime();
	for(int i=0;i<V;i++){
	    BellmanFordSerial(graph2, vertex_num,edge_num, i);
	}
	double en2=omp_get_wtime();
	double serialTime = en2 - st2;
	
	
	cout<< "serial Time : " << serialTime << endl; 
//	cout<< "parallel Time : "<< parallelTime << endl;
	
	
	
	return 0;
}

