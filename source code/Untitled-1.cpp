#include<iostream>
#include<vector>
using namespace std;

// class Cache{
// 	public:
// 		int cache_size, block_size, set_size;
// 		int offset_bit, index_bit, line, set_n;
// 		vector<vector<cache_content>> data;
		
// 		Cache(int cache_size, int block_size, int set_size = 8){
// 			this->cache_size = cache_size;
// 			this->block_size = block_size;
// 			this->set_size = set_size;

// 			this->offset_bit = (int)log2(block_size);			//2^(offset_bit) bytes in one block
// 			this->index_bit = (int)log2((cache_size / block_size) / set_size);
// 			this->line = cache_size >> (this->offset_bit);		// cache/2^(offset_bit) is "number of block"
// 			this->set_n = this->line / set_size;				//how many sets in cache

// 			this->data.resize(set_n);                           //initialize cache content
// 			for (int i = 0; i < set_n; i++){
// 				this->data[i].resize(set_size);
//                 for(int j = 0; j < set_size; j++)
// 				    this->data[i][j] = false;
// 			}
// 		}
// };

int main(){
    // Cache a(64, 4, 8);
    // cout << a.index_bit << " " << a.offset_bit << " " << a.line << " " << a.set_n;
    // for(auto i : a.data){
    //     for(auto j : i)
    //         cout << j
    // }
    int a;
    cout << (a=100);
    return 0;
}