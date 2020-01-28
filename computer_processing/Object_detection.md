# Object Detection

> 객체 인식과 검출은 엄연히 다른 말이다. 인식은 자동차가 정지 신호를 인식하고 보행자와 가로등을 구별할 수 있도록 하는 것이고 검출은 이미지 내에서 특정 feature를 검출 하는 것이다.





## cv2.CascadeClassifier()

- 이미지에서 feature 를 검출하기 위해 모든 가능한 크기의 커널에 대해 이미지의 모든부분에 적용을 해야 한다. 예시로 adaboost를 꼽을수 있지만 이 방법으로는 시간이 너무 걸리게되는 무식한 작업인데 예를들어 3x3 크기의 이미지에 대해 이 방법을 적용할 경우 수만가지에 대해 계산을 해야 한다.

  <img src="C:/Users/myounghwan/TIL/computer_processing/images/image-20200129002259235.png" alt="image-20200129002259235" style="zoom:50%;" />



- 이런 방법 대신 단순하고 시간을 적게 걸리게 하기위해 Cascade Classifier가 구현되었다. 
- haarcascade 방식의 알고리즘은 머신 러닝의 컨볼류션(convolution neural network) 신경망 분석 기법과 유사하다. Opencv에서는 haarcascade를 통해 이미지 feature를 학습 시킬 수 있고 특정 이미지에서 feature를 검출 할 수 있다. 
- 얼굴을 인식하기 위한 haarvascade_frontalface_default.xml의 예를 들면 수천개의 양화와 음화 이미지를 학습하여 만들어진다. 음화는 과거에 카메라 촬영 후 현상 작업을 통하여 얻어지는 결과가 네가티브 즉 음화이다. 위 그림에서처럼 이미 얼굴이 인식되었다고 하면 눈의 명암적 특징을 컨볼루션 Neural Network 머신 러닝에 의해서 찾아내는 것도 가능할 것이다. 사람이 얼굴 및 신체 각부위의 특징을 찾아내듯이 수많은 자동차의 특징도 유사한 방법으로 찾아낼 수 있을 것이며 cars.xml 라이브러리가 바로 haarcascade 라이브러리가 제공하는 자동차 인식 라이브러리이다.

- OpenCV에서는 얼굴 또는 특정신체부위를 검출하기 위해 학습된 데이터(haarcascade_frontalface_default.xml, haarcascade_eye.xml)를 제공하고 있다.

- 사용예시

  ```python
  #얼굴 검출용
  classifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
  #눈 검출용
  classifier = cv2.CascadeClassifier('haarcascade_eye.xml')
  
  #jpg
  src = cv2.imread('pic/dog.jpg')
  
  faces = classifier.detectMultiScale(src)
  
  #해상도가 작으면 찾기 어렵다
  #회전되어 있는 얼굴은 회전을 해주고 검출해야 함
  for (x, y, w, h) in faces:
      cv2.rectangle(src, (x, y), (x + w, y + h), (255, 0, 255), 2)
  imshow('src', src)    
  ```

  ![image-20200129003013345](images\image-20200129003013345.png)![image-20200129004156855](images\image-20200129004156855.png)

  > 얼굴 검출과 눈 검출, 눈 같은 경우 검출이 제대로 되지 않는 것을 볼 수 있다.

- 얼굴은 공통부분이 많아 검출이 쉽게 된다.

- 눈은 고주파 성분이 없고 패턴이 너무 단순하므로 학습을 잘 시켜도 눈이 아니어도 눈으로 검출할 가능성이 크기 떄문에 어렵다.

- 해당 문제를 해결하기 위한 대안으로 먼저 얼굴 검출 후 얼굴 높이의 반만 정해주면 입이 눈으로 인식되는 부분을 피할 수 있다.

- 사용예시

  ```python
  face_classifier = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
  eye_classifier = cv2.CascadeClassifier('haarcascade_eye.xml')
  
  src = cv2.imread('pic/kids.png')
  
  faces = face_classifier.detectMultiScale(src)
  
  for (x1, y1, w1, h1) in faces:#얼굴부분을 먼저 검출
          cv2.rectangle(src, (x1, y1), (x1 + w1, y1 + h1), (255, 0, 255), 2)
  
          print(x1, y1, w1,h1)
          faceROI = src[y1:y1 + (h1), x1:x1 + w1]#얼굴의 높이의 반정도 주면 입이 눈으로 인식되는 부분을 피할 수 있따.
          eyes = eye_classifier.detectMultiScale(faceROI) #얼굴부분에서만 눈 체크
  
          for (x2, y2, w2, h2) in eyes:
              center = (int(x2 + w2 / 2), int(y2 + h2 / 2))
              cv2.circle(faceROI, center, int(w2 / 2), (255, 0, 0), 2, cv2.LINE_AA)
  
  imshow('src', src)  
  ```

  ![image-20200129003534129](images\image-20200129003534129.png)

  

  

## cv2.HOGDescriptor()

> HOG Algorithm은 일반적으로 보행자 검출이나 사람의 형태에 대한 검출 즉, Object Tracking에 많이 사용되는 Feature 중 하나이다. Image의 지역적인 Gradient를 해당 영상의 특징으로 사용하는 방법이다. 
>
> 출처: https://eehoeskrap.tistory.com/98 [Enough is not enough]

> 사람 및 사물을 검출하는 방법은 다음과 같이 수행된다.

1. 이미지 전처리를 위한 crop 및 resize 

   <img src="images\image-20200129010353415.png" alt="image-20200129010353415" style="zoom:33%;" />

2. 이미지의 gradient 계산

   - x, y 축에 대해 edge 추출을 위해 커널 적용 후 gradient 계산

   <img src="images\image-20200129010520372.png" alt="image-20200129010520372" style="zoom:33%;" />

   - sobel 필터를 통해 gradient 에 따른 이미지를 검출 할 수 있음

     ```python
     # Read image
     im = cv2.imread('bolt.png')
     im = np.float32(im) / 255.0
      
     # Calculate gradient 
     gx = cv2.Sobel(img, cv2.CV_32F, 1, 0, ksize=1)
     gy = cv2.Sobel(img, cv2.CV_32F, 0, 1, ksize=1)
     
     #magnitude(벡터크기) , direction
     mag, angle = cv2.cartToPolar(gx, gy, angleInDegrees=True)
     ```

     - gradient의 magnitude와 direction을 아래의 식을 통해 얻을 수 있음

     ![image-20200129010832747](images\image-20200129010832747.png)

     <img src="images\image-20200129011024382.png" alt="image-20200129011024382" style="zoom:50%;" />

     > 왼쪽: x-gradient 의 절대 값, 중앙: y-graident의 절대 값,  오른쪽: gradient의 magnitude(벡터크기)

3. 8x8 셀 내의 Histogram of Gradient 계산

   - 해당 이미지(64 x 128)는 8x8 로 ROI(얼굴,머리,상단 등)를 검출하기에는 충분하며 16(128/8), 8(64/8)의 이미지로 다시 표현한 것 
   - 만약 crop 및 resize의 크기를 다르게 할 경우 최적의 셀을 알아봐야 할 것

   <img src="images\image-20200129011602238.png" alt="image-20200129011602238" style="zoom:50%;" />

   - 위는 8x8 패치에 대한 Gradient의 크기와 방향에 대해서 나타낸 사진이다.

   - 위와 같은 사진의 결과는 0 ~ 360도도가 아닌 signedGradient=False인 경우이다.

   - 따라서 모든 각도를 0 ~ 180도로 표현한 것 이다.

   - 위와 같은 결과를 몇개의 bin으로서 표현할 지 정하여서 나타낸다.

   - 아래의 사진은 nbins=9로 두어서 0 ~ 180도를 9개의 bin으로서 표현한 것 이다.

     <img src="images\image-20200129012010321.png" alt="image-20200129012010321" style="zoom:50%;" />

     > direction이 80 일떄 값은2 이며 10도일때 값은 4이지만 0과 20사이 절반이므로 각각 2 씩 들어가게된다.



참고주소:

https://www.learnopencv.com/histogram-of-oriented-gradients/

https://wjddyd66.github.io/opencv/OpenCV(8)/