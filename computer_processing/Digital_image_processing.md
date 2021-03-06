# Digital image processing

> 이미지 처리에는 다음과 같이 진행을 한다.
>
> 1. 칼러를 흑백으로 변환
> 2. 엣지검출
> 3. 이진화 처리(상황에 따라 다름)
> 4. 모폴로지(침식, 팽창, 오픈, 클로즈)
> 5. 기하학적 변형(회전, 이동 등 작은 해상도에서 큰해상도로 바꿀 경우 인터폴레이션? 이 중요하다)
> 6. 코너 검출





## 압축의 종류

### 손실압축

> 데이터를 압축하여 자료를 받는 곳에 압축으로 풀어서 원래의 것과 다르게 보여주는 것을 말하지만 어떠한 부분에서는 충분히 유용한 방식이다. 손실 압축은 특히 스트리밍 미디어와 인터넷 전화 등의 응용 프로그램 안에서 멀티미디어 데이터를 압축하는 데에 가장 많이 사용된다. (오디오, 비디오, 스틸 이미지) 한편, 무손실 압축은 텍스트로 된 파일, 그리고 은행 기록과 같은 데이터 파일에 선호된다.
>
> 이미지는 jpg
>
> 

### 비손실압축

> 데이터 압축의 일종으로 손실 압축의 반대말이다. 원래의 정보를 그대로 보존해야 하기 때문에, 정보 엔트로피의 한계가 그대로 반영된다. 여기에서 정보 엔트로피의 한계란 개별 정보의 확률값에 의하여 계산되는 값이 아닌, 전체 신호의 상관관계를 반영한 한계값이다. 이러한 성질을 이용한 대표적인 압축 방법으로 반복 길이 부호화가 있다.
>
> 일반적으로 파일 데이터 압축에 사용하는 gzip을 비롯한 알고리즘들이 이에 해당한다. 오디오나 이미지 압축에서 사용하는 무손실 압축 기술들은 각각의 신호 특성에 맞추어서 최적화가 된 것으로, 범용성을 가지는 데이터 압축 기술에 비하여 조금 더 압축률을 끌어 올릴 수 있다.
>
> 이미지는 png



## 처리방식

### 화소 점 처리(point processng)

> 점 단위로 화소 값을 변경해서 밝기 조절등을 수행,

#### 문제점

- 결과 값이 화소의 최대값과 최소값을 넘을 수 있음.

#### 해결방안

 1. 클래핑 기법
    - 연산의 결과 값이 최소값보다 작으면 그 결과 값을 최소값으로, 최대값보다 크면 결과 값을 최대값으로 하는 기법 
    - 8비트 그레이 영상의 최소값은 0, 최대값은 255
    - 음수는 0으로 설정하고, 255보다 큰 값은 255로 설정함.
 2. 랩핑 기법
    - 연산의 결과 값이 최소값보다 작으면 그 결과 값을 최소값으로, 최대값보다 크면 최소값부터 최대값까지를 한 주기로 해서 이를 반복하는 기법 
    - 최대값+1은 최소값이 되고, 연산의 결과 값이 최대값+상수 값일 때는 계속 상수 값-1로 설정함.
    - 8비트 그레이 영상의 최소값은 당연히 0이고, 최대값은 255 
    - 음수는 0으로, 255보다 큰 결과 값 256은 0으로, 257은 1로 설정한 후 이런 방식으로 주기를 계속 반복

![화소점처리](images/화소점처리.PNG)

### LUT

> 1. 색상hue, 채도saturation, 조도brightness를 "수학적으로 정확하게" 조정하여 촬영된 원본 이미지의 RGB값을 새로운 RGB값으로 만들어주는 방법이다.
> 2. lut 함수를 사용하면 픽셀을 돌기전에 밝기가 100일 경우 110으로 리턴할 수 있도록 lut[100] = 110을 리턴
> 3. 만약 lut 함수를 사용하지 않으면 픽셀을 돌면서 밝기가 100인 픽셀 300개가 있다면 100개 각각마다 +10 해서 110으로 결과값 리턴

![LUT](images/LUT.png)

#### 종류 

1. 포스터라이징

   - 영상에서 화소에 있는 명암 값의 범위를 경계 값으로 축소

   -  경계 값 8개로 8비트 그레이 레벨 영상을 포스터라이징 처리하면, 명암 값 256개가 명암 값 8개로 변경됨.

     <img src="images/포스터라이징.PNG" alt="포스터라이징" style="zoom: 50%;" />

2. 이진화

   - 경계 값을 이용해 값이 두 개만 있는 영상으로 변환해 주는것

   - 보통 그레이 레벨 영상을 이진 영상으로 변환할 때 사용

   -  값이 두 개뿐이라서 영상을 쉽게 분석할 수 있고, 명암 대비가 매우 낮은 영상에서는 배경과 물체를 확실하게 구분할 수 있게 해줌.

     <img src="images/이진화.PNG" alt="이진화" style="zoom:50%;" />

3. 범위 강조 변환

   - 영상에서 한 부분의 화소는 원 상태를 그대로 유지한 채 일정 범위의 화소만 강조하는 변환 

   - 원하는 부분의 화소 값이 더 커지거나 작아져 다른 부분과 비교해서 더욱 도드라져 보임.

     <img src="images/범위강조변환.PNG" alt="범위강조변환" style="zoom:50%;" />

4. 감마

   <img src="images/감마.PNG" alt="감마" style="zoom:50%;" />

#### 실습

1. [정규분포 기반 모델 학습 및 리스트 컴프레션, 클래핑](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/image_processing/20200107/1.1_Normal_distribution.ipynb)
2. [LUT_1](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/image_processing/20200107/1.2_LUT.ipynb)
3. [LUT_2 및 움직이는 그림(gif)파일 생성](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/image_processing/20200107/1.3_LUT_lab.ipynb)







### 화소 영역 처리

> 1. 주변을 신경써서 처리하겠다는 컨셉, CNN의 원조
> 2. 
> 3. 화소의 원값이나 위치를 바탕으로 화소 값을 변경하는 화소의 점 처리과 달리 해당 입력 화소뿐만 아니라 그 주위의 화소 값도 함께 고려하는 공간 영역 연산 
> 4. 회선 기법(또는 컨벌루션 기법, Convolution Technique)으로 수행하므로, 화소의 영역 처리를 회선 처리(Convolution Processing) 또는 컨벌루션 처리라고 함. 
> 5. 원시 화소와 이웃한 각 화소에 가중치를 곱한 합을 출력 화소로 생성 

<img src="images/화소영역처리_1.PNG" alt="화소영역처리_1" style="zoom:50%;" />

> - Output_pixel[x, y]: 회선 처리로 출력한 화소
> -  I[m, n]: 입력 영상의 화소 
> - M[m, n]: 입력 영상의 화소에 대응하는 가중치

<img src="images/화소영역처리_2.PNG" alt="화소영역처리_2" style="zoom:50%;" />

#### 종류

- 엠보싱

  - 미분값을 제거한다는 의미

    

- 블러링

  - low pass filter, 고주파 성분을 지우고 저주파 성분만 추출

  - 세세한 부분까지 제거해 디지털영상을 흐리게 만듬

  - 영상의 세밀한 부분을 제거하여 영상을 흐리게 하거나 부드럽게 하는 기술

  - 영상의 세밀한 부분은 주파수 축에서 보면 고주파 성분인데, 블러링은 이 고주파 성분을 제거해 줌. 

  - 사용하는 가중치의 회선 마스크는 저역통과 필터(Low Pass Filter)가 됨 

  - 주변픽셀은 낮아질 수 있음

  - 가우시안 필터 스무딩이 있다

    

- 샤프닝

  - high pass filter, 블러링의 반대, 저주파 성분을 빼고 고주파성분만 남계함
  - 블러링과는 반대로 디지털 영상에서 상세한 부분을 더욱 강조하여 표현. 
  - 영상의 상세한 부분은 고주파 성분이므로 영상에서 저주파 성분만 제거하면 샤프닝 효과를 얻을 수 있음 
  - 사용되는 가중치의 회선 마스크는 고역통과 필터(High Pass Filter)가 됨.

  

- 경계선 검출

  - 반도체에서 가장많이 사용, 밝기가 급격하게 변하는 부분을 경계선이라 함
  - 디지털 영상의 경계선을 찾아내는 기술 
  - 경계선은 영상의 밝기가 낮은 값에서 높은 값으로 또는 높은 값에서 낮은 값으로 변하는 지점에 있으므로 입력한 영상의 정보가 많이 듬

  

- 잡음 제거

  

#### 수행방법

1. 가중치를 포함한 회선 마스크가 이동하면서 수행 
2. 회선 마스크가 영상의 왼쪽 위 화소에서 오른쪽으로 한 화소씩 차례로 이동하면서 수행하여 새로운 화소를 만들어 냄. 
3. 한 줄에서의 회선 수행이 끝나면, 다음 줄로 이동하여 다시 한 화소씩 오른쪽으로 이동하면서 차례로 수행됨. 





#### 문제점



### 기하학 처리 

> 1. 영상 화소의 위치나 화소의 모임인 배열을 변화시키는 것
> 2. 원래 영상에 변화시킴
> 3. 전이학습에서 많이 사용할 거

- 스케일 영상 크기 줄이거나 확대
- 회전하거나 축소

 

### 프레임처리

> 영상으로 각종 연산을 조합하여 새로운 화소값을 생성

- 산술연산(덧셈, 뺄셈) , 논리연산(AND, OR 등)



## 시각

RGB, CMY(K), HSI, YCrCh, YUV 등이 있음 

하나의 색상(R) 당 2^8이므로 R + G + B 총 2^24 1600만의 컬러



## edge filter(필터)

> 딥러닝 CNN 이 이기술을 기반으로 만들어짐



#### 마스크종류

1. 로버츠

   - 자기점과 대각선만 계산 , 잡음 때문에 잘안씀

   - 장점 : 크기가 작아 매우 빠른 속도로 동작하여 효과적으로 사용 가능.
   - 단점 : 돌출된 값을 잘 평균할 수 없으며, 잡음에 민감함.

2. 프리윗

   - 장점 : 돌출된 값을 비교적 잘 평균화함.
   - 
     단점 : 대각선보다 수평과 수직에 놓인 에지에 더 민감하게 반응함.

3. 소벨

   - 요즘 많이 씀

   - 장점 : 돌출된 값을 비교적 잘 평균화함.
   - 단점 : 대각선 방향에 놓인 에지에 더 민감하게 반응함. 



#### 미분

1. 1차 미분 
2. 2차미분(라플라시안 연산자)
   - 



#### 실습



## Binary processing

> 영상에서는 0~255 사이의 값을 가진 영상을 **바이너리 영상**이라 부름