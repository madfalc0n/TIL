# DJANGO

<img src="images/Django/image-20200218191654448.png" alt="image-20200218191654448" style="zoom:80%;" />

> 파이썬의 경량 웹 프레임워크, 플라스크의 단점을 보완

## 정의

**장고**(Django, FAQ 발음으로는 "쟁고"([IPA](https://ko.wikipedia.org/wiki/위키백과:IPA): [ˈdʒæŋgoʊ])[[2\]](https://ko.wikipedia.org/wiki/장고_(웹_프레임워크)#cite_note-2))는 [파이썬](https://ko.wikipedia.org/wiki/파이썬)으로 작성된 [오픈 소스](https://ko.wikipedia.org/wiki/오픈_소스) [웹 애플리케이션 프레임워크](https://ko.wikipedia.org/wiki/웹_애플리케이션_프레임워크)로, [모델-뷰-컨트롤러](https://ko.wikipedia.org/wiki/모델-뷰-컨트롤러)(MVC) 패턴을 따르고 있다. 현재는 [장고 소프트웨어 재단](https://ko.wikipedia.org/wiki/장고_소프트웨어_재단)에 의해 관리되고 있다.

고도의 [데이터베이스](https://ko.wikipedia.org/wiki/데이터베이스) 기반 웹사이트를 작성하는 데 있어서 수고를 더는 것이 장고의 주된 목표이다. 장고는 콤포넌트의 재사용성(reusability)과 플러그인화 가능성(pluggability), 빠른 개발 등을 강조하고 있다. 또한, "DRY(Don't repeat yourself: [중복배제](https://ko.wikipedia.org/wiki/중복배제))" 원리를 따랐다. 설정 파일부터 데이터 모델에까지 파이썬 언어가 구석구석에 쓰였다.

> 출처: 위키백과 [장고_위키백과](https://ko.wikipedia.org/wiki/%EC%9E%A5%EA%B3%A0_(%EC%9B%B9_%ED%94%84%EB%A0%88%EC%9E%84%EC%9B%8C%ED%81%AC))



### 특징

장고는 파이썬으로 코딩한 모델을 관계형 데이터베이스로 구축해주는 모델(Model), HTTP 요청을 처리하는 웹 템플릿 시스템인 뷰(View), URL의 라우팅을 처리하는 URL 컨트롤러 (Controller) 로 구성된 **MVC** 디자인 패턴을 따른다. 하지만 전통적인 MVC 디자인 패턴에서 이야기하는 컨트롤러의 기능을 프레임워크를 자체에서 하기 때문에 모델(Model), 템플릿(Template), 뷰(View)로 분류해 **MTV** 프레임워크라고 보기도 한다.

#### 모델

모델은 데이터에 관한 정보를 담는다. 데이터에 대한 접근, 검증, 작동과 데이터 사이의 관계를 정의하는데, 일반적으로 각각의 모델은 데이터베이스에서 테이블에 해당한다. 장고에서는 모델을 정의할 때 필드의 종류를 지정해줘야 하는데, 이것이 데이터베이스에게 컬럼 타입을 알려주고 HTML 폼으로 표시 될 때의 입력 타입도 내포하는 역할을 한다. 또한 장고의 폼 자동 생성 API 를 이용할 때 데이터 검증에 쓰이기도 한다.

#### 뷰

어떤 데이터가 표시될 것인지를 정의한다. 뷰는 HTTP 응답(response)를 반환해야 하며 응답의 종류는 웹 페이지, 리디렉션, 문서 등의 다양한 형태가 가능하다. 장고에는 자주 사용되는 형태의 뷰를 패턴화하여 추상화 해둔 재사용 가능한 뷰들을 내장해 놓았는데, 이들을 제네릭 뷰(generic view) 라고 하며 원하는 제네릭 뷰를 상속한 클래스 뷰를 생성하여 사용할 수 있다.

#### 템플릿

데이터가 어떻게 표시되는 지를 정의한다. 템플릿은 사용자에게 실제로 보여지는 웹 페이지나 문서를 다룬다. 흔히 HTML 에 기반해서 템플릿을 만들며, HTML 에 동적인 요소를 추가하기 위해 파이썬의 일부 기능을 쓰게 도와주는 장고 템플릿 태그가 존재한다.





## 설치

- bash 쉘에서 `pip install django` 입력

  <img src="images/Django/image-20200213092647790.png" alt="image-20200213092647790" style="zoom:50%;" />



## 사용해보기

장고는 다음의 프로세스를 거치면 끝이다. 

1. 프로젝트 생성
2. urls.py 지정
3. views.py 설정





### 프로젝트 생성

- `django-admin startproject [프로젝트명]` 입력 후 프로젝트 생성

  ```bash
  (base) C:\Users\student\KMH\Image-analysis-and-develope\WEB\20200213>django-admin startproject mysite
  #해당경로에 mysite라는 폴더가 생성됨 
  ```

  ![image-20200213093001958](images/Django/image-20200213093001958.png)

![image-20200213093340110](images/Django/image-20200213093340110.png)

- 프로젝트의 템플릿과 DB 등의 다양한 설정은 `setting.py` 에서 설정함
- 웹의 도메인 설정은 `urls.py`에서 수정 가능



### 웹 서버 실행

- bash 쉘에서 `python manage.py runserver` 입력
- 서버는 default로 **8000번 포트**를 사용함

![image-20200213093613213](images/Django/image-20200213093613213.png)

<img src="images/Django/image-20200213093802389.png" alt="image-20200213093802389" style="zoom:50%;" />



### 초기 APP 설치

- bash **프로젝트 상위폴더**에서 `python manage.py startapp myapp` 입력

![image-20200213094009511](images/Django/image-20200213094009511.png)

![image-20200213094059892](images/Django/image-20200213094059892.png)

> 대부분 app 부분에서 설정을 한다고 함



### view.py 파일 설정

- 생성한 APP(myapp) 폴더의  **view.py**에서 다음과 같이 코드를 작성함
- view는 어떤요청이 왔을 때 어떻게 보여줄 지 설정하는 부분임(view + control)

```python
from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.
def index(request):
    return HttpResponse("Hello DJango!!!")

def test(request):
    return HttpResponse("test mode!!")
#새로운 객체가 생성되면 import 해주어야 함
#어떤 url이 들어왔을 때 실행시켜줘야 할지 설정해야 함

```

### urls.py 파일 설정

#### 1. 프로젝트 메인 urls.py 설정

- 위 작성한 함수를 실행되기 위해서는 `mysite - urls.py`  에서 아래와 같이 **include 모듈과 urlpattern**을 설정해주어야 함

```python
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('',include('myapp.urls')), #사용자가만든 myapp이라고하는 urls를 include 하라는 의미, 내가만든 어플리케이션을 참고해서 추가시켜주라는 의미로해석하면 됨
    path('admin/', admin.site.urls), # default 설정 , admin.site.urls(기본 패키지) 를 include 하라는 의미
]
```

#### 2. 생성한 APP의 urls.py 설정

- `mysite - myapp`에서 `url.py`를 생성 후  `view.py`에서 생성한 함수를 아래와 같이 지정해주어야 함

```python
from django.urls import path
from . import views # '.' current 폴더의 의미, 현재폴더에서 views.py를 import 하라는 의미

urlpatterns = [
    path('',views.index), #views.py 에 있는 index라는 함수를 실행시켜 달라는 의미
    path('test', views.test),#views.py 에 있는 test라는 함수를 실행시켜 달라는 의미
]
```

### 접속테스트

- 실행해서 변경사항 확인 하기

<img src="images/Django/image-20200213101140557.png" alt="image-20200213101140557" style="zoom:80%;" /><img src="images/Django/image-20200213101525638.png" alt="image-20200213101525638" style="zoom:80%;" />

- 만약 url을 지정하지 않은 경로로 접속 할 경우 다음과 같은 에러가 발생함

<img src="images/Django/image-20200213101625407.png" alt="image-20200213101625407" style="zoom:50%;" />





### html 템플릿 생성해서 호출하기

#### 1. `settings.py`에서 설정

- TEMPLATES - DIRS에서 아래와 같이 html 파일을 불러올 경로를 설정

![image-20200213104025236](images/Django/image-20200213104025236.png)

#### 2. templates 폴더에 `html` 파일 생성



#### 3. Views 및 urls 에서 설정







### 이미지 저장할 `Static`폴더 설정하기

#### 1. `settings.py`에서 아래와 같이 설정 후 `static` 폴더 생성

<img src="images/Django/image-20200213112332487.png" alt="image-20200213112332487" style="zoom:80%;" /><img src="images/Django/image-20200213112644748.png" alt="image-20200213112644748" style="zoom:80%;" />

#### 2. 해당 폴더에 속해있는 이미지 호출

####  <img src="images/Django/image-20200213112746766.png" alt="image-20200213112746766" style="zoom:50%;" />





### 아이디, 패스워드 만들어보기

#### 1. static 폴더에 login.html 생성

```python
#login.html 에 아래 소스코드 붙여넣기
<meta charset="UTF-8"> #인코딩 안해주면 한글 깨짐
<form action ='/login' method="GET"> #액션 실행 시, '/login'으로 id,pwd 값을 전달

    id <input type=text name=id> <br>
    pwd <input type=text name=pwd> <br>
    <input type="submit" value='로그인'>
    
</form>
```

<img src="images/Django/image-20200213113257747.png" alt="image-20200213113257747" style="zoom:80%;" /><img src="images/Django/image-20200213114937239.png" alt="image-20200213114937239" style="zoom:80%;" />

> 한글이 깨지는 현상이 있다... UTF-8 로 인코딩 해야 함



#### 2. views.py, urls.py에 아래와 같이 추가

```python
#views.py 에서 아래 함수를 추가
def login(request):
    return HttpResponse("login 성공~~")

#myapp - urls.py 에서 아래 구문 추가
path('login',views.login),
```

<img src="images/Django/image-20200213114831362.png" alt="image-20200213114831362" style="zoom:80%;" /><img src="images/Django/image-20200213114847642.png" alt="image-20200213114847642" style="zoom:80%;" />

#### 3. login 성공 및 실패여부 간단하게 만들어보기

- id와 pwd 값이 같을 경우 성공, 다를경우 실패로 반환해주기

```python
#views.py에서 아래 함수를 다음과 같이 수정
def login(request):
    id = request.GET['id']
    pwd = request.GET['pwd']
    if id == pwd :
        return HttpResponse("login 성공~~")
    return HttpResponse("login 실패ㅠㅠ")
```

<img src="images/Django/image-20200213130505225.png" alt="image-20200213130505225" style="zoom:80%;" /><img src="images/Django/image-20200213130434408.png" alt="image-20200213130434408" style="zoom:80%;" />

> ip와 pwd 가 같을 경우와 다른경우









## `HttpResponse`와 `render`와 `redirect`차이

`HttpResponse`는 응답을 반환하는 가장 기초함수, 항상 응답코드를 200 OK 로 전달하며 아래와 같이 쓸 수 있다.

```python
#메인 urls.py
from django.contrib import admin
from django.urls import path, include
urlpatterns = [
    path('blog/', include('blog.urls')),
]

#urls.py
from django.urls import path
from . import views
urlpatterns = [
    path('',views.index),
]

#views.py
from django.http import HttpResponse
def index(request):
    return HttpResponse('ok')
```

<img src="../web/images/Web/image-20200218174734287.png" alt="image-20200218174734287" style="zoom:80%;" />





`render`는 페이지를 요청하면서 템플릿을 context와 같이 반환 하는 것이고 아래와 같이 쓸 수 있다.

```python
#views.py
from django.shortcuts import render
def detail(request,pk):
    print(Post)
    p = get_object_or_404(Post, pk=pk)
    return render(request, 'blog/detailview.html', {'data':p})
```

<img src="../web/images/Web/image-20200218180520321.png" alt="image-20200218180520321" style="zoom:80%;" />

이런식으로 템플릿에 context를 반영해서 출력 해줌



`redirect`는 클라이언트 측에 해당 url에 대해 **다시 접속**하라는 응답을 보냄(응답코드 304)

주로 로그인 기능에서 사용하며 http 접속 시 https 로 redirect 할 때도 사용

```python
# views.py
from django.shortcuts import redirect
def my_view(request):
    return redirect('view_name')             # view_name 사용
    # return redirect('/blog/list')                  # 상대 경로 
    # return redirect('https://www.naver.com/') # 절대 경로 
```







## 문제점들

입력과 출력이 항상 같아야 함

내브라우저에서 접속을 했냐 안했느냐, 유저들이 다 구분되어야 한다.

- 로그인 후 반환문을 `return service(request)`를 사용하면 아래와 같이 메인 서비스로 이동된다. 저상태에서 새로고침을 할 경우 계속 로그인을 시도하게 되는 셈이다. 문제인 상황이다.

<img src="images/Django/image-20200213134351613.png" alt="image-20200213134351613" style="zoom:80%;" /><img src="images/Django/image-20200213134306054.png" alt="image-20200213134306054" style="zoom:80%;" />







### 보안관련 설정

- 장고에서는 쿠키베이스와 세션베이스로 설정이 가능하다.
- 쿠키베이스로 하면 보안에 좀 취약하긴 함 , 클라이언트 브라우저에 저장됨

- 세션베이스로 하면 서버에서 세션을 관리하므로 보안에 강함
- 서버에서 어떤내용을 가지고 있나?  세션 설정 방법
- 해킹공격방법중 `CSRF` 보호

#### 세션 설정방법

#### 1. views.py 설정

- `requset.session['user'] = id `

```python
def login(request):
    id = request.GET['id']
    pwd = request.GET['pwd']
    if id == pwd :
        request.session['user'] = id
        return redirect('/service')
    return redirect("static/login.html")
    
def service(request):
    if request.session.get('user', '') == '': #만약 세션 값이 없다면
        return redirect('/static/login.html') # 로그인 페이지로 리다이렉트
    html = 'main service<br> ' + request.session.get('user') + '님 감사합니다 어서오세요'
    return HttpResponse(html) #세션이 존재한다면 메인 서비스로 이동
```

#### 2. DB 설정

- bash에서 `python manage.py migrate`입력 후 DB에서 세션을 초기화 시켜줘야 함
- 초기화 시켜주지 않으면 에러가 발생 

![image-20200213142809960](images/Django/image-20200213142809960.png)

![image-20200213142851297](images/Django/image-20200213142851297.png)

#### 3. 접속 확인

- 브라우저를 닫고 일정 시간 내에 다시 실행하면 로그인을 유지하는 것처럼 뜸
- 크롬의 게스트 모드에서 브라우저를 닫고 다시 로그인 하면 세션유지가 되지 않음

![image-20200213142933013](images/Django/image-20200213142933013.png)

