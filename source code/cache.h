#include <iostream>
#include <stdio.h>
#include <math.h>
#include <climits>
#include <string>
#include <vector>

using namespace std;

 long long cycle = 0;
 long long stall_a = 0, stall_b = 0, stall_c = 0;

double log2(double n)
{
	// log(n) / log(2) is log2.	log with base 2
	return log(n) / log(double(2));
}

struct cache_content
{
	bool v;				//verify bit
	unsigned int tag;
	unsigned int time;	//time stamp for last use
};

class Cache{
	public:
		int cache_size, block_size, set_size;
		int offset_bit, index_bit, line, set_n;
		vector<vector<cache_content>> data;

		Cache(int cache_size, int block_size, int set_size = 8){
			this->cache_size = cache_size;
			this->block_size = block_size;
			this->set_size = set_size;

			this->offset_bit = (int)log2(block_size);			//2^(offset_bit) bytes in one block
			this->index_bit = (int)log2((cache_size / block_size) / set_size);
			this->line = cache_size >> (this->offset_bit);		// cache/2^(offset_bit) is "number of block"
			this->set_n = this->line / set_size;				//how many sets in cache

			this->data.resize(set_n);							//initialize cache content
			for (int i = 0; i < set_n; i++){
				this->data[i].resize(set_size);

                for(int j = 0; j < set_size; j++)
				    this->data[i][j].v = false;
			}
		}
};


void simulate(Cache& cache, long long address)
{
	unsigned int tag, index;

	int offset_bit = cache.offset_bit;			//2^(offset_bit) bytes in one block
	int index_bit = cache.index_bit;
	int line = cache.line;						// cache/2^(offset_bit) is "number of block"
	int set_n = cache.set_n;					//how many sets in cache


	index = (address >> cache.offset_bit) & (cache.set_n - 1);				//filter the index bits
	tag = address >> (cache.index_bit + cache.offset_bit);					//filter the tag bits

	bool hit_flag = false, empty = false;
	for (int i = 0; i < cache.set_size; i++){
		if (cache.data[index][i].v && cache.data[index][i].tag == tag){
			hit_flag = true;					//hit
			cache.data[index][i].time = cycle;
		}
	}

	if (hit_flag == false){						//miss
		
		for (int i = 0; i < cache.set_size; i++){
			if (cache.data[index][i].v == false){
				empty = true;					//some idle space for new data
				cache.data[index][i].v = true;
				cache.data[index][i].tag = tag;
				cache.data[index][i].time = cycle;
			}
		}

		if (empty == false){					//there are no idle space
			int earliest = INT_MAX, LRU = -1;
			for (int i = 0; i<cache.set_size; i++){				//find LRU block
				if (cache.data[index][i].time <= earliest){
					earliest = cache.data[index][i].time;
					LRU = i;
				}
			}

			cache.data[index][LRU].tag = tag;
			cache.data[index][LRU].time = cycle;
		}
	}

}