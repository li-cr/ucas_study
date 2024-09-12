### 1. Longest Balanced Substring.

1. 首先，对一个区间来说，如果有个字母没有对应的大写或者小写字母，那么可以以这些字母为切割点分成若干段。
  <br>  例如： (aAzBbzCcDdzUu 中字母z不合法。将其分割成aA Bb CcDd Uu)。<br>
  那么可以这样一直分割的做。 
2. 判断一个区间是否合法：扫描区间，
3. 时间复杂度： <br>
  $由于每分割1次，其字母集的个数-2,最多进行26次分割，其中每次最大复杂度为O(n)。\\
    \because T(n, m) = \sum{T(len_i, m_i)}。\\
    \because T(n+1,m) > T(n,m) 
    \quad \sum{len_i} < n
    \quad  m_i < m
    \quad T(n,1) \leqslant n \quad T(n, 2) = n \\
    \therefore T(n, m) \leqslant \sum{T(len_i,m-2)} + n \leqslant mn = 26n \quad {\sum{len_i} = n} \\
    \therefore O(n) = n$  
<!-- $T(n) = \displaystyle\sum{T(len_i)}+n。其中由于每分割1次，其字母集的个数-1$ -->
4. 空间复杂度：

### 2. Cutting Bamboo Poles

1. 
2. 
3. 
4. 

### 3. Multiple Calculations

1. 
2. 
3. 
4. 

### 4. N-sum

1. 将B数组构造成 $F(x, 1) = \sum{x^{b[i]}}。\\ F(x, n)=F(x,1)^n, ans=F(x,n)中x^m的系数。其中可以用NTT优化+NTT后将x前的系数变为bool值$
2. 初始化$G(x) = 1$<br>从高到低遍历n的二进制<br>$为1时G(x) = G(x)*G(x)*F(x, 1);为0时G(x) = G(x)*G(x)$
```cpp
    G(x) = 1, F(x, 1) = init
    for i in range (high_position, 0):
        G(x) = NTT(G(x), G(x))
        if(n>>i&1)
            G(x) = NTT(G(x), F(x, 1))
        for i in G(x): # 改变G(x)每项的系数为bool值。
            G(x)[i] = G(x)[i] > 0
```
3. 时间复杂度：<br> 
  $n次多项式相乘NTT时间复杂度: O(n\log{n})\\
  \begin{aligned} 
  T(n) &\leqslant \sum_{i=0}^{high\_position}{2(\texttt{n>>i})*n\log(\texttt{n>>i})} \\
   &\leqslant 2n\log(n)\sum_{i=0}^{high\_position}{\texttt{n>>i}} \\
   &\leqslant 2n\log(n)*(2n)\\
   \therefore O(n) &= n^2\log(n)
   \end{aligned}
   $
4. 空间复杂度:<br>
   $其中间暂存结果O(n^2)$


### 5. Ex.  Unary Cubic Equation

1. 
2. 
3. 
4. 

### 6. Ex.  Distance

1. 
2. 
3. 
4. 

