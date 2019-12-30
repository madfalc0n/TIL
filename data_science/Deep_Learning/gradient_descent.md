## Gradient descent(경사 하강법)

> 1. 미분 기울기를 이용하는 **경사 하강법(gradient decent)**은 이차 함수 그래프에서 오차를 비교하여 가장 **작은 방향으로 이동시키는 방법**
>
> 2. 기본 개념은 함수의 [기울기](https://ko.wikipedia.org/wiki/기울기_(벡터))(경사)를 구하여 기울기가 낮은 쪽으로 계속 이동시켜서 [극값](https://ko.wikipedia.org/wiki/극값)에 이를 때까지 반복시키는 것

![gradient_descent](C:/Users/myounghwan/TIL/data_science/Machine_Learning/images/gradient_descent.png)

#### 평가 및 장단점

- 경사 하강법은 모든 차원과 모든 공간에서의 적용이 가능하다. 심지어 무한 차원상에서도 쓰일 수 있다. (이 경우 해당 차원이 만들어내는 공간을 [함수 공간](https://ko.wikipedia.org/wiki/함수_공간)이라고 한다.)

- 정확성을 위해서 [극값](https://ko.wikipedia.org/wiki/극값)으로 이동함에 있어 매우 많은 단계를 거쳐야하며, 주어진 함수에서의 [곡률](https://ko.wikipedia.org/wiki/곡률)에 따라서 거의 같은 위치에서 시작했음에도 불구하고 완전히 다른 결과로 이어질 수도 있다.
  - 함수 최적화 방법인 경사하강법 알고리즘은 **그리디 접근방식**을 사용한다. 이것은 즉 **휴리스틱(heuristic)**한 탐색을 하기 때문에 **국소 최적해(Local Minimum)**을 가질 위험이 있다.
  - 간단하게 예를 들어보자면,  어떤 사람이 등산을 할 때 정상을 향해서 등산을 하게 되는데 정상인 줄 알고 올라와봤더니 옆에 더 높은 봉우리가 있는 것이다.
  - 이와 같이 정상이 어디인지 모르고 일단 사람이 판단했을 때 최적의 길로 올라 갔을 때 휴리스틱한 탐색을 한다하고 사람은 봉우리에 올라갔을 때 주변을 탐색할 수 있지만
  - 기계는 그러지 못한다. 따라서 그를 해결하기 위한 매커니즘으로 **Convex Function**을 활용한다. 이를 활용하면 어디서 시작하든지 간에 우리가 원하는 지점에 갈 수 있는 것이다. 
#### 실습

1. [Gradient_descent]( https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/Deep_Learning/20191230/1.1_gradient_descent.ipynb)
2. [Gradient_descent_Logistic_regression](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/Deep_Learning/20191230/1.2_gradient_descent_logistic_regression.ipynb)

#### 참고

- 참고1 : [경사하강법_1](https://ko.wikipedia.org/wiki/%EA%B2%BD%EC%82%AC_%ED%95%98%EA%B0%95%EB%B2%95)
- 참고2 : [경사하강법_2](https://gdyoon.tistory.com/9)
- 참고3 : [딥러닝_경사하강종류 ](https://wikidocs.net/36033)
