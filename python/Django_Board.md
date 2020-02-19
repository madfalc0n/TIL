

## Django 게시판 구현하기

장고DB에 저장되어 있는 데이터를 웹에 게시하여 게시판 형식으로 구현이 가능하다.

웹 페이지에 게시글을 확인하고 수정 또는 삭제가 가능하도록 구현 하였다.

<img src="images/Django_Board/image-20200219180339211.png" alt="image-20200219180339211" style="zoom:80%;" />



## 절차

1. `mysite` 에서 `python manage.py startapp myboard`

   - 게시판을 구현하기위한 APP 생성

2. `mysite - settings.py`에 `INSTALLED_APPS` 항목에 아래와 같이 `myboard`추가

   ```python
   INSTALLED_APPS = [
       'django.contrib.admin',
       'django.contrib.auth',
       'django.contrib.contenttypes',
       'django.contrib.sessions',
       'django.contrib.messages',
       'django.contrib.staticfiles',
       'django_extensions',
       'myapp',
       'blog',
       'myboard', #APP 추가
   ]
   ```

3. `myboard`에 `models.py` 추가

   - 실제 myboard 에 대한 DB를 구성할 때의 항목들이다.
   - 아래에 보면 title, text, cnt, image, category 가 있다.

   ```python
   from django.db import models
   from django.utils import timezone
   
   
   # Create your models here.
   
   class Board(models.Model): # 기본적으로 db모듈을 제공하며 제공된 모듈을 통해 board db 생성
       author = models.ForeignKey('auth.User', on_delete=models.CASCADE) #auth.User는 시스템이 만든 테이블 , cascade 단계별로 이루어진 , 원래 특정 유저와 관련된거 다 지워야 함, on_delete 는 해당 유저 삭제시 같이 삭제하라는 옵션
       title = models.CharField(max_length=200)
       text = models.TextField()  # 글자수에 제한 없는 텍스트
       created_date = models.DateTimeField(
           default=timezone.now)  # 날짜와 시간
       cnt = models.IntegerField(default=0)
       image = models.CharField(max_length=200, null=True, blank=True)
       category = models.CharField(max_length=10, default='common')
   
   
       def __str__(self):
           return self.title
   ```

4. `myboard`에 `admin.py` 수정

   - myboard에 대한 DB 를 admin site에서 관리하기 위한 추가설정

   ```python
   from django.contrib import admin
   from . import models
   
   # Register your models here.
   admin.site.register(models.Board)
   ```

5. 쉘에서 `python manage.py makemigrations` 입력 후 `python manage.py migrate` 입력

   * models.py 가 수정될 경우 항상 `makemigrations` 를 적용해야하고(미리 db에 적용할 대상을 대기 시켜놓는다고 생각하면 됨)

   * db에 실제로 적용할 경우 `migrate`를 입력하면 된다. 

     <img src="images/Django_Blog/image-20200219173011736.png" alt="image-20200219173011736" style="zoom:80%;" />

   > admin 페이지에서 myboard DB가 생성된거 확인

6. `myboard`에  `forms.py`를 추가하고 아래 소스코드를 넣는다.

   ```python
   from django.forms import ValidationError
   from django import forms
   from . import models
   
   def validator(value) :
       if len(value) < 5 : raise  ValidationError("길이가 너무 짧아요")
   
   class BoardForm(forms.ModelForm): #forms를 상속받는 부분, 장고에서 제공되는 forms 모듈 사용
       class Meta:
           model = models.Board
           fields = ['title', 'text', 'category']
   
       def __init__(self, *args, **kwargs):
           super(BoardForm, self).__init__(*args, **kwargs)
           self.fields['title'].validators = [validator]
   ```

   <img src="images/Django_Board/image-20200219174559328.png" alt="image-20200219174559328" style="zoom:80%;" />

   - `forms.py` 는 웹에서 게시글 작성시에 대한 폼을 제시한다.
   - 장고에서 제공하는  forms 모듈이 기본적인 양식을 제공한다.

7. `myboard`에` view.py` 수정

   ```python
   from django.shortcuts import render, get_object_or_404,redirect
   from django.http import HttpResponse
   from django.views.generic import View
   from django.contrib.auth.models import User
   from django.forms import CharField, Textarea, ValidationError
   from . import forms
   from . import models
   
   
   class BoardView(View) :
       def get(self, request, pk, mode, category):
           print("보드 뷰의 현장")
           print(pk , mode, category)
           if mode =='add': # 새 데이터 추가할 경우 빈폼으로
               form = forms.BoardForm()
           
           elif mode == 'list': 
               username = '이순신' #request.session["username"]
               user = User.objects.get(username=username)
               if category == 'category':
                   data = models.Board.objects.all().filter(author=user)
               else:
                   data = models.Board.objects.all().filter(author=user, category=category)
               context = {"data":data, "username":username}
               return render(request, "myboard/list.html", context)
           
           elif mode == 'detail':
               p = get_object_or_404(models.Board, pk=pk)
               return render(request, "myboard/detailview.html", {"data":p})
           
           elif mode == 'edit' :
               post = get_object_or_404(models.Board, pk=pk)
               form = forms.BoardForm(instance=post)
           
           else:
               return HttpResponse("error")
           
           return render(request, "myboard/edit.html", {"form":form})
   
       def post(self, request, pk, mode, category):
   
           #username = request.session["username"]
           username = '이순신'
           user = User.objects.get(username=username)
   
           if pk == 0: #  신규 데이터 추가할 항목
               form = forms.BoardForm(request.POST)
               print(form)
           else: # 기존 데이터 수정
               post = get_object_or_404(models.Board , pk=pk)
               form = forms.BoardForm(request.POST, instance=post)
   
           if form.is_valid(): # 폼 작성 시 유효하지 않으면
               post = form.save(commit=False)
               if pk == 0: #새로 데이터를 추가하는 케이스
                   post.author = user
               post.save()
               return redirect("myboard",category,0, 'list') 
           return render(request, "myboard/edit.html", {"form": form})
   
   ```

   

8. template-myboard 안에 base edit... html 파일들 추가

   - bash.html

   ```html
   <font color=red size=6>My 게시판</font><br>
   로그인 사용자 :{{username}}<br>
   
   <a href="/myboard/category/0/list"> 모든게시판 </a><br>
   <a href="/myboard/data/0/list"> 자료실 </a><br>
   <a href="/myboard/common/0/list"> 일반게시판 </a><br>
   <a href="/myboard/etc/0/list"> 자유게시판 </a><br>
   
   <br>
   <hr>
   
   {% block content %}
   
   {% endblock %}
   <hr>
   
   <h5>copy right ...</h5>
   명만킴
   ```

   - list.html

   ```html
   {% extends 'myboard/base.html' %}
   
   {% block content %}
   <a href="{% url 'myboard' 'category' 0 'add'%}"> 신규 작성하기  </a> <br>
   <hr>
   
   <h5> 게시글 내용  </h5> 
   {%  for d in data %}
   <a href="{% url 'myboard' 'category' d.pk 'detail'%}"> {{d.title}} </a> 
   <a href="{% url 'myboard' 'category' d.pk 'delete'%}"> 삭제하기</a> <br>
   {% endfor %}
   
   {% endblock %}
   ```

   - edit.html

   ```html
   <script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
   <script src="http://code.jquery.com/jquery-migrate-1.2.1.min.js"></script>
   
    <style>
         .bg { background-color: #eeeeee; }
         .bd { border: 1px solid #666666; }
    </style>
   
   {% if form.title.value %}
   <h1>  수정하기 </h1>
   {% else %}
   <h1>  신규작성</h1>
   {% endif %}
   
   
   <form method=post>
      {% csrf_token %}
      	{{ form.as_p }}
   
      <input type="submit" value="작성" >
   
   </form>
   
   <script>
      $("#id_title").addClass('bg bd');
   </script>
   ```

   - detailview.html

   ```html
   {% extends 'myboard/base.html' %}   
   
   
   게시물 보기  <br>
   
   {% block content %}
       <hr>
       {{data.title}}  <br>
       {{data.text | linebreaks}}
       <hr>
       <a href="{% url 'myboard' 'category' 0 'list' %}">  리스트로 돌아가기 </a> <br>
       <a href="{% url 'myboard' 'category' data.pk 'edit'%}"> 수정하기 </a> <br>
   
   {% endblock %}
   ```

   

<img src="images/Django_Board/image-20200219173644545.png" alt="image-20200219173644545" style="zoom:80%;" /><img src="images/Django_Board/image-20200219174048079.png" alt="image-20200219174048079" style="zoom:80%;" />

> 웹 구축 후 접속화면..처음 접속은 `localhost:8000/myboard/category/0/list`로 접속을 해야 함 
>
> 장고 DB와 연동되어 있는 것을 볼 수 있다.



## 실습

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/web/20200219)