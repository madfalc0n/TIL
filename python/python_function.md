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

    

    