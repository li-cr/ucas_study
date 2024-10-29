### Question1

The Nine Links is a traditional intellectual game originating from China, featuring nine circular rings threaded onto a "sword," which are interlinked with one another.
In the traditional Nine Links, the $ k $th ring ($ k \geq 2 $) can either be placed on the sword (denoted as $ 1 $) or removed from it (denoted as $ 0 $), and this can happen only if the $ k-1 $th ring is on the sword and all previous rings are off.
Notably, the first ring can move freely.

In this problem, we will discuss a more general case, although this simple Nine Links may not necessarily be feasible in a physical sense.

A simple Nine Links can be viewed as two binary strings: a rule string $ s $ and a state string $ t $, with the condition $ |s| = |t| - 1 $.
Here, $ t_i = 1 $ indicates that the $ i $th ring is placed on the sword, while $ t_i = 0 $ indicates that it is removed.
The string $ s $ remains constant throughout the game, while $ t $ changes one position at a time (either from $ 0 $ to $ 1 $ or from $ 1 $ to $ 0 $).
The simple Nine Links is removed when all $ t_i $ are $ 0 $, and it is placed on when all $ t_i $ are $ 1 $.

In the simple Nine Links, $ t_i $ can change only if $ t_{1 \sim i-1} $ is a **suffix** of $ s $.
It can be observed that the traditional Nine Links is a special case where $ s $ is $ 00...01 $.

Given a string $ s $, the task is to determine the minimum number of steps required to transition from the removed state to the placed state.
The answer should be taken modulo $ 10^9 + 7 $.

Input:  

1. An integer $ n $, representing the length of $ s $. **Note that this is not the number of rings.**  
2. A binary string $ s $.

Output:  
One line containing an integer that represents the value of the answer modulo $ 10^9 + 7 $.

### Question2

Given a $ 01 $ sequence $\{a_n\} $ of length $ n $, you need to find the minimum number of operations required to transform the sequence into a "good sequence".

A "good sequence" is defined as follows:  

1. There exist $ k $ intervals $ \{(l_k, r_k)\} $, where within each interval all values are $1$, i.e.,
$$ \forall i\in[1,n],a_i=1\text{ if and only if }\exists j\in[1,k],i\in[l_j,r_j] $$
2. The sequence is considered "good" if and only if the lengths of these intervals are strictly increasing from left to right, meaning:
$$ r_i-l_i<r_{i+1}-l_{i+1},\forall i\in[1,k-1] $$

You are allowed to perform the following operation: select two different positions $ i $ and $ j $ ($i \neq j$), and swap the values $ a_i$ and $ a_j $.

Your task is to find the minimum number of operations needed to transform the sequence $\{a_n\}$ into a "good sequence."

Input:  
A single line contains a $01$ sequence $\{a_n\}$ of length $n$ ($ n\leq 800 $).

Output:  
The minimum number of swaps required to transform the sequence into a "good sequence".

### Question3

You are given an array $a_1,a_2,...,a_n$ of positive integers.
You can color some elements of the array red, but there cannot be two adjacent red elements.

Your score is the maximum value of a red element, plus the minimum value of a red element, plus the number of red elements.
Find the maximum score you can get.

Input:  
Each test contains multiple test cases.
The first line contains the number of test cases $t (1\leq t\leq 10^{4})$.
The description of the test cases follows.  
For each test case:  

1. The first line contains a single integer $n (1\leq n\leq 2\times 10^5)$ -- the length of the array.  
2. The second line contains $n$ integers $a_1,a_2,...,a_n (1\leq a_i\leq 10^9)$ -- the given array.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\times 10^5$.

Output:  
For each test case, output a single integer: the maximum possible score you can get after coloring some elements red according to the statement.
