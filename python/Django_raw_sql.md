# Django raw SQL

장고에서는 model layer를 수행하지 않고 DB에 **직접적**으로 SQL 실행이 가능하도록 하는 기능이다.



## 0. 주의사항

raw SQL을 사용할 경우 **SQL injection**에 각별히 주의해야 한다. 제어와 관련된 모든 매개 변수를 **escape** 해야하며 자세한 내용은 [SQL inection 문서](https://docs.djangoproject.com/en/3.0/topics/security/#sql-injection-protection) 를 참조해보라 



## 1. 사용해보기 - 1/2

우선 사용해보기 전에 DB에 테이블이 있어야 한다. 이 점 참고하고 나는 미리 테이블을 만들어 놓았다.

<img src="images/Django_raw_sql/image-20200221183941932.png" alt="image-20200221183941932" style="zoom:80%;" />

<img src="images/Django_raw_sql/image-20200221184555721.png" alt="image-20200221184555721" style="zoom:80%;" />



> `DB Browser for SQLite` 를 통해 Django 프로젝트의 `db.sqlite3`를 불러왔다. `db.sqlite3`는 프로젝트 내 모든 데이터 정보가 담겨있다.

### 1.1 모듈 호출

Django db에 속해있는 `connection`  모듈을 호출한다.

```python
from django.db import connection 
```

### 1.2 객체 선언 및 쿼리 요청 테스트

쿼리를 실행하기 이전에 미리 구문을 작성해서 불러와야 한다. 나는 `auth_user`테이블에서 `username`이 '이순신'인 사람이 작성한 데이터를 출력하고 싶었다. 즉 '이순신'이라는 사람이 작성한 글을 모두 호출하기위해 아래의 sql 구문을 선언하였다.

<img src="images/Django_raw_sql/image-20200221184941911.png" alt="image-20200221184941911" style="zoom:80%;" />

> `SELECT id from auth_user where username  = '이순신'`에 대한 결과는 `2`가 나오게된다. 즉 author_id 가 `2`인 글들에 대해 호출하고자 한다.

```python
username = '이순신'
category = 'common'
#데이터 호출을 위한 sql 선언
sql =f""" 
    SELECT id, title, cnt
    from myboard_board
    where author_id = (SELECT id from auth_user where username  = '{username}') and category ='{category}'
"""

cursor = connection.cursor()
cursor.execute(sql)
```

<img src="images/Django_raw_sql/image-20200221185150033.png" alt="image-20200221185150033" style="zoom:80%;" />

> sql 에 대해 쿼리한 결과이며 총 6개의 데이터가 출력되는 것을 확인 할 수 있다.



### 1.3 Django를 통해 WEB에서 결과 출력하기

sql 결과를 Django를 통해 WEB에서 결과로 출력해보고자 한다. 결과는 다음과 같았다.

<img src="images/Django_raw_sql/image-20200221185702131.png" alt="image-20200221185702131" style="zoom:80%;" />

> 페이지 별로 3개의 게시글을 출력하도록 작성하였다. 해당 구현 코드는 아래 깃허브를 링크로 연결해놓겠다.



## 2. 사용해보기 -2/2

두 번째로는 유저별로 저장소에 이미지 파일을 업로드 하고 개수만큼 출력하는 것이다. 이전 단계에서 이미지 관련 테이블을 추가적으로 만들었다. 

<img src="images/Django_raw_sql/image-20200221190309923.png" alt="image-20200221190309923" style="zoom:80%;" />



테이블에 저장된 데이터 만큼 web에서 표시를 해주기 위해선 먼저 이미지 업로드 마다 데이터를 테이블에 넣어주는 쿼리구문을 만들어야 했다. 구문은 다음과 같다.

```python

```







<img src="images/Django_raw_sql/image-20200221190429431.png" alt="image-20200221190429431" style="zoom:80%;" />

> DB 테이블에 존재하는 개수만큼 WEB 서버에서 해당 이미지들이 출력 되는 것을 확인 할 수 있었다.







## 3. 실습자료

- [실습자료](https://github.com/madfalc0n/Image-analysis-and-develope/tree/master/web/20200221/mysite)



1. 모듈 호출 후 객체 선언 및 사용