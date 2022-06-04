# MTU-CS4411-OSHW4-
Quicksort with Unix Shared Memory

Program Specification
Write two programs main and compute. The former does not require any command line arguments and the latter takes at least two command line arguments Left and Right. The job for program main to do consists of the following:

1. Program main reads an input array a[ ] of distinct integers into a shared memory. Let the number of elements of this array be n.
2. main prints out the input array.
3. Then, main creates a child process to run program compute using the execvp() system call and passes the assigned Left, Right and other needed information to program compute. Initially, Left and Right are 0 and n-1, respectively.
4. Program main waits for the completion of its only child process and then prints out the sorted result.

The job for program compute to do is the following:

1. When program compute runs, it receives the left and right section indices Left and Right from its command line arguments.
2. Then, it partitions the array section a[Left..Right] into two at element a[M]. See your data structures and/or algorithms textbooks for this partitioning procedure. After the partition is obtained, two child processes are created, each of which runs compute using system call execvp. The first child receives Left and M-1, while the second receives M+1 and Right. The parent then waits until both child processes complete their job.
3. After this, program compute exits.


Input and Output
The input to program main is in a file with the following format:
        n           <--------------------- the number of elements of array a[ ]
        a[0]  a[1]  a[2] ..... a[n-1] <--- elements of array a[ ]
You can assume the following:
- The value of n is an integer larger than or equal to 5.
- The values for array a[ ] are distinct integers.

The following shows a possible program output:

      Quicksort with multiple processes:

      *** MAIN: shared memory key = 1627930027
      *** MAIN: shared memory created
      *** MAIN: shared memory attached and is ready to use

      Input array has 8 elements:
          4  7  2  9  3  5  8  6

      *** MAIN: about to spawn processes
         ### PROC(4913): entering with a[0..7]
             ..........
         ### PROC(3717): entering with a[3..6]
             XX  XX  XX  XX <---------------------- elements of a[3] to a[6]
             ..........
         ### PROC(3717): partition position is a[4] = XX 
             ..........
         ### PROC(3717): section a[3..6] sorted
             YY  YY  YY  YY
             ..........
         ### PROC(3717): exits 
             ..........
      *** MAIN: sorted array:
           2  3  4  5  6  7  8
      *** MAIN: shared memory successfully detached
      *** MAIN: shared memory successfully removed
      
The output lines from main always starts with *** MAIN:. Program main first prints out the shared memory key being used, followed by messages indicating the shared memory being created and attached. Then, main prints out the input array.

Messages from a child process have an indentation of three spaces. The first message below indicates that the child process with process ID 3717 receives Left = 3 and Right = 6, and the current content of this array section. The second message below shows the partition element a[4] and its value. The third message shows the sorted array section of a[3..6]. Finally, the fourth message indicates that this process exits.

     ### PROC(3717): entering with a[3..6]
         XX  XX  XX  XX <---------------------- elements of a[3] to a[6]
         ..........
     ### PROC(3717): partition position is a[4] = XX 
         ..........
     ### PROC(3717): section a[3..6] sorted
         YY  YY  YY  YY
         ..........
     ### PROC(3717): exits 
