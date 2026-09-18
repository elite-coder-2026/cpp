the problem can be solved using the two pointer technique. we can maintain two
pointers, left and right and calculate their sum 

- if s = target, return left and right
- if s < target, then we need to increase sum s, so we incrememnt left by 1
- if s > target, then we decress s by one
#### how it works
---
- we need to initialize two pointer as left and right with the position at
the beginning and at the end of the array.
- if the sum equals to the target value, return the index of the two elements
- if the some comes out to be less than the target, move the right pointer to the left to decrease th sum
- repeat the following steps both points meet
