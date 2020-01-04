# LGBM- Light Gradient Boosting algorithm

> 트리 기반 학습 알고리즘을 사용하는 Gradient boosting 프레임 워크.



### 장점

- 정확성이 높음
- 대용량 데이터를 처리할 수 있으며 다른 알고리즘에 비해 적은 메모리를 사용함
- GPU 학습도 지원하므로 데이터 사이언스 분야에서 널리 사용하고 있음.



### 다른 트리 기반 알고리즘들과의 차이점

- 다른 트리 기반 알고리즘은 나무를 가로로 자르지만, LGBM은 나무를 세로로 자름
- 다른 트리 기반 알고리즘은 레벨(level-wise)을 자라고 LGBM은 나무를 잎(Leaf-wise)처럼 자람
- 최대 델타 손실이 있는 잎을 선택하여 자람.
- 동일한 리프를 성장시킬 때 Leaf-wise 가 level-wise 보다 더 많은 손실을 줄일 수 있음

#### 		1. Leaf_wise 형식(LGBM)

<img src="./images/leaf-wise.png" alt="leaf_wise" style="zoom:50%;" />

#### 		2. Level_wise 형식(다른 트리 기반 알고리즘)

<img src="./images/level-wise.png" alt="level_wise" style="zoom:50%;" />



### 주의사항

- LGBM은 Over-fitting에 민감하여 작은 데이터에서는 사용하지 않는 것이 좋다.
- 대략 행 수가 10,000 개 이상인 데이터에서만 사용하는 것을 권장
- 100개가 넘는 파라미터가 있으나 일부 파라미터만 조정하여 강력한 알고리즘을 만들 수 있다.



### 파라미터 조정

1. **num_leaves** : Tree 모델의 복잡성을 제어하는 파라미터, 이론적으로 num_leaves =< 2^(max_depth) 이어야 한다. 만약 이를 어길 시 over-fitting이 된다.
2. **min_data_in_leaf** : Leaf-wise 트리에서 Over-fitting을 예방하는 가장 중요한 파라미터, 값을 크게 설정할 경우 트리가 깊게 자라는것을 피할 수 있으나 Under-fitting이 될 수 있으며 큰 데이터의 경우 수백에서 수천이 적당하다.
3. **max_depth** : 트리의 최대 깊이를 설정하며 과적합이라고 생각될 경우 값을 낮춘다.
4. **feature_fraction** : 부스팅 (나중에 논의)이 임의의 포리스트 일 때 사용됩니다. 0.8 기능 비율은 LightGBM이 트리를 구축 할 때마다 반복마다 매개 변수의 80 %를 임의로 선택 함을 의미합니다.
5. **bagging_fraction** : 각 반복에 사용될 데이터의 비율을 지정하며 일반적으로 훈련 속도를 높이고 과적 합을 피하는 데 사용됩니다.
6. **early_stopping_round** :이 매개 변수를 사용하면 분석 속도를 높일 수 있습니다. 마지막 early_stopping_round 라운드에서 하나의 검증 데이터 메트릭 중 하나가 개선되지 않으면 모델이 교육을 중단합니다. 과도한 반복이 줄어 듭니다.
7. 람다 : 람다는 정규화를 지정합니다. 일반적인 값의 범위는 0에서 1입니다.
8. **min_gain_to_split** :이 파라미터는 분할을위한 최소 게인을 설명합니다. 트리에서 유용한 스플릿 수를 제어하는 데 사용할 수 있습니다.
9. **max_cat_group** : 범주 수가 많을 때 분리 점을 찾는 것이 쉽게 과적 합합니다. 따라서 LightGBM은이를 'max_cat_group'그룹으로 병합하고 그룹 경계에서 분리 점을 찾습니다 (기본값 : 64).



### 상황별 파라미터 조정방법

#### 1. For Faster Speed

- Use bagging by setting bagging_fraction and bagging_freq
- Use feature sub-sampling by setting feature_fraction
- Use small max_bin
- Use save_binary to speed up data loading in future learning
- Use parallel learning, refer to Parallel Learning Guide

#### 2 For Better Accuracy

- Use large max_bin (may be slower)
- Use small learning_rate with large num_iterations
- Use large num_leaves (may ca- Use over-fitting)
- Use bigger training data
- Try dart

#### 3 Deal with Over-fitting

- Use small max_bin
- Use small num_leaves
- Use min_data_in_leaf and min_sum_hessian_in_leaf
- Use bagging by set bagging_fraction and bagging_freq
- Use feature sub-sampling by set feature_fraction
- Use bigger training data
- Try lambda_l1, lambda_l2 and min_gain_to_split for regularization
- Try max_depth to avoid growing deep tree



### 느낀점

- 파라미터를 통해 accuracy 조정을 하지만 한계가 있다...
- accuracy를 높이기 위해 파라미터를 올려도 예측력이 떨어질 수 있다.



### 참고

- https://ko.raw3h.net/page/what-is-lightgbm-how-to-implement-it-how-to-fine-tune-the-parameters-5295f7/
- https://lightgbm.readthedocs.io/en/latest/Parameters-Tuning.html