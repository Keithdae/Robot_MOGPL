#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <unistd.h>


// Definit la taille maximale de la matrice des obstacles d'un probleme
#define MAX_ROWS 50
#define MAX_COLS 50



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

		bool grid[MAX_ROWS][MAX_COLS];  // true => obstacle ; false => libre
};


class graph
{
	public:
		graph();
		virtual ~graph();
		

		bool closeFiles();

		bool readProblems(const std::string fName); // Lit l'ensemble des problemes dans le fichier d'entree et le stocke dans le vecteur problems

		
	private:
		void createGraph(); // Parcourt le probleme pour creer le graphe (sommet et liste d'adjacence pour les aretes)

		std::vector<problem> problems;
		
		std::vector<node> grid[4];

		void bfs();

		
		void writeSolution(); // Ecrit la solution dans le fichier resultat
};



#endif // GRAPH_H
