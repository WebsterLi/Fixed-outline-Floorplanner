#include "floorplan.h"

void GRAPH::InitialTree(){
	
	sort(AllBlock.begin(), AllBlock.end(),\
			[](BLOCK* & B1, BLOCK* & B2 )->bool { return B1->GetArea() > B2->GetArea(); });

	int bound = 0;
	BLOCK* most_left_block;
	
	for(int i = 0; i < (int)AllBlock.size(); ++i){

		if(i == 0){	
			root = AllBlock[i];
			most_left_block = root;
		}
		else {
			
			bound = AllBlock[i-1]->EndX() + AllBlock[i]->GetW(); 
			
			if(bound <= boundry_x){
				AllBlock[i-1]->leftchild = AllBlock[i];
				AllBlock[i]->parent = AllBlock[i-1];
				AllBlock[i]->is_left = 1;
				AllBlock[i]->WriteX(AllBlock[i-1]->EndX());
			}
			else {
				most_left_block->rightchild = AllBlock[i];
				AllBlock[i]->parent = most_left_block;
				AllBlock[i]->is_left = 0;
				AllBlock[i]->WriteX(0);
				most_left_block = AllBlock[i];
			}
		}
	}
}

void GRAPH::Traversal(BLOCK *r){
	
	if(r == NULL)return;

	if(root == r){
		for(int i = 0; i < (int)contour.size(); ++i)contour[i] = 0;
		r->WriteX(0);
		r->WriteY(0);
		max_x = 0;
		max_y = 0;
	}	
	else{

		if(r->is_left) r->WriteX(r->parent->EndX());
		else r->WriteX(r->parent->GetX());
		
		int y_mark = 0;//Record the current contour.
		
		if(r->EndX() > (int)contour.size()) contour.resize(r->EndX());
		for(int i = r->GetX(); i < r->EndX(); ++i){
			if(contour[i] > y_mark)	y_mark = contour[i];
		}
		r->WriteY(y_mark);
		fill(contour.begin() + r->GetX(), contour.begin() + r->EndX(), y_mark + r->GetH());//Update contour.

	}
	if(r->EndX() > max_x)max_x = r->EndX();
	if(r->GetY() + r->GetH() > max_y)max_y = r->GetY() + r->GetH();
	if(r->leftchild != NULL)Traversal(r->leftchild);
	if(r->rightchild != NULL)Traversal(r->rightchild);
	
}

void GRAPH::StoreResult(){

	last_root = root; 

	for(auto iter : AllBlock){
		
		iter->BackupW();
		iter->BackupH();
		iter->last_is_left = iter->is_left;
		iter->last_leftchild = iter->leftchild;
		iter->last_rightchild = iter->rightchild;
		iter->last_parent = iter->parent;
		if(iter->leftchild != NULL){
			iter->leftchild->last_parent = iter;
			iter->leftchild->last_is_left = 1;
		}
		if(iter->rightchild != NULL){
			iter->rightchild->last_parent = iter;
			iter->rightchild->last_is_left = 0;
		}
		if(iter->parent != NULL){
			if(iter->is_left)iter->parent->last_leftchild = iter;
			else iter->parent->rightchild = iter;
		}

	}

}

void GRAPH::LoadResult(){
	
	root = last_root; 

	for(auto iter : AllBlock){

		iter->RestoreW();
		iter->RestoreH();
		iter->is_left = iter->last_is_left;
		iter->leftchild = iter->last_leftchild;
		iter->rightchild = iter->last_rightchild;
		iter->parent = iter->last_parent;
		if(iter->last_leftchild != NULL){
			iter->last_leftchild->parent = iter;
			iter->last_leftchild->is_left = 1;
		}
		if(iter->last_rightchild != NULL){
			iter->last_rightchild->parent = iter;
			iter->last_rightchild->is_left = 0;
		}
		if(iter->last_parent != NULL){
			if(iter->last_is_left)iter->last_parent->leftchild = iter;
			else iter->last_parent->rightchild = iter;
		}

	}

}

void GRAPH::ReleasePointer(){

	for(auto AB : AllBlock)delete AB;	
	for(auto AT : AllTerminal)delete AT;	

}

