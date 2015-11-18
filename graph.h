#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>



class graph
{
	public:
		graph();
		virtual ~graph();
		

		bool openFile(std::string fName);
		bool closeFiles();

		
	private:
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
		bool problem[50][50];  // true => obstacle ; false => libre
		
		

		void createGraph(); // Parcourt le probleme pour creer le graphe (sommet et liste d'adjacence pour les aretes)
		void bfs();

		void readProblem(); // Lit un probleme dans le fichier d'entree et renseigne n m problem xStart yStart xGoal yGoal dirStart
		void writeSolution(); // Ecrit la solution dans le fichier resultat
		
};



#endif // GRAPH_H
