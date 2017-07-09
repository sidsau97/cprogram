#include <stdio.h>
#include <stdlib.h>
#include "bisearchtree.h"
int main() {

	printf("begining...\n");
	BiSearchTree *searchTree;
	searchTree = bisearch_tree_new();
	searchTree = bisearch_tree_insert(searchTree, 19); // 第一次insert
	// warning: implicit declaration of function ‘exit’
	// too few arguments to function ‘exit’
//    exit(EXIT_SUCCESS);
	bisearch_tree_insert(searchTree, 3);
	bisearch_tree_insert(searchTree, 122);
	bisearch_tree_insert(searchTree, 55);
	bisearch_tree_insert(searchTree, 65);
	bisearch_tree_insert(searchTree, 65);
	bisearch_tree_insert(searchTree, 180);
	printf("inorder traversal\n");
	bisearch_tree_inorder_traversal(searchTree);
	//=======search ============================================
	printf("find node...\n");
	int find = 55;
	//  warning: implicit declaration of function ‘bisearch_tree_search_recursive’
	if (bisearch_tree_search_recursive(searchTree, find) < 0) {
		printf("node %d not exits\n", find);
	} else {
		printf("node %d exits\n", find);
	}

	find = 33;
	// @todo infinite while loop, check why ?
	if (bisearch_tree_search(searchTree, find) < 0) {
		printf("node %d not exits\n", find);
	} else {    //
		printf("node %d exits\n", find);
	}

//
	//====== delete,会影响到serachTree值，所以应该传递serachTree的指针 ======================================
	printf("delete node..\n");
	find = 4;
	if (bisearch_tree_delete(&searchTree, find) < 0) {
		printf("delete node %d failure\n", find);
	} else {
		printf("delete node %d success\n", find);
		bisearch_tree_inorder_traversal(searchTree);
		bisearch_tree_insert(searchTree, find);
	}
	exit(EXIT_SUCCESS);

	find = 65;    //叶子
	if (bisearch_tree_delete(&searchTree, find) < 0) {
		printf("delete node failure\n");
	} else {
		printf("delete node %d success\n", find);
		bisearch_tree_inorder_traversal(searchTree);
		bisearch_tree_insert(searchTree, find);
	}

	find = 55;    //单分支
	if (bisearch_tree_delete(&searchTree, find) < 0) {
		printf("delete node failure\n");
	} else {
		printf("delete node %d success\n ", find);
		bisearch_tree_inorder_traversal(searchTree);
		bisearch_tree_insert(searchTree, find);
	}

	find = 122;    //双分支
	if (bisearch_tree_delete(&searchTree, find) < 0) {
		printf("delete node failure\n");
	} else {
		printf("delete node %d success\n", find);
		bisearch_tree_inorder_traversal(searchTree);
		bisearch_tree_insert(searchTree, find);
	}

	return 0;
}
