#include <stdio.h>

// 12
// notes:
// 1) two adjacent elements are sorted after each iteration (arr[idx] <= arr[idx + 1]) with old value of idx
// 2) that means that number of inversions are decremented or stays the same because the pair of elements can be already sorted
// 3) when all elements are sorted number of inversions equals 0
// 4) idx changes in range [-1, n - 1]
// 5) when idx reaches -1 the loop ends and array is sorted. but array can be sorted way before idx == -1
// 6) sorted array remains permuation of an input array
// 7) time complexity of this sorting algorithm is O(swaps + skips) where swaps var 
//    is max number of possible inversions (N * (N - 1) / 2) and
//    skips var is max consecutive sorted elements which is N. O((N * (N - 1) / 2) + N) -> O(N^2)
/*
int inversions_old(int *arr, int n) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i < j && arr[i] > arr[j])
				++res;
		}
	}
	return res;
}


int in_order(int *arr, int n) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i < j && arr[i] <= arr[j])
				++res;
		}
	}
	return res;
}

int pow(int base, int power) {
	int result = 1;
	for (int i = 0; i < power; ++i)
		result *= base;
	return result;
}

int order(int n) {
	if (n < 10)
		return 0;
	return 1 + order(n/10);
}

int sorted(int *arr, int start, int end) {
	for (int i = start; i < end - 1; ++i) {
		if (arr[i] > arr[i + 1])
			return 0;
	}
	return 1;
}



int inversion(int *arr, int i, int j) {
	return arr[i] > arr[j];
}

int inversions_for(int *arr, int idx, int n) {
	if (n <= idx) 
		return 0;
	if (inversion(arr, idx, n - 1))
		return 1 + inversions_for(arr, idx, n - 1);
	else 
		return inversions_for(arr, idx, n - 1);
}

int inversions_new(int *arr, int start, int end) {
	if (end <= start)
		return 0;
	else 
		return inversions_for(arr, start, end) + inversions_new(arr, start + 1, end);
}
*/

/*@ predicate inversion{L}(int *arr, integer i, integer j) =
  @	\at(arr[i], L) > \at(arr[j], L);
  @
  */

/*@ axiomatic Inversions_for {
  @	//counts all inversions for arr[idx] element
  @	logic integer inversions_for{L}(int *arr, integer idx, integer n);
  @
  @	axiom inv_for_empty{L}:
  @		\forall int *arr, integer idx, integer n;
  @			n <= idx ==> inversions_for{L}(arr, idx, n) == 0;
  @	axiom inv_for_true{L}:
  @		\forall int *arr, integer idx, integer n;
  @			idx < n && inversion{L}(arr, idx, n - 1)
  @				==> inversions_for{L}(arr, idx, n) == 1 + inversions_for{L}(arr, idx, n - 1);
  @	axiom inv_for_false{L}:
  @		\forall int *arr, integer idx, integer n;
  @			idx < n && !inversion{L}(arr, idx, n - 1)
  @				==> inversions_for{L}(arr, idx, n) == inversions_for{L}(arr, idx, n - 1);
  @
  @ }
 */

/*@ axiomatic Inversions {
  @	//counts all inversions for each element in the array
  @	logic integer inversions{L}(int *arr, integer start, integer end);
  @	
  @//	axiom inv_empty{L}:
  @//		\forall int *arr, integer start, end;
  @//			end <= start ==> inversions{L}(arr, start, end) == 0;
  @//	axiom inv_next{L}:
  @//		\forall int *arr, integer start, end;
  @//			start < end 
  @//		==> inversions{L}(arr, start, end) == inversions_for{L}(arr, start, end) + inversions{L}(arr, start + 1, end);
  @ 	
  @	axiom inv_nonneg{L}:
  @ 		\forall int *arr, integer start, end;
  @			 start < end  ==> inversions{L}(arr, start, end) >= 0;
  @ 	axiom inv_exchange{L1, L2}:
  @             \forall int *a1, *a2, integer idx, n;
  @                          idx < n - 1 && 
  @                          inversion{L1}(a1, idx, idx + 1) &&
  @                          !inversion{L2}(a2, idx, idx + 1) && 
  @	     	          swap{L1, L2}(a1, a2, idx, idx + 1, n) 
  @         ==>           inversions{L2}(a2, 0, n) < inversions{L1}(a1, 0, n);
  @}
  */



/*@ axiomatic Permut {
@ // permut{L1,L2}(t1,t2,n) is true whenever t1[0..n-1] in state L1
@ // is a permutation of t2[0..n-1] in state L2
@ 	predicate permut{L1,L2}(int *t1, int *t2, integer n);
@ 	axiom permut_refl{L}:
@		\forall int *t, integer n; permut{L,L}(t,t,n);
@ 	axiom permut_sym{L1,L2} :
@		\forall int *t1, *t2, integer n;
@			permut{L1,L2}(t1,t2,n) ==> permut{L2,L1}(t2,t1,n) ;
@ 	axiom permut_trans{L1,L2,L3} :
@		\forall int *t1, *t2, *t3, integer n;
@			permut{L1,L2}(t1,t2,n) && permut{L2,L3}(t2,t3,n)
@			==> permut{L1,L3}(t1,t3,n) ;
@ 	axiom permut_exchange{L1,L2} :
@		\forall int *t1, *t2, integer i, j, n;
@	   	swap{L1, L2}(t1, t2, i, j, n)
@		==> permut{L1,L2}(t1,t2,n);
@ }
@*/


/*@ predicate sorted{L}(int *a, integer start, integer n) =
  @	\forall integer i;
  @ 		start <= i < n - 1 ==> a[i] <= a[i + 1];  
  @*/

/*@ predicate swap{L1, L2}(int *a, int *b, integer i, integer j, integer n) =
  @	\at(a[i], L1) == \at(b[j], L2) &&
  @	\at(a[j], L1) == \at(b[i], L2) &&
  @	(\forall integer k;
  @		(0 <= k < n && k != i && k != j ==> \at(a[k], L1) == \at(b[k], L2))); 
*/

/*@ requires n > 0;
  @ requires \valid(arr + (0..n-1));
  @ assigns arr[0..n-1];
  @ ensures sorted{Post}(arr, 0, n);
  @ ensures permut{Pre,Post}(arr,arr, n);
*/



void gnome_rl(int *arr, int n) {
    
    int tmp, idx = n - 1;
    if (n <= 1) return ;


/*@ loop invariant -1 <= idx <= n - 1;
  @ loop invariant permut{Pre, Here}(arr, arr, n);
  @ loop invariant sorted(arr, idx + 1, n);
  @ loop invariant inversions{Here}(arr, 0, n) >= 0;
  @ loop assigns tmp, idx, arr[0..n-1];
  @ loop variant inversions{Here}(arr, 0, n) * 2 + idx;
 */
    while (idx >= 0) {
	if (idx == n - 1) {
            idx--;
        }
	if (arr[idx] <= arr[idx + 1]) {
	    idx--;
	    //@ assert \at(idx, Here)  < \at(idx, LoopCurrent);
	} else {
            tmp = arr[idx];
	    arr[idx] = arr[idx + 1];
            arr[idx + 1] = tmp;
	    //@ assert swap{LoopCurrent, Here}(arr, arr, idx, idx + 1, n);
	    //@ assert inversions{Here}(arr, 0, n) < inversions{LoopCurrent}(arr, 0, n);
            idx++;
        }
    	//@ assert inversions{Here}(arr, 0, n) * 2 + \at(idx, Here) < inversions{LoopCurrent}(arr, 0, n) * 2 + \at(idx, LoopCurrent);
    }
    
}

/*
int main(void) {
 	int arr[] = {9, 3, 7, 6, 5, 4};
	int size = sizeof(arr) / sizeof(int);
	printf("inv_old: %d\n", inversions_old(arr, size));
	printf("inv_new: %d\n", inversions_new(arr, 0, size));
	//	gnome_rl(arr, size);
	//gnome_lr(arr, size);
	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}*/
