#include "floorplan.h"


void GRAPH::ParseLine(const string& line){
	for(int i=0; i < 100; ++i){
		targv[i].clear();
	}
	if(!line.empty()){
		targc = 1;
		bool flag = 0;
		for(auto pos = line.begin(), end = line.end(); pos != end; ++pos){
			if(*pos <= ' '){
				if(flag){
					targc++;
					flag = 0;
				}
				continue;
			}
			targv[targc-1].push_back(*pos);
			flag = 1;
		}
	}
	else{
		targc = 0;
	}
}

void GRAPH::BlockParser(string BlockFile){

	ifstream BF;
	string line;
	BF.open(BlockFile);

	int flag = 0;
	while(!BF.eof()&&!BF.bad()){

		getline(BF,line);
		ParseLine(line);
		if (targc == 5 ) flag = 3;//jump to case 3.
		switch(flag){

			case 0:{

					   if (targv[0][0]=='O'){
						   boundry_x = stoi(targv[1]);
						   boundry_y = stoi(targv[2]);
						   contour.resize(2*boundry_x);
						   ++flag ;
					   }

				   }
				   break;

			case 1:{ 

					   if(targv[0][3] == 'B'){	
						   int b = stoi(targv[1]);
						   AllBlock.reserve(b);
					   }
					   else if(targv[0][3] == 'T'){
						   int t = stoi(targv[1]);
						   AllTerminal.reserve(t);
						   ++flag ;
					   }	

				   }
				   break;

			case 2:{

					   if (targc == 1)break;
					   int w = stoi(targv[1]);
					   int h = stoi(targv[2]);
					   BLOCK *bl = new BLOCK(targv[0],w,h);
					   AllBlock.push_back(bl);

				   }
				   break;

			case 3:{

					   if(targc <= 1)break;
					   int x = stoi(targv[2]);
					   int y = stoi(targv[3]);
					   TERMINAL *tm = new TERMINAL(targv[0],x,y);
					   AllTerminal.push_back(tm);

				   }
				   break;
		}
		
	}
	BF.close();
}

void GRAPH::NetParser(string NetFile){
	
	ifstream NF;
	string line;
	NF.open(NetFile);
	int net_num = 0;		

	if(!NF.eof()&&!NF.bad()){//first line of .net.
		getline(NF,line);
		ParseLine(line);
		net_num = stoi(targv[1]);		
		AllNet.resize(net_num);
	}
	for(int i = 0; i < net_num; ++i){
	
		getline(NF,line);
		ParseLine(line);
		int net_degree = stoi(targv[1]);

		for(int j = 0; j< net_degree; ++j){	
			getline(NF,line);
			ParseLine(line);
			AllNet[i].push_back(targv[0]);
		}
	}

	NF.close();

}
