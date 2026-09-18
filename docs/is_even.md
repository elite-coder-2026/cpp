given a number n check wither it is even or odd. return true for even and fasle if odd.

### naive approach
we check if  the remainder when divided by 2. if the remainder is 0, the number is even,
it is odd. for instance, when we divide 13 by 2, we get a remaining value of 1 and when 
we divide 14 by 2, we get a remainder of 0

```c++
bool isEven(int n) {
    int rem = n % 2;
    if (rem == 0) {
        return true;
    } else {
        return false;
    }
}
```
