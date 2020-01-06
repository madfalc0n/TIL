# 앙상블

> 1. 여러개의 머신러닝 모델을 연결하여 더 강력한 모델을 만드는 기법. 
> 2. 분류와 회귀 문제의 다양한 데이터셋에서 효과적이라고 입증되었고 많이 씀 
> 3. 랜덤 포레스트random forest와 그래디언트 부스팅gradient boosting 결정 트리는 둘 다 모델을 구성하는 기본 요소로 결정 트리를 사용함



## 배깅(Bootstrap, AGGregatING, Bagging)

> 테스트 데이터 샘플링(Bootstrap) 통해 여러개의 테스트 데이터를 만들고, 각 테스트 데이터를 이용해 여러개의 weak learner 를 만든다. 최종적으로 각 learner 의 예측결과를 평균내서 종합(aggregate)한다.



## 부스팅(Boosting)

> 부스트래핑된 테스트 데이터로 여러개의 weak learner 들을 순차적으로(iterative) 만드는데, i번째 learner 는 i-1 번째 learner 가 잘못 예측한 데이터에 가중치를 좀 더 주어서(boosting) 학습한다. 최종적으로 마지막에 생성된 learner 를 이용하여 예측한다.



