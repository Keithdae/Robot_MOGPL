#include "graph.h"

using namespace std;

node::node(int x,int y,int dir)
{
	this->x=x;
	this->y=y;
	this->dir=dir;
}

graph::graph()
{

}

graph::~graph()
{

}


void graph::createGraph(const problem p)
{
	//creation de le grille avec n+1 lignes, m+1 colonnes et 4 direction pour chaque noeud 
	vector< vector< vector<node> > > grille;
	for(int i=0;i<=p.n;i++)
	{
		vector< vector<node> > ligne;
		for(int j=0;j<=p.m;j++)
		{			
			vector<node> noeud4;
			for(int k=0;k<4;k++)
			{
				node noeud=node(i,j,k);
				noeud4.push_back(noeud);
			}
			ligne.push_back(noeud4);
		}
		grille.push_back(ligne);
	}

	//creation de toutes les aretes 
	for(int i=0;i<=p.n;i++)
	{
		for(int j=0;j<=p.m;j++)
		{
			//noeud au nord
			grille[i][j][0].voisins.push_back(&grille[i][j][1]);
			grille[i][j][0].voisins.push_back(&grille[i][j][3]);
			if(i-3>=0)
			{
				grille[i][j][0].voisins.push_back(&grille[i-1][j][0]);
				grille[i][j][0].voisins.push_back(&grille[i-2][j][0]);
				grille[i][j][0].voisins.push_back(&grille[i-3][j][0]);
			}
			else
			{
				if(i-2>=0)
				{
					grille[i][j][0].voisins.push_back(&grille[i-1][j][0]);
					grille[i][j][0].voisins.push_back(&grille[i-2][j][0]);
				}
				else
				{
					if(i-1>=0)
					{
						grille[i][j][0].voisins.push_back(&grille[i-1][j][0]);
					}
				}
			}

			//noeud a l'est
			grille[i][j][1].voisins.push_back(&grille[i][j][2]);
			grille[i][j][1].voisins.push_back(&grille[i][j][0]);
			if(j+3<=p.m)
			{
				grille[i][j][1].voisins.push_back(&grille[i][j+1][1]);
				grille[i][j][1].voisins.push_back(&grille[i][j+2][1]);
				grille[i][j][1].voisins.push_back(&grille[i][j+3][1]);
			}
			else
			{
				if(j+2<=p.m)
				{
					grille[i][j][1].voisins.push_back(&grille[i][j+1][1]);
					grille[i][j][1].voisins.push_back(&grille[i][j+2][1]);
				}
				else
				{
					if(j+1<=p.m)
					{
						grille[i][j][1].voisins.push_back(&grille[i][j+1][1]);
					}
				}
			}

			//noeud au sud
			grille[i][j][2].voisins.push_back(&grille[i][j][3]);
			grille[i][j][2].voisins.push_back(&grille[i][j][1]);
			if(i+3<=p.n)
			{
				grille[i][j][2].voisins.push_back(&grille[i+1][j][2]);
				grille[i][j][2].voisins.push_back(&grille[i+2][j][2]);
				grille[i][j][2].voisins.push_back(&grille[i+3][j][2]);
			}
			else
			{
				if(i+2<=p.n)
				{
					grille[i][j][2].voisins.push_back(&grille[i+1][j][2]);
					grille[i][j][2].voisins.push_back(&grille[i+2][j][2]);
				}
				else
				{
					if(i+1<=p.n)
					{
						grille[i][j][2].voisins.push_back(&grille[i+1][j][2]);
					}
				}
			}

			//noeud a l'ouest
			grille[i][j][3].voisins.push_back(&grille[i][j][0]);
			grille[i][j][3].voisins.push_back(&grille[i][j][2]);
			if(j-3>=0)
			{
				grille[i][j][3].voisins.push_back(&grille[i][j-1][3]);
				grille[i][j][3].voisins.push_back(&grille[i][j-2][3]);
				grille[i][j][3].voisins.push_back(&grille[i][j-3][3]);
			}
			else
			{
				if(j-2>=0)
				{
					grille[i][j][3].voisins.push_back(&grille[i][j-1][3]);
					grille[i][j][3].voisins.push_back(&grille[i][j-2][3]);
				}
				else
				{
					if(j-1>=0)
					{
						grille[i][j][3].voisins.push_back(&grille[i][j-1][3]);
					}
				}
			}
		}
	}
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
				fileNameOutput = fName;
				fileNameOutput.append("Results");
				res = true;	
				file.close();
			}
			else // Il reste au moins un probleme a lire
			{
				problem p;
				int temp;
				p.n = n;
				p.m = m;
				for(int i=0; i<n; i++)
				{
					vector<bool> row;
					for(int j=0; j<m; j++)
					{
						file >> temp;
						row.push_back((temp == 1));
					}
					p.grid.push_back(row);
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

vector<problem> graph::getProblems()
{
	return this->problems;
}

void problem::afficher_grille()
{
	for(int i=0;i<this->n;i++)
	{
		for(int j=0;j<this->m;j++)
		{
			cout << this->grid[i][j] << " ";
		}
		cout << endl;
	}
}


