# Kalman filter



## 0. 학습목표

1. 칼만필터가 무엇인가? 왜 필요한가?
2. 칼만필터의 종류와 각각 언제 적용해야할까?
   - Bayesian Filters
   - One-dimensional Kalman Filters
   - Multivariate Kalman Filters
   - Unscented Kalman Filters
   - Extended Kalman Filters
   - Particle Filters





## 1. 칼만필터가 무엇인가? 왜 필요한가?

우리가 살고있는 세상은 잡음으로 꽉찬 세상이다. 무슨 의미냐면 우리는 무언가를 측정할 때, 측정할 때마다 값이 다를 수 있음을 의미한다. 즉 이는 측정 값이 올바른지 100% 확신하지 못한다는 뜻이며 우리가 살고 있는 본질이다.

하지만 우리는 정확한 값 대신 수학적 방법을 사용하여 어느정도 해결이 가능하다. 즉 잡음을 줄일 수 있다는 뜻이다. 해결방법이 바로 `칼만 필터`이며 로봇 공학에서 많이 쓰인다.

예를 들어, 로봇을 향해 다가오는 물체가 갑자기 방향을 바꾸는 것을 측정할 때 물체가 정말로 변했는지 ? 아니면 센서에 잡음이 있어서 오류가 생겼을 수 있다. 이러한 문제를 해결하기 위해 필요하다. 



## 2. 칼만필터의 종류와 각각 언제 적용해야 할까?



### 2-1. Bayesian Filters

#### 2-1-0. summary

아래 항목들을 배우게 될 것

1. Bayes 필터의 구성요소
2. 센서잡음이  예측에 미치는 영향
3. 불확실성하의 로봇 동작
4. 베이지안 필터링의 재귀적 특성
5. 1차원 이산적 베이지안 필터를 구현하는 방법



#### 2-1-1. 베이지안 필터란?

과거 값을 사용하여 정확한 추정치를 제공하기 위한 추정 알고리즘이다. 불확실성 하에서 추정값을 생성하기 위해 과거 정보를 고려한다는 점에서 베이지안 통계의 개념과 관련이 되어있다.