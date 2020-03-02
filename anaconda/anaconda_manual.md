# 아나콘다 가상환경 메뉴얼

## 정의

아나콘다(Anaconda)는 패키지 관리와 디플로이를 단순케 할 목적으로 과학 계산(데이터 과학, 기계 학습 애플리케이션, 대규모 데이터 처리, 예측 분석 등)을 위해 파이썬과 R 프로그래밍 언어의 **자유-오픈 소스 배포판**이다. 패키지 버전들은 패키지 관리 시스템 conda를 통해 관리된다. 아나콘다 배포판은 1300만 명 이상의 사용자들이 사용하며 윈도우, 리눅스, macOS에 적합한 1,400개 이상의 유명 데이터 과학 패키지가 포함되어 있다.

쉽게말하면 아나콘다는 윈도우 리눅스 macOS 에서 자신이 원하는 패키지들을 이용하여 가상환경을 구현할 수 있고 시뮬레이션 하기 위한 툴이라고 생각하면 된다.

> 출처는 [위키백과](https://ko.wikipedia.org/wiki/아나콘다_(파이썬_배포판))


## 0. 기타 명령어

 - `conda --version `

   - 아나콘다 버전 확인

     <img src="/images/anaconda_manual/image-20200302194501728.png" alt="image-20200302194501728" style="zoom:80%;" />

 - `conda search python`

   - 아나콘다에 설치된 파이선 버전에 대한 목록을 불러옴

     <img src="/images/anaconda_manual/image-20200302194524063.png" alt="image-20200302194524063" style="zoom:80%;" />

- `conda list`

  - 아나콘다에 설치된 패키지 정보를 불러옴

    <img src="/images/anaconda_manual/image-20200302194553049.png" alt="image-20200302194553049" style="zoom:80%;" />

## 1. 가상환경 설치 및 실행

 - `conda create -n [이름] python=[버전]`

   - conda create -n python374 python=3.7.4

     - `python374` 이름으로 python 버전이 3.7.4 인 가상환경을 생성한다.

     <img src="/images/anaconda_manual/image-20200302194736442.png" alt="image-20200302194736442" style="zoom:80%;" />

     <img src="/images/anaconda_manual/image-20200302194834068.png" alt="image-20200302194834068" style="zoom:80%;" />

     - 여기서 y를 입력하게 될 경우 가상환경이 생성 진행된다.

       <img src="/images/anaconda_manual/image-20200302194932240.png" alt="image-20200302194932240" style="zoom:80%;" />

- `conda activate [생성한환경이름]`을 입력하여 활성화 모드로 전환한다.

  <img src="images/anaconda_manual/image-20200302195312019.png" alt="image-20200302195312019" style="zoom:80%;" />



## 2. 가상환경 제거

 - `conda remove --name [생성했던 가상환경 이름] --all`

    - 생성했던 가상환경을 제거함

      <img src="images/anaconda_manual/image-20200302200213808.png" alt="image-20200302200213808" style="zoom:80%;" />

      y를 입력하게되면 해당 가상환경이 제거됨



## 3. 생성한 가상환경 리스트 확인

 - `conda info --envs`

    - 생성했던 모든 가상환경 리스트가 출력됨

      <img src="images/anaconda_manual/image-20200302195541961.png" alt="image-20200302195541961" style="zoom:80%;" />



 - `conda info`

    - 현재 activate 되어있는 가상환경의 상세정보가 나옴, conda 버전부터 파이썬 버전, 패키지 설치되어 있는 경로 등등

      <img src="images/anaconda_manual/image-20200302195610172.png" alt="image-20200302195610172" style="zoom:80%;" />



## 4. 가상환경 종료

 - `conda deactivate`

```bash
(python374) C:\Users\student>conda deactivate
(base) C:\Users\student>
```

## 5. 가상환경 캐시삭제

 - `conda clean --all`
   - 아나콘다의 clean 명령어를 통해서 캐시를 삭제할 수 있다. 인덱스 캐시, 잠긴 파일, 사용하지 않는 패키지, 소스 캐시 등을 삭제할 수 있다.

## 6. 모듈관련 설치

 - `conda install [모듈이름]`

    - 내가 사용하고자하는 모듈을 설치함

    - 콘다 명령어를 통해 모듈이 설치되지 않는다면 `pip install [모듈이름]`이용하여 모듈을 설치해도 된다.

      <img src="images/anaconda_manual/image-20200302200804850.png" alt="image-20200302200804850" style="zoom:80%;" />



## 7. 가상환경에 설치된 모듈 내용 export 후 import

아나콘다에서는 가상환경 정보를 export 하고 import 할 수 있는 기능이 존재한다.`yaml`형식으로 옮겨지며 내용은 가상환경에 설치되어 있는 모듈에 대한 정보가 들어가 있다.

<img src="images/anaconda_manual/image-20200302201723693.png" alt="image-20200302201723693" style="zoom:50%;" />

참고해야할 점은 가상환경을 export 후 import 할 때 같은 운영체제간에는 잘 옮겨지지만 **서로 다른 운영체제(예를들어 윈도우에서 리눅스환경으로 전환 시)**인 경우 yml 내에 명시된 모듈을 설치하는 과정에서 에러가 발생할 수 있다. 

각각의 운영체제에서만 지원하는 모듈이 있기 때문에 **에러가 발생하는 모듈정보는 삭제 후 진행**해야 하는 경우가 있다.

### 1. 가상환경에 저장된 모듈정보 export 하기

- `export` 할 가상환경 `activate` 후 아래의 명령어 입력

  - conda activate [export할 가상환경이름]
  - `conda env export > [아무파일명].yaml`

  ```bash
  (base) C:\Users\student\Downloads>conda activate py36
  
  (py36) C:\Users\student\Downloads>conda env export > py36.yaml
  ```

### 2. export 했던 yml 파일 import 하기

- `conda env create -f [export 한 파일명]`
  - export 했던 가상환경 파일을 import 하기 위한 명령어



## 8. 가상환경 이름변경

> 따로 이름만 변경은 불가하다. 새로 clone 생성 후 기존 환경을 제거해주면 된다.

- `conda create --name [신규이름] --clone [기존이름]`
- `conda env remove --name [기존이름]`