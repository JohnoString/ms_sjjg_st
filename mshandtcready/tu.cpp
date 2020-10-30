// 创建图:将抽象数据结构具象为数组存储数据
#if 0
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;

queue<char> q;
#define MVNum 7			
int visited[MVNum];

typedef struct AMGraph
{
	int vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;

int LocateVex(AMGraph& G, char v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)
			return i;
}

int CreateUDG_1(AMGraph& G)
{
	int i, j, k;
	int v1, v2;
	cout << "输入顶点个数跟边数" << endl;
	scanf_s("%d%d", &G.vexnum, &G.arcnum);

	cout << "初始化顶点" << endl;
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;

	cout << "初始化边, 不能重复" << endl;
	for (k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j] = G.arcs[j][i] = 1;
	}

	return 1;
}

// 邻接矩阵广度优先遍历连通图
void BFS_AM(AMGraph& G, char v0)
{

	int u, i, v, w;
	v = LocateVex(G, v0);
	printf("%d ", v0);
	visited[v] = 1;
	q.push(v0);

	while (!q.empty())
	{
		u = q.front();
		v = LocateVex(G, u);
		q.pop();
		for (i = 0; i < G.vexnum; i++)
		{
			w = G.vexs[i];
			if (G.arcs[v][i] && !visited[i])
			{
				printf("%d ", w);
				q.push(w);
				visited[i] = 1;
			}
		}
	}
}

/*广度优先搜索非连通图*/
void BFSTraverse(AMGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;							//将visited数组初始化
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v]) BFS_AM(G, G.vexs[v]);	                        //对尚未访问的顶点调用BFS
}

// 邻接矩阵深度优先遍历
void DFS_AM(AMGraph& G, int v)
{
	int w;
	printf("%d ", G.vexs[v]);
	visited[v] = 1;
	for (w = 0; w < G.vexnum; w++)
		if (G.arcs[v][w] && !visited[w]) //递归调用
			DFS_AM(G, w);
}

// 最小生成树


int main()
{
	AMGraph amG;
	if (CreateUDG_1(amG))
	{
		BFS_AM(amG, 1); // 第二个参数指的是顶点值
	}

	cout << endl;

	DFS_AM(amG, 1); // 第二个参数指的是下标
	return 0;
}

#endif