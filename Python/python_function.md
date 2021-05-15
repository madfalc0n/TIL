## 파이썬 함수들



- Counter( list  )

  - 모듈 호출 from collections import Counter

  - 사용예시

    ```python
    d = Counter([0,0,0,0,0,0,0,1,2,3,4,12,4])
    print(d)
    Counter({0: 7, 4: 2, 1: 1, 2: 1, 3: 1, 12: 1})
    print(d.most_common())
    [(0, 7), (4, 2), (1, 1), (2, 1), (3, 1), (12, 1)]
    ```

- math 함수

  - 복잡한 연산이 필요한 경우 사용, 함수가 많으므로 필요할 때 찾아봐야 할 듯 하다

  - [math관련 doc 문서](https://docs.python.org/ko/3.7/library/math.html)

  - ceil()

    - 소수점을 올림하여 정수로 표현 

    - 사용예시

      ```python
      from math import ceil
      
      print(130/4) #32.5
      print(ceil(130/4)) #33
      ```

- Json 관련 함수

  - Json 형식으로 된 파일을 읽고 쓸때 사용

  - json() 함수는 str형식을 dict 로 변경 json.dumps()는 dict를 str 형식으로 변경

  - 사용예시

    ```python
    #data_send는 dict형
    """
    data_send = {
            'query': 'text', 
            'sessionId': 'sessionId',
            'lang': 'ko', 
            'timezone' : 'Asia/Seoul'
        }
    """
    str_data_send = json.dumps(data_send)
    print(type(str_data_send)) #<class 'str'>
    
    str_data_send.json() #이렇게 사용해서 dict 로 변경한다.
    ```

    