#include <iostream>
#include "Vertex.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;
vector<int> merge (vector<int> v1, vector<int> v2){
vector<int> mergedVec;
bool bo = true;

for(auto a : v1){

	mergedVec.push_back(a);
	if(a==v2[0]&&bo){
		mergedVec.pop_back();
		for(auto b : v2){
			mergedVec.push_back(b);
		}

		bo=false;
	}

}

return mergedVec;

}

int main(int argc, char const *argv[]) {


	string infile_name = argv[1];
	
	string outfile_name = argv[2];
 	
 	ifstream infile ;
	
	infile.open(infile_name);
	
	ofstream outfile ;
	
	outfile.open(outfile_name);

	string strNOfVertex;

	infile>>strNOfVertex;

	bool isEulerian;
	
	int nOfVertex = stoi(strNOfVertex);
	vector<Vertex*> vertexVec;
	int edgeVecSize = 0 ;
	for(int i = 0 ; i<nOfVertex ; i++){
		Vertex *vertex = new Vertex(i);
		vertexVec.push_back(vertex);
	}
	
	for(int i = 0 ; i<nOfVertex ; i++){

		string strVID;
		string strOutDegree;
		infile>>strVID>>strOutDegree;
		int vertexID = stoi(strVID);
		int outDegree = stoi(strOutDegree);
		
		vertexVec[i]->outDegree=outDegree;
		edgeVecSize+=outDegree;
		for(int j = 0 ; j<outDegree;j++){
			string strID;
			infile>>strID;
			int ID = stoi(strID);
			vertexVec[i]->outDegreeIDs.push_back(ID);
			vertexVec[ID]->inDegree++;
			if(vertexVec[ID]->inDegree==vertexVec[ID]->outDegree){
				isEulerian=true;
			}
			else{
				isEulerian=false;
			}
		}
	
		
	}
	string strStart;
	infile>>strStart;
	int startingVertexID = stoi(strStart);
	vector<int> eulerianCircuitVector;

	
	if(!isEulerian){

		outfile<<"no path";
		return 0;
	}
		
		eulerianCircuitVector.push_back(startingVertexID);
		
		while(eulerianCircuitVector.size()<=edgeVecSize){
			
			
			vector<int> tourVector;
			tourVector.push_back(startingVertexID);
			while(vertexVec[startingVertexID]->outDegree>0){

int idx = vertexVec[startingVertexID]->outDegreeIDs.size()-vertexVec[startingVertexID]->outDegree;
				
				vertexVec[startingVertexID]->outDegree--;

				tourVector.push_back(vertexVec[startingVertexID]->outDegreeIDs[idx]);

				startingVertexID = vertexVec[startingVertexID]->outDegreeIDs[idx];
				
			}
			
				

			if(tourVector.size()>0){
			eulerianCircuitVector = merge(eulerianCircuitVector,tourVector);
		}


		for(auto x: eulerianCircuitVector){
			if(vertexVec[x]->outDegree>0){
				startingVertexID=x;
			
				break;
				
			}
		}



		}
		for(auto x : eulerianCircuitVector){
			outfile<<x<<" ";
		}



	infile.close();
	outfile.close();
	return 0;
}