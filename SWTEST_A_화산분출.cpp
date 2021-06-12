

#include<iostream>
#include<queue>
#include<cstring>
#define p pair<int,int>
using namespace std;
int map[50][50];
int visit[50][50];
int n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
bool inRange(int x, int y){
	if (x == -1 || x == n || y == -1 || y == n)
		return false;
	else
		return true;
}
int main(){
	int TC;
	cin >> TC;

	for (int tc = 1; tc <= TC; tc++){
		memset(map, 0, sizeof(map));
		memset(visit, 0, sizeof(visit));
		cin >> n;

		int vol = -1;
		int home = 2e9;

		p pos_vol;
		p pos_home;

		for (int i = 0; i<n; i++){
			for (int j = 0; j<n; j++){
				scanf("%d", &map[i][j]);
				if (vol < map[i][j]){
					vol = map[i][j];
					pos_vol = { i, j };
				}
				if (home > map[i][j]){
					home = map[i][j];
					pos_home = { i, j };
				}
			}
		}

		queue<p> q;
		q.push(pos_vol);

		int time = 0;
		int size;

		while (time <1000 && !visit[pos_home.first][pos_home.second]) {
			time++;
			size = (int)q.size();

			vector<p> _v;
			for (int i = 0; i<size; i++){
				int x = q.front().first;
				int y = q.front().second;
				q.pop();
				if (visit[x][y]) continue;
				visit[x][y] = 1;

				bool flow = false;
				for (int j = 0; j<4; j++){
					int nx = x + dx[j];
					int ny = y + dy[j];

					if (map[x][y] > map[nx][ny] && !visit[nx][ny] && inRange(nx, ny)){
						flow = true;
						q.push({ nx, ny });
						if (nx == pos_home.first && ny == pos_home.second){
							visit[nx][ny] = 1;
						}
					}
				} // end of for j

				// 4�������� �� ���� �������ϱ� �� ++
				// �׸��� queue�� �ٽ� ����
				if (flow == false){
					_v.push_back({ x, y });
					map[x][y] ++;
					q.push({ x, y });
				}
			}// end of for i

			// �� ���⵵ ������ �� ++ �� �����ε�
			// while �ȿ� visit[x][y] = 1; �� �ڵ� ������
			// �̹� �湮�Ѱ�ó�� ó���߱� ������
			// �湮���� ���� ���·� �ʱ�ȭ
			for (int i = 0; i<_v.size(); i++){
				visit[_v[i].first][_v[i].second] = 0;
			}
			_v.clear();
		} // end of while
		printf("#%d %d\n", tc, time);
	}
	return 0;
}