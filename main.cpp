#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

double T0=0.05;
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
        return 1/(1+exp(-(dd-D)/T));
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
    double Fire(int f=0){
        for(int i=0;i<Layers.size();i++){
            if(f)cout<<"Layer "<<(i<10?" ":"")<<i<<": ";
            Layers[i].Fire(f);
        }
        return Layers[Layers.size()-1].Output[0];
    }
    void SetInput(vector<double> in){
        Layers[0].Input=in;
    }
    
    void SetW(int k){
        
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
    for(int i=0;i<16;i++)inn[i]=1;
    
    
    vector<double> WhiteNoise(inn,inn+n);
    
    for(int i=0;i<16;i++)cout<<Signal[i]<<" ";
    cout<<endl;
    for(int i=0;i<16;i++)cout<<WhiteNoise[i]<<" ";
    cout<<endl;
    int N=4*n*n+n;
//     double *tab[N];
    Net Siec=Net(Signal,1,5);
//     Siec.SetTableW(tab);
//     cout<<N<<endl;
    for(int i=0;i<1;i++){
//         for(int j=0;j<N;j++){(*tab)[j]=(rand()%3-1);cout<<j<<" "<<N<<endl;}
//         Siec.SetInput(&Signal);
//         double a=Siec.Fire();
//         Siec.SetInput(&WhiteNoise);
//         double b=Siec.Fire();
//         
//         cout<<b-a<<endl;
    }
    cout<<"Cześć pracy!"<<endl;
}