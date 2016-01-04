#include<iostream>
#include<vector>

using namespace std;
const int maxN = 1000;

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int isPow2(int a) {
	return !(a&(a - 1));
}

int MinDivPow2(int n){
	int i = 0;
	while ((1 << i) < n) {
		i++;
	}
	return 1 << i;
}

vector<pair<int,int>> pairs_Batcher(int begin, int end, int r){
	vector<pair<int,int>> res,t;

	int step = 2 * r;
	if (step < end - begin){
	
		t = pairs_Batcher(begin, end, step);
		res.insert(res.end(), t.begin(), t.end());

		t = pairs_Batcher(begin + r, end, step);
		res.insert(res.end(), t.begin(), t.end());

		for (int i = begin + r; i <= end - r; i += step)
		{
			res.push_back(pair<int,int>(i, i + r));
		}
	}
	else
		res.push_back(pair<int, int>(begin, begin + r));

	return res;
}

vector<pair<int, int>> pairs_Batcher_range(int begin, int end){
	vector<pair<int, int>> res, range;

	if (end - begin >= 1){							//add pairs from first half, second half and from all length
		int mid = begin + (end - begin) / 2;

		range = pairs_Batcher_range(begin, mid);
		res.insert(res.end(), range.begin(), range.end());


		range = pairs_Batcher_range(mid + 1, end);
		res.insert(res.end(), range.begin(), range.end());


		range = pairs_Batcher(begin, end, 1);
		res.insert(res.end(), range.begin(), range.end());
	}

	return res;
} 

void merge_arrays(int first[], int second[], int res[], int length)
{
	for (int i = 0, j = 0, k = 0; k < 2 * length; k++)
	{
		if (i == length) { res[k] = second[j++]; continue; }
		if (j == length) { res[k] = first[i++]; continue; }
		res[k] = (first[i] < second[j]) ? first[i++] : second[j++];
	}
}

void merge(pair<int, int> array, int **data, int length){	
	int *sorted_array = new int[2*length];												//merge two sorted arrays into the one array 
	merge_arrays(data[array.first], data[array.second], sorted_array, length);
	for (int i = 0; i < length; i++) data[array.first][i] = sorted_array[i];			// split in half the sorted array between two processors
	for (int i = 0; i < length; i++) data[array.second][i] = sorted_array[i + length];
	delete[] sorted_array;
}


int main(){
	int k, N, length; 
	cout << "Input amount of genereted elements for sorting and k (amount of streams) :";
	cin >> N >> k;

	int number_of_streams = k;
	if (!isPow2(k)) number_of_streams = MinDivPow2(k);		// k has to be a power of two, if it isn`t, 
	length = N / k;											// we will just generete more numbers, but won`t output they in results
	int **data = new int* [number_of_streams];
	for (int i = 0; i< number_of_streams; i++) {			// numbers are saved in matrix, where rows are streams
		data[i] = new int[length];							// amount numbers in every streams are equal 'length'
		if (i < k){
			for (int j = 0; j < length; j++){
				data[i][j] = rand() % 50 ;
				cout << data[i][j] << ' ';
			}
			cout << endl;
		}
		else 	{
			for (int j = 0; j < length; j++)
				data[i][j] = INT_MAX;
		}
	}  cout << endl;

	for (int i = 0; i < k; i++)							// sorting array on every stream
	{
		qsort(data[i], length, sizeof(int), compare);
		for (int j = 0; j < length; j++){				//output all datas on every stream
			cout << data[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl; cout << endl;

	vector<pair<int,int>> pairs;						// create Batcer`s net for sorting that depends on only number k (number of streams)
	pairs = pairs_Batcher_range(0, number_of_streams - 1);
	for (int i = 0; i < pairs.size(); i++)
		cout << "(" << pairs[i].first << ':' << pairs[i].second << "), "; // got list of pairs for comparing
	cout << endl;

	for (int i = 0; i < pairs.size(); i++){				// comparing and merging in every pair
		merge(pairs[i], data, length);
	}

	for (int i = 0; i< k; i++) {					//output all datas on every streams
		for (int j = 0; j < length; j++){
			cout << data[i][j] << ' ';
		}
	}

	for (int i = 0; i < k; i++)						//cleaning memory of datas
		delete[]data[i];
	system("pause");
}