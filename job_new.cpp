#include <iostream>                                                             
#include <vector>                                                               
#include <algorithm>                                                            
#include <utility>
#include <cstdlib>

using std::vector;                                                              
using std::cin;                                                                 
using std::cout;
using std::pair;
using namespace std;

/*
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector<std::pair< long long, long long>> prio_queue;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void initializeHeap() {
    for (int i = 0; i < num_workers_; i++) {
       prio_queue.push_back(make_pair(i, 0));
    }
  }

  void insertIntoHeap(int job_time) {
    
  }

  int extractMax() {

  }

  void sift_down(int thd, int time) {
    if (time < prio_queue[0].second) {
      
    }
  }

  void sift_up() {

  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    *//*for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }*/
   /* initializeHeap();
    for (int i = 0; i < jobs_.size(); ++i) {
      assigned_workers_[i] = extractMax();
      calc_next_free(assigned_workers_[i]);
    }
 }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};*/

void sift_down(vector<std::pair<long long, long long>> *prio_queue) {
  int i = 0;
  while (1) {
  //for(int i = 0; (2*i + 2 < (prio_queue.size() - 1)); i++) {
      long long smaller_child, left_index, right_index;
      left_index = (2*i + 1 < prio_queue->size()) ? 2*i + 1 : 0;
      right_index = (2*i + 2 < prio_queue->size()) ? 2*i + 2 : 0;
      //cout << "LEFT INDEX: " << left_index << " RIGHT INDEX: " << right_index << " I: " << i << " SIZE: " << prio_queue->size() << endl;
      if (!left_index && !right_index) {
         break;
      }

      if (left_index && right_index) {
         if ((prio_queue->begin() + left_index)->second < (prio_queue->begin() + right_index)->second) {
           smaller_child = left_index;
         } else if ((prio_queue->begin() + left_index)->second > (prio_queue->begin() + right_index)->second) {
           smaller_child = right_index;
         } else {
           if ((prio_queue->begin() + left_index)->first < (prio_queue->begin() + right_index)->first) {
             smaller_child = left_index;
           } else {
             smaller_child = right_index;
           }
         }
      } else if (left_index) {
         smaller_child = left_index;
      } else {
         smaller_child = right_index;
      }
      
      // Compare with parent now
      if ((prio_queue->begin() + i)->second > (prio_queue->begin() + smaller_child)->second) {
        iter_swap(prio_queue->begin() + i, prio_queue->begin() + smaller_child);
        i = smaller_child;
        continue;
      } else if ((prio_queue->begin() + i)->second == (prio_queue->begin() + smaller_child)->second) {
        if ((prio_queue->begin() + i)->first > (prio_queue->begin() + smaller_child)->first) {
          iter_swap(prio_queue->begin() + i, prio_queue->begin() + smaller_child); 
        }
        i = smaller_child;
        continue;
      }
  }

}


std::pair<long long, long long> extractMax(vector<std::pair<long long, long long>> *prio_queue) {
   std::pair<long long, long long> res = make_pair(prio_queue->begin()->first, prio_queue->begin()->second);
   prio_queue->begin()->first = (prio_queue->begin() + prio_queue->size() - 1)->first;
   prio_queue->begin()->second = (prio_queue->begin() + prio_queue->size() - 1)->second;
   prio_queue->erase(prio_queue->begin() + (prio_queue->size() - 1));
   sift_down(prio_queue);
   return res;
}

void sift_up(vector<std::pair<long long, long long>> *prio_queue) {
   long long curr_index = prio_queue->size() - 1;
   long long parent_index;
   while (curr_index) {
      parent_index = (curr_index - 1)/2;
      if ((prio_queue->begin() + parent_index)->second > (prio_queue->begin() + curr_index)->second) {
        iter_swap(prio_queue->begin() + parent_index, prio_queue->begin() + curr_index); 
        curr_index = parent_index;
        continue;
      } else if ((prio_queue->begin() + parent_index)->second == (prio_queue->begin() + curr_index)->second) {
        if ((prio_queue->begin() + parent_index)->first > (prio_queue->begin() + curr_index)->first) {
          iter_swap(prio_queue->begin() + parent_index, prio_queue->begin() + curr_index); 
          curr_index = parent_index;
          continue;
        }
      }
      break;
   }
}

void insert(vector<std::pair<long long, long long>> *prio_queue, std::pair<long long, long long>ele) {
   prio_queue->push_back(ele);
   sift_up(prio_queue);
}


int main() {
  long long num_workers = 0;
  vector<std::pair<long long, long long>> prio_queue;
  vector<int> jobs;
  int m;
  
  std::ios_base::sync_with_stdio(false);
  cin >> num_workers >> m;
  jobs.resize(m);
  for (int i = 0; i < m; ++i) {
    cin >> jobs[i];
  }

  // Initial list of prio queue members
  for (int i = 0; i < num_workers; i++) {
     prio_queue.push_back(make_pair(i, 0));
  }

  //cout << "INSERTED ALL JOBS AND THREADS: " << jobs.size() << endl;

  // Print thread number and start running time and calculate the next running time
  while (!jobs.empty()) {
     std::pair<long long, long long> curr = extractMax(&prio_queue);
     cout << curr.first << " " << curr.second << endl;

     // Calculate next running time for currently executing thread
     int curr_job = jobs[0];
     jobs.erase(jobs.begin());
     insert(&prio_queue, make_pair(curr.first, curr.second + curr_job));
  }
  return 0;
}
