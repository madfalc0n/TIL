# Keras_callback Function

## EarlyStopping

- 정해진 epochs 내에 모델이 향상되지 않으면 훈련을 중단

  ```python
  keras.callbacks.callbacks.EarlyStopping(monitor='val_loss', min_delta=0, patience=0, verbose=0, mode='auto', baseline=None, restore_best_weights=False)
  ```

- **monitor**: 모니터 할 요소? 

- **min_delta**: 

  - minimum change in the monitored quantity to qualify as an improvement, i.e. an absolute change of less than min_delta, will count as no improvement.

- **patience**: 관찰할 epochs 수 , 만약 10일 경우 10번 epochs 동안 향상되지 않으면 중단 

  - number of epochs that produced the monitored quantity with no improvement after which training will be stopped. Validation quantities may not be produced for every epoch, if the validation frequency (`model.fit(validation_freq=5)`) is greater than one.

- **verbose**: 1이면 로그로 기록, 0이면 로그에 기록 x

  - verbosity mode.

- **mode**: 

  - one of {auto, min, max}. In `min` mode, training will stop when the quantity monitored has stopped decreasing; in `max` mode it will stop when the quantity monitored has stopped increasing; in `auto` mode, the direction is automatically inferred from the name of the monitored quantity.

- **baseline**: 

  - Baseline value for the monitored quantity to reach. Training will stop if the model doesn't show improvement over the baseline.

- **restore_best_weights**: 

  - whether to restore model weights from the epoch with the best value of the monitored quantity. If False, the model weights obtained at the last step of training are used.



## ModelCheckpoint

- 훈련하는 동안 모델을 저장

  ```python
  keras.callbacks.callbacks.ModelCheckpoint(filepath, monitor='val_loss', verbose=0, save_best_only=False, save_weights_only=False, mode='auto', period=1)
  ```

- **filepath**: 저장할 파일 경로

  - string, path to save the model file.

- **monitor**: 모니터 할 요소? 

  - quantity to monitor.

- **verbose**: 1은 기록, 0은 기록x

  - verbosity mode, 0 or 1.

- **save_best_only**: monitor 하는 요소중 가장 best 인 모델 저장

  - if `save_best_only=True`, the latest best model according to the quantity monitored will not be overwritten.

- **save_weights_only**: 모델 weights 저장

  - if True, then only the model's weights will be saved (`model.save_weights(filepath)`), else the full model is saved (`model.save(filepath)`).

- **mode**: 

  - one of {auto, min, max}. If `save_best_only=True`, the decision to overwrite the current save file is made based on either the maximization or the minimization of the monitored quantity. For `val_acc`, this should be `max`, for `val_loss` this should be `min`, etc. In `auto` mode, the direction is automatically inferred from the name of the monitored quantity.

- **period**: 

  - Interval (number of epochs) between checkpoints.



## ReduceLROnPlateau

- Metric 개선이 중단되면 학습 속도를 조정(reduce)

  ```python
  keras.callbacks.callbacks.ReduceLROnPlateau(monitor='val_loss', factor=0.1, patience=10, verbose=0, mode='auto', min_delta=0.0001, cooldown=0, min_lr=0)
  ```

- loss를 모니터링하면서 patience 값 이내에 개선되지 않을 경우 학습률을 감소시킴

- 사용예시

  ```python
  from keras import callbacks
  
  reduce_lr = keras.callbacks.ReduceLROnPlateau(monitor='val_loss', factor=0.2,
                                patience=5, min_lr=0.001)
  model.fit(X_train, Y_train, callbacks=[reduce_lr])
  ```

  - **monitor**: 모니터 할 요소? 
    - (quantity to be monitored.)
  - **factor**: 학습률이 감소되는 요인, 새 학습률 = 기존 학습률 * 값 
    - (factor by which the learning rate will be reduced. new_lr = lr * factor)
  - **patience**: 
    - number of epochs that produced the monitored quantity with no improvement after which training will be stopped. Validation quantities may not be produced for every epoch, if the validation frequency (`model.fit(validation_freq=5)`) is greater than one.
  - **verbose**: 학습률 업데이트 후 메시지 발생여부 , 1일 떄 로그 발생 , 0은 발생x 
    - int. 0: quiet, 1: update messages.
  - **mode**:    
    - `min`모드: 감소하는 모니터링의 수가 stop되는 경우 학습률이 감소할 것이다.
    - `max`모드: 증가하는 모니터링의 수가 stop 되는 경우 학습률이 줄어들 것이다.
    - `auto`모드: 모니터링 양의 이름으로부터 자동으로 지정된다? 
    - one of {auto, min, max}. In `min` mode, lr will be reduced when the quantity monitored has stopped decreasing; in `max` mode it will be reduced when the quantity monitored has stopped increasing; in `auto` mode, the direction is automatically inferred from the name of the monitored quantity.
  - **min_delta**: 중요한 변화에만 초점을 맞추기 위해 새로운 최적 측정을 위한 임계 값
    - threshold for measuring the new optimum, to only focus on significant changes.
  - **cooldown**: 학습률 줄이고 난 후 정상작동을 재개하기 전 기다리는 epochs 의 수 
    - number of epochs to wait before resuming normal operation after lr has been reduced.
  - **min_lr**: 학습률의 최고 하한값
    - lower bound on the learning rate.





