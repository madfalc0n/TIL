# 파이썬 함수들



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

      