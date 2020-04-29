# Python List 의 append 와 extend 의 차이?

- append

  append는 리스트의 끝에 리스트(b)1개를 넣는다. 있는 그대로 넣는다고 생각하면 된다.

```python
#append
a = [1,2,3,4,5]
b = [1,2,3]
a.append(b)
print(a)
#결과
#[1, 2, 3, 4, 5, [1, 2, 3]]

a = [1,2,3,4,5]
b = [[1,2,3]]
a.append(b)
print(a)
#결과
#[1, 2, 3, 4, 5, [[1, 2, 3]]]

a = [1,2,3,4,5]
b = 'apple'
a.append(b)
print(a)
#결과
#[1, 2, 3, 4, 5, 'apple']
```



- extend

  extend는 리스트 끝에 `iterable`의 모든 항목을 넣는다. 리스트를 풀어서 넣는다. 문자열일 경우 한 문자로 나뉘어 넣는다. 하나를 벗겨서 넣는다고 생각하면된다.

```python
#extend
a = [1,2,3,4,5]
b = [1,2,3]
a.extend(b)
print(a)
#결과
#[1, 2, 3, 4, 5, 1, 2, 3]

a = [1,2,3,4,5]
b = 'apple'
a.extend(b)
print(a)
#결과
#[1, 2, 3, 4, 5, 'a', 'p', 'p', 'l', 'e']

a = [1,2,3,4,5]
b = ['apple']
a.extend(b)
print(a)
#결과
#[1, 2, 3, 4, 5, 'apple']
```

