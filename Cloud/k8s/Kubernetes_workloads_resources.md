# K8s Workloads Resources

워크로드는 쿠버네티스에서 구동되는 애플리케이션이다. 워크로드가 단일 컴포넌트이거나 함께 작동하는 여러 컴포넌트이든 관계없이, 쿠버네티스에서는 워크로드를 일련의 [파드](https://kubernetes.io/ko/docs/concepts/workloads/pods) 집합 내에서 실행한다. 쿠버네티스에서 파드는 클러스터에서 실행 중인 [컨테이너](https://kubernetes.io/ko/docs/concepts/containers/) 집합을 나타낸다.

파드에는 정의된 라이프사이클이 있다. 예를 들어, 일단 파드가 클러스터에서 실행되고 해당 파드가 실행 중인 [노드](https://kubernetes.io/ko/docs/concepts/architecture/nodes/)에서 심각한 오류가 발생하게 되면 해당 노드의 모든 파드가 실패한다. 쿠버네티스는 이 수준의 실패를 최종적으로 처리한다. 나중에 노드가 복구되더라도 새 파드를 만들어야 한다.

그러나, 작업이 훨씬 쉽도록, 각 파드를 직접 관리할 필요는 없도록 만들었다. 대신, 사용자를 대신하여 파드 집합을 관리하는 *워크로드 리소스* 를 사용할 수 있다. 이러한 리소스는 지정한 상태와 일치하도록 올바른 수의 올바른 파드 유형이 실행되고 있는지 확인하는 [컨트롤러](https://kubernetes.io/ko/docs/concepts/architecture/controller/)를 구성한다.

> 출처 : [쿠버네티스 공식문서](https://kubernetes.io/ko/docs/concepts/workloads/)

## 1. Deployment or ReplicaSet



## 2. StatefulSet



## 3. DaemonSet



## 4. Job or CronJob

