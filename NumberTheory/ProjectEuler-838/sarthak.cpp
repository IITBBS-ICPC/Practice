#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e6+1;
int main()
{
    vector<int> spf(N);
    vector<int> sevenPrimes,ninePrimes,primes,threePrimes;
    for(int i=2;i<N;++i){
        if(!spf[i]){
            spf[i] = i;
            primes.pb(i);
            int u = i%10;
            if(u==3){
                threePrimes.pb(i);
            }
            else if(u==7){
                sevenPrimes.pb(i);
            }
            else if(u==9){
                ninePrimes.pb(i);
            }
        }
        for(auto p:primes){
            if((i*1ll*p)>=N)
                break;
            spf[i*p] = p;
            if(p==spf[i])break;
        }
    }
    int mn = 0;
    for(int i=2;i<sevenPrimes.size();++i){
        if((sevenPrimes[i]*1ll*sevenPrimes[i-1]*1ll*sevenPrimes[i-2])>=N){
            mn = i-2;
            break;
        }
    }
    long double ans = 0, cur_ans = 0;
    for(auto sp:sevenPrimes)
        ans += log(sp);
    for(int i=0;i<mn;++i)
        cur_ans += log((long double)sevenPrimes[i]);
    for(auto np:ninePrimes)
        cur_ans += log((long double)np);
    for(int i=mn,j=ninePrimes.size()-1;i<sevenPrimes.size();++i){
        while((j>=0)&&(sevenPrimes[i]*1ll*ninePrimes[j]>=N)){
            cur_ans-=log((long double)ninePrimes[j--]);
        }
        ans = min(ans,cur_ans);
        cur_ans+=log((long double)sevenPrimes[i]);
    }
    for(auto tp:threePrimes)
        ans+=log((long double)tp);
    cout<<fixed<<setprecision(6)<<ans<<"\n";
}