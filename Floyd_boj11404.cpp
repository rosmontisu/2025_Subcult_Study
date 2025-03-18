#include <iostream>
using namespace std;

const int INF = 987654321;
int map[105][105];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n; 
	cin >> m;

	// 그래프 최단 거리 초기화
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = INF;

	// 그래프 입력
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		map[a][b] = min(map[a][b], c); // 더 짧은 거리로 갱신
	}

	// 플로이드 알고리즘
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (i == j) continue; // 출발지와 도착지가 같다면 패스

				// 직통이 경유보다 비싸다면 갱신
				// (출발지->목적지) > (출발지->경유지) + (경유지->목적지)
				if (map[i][j] > map[i][k] + map[k][j])
					map[i][j] = map[i][k] + map[k][j];
			}
		}
	}

	// 정답 출력
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (map[i][j] == INF) cout << '0' << ' ';
			else cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}
