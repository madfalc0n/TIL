# Segmentation

- Segmentation은 픽셀을 대상으로 한 Classification 문제로 접근할 수 있습니다.
- 입력으로 주어진 이미지 내에서 각 픽셀이 어떤 클래스에 속하는지 분류합니다.
- 각 픽셀의 분류된 클래스는 모델이 생성한 결과물인 예측 마스크 (mask)에 픽셀 단위로 기록됩니다. 만일 특정 픽셀이 어떤 클래스에도 해당하지 않는 경우, Background 클래스로 규정해 0을 표기하는 방식을 사용합니다.
- 분할의 기본 단위를 무엇으로 설정하느냐에 따라, Segmentation의 세부 문제를 나눌 수 있습니다.



## semantic segmentation

> 전통적인 기법, 픽셀별로 어디에 속하는지,

슬라이딩 윈도우방식으로 매 픽셀단위로 분류







## instance segmentation

> 오브젝트 찾고 세그멘테이션 하는게 인스턴스 세그멘테이션







### 문제 접근 방식 정의 - Semantic Segmentation

본격적으로 프로젝트 시작 전, 프로젝트가 어떤 Task인지 정의했습니다.

딥러닝을 이용한 이미지 처리 분야에서 가장 자주 다루게 되는 Task는 다음과 같습니다.

##### 1. Classification

- 입력으로 주어진 이미지 안의 객체(Object)의 종류(Class)를 구분하는 Task입니다.
- 예시) MNIST 데이터 세트의 경우, 0부터 9까지 총 10가지의 숫자들을 각각의 Class로 구분.

##### 2. Localization

- 입력으로 주어진 이미지 안의 객체가 이미지 안의 어느 위치에 존재하는지 위치 정보를 판단하는 Task입니다.
- 위치 정보의 형태는 주로 Bounding Box를 많이 사용합니다.

##### 3. Object Detection

- 일반적으로 Classification과 Localization을 동시에 수행합니다.
- 입력으로 주어진 이미지 안의 객체 위치(Localization)와 해당 객체의 종류(Classification)를 출력하는 Task입니다.

##### 4. Segmentation

- 
- 
- Instance Segmentation
  - 분할의 기본 단위를 **사물**로 설정한 분할 문제입니다.
  - 만일 두 개 이상의 사물이 동일한 클래스에 속하더라도, 서로 다른 사물에 해당하면 이들은 서로 다른 예측 마스크값을 가집니다.
- Semantic Segmentation
  - 분할의 기본 단위를 **클래스**로 설정한 분할 문제입니다.
  - 만일 두 개 이상의 사물이 동일한 클래스에 해당하면 이들은 서로 같은 예측 마스크값을 가집니다.

![img](images/Segmentation/semantic_and_instance_segmentation.png)

다시 정리하면 모델은 **주어진 차량 이미지 내의 파손 영역과 파손 종류를 픽셀 단위로 분류**해야 합니다.

이미지 단위가 아닌 픽셀 단위로 “이 픽셀이 파손에 해당하는가?”에 대한 판별이 필요하기 때문에 **Segmentation 문제**에 속하며, 서로 떨어져 있는 파손 영역이라도 동일한 종류의 파손일 경우 **클래스에 기반하여** 하나의 동일한 예측 마스크값을 가져야 합니다.

이러한 점들을 고려했을 때, 모델이 수행해야 하는 행위를 기술적으로 분류 시, **Semantic Segmentation**에 속한다고 설정할 수 있습니다.