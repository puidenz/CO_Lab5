#include<iostream>

using namespace std;

void addu(long long& rd, long long rs, long long rt){
    rd = rs + rt;
}

void mul(long long& rd, long long rs, long long rt){
    rd = rs * rt;
}

void lw(){}
void sw(){}

int main(){
    // long long r24, r24, r26;  //A B C[] base
    // long long r3, r4, r5;     //i, j, k 
    // const long long r1 = 4;   //const 4

    long long r[27] = {0};
    cin >> hex >> r[24] >> r[25] >> r[26];  //A B C[] base
    cin >> r[21] >> r[22] >> r[23];         //m, n, p
                                            
    long long& a_base = r[24], b_base = r[25], c_base = r[26];
    long long& m = r[21], n = r[22], p = r[23];
    long long& i = r[3], j = r[4], k = r[5];
    //matrix multiplication
    r[1] = 4;                               // $1 = const 4;

    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < p; k++){
                mul(r[7], r[3], r[23]);
                addu(r[8], r[7], r[4]);
                mul(r[8], r[8], r[1]);
                addu(r[9], r[8], r[26]);    //r[9] = 4(i*p+j) + C[]base

                lw();
                mul(r[11], r[3], r[22]);
                addu(r[12], r[11], r[5]);
                mul(r[12], r[12], r[1]);
                addu(r[13], r[12], r[24]);  //r[13] = 4(i*n+k) + A[]base

                lw();
                mul(r[15], r[5], r[23]);
                addu(r[16], r[15], r[4]);
                mul(r[16], r[16], r[1]);
                addu(r[17], r[16], r[25]);  //r[17] = 4(k*p+j) + B[]base

                lw();
                mul(r[19], r[18], r[14]);
                addu(r[20], r[10], r[19]);
                sw();
            }
        }
    }


    return 0;
}

