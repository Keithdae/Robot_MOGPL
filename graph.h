#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>



class node // Pour representer les successeurs
{
	int x;
	int y;
	int dir;
	/* Nord  => 0
	*  Est   => 1
	*  Sud   => 2
	*  Ouest => 3
	*/
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
};


class graph
{
	public:
		graph();
		virtual ~graph();
		
		void solveAllProblems();

		bool readProblems(const std::string fName); // Lit l'ensemble des problemes dans le fichier d'entree et le stocke dans le vecteur problems

		
	private:
		std::string fileNameOutput;
		void createGraph(); // Parcourt le probleme pour creer le graphe (sommet et liste d'adjacence pour les aretes)

		std::vector<problem> problems;
		
		std::vector<node> grid[4];

		void bfs();

		
		void writeSolution(); // Ecrit la solution dans le fichier resultat
};



#endif // GRAPH_H
