#include "floorplan.h"

void GRAPH::SwapBlock(BLOCK *B1, BLOCK *B2){

	BLOCK *temp = new BLOCK("t",0,0);//new BLOCK* for swapping.

	temp->rightchild = B1->rightchild;//store B1.
	temp->leftchild = B1->leftchild;
	temp->parent = B1->parent;
	temp->is_left = B1->is_left;
	
	B1->rightchild = B2->rightchild;
	B1->leftchild = B2->leftchild;
	B1->parent = B2->parent;
	B1->is_left = B2->is_left;
	//update child & parent's informarion.
	//prevent from segmentation fault cause by NULL(parent or child).
	if(B1->rightchild != NULL)B1->rightchild->parent = B1;
	if(B1->leftchild != NULL)B1->leftchild->parent = B1;
	if((B1->is_left) && (B1->parent != NULL)) B1->parent->leftchild = B1;
	else if(B1->parent != NULL) B1->parent->rightchild = B1;

	B2->rightchild = temp->rightchild;
	B2->leftchild = temp->leftchild;
	B2->parent = temp->parent;
	B2->is_left = temp->is_left;
	//update child & parent's informarion.
	//prevent from segmentation fault cause by NULL(parent or child).
	if(B2->rightchild != NULL)B2->rightchild->parent = B2;
	if(B2->leftchild != NULL)B2->leftchild->parent = B2;
	if((B2->is_left) && (B2->parent != NULL)) B2->parent->leftchild = B2;
	else if(B2->parent != NULL) B2->parent->rightchild = B2;

}

void GRAPH::RotateBlock(BLOCK *B){
	
	int temp = B->GetW();
	B->WriteW(B->GetH());
	B->WriteH(temp);

}

void GRAPH::DeleteBlock(BLOCK *B1, BLOCK *B2){

	if(B1->is_left) B1->parent->leftchild = NULL;
	else B1->parent->rightchild = NULL;
	
	if(B2->leftchild == NULL){
			
		B2->leftchild = B1;
		B1->parent = B2;
		B1->is_left = 1;

	}
	else{	
		
		B2->rightchild = B1;
		B1->parent = B2;
		B1->is_left = 0;

	}
}

void GRAPH::RandomOperation(){
	
	int size = AllBlock.size();
	
	int operation = rand()%3;/*random */
	int b1 = rand()%size;/*random */
	int b2 = rand()%size;/*random */
	

	switch(operation){
		case 0:
			
			//if adjacent, skip the operation.
			while((AllBlock[b1]->parent == AllBlock[b2])\
					||(AllBlock[b2]->parent == AllBlock[b1])\
					||(b1 == b2)||(AllBlock[b1] == root)||(AllBlock[b2] == root)){
			
				b1 = rand()%size;/*re-random */
				b2 = rand()%size;/*re-random */
			
			}
			SwapBlock(AllBlock[b1],AllBlock[b2]);
			break;	
		
		case 1:
			RotateBlock(AllBlock[b1]);   
			break;
		case 2:
			//if b1 = root or b2 is not leaf, random again.
			 while((AllBlock[b1] == root) \
					 || ((AllBlock[b1]->rightchild != NULL) \
						 || (AllBlock[b1]->leftchild != NULL)))
				b1 = rand()%size;/*re-random */
			 while((b1 == b2)\
					 ||((AllBlock[b2]->rightchild != NULL)\
					 &&(AllBlock[b2]->leftchild !=NULL)))
				b2 = rand()%size;/*re-random */

			DeleteBlock(AllBlock[b1],AllBlock[b2]);
			break;
			
	}
}

bool GRAPH::UpdateCost(double t){

	current_cost =pow((max_x - boundry_x),2) + pow((max_y - boundry_y),2);

	if (current_cost < best_cost){
		best_cost = current_cost;
		StoreResult();
		last_cost = current_cost;
		return 1;
	}
	else if (MoveOnPossibility(t) < 0.6){
		LoadResult();	
	//	Traversal(root);//reverse the x,y coordinate.
		last_cost = best_cost;
		return 0;
	}
	else{ 
		last_cost = current_cost;
		return 1;
	}

}

bool GRAPH::AreaLegality(){

	if(max_x > boundry_x) return 0;
	if(max_y > boundry_y) return 0;
	return 1;

}

double GRAPH::MoveOnPossibility(double t){

	if(current_cost - last_cost <= 0){
		possibility = 1;
		return possibility;
	}
	else {
		possibility = pow(2.71,(last_cost - current_cost)/t);
		return possibility;
	}

}
