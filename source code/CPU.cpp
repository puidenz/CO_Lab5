#include<iostream>
#include<vector>
#include"cache.h"

using namespace std;

vector<cache_content> cache_a(16);      //2^4 blocks
cache_content cache_b(16);      //2^4 blocks
cache_content cache_c_L1 (8);   //2^3 blocks
cache_content cache_c_L2 (32);  //2^5 blocks

vector<vector<int>> A, B, C;

void addu(long long& rd, long long rs, long long rt){
    rd = rs + rt;
}

void mul(long long& rd, long long rs, long long rt){
    rd = rs * rt;
}

void lw_a(long long& rt, long long address){
    
}

void sw(long long rt, long long address){

}

void cache_initial(vector<cache_content>& cache){
    int size = cache.size;
    for(int i=0; i<size; i++){
        cache[i].v = false;
    }
}

int main(){
    long long count = 0;         //count cycle

    long long r[27] = {0};
    cin >> hex >> r[24] >> r[25] >> r[26];  //A B C[] base
    cin >> r[21] >> r[22] >> r[23];         //m, n, p
                                            
    long long& a_base = r[24], b_base = r[25], c_base = r[26];
    long long& m = r[21], n = r[22], p = r[23];
    long long& i = r[3], j = r[4], k = r[5];

    
    A.resize(m);                //vector matrix resize
    B.resize(n);
    C.resize(m);

    for(int i = 0; i < m; i++)   
        A[i].resize(n);
    for(int i = 0; i < n; i++)
        B[i].resize(p);
    for(int i = 0; i < m; i++)
        C[i].resize(p);

    for(int i=0; i<m; i++)       //matrix initialize
        for(int j=0; j<n; j++)
            cin >> A[i][j];
    for(int i=0; i<n; i++)
        for(int j=0; j<p; j++)
            cin >> B[i][j];
    for(int i=0; i<m; i++)
        for(int j=0; j<p; j++)
            C[i][j] = 0;

    cache_initial(cache_a);     //cache initialize
    cache_initial(cache_b);
    cache_initial(cache_c_L1);
    cache_initial(cache_c_L2);


    //matrix multiplication
    r[1] = 4;                               // $1 = const 4;
    count ++;

    for(i = 0; i < m; i++){
        count += 2;                         //for slt & beq
        
        for(j = 0; j < n; j++){
            count += 2;

            for(k = 0; k < p; k++){
                count +=2;

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

                count += 18;                //for 18 instructions above 

                count += 2;
            }

            count += 2;
        }

        count += 2;                         //for addi & j
    }

    // for(int i = 0; i < m; i++)
    //     delete[] A[i];
    // for(int i = 0; i < n; i++)
    //     delete[] B[i];
    // for(int i = 0; i < m; i++)
    //     delete[] C[i];

    // delete[] A;
    // delete[] B;
    // delete[] C;

    return 0;
}

