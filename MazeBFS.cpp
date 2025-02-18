#include <iostream>
#include <queue>
#include <windows.h>
#include <conio.h>

using namespace std;

#define X first
#define Y second

enum Tile { WALL, PATH, VISITED, START, END };
const int mazeSize = 10;

// 콘솔 색상 설정
void SetColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 미로 초기화 (수동, 생성 알고리즘 미구현)
Tile maze[mazeSize][mazeSize] = 
{
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, PATH, PATH, WALL, PATH, PATH, PATH, PATH, PATH, WALL},
    {WALL, WALL, PATH, WALL, PATH, WALL, WALL, PATH, WALL, WALL},
    {WALL, PATH, PATH, PATH, PATH, WALL, PATH, PATH, PATH, WALL},
    {WALL, PATH, WALL, WALL, WALL, WALL, WALL, WALL, PATH, WALL},
    {WALL, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, WALL},
    {WALL, WALL, WALL, PATH, WALL, WALL, WALL, WALL, PATH, WALL},
    {WALL, PATH, PATH, PATH, WALL, PATH, PATH, PATH, PATH, WALL},
    {WALL, PATH, WALL, PATH, PATH, PATH, WALL, WALL, PATH, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
};

pair<int, int> startPos = { 1, 1 };  // 시작 좌표
pair<int, int> endPos = { 8, 8 };    // 종료 좌표

// 미로 출력
void PrintMaze(bool isVisited[mazeSize][mazeSize]) 
{
    system("cls"); // 화면 지우기

    for (int i = 0; i < mazeSize; i++) 
    {
        for (int j = 0; j < mazeSize; j++) 
        {
            if (i == startPos.X && j == startPos.Y) 
            {
                SetColor(12); // 시작점 빨강
                cout << "S ";
            }
            else if (i == endPos.X && j == endPos.Y) 
            {
                SetColor(12); // 종료점 빨강
                cout << "E ";
            }
            else if (isVisited[i][j]) 
            {
                SetColor(12); // 방문한곳 빨강
                cout << "* ";
            }
            else if (maze[i][j] == WALL) 
            {
                SetColor(10); // 벽 초록
                cout << "■";
            }
            else 
            {
                SetColor(15); // 길 흰색
                cout << "  ";
            }
        }
        cout << '\n';
    }
    SetColor(15); // 색상 리셋
}

// BFS 탐색 함수
void BFS() 
{
    bool visited[mazeSize][mazeSize] = { false };
    queue<pair<int, int>> q;
    q.push(startPos);
    visited[startPos.first][startPos.Y] = true;

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };

    while (!q.empty()) 
    {
        int size = q.size();
        for (int i = 0; i < size; i++) 
        {
            pair<int, int> current = q.front();
            q.pop();

            // 종료 지점 도달 시
            if (current == endPos) 
            {
                PrintMaze(visited);
                cout << "\n탐색 성공\n\n";
                return;
            }

            // 4방향 탐색
            for (int dir = 0; dir < 4; dir++) 
            {
                int nx = current.X + dx[dir];
                int ny = current.Y + dy[dir];

                if (nx < 0 || nx >= mazeSize || ny < 0 || ny >= mazeSize) continue;
                if (visited[nx][ny] || maze[nx][ny] == WALL) continue;

                visited[nx][ny] = true;
                q.push({ nx, ny });
            }
        }
        PrintMaze(visited);
        Sleep(500); // 0.5초 대기
    }
    cout << "\n탐색 실패\n\n";
}

int main() 
{
    cout << "2차원 배열로 생성한 미로에서 BFS를 시각적으로 보여줍니다.\n";
    cout << "출발지 S -> 도착지 E\n";
    cout << "키 입력으로 시작\n";
    _getch();

    BFS();
    return 0;
}
