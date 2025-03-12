#include <iostream>
#include <random>
#include <chrono>
#include <new>

#define N 300'000

void rand(int (*mass)){
	unsigned seed = 1050;
	std :: default_random_engine rng(seed); 
	std :: uniform_int_distribution<unsigned> dstr (0, 100'000);
	for (unsigned counter = N-1; counter != -1; --counter){
			mass[counter] = dstr(rng);
	}
}

int search(int mass[N], int len, int n){
	for(int i = 0; i < len; ++i){
		if(mass[i] == n){
			return 0;
		}
	}
	return -1;
}

int search_a(int mass[N], int (*ref), int len, int n){
	for(int i = 0; i < len; ++i){
		if(mass[i] == n){
			int tmp = ref[i];
			ref[i] = ref[0];
			ref[0] = tmp;
			return 0;
		}
	}
	return -1;
}

int search_b(int mass[N], int (*ref), int len, int n){
	for(int i = 0; i < len; ++i){
		if(mass[i] == n){
			if(i > 0){
				int tmp = ref[i];
				ref[i] = ref[i-1];
				ref[i-1] = tmp;
			}
			return 0;
		}
	}
	return -1;
}

int search_c(int mass[N], int (*ref), int (&m)[N], int len, int n){
	for(int i = 0; i < len; ++i){
		if(mass[i] == n){
			++m[i];
			if(m[i] > m[i-1]){
				int tmp = ref[i];
				ref[i] = ref[i-1];
				ref[i-1] = tmp;
			}
			return 0;
		}
	}
	return -1;
}

int binarySearch(int mass[1000000], int len, int x){
	int low = 0, high = len-1;
	int index=0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mass[mid] == x)
		index = mid;
		high = mid - 1; 
        if (mass[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int sum_search(int mass[N], int len, int sum){
	for (int i = 0; i < len; i++){
		for (int j = i; j < len; j++){
			if((mass[i]+mass[j])==sum){
				return 0;
			}
		}
	}
	return -1;
}

int sum_optimal(int mass[N], int len, int sum){
	int right = len-1, left = 0;
	while(left <= right){
		if(mass[left]+mass[right] == sum){
			return 0;
		}
		else{
			if(mass[left]+mass[right]<sum){
				++left;
			}
			else{
				if(mass[left]+mass[right]>sum){
					--right;
				}
			}
		}
	}
	return -1;
}




int main(){
	int *m = new int[N];
	int s, n = 0;
	for(unsigned len = 100; len < N+100; len=len + len/40){
		rand(m);
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0,100000);
		auto begin = std :: chrono :: steady_clock ::now();
		
		int nuls[N] = {0};
		for (int i = 0; i < 1000; i++){
			//if(n%101 == 0){
			//	s = 35;
			//}
			//else{
				s = distribution(generator);
			//}
			//++n;
			search(m,len,s)
			;
		}
		auto end = std :: chrono :: steady_clock ::now(); 
		auto time_span = std :: chrono :: duration_cast<std :: chrono :: milliseconds >(end - begin );
		std :: cout << len << std :: endl;
		std :: cout << time_span.count() << std :: endl ;
	}
	delete []m;
}