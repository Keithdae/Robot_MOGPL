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

	//suppression des aretes en contact/passant par un ostacle
	for(int i=0;i<p.n;i++)
	{
		for(int j=0;j<p.m;j++)
		{
			if(p.grid[i][j])//il y a un obstacle a (i,j)
			{
				//les 4 coins adjacents a l'obstacle
				for(int k=0;k<4;k++)
				{
					grille[i][j][k].voisins.clear();
					grille[i+1][j][k].voisins.clear();
					grille[i][j+1][k].voisins.clear();
					grille[i+1][j+1][k].voisins.clear();
				}

				//suppression des aretes des sommets au dessus de l'obstacle
				if(i-3>=0)
				{
					if(grille[i-3][j][2].voisins.size()==5)
						grille[i-3][j][2].voisins.erase(grille[i-3][j][2].voisins.end()-1);
					if(grille[i-3][j+1][2].voisins.size()==5)
						grille[i-3][j+1][2].voisins.erase(grille[i-3][j+1][2].voisins.end()-1);
				}
				if(i-2>=0)
				{
					if(grille[i-2][j][2].voisins.size()>=4)
						grille[i-2][j][2].voisins.erase(grille[i-2][j][2].voisins.begin()+3,grille[i-2][j][2].voisins.end());
					if(grille[i-2][j+1][2].voisins.size()>=4)
						grille[i-2][j+1][2].voisins.erase(grille[i-2][j+1][2].voisins.begin()+3,grille[i-2][j+1][2].voisins.end());
				}
				if(i-1>=0)
				{
					if(grille[i-1][j][2].voisins.size()>=3)
						grille[i-1][j][2].voisins.erase(grille[i-1][j][2].voisins.begin()+2,grille[i-1][j][2].voisins.end());
					if(grille[i-1][j+1][2].voisins.size()>=3)
						grille[i-1][j+1][2].voisins.erase(grille[i-1][j+1][2].voisins.begin()+2,grille[i-1][j+1][2].voisins.end());
				}

				//suppression des aretes des sommets en desous de l'obstacle
				if(i+4<=p.n)
				{
					if(grille[i+4][j][0].voisins.size()==5)
						grille[i+4][j][0].voisins.erase(grille[i+4][j][0].voisins.end()-1);
					if(grille[i+4][j+1][0].voisins.size()==5)
						grille[i+4][j+1][0].voisins.erase(grille[i+4][j+1][0].voisins.end()-1);
				}
				if(i+3<=p.n)
				{
					if(grille[i+3][j][0].voisins.size()>=4)
						grille[i+3][j][0].voisins.erase(grille[i+3][j][0].voisins.begin()+3,grille[i+3][j][0].voisins.end());
					if(grille[i+3][j+1][0].voisins.size()>=4)
						grille[i+3][j+1][0].voisins.erase(grille[i+3][j+1][0].voisins.begin()+3,grille[i+3][j+1][0].voisins.end());
				}
				if(i+2<=p.n)
				{
					if(grille[i+2][j][0].voisins.size()>=3)
						grille[i+2][j][0].voisins.erase(grille[i+2][j][0].voisins.begin()+2,grille[i+2][j][0].voisins.end());
					if(grille[i+2][j+1][0].voisins.size()>=3)
						grille[i+2][j+1][0].voisins.erase(grille[i+2][j+1][0].voisins.begin()+2,grille[i+2][j+1][0].voisins.end());
				}

				//suppression des aretes des sommets a gauche de l'obstacle
				if(j-3>=0)
				{
					if(grille[i][j-3][1].voisins.size()==5)
						grille[i][j-3][1].voisins.erase(grille[i][j-3][1].voisins.end()-1);
					if(grille[i+1][j-3][1].voisins.size()==5)
						grille[i+1][j-3][1].voisins.erase(grille[i+1][j-3][1].voisins.end()-1);
				}
				if(j-2>=0)
				{
					if(grille[i][j-2][1].voisins.size()>=4)
						grille[i][j-2][1].voisins.erase(grille[i][j-2][1].voisins.begin()+3,grille[i][j-2][1].voisins.end());
					if(grille[i+1][j-2][1].voisins.size()>=4)
						grille[i+1][j-2][1].voisins.erase(grille[i+1][j-2][1].voisins.begin()+3,grille[i+1][j-2][1].voisins.end());
				}
				if(j-1>=0)
				{
					if(grille[i][j-1][1].voisins.size()>=3)
						grille[i][j-1][1].voisins.erase(grille[i][j-1][1].voisins.begin()+2,grille[i][j-1][1].voisins.end());
					if(grille[i+1][j-1][1].voisins.size()>=3)
						grille[i+1][j-1][1].voisins.erase(grille[i+1][j-1][1].voisins.begin()+2,grille[i+1][j-1][1].voisins.end());
				}

				//suppression des aretes des sommets a droite de l'obstacle
				if(j+4<=p.m)
				{
					if(grille[i][j+4][3].voisins.size()==5)
						grille[i][j+4][3].voisins.erase(grille[i][j+4][3].voisins.end()-1);
					if(grille[i+1][j+4][3].voisins.size()==5)
						grille[i+1][j+4][3].voisins.erase(grille[i+1][j+4][3].voisins.end()-1);
				}
				if(j+3<=p.m)
				{
					if(grille[i][j+3][3].voisins.size()>=4)
						grille[i][j+3][3].voisins.erase(grille[i][j+3][3].voisins.begin()+3,grille[i][j+3][3].voisins.end());
					if(grille[i+1][j+3][3].voisins.size()>=4)
						grille[i+1][j+3][3].voisins.erase(grille[i+1][j+3][3].voisins.begin()+3,grille[i+1][j+3][3].voisins.end());
				}
				if(j+2<=p.m)
				{
					if(grille[i][j+2][3].voisins.size()>=3)
						grille[i][j+2][3].voisins.erase(grille[i][j+2][3].voisins.begin()+2,grille[i][j+2][3].voisins.end());
					if(grille[i+1][j+2][3].voisins.size()>=3)
						grille[i+1][j+2][3].voisins.erase(grille[i+1][j+2][3].voisins.begin()+2,grille[i+1][j+2][3].voisins.end());
				}
			}
		}
	}

	return grille;
}


string graph::bfs(const problem p)
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

	bool goalReached = false;
	node bestGoal = *start;

	while(!q.empty() && !goalReached)
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
				if(cur->x == p.xGoal && cur->y == p.yGoal)
				{
					goalReached = true;
					bestGoal = *cur;
				}
			}	
		}
	}

	if(bestGoal.x == (*start).x && bestGoal.y == (*start).y)
	{
		cout << "Pas de chemin trouve!" << endl;
		return "-1\n";
	}

	// Debug
	vector<node> chemin;
	node par = bestGoal;
	chemin.push_back(par);
	cout << "la longueur du plus court chemin est: " << bestGoal.distance << endl;
	while(par.parent != NULL)
	{
		par = *par.parent;
		chemin.insert(chemin.begin(),par);
	}
	string res = writeSolution(bestGoal.distance,chemin);
	cout << res;
	return res;
	// /Debug
}


void graph::solveAllProblems()
{
	ofstream out(this->fileNameOutput);
	
	/*float timer[10];
	struct timeval tbegin, tend;
	float texec = 0.f;*/
	
	
	if(out.is_open())
	{
		for(unsigned int i=0; i<problems.size(); i++)
		{
			// Timer start
			//gettimeofday(&tbegin, NULL);
			
			string solution = bfs(problems[i]);
			
			// Timer end
			/*gettimeofday(&tend, NULL);
			texec = ((float)(tend.tv_sec - tbegin.tv_sec)) + (tend.tv_usec - tbegin.tv_usec) / 1000000.f;
			timer[i] = texec;*/
			
			out << solution;
		}
	}
	
	/*float averageTime = 0.f;
	for(int j=0; j<10; j++)
		averageTime += timer[j];
	
	averageTime = averageTime / 10.f;
	
	out << averageTime;*/
	
	problems.clear();
	
	out.close();
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

string graph::writeSolution(const int longueur, const vector<node> chemin)
{
	string solution = to_string(longueur);
	for(size_t i=0;i<chemin.size()-1;i++)
	{
		if(chemin[i].x == chemin[i+1].x && chemin[i].y == chemin[i+1].y && chemin[i+1].dir == ((chemin[i].dir + 1) % 4))
			solution += " D"; 
		else if(chemin[i].x == chemin[i+1].x && chemin[i].y == chemin[i+1].y && chemin[i+1].dir ==((4+((chemin[i].dir - 1) % 4))%4))
				solution += " G"; 
		else if(abs(chemin[i].x - chemin[i+1].x) == 1  || abs(chemin[i].y - chemin[i+1].y) == 1)
				solution += " a1"; 
		else if(abs(chemin[i].x - chemin[i+1].x) == 2  || abs(chemin[i].y - chemin[i+1].y) == 2)
				solution += " a2"; 
		else if(abs(chemin[i].x - chemin[i+1].x) == 3  || abs(chemin[i].y - chemin[i+1].y) == 3)
				solution += " a3"; 
		else
			cout << "NOPE"<< chemin[i].x << " " << chemin[i+1].x << " " << chemin[i].y << " " <<  chemin[i+1].y << " " << chemin[i].dir << " " << chemin[i+1].dir << endl;
	}
	return solution + "\n";
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


void graph::generateProblems(const int N, const int M, const int nbInst, const int nbObst, const std::string fName)
{
	vector< vector<bool> > grid(N + 1, vector<bool>(M + 1));  // Represente la grille d'obstacle avec true pour indiquer la presence d'un obstacle
	
	ofstream pbFile;
	pbFile.open(fName.c_str(), ios::out | ios::trunc );  // Ouverture du fichier en ecriture, si il existe deja il est ecrase


	for(int inst=0; inst<nbInst; inst++)
	{
		// Reinitialisation de la grille
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<M; j++)
			{
				grid[i][j] = false;
			}
		}
		
		int setObst = 0;  // Nombre d'obstacles en place dans la grille
		while(setObst < nbObst)
		{
			int x = rand()%N;
			int y = rand()%M;
			if(!grid[x][y])  // On verifie qu'il n'y a pas deja un obstacle
			{
				grid[x][y] = true;
				setObst++;
			}
		}
		
		// Une fois la grille remplie avec le bon nombre d'obstacle, on ecrit le probleme dans le fichier en respectant le format demande
		pbFile << N << " " << M << endl;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<M; j++)
			{
				pbFile << grid[i][j] << " ";
			}
			pbFile << endl;
		}
		
		bool done = false;
		int xStart = 0;
		int yStart = 0;
		while(!done)  // On genere des coordonnees de depart en verifiant que l'on ne tombe pas sur un obstacle
		{
			int xStart = rand()%(N+1);
			int yStart = rand()%(M+1);
			if( (!grid[xStart][yStart]) && (!grid[xStart - (xStart>0?1:0)][yStart]) && (!grid[xStart][yStart - (yStart>0?1:0)]) && (!grid[xStart - (xStart>0?1:0)][yStart - (yStart>0?1:0)]) )
			{
				pbFile << xStart << " " << yStart << " ";
				done = true;
			}
		}
		done = false;
		while(!done)  // On genere les coordonnees d'arrivee en verifiant que l'on tombe ni sur un obstacle ni sur le point de depart
		{
			int xGoal = rand()%(N+1);
			int yGoal = rand()%(M+1);
			if( (xGoal != xStart) || (yGoal != yStart) )
			{
				if( (!grid[xGoal][yGoal]) && (!grid[xGoal - (xGoal>0?1:0)][yGoal]) && (!grid[xGoal][yGoal - (yGoal>0?1:0)]) && (!grid[xGoal - (xGoal>0?1:0)][yGoal - (yGoal>0?1:0)]) )
				{
					pbFile << xGoal << " " << yGoal << " ";
					done = true;
				}
			}
		}
		int dir = rand()%4;  // On genere la direction
		pbFile << (dir == 0?"nord":(dir == 1?"est":(dir == 2?"sud":"ouest"))) << endl;
	}	

	// Une fois les problemes generes, on insere 0 0 pour indiquer la fin du fichier puis on le ferme
	pbFile << 0 << " " << 0;
	pbFile.close();
}


