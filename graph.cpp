#include "graph.h"

using namespace std;

graph::graph()
{

}

graph::~graph()
{

}


bool graph::openFile(const std::string fName)
{
	bool res = true;
	this->file->open(fName.c_str(), ifstream::in);
	if (!file->is_open())
	{
		res = true;
	}
	
	return res;
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


void graph::readProblem()
{
	*file >> this->n >> this->m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			*file >> problem[i][j];
		}
	}
	*file >> this->xStart >> this->yStart >> this->xGoal >> this->yGoal >> this->dirStart;
}		


void graph::writeSolution()
{

}
