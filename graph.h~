#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unistd.h>

#define INF 10000000

class node // Pour representer les successeurs
{
	public: 
		int x;
		int y;
		int dir;
		/* Nord  => 0
		*  Est   => 1
		*  Sud   => 2
		*  Ouest => 3
		*/

		int distance;

		node *parent;
		
		std::vector<node *> voisins;

		
		

		node(int, int, int);
};


class problem
{
	public:
		int xStart;
		int yStart;
		int xGoal;
		int yGoal;

		int dirStart;
		/* Nord  => 0
		*  Est   => 1
		*  Sud   => 2
		*  Ouest => 3
		*/

		int n; // Nombre de lignes du probleme
		int m; // Nombre de colonnes du probleme

		std::vector< std::vector<bool> > grid;  // true => obstacle ; false => libre

		void afficher_grille();
};

class graph
{
	public:
		graph();

		virtual ~graph();
		
		void solveAllProblems();

		bool readProblems(const std::string fName); // Lit l'ensemble des problemes dans le fichier d'entree et le stocke dans le vecteur problems

		std::vector<problem> getProblems();

		// Genere un nombre nbInst de probleme avec N lignes, M colonnes et nbObst obstacles, puis stocke le resultat dans le fichier fName 
		void generateProblems(const int N, const int M, const int nbInst, const int nbObst, const std::string fName);
		
	private:
		std::string fileNameOutput;

		std::vector< std::vector< std::vector<node> > > createGraph(const problem); // Parcourt le probleme pour creer le graphe (sommet et liste d'adjacence pour les aretes)

		std::vector<problem> problems;

		std::string bfs(const problem);
		
		std::string writeSolution(const int longueur, const std::vector<node>); // Ecrit la solution dans le fichier resultat
  
};



#endif // GRAPH_H
