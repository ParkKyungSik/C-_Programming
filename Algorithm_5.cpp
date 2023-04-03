#include<iostream>
#include<vector>
#include<queue>
#define INF 1e9
using namespace std;
 
int main()
{
    int V,E;
    printf("노드의 갯수와 엣지의 갯수를 입력받습니다 : ");
    scanf("%d %d", &V ,&E);
    int start;
    printf("\n시작점을 입력받습니다 : ");
    scanf("%d",&start);         
    vector<pair<int,int> > arr[V+1];
    
    printf("\n그래프 상의 엣지들에 대한 정보를 입력받습니다 : \n");
    for(int i=0;i<E;i++){
        int from,to,val;
        scanf("%d %d %d", &from, &to, &val);
        arr[from].push_back({to,val});
    }
    int dist[V+1];    //최단거리를 갱신해주는 배열입니다. 
    fill(dist,dist+V+1,INF);    //먼저 무한대로 전부 초기화를 시켜둡니다. 
    priority_queue<pair<int,int> > qu;     
    
    qu.push({0,start});    //우선순위 큐에 시작점을 넣어줍니다. 
    dist[start]=0;    //시작점의 최단거리를 갱신합니다. 
    
    while(!qu.empty()){
        int cost=-qu.top().first;    // cost는 다음 방문할 점의 dist값을 뜻합니다. 
        int here=qu.top().second;     // here을 방문할 점의 번호를 뜻합니다 
        
        qu.pop();
            
        for(int i=0; i<arr[here].size(); i++){
            int next=arr[here][i].first;
            int nextcost=arr[here][i].second;
            if(dist[next] > dist[here] + nextcost){    
                //현재 next에 저장된 dist의값보다 현재의 점을 거쳐서 갈 경우가 
                // 거리가 더짧으면 갱신해 주고 큐에 넣습니다.
                dist[next]=dist[here]+nextcost;
                qu.push({-dist[next],next});
            }
        }
        
    }
    printf("v1에서 각 노드까지 거리 : \n");
    for(int i=1;i<=V;i++){
        printf("%d\n", dist[i]);
    }

    return 0;
}