#include "neuron.hpp"

int main(){
    int nn=16;
    int n=nn*nn;
    vector<double> letterA;
    vector<double> letterB;
    image<rgb_pixel> imageA(nn,nn),imageB(nn,nn);
    imageA.read("a1.png");
    imageB.read("b1.png");
    for(int i=0;i<n;i++){
        rgb_pixel a=imageA[i/nn][i%nn];
        letterA.push_back(((int)a.red)==255?0:1);
        a=imageB[i/nn][i%nn];
        letterB.push_back(((int)a.red)==255?0:1);
        if(i%nn==0)cerr<<endl;
        cerr<<letterA[i];
    }
    int N=4*n*n+n;
    int N2=N/n;
    Net Siec=Net(letterA,1,5);
// //     for(int i=0;i<N;i++)cerr<<Siec.SetW(i)<<endl;
// //     cerr<<N<<endl;
    double min=0;
    double tab[N];
    double tab2[N];
    double tTab[N2];
    double tTab2[N2];
    double dTab[N2];
    double dTab2[N2];
    
    cerr<<endl;
    
    for(int i=0;i<10000;i++){
        for(int j=0;j<N;j++){tab2[j]=(rand()%3-1);}
        for(int j=0;j<N2;j++){
            tTab2[j]=rand()%2*100;
            dTab2[j]=rand()%2;
        }
        Siec.SetW(tab2);
        Siec.SetT(tTab2);
        Siec.SetD(dTab2);
        double a=Siec.Fire(letterA);
        double b=Siec.Fire(letterB);
//         cerr<<"\r"<<i<<flush;
        if(min<a-b){
            cerr<<"\r"<<i<<"\t"<<a<<"\t"<<b<<"\t"<<a-b<<endl;
            min=a-b;
            for(int j=0;j<N;j++)tab[j]=tab2[j];
            for(int j=0;j<N2;j++)tTab[j]=tTab2[j];
            for(int j=0;j<N2;j++)dTab[j]=dTab2[j];
        }
    }

    int i=0;
    double t=time(0);
    while(true){
    int k=rand()%N;
    double v=tab[k];
    int k2=rand()%N2;
    double v2=tTab[k2];
    int k3=rand()%N2;
    double v3=dTab[k3];
    tab[k]=rand()%3-1;
    tTab[k2]=rand()%3/2.*100;
    dTab[k3]=rand()%3/2.;
    Siec.SetW(tab);
    Siec.SetT(tTab);
    Siec.SetD(dTab);
    double a=Siec.Fire(letterA);
    double b=Siec.Fire(letterB);
//     cerr<<"\r"<<i++<<flush;
    i++;
    if(a-b<=min){tab[k]=v;tTab[k2]=v2;dTab[k3]=v3;}
    else{min=a-b;cerr<<"\r"<<i<<scientific<<setprecision(6)<<"\t"<<a<<"\t"<<b<<"\t"<<min<<"\t"<<fixed<<(int)(i/(time(0)-t))<<endl;
        cout<<i<<"\t"<<min<<endl;
    }
    if(min>0.9999)break;
        
    }
//     Siec.Fire(letterA,1);
//     Siec.Fire(letterB,1);
    
    fstream file("W.txt",ios::out);
    for(int i=0;i<N;i++)file<<tab[i]<<endl;
    file<<endl;
    for(int i=0;i<N2;i++)file<<tTab[i]<<endl;
    file<<endl;
    for(int i=0;i<N2;i++)file<<dTab[i]<<endl;
    file.close();

}