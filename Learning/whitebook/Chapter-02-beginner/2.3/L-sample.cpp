#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXV 410
#define MAXM 40010
 
typedef struct {
    int h,a,c;
}Blocks;
 
Blocks v[MAXV];
 
int cmp(Blocks x,Blocks y){
    return x.a<y.a;
}
int dp[MAXM],user[MAXM];
 
int main(){
    int i,t,j,M;
    int test = 1;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(~scanf("%d",&t)){
        for(i=1;i<=t;i++){
            scanf("%d%d%d",&v[i].h,&v[i].a,&v[i].c);
        }
        sort(v+1,v+t+1,cmp);
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        M=0;  //赋值为0，高度可能为零
        for(i=1;i<=t;i++){
            memset(user,0,sizeof(user));
            for (j=v[i].h;j<=v[i].a;j++){
                if(!dp[j] && dp[j-v[i].h] && user[j-v[i].h]+1<=v[i].c){
                    dp[j]=1;
                    user[j]=user[j-v[i].h]+1;
                    if(j>M) M=j;
                }
            }
        }
        printf("Case %d: %d\n", test++ ,M);
        //printf("%d\n", M);
    }
    return 0;
}