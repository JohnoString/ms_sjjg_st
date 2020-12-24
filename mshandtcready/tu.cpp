// ����ͼ_�ڽӾ���
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
	cout << "���붥�����������" << endl;
	scanf_s("%d%d", &G.vexnum, &G.arcnum);

	cout << "��ʼ������" << endl;
	for (i = 0; i < G.vexnum; i++)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;

	cout << "��ʼ����, �����ظ�" << endl;
	for (k = 0; k < G.arcnum; k++)
	{
		scanf_s("%d%d", &v1, &v2);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j] = G.arcs[j][i] = 1;
	}

	return 1;
}

// �ڽӾ��������ȱ�����ͨͼ
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

/*���������������ͨͼ*/
void BFSTraverse(AMGraph G)
{
	int v;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = 0;							//��visited�����ʼ��
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v]) BFS_AM(G, G.vexs[v]);	                        //����δ���ʵĶ������BFS
}

// �ڽӾ���������ȱ���
void DFS_AM(AMGraph& G, int v)
{
	int w;
	printf("%d ", G.vexs[v]);
	visited[v] = 1;
	for (w = 0; w < G.vexnum; w++)
		if (G.arcs[v][w] && !visited[w]) //�ݹ����
			DFS_AM(G, w);
}

// ��С������


int main()
{
	AMGraph amG;
	if (CreateUDG_1(amG))
	{
		BFS_AM(amG, 1); // �ڶ�������ָ���Ƕ���ֵ
	}

	cout << endl;

	DFS_AM(amG, 1); // �ڶ�������ָ�����±�
	return 0;
}

#endif

// ͼ��������_�ڽӱ�
#if 0
#include <iostream>
#include <vector>
using namespace std;

#define MAX_SIZE 100

// ��ڵ�
//template <class InfoData>
struct EdgeNode
{
	//InfoData info;   // �ߵ�Ȩֵ
	uint32_t pos;
	EdgeNode* next;
};

// ͷ�ڵ�
template <class VexData>
struct VexNode
{
	VexData data;
	EdgeNode* next;
};

template <class VexData>
class Graph
{
public:
	Graph(uint32_t vex_num, uint32_t edge_num, bool direct = false) :vex_num_(vex_num), edge_num_(edge_num), direct_(direct) 
	{
		memset(&adjlist_, 0, sizeof(adjlist_)); 
	}

	bool CreateGraph();
	bool Print();

	// ������ȱ���
	bool BfsTravel();
	
	// ������ȱ���
	bool DfsTravel();
	bool Destory();

private:
	void DFS(uint32_t pos);
	void BFS(uint32_t pos);

private:
	VexNode<VexData> adjlist_[MAX_SIZE];
	uint32_t vex_num_;
	uint32_t edge_num_;
	bool direct_;
};

template <class VexData>
bool Graph<VexData>::CreateGraph()
{
	if (vex_num_ <= 0 || edge_num_ <= 0)
	{
		return false;
	}

	// ���������
	cout << "�����붥��" << endl;
	for (uint32_t i = 0; i < vex_num_; ++i)
	{
		cin >> adjlist_[i].data;
		adjlist_[i].next = nullptr;
	}

	// �����߱�
	uint32_t va, vb;
	EdgeNode* pnode = nullptr;
	for (uint32_t j = 0; j < edge_num_; ++j)
	{
		cout << "�������������������±�, ��Ҫ����������������" << endl;
		cin >> va >> vb;
		pnode = new EdgeNode;
		pnode->pos = vb;
		pnode->next = adjlist_[va].next;
		adjlist_[va].next = pnode;

		if (!direct_)   // ����ͼ
		{
			pnode = new EdgeNode;
			pnode->pos = va;
			pnode->next = adjlist_[vb].next;
			adjlist_[vb].next = pnode;
		}
	}

	return true;
}

template <class VexData>
bool Graph<VexData>::Print()
{
	uint32_t i, j;
	EdgeNode* pnode = nullptr;
	for (i = 0; i < vex_num_; i++)
	{
		cout << i << "->";
		pnode = adjlist_[i].next;
		while (1)
		{
			if (pnode == nullptr)
			{
				cout << "^";
				break;
			}

			cout << pnode->pos << "->";
			pnode = pnode->next;
		}
		cout << endl;
	}
	return true;
}

#include <queue>
uint32_t visit_b[MAX_SIZE] = { 0 };
template <class VexData>
void Graph<VexData>::BFS(uint32_t pos)
{
	if (pos < 0 || pos >= vex_num_ || adjlist_ == nullptr)
	{
		return;
	}

	EdgeNode* pnode = nullptr;

	queue<uint32_t> vexque;
	vexque.push(pos);
	cout << "visit->" << adjlist_[pos].data << " ";
	visit_b[pos] = 1;
	while (!vexque.empty())
	{
		uint32_t sub_pos = vexque.front();
		vexque.pop();
		pnode = adjlist_[sub_pos].next;

		while (pnode != nullptr)
		{
			if (!visit_b[pnode->pos])
			{
				vexque.push(pnode->pos);
				cout << "visit->" << adjlist_[pnode->pos].data << " ";
				visit_b[pnode->pos] = 1;
			}

			pnode = pnode->next;
		}
	}
	cout << endl;
}

// ������ȱ���
template <class VexData>
bool Graph<VexData>::BfsTravel()
{
	cout << "������ȱ���˳��Ϊ��" << endl;
	for (uint32_t i = 0; i < vex_num_; ++i)
	{
		if (!visit_b[i])
		{
			BFS(i);
		}
	}

	return true;
}

uint32_t visit[MAX_SIZE] = {0};
template <class VexData>
void Graph<VexData>::DFS(uint32_t pos)
{
	EdgeNode* pnode = nullptr;
	if (pos < 0 || pos >= vex_num_)
	{
		return;
	}
	else
	{
		visit[pos] = 1;
		cout << "visit:" << adjlist_[pos].data << " ";
		pnode = adjlist_[pos].next;

		while (pnode)
		{
			if (visit[pnode->pos] != 1)
				DFS(pnode->pos);
			pnode = pnode->next;
		}
	}

	cout << endl;
}

// ������ȱ���
template <class VexData>
bool Graph<VexData>::DfsTravel()
{
	cout << "������ȱ���˳��Ϊ��" << endl;
	for (uint32_t i = 0; i < vex_num_; ++i)
	{
		if (!visit[i])
		{
			DFS(i);
		}
	}

	return true;
}

template <class VexData>
bool Graph<VexData>::Destory()
{

}

int main()
{
	Graph<uint32_t> g(8, 9, false);
	g.CreateGraph();
	g.Print();
	g.DfsTravel();
	g.BfsTravel();
	return 0;
}
#endif