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

void parallel(vector<int> numbers, int N) {
  int P = 4;
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
  double time_taken;
  clock_t start, end;
  for (int N = 1; N < 11; N +=1) {
    vector<int> numbers;
    srand (time(NULL));


    for (int i=0; i<N; ++i)
      numbers.push_back(rand() % 50000);

    printf("%d\n", numbers);

    // start
    start = clock();
    // execute
    // **********************************************************
    parallel(numbers, N);
    // **********************************************************
    // end

    end = clock();
    time_taken = double(end - start)/double(CLOCKS_PER_SEC)*1000; 
    cout << "Tiempo n = " << N <<": " << fixed 
          << time_taken << setprecision(5); 
    cout << " ms " << endl; 
  }
  return 0;
}