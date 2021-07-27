#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <math.h>//pow
#include <fstream>
#include <limits>// std::numeric_limits
#include <cstdlib>
#include <algorithm>
#include <stdlib.h> /* for ramdom*/
#include <time.h>   /* for time()*/
#include <chrono>

#define Initial_Temperature 100000
#define heat_down_rate 0.9995
using namespace std;

class BLOCK{
	
	public:
		
		BLOCK(string name, int w, int h);
		BLOCK *leftchild;//Left child of the BLOCK.
		BLOCK *rightchild;//Right child of the BLOCK.
		BLOCK *parent;//Parent of the BLOCK.
		bool is_left;//1 if the BLOCK is the left children of its parent.
		void RestoreW(){w =last_w;}
		void RestoreH(){h =last_h;}
		void RestoreX(){h =last_x;}
		void RestoreY(){h =last_y;}

		BLOCK *last_leftchild;//Left child of the BLOCK.
		BLOCK *last_rightchild;//Right child of the BLOCK.
		BLOCK *last_parent;//Parent of the BLOCK.
		bool last_is_left;//1 if the BLOCK is the left children of its parent.
		void BackupW(){last_w = w;}
		void BackupH(){last_h = h;}
		void BackupX(){last_x = x;}
		void BackupY(){last_y = y;}
		
		string GetName(){return name;}
		int GetW(){return w;}
		int GetH(){return h;}
		int GetX(){return x;}
		int GetY(){return y;}
		int GetArea(){return (w*h);}
		int EndX(){return (x+w);}
		void WriteX(int x){this->x = x;}
		void WriteY(int y){this->y = y;}
		void WriteW(int w){this->w = w;}
		void WriteH(int h){this->h = h;}

	private:
		
		string name;	
		int w;//width. 
		int h;//height.
		int last_w;//last width. 
		int last_h;//last height.
		int x;//x coordinate of its left-down corner.
		int y;//y coordinate of its left-down corner.
		int last_x;//last better x. 
		int last_y;//last better y. 

};

class TERMINAL{//pin coordinate to caculate HPWL.
	
	public:

		TERMINAL(string name, int x, int y);
		int GetX(){return x;}
		int GetY(){return y;}
		string GetName(){return name;}
		void WriteX(int x){this->x = x;}
		void WriteY(int y){this->y = y;}

	private:

		string name;
		int x;
		int y;

};

class GRAPH{

	public:
	
		GRAPH();
		BLOCK *root;
		BLOCK *last_root;
		int current_cost;
		int last_cost;
		int best_cost;
		double possibility ;
		vector<int> contour;
		clock_t start;

		/*parser.cpp*/
		void ParseLine(const string& line);
		void BlockParser(string BlockFile);//.block parser.
		void NetParser(string NetFile);//.net parser.

		/*output.cpp*/
		void CoutTest();//Cout info.
		void GNUPlot(const string& GNUFile);//output GNUPlot file.
		void WriteOutputFile(string OutputFile);

		/*operation.cpp*/
		bool AreaLegality();
		double MoveOnPossibility(double t);
		void SwapBlock(BLOCK *B1, BLOCK *B2);
		void DeleteBlock(BLOCK *B1, BLOCK *B2);
		void RotateBlock(BLOCK *B);
		bool UpdateCost(double t);
		void RandomOperation();//determine operation by random.

		/*bstree.cpp*/
		void InitialTree();//Initial solution B*Tree.
		void Traversal(BLOCK *r);//Update x,y coordionate & contour.
		void ReleasePointer();//Release memory.
		void StoreResult();//Backup Current best solution. 
		void LoadResult();//Recover Current best solution. 

	private:
	
		vector<BLOCK*> AllBlock;
		vector<BLOCK*> TempResult;
		vector<TERMINAL*> AllTerminal;
		vector<vector<string>> AllNet;
		int boundry_x;//x size of core region.
		int boundry_y;//y size of core region.
		int max_x;
		int max_y;
		string targv[100];
		int targc;

};

