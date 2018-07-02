#include<iostream>
#include<vector>
#include"cache.h"

using namespace std;



Cache cache_a(512, 32);
Cache cache_b(512, 32);
Cache cache_c_L1(128, 16);
Cache cache_c_L2(4096, 128);

vector<vector<int>> A, B, C;

void addu(long long& rd, long long rs, long long rt){
    rd = rs + rt;
}

void mul(long long& rd, long long rs, long long rt){
    rd = rs * rt;
}

void lw_a(long long& rt, long long address, int i, int j, int k, char matrix){
    simulate(cache_a, address);
    
    if(matrix == 'A')
        rt = A[i][k];
    else if(matrix == 'B')
        rt = B[k][j];
    else if(matrix == 'C')
        rt = C[i][j];

}

void sw(long long rt, int i, int j){
    C[i][j] = rt;
}


int main(){

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

    
    //matrix multiplication
    r[1] = 4;                               // $1 = const 4;
    cycle ++;
    r[3] = 0;
    cycle++;

    for(i = 0; i < m; i++){
        cycle += 2;                         //for slt & beq
        cycle ++; //for addi $4, $0,0
        for(j = 0; j < n; j++){
            cycle += 2;
            cycle ++; //addi $5, $0, 0
            for(k = 0; k < p; k++){
                cycle +=2;

                mul(r[7], r[3], r[23]);
                addu(r[8], r[7], r[4]);
                mul(r[8], r[8], r[1]);
                addu(r[9], r[8], r[26]);    //r[9] = 4(i*p+j) + C[]base

                lw_a(r[10], r[9], i, j, k, 'C');
                mul(r[11], r[3], r[22]);
                addu(r[12], r[11], r[5]);
                mul(r[12], r[12], r[1]);
                addu(r[13], r[12], r[24]);  //r[13] = 4(i*n+k) + A[]base

                lw_a(r[14], r[13], i, j, k, 'A');
                mul(r[15], r[5], r[23]);
                addu(r[16], r[15], r[4]);
                mul(r[16], r[16], r[1]);
                addu(r[17], r[16], r[25]);  //r[17] = 4(k*p+j) + B[]base

                lw_a(r[18], r[17], i, j, k, 'B');
                mul(r[19], r[18], r[14]);
                addu(r[20], r[10], r[19]);
                sw(r[20], i, j);

                cycle += 18;                //for 18 instructions above 

                cycle += 2;
                if(k==p-1){
                    cycle+=2;
                }
            }

            cycle += 2;
            if(j==n-1){
                cycle +=2;
            }
        }

        cycle += 2;
        if(i==m-1){
            cycle +=2;
        }                         //for addi & j
    }
    cycle++;
    cout <<"cycle=" <<cycle<<endl;

	for (auto i : C)
		for (auto j : i)
			cout << j;
    return 0;
}

