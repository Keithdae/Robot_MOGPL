#include "graph.h"

int main(int argc, char* argv[])
{
	bool done = false;
	std::string prompt = "";


	while(!done)
	{
		std::cout << "Veuillez entrer un nom de fichier, ou <q> pour quitter le programme : " << std::endl;
		getline(std::cin, prompt);
		if( ((prompt[0] == 'q') || (prompt[0] == 'Q')) && (prompt.size() == 1) )
		{
			done = true;
		}
		else
		{
			graph solver = graph(prompt);
			if(solver.isFileOpen())
			{
				solver.readProblem();
				// On boucle pour resoudre les problemes que l'on trouve dans le fichier
				bool end = false;
				while(!end)
				{
					end = true;
				}
				//solver.detruire();
			}
			else
			{
				std::cout << "L'ouverture du fichier a echoue" << std::endl;
				//solver.detruire(); 
			}
		}
		
	}
	std::cout << "Bye bye !" << std::endl;
	return 0;
}
