#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <array>
#include <string.h>
#include <limits>
using namespace std;


const int INF = numeric_limits<int>::max();

vector<int> curFlowCopy ;
vector<int> prevVerCopy;
vector<int> prevEdgeCopy;
vector<int> distCopy;
class Edge {
public:
	int to,cost,capacity, back;
	int flow =0;
	Edge(int to,int capacity, int cost, int back) {
		this->cost = cost;
		this->back=back;
		this->to = to;
		this->capacity = capacity;
	}
};


void bellmanFord(vector<vector<Edge>> residualGraph,int source,vector<int> distances, vector<int> prevVer,vector<int> prevEdge, vector<int> currentFlow){
	// references: https://sites.google.com/site/indy256/algo/min_cost_flow_bf, PS11, PS12
	int nOfEdges = residualGraph.size();
	fill(distances.begin(),distances.end(),INF);
	distances[source] = 0;
	currentFlow[source] =INF;
	vector<bool> inqueue(nOfEdges,false);
	vector<int> vertexGraph (nOfEdges);
	int currentVertex = 0;
	vertexGraph[currentVertex++] = source;
	
	for(int i = 0 ; (i- currentVertex )%nOfEdges !=0;i++){

		int u = vertexGraph[i%nOfEdges];
	
		inqueue[u] =false;
		
	
		  

		for(int i = 0 ; i<residualGraph[u].size();i++){

			if(residualGraph[u][i].flow>=residualGraph[u][i].capacity){			 
					  
				continue;
			}
			int v = residualGraph[u][i].to;

			int currentDist = distances[u]+residualGraph[u][i].cost;
				
			
			if(distances[v]>currentDist){

				distances[v]=currentDist;
				prevVer[v]=u;

				prevEdge[v] =i;

				currentFlow[v] = min(currentFlow[u],residualGraph[u][i].capacity- residualGraph[u][i].flow);
		
				if(!inqueue[v]){

					inqueue[v]=true;

					vertexGraph[currentVertex++%nOfEdges]=v;



				}
			}

		}

	}
	curFlowCopy = currentFlow;
	prevVerCopy = prevVer;
	prevEdgeCopy = prevEdge;
	distCopy=distances;


}
int minCostMaxFLow(vector<vector<Edge>> residualGraph,int source,int sink,int maxFlow){
	// references: https://sites.google.com/site/indy256/algo/min_cost_flow_bf, PS11, PS12
int nOfEdges = residualGraph.size();
vector<int> distances (nOfEdges);
vector<int> currentFlow (nOfEdges);
vector<int> prevEdge (nOfEdges);
vector<int> prevVer (nOfEdges);
int flow = 0;
int flowCost = 0;

while(flow<maxFlow){

	bellmanFord(residualGraph,source,distances,prevVer,prevEdge,currentFlow);
	currentFlow = curFlowCopy;
	prevEdge=prevEdgeCopy;
	prevVer=prevVerCopy;
	distances = distCopy;
	if(distances[sink]==INF){
		break;
	}

	int backFlow =min(currentFlow[sink],maxFlow-flow);

	flow+=backFlow;

	for(int v = sink ; v!=source ; v=prevVer[v]){

	 residualGraph[prevVer[v]][prevEdge[v]].flow+=backFlow;


		residualGraph[v][residualGraph[prevVer[v]][prevEdge[v]].back].flow-=backFlow;
		flowCost+=backFlow* residualGraph [prevVer[v]][prevEdge[v]].cost;

	}

}
return -flowCost;

}

int main(int argc, char* argv[]) {
	
	

	string infile_name = argv[1];
	
	string outfile_name = argv[2];
 	
 	ifstream infile ;
	
	infile.open(infile_name);
	
	ofstream outfile ;
	
	outfile.open(outfile_name);

	string snOfTestCases;
	
	infile>>snOfTestCases;
	
	int nOfTestCases = stoi(snOfTestCases);



	for(int a = 0 ; a<nOfTestCases;a++){
	
	
		string snOfCables;
	
		infile>>snOfCables;
		
		int nOfCables = stoi(snOfCables);
		int nOfVertex = nOfCables*2+2;
		bool used = false;

	vector<vector<int>> cost(nOfVertex+1,vector<int>(nOfVertex+1, 0));
	vector<vector<int>> capacities(nOfVertex+1,vector<int>(nOfVertex+1, 0));

		 int nOfEdge = (nOfCables*2)+(nOfCables*nOfCables);

		vector<vector<Edge>> graphVector (nOfEdge);


		for(int i = 1; i<=nOfCables ; i++){

			Edge s = Edge(i,1,0,graphVector[i].size());
			Edge t = Edge(0,0,0,graphVector[0].size()-1);
			graphVector[0].push_back(s);
			graphVector[i].push_back(t);	

			for(int j = nOfCables+1; j<nOfCables*2+1 ; j++){

				
				string svoltage;
				
				infile>>svoltage;

				int voltage = stoi(svoltage);

	
				Edge from = Edge(j,1,-voltage,graphVector[j].size());
				Edge to = Edge(i,0,voltage,graphVector[i].size());

				graphVector[i].push_back(from);
				graphVector[j].push_back(to);



				
		}

		used = true;
		}
	for(int b = nOfCables+1;b<nOfCables*2+1;b++){
		

					Edge frm = Edge(nOfVertex-1,1,0,graphVector[nOfVertex-1].size());
					Edge too = Edge(b,0,0,graphVector[b].size()-1);
			
					graphVector[b].push_back(frm);
					graphVector[nOfVertex-1].push_back(too);
				}
	




    int src = 0;
    int sink = nOfVertex-1;



outfile<<minCostMaxFLow(graphVector,src,sink,INF)<<endl;


}
	
	
	infile.close();
	outfile.close();
    return 0;
}
