/*
   Random regular graph generator.
   copyright@XYZ
   xyzdirac@gmail.com
   2018-9-19
 */
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>

using namespace std;

typedef pair<int, int> link;

int main()
{
    srand(unsigned(time(NULL)));
    random_device rd();
    mt19937 gen;
    for (int i= rand()% 10000; i> 0; i--)
        gen();
    int N= 1000;
    int cc= 5;
    stringstream ss;
    ss<<"RR_"<<cc<<"_"<<N<<".net";
    string fname= ss.str();
    cout<<fname<<endl;

    int M= cc* N/ 2;
    uniform_real_distribution<double> unfrand(0.0, 1.0);
    vector<int> candidate(N* cc);
    int nindex= 0;
    for(int ii= N; ii> 0; ii--)
    for(int k= cc; k> 0; k--)
    {
        candidate[nindex]= ii;
        nindex++;
    }
    set<link> edges;
    vector<link> edbk;
    link lk;
    vector<link>::reverse_iterator rit;
    nindex= 5;
    while(edges.size()< M)
    {
        int nlen= candidate.size();
        int ntmp0, ntmp1;
        int nhead, ntail;
        do{
                ntmp0= unfrand(gen)* nlen;
                ntmp1= unfrand(gen)* nlen;
                nhead= candidate[ntmp0];
                ntail= candidate[ntmp1];
        }while(nhead == ntail);
        if(nhead< ntail)
            lk= link(nhead, ntail);
        else
            lk= link(ntail, nhead);
        if(!edges.count(lk))
        {
            edbk.push_back(lk);
            edges.insert(lk);
            if (ntmp0 > ntmp1)
            {
                candidate.erase(candidate.begin()+ ntmp0);
                candidate.erase(candidate.begin()+ ntmp1);
            }
            else
            {
                candidate.erase(candidate.begin()+ ntmp1);
                candidate.erase(candidate.begin()+ ntmp0);
            }
        }
        else if(edbk.size()> nindex)
        {
            for(int ii= 0; ii< nindex; ii++)
            {
                rit= edbk.rbegin();
                candidate.push_back(rit->first);
                candidate.push_back(rit->second);
                edges.erase(*rit);
                edbk.erase(rit.base());
            }
        }
    }
    ofstream fout;
    fout.open(fname.c_str());
    fout<<N<<'\t'<<M<<endl<<endl;
    for(auto ip: edbk)
    if(unfrand(gen)< 0.5)
        fout<<ip.first<<'\t'<<ip.second<<endl;
    else
        fout<<ip.second<<'\t'<<ip.first<<endl;
    fout.close();
    return 0;
}
