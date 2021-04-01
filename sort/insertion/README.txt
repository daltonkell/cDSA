Insertion Sort
==============

Insertion sort is almost as simple as selection sort. The item
that's currently being considered is placed in between the smaller
and larger elements already considered. Larger elements are moved
(respectively) one position to the right, and the element in question
is inserted into the empty spot.

IMPORTANT: Insertion sort doesn't necessarily work for all inputs!
Why is this? When the value being check is the smallest element of
the array, the algorithm will attempt to go past the lower bound of
the array in order to set it in the "correct" position. For this reason,
insertion sort often uses a "sentinel" value at the beginning of the
array which is at least as small as the smallest element in the array,
which will guarantee the the lower bound is never exceeded. It's possible
to use a different check, like checking j>1, but this would be evaluated
for each element in the while loop, a tradeoff you will consider.
