#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "Main.h"
using namespace std;

int main(int argc,char* argv[]){
    if(argc!= 3){
        throw invalid_argument("Number of arguments mismatch\n");// if fullyconnected is found argc must be 6 else we throw exception
    } 
    const char* input=argv[1];
    pred_t *pred,p;
    pred=&p;
    libaudioAPI(input,pred);
    string outcomes[]={"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};

    ofstream outfile;
    outfile.open(argv[2], std::ofstream::out | std::ofstream::app);
    outfile<<argv[1];
    outfile<<" ";
    outfile<<outcomes[p.label[0]];
    outfile<<" ";
    outfile<<outcomes[p.label[1]];
    outfile<<" ";
    outfile<<outcomes[p.label[2]];
    outfile<<" ";
    outfile<<p.prob[0];
    outfile<<" ";
    outfile<<p.prob[1];
    outfile<<" ";
    outfile<<p.prob[2];
    outfile<<"\n";
    outfile.close();
    return 0;
}