#include <iostream>
#include <cstdlib>
#include <chrono> 
#include <algorithm>
#include <iostream>
#include <cmath>
#include <time.h>       /* time */
#include <bits/stdc++.h> 
#include <pthread.h>
using namespace std::chrono;
using namespace std; 
int N = 10000;

struct thread_param {
  int *list;
  int n;
};

int serial_max(int list[], int n) {
  int greater = 0;
  for (int i = 0; i < n; i++)
    if (list[i] > greater)
      greater = list[i];
  return greater;
}

void *parallel_max(void* data) {
  struct thread_param *my_data = (struct thread_param *) data; 
  return (void*)serial_max(my_data->list, my_data->n);
}

void parallel(vector<int> numbers) {
  int P = 8;
  int global_greater = 0;
  int n = (int) N/P;
  pthread_t threads[P];
  struct thread_param td[P];
  void *tmp;
  int local, s;
  for (int p = 0; p < P; p++) {
    td[p].list = &numbers[n*p];
    td[p].n = n;
    int rc = pthread_create(&threads[p], NULL, parallel_max, (void *)& td[p]);
    s = pthread_join(threads[p], &tmp);
    local = (int) tmp;
    global_greater = max(global_greater, local);
  }
  printf("mayor:\t%d\n", global_greater);
}

int max(int a, int b) {
  if (b > a) {
    return b;
  }
  return a;
}

int main() {
  vector<int> numbers;
  srand (time(NULL));
  
  
  for (int i=0; i<N; ++i)
    numbers.push_back(rand() % 50000);

  clock_t start, end;

  // start
  start = clock();
  // execute
  // **********************************************************
  printf("mayor: %d\n", serial_max(&numbers[0], N));
  // **********************************************************
  // end
  end = clock();
  double time_taken = double(end - start)/double(CLOCKS_PER_SEC)*1000; 
  cout << "Tiempo serial : " << fixed 
        << time_taken << setprecision(5); 
  cout << " ms " << endl; 

  // start
  start = clock();
  // execute
  // **********************************************************
  parallel(numbers);
  // **********************************************************
  // end
  end = clock();
  time_taken = double(end - start)/double(CLOCKS_PER_SEC)*1000; 
  cout << "Tiempo paralelo : " << fixed 
        << time_taken << setprecision(5); 
  cout << " ms " << endl; 
  return 0;
}