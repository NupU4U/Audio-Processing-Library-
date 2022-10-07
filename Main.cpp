#include "/usr/include/x86_64-linux-gnu/openblas-pthread/cblas.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
//g++ -o a2.out openBlas_pointer.cpp Main.cpp -I /usr/include/x86_64-linux-gnu/openblas-pthread/ -L /usr/include/x86_64-linux-gnu/ -lopenblas -lpthread -lgfortran

typedef struct{
    int label[3];
    float prob[3];
}pred_t;

void open_multiply(float* P, float* Q, float* R,float* AA, int k, int m, int n){
    float alpha, beta;
    alpha = 1.0; beta = 1.0;
    
    cblas_sgemm(CblasRowMajor,
				CblasNoTrans, 
				CblasNoTrans, 
				k,
				n,
				m,
				alpha,
				P,
				m,
				Q,
				n,
				beta,
				R,
				n
			);


    for (int p = 0; p < n; p++)
    {
       for (int q = 0; q < k; q++)
        {
            *(AA+k*p+q) = R[(k*p+q)];
        }
    }

}

void takeInput1(string inp,float* p,int a,int b){//a is rows b is columns
    ifstream in(inp);
    if(in.fail()){
        throw invalid_argument("Maybe File Does Not Exist.");
    }
    string st;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            getline(in,st,' ');
            float f=stof(st);
            *(p+i*b+j)=f;
        }
    }
    in.close();
}

void takeInput2(string inp,float* p,int a,int b){//a is rows b is columns
    ifstream in(inp);
    if(in.fail()){
        throw invalid_argument("Maybe File Does Not Exist.");
    }
    string st;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            getline(in,st,',');
            float f=stof(st);
            *(p+i*b+j)=f;
        }
    }
    in.close();
}

void softMax(float* p,int n){  //pointer to vector and vector length.
    float total=0;
    for(int i=0;i<n;i++){
        total+=exp(*(p+i));
    }
    for(int i=0;i<n;i++){
        *(p+i)=exp(*(p+i))/total;
    }
}

void relu(float* p,int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0; j<c; j++){
            if(*(p+i*c+j)<0){
                *(p+i*c+j)=0;
            }
        }
    }
}

// void topthree(string inputstr,string outputstr,float* answer){
//     float first=0,second=0,third=0;//top 3 probabilities
//     for(int i=0;i<12;i++){
//         if(*(answer+i)>first){
//             third=second;
//             second=first;
//             first=*(answer+i);
//         }
//         else if(*(answer+i)>second){
//             third=second;
//             second=*(answer+i);
//         }
//         else if(*(answer+i)>third){
//             third=*(answer+i);
//         }
//         else{}
//     }
//     //all possible outcomes
//     string outcomes[]={"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
//     int i1,i2,i3;
//     for(int i=0;i<12;i++){
//         if(first==*(answer+i)){
//             i1=i;
//         }
//         else if(second==*(answer+i)){
//             i2=i;
//         }
//         else if(third==*(answer+i)){
//             i3=i;
//         }
//         else{}
//     }

//     ofstream outfile;
//     outfile.open(outputstr);
//     outfile<<inputstr;
//     outfile<<" ";
//     outfile<<outcomes[i1];
//     outfile<<" ";
//     outfile<<outcomes[i2];
//     outfile<<" ";
//     outfile<<outcomes[i3];
//     outfile<<" ";
//     outfile<<first;
//     outfile<<" ";
//     outfile<<second;
//     outfile<<" ";
//     outfile<<third;
//     outfile.close();
// }

// void libaudioAPI(string inputstr,string outputstr){
//     //1st multiply and relu
//     int k1=1;
//     int m1=250;
//     int n1=144;

//     float input1[k1][m1];
//     float input2_1[m1][n1];
//     float input3_1[k1][n1];
//     float answer[k1][n1];
//     float* P1=(float*)input1;
//     float* Q1=(float*)input2_1;
//     float* R1=(float*)input3_1;
//     float* A1=(float*)answer;

//     takeInput1(inputstr,P1,k1,m1);
//     takeInput2("weight1.txt",Q1,m1,n1);
//     takeInput2("bias1.txt",R1,k1,n1);

//     open_multiply(P1,Q1,R1,A1,k1,m1,n1);
//     relu(A1,k1,n1);

//     //2nd multiply and relu
//     int k2=1;
//     int m2=144;
//     int n2=144;

//     float input2_2[m2][n2];
//     float input3_2[k2][n2];
//     float answer2[k2][n2];
//     float* Q2=(float*)input2_2;
//     float* R2=(float*)input3_2;
//     float* A2=(float*)answer2;

//     takeInput2("weight2.txt",Q2,m2,n2);
//     takeInput2("bias2.txt",R2,k2,n2);

//     open_multiply(A1,Q2,R2,A2,k2,m2,n2);
//     relu(A2,k2,n2);

//     //3rd multiply and relu
//     int k3=1;
//     int m3=144;
//     int n3=144;

//     float input2_3[m3][n3];
//     float input3_3[k3][n3];
//     float answer3[k3][n3];
//     float* Q3=(float*)input2_3;
//     float* R3=(float*)input3_3;
//     float* A3=(float*)answer3;

//     takeInput2("weight3.txt",Q3,m3,n3);
//     takeInput2("bias3.txt",R3,k3,n3);

//     open_multiply(A2,Q3,R3,A3,k3,m3,n3);
//     relu(A3,k3,n3);

//     //final multiply and softmax
//     int k4=1;
//     int m4=144;
//     int n4=12;

//     float input2_4[m4][n4];
//     float input3_4[k4][n4];
//     float answer4[k4][n4];
//     float* Q4=(float*)input2_4;
//     float* R4=(float*)input3_4;
//     float* A4=(float*)answer4;

//     takeInput2("weight4.txt",Q4,m4,n4);
//     takeInput2("bias4.txt",R4,k4,n4);

//     open_multiply(A3,Q4,R4,A4,k4,m4,n4);
//     softMax(A4,n4);

//     topthree(inputstr,outputstr,A4);
// }
void topthree(const char* inputstr,pred_t* pred,float* answer){
    float first=0,second=0,third=0;//top 3 probabilities
    for(int i=0;i<12;i++){
        if(*(answer+i)>first){
            third=second;
            second=first;
            first=*(answer+i);
        }
        else if(*(answer+i)>second){
            third=second;
            second=*(answer+i);
        }
        else if(*(answer+i)>third){
            third=*(answer+i);
        }
        else{}
    }
    //all possible outcomes
    string outcomes[]={"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
    int i1,i2,i3;
    for(int i=0;i<12;i++){
        if(first==*(answer+i)){
            i1=i;
        }
        else if(second==*(answer+i)){
            i2=i;
        }
        else if(third==*(answer+i)){
            i3=i;
        }
        else{}
    }

    (*pred).label[0]=i1;
    (*pred).label[1]=i2;
    (*pred).label[2]=i3;
    (*pred).prob[0]=first;
    (*pred).prob[1]=second;
    (*pred).prob[2]=third;

}

pred_t* libaudioAPI(const char* inputstr,pred_t* pred){
    //1st multiply and relu
    int k1=1;
    int m1=250;
    int n1=144;

    float input1[k1][m1];
    float input2_1[m1][n1];
    float input3_1[k1][n1];
    float answer[k1][n1];
    float* P1=(float*)input1;
    float* Q1=(float*)input2_1;
    float* R1=(float*)input3_1;
    float* A1=(float*)answer;

    takeInput1(inputstr,P1,k1,m1);
    takeInput2("weight1.txt",Q1,m1,n1);
    takeInput2("bias1.txt",R1,k1,n1);

    open_multiply(P1,Q1,R1,A1,k1,m1,n1);
    relu(A1,k1,n1);

    //2nd multiply and relu
    int k2=1;
    int m2=144;
    int n2=144;

    float input2_2[m2][n2];
    float input3_2[k2][n2];
    float answer2[k2][n2];
    float* Q2=(float*)input2_2;
    float* R2=(float*)input3_2;
    float* A2=(float*)answer2;

    takeInput2("weight2.txt",Q2,m2,n2);
    takeInput2("bias2.txt",R2,k2,n2);

    open_multiply(A1,Q2,R2,A2,k2,m2,n2);
    relu(A2,k2,n2);

    //3rd multiply and relu
    int k3=1;
    int m3=144;
    int n3=144;

    float input2_3[m3][n3];
    float input3_3[k3][n3];
    float answer3[k3][n3];
    float* Q3=(float*)input2_3;
    float* R3=(float*)input3_3;
    float* A3=(float*)answer3;

    takeInput2("weight3.txt",Q3,m3,n3);
    takeInput2("bias3.txt",R3,k3,n3);

    open_multiply(A2,Q3,R3,A3,k3,m3,n3);
    relu(A3,k3,n3);

    //final multiply and softmax
    int k4=1;
    int m4=144;
    int n4=12;

    float input2_4[m4][n4];
    float input3_4[k4][n4];
    float answer4[k4][n4];
    float* Q4=(float*)input2_4;
    float* R4=(float*)input3_4;
    float* A4=(float*)answer4;

    takeInput2("weight4.txt",Q4,m4,n4);
    takeInput2("bias4.txt",R4,k4,n4);

    open_multiply(A3,Q4,R4,A4,k4,m4,n4);
    softMax(A4,n4);

    topthree(inputstr,pred,A4);
    return pred;
}

