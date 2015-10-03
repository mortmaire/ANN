#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <png++/png.hpp>

using namespace std;
using namespace png;
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
            cerr<<fixed<<setprecision(2)<<Output[i]<<" ";
        if(f)cerr<<endl;
        
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
            if(f)cerr<<"Layer "<<(i<10?" ":"")<<i<<": ";
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
        Layers[k/(s*s)].Neurons[k%(s*s)/s].W[k%s]=val;
        Layers[k/(s*s)].Neurons[k%(s*s)/s].refresh();
                
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

};
