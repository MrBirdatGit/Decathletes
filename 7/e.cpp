#include<bits/stdc++.h>
using namespace std;
int mat[25][7][7];
int conn[2][7][7][4];
int M[2][7][7];
int ok[2][8][8];
int s[2][2], t[2][2];
int nextx[4]  = {1, 0, 0, -1};
int nexty[4]  = {0, -1, 1, 0};
char cc[4] = {'D', 'L','R', 'U'};
void init(int m){
	for(int i = 1;i<=6;i++){
		for(int j = 1;j<=6;j++){
			if(M[m][i][j] & (1<<1)) conn[m][i][j][0] = 1;
			else conn[m][i][j][0] = 0;
			if(M[m][i][j] & (1<<0)) conn[m][i][j][1] = 1;
			else conn[m][i][j][1] = 0;
			if(M[m][i][j] & (1<<2)) conn[m][i][j][2] = 1;
			else conn[m][i][j][2] = 0;
			if(M[m][i][j] & (1<<3)) conn[m][i][j][3] = 1;
			else conn[m][i][j][3] = 0;
			if(M[m][i][j] & (1<<4)) ok[m][i][j] = 1;
			else ok[m][i][j] = 0;
			if(M[m][i][j] & (1<<5)){
				s[m][0] = i;
				s[m][1] = j;
			}
			if(M[m][i][j] & (1<<6)){
				t[m][0] = i;
				t[m][1] = j;
			}
		}
	}
}
struct node{
	int x0, y0, x1, y1, step;
	string s;
	node(){
    }
	node(int x0, int y0, int x1, int y1):x0(x0), y0(y0), x1(x1), y1(y1){
        step = 0;
        string s = "";
    }
	void seti(int x0, int y0, int x1, int y1){
		this->x0 = x0;
		this->y0 = y0;
		this->x1=  x1;
		this->y1 = y1;
        step = 0;
        string s = "";
	}
    void print(){
        cout<<x0<<' '<<y0<<' '<<x1<<' '<<y1<<' '<<step<<' '<<s<<endl;
    }
};
bool visited[7][7][7][7];
bool bfs(){
	queue<node>que;
	que.push(node(s[0][0],s[0][1], s[1][0], s[1][1]));
	memset(visited, 0, sizeof(visited));
	que.front().s ="";que.front().step = 0;
	node nnd;
	while(!que.empty()){
		node nd = que.front();que.pop();
		if(nd.x0 == t[0][0] && nd.y0 == t[0][1] && nd.x1 == t[1][0] && nd.y1 == t[1][1]){
            cout<<nd.s<<endl;
            return 1;
		}
		for(int i = 0;i<4;i++){
            int tx0,ty0,tx1,ty1;
			if(conn[0][nd.x0][nd.y0][i] == 0){
                tx0 = nd.x0 + nextx[i];
			    ty0 = nd.y0 + nexty[i];
            }else{
                tx0 = nd.x0;
                ty0 = nd.y0;
            }
            if(conn[1][nd.x1][nd.y1][i] == 0){
                tx1 = nd.x1 + nextx[i];
                ty1 = nd.y1 + nexty[i];
            }else{
                tx1 = nd.x1;
                ty1 = nd.y1;
            }
            if(ok[1][tx1][ty1] != 1 ||ok[0][tx0][ty0] != 1||visited[tx0][ty0][tx1][ty1])
				continue;
			visited[tx0][ty0][tx1][ty1] = 1;
			nnd.seti(tx0, ty0, tx1, ty1);
			nnd.s = nd.s + cc[i];
			nnd.step = nd.step + 1;
			que.push(nnd);
		}
	}
    return 0;
}
int main(){
    int T;
    for(int i = 0;i<=7;i++){
        ok[0][i][0] = ok[0][i][7] = ok[1][i][0] = ok[1][i][7] = -1;
        ok[0][0][i] = ok[0][7][i] = ok[1][0][i] = ok[1][7][i] = -1;
    
    }
	scanf("%d", &T);
	for(int cs = 0;cs<T;cs++){
		for(int i = 1;i<=6;i++)
			for(int j = 1;j<=6;j++)
				scanf("%d", &mat[cs][i][j]);
	}
	for(int cs = 1;cs<T;cs++){
		memcpy(M[0], mat[cs-1], sizeof(M[0]));
		memcpy(M[1], mat[cs], sizeof(M[1]));
		init(0);init(1);

		if(!bfs()){
            cout<<-1<<endl;
        }
	}
}