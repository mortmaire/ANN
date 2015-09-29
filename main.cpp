#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

double T0=0.1;
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
//         Layer L1(&Input,n,n,n);
//     for(int i=0;i<n;i++){
//         vector<double> In(n,0);
//         In[i]=Input.size();
//         L1[i]->GetW(&In);
//     }
//     
//     cout<<"Input:   ";
//     for(int i=0;i<Input.size();i++)cout<<Input[i]<<" ";
//     cout<<endl;
//     L1.Fire();
//     cout<<"Layer 1: ";
//     L1.Show();
//     Layer L2(L1.ShowOutput(),n,n,n);
//     L2.Fire();
//     cout<<"Layer 2: ";
//     L2.Show();
//      
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
    Net Siec(&Input,1,5);
    double a=Siec.Fire(1);
    double b=a;
    int ii=0;
/*    while(b-a<=DD){
//     for(int i=0;i<100;i++){
    Siec.Switch(rand()%4,rand()%16,rand()%16);
    b=Siec.Fire();
    ii++;
    if(ii%1000==0)cout<<"\r"<<ii<<flush;
    }
    cout<<endl;
    cout<<setprecision(99)<<b-a<<endl;
//     vector<double>* Output=L2.ShowOutput();
    
           */ 
}