# Imgaug user manual

## Imgaug 란?

이미지를 다루는 딥러닝 모델 경우 데이터 augmentation 기술을 많이 적용할 것이다. `Imgaug`는 이 데이터 augmentation 을 쉽게 하기위해 만들어진 파이썬 모듈이다.

<img src="https://raw.githubusercontent.com/aleju/imgaug-doc/master/readme_images/examples_grid.jpg?raw=true" alt="img" style="zoom:80%;" />

출처 : [깃허브](https://github.com/aleju/imgaug)

해당 모듈에서는 augmentation 통해 만들어진 새로운 이미지들에 대해 bounding box, Keypoints, Segmentation map이 적용된 상태로 저장가능하다. 

<img src="images/Imgaug_manual/image-20200423212358836.png" alt="image-20200423212358836" style="zoom:80%;" />



## 사용방법

