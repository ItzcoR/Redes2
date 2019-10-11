#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <time.h>
int arr*;

void swap(int ind1, int ind2/* */) {

  int temp = arr[ind1];
  arr[ind1]=arr[ind2];
  arr[ind2]=temp;
}
void* pse_sort(void * arg) {
  int * indexes=(int *)arg;
  int b_index = indexes[0];
  int e_index = indexes[1];
  //int piv_value = arr[piv_index];
  //int left = b_index, right =e_index -1;
  while (1/* condition */) {
    //left
    while (1) {
      if (arr[left]>pivot) {
        break;
        /* code */
      }

      left++;/*  */
      if (left > e_index) {
        left--;
        break;/* code */

      }
    }

    /* right */
    if (arr[right]<=pivot) {
      break;
    }
    right--;
    if (right < b_index) {
      right++;
      break;

    }
    if (left >= right) {
      swap(left, e_index);
      break;
    }
    swap(left, right);
    left++;right--;
  }
  //Threads
  pthread_t t1,t2;
  int newb1 = b_index, newe1 = left -1;
  int newb2 = left+1, newe1 = e_index;
  int vals1 [2]= {newb1, newe1};
  int vals2 [2]= {newb2, newe2};
  if (newb1z newe1) {
    pthread_create(&t1,NULL, pseudo_sort, (void*)vals1);
  }
  if (newb2<newe2) {
    pthread_create(&t2,NULL, pseudo_sort, (void*)vals1);
  }
  if (newb1z newe1) {
    pthread_join(t1,NULL);
  }
  if (newb2<newe2) {
    pthread_join(t2,NULL);
  }
  pthread_exit(NULL);
}
/*void pse_sort(int piv_index, int b_index, int e_index/* arguments ) {
   Hay que poner un apuntador al inicio y al final,
  si el pivote es uno de esos se cambia al inmediato siguiente o anterior segun el caso
  int piv_value = arr[piv_index];
  int left = b_index, right =e_index -1;
  while (1) {
    //left
    while (1) {
      if (arr[left]>pivot) {
        break;

      }

      left++;/*
      if (left > e_index) {
        left--;
        break;/* code

      }
    }

    // right
    if (arr[right]<=pivot) {
      break;
    }
    right--;
    if (right < b_index) {
      right++;
      break;

    }
    if (left >= right) {
      swap(left, e_index);
      break;
    }
    swap(left, right);
    left++;right--;
  }
  //Threads
  pthread_t t1,t2;
  int newb1 = b_index, newe1 = left -1;
  int newb2 = right+1, newe1 = e_index;
}*/

int main(int argc, char const *argv[]) {
  int n;
  //srand(time(NULL))
  printf("Tamaño del arreglo\n" );
  scanf("%d",&n );
  arr=(int *)malloc(sizeof(int)*n);
  for (i = 0; i < n; i++) {
    arr[i] = rand()%100+1
  }
  int piv=n-1;

  return 0;
}
