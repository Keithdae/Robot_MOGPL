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
		bool closeFile();
	private:
		
};



#endif // GRAPH_H
