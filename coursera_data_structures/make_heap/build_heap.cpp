#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    /*
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
      */
    /*
    div_t div_result = div((data_.size() - 1),2);
    int first_subtree = div_result.quot;
    for (int i = first_subtree; i >= 0; --i) {
	    int left_child = (i*2) + 1;
	    int right_child = (i*2) + 2;
	    if(right_child < data_.size()) {
		if(data_[i] > data_[right_child]) {
			swap(data_[i],data_[right_child]);
			swaps_.push_back(make_pair(i, right_child));
		}
	    }
	    if(left_child < data_.size()) {
	    	if(data_[i] > data_[left_child]) {
			swap(data_[i],data_[left_child]);
			swaps_.push_back(make_pair(i, left_child));
		}
	    }
    }
    */
    for (int i = (data_.size() - 1) ; i > 0; --i) {
	    siftUp(i);
    }

  }

  void siftUp(int index) {
	  div_t div_result = div((index - 1),2);
	  int parent = div_result.quot;
	  if (index > 0 && data_[index] < data_[parent])
	  {
		  swap(data_[index],data_[parent]);
		  swaps_.push_back(make_pair(parent, index));
		  siftUp(parent);
	  }
  }
 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
