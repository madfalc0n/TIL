# Divide and Conquer

**분할과 정복**이라는 뜻으로 문제를 단번에 알아내기 어려울 경우 부분 부분으로 나누어 푸는 방법론이다. 이는 총 3단계로 나뉘는데 `Divide(분할)`, `Conquer(정복)`, `Combine(결합)`으로 나뉜다.

1. `Divide(분할)`는 하나의 복잡한 문제를 부분적으로 분할한다는  의미이다.
2. `Conquer(정복)`은 부분적으로 분할된 문제들의 답을 도출한다는 의미이다.
3. `Combine(결합)`은 도출된 답들을 모두 결합하여 기존 문제를 해결 한다는 의미이다.



## Divide and Conquer 예시

`f(x)`라는 문제가 있다. 

<img src="images/Divide_and_Conquer/image-20200402021432462.png" alt="image-20200402021432462" style="zoom:80%;" />

1. 해당 문제는 너무 복잡해서 한번에 풀 기 어렵다고 가정하였다. 그리하여 `Divide(분할)`를 통해 문제를 부분 문제로 나눈다. 즉 x를 x1과 x2로 나눈다.

   <img src="images/Divide_and_Conquer/image-20200402021542648.png" alt="image-20200402021542648" style="zoom:80%;" />

2. 여러 부분으로 나누어진 문제의 답을 도출하여  `Conquer(정복)`하였다. 그리하여 `A`와 `B`라는 답을 얻어 내었다.

   <img src="images/Divide_and_Conquer/image-20200402021837198.png" alt="image-20200402021837198" style="zoom:80%;" />

3. `Combine`은 부분 문제들의 답을 합쳐서 기존 문제를 해결한다.

   <img src="images/Divide_and_Conquer/image-20200402022441275.png" alt="image-20200402022441275" style="zoom:80%;" />

이 방법론이 어려운 이유는 해당 문제를 아주 적은단위로 부분 부분 나누어 주어야 한다는 점이다.

<img src="images/Divide_and_Conquer/image-20200402023508723.png" alt="image-20200402023508723" style="zoom:80%;" />

예시로 숫자 n까지의 합을 들 수 있다(1~8의 합을 예시로 들어보자).

<img src="images/Divide_and_Conquer/image-20200402024101665.png" alt="image-20200402024101665" style="zoom:80%;" />

1. `Divide`: 1~8까지의 합을 부분부분 나누어 최소의 부분까지 나눈다.
2. `Conquer`: 각 최소부분에 대한 답을 구한다.
3. `Combine`: 최소부분별로 구한 답을 모두 결합한다. 





## Divide and Conquer 예시 소스코드

1부터 n 까지 합에 대해 Divide and Conquer 방법을 이용하여 문제를 해결해 보았다.

<script src="https://gist.github.com/madfalc0n/1875cc692ea8f5b8e792bb738a1a689e.js"></script>