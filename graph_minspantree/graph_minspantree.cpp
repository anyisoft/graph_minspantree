// graph_minspantree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

struct edge {
	int from;
	int to;
	int weight;
	struct edge *nextedge;
};

typedef struct edge *edgelist;
edgelist list = NULL;
int node[6];

#define	MAXVALUE	1000
int edgecost[6][6];

void creategraph(int *node, int num)
{
	int from, to, i;

	for (i = 0; i < num; i++) {
		from = node[i * 3];
		to = node[i * 3 + 1];
		edgecost[from][to] = node[i * 3 + 2];
	}
}

edgelist createdgelist(edgelist list, int *edges, int num)
{
	edgelist newnode;
	edgelist last = NULL;
	int i;

	for (i = 0; i < num; i++) {
		newnode = (edgelist)malloc(sizeof(struct edge));
		newnode->from = edges[3 * i];
		newnode->to = edges[3 * i+1];
		newnode->weight = edges[3 * i+2];
		newnode->nextedge = NULL;
		if (NULL == list) {
			list = newnode;
			last = list;
		}
		else {
			last->nextedge = newnode;
			last = newnode;
		}
	}

	return list;
}

/**
 * 结合成同一集合
 */
int uniongroup(int from, int to)
{
	int to_root;

	to_root = to;
	while (node[to_root] > 0) {
		to_root = node[to_root];
	}
	node[to_root] = from;

	return 0;
}

/**
 * 是否存在同一集合
 */
int samegroup(int from, int to)
{
	int from_root;
	int to_root;

	from_root = from;
	while (node[from_root] > 0) {
		from_root = node[from_root];
	}

	to_root = to;
	while (node[to_root] > 0) {
		to_root = node[to_root];
	}

	if (from_root == to_root) {
		return 1;
	}
	else {
		return 0;
	}
}

void minspantree()
{
	edgelist ptr;

	ptr = list;
	while (ptr != NULL) {
		if (!samegroup(ptr->from, ptr->to)) {
			printf("tree branch from vertex %d to %d, weight: %d\n", ptr->from, ptr->to, ptr->weight);
			uniongroup(ptr->from, ptr->to);
		}

		ptr = ptr->nextedge;
	}
}

/**
 * adjacent matrix
 */
void minspantree_am()
{
	int selected_edge_count = 0;
	int min_value = MAXVALUE;
	int from, to;

	while (selected_edge_count < 4) {
		min_value = MAXVALUE;
		for (int i = 1; i <= 5; i++) {
			for (int j = 1; j <= 5; j++) {
				if (edgecost[i][j] < min_value) {
					min_value = edgecost[i][j];
					from = i;
					to = j;
				}
			}
		}

		if (!samegroup(from, to)) {
			printf("tree branch from vertex %d to %d, weight: %d\n", from, to, edgecost[from][to]);
			uniongroup(from, to);
			edgecost[from][to] = MAXVALUE;
			selected_edge_count++;
		}
		else {
			edgecost[from][to] = MAXVALUE;
		}
	}
}

int main()
{
	int edges[8][3] = {
		{ 1, 2, 2 },
		{ 2, 4, 3 },
		{ 1, 4, 4 },
		{ 3, 5, 5 },
		{ 2, 5, 6 },
		{ 2, 3, 8 },
		{ 3, 4, 10 },
		{ 4, 5, 15 }
	};
	int i, j;

	//list = createdgelist(list, &edges[0][0], 8);
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			edgecost[i][j] = MAXVALUE;
		}
	}
	creategraph(&edges[0][0], 8);

	for (i = 1; i <= 5; i++) {
		node[i] = -1;
	}
	printf("graph's minspantree:\n");
	//minspantree();
	minspantree_am();
	printf("the vertexs array: ");
	for (i = 1; i <= 5; i++) {
		printf(" [%d] ", node[i]);
	}
	printf("\n");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
