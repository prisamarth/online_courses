#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> 

using std::vector;
using std::cin;
using std::cout;
using std::swap;

class Worker {
  private:
     int index;
     long long next_free_time;
  public:
     Worker():index(0),next_free_time(0) {}

     Worker(int i,long long n):index(i),next_free_time(n) {}

     void setIndex(int i) {
	     index = i;
     }

     int getIndex() const {
	     return index;
     }

     void setNextFreeTime(long long n) {
	     next_free_time = n;
     }

     long long getNextFreeTime() const {
	     return next_free_time;
     }

     void print() const {
	     cout << "Index:" << index << " Next free time:" << next_free_time << std::endl;
     }

     friend bool operator<(const Worker &a,const Worker &b);
     friend bool operator>(const Worker &a,const Worker &b);
};

bool operator<(const Worker &a,const Worker &b) {
	if (a.next_free_time < b.next_free_time)
		return true;
	else if(a.next_free_time == b.next_free_time) {
		if (a.index < b.index)
			return true;
	}
	return false;
}

bool operator>(const Worker &a,const Worker &b) {
	if (a.next_free_time > b.next_free_time)
		return true;
	else if(a.next_free_time == b.next_free_time) {
		if (a.index > b.index)
			return true;
	}
	return false;
}


template <class T>
class MinQueue {
  private:
    vector<T> queue_;
    int queue_size_;

  public:
    MinQueue():queue_size_(0) 
    { }

    void resize(int size) {
      queue_.resize(size);
    }

    int Parent(int index) const {
      div_t div_result = div((index - 1),2);
      return div_result.quot;
    }

    int LeftChild(int index) const {
      return ((index * 2) + 1);
    }

    int RightChild(int index) const {
      return ((index * 2) + 2);
    }

    void SiftUp(int index) {
    	if (index > queue_size_)
	  return;
	while (index > 0 && (queue_[index] < queue_[Parent(index)])) {
		swap(queue_[index],queue_[Parent(index)]);
		index = Parent(index);
	}
    }

    bool isEmpty() {
	    return (queue_size_ < 1);
    }

    void SiftDown(int index);
 
    bool Insert(T value);

    T GetMin();

    void print() {
	    cout << "Queue size:" << queue_size_ << std::endl;
	    for(int i = 0; i < queue_size_; ++i) {
		queue_[i].print();
	    }
    }
};

template <class T>
void MinQueue<T>::SiftDown(int index) {
       if(index < queue_size_) {
           int minindex = index;
	   if((LeftChild(index) < queue_size_) && (queue_[LeftChild(index)] < queue_[minindex]))
		   minindex = LeftChild(index);
	   if((RightChild(index) < queue_size_) && (queue_[RightChild(index)] < queue_[minindex]))
		  minindex = RightChild(index);
	   if(minindex != index) {
	   	swap(queue_[index],queue_[minindex]);
		SiftDown(minindex);
	   } 
          
       }
 }

template<class T>
bool MinQueue<T>::Insert(T value) {
	if ((queue_size_ + 1) > queue_.size())
		return false;
	queue_[queue_size_] = value;
	SiftUp(queue_size_);
	queue_size_++;
	return true;
}

template<class T>
T MinQueue<T>::GetMin() {
	T result = queue_[0];
	queue_[0] = queue_[(queue_size_ - 1)];
	queue_size_--;
	SiftDown(0);
	return result;
}

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

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

  void PrintJobs() {
	  for (int i = 0; i < jobs_.size(); ++i) 
		  cout << jobs_[i];
	  cout << std::endl;
  }
  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    /*
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
    */
	  MinQueue<Worker> queue;
	  queue.resize(num_workers_);
          assigned_workers_.resize(jobs_.size());
          start_times_.resize(jobs_.size());

	  for(int i = 0; i < num_workers_; ++i) {
	  	queue.Insert(Worker(i,0));
	  }
  	  for(int i = 0; i < jobs_.size(); ++i) {
		  Worker w = queue.GetMin();
		  assigned_workers_[i] = w.getIndex();
		  start_times_[i] = w.getNextFreeTime();

		  long long duration = w.getNextFreeTime() + jobs_[i];
		  w.setNextFreeTime(duration);
		  queue.Insert(w);
		  
	  }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
