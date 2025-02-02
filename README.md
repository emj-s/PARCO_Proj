
## i) Screenshot of program output with execution time for all cases

![](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

## ii) Comparative table of execution times

### Avg time for size n = 1048576 (in ms)
| Language | Trial 1 | Trial 2 | % increase |
| --- | --- | --- | --- | 
| c | 2.221893 ms |  2.230917 ms |  -0.41% |
| x86-64 | 0.759703 ms | 0.646217 ms | 14.94% | 
| SIMD XMM | 0.476223 ms | 0.517763 ms | -8.72% |
| SIMD YMM | 0.475753 ms | 0.479500 ms | -0.79% |

* Majority of % are a decrease in time. This could be due to human error or dependent on the user's computer specs. Furtuher testing may be needed for this. Assembly language showing its speed over C language.

### Avg time for size n = 67108864 (in ms)
| Language | Trial 1 | Trial 2 | % increase |
| --- | --- | --- | --- | 
| c | 146.926203 ms |  143.122330 ms | 2.59% |
| x86-64 | 52.568163 ms | 49.703820 mss | 5.45% |
| SIMD XMM | 39.738370 ms | 38.419083 ms | 3.32% |
| SIMD YMM | 39.581590 ms | 38.706023 ms | 2.21% |

* An increase of about 2-5% can be seen being more efficient and faster compared to the C code version. Baded on time it is visible that C language is the lowest and XMM regiter being the lastest.

### Avg time for size n = 268435456 (in ms)
| Language | Trial 1 | Trial 2 | % increase |
| --- | --- | --- | --- | 
| c | 568.411570 ms |  580.188820 ms | -2.07% |
| x86-64 | 214.798213 ms | 199.011323 ms | 7.35% |
| SIMD XMM | 183.867480 ms | 151.913040 ms |17.38%|
| SIMD YMM | 165.358517 ms | 151.990617 ms | 8.08%|

*  This result has the greatest increase % from testing at 17%%. An observation that can be made is that at trial 1 the ymm beats out the xmm regisrer however, at trial 2 the ymm register is marginally worse than the previous.

## iii-vi) Screenshot of program output wih correctness check

![C](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

![x86-64](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

![SIMD XMM](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

![SIMD YMM](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

## vii) Discussion 

There were a lot of problems there were encountered before the final version of the program. The inital version had an error the group had difficulty in problem solving, hence we made the decision to change our code from the start. Thankfully this was a good decison and we were able to make a functional dot product program. We are unsure if we followed with a methodology but we were able to create a product we are happy with. 

Following the results from ii, the times of C compared to assembly are noticably slower meaning assembly is able to execute the code faster. Taking the the second table for example. C at 143.122 ms is slower compared to the time of ymm register assembly. This speed increase could be due to the Single Instruction Multiple Data structure of xmm and ymm registers. These registers can hold multiple data within a single register. Because of this, we can perform operations such as addition or multiplication faster due to their access to AVX2 instructions such as movdqu which moves all data to a xmm or ymm register (as many as it can). The conclusion is that SIMD AVX2 programs are faster than compared to C functions. However, there are parts that aren't a increase such as in table 1. This could be due to human error or something else. Further testing would be needed.

Probably an AHA moment was when we finally got our program to work. The group collectively was happy that we were able to output an answer. Also problem solving took too long we had to change our program from the bottom up. Other than those, nothing else notable.

  
