#include "graph.h"

using namespace std;

graph::graph()
{

}

graph::~graph()
{

}


ifstream graph::openFile(const std::string fName)
{
	ifstream file;
	file = open(fName, ios::in);
	if (!file){
		cerr << "Impossible d'ouvrir le fichier!" << endl;
	}
	
	return file;
}

bool graph::closeFiles()
{
	bool res = false;
	
	return res;
}


void graph::createGraph()
{

}


void graph::bfs()
{

}


void graph::readProblem(ifstream file)
{
	file >> this->n >> this->m;
	for(size_t i=0; i<n; i++){
		for(size_t j=0; j<m; j++){
			file >> problem[i][j];
		}
	}
	file >> this->xStart >> this->yStart >> this->xGoal >> this->yGoal >> this->dirStart;
}		


void graph::writeSolution()
{

}
