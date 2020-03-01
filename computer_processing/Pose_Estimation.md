# Pose Estimation

객체의 위치(position)와 방향(orientation)을 찾는 솔루션으로 사람의 신체 관절인 keypoint가 어떻게 구성되어있는지 위치를 측정(localization)하고 추정(estimation)하는 문제이다.

주요 keypoint는 Head, Neck, Sholder, Elbow, Wrist, Hip, Knee, Ankle 이 있음



성능평가는 PCK(Percentage of Correct Keypoint) 지표를 이용



## Pose Estimation의 분류

Pose Estimation 의 종류는 2D/3D Pose Estimation 으로 나뉜다.

### 2D Pose Estimation



### 3D Pose Estimation







## Pose Estimation의 estimation 방식

Estimation 하는 방식에는 TOP-down 방식과 Bottom-up 방식이 있음

### TOP-down

영상에서 사람을 먼저 detection 후 bounding box 내에서 포즈를 추정하는 방식

정확도가 bottom-up 방식에 비해 높고 crop 과정이 필요하다

multi-person일 경우 detection 된 사람마다 포즈를 추정해야하므로 느린 단점이 있음



### Bottom-up

영상에 포함된 사람의 키포인트를 모두 estimation 후 키포인트간의 상관관계를 분석하여 포즈를 추정하는 방식

detection 과정을 거치지 않으므로 빠르다는 장점이 있고 실시간으로 적용할 수 있음



<img src="images/Pose_Estimation/image-20200228223404656.png" alt="image-20200228223404656" style="zoom:80%;" />

>  위가 Top-down 방식이고 아래가 Bottom-down 방식









## OPEN POSE

최근 가장 인기있는 bottom-up 방식의 포즈 추정방식으로 동작하며 포징 추정시 실시간으로 처리

Multi-person keypoint detection 과 multi-threading written 지원

C++ 전용이지만 파이썬도 사용가능



### 데모판 사용

[오픈포즈](https://github.com/CMU-Perceptual-Computing-Lab/openpose)에서 제공하는 데모판이 있다. 간단하게 다운로드 하여 소스코드를 실행하면 된다.

<img src="images/Pose_Estimation/image-20200301214142367.png" alt="image-20200301214142367" style="zoom:50%;" /><img src="images/Pose_Estimation/image-20200301214157717.png" alt="image-20200301214157717" style="zoom:50%;" />

> 실제 데모판을 이용하여 pose estimation 구현한 모습, 테스트 환경의 사양이 너무 딸려서 동영상을 추정할 수 없었다..



## Pose Estimation with TensorFlow + OpenCV

[유튜브](https://www.youtube.com/watch?v=nUjGLjOmF7o)에서 제공하는 영상을 통해 구현을 할 예정이다.



### 아나콘다 가상환경 생성

```bash
conda create -n 
```

