# OpenCV FILTER 관련 함수

> 이미지에 대한 잡음처리 및 꼭지점을 확보하기 위해 사용되는 함수 리스트



### 주의사항

- 이미지 필터를 적용전에 흑백으로 read  해야 함



### 사전 모듈 호출

```python
import scipy.stats as sp
import numpy as np
import matplotlib.pyplot as plt
from PIL import ImageFont, ImageDraw, Image
import cv2
%matplotlib inline

# 이미지 호출에 따른 흑백 또는 컬러로 출력하는 함수
def imshow(tit,image):
    plt.title(tit)
    if len(image.shape) == 3: #행렬의 크기가 나옴, 컬러영상일경우 3이 나옴
        plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB)) #BRG to RGB
    else: # 흑백영상일 경우 2가 나옴
        plt.imshow(image, cmap='gray') #흑백
    plt.show()
    plt.close()
```





### 사용하는 함수 종류

#### 1. 이미지 호출

##### cv2.imread 

> cv2.imread('이미지명', [0]) 

  - 0을 입력하게 되면 `흑백`으로 가져옴, 0을 입력하지 않으면 `컬러(RGB)`로 가져옴





#### 2. 이미지 binary(이진화) 처리

> 영상에서는 0~255 사이의 값을 가진 영상을 **바이너리 영상**이라 부름

##### cv2.threshold

> cv2.threshold(이미지,  기준값, 최대값, type )
>
> 색상을 이진화 하기 위해 사용

- **역치값(기준값)** : 색상크기를 0 또는 최대로 변경할 기준값, 예를들어 기준값이 80이고 최대값이 255인 경우, 색상크기가 80이하인 경우 0으로 처리됨

- **최대값** : 최대값보다 값이 이상인 경우 최대값으로 처리됨

- 사용예시

  ```python
  thr, mask = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
  #thr 은 127이 된다. mask가 이진화된 이미지가 됨
  # 색상크기가 127 이하는 0이되고, 255 이상인경우 255로 적용
  #thr,mask = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
  #cv2.THRESH_OTSU는 자동으로 역치값을 평균에 의해 정해준다.
  ```

  
  <img src="images/image-20200109214337676.png" alt="image-20200109214337676" style="zoom:50%;" /><img src="images/image-20200109214350522.png" alt="image-20200109214350522" style="zoom:50%;" />
  
  ![image-20200109215335535](images/image-20200109215335535.png)
  
  > 왼쪽이 원본 , 오른쪽이 스레솔드를 이용해 잡음 제거
  



##### cv2.adaptiveThreshold

> cv2.adaptiveThreshold(src, maxValue, adaptiveMethod, thresholdType, blockSize, C)

  - 이전 Threshold 함수가 `임계값을 이미지 전체에 적용`한경우이며 해당 함수는 `영역별로 임계값을 적용` 하는것이다.
  - **src** – gray색의 소스이미지
  - **maxValue** – 임계값
  - **adaptiveMethod** – thresholding value를 결정하는 계산 방법
  - **thresholdType** – threshold type
  - **blockSize** – thresholding을 적용할 영역 사이즈
  - **C** – 평균이나 가중평균에서 차감할 값

  ```python
  binary = cv2.adaptiveThreshold(te_img, 255, 
                                 cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
                                 cv2.THRESH_BINARY, 21, 2)
  # 색상크기가 255이상인 경우 255로 처리
  # 각각 적용할 블록사이즈 21이면 21개씩 처리함
  # 기존 평균에서 2를 차감하여 필터적용, 예로 평균이 80이면 실제 적용되는 값은 78부터이며 78보다 작은 값은 0으로 처리
  ```

  <img src="images/image-20200109220221937.png" alt="image-20200109220221937" style="zoom:50%;" /><img src="images/image-20200109220143799.png" alt="image-20200109220143799" style="zoom:50%;" />

  <img src="images/image-20200109220338446.png" alt="image-20200109220338446" style="zoom:50%;" /><img src="images/image-20200109220353393.png" alt="image-20200109220353393" style="zoom:50%;" />

  > 이렇게 바꿀수있따.



##### cv2.morphologyEx

> cv2.morphologyEx(src, op, kernel[, dst[, anchor[, iterations[, borderType[, borderValue]]]]]) → dst

- src – Source image. The number of channels can be arbitrary. The depth should be one of CV_8U, CV_16U, CV_16S, CV_32F` or ``CV_64F.

- op – Type of a morphological operation that can be one of the following:

  - MORPH_OPEN - an opening operation
  - MORPH_CLOSE - a closing operation
  - MORPH_GRADIENT - a morphological gradient. Dilation과 erosion의 차이.
  - MORPH_TOPHAT - “top hat”. Opeining과 원본 이미지의 차이
  - MORPH_BLACKHAT - “black hat”. Closing과 원본 이미지의 차이

- kernel – structuring element. cv2.getStructuringElemet() 함수로 만들 수 있음.

- anchor – structuring element의 중심. default (-1,-1)로 중심점.

- iterations – erosion and dilation 적용 횟수

- borderType – Pixel extrapolation method. See borderInterpolate for details.

- borderValue – Border value in case of a constant border. The default value has a special meaning.

- 사용예시

  ```python
  #침식 연산자
  dilated = cv2.morphologyEx(binary, cv2.MORPH_DILATE, (3,3), iterations = 8)
  # 이터레이션 수 커질수록 흩어짐
  
  #팽창 연산자, 구멍이 메워짐
  eroded = cv2.morphologyEx(binary, cv2.MORPH_ERODE, (3,3), iterations = 10) 
  #이터레이션 수 커질수록 뭉쳐짐
  
  #개방, 주변잡음 제거후 완만하게, 잔 테두리 제거하기
  opened = cv2.morphologyEx(binary, cv2.MORPH_OPEN,
        cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5)), 
         iterations = 3 )
  
  #폐쇄, 비어있는 구멍 채운 후 원래사이즈로 복귀 , 구멍메꾸기
  closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE,
        cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3)), 
         iterations = 12 )
  ```

  <img src="images/침식팽창.png" alt="침식팽창" style="zoom:50%;" />





##### 실습

- [threshold(adaptive 포함)](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200109/1.3_binary_3.ipynb)

- [morphologyEx](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200109/1.3_binary_3.ipynb)

  





#### 3. 이미지 블러 관련

> - 영상의 세밀한 부분을 제거하여 영상을 흐리게 하거나 부드럽게 하는 기술
> - 영상의 세밀한 부분은 주파수 축에서 보면 고주파 성분인데, 블러링은 이 고주파 성분을 제거해 줌
> - 사용하는 가중치의 회선 마스크는 저역통과 필터(Low Pass Filter)가 됨 

![image-20200209194250924](images/image-20200209194250924.png)

##### cv2.GaussianBlur

> cv2.GaussianBlur(이미지, (X,X), 0 )
>
> 이미지에 블러 처리, 잡음제거에 사용

- `(X,X)` : 필터 사이즈, **홀수**로 넣어야함

- 사용예시

  ```python
  img_blur = cv2.GaussianBlur(img, (21,21), 0 )
  #필터사이즈를 크게하면 블러가 더 심해진다.
  #뒤에 0은 차이를 잘 모르겠다. Gaussian kernel standard deviation in X direction. 라고 한다.
  ```
  
  <img src="images/image-20200109215210151.png" alt="image-20200109215210151" style="zoom:50%;" /><img src="images/image-20200109215222785.png" alt="image-20200109215222785" style="zoom:50%;" />



##### cv2.medianBlur

> cv2.medianBlur(src, ksize)

- 커널과 픽셀의 값들을 정렬 후 평균값을 선택하여 적용

- src – 1,3,4 channel image. depth가 CV_8U, CV_16U, or CV_32F 이면 ksize는 3또는5, CV_8U이면 더 큰 ksize가능

- ksize – 1보다 큰 홀수

  ```python
  #median 필터, 값들의 중간값
  median = cv2.medianBlur(img, 5)
  
  plt.imshow(median) #엄청 깨끗하게 나온다
  ```

  

![image-20200209194441202](images/image-20200209194441202.png)

> 원본 , 가우시안 , 미디안 순
>
> 원본은 잡음이 너무 많고, 가우시안은 블러가 심하고, median 은 평균화, 고주파 성분이 남아잇다.?



##### 실습

- [blur](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/image_processing/20200108)



#### 4. 이미지 영역 경계선 처리 관련

##### cv2.findContours

> cv2.findContours(image, mode, method[, contours[, hierarchy[, offset]]]) → image, contours, hierarchy
>
> 컨투어(contour)란 동일한 색 또는 동일한 픽셀값(강도,intensity)을 가지고 있는 영역의 경계선 정보다. 물체의 윤곽선, 외형을 파악하기위해 위 함수를 사용된다.
>
> 참고주소는 https://datascienceschool.net/view-notebook/f9f8983941254a34bf0fee42c66c5539/

- image – 8비트 싱글채널 이미지 또는  binary 이미지

- 이미지 가져오기전에 copy 함수 이용해서 가져와야함,, 원본에 영향을 미치는 함수이기 때문

- mode

  > contours를 찾는 방법
  
  - cv2.RETR_EXTERNAL : contours line중 가장 바같쪽 Line만 찾음.
  - cv2.RETR_LIST : 모든 contours line을 찾지만, hierachy 관계를 구성하지 않음.
  - cv2.RETR_CCOMP : 모든 contours line을 찾으며, hieracy관계는 2-level로 구성함.
  - cv2.RETR_TREE : 모든 contours line을 찾으며, 모든 hieracy관계를 구성함.
  
- method
  
  >contours를 찾을 때 사용하는 근사치 방법
  
    - cv2.CHAIN_APPROX_NONE : 모든 contours point를 저장.
  
    - cv2.CHAIN_APPROX_SIMPLE : contours line을 그릴 수 있는 point 만 저장. (ex; 사각형이면 4개 point)
  
    - cv2.CHAIN_APPROX_TC89_L1 : contours point를 찾는 algorithm
  
    - cv2.CHAIN_APPROX_TC89_KCOS : contours point를 찾는 algorithm
  
- Method에 대해서 설명을 하면 아래 예제의 결과에서 처럼 사각형의 contours line을 그릴 때, `cv2.CHAIN_APPROX_NONE` 는 모든 point를 저장하고 `cv2.CHAIN_APPROX_SIMPLE` 는 4개의 point만을 저장하여 메모리를 절약.



##### cv2.drawContours

> cv2.drawContours(image, contours, contourIdx, color[, thickness[, lineType[, hierarchy[, maxLevel[, offset]]]]]) → dst

- contour 그려진 결과를 반환
- image – 원본 이미지
  contours – contours정보.
  contourIdx – contours list type에서 몇번째 contours line을 그릴 것인지. -1 이면 전체
  color – contours line color
  thickness – contours line의 두께. 음수이면 contours line의 내부를 채움.

- 사용예시

  ```python
  contours[0].shape #cv2.CHAIN_APPROX_SIMPLE(4 point)
  (4, 1, 2)
  contours[0].shape #cv2.CHAIN_APPROX_NONE(750 point)
  (750, 1, 2)
  contours, _ = cv2.findContours(binary,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
print(contours)
  [array([[[48,  6]],
       [[49,  7]]], dtype=int32)]
  cv2.drawContours(img, coutours, -1, (0, 255, 255), 1) 
  #img에 contours 값 적용, -1은 찾아진 꼭지점 전부 색칠,  맨뒤 값은 꼭지점굵기
  ```

  <img src="images/점선2.PNG" alt="점선2" style="zoom:50%;" /><img src="images/점선.png" alt="점선" style="zoom:50%;" />



##### cv2.contourArea

> area = cv2.contourArea(con) 

- 컨투어의 영역(면적)을 계산, 실수값으로 나옴
- 사물 탐지할때 사용하면 될듯



##### cv2.arcLength

> cv2.arcLength(con,True)

- `Contour의 둘레 길이`를 구할 수 있습니다. 사각형의 경우는 둘레길이의 합이 됩니다. 아래 함수의 2번째 argument가 `true이면 폐곡선 도형을 만들어 둘레길이`를 구하고, `False이면 시작점과 끝점을 연결하지 않고 둘레 길이`를 구합니다.

- 사용예시

  ```python
  peri = cv2.arcLength(c, True)
  #c는 contours 요소 중 하나
  ```

  

##### cv2.approxPolyDP

> ##### cv2.approxPolyDP(curve, epsilon, closed[, approxCurve]) → approxCurve

- curve – contours point array

- epsilon – original cuve와 근사치의 최대거리. 최대거리가 클 수록 더 먼 곳의 Point까지 고려하기 때문에 Point수가 줄어듬.

- closed – 폐곡선 여부

- 근사치가 적용된 contours point array 반환

- 사용예시

  ```python
  approx = cv2.approxPolyDP(c, 0.02 * peri, True) 
  #c는 contours의 값 일부, 꼭지점의 개수를 반환한다.
  ```



##### 실습

- [Contours](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200109/1.3_binary_2.ipynb)




#### 5. 이미지 영역 표시 관련

##### cv2.putText

> cv2.putText(img, text, org, font, fontSacle, color)

- 이미지에 텍스트 추가

- img – image

- text – 표시할 문자열

- org – 문자열이 표시될 위치. 문자열의 bottom-left corner점

- font – font type. CV2.FONT_XXX

- fontSacle – Font Size

- color – fond color

  ```python
  #바이너리화
  img = cv2.imread('./data/shape3.png') #노이즈로 인해 엣지가 너무 많음
  gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
  thr,mask = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU) # 역치값이 작다는 것은, 구분이 잘 된다는 뜻이다., 색의 전경과 배경의 명암대비에 따라 달라짐
  mask = 255 - mask
  imshow('', mask)
  
  #바운더리(꼭지점?) 찾기
  contours, _ = cv2.findContours(mask,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
  #print(countours)
  
  print( f"전체 도형 shpae = {len(contours)}")
  for con in contours:
      x = con[0][0][0]
      y = con[0][0][1]
      peri = cv2.arcLength(con,True)
      approx = cv2.approxPolyDP(con, 0.02*peri, True)
      
      print(f"shape={len(con)}  length={peri} approx={len(approx)}"   )
      
      if len(approx) == 3:
          cv2.putText(img, 'triangle', (x,y-20), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (255, 0, 255) , 5) 
      
      elif len(approx) == 4 :
          cv2.putText(img, 'rectangle', (x,y-20), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (255, 0, 255) , 5) 
      
      elif len(approx) == 5:
          cv2.putText(img, 'pentagon', (x,y-20), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (255, 0, 255) , 5) 
      
      elif len(approx) > 5:
          cv2.putText(img, 'polygon', (x,y-20), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (255, 0, 255) , 5) 
      
      #꼭지점 그림에 표시해주기
      cv2.drawContours(img, [approx], -1, (255, 0, 255), 3) #두번째 배열처럼 넣어줘야함
      cv2.circle(img, (x,y),5 ,(255,0,0), -1) #중심점, 반지름 크기, 색깔, 굵기
  
  imshow('',img)
  ```

  

<img src="images/image-20200209195349033.png" alt="image-20200209195349033" style="zoom:50%;" />

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200109/1.3_binary_2.ipynb)



##### cv2.ellipse

> cv2.ellipse(img, center, axes, angle, startAngle, endAngle, color[, thickness[, lineType[, shift]]]) → img

- 타원 그리기

- 중심점, 반지름 크기, 색깔, 굵기

- img – image

- center – 타원의 중심

- axes – 중심에서 가장 큰 거리와 작은 거리

- angle – 타원의 기울기 각

- startAngle – 타원의 시작 각도

- endAngle – 타원이 끝나는 각도

- color – 타원의 색

- thickness – 선 두께 -1이면 안쪽을 채움

  ```python
  
  #cont_img = closing.copy()
  cont_img = thresh.copy()
  
  
  #바운더리(꼭지점?) 찾기
  contours, _ = cv2.findContours(cont_img,cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) #findContours 함수는 원본이미지를 변경시키기 때문에 copy를 미리 사용한다.
  #print(contours)
  print( f"전체 도형 shpae = {len(contours)}")
  
  for con in contours:
      area = cv2.contourArea(con) # 컨투어의 영역(면적)을 계산, 실수값으로 나옴
      if area < 2000 or area > 4000:# 2000보다 작고 4000보다 크면 우리가 원하는게 아님
          continue
      if len(con) < 5: # 점의 개수가 5개보다 작다, 원이 아니다, 패스
          continue
      
      ellipse = cv2.fitEllipse(con) #주어진 점을통해 타원으로 만드는 함수, 만들고나서 값으로 돌려줌
      cv2.ellipse(roi, ellipse, (0, 255,0), 2) #ellipse 는 타원을 그리는 함수임, 그림파일, 길이, 색깔 , 굵기?
      
      #타원으로 매핑하려면 최소한 5개는 있어야 함, 없으면 에러남
  
      
  imshow('',thresh)
  imshow('',cont_img )
  imshow('',roi )
  ```

  

<img src="images/image-20200209195623552.png" alt="image-20200209195623552" style="zoom:50%;" />

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/blob/88aa5c50d3f229765ddfae7106f5d294e9bb6ef4/image_processing/20200109/1.4_coin_lab.ipynb)



##### cv2.circle

> cv2.circle(img, center, radian, color, thickness)

- 원그리기

- img – 그림을 그릴 이미지

- center – 원의 중심 좌표(x, y)

- radian – 반지름

- color – BGR형태의 Color

- thickness – 선의 두께, -1 이면 원 안쪽을 채움

- 사용예시

  ```python
  cv2.circle(img, (x, y), int(r), (255, 255, 0), 2)
  # x,y, r(반지름), 색깔, 선굵기(-1은 꽉채움)
  ```

  <img src="images/image-20200110112818072.png" alt="image-20200110112818072" style="zoom:50%;" /><img src="images/image-20200110112927465.png" alt="image-20200110112927465" style="zoom:50%;" />
  
  > 왼쪽이 0이상일떄, 오른쪽이 -1일때

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200110/1.2_low_level_filter.ipynb)



#### 6. 이미지 변형 관련

##### cv2.getRotationMatrix2D

> cv2.getRotationMatrix2D(center, angle, scale) → M

- 이미지를 회전 시킴

- center – 이미지의 중심 좌표

- angle – 회전 각도

- scale – scale factor(확대율)

- 값은 다음과 같은 행렬로 나온다.

- 사용예시

  ```python
img = cv2.imread("./data/Lena.png")
  height, width = img.shape[:2]
  #print(width,height )
  
  img_center = (width /2, height/2)
  M = cv2.getRotationMatrix2D(img_center, 30, 0.7) # 이미지, 회전각도, 확대배율
  print(M)
  [[  0.60621778   0.35        11.20824764]
   [ -0.35         0.60621778 190.40824764]]
  ```
  
  
  
  <img src="images/image-20200110144723535.png" alt="image-20200110144723535" style="zoom: 50%;" /> <img src="images/image-20200110144831452.png" alt="image-20200110144831452" style="zoom:50%;" /><img src="images/image-20200110144800061.png" alt="image-20200110144800061" style="zoom:50%;" />



##### cv2.flip

> cv2.flip(img,0) #사진 뒤집기

<img src="images/image-20200110144831452.png" alt="image-20200110144831452" style="zoom:50%;" /><img src="images/image-20200110201217442.png" alt="image-20200110201217442" style="zoom:50%;" />



##### cv2.warpAffine

> cv2.warpAffine(src, M, dsize)

- 이미지의 위치 변경

- src – Image

- M – 변환 행렬

- dsize (tuple) – output image size(ex; (width=columns, height=rows)

- 사용예시

  ```python
  img = cv2.imread("./data/Lena.png")
  height, width = img.shape[:2]
  print(width,height )
  m = np.float32([
      [1,0,20], 
      [0,1,30]
  #   x,y,크기
  ])
  dst = cv2.warpAffine(img, m , (width, height), borderValue=(255,50,50) )
  imshow('',dst)
  ```

  <img src="images/image-20200110201537757.png" alt="image-20200110201537757" style="zoom:50%;" />



##### cv2.getPerspectiveTransform

> cv2.getPerspectiveTransform(pts1,pts2)

- 이미지 합체, 해당 점의 4 쌍에서 원근 변환을 계산

- src – 소스 이미지에서 사각형 꼭지점의 좌표.
  dst – 대상 이미지에서 해당 사각형 꼭지점의 좌표.

- 사용예시

  ```python
  #좌표순서
  point_list = [[27,179], [611,36], [118,534], [754,325]]
  
  pts1 = np.float32([list(point_list[0]),
                    list(point_list[1]),
                    list(point_list[2]),
                    list(point_list[3])
                    ])
  print(pts1)# 꼭지점 4개
  [[ 27. 179.]
   [611.  36.]
   [118. 534.]
   [754. 325.]]
  
  pts2 = np.float32([ [0,0],[width,0],[0,height],[width,height] ])
  print(pts2) # 0,0 -> 0,x -> y,0 -> x,y 순
  [[  0.    0. ]
   [405.5   0. ]
   [  0.  288.5]
   [405.5 288.5]]
  
  M = cv2.getPerspectiveTransform(pts1,pts2) # 이미지, 회전각도, 확대배율
  print(M)
  [[ 6.11584185e-01 -1.56772284e-01  1.15494658e+01]
   [ 2.26751420e-01  9.26033771e-01 -1.71882333e+02]
   [-1.29571760e-04  4.23781663e-04  1.00000000e+00]]
  ```



##### cv2.warpPerspective

> cv2.warpPerspective(img, M , (width,height) )

- 이미지에 원근 변환을 적용

- Perspective(원근법) 변환은 직선의 성질만 유지가 되고, 선의 평행성은 유지가 되지 않는 변환입니다. 기차길은 서로 평행하지만 원근변환을 거치면 평행성은 유지 되지 못하고 하나의 점에서 만나는 것 처럼 보입니다.(반대의 변환도 가능)

- 4개의 Point의 Input값과이동할 output Point 가 필요합니다.

- 변환 행렬을 구하기 위해서는 `cv2.getPerspectiveTransform()` 함수가 필요하며, `cv2.warpPerspective()` 함수에 변환행렬값을 적용하여 최종 결과 이미지를 얻을 수 있습니다.

- src – 입력 이미지.

- dst – 크기 dsize 와 유형이 같은 이미지를 출력합니다 src.

- M – 3 회 ~ 3 회 변환 행렬.

- dsize – 출력 이미지의 크기입니다.

- flags – 보간 방법 ( INTER_LINEAR또는 INTER_NEAREST)과 선택적인 플래그의 

- WARP_INVERSE_MAP조합 M으로 역변환 ( \ texttt {dst} \ rightarrow \ texttt {src}) 으로 설정 됩니다 .

- borderMode – 픽셀 외삽 법 ( BORDER_CONSTANT또는 BORDER_REPLICATE).

- borderValue – 경계가 일정한 경우에 사용되는 값. 기본적으로 0과 같습니다.

- 사용예시

  ```python
  M = cv2.getPerspectiveTransform(pts1,pts2) # 이미지, 회전각도, 확대배율
  print(M)
  
  #원근법 이미지에 적용
  rotate_img = cv2.warpPerspective(img, M , (width,height) ) 
  imshow(" ", img) #원본 
  imshow('',rotate_img)#적용본
  ```

  <img src="images/image-20200110202421483.png" alt="image-20200110202421483" style="zoom:50%;" /><img src="images/image-20200110202408938.png" alt="image-20200110202408938" style="zoom:50%;" />
  
  <img src="images/image-20200110202446090.png" alt="image-20200110202446090" style="zoom:50%;" /><img src="images/image-20200110202454427.png" alt="image-20200110202454427" style="zoom:50%;" />

  <img src="images/image-20200110202538340.png" alt="image-20200110202538340" style="zoom:50%;" /><img src="images/image-20200110202600913.png" alt="image-20200110202600913" style="zoom:50%;" />



##### 실습

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/blob/master/image_processing/20200110)









## 기타 추후 정리 자료?

인터플레이스 알고리즘

거꾸로 푸는

작은해상도의 이미지를 큰 해상도로 복사할때 사용

https://datascienceschool.net/view-notebook/7eb4b2a440824bb0a8c2c7ce3da7a4e2/





