/*
 * tree_headers.h
 *
 *  Created on: Jul 30, 2022
 *      Author: gg
 */

#ifndef TREE_HEADERS_H_
#define TREE_HEADERS_H_

#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned int uit;

typedef struct TreeNode{
	TreeNode* left = NULL;
	TreeNode* parent = NULL;
	TreeNode* right = NULL;
	uit hash_val = 0;
	uint data = 0;
}Tree;

class MKTree{
private:
	int tar = 0;
public:
	uit hash_cal(char* k);
	uit dou_cal(uit n1, uit n2);
	Tree* find_node(Tree* rt);
	Tree* find_room(Tree* rt);
	uint hash_int(int num);
	void add_node(Tree* rt, int depth);
	void print_tree_val(Tree* rt, int height);
	Tree* create_tree(Tree* rt, int num, int depth, int* arr);
};

void MKTree:: print_tree_val(Tree* rt, int height){
	Tree* p = rt;
	int i, tmp;
	if(p == NULL)return;
	if(p->left == NULL && p->right == NULL){
		cout<<"\n";
		tmp = height - p->hash_val;
		for(i = 0; i < tmp; i ++){
			cout<<"   ";
		}
		cout<<"---->"<<p->data;
		return;
	}
	else{
		print_tree_val(rt->left, height);
		if(tar == 1){
			tmp = height - p->hash_val;
			for(i = 0; i < tmp; i ++){
				cout<<"    ";
			}
			cout<<"---->";
		}
		else{
			cout<<"---->";
			tar = 0;
		}
		print_tree_val(rt->right, height);
	}
}

uit MKTree:: hash_cal(char* k){
	uit cal = 11, hash = 0;
	while(*k != '\0' && *k != 0){
		hash = hash * cal + *k;
		k ++;
	}
	return hash & 0x7FFFFFFF;
}

uint MKTree:: hash_int(int num){
	uint cal = 11, hash = 0;

	hash = num * cal;
	return hash & 0x7FFFFFFF;
}

uit MKTree:: dou_cal(uit n1, uit n2){
	uit cal = 9, hash = 0;
	hash = n1 + n2;
	hash *= cal;
	return hash & 0x7FFFFFFF;
}

Tree* MKTree:: find_node(Tree* rt){
	Tree* p = rt;
	if(p->left == NULL && p->right == NULL)
		return p;
	else if(p->right== NULL && p->left != NULL)
		return find_node(p->left);
	else if(p->right!= NULL)
		return find_node(p->right);
	else
		return NULL;
}

Tree* MKTree:: find_room(Tree* rt){
	Tree* p = rt->parent;
	while(p->left != NULL && p->right != NULL && p->parent != NULL){
		p = p->parent;
	}
	if(p->parent == NULL && p->left != NULL && p->right != NULL){
		return NULL;
	}
	else
		return p;
}

void MKTree:: add_node(Tree* rt, int depth){
	if(rt->hash_val == 0){
		rt->hash_val = 0;
	}
	else if(rt->hash_val == 1){
		rt->hash_val = dou_cal(hash_int(rt->left->data), hash_int(rt->right->data));
	}
	else{
		add_node(rt->left, depth-1);
		add_node(rt->right, depth-1);
		rt->hash_val = dou_cal(rt->left->hash_val, rt->right->hash_val);
	}
}

Tree* MKTree:: create_tree(Tree* rt, int num, int depth, int* arr){
	Tree* p,*tmp, *p2;
	int i;
	if(num == 0){
		cout<<"over"<<endl;
		if(rt != NULL){
			tar = 0;
			print_tree_val(rt, rt->hash_val);
		}
		return rt;
	}
	else{
		add_node(p2, 0);
		p2->data = *arr;
		if(rt == NULL){
			add_node(rt, 1);
			rt->left = p2;
			p2->parent = rt;
			depth ++;
			rt = create_tree(rt, num - 1, depth, arr + 1);
		}
		else{
			p = find_room(find_node(rt));
			if(p != NULL){
				if(p ->left->hash_val == 0 && p->right == NULL){
					p->right = p2;
					p2->parent = p;
				}
				else{
					i = p->hash_val - 1;
					add_node(tmp, i);
					p->right = tmp;
					tmp->parent = p;
					p ->left->hash_val = 0;
					p = p->right;
					i --;
					while(i > 0){
						add_node(tmp, i);
						p->left = tmp;
						tmp->parent = p;
						p = p->left;
						i --;
					}
					p->left = p2;
					p2->parent = p;
				}
				rt = create_tree(rt, num - 1, depth, arr + 1);
			}
			else{
				tmp = rt;
				depth ++;
				add_node(rt, depth);
				rt->left = tmp;
				tmp->parent = rt;
				i = depth - 1;
				add_node(tmp, i);
				rt->right = tmp;
				tmp->parent = rt;
				i --;
				p = rt->right;
				while(i > 0){
					add_node(tmp, i);
					p->left = tmp;
					tmp->parent = p;
					p = p->left;
					i--;
				}
				p->left = p2;
				p2->parent = p;
				rt = create_tree(rt, num - 1, depth,  arr + 1);
				//}
			}
		}
	}
	return rt;
}


#endif /* TREE_HEADERS_H_ */
