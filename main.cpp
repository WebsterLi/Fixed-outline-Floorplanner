#include "floorplan.h"

int main(int argc,char **argv){

	double t = Initial_Temperature;
	GRAPH graph;
	graph.BlockParser(argv[2]);
	graph.InitialTree();//Including Traversal_X() first time.	
	graph.Traversal(graph.root);
	graph.UpdateCost(t);
	cout <<"Initial cost : "<< graph.best_cost << endl;
	srand(time(NULL));/*time seed*/
	while(!graph.AreaLegality()){
		
		t *= heat_down_rate;
		graph.RandomOperation();
		graph.Traversal(graph.root);
		if(!graph.UpdateCost(t)) t = Initial_Temperature;

	}

	graph.NetParser(argv[3]);
	graph.WriteOutputFile(argv[4]);
	graph.GNUPlot(argv[5]);
	graph.ReleasePointer();
	
}
