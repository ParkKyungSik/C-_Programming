#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 100;
// 그래프의 인접 행렬 표현
// D[u][v] = u 에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다.
int D[MAX][MAX];

// P[u][v] = u에서 v까지 가는 최단 경로가 경유하는 점 중 가장 번호가 큰 정점
int P[MAX][MAX];

// 정점의 개수
int V;

// 플로이드의 모든 쌍 최단 거리 알고리즘
void folyd2()
{

	for (int i = 0; i < V; ++i)
		D[i][i] = 0;
	memset(P, -1, sizeof(P));

	for(int k=0; k<V; ++k)
		for(int i=0; i<V; ++i)
			for (int j = 0; j < V; ++j)
			{
				if (D[i][j] > D[i][k] + D[k][j]) 
                {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
			}
}

void reconstruct(int u, int v, vector<int>& path)
{

	if (P[u][v] == -1)
	{
		path.push_back(u);
		if (u != v) path.push_back(v);
	}

	else
	{
		int w = P[u][v];
		reconstruct(u, w, path);
		// w 가 중복으로 들어가므로 지운다.
		path.pop_back();
		reconstruct(w, v, path);
	}
}

int main()
{
    int a, b;

	cin >> V;

	cout << " folyd2() 알고리즘 수행 전 " << endl;

	cout << endl;

	for(int i=0; i<V; ++i)
		for (int j = 0; j < V; ++j)
		{
			cin >> D[i][j];
		}

	folyd2();

	cout << endl;

	cout << " folyd2() 알고리즘 수행 후 " << endl;

	cout << endl;

	for (int i = 0; i < V; ++i)
    {
		for (int j = 0; j < V; ++j)
			cout << D[i][j] << " ";
		cout << endl;
	}

	cout << endl;

	vector<int> path;

    cin >> a >> b;

    cout << endl;

	reconstruct(a-1, b-1, path);

	for (int i = 0; i < path.size(); ++i)
		cout << path[i]+1 << " ";
	cout << endl;

	return 0;
}
