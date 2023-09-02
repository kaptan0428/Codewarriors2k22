#include <bits/stdc++.h>
using namespace std;
int n, m;
const int INF=1e9;
vector<vector<int>> adj;
vector<vector<pair<int, int>>> playerPos;
vector<int> lastCoin;
int player,opponent;
int finalMove;
int maxDepth=4;
// clock_t start;
// clock_t finish;
// double timelimit = .9;
int heuristiclimit = 3;
int maxdis1 = 0;
int maxdis2 = 0;
int score_atmax;
int score_at_secondmax;

vector<pair<int,int>> moves {{1,0} , {-1,0} , {0,1} , {0,-1}};

bool isFree(int x,int y)
{
    for(int i=1;i<=2;i++)
        for(int j=1;j<=3;j++)
            if(playerPos[i][j].first==x && playerPos[i][j].second==y )
                return false;
    if (x < 0 || y < 0 || x >= n || y >= m )
        return false;
    if(adj[x][y]==3)
        return false;
    return true;
}

int coinscore(int x,int y){
    int score = 0;
    for(int j=0;j<4;j++){
        int nx = x + moves[j].first;
        int ny = y + moves[j].second;
        if(!isFree(nx , ny)) continue;
        score += (3 - adj[nx][ny]);
    }
    return score;
}

void findpath(int x,int y,int len){
    if(len > maxdis1){
        maxdis2 = maxdis1;
        maxdis1 = len;
        score_atmax = coinscore(x , y);
    }
    else if(len < maxdis1){
        maxdis2 = max(maxdis2 , len);
        score_at_secondmax = coinscore(x,y);
    }
    else{
        maxdis2 = maxdis1;
        int temp = coinscore(x,y);
        score_atmax = max(score_atmax , temp);
        score_at_secondmax = max(score_at_secondmax , temp);
    }

    if(len == heuristiclimit) return;

    for(auto it:moves){
        int i = x + it.first;
        int j = y + it.second;
        if(isFree(i,j)){
            adj[x][y]--;
            findpath(i,j,len+1);
            adj[x][y]++;
        }
    }
}


int heuristic(){
    int scr = 0;
    for(int i=1;i<=3;i++){
        maxdis1 = 0;
        maxdis2 = 0;
        score_atmax = 0;
        score_at_secondmax = 0;
        int temp = coinscore(playerPos[player][i].first , playerPos[player][i].second);
        findpath(playerPos[player][i].first, playerPos[player][i].second, 0);
        scr += (maxdis1*maxdis1*score_atmax);
        scr += (maxdis2*score_at_secondmax);
        scr += temp * temp;
    }
    for(int i=1;i<=3;i++){
        maxdis1 = 0;
        maxdis2 = 0;
        score_atmax = 0;
        score_at_secondmax = 0;
        int temp = coinscore(playerPos[opponent][i].first , playerPos[opponent][i].second);
        findpath(playerPos[opponent][i].first,playerPos[opponent][i].second,0);
        scr -= (maxdis1*maxdis1*score_atmax);
        scr -= (maxdis2*score_at_secondmax);
        scr -= temp * temp;
    }
    return scr;
}

// int setChoice(int bestVal,int minMax,vector<int>& choice, int &coin_no,int x,int y,int coin){
//     if(minMax>=bestVal){
//         choice[0]=x,choice[1]=y,coin_no=coin;
//         return minMax;
//     }
//     return bestVal;
// }

int minMax(int depth , int maxTurn , int alpha , int beta){
    if(depth==maxDepth)
        return heuristic(); 
    int bestVal,oldLastCoin;
    if(maxTurn){
        bestVal=-INF;
        for(int coin=1;coin<=3;coin++){
            if(coin!=lastCoin[player]){
                for (int i = 0; i < 4; i++){
                    int x=playerPos[player][coin].first, y=playerPos[player][coin].second;
                    int nx = x + moves[i].first, ny = y + moves[i].second;

                    if(isFree(nx,ny)){
                        oldLastCoin=lastCoin[player];
                        lastCoin[player]=coin;
                        adj[x][y]+=1;
                        playerPos[player][coin].first=nx;
                        playerPos[player][coin].second=ny;
                        bestVal=max(bestVal,minMax(depth+1,!maxTurn,alpha,beta));
                        //pruning
                        alpha = max(alpha , bestVal);
                        lastCoin[player]=oldLastCoin;
                        adj[x][y]-=1;
                        playerPos[player][coin].first=x;
                        playerPos[player][coin].second=y;
                        if(alpha >= beta) return bestVal;

                        // finish = clock();
                        // //checking if the program didnt run out of time at this depth
                        // if(double(finish - start)/CLOCKS_PER_SEC > timelimit){
                        //     return bestVal;
                        // }
                    }
                }
            }
        }
    }
    else{
        bestVal=+INF;
        for(int coin=1;coin<=3;coin++){
            if(coin!=lastCoin[opponent]){
                for (int i = 0; i < 4; i++){
                    int x=playerPos[opponent][coin].first, y=playerPos[opponent][coin].second;
                    int nx = x + moves[i].first, ny = y + moves[i].second;
                    if(isFree(nx,ny)){
                        oldLastCoin=lastCoin[opponent];
                        lastCoin[opponent]=coin;
                        adj[x][y]+=1;
                        playerPos[opponent][coin].first=nx;
                        playerPos[opponent][coin].second=ny;
                        bestVal=min(bestVal,minMax(depth+1,!maxTurn,alpha,beta));
                        //pruning
                        beta = min(beta , bestVal);
                        lastCoin[opponent]=oldLastCoin;
                        adj[x][y]-=1;
                        playerPos[opponent][coin].first=x;
                        playerPos[opponent][coin].second=y;
                        if(alpha >= beta) return bestVal;

                        // finish = clock();
                        // //checking if the program didnt run out of time at this depth
                        // if(double(finish - start)/CLOCKS_PER_SEC > timelimit){
                        //     return bestVal;
                        // }
                    }
                }
            }
        }
    }

    return bestVal;
}


void findBestMove(){
    pair<int,int> bestmove = {-1,-1};
    int moveval , bestval= -INF;
    int bestcoin = 0;
    
    for(int coin=1;coin<=3;coin++){
        if(coin != lastCoin[player]){
            int x = playerPos[player][coin].first;
            int y = playerPos[player][coin].second;
            for(int i=0;i<4;i++){
                int nx = x + moves[i].first;
                int ny = y + moves[i].second;

                if(!isFree(nx , ny)) continue;
                int oldLastCoin = lastCoin[player];
                lastCoin[player] = coin;
                playerPos[player][coin].first = nx;
                playerPos[player][coin].second = ny;

                moveval = minMax(0 , false , -INF , +INF);
                if(moveval >= bestval){
                    bestval = moveval;
                    bestmove.first = nx;
                    bestmove.second = ny;
                    bestcoin = coin;
                }
                lastCoin[player] = oldLastCoin;
                playerPos[player][coin].first = x;
                playerPos[player][coin].second = y;

                //checking if the program didnt run out of time at this depth
                // finish = clock();
                // if(double(finish - start)/CLOCKS_PER_SEC > timelimit){
                //     return {bestcoin , bestmove};
                // }
            }
        }
    }
    cout<<bestcoin<<" "<<bestmove.first<<" "<<bestmove.second<<endl;

}


// void iterativedeepening(){
//     start = clock();
//     maxDepth = 1;
//     pair<int,pair<int,int>> finalMove , newMove;

//     //increasing the depth until the program doesnt run out of time
//     while(maxDepth < 10){
//         newMove = findBestMove(maxDepth);
//         finish = clock();
//         if(double(finish - start)/CLOCKS_PER_SEC > timelimit){
//             cout<<finalMove.first<<" "<<finalMove.second.first<<" "<<finalMove.second.second<<endl;
//             return;
//         }
//         finalMove = newMove;
//         maxDepth++;
//     }

//     cout<<finalMove.first<<" "<<finalMove.second.first<<" "<<finalMove.second.second<<endl;
//     return;
// }

int main()
{
    cin >> n >> m >> player;
    opponent=3-player;

    adj = vector<vector<int>>(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> adj[i][j];

    playerPos = vector<vector<pair<int, int>>>(3, vector<pair<int, int>>(4));
    for(int i=1;i<=2;i++)
        for(int j=1;j<=3;j++)
        cin >> playerPos[i][j].first >> playerPos[i][j].second;

    lastCoin=vector<int>(3);
    for(int i=1;i<=2;i++)
        cin >> lastCoin[i];
    
    findBestMove();
    return 0;
}