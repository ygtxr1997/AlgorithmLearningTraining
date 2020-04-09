#include <iostream>
#include <string.h>
#include <queue>
#include <stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=200005;//这块一定是200000，因为点数增加了一倍
const int maxm=800010;
struct Edge
{
    int to,next,w;
} edge[maxm];
int tot;
int head[maxn];
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w)
{
    edge[tot].to=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int d[maxn*2];
bool vis[maxn*2];
struct node
{
    int u,w;
    node(int u,int d):u(u),w(d) {}
};
bool operator < (node a,node b)
{
    return a.w > b.w;
}
void  dijk(int s,int n)
{
    memset(vis,0,sizeof(vis));
    priority_queue<node> que;
    for(int i=0; i<=n; i++) d[i]=INF;
    d[s]=0;
    que.push(node(s,0));
    while(!que.empty())
    {
        node tmp = que.top();
        que.pop();
        int u=tmp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int e=head[u]; e!=-1; e=edge[e].next)
        {
            int v=edge[e].to,w=edge[e].w;
            if(vis[v]) continue;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                que.push(node(v,d[v]));
            }
        }
    }
}
int a[maxn*2];
int main()
{
    //ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T,n,m,t,u,v,w;
    int cases=1;
    scanf("%d",&T);
    //cin>>T;
    while(T--)
    {
        init();
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        memset(vis,0,sizeof(vis));
        //cin>>n>>m>>t;
        scanf("%d%d%d",&n,&m,&t);
        int val;
        for(int i=1;i<=n;i++)
            {
                //cin>>val;
                scanf("%d",&val);
                a[i]=val;//a[i]//表示i的层数是val
                vis[val]=1;//这是用来标记这个层是否曾经出现过 
            }
            for(int i=1;i<=n;i++)
            {
                if(a[i]==1)//如果是第一层，则只能连到下一层
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)//注意这里一定是a[i]+1，因为要表示的是这层的下一层
                // 如果写成了a[i+1]的话表示的则是i的下一个点的那一层，这样是不对的，只能相邻的层建边
                        addedge(i,a[i]+n+1,t);
                }
                else if(a[i]==n)//如果是第n层，则只能连到上一层
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
                else
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)
                        addedge(i,a[i]+n+1,t);
                      if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
            }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            //cin>>u>>v>>w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dijk(1,n*2);
        if(d[n]==INF)
            d[n]=-1;
       // cout<<"Case #"<<cases++<<": ";
        //cout<<d[n]<<endl;
        printf("Case #");
        printf("%d",cases++);
        printf(": ");
        printf("%d\n",d[n]);

    }
    return 0;
}
