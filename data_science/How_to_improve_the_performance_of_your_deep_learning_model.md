# 딥러닝 모델의 성능을 향상시키는 방법



1. 과적합(overfitting)을 피하자
   
   - 옷 입는 것을 예시로 언더피팅은 
   
2. 정규화 진행

   - Batch Normalization 을 추가할 수록 loss 및 val_loss 가 stable 하게 낮아진다.

     - 비선형 함수에 적용한다.

     - 적용은 activation 전에 한다.

       ```python
       
       
       model.add(Dense(50, input_shape = (784, )))
       model.add(BatchNormalization())       
       model.add(Activation('sigmoid'))    
           
       ```

     - fit 하고나서 scale을 복귀 시켜주어야 함, 모든 층마다 적용해야함



2. Dropout

   - 비율만큼 학습을 drop 한다.(weight를 비율만큼 0으로 만들어버림)

   - 적용은 activation  후에 한다.
   - 효과가 사실상 보기가 힘들다
   - 모든 층에 할 필요는 없다.
   - 비율은 0.5이상해야 신경망이 층별로 끊긴것 처럼 효과가 있다.
   - 앙상블
     - voting
       - 하드방식(다수결의 원칙, 각 분류기별 가중치를 똑같이 설정)
         - 약한 분류기 끼리 모아서 다수결의 원칙에 의해 강한 분류기를 만든다(앙상블)
         - 대표가 바로 얼굴검출기
       - 소프트방식(각 분류기별 가중치를 다르게 설정)
         - 

