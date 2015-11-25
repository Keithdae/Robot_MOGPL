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


vector< vector< vector<node> > > graph::createGraph(const problem p)
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
			grille[i][j][0].voisins.push_back(&grille[i][j][1]); // Tourne Droite
			grille[i][j][0].voisins.push_back(&grille[i][j][3]); // Tourne Gauche
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
			grille[i][j][1].voisins.push_back(&grille[i][j][2]); // Tourne Droite
			grille[i][j][1].voisins.push_back(&grille[i][j][0]); // Tourne Gauche
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
			grille[i][j][2].voisins.push_back(&grille[i][j][3]); // Tourne Droite
			grille[i][j][2].voisins.push_back(&grille[i][j][1]); // Tourne Gauche
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
			grille[i][j][3].voisins.push_back(&grille[i][j][0]); // Tourne Droite
			grille[i][j][3].voisins.push_back(&grille[i][j][2]); // Tourne Gauche
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
	return grille;
}


void graph::bfs(const problem p)
{
	vector< vector< vector<node> > > grille = createGraph(p);
	for(unsigned int i=0; i<grille.size();i++)
	{
		for(unsigned int j=0; j<grille[0].size(); j++)
		{
			for(unsigned int k=0; k<grille[0][0].size(); k++)
			{
				grille[i][j][k].distance = INF; // Tous les noeuds sont consideres a une distance infinie
				grille[i][j][k].parent = NULL;  // On ne connait pas le chemin pour les atteindre
			}
		}
	}
	
	cout << "Debut du parcours" << endl;

	node *start = &grille[p.xStart][p.yStart][p.dirStart]; // Noeud de depart
	start->distance = 0;
	queue<node *> q;
	q.push(start);

	while(!q.empty())
	{
		node *u = q.front();
		q.pop();
		for(unsigned int v=0; v<u->voisins.size(); v++)
		{
			node *cur = u->voisins[v];
			if(cur->distance == INF)
			{
				cur->distance = u->distance + 1;
				cur->parent = u;
				q.push(cur);
			}	
		}
	}

	cout << "Fin du parcours" << endl;
	// Debug
	vector<node> goals = grille[p.xGoal][p.yGoal];
	node bestGoal = goals[0];
	for(unsigned int t=1; t<goals.size(); t++)
	{
		if(goals[t].distance < bestGoal.distance)
		{
			bestGoal = goals[t];
		}
	}
	node par = bestGoal;
	while(par.parent != NULL)
	{
		cout << "x=" << par.x << ", y=" << par.y << ", dir= " << (par.dir == 0?"Nord":(par.dir == 1?"Est":(par.dir == 2?"Sud":"Ouest"))) << endl;
		par = *par.parent;
	}
	// /Debug
}


void graph::solveAllProblems()
{
	for(unsigned int i=0; i<problems.size(); i++)
	{
		bfs(problems[i]);
	}
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


