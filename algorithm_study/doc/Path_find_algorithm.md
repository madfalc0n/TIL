# Path finding algorithm

길 찾기 알고리즘, 출발지 부터 목적지 까지의 거리 또는 최적의 거리를 찾기 위한 알고리즘들임


## 1. 좌/우선법

- 좌 또는 우중 한쪽 방향을 우선 선택하여 목적지까지 이동하는 경로를 탐색함
- 최선의 방법은 아니며 중복을 어느정도 줄여나갈 수 있다
- 그래서 가장 고전적인 방법이다

## 2. DFS/BFS(깊의/넓이) 우선 탐색

- 막다른 길이 나올 때까지 경로를 탐색(DFS)
- 모든 갈림길을 가까운 곳부터 탐색하여 점점 깊은 방향으로 경로 탐색 범위를 넓힘(BFS)

## 3. 다익스트라 알고리즘

- 경우의 수만큼 분신을 만들어서 경로를 탐색하고 가장 최단 거리의 분신이 이동한 경로를 최종 경로로 찾아내는 알고리즘
- 모든 분신들이 이동한 거리 중 가장 최단 경로를 가지는 분신을 선택
- 모든 경로를 탐색하고 분신을 그만큼 만들어야 하기 때문에 소모되는 비용이 큼, **최적화에는 적합하지 않다**

## 4. A*(에이스타) 알고리즘

- 다익스트라 알고리즘의 개량형으로 현재 위치에서 목표에 가장 가까운 이웃 노드를 검색하여 최단 경로를 찾아내는 알고리즘 

- 최근 나오는 길찾기 알고리즘들이 에이스타 알고리즘에서 변형되어 나온 것들임

  ### 특징

  해당 알고리즘은 3개의 Cost를 가지고 거리 측정법은 **Manhatton distance**의 식을 따른다.

  ```
  X측 이동량 = | 시작 위치의 x좌표 - 최종 위치의 x 좌표|
  Y측 이동량 = | 시작 위치의 y좌표 - 최종 위치의 y 좌표|
  총 이동량 = X측 이동량 + Y측 이동량
  ```

  1. **G(Goal) Cost**
     - 시작 노드부터 현재 노드까지 지나온 거리(실제 비용)
  2. **H(Heuristic) Cost**
     - 현재 노드부터 목표 노드까지 이동할 거리(추정 비용)
     - 이동한 거리가 중간의 장애물 노드에 의해 변경이 될 수 있으므로 추정 cost라고 부름
  3. **F(fitness) Cost**
     - G cost와 H cost의 합계(최선의 추정 비용)
     - 지금 비용과 앞으로의 비용을 합친 비용이라고 말함

  또한 5개 종류의 노드를 따른다.

  1. 시작 노드
     - 말 그대로 시작지점의 노드
  2. 목표 노드
     - 말 그대로 목표지점의 노드
  3. 장애물 노드
     - 말 그대로 갈 수 없는 노드
  4. **개방 노드**
     - 현재 노드의 이웃 노드 중 이동가능한 노드의 리스트
  5. **폐쇄 노드**
     - 장애물 노드거나, 이미 지나온 노드

  ### 방법

  ```
  PQ.push(start_node, g(start_node) + h(start_node))//우선순위 큐에 시작 노드를 삽입한다.
  while PQ is not empty//우선순위 큐가 비어있지 않은 동안
      node = PQ.pop//우선순위 큐를 pop한다.
      if node == goal_node//만일 해당 노드가 목표 노드이면 반복문을 빠져나온다.
          break
      for next_node in (next_node_begin...next_node_end)//해당 노드에서 이동할 수 있는 다음 노드들을 보는 동안
          PQ.push(next_node, g(node) + cost + h(next_node))//우선순위 큐에 다음 노드를 삽입한다.
  
  print goal_node_dist//시작 노드에서 목표 노드까지의 거리를 출력한다.
  
  ```

  1. F cost 기준으로 오름차순 우선순위 큐에 노드로 삽입한다.
  2. 우선순위 큐를 pop한다.
  3. 해당 노드에서 이동할 수 있는 노드를 찾는다.
  4. 그 노드들의 F cost 를 구한다.
  5. 그 노드들을 우선순위 큐에 삽입한다.
  6. 목표 노드에 도달할 때까지 반복한다.

  출처: [나무위키](https://namu.wiki/w/A*%20%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)
