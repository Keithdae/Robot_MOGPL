#include "graph.h"

int main(int argc, char* argv[])
{
	bool done = false;
	std::string prompt = "";

	graph solver = graph();

	while(!done)
	{
		std::cout << "Veuillez entrer un nom de fichier, ou <q> pour quitter le programme : " << std::endl;
		getline(std::cin, prompt);
		if( ((prompt[0] == 'q') || (prompt[0] == 'Q')) && (prompt.size() == 1) )
		{
			done = true;
		}
		else if(solver.openFile(prompt))
		{
			// On boucle pour resoudre les problemes que l'on trouve dans le fichier
			bool end = false;
			while(!end)
			{
				end = true;
			}

			solver.closeFiles(); // On demande la fermeture du fichier
		}
		else
		{
			std::cout << "L'ouverture du fichier a echoue" << std::endl; 
		}
	}
	std::cout << "Bye bye !" << std::endl;
	return 0;
}
