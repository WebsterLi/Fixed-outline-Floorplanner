#include "floorplan.h"

//Choose the element want to cout to un-comment
void GRAPH::CoutTest(){	
	
	cout <<"Update cost : "<< best_cost << endl;
	cout <<"Boundry : " << boundry_x << ' ' << boundry_y << endl;
	cout <<"Max : " << max_x << ' ' << max_y << endl;
	
	cout << "Boundry is : " << boundry_x << ' ' << boundry_y << endl;
	cout << endl << "Block Info : " << endl;	

	for(auto AB : AllBlock){

		cout << AB->GetName() << ", leftchild : ";
		if(AB->leftchild != NULL) cout << AB->leftchild->GetName();
		else cout << "NULL";

		cout << ", rightchild : ";
		if(AB->rightchild != NULL) cout << AB->rightchild->GetName();
		else cout << "NULL";

		cout << ", parent : ";
		if(AB->parent != NULL) cout << AB->parent->GetName() << endl;
		else cout << "NULL" << endl;

		cout << "is_left : " << AB->is_left << endl;
	}

	cout << "Terminal :" << endl;
	for (auto AT : AllTerminal)cout << AT->GetX() << ' ' << AT->GetY() << endl;
	

}

void GRAPH::GNUPlot(const string& GNUFile){

	fstream GNU_out;
	GNU_out.open(GNUFile, fstream::out);
	
	for(int i=0; i < (int)AllBlock.size(); ++i){
		GNU_out << "set object " << i+1; 
		GNU_out << " rect from " << AllBlock[i]->GetX() << "," << AllBlock[i]->GetY();
		GNU_out << " to " << AllBlock[i]->EndX() << "," << AllBlock[i]->GetY() + AllBlock[i]->GetH();
		GNU_out << " fc rgb \"gold\"\n";
	}

	GNU_out << "set xrange [0:" << boundry_x << "]\n";//boundry_x.
	GNU_out << "set yrange [0:" << boundry_y << "]\n";//boundry_y.
	GNU_out << "plot sin(x) lt -1\n";
	GNU_out.close();

}

void GRAPH::WriteOutputFile(string OutputFile){
	
	fstream fout;
	fout.open(OutputFile, fstream::out);

	clock_t finish = clock();

	fout << best_cost << endl;
	fout << rand() << endl;
	fout << (boundry_x * boundry_y) << endl;
	fout << boundry_x << ' ' << boundry_y << endl;
	fout << 0 << endl;
	for(auto iter : AllBlock){
		fout << iter->GetName() << ' ' << iter->GetX() << ' ' << iter->GetY() << ' ';
		fout << iter->EndX() << ' ' << (iter->GetY() + iter->GetH()) << endl;
	}

	fout.close();
}
