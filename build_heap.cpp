#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using std::is_sorted;

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
    /*for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
      */
    // Build Heap
    if (is_sorted(data_.begin(), data_.end())) {
       return;
    }
    for (int i = data_.size()/2 - 1; i >= 0; i--) {
      sift_down(i);      
    }
   // Sort the Heap
    heap_sort();
  }

  void sift_down(int i) {
   int smaller_child;
   if (2*i + 1 > data_.size() - 1) {
      return;
   } else if (2*i + 2 > data_.size() - 1) {
      smaller_child = 2*i + 1;
   } else {
      smaller_child = (data_[2*i + 1] < data_[2*i + 2]) ? 2*i + 1 : 2*i + 2;
   }
   
   if (data_[i] <= data_[smaller_child]) {
      return;
   } else {
      //swap with smaller child
      swaps_.push_back(make_pair(i, smaller_child)); 
      int temp = data_[smaller_child];
      data_[smaller_child] = data_[i];
      data_[i] = temp;
   }
   sift_down(smaller_child);
  }

  void heap_sort() {
    
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
