# correlation coefficient(상관계수)

> 2개 이상의 양적인 변수간 관계가 유의한지 확인하는 방법
>
> 인터넷 이용 횟수와 수학 성적간의 관계, 독서실 이용률과 스트레스 지수 간의 관계를 예로 들수 있다.
>
> 파이썬에서는 pearson correlation coefficient를 구할 수 있는 corr(), corrwith()함수를 제공함

## 정의

1. r = x,y가 함께 변하는 정도
2. x,y가 각각 변하는 정도

## 해석 방법

- r 값은 x와 y가 완전히 동일하면 +1, 전혀 다르면 0, 반대방향으로 완전히 동일하면 -1의 값을 갖는다.

![correlation_1](images/correlation_1.PNG)



### 파이썬에서 사용방법

`df.corr()` 적용 

![correlation_2](images/correlation_2.PNG)



이런식으로 나온다...



