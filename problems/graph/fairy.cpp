//fairy
#include <bits/stdc++.h>
using namespace std;
const int N=10010;
int n,m,dep[N],fat[14][N],d[N][2],z[2],ans[N],cnt;
vector<pair<int,int> > ed[N];
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int ret=dep[x]-dep[y];
	for(int i=13;i>=0;i--) if(ret>=(1<<i)) ret-=1<<i,x=fat[i][x];
	if(x==y) return x;
	for(int i=13;i>=0;i--) if(fat[i][x]!=fat[i][y]) x=fat[i][x],y=fat[i][y];
	return fat[0][x];
}
void dfs(int x,int fa){
	dep[x]=dep[fa]+1;fat[0][x]=fa;
	for(int i=1;i<=13;i++) fat[i][x]=fat[i-1][fat[i-1][x]];
	for(auto [v,w]:ed[x]){
		if(v==fa) continue;
//		cout<<x<<' '<<v<<' '<<dep[v]<<endl;
		if(!dep[v]) dfs(v,x);
		else{
			int lca=LCA(x,v);
			int c=dep[x]+dep[v]-2*dep[lca]+1;z[c&1]++;
			d[x][c&1]++;d[v][c&1]++;d[lca][c&1]-=2;
//			cout<<x<<' '<<v<<' '<<lca<<endl;
		}
	}
}
bool vis[N];
void solve(int x,int fa){
	vis[x]=1;
	for(auto [v,w]:ed[x]){
		if(v==fa) continue;
		if(vis[v]){
			int lca=LCA(x,v);
			int c=dep[x]+dep[v]-2*dep[lca]+1;
			if((c&1)&&z[c&1]==2) ans[++cnt]=w; 
			continue;
		}
		solve(v,x);
		if(d[v][1]==z[1]&&!d[v][0]) cnt++,ans[cnt]=w;
		d[x][0]+=d[v][0],d[x][1]+=d[v][1];
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;cin>>x>>y;
		ed[x].push_back({y,i});
		ed[y].push_back({x,i});
	}
	for(int i=1;i<=n;i++) if(!dep[i]) dfs(i,0);
	if(!z[1]){
		cout<<m<<'\n';
		for(int i=1;i<=m;i++) cout<<i<<' ';
		return 0;
	}
	for(int i=1;i<=n;i++) if(!vis[i]) solve(i,0);
	sort(ans+1,ans+cnt+1);cnt=unique(ans+1,ans+cnt+1)-ans-1;
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++) cout<<ans[i]<<' ';
	return 0;
}
