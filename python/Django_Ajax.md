# Ajax(Asynchronous Javascript And XML)

> 자바스크립트와 XML을 이용한 비동기 방식의 연동 방법론



## 정의

클라이언트 화면에서 javascript 또는 jQuery 로 서버에 자료를 요청하면 **현재 페이지의 화면 전환 없이** 서버에서 XML 또는 JSON 데이터 자료를 전송한다.



## 기존 기술과의 차이점

기존의 [웹 애플리케이션](https://ko.wikipedia.org/wiki/웹_애플리케이션)은 브라우저에서 [폼](https://ko.wikipedia.org/wiki/폼)을 채우고 이를 웹 서버로 제출(submit)을 하면 하나의 요청으로 웹 서버는 요청된 내용에 따라서 데이터를 가공하여 새로운 웹 페이지를 작성하고 응답으로 되돌려준다. 이때 최초에 폼을 가지고 있던 페이지와 사용자가 이 폼을 채워 결과물로서 되돌려 받은 페이지는 일반적으로 유사한 내용을 가지고 있는 경우가 많다. 결과적으로 **중복되는 [HTML](https://ko.wikipedia.org/wiki/HTML) 코드를 다시 한번 전송을 받음으로써 많은 대역폭을 낭비하게 된다**. 대역폭의 낭비는 금전적 손실을 야기할 수 있으며 사용자와 대화(상호 반응)하는 서비스를 만들기 어렵게도 한다.

반면에 Ajax 애플리케이션은 **필요한 데이터만을 웹서버에 요청**해서 받은 후 클라이언트에서 데이터에 대한 처리를 할 수 있다. 보통 [SOAP](https://ko.wikipedia.org/wiki/SOAP)이나 [XML](https://ko.wikipedia.org/wiki/XML) 기반의 웹 서비스 프로토콜이 사용되며, 웹 서버의 응답을 처리하기 위해 클라이언트 쪽에서는 [자바스크립트](https://ko.wikipedia.org/wiki/자바스크립트)를 쓴다. [웹 서버](https://ko.wikipedia.org/wiki/웹_서버)에서 전적으로 처리되던 데이터 처리의 일부분이 클라이언트 쪽에서 처리 되므로 웹 브라우저와 웹 서버 사이에 교환되는 데이터량과 웹서버의 데이터 처리량도 줄어들기 때문에 애플리케이션의 응답성이 좋아진다. 또한 웹서버의 데이터 처리에 대한 부하를 줄여주는 일이 요청을 주는 수많은 컴퓨터에 대해서 일어나기 때문에 **전체적인 웹 서버 처리량도 줄어들게 된다**.

<img src="images/Django_Ajax/image-20200214095755033.png" alt="image-20200214095755033" style="zoom:80%;" />

> [출처] [위키백과](https://ko.wikipedia.org/wiki/Ajax)









개발속도 향상 방식?

서버와 데이터를 교환하는 기술방식 중 하나



CDN 서비스

j쿼리 api

이미지 없을 떄 실시간으로 웹에서 가져오고 로컬에 있으면 로컬에서 읽어옴





## 사용해보기

Django에서 Ajax를 사용해보자!

### Ajax 폴더 생성 및 테스트

- Django 프로젝트에서 `python manage.py startapp ajax`입력 후 `ajax`폴더 생성됨 확인

<img src="images/Django_Ajax/image-20200214094639632.png" alt="image-20200214094639632" style="zoom:80%;" />

![image-20200214094858346](images/Django_Ajax/image-20200214094858346.png)

- 메인 `urls.py` 에 ajax와 관련해서 추가하고 ajax 폴더에도 `urls.py` 생성 후 아래와 같이 작성

<img src="images/Django_Ajax/image-20200214100214864.png" alt="image-20200214100214864" style="zoom:80%;" /><img src="images/Django_Ajax/image-20200214100220794.png" alt="image-20200214100220794" style="zoom:80%;" />



- 접속테스트

<img src="images/Django_Ajax/image-20200214101008282.png" alt="image-20200214101008282" style="zoom:80%;" />

### path 플로우

<img src="images/Django_Ajax/image-20200214141118998.png" alt="image-20200214141118998" style="zoom:80%;" />

<img src="images/Django_Ajax/image-20200214160522351.png" alt="image-20200214160522351" style="zoom:80%;" />

> 2020-02-13에 했던 실습내용에 대한 프로젝트를 그대로 옮긴 후 ajax를 추가하였다. 진행 내용에 대해 궁금하면 [Django](), [실습내용]()한번 보시길





### 계산기 만들어보기



### 로그인 페이지 만들어보기



### 이미지 업로드 상태표시바 만들어보기



### 파이썬코드 실행에 따른 결과 표시 만들어보기

입력에 대한 출력 결과들을  stringIO를 통해  메모리에 저장하도록 설정 -> 메모리에 저장된 결과를 변수에 저장하고 표준 출력 장치로 전송



메모리에 보관하기위해 아래 설정

```python
#파이썬 컴파일하기위한 모듈
import sys
from io import StringIO 

code = request.GET['code'] # code 변수에 받아옴
original_stdout = sys.stdout # 기존 출력값 백업 
# sys.stdout는 표준 출력 스트림으로 기본적으로 콘솔에 결과값을 출력함

sys.stdout = StringIO() #메모리에 읽고 저장하도록 사용
#출력결과들이 메모리에 저장되면서 콘솔에 결과값이 출력되지 않음

exec(code) #파이썬 코드를 실행시켜주는 인터프리터
contents = sys.stdout.getvalue() #메모리에 저장된 내용(실행결과)을 contents 변수에 저장
sys.stdout = original_stdout #다시 원상태로 복귀

print(contents) # 코드 결과가 담겨잇다.
```





## 실습

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/web/20200214/mysite)