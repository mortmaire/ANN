#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdio>
using namespace std;

double T0=20;
double D0=0.15;

class Neuron{
    friend class Net;
    
    vector<double> W;
    double T;
    double D;
    double SW;
public:
    Neuron(int N){
        T=T0;
        D=D0;
        for(int i=0;i<N;i++){
            W.push_back(double(rand()%3-1));
            SW+=abs(W[i]);
        }
        if(SW==0)SW=1;
    }
    ~Neuron(){
//         for(int i=0;i<W.size();i++)
//             delete W[i];
//         delete T,D;
    }
    void refresh(){
        SW=0;
        for(int i=0;i<W.size();i++)SW+=abs(W[i]);
        if(SW==0)SW=1;
    }
    double Fire(vector<double> Input){
        double dd=0;
        for(int i=0;i<Input.size();i++){
            dd+=(W[i])*Input[i];  
        }
        dd/=SW;
        return 1/(1+exp(-(dd-D)*T));
    }
};

class Layer{
    friend class Net;
    vector<Neuron> Neurons;
    vector<double> Input;
    vector<double> Output;
public:
    Layer(vector<double> Input,int n):Input(Input){
        int s=Input.size();
        for(int i=0;i<n;i++)Neurons.push_back(Neuron(s));
        Output=vector<double>(s);
    }
    ~Layer(){}

    void Fire(int f=0){
        for(int i=0;i<Neurons.size();i++){Output[i]=Neurons[i].Fire(Input);}
        if(f)for(int i=0;i<Output.size();i++)
            cout<<fixed<<setprecision(2)<<Output[i]<<" ";
        if(f)cout<<endl;
        
    }


};

class Net{
    vector<Layer> Layers;
    int s;
    int L;
    vector<double> Input;
public:
    Net(vector<double> in,int OutN,int n){
        s=in.size();
        Layers.push_back(Layer(in,s));
        vector<double> temp=Layers[0].Output;
        for(int i=1;i<n-1;i++){
            Layers.push_back(Layer(temp,s));
            temp=Layers[i].Output;
        }
        Layers.push_back(Layer(temp,1));
    }
    double Fire(vector<double> Input,int f=0){
        for(int i=0;i<Layers.size();i++){
            if(f)cout<<"Layer "<<(i<10?" ":"")<<i<<": ";
            Layers[i].Input=Input;
            Layers[i].Fire(f);
            Input=Layers[i].Output;
        }
        return Layers[Layers.size()-1].Output[0];
    }
    void SetInput(vector<double> in){
        Layers[0].Input=in;
    }
    
    double SetW(int k,double val=999){
        if(val==999){
//             printf("Layer %d Neuron %d Weight %d\t",k/(s*s),k%(s*s)/s,k%s);
            return Layers[k/(s*s)].Neurons[k%(s*s)/s].W[k%s];
        }
        else Layers[k/(s*s)].Neurons[k%(s*s)/s].W[k%s]=val;
    }
    
    double SetW(double *tab){
        int N=4*s*s+s;
        for(int i=0;i<N;i++)SetW(i,tab[i]);
    }
    
    double SetT(int k,double val=999){
        if(val==999)return Layers[k/s].Neurons[k%s].T;
        Layers[k/s].Neurons[k%s].T=val;
    }
    double SetT(double *tab){
        int NN=4*s+1;
        for(int i=0;i<NN;i++)SetT(i,tab[i]);
    }
    double SetD(int k,double val=999){
        if(val==999)return Layers[k/s].Neurons[k%s].D;
        Layers[k/s].Neurons[k%s].D=val;
    }
    double SetD(double *tab){
        int NN=4*s+1;
        for(int i=0;i<NN;i++)SetD(i,tab[i]);
    }
//     void SetTableW(double **tab){
//         int L=Layers.size();
//         for(int i=0;i<L-1;i++)
//             for(int j=0;j<s;j++)
//                 for(int k=0;k<s;k++){
//                     tab[i*s*s+j*s+k]=Layers[i].Neurons[j].W[k];
//                     cout<<i*s*s+j*s+k<<endl;
//                 }
//         for(int i=0;i<s;i++){
//             tab[(L-1)*s*s+i]=Layers[L-1].Neurons[0].W[i];
//             cout<<i<<endl;
//         }
//     }
};


int main(){
    int n=16;
    double inn[]={
    0,1,0,1,
    0,1,1,1,
    0,0,0,1,
    0,0,0,1
    };
    vector<double> Signal(inn,inn+n);
    for(int i=0;i<n;i++)inn[i]=1;
    
    
    vector<double> WhiteNoise(inn,inn+n);
    
    for(int i=0;i<n;i++)inn[i]=0;
    
    vector<double> BlackNoise(inn,inn+n);
    
    for(int i=0;i<n;i++)cout<<Signal[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)cout<<WhiteNoise[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)cout<<BlackNoise[i]<<" ";
    cout<<endl;
    int N=4*n*n+n;
    int N2=N/n;
    double tab[N];
    double tab2[N];
    Net Siec=Net(Signal,1,5);
//     for(int i=0;i<N;i++)cout<<Siec.SetW(i)<<endl;
//     cout<<N<<endl;
    double min=0;
    double tTab[N2];
    double tTab2[N2];
    double dTab[N2];
    double dTab2[N2];
    
    for(int i=0;i<100000;i++){
        for(int j=0;j<N;j++){tab2[j]=(rand()%3-1);}
        for(int j=0;j<N2;j++){
            tTab2[j]=rand()%100+1;
            dTab2[j]=rand()%100/100.;
        }
        Siec.SetW(tab2);
//         cout<<"aa"<<endl;
        Siec.SetT(tTab2);
        Siec.SetD(dTab2);
        double a=Siec.Fire(Signal);
        double b=Siec.Fire(WhiteNoise);
        double c=Siec.Fire(BlackNoise);
if(min<a-b-c){         
        cout<<i<<"\t"<<a<<"\t"<<b<<"\t"<<c<<"\t"<<a-b-c<<endl;
        min=a-b-c;
        for(int j=0;j<N;j++)tab[j]=tab2[j];
        for(int j=0;j<N2;j++)tTab[j]=tTab2[j];
        for(int j=0;j<N2;j++)dTab[j]=dTab2[j];
}
    }
    for(int i=0;i<1000000;i++){
    int k=rand()%N;
    double v=tab[k];
    int k2=rand()%N2;
    double v2=tTab[k2];
    int k3=rand()%N2;
    double v3=dTab[k3];
    tab[k]=rand()%3-1;
    tTab[k2]=rand()%100;
    dTab[k3]=rand()%100/100.;
    Siec.SetW(tab);
    Siec.SetT(tTab);
    Siec.SetD(dTab);
    double a=Siec.Fire(Signal);
    double b=Siec.Fire(WhiteNoise);
    double c=Siec.Fire(BlackNoise);
    if(a-b-c<=min){tab[k]=v;tTab[k2]=v2;dTab[k3]=v3;}
    else{min=a-b-c;cout<<i<<"\t"<<a<<"\t"<<b<<"\t"<<c<<"\t"<<min<<endl;}
        
    }
    cout<<"Cześć pracy!"<<endl;
}