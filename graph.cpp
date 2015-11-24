#include "graph.h"

using namespace std;

graph::graph()
{

}

graph::~graph()
{

}



void graph::createGraph()
{

}


void graph::bfs()
{

}


void graph::solveAllProblems()
{

}


bool graph::readProblems(const std::string fName)
{
	bool res = false;
	
	ifstream file(fName, ios::in);
	
	if(file) // Test l'ouverture du fichier
	{
		int n = -1;
		int m = -1;
		while(!res)
		{
			file >> n >> m;
			if((n == 0) && (m == 0)) // On a atteint la fin du fichier
			{
				res = true;	
			}
			else // Il reste au moins un probleme a lire
			{
				problem p;
				p.n = n;
				p.m = m;
				for(int i=0; i<n; i++)
				{
					for(int j=0; j<m; j++)
					{
						file >> p.grid[i][j];
					}
				}

				string dir = "";
				file >> p.xStart >> p.yStart >> p.xGoal >> p.yGoal >> dir;

				if(dir == "nord"){p.dirStart = 0;}
				else if(dir == "est"){p.dirStart = 1;}
				else if(dir == "sud"){p.dirStart = 2;}
				else{p.dirStart = 3;}
				
				problems.push_back(p);
			}
		}
	}

	return res;
}		


void graph::writeSolution()
{

}
