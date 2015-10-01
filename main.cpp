#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

double T0=0.15;
double D0=0.5;

class Neuron{
    vector<double> W;
public:
    Neuron(int inN){
        for(int i=0;i<inN;i++)W.push_back(rand()%2);
    }
    double Fire(vector<double> *Input){
        double SW=0;
        for(int i=0;i<W.size();i++)SW+=W[i];
        if(SW==0)SW=1;
        double dd=0;
        for(int i=0;i<Input->size();i++)dd+=W[i]*(*Input)[i];
        dd/=SW;
        return 1/(1+exp(-(dd-D0)/T0));
    }
    void SetW(int i,double w){
        W[i]=w;
    }
    double ShowW(int w){
        return W[w];
    }
    
};

class Layer{
    vector<Neuron*> Neurons;
    vector<double> *Input;
    vector<double> *Output;
public:
    Layer(vector<double> *In,int n,int inN,int outN):Input(In){
        for(int i=0;i<n;i++)Neurons.push_back(new Neuron(inN));
        Output=new vector<double>(outN);
    }
    Neuron* operator[](int i){
        return Neurons[i];
    }
    vector<double>* Fire(int f=0){
        for(int i=0;i<Neurons.size();i++)(*Output)[i]=Neurons[i]->Fire(Input);
        
        if(f)for(int i=0;i<Output->size();i++)
            cout<<fixed<<setprecision(2)<<(*Output)[i]<<" ";
   if(f)     cout<<endl;
        return Output;
    }
    vector<double>* ShowOutput(){
        return Output;
    }
//     void Show(){
//         
// //         cout<<"Output: ";
//         for(int i=0;i<Output->size();i++)cout<<(*Output)[i]<<" ";
//         cout<<endl;
//     }
//     
    void SetW(int N,int n,int W){
        Neurons[N]->SetW(n,W);
    }
    Neuron* ShowN(int N){
        return Neurons[N];
    }
    
};

class Net{
    vector<Layer*> Layers;
public:
    Net(vector<double> *in,int OutN,int n){
        int s=in->size();
        Layers.push_back(new Layer(in,s,s,s));
        
        vector<double> *temp=Layers[0]->ShowOutput();
        for(int i=1;i<n-1;i++){Layers.push_back(new Layer(temp,s,s,s));
            temp=Layers[i]->ShowOutput();
            }
            Layers.push_back(new Layer(temp,1,s,1));
        for(int i=0;i<s;i++)Layers[n-1]->SetW(0,i,1);
    }
    
    
    
    double Fire(int f=0){
        vector<double> *out;
        for(int i=0;i<Layers.size()-1;i++){
            if(f)cout<<"Layer "<<(i<10?" ":"")<<i<<": ";
            Layers[i]->Fire(f);
        }
        if(f)cout<<"Output:   ";
        out=Layers[Layers.size()-1]->Fire(f);
        return (*out)[0];
    }
    void Switch(int L,int N,int W,int v=1){
    double a=Layers[L]->ShowN(N)->ShowW(W);
    Layers[L]->ShowN(N)->SetW(W,v);
        
    }
    
    
    
};


int main(int argc, char**argv){
    
    double inn[]={
    0,1,0,1,
    0,1,1,1,
    0,0,0,1,
    0,0,0,1
    };
//     for(int i=0;i<16;i++)inn[i]=1;
    
    srand(time(0));
    int n=16;
    double DD=0.0002;
    if(argc>1)DD=atof(argv[1]);
    vector<double> Input(n,0);
    cout<<"Input:    ";
    for(int i=0;i<n;i++){
        Input[i]=inn[i];
        cout<<inn[i]<<" ";
    }
    cout<<endl;
      while(true){cout<<endl;
    Net Siec(&Input,1,5);
    double a=Siec.Fire();
    double b=a;
    int ii=0;
    int jj=0;
    cout<<setprecision(20)<<a<<endl;
  
   while(b-a<=DD){
//     for(int i=0;i<100;i++){
       int K=10;
       int aa[K],bb[K],cc[K];
       for(int i=0;i<K;i++){
       aa[i]=rand()%4;
       bb[i]=rand()%16;
       cc[i]=rand()%16;
       if(aa[i]==4)bb[i]=0;
    Siec.Switch(aa[i],bb[i],cc[i]);
    }
    b=Siec.Fire();
    if(b-a>0){a=b;
    cout<<"\r"<<ii<<"\t"<<setprecision(20)<<b<<endl;
        jj=0;
    }
    else
        for(int i=0;i<K;i++)Siec.Switch(aa[i],bb[i],cc[i]);
    cerr<<"\r"<<ii++<<flush;
    jj++;
    if(jj>1e6)break;
    }}
//     cout<<setprecision(99)<<b-a<<endl;
//     vector<double>* Output=L2.ShowOutput();
    
}

