/*
* @@name:       target_ptr_map_4.c
* @@type:       C
* @@compilable: yes
* @@linkable:   no
* @@expect:     success
* @@version:	omp_5.1
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void do_work(int *ptr, const int size);

int main() 
{
   const int n = 1000;
   const int buf_size = sizeof(int) * n;
   const int dev = omp_get_default_device();

   int *ptr = (int *) malloc(buf_size); // possibly compiled on 
                                        // Unified Shared Memory system
   const int accessible = omp_target_is_accessible(ptr, buf_size, dev);

   #pragma omp metadirective \
      when(user={condition(accessible)}: target firstprivate(ptr) ) \
      default(                           target map(ptr[:n])      )
   {
      do_work(ptr, n);
   } 

   free(ptr);
   return 0;
}
