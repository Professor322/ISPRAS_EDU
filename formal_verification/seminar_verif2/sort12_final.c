
/*@ predicate inversion{L}(int *arr, integer i, integer j) =
  @	\at(arr[i], L) > \at(arr[j], L);
  @
  */
/*@ axiomatic Inversions {
  @	//counts all inversions for each element in the array
  @	logic integer inversions{L}(int *arr, integer start, integer end);
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

