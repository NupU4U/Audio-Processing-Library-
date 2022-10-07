using namespace std;

#ifndef Main_h__
#define Main_h__

typedef struct{
    int label[3];
    float prob[3];
}pred_t;

extern pred_t* libaudioAPI(const char* inputstr,pred_t* pred);
#endif