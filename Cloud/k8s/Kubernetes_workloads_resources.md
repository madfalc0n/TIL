# K8s Workloads Resources

워크로드는 쿠버네티스에서 구동되는 애플리케이션이다. 워크로드가 단일 컴포넌트이거나 함께 작동하는 여러 컴포넌트이든 관계없이, 쿠버네티스에서는 워크로드를 일련의 [파드](https://kubernetes.io/ko/docs/concepts/workloads/pods) 집합 내에서 실행한다. 쿠버네티스에서 파드는 클러스터에서 실행 중인 [컨테이너](https://kubernetes.io/ko/docs/concepts/containers/) 집합을 나타낸다.

파드에는 정의된 라이프사이클이 있다. 예를 들어, 일단 파드가 클러스터에서 실행되고 해당 파드가 실행 중인 [노드](https://kubernetes.io/ko/docs/concepts/architecture/nodes/)에서 심각한 오류가 발생하게 되면 해당 노드의 모든 파드가 실패한다. 쿠버네티스는 이 수준의 실패를 최종적으로 처리한다. 나중에 노드가 복구되더라도 새 파드를 만들어야 한다.

그러나, 작업이 훨씬 쉽도록, 각 파드를 직접 관리할 필요는 없도록 만들었다. 대신, 사용자를 대신하여 파드 집합을 관리하는 *워크로드 리소스* 를 사용할 수 있다. 이러한 리소스는 지정한 상태와 일치하도록 올바른 수의 올바른 파드 유형이 실행되고 있는지 확인하는 [컨트롤러](https://kubernetes.io/ko/docs/concepts/architecture/controller/)를 구성한다.

> 출처 : [쿠버네티스 공식문서](https://kubernetes.io/ko/docs/concepts/workloads/)

## 1. Deployment or ReplicaSet

### 1. Deployment

앱을 배포할 때 사용되는 기본중의 기본 컨트롤러이다. 배포를 위한 기능들을 제공한다.

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: test-web
  labels:
    app: test
spec:
  replicas: 3
  selector:
    matchLabels:
      app: test
  template:
    metadata:
      labels:
        app: test
    spec:
      containers:
      - name: test
        image: chadool116/test-web-node:v1
        ports:
        - containerPort: 8080   
        
## metadata - name : kubectl get deploy 입력시 보여지는 name

madfalcon@madfalcon:~/my_tmp/component$ kubectl get deploy 
NAME                                 READY   UP-TO-DATE   AVAILABLE   AGE
test-web                             3/3     3            3           41m

## spec 내 containers - image 본인이 업로드 한 image:tag 입력
## containerPort : DockerFile을 통해 이미지를 생성했을 때 expose port 번호, 실제 서비스 open시 생성되는 port번호

## kubectl apply -f 위.yaml 업로드 후 pod 생성되었는지, 
madfalcon@madfalcon:~/my_tmp/component$ kubectl get pods
NAME                                                  READY   STATUS    RESTARTS   AGE
test-web-6dd5c847d7-7f22d                             1/1     Running   0          43m
test-web-6dd5c847d7-s84hr                             1/1     Running   0          43m
test-web-6dd5c847d7-xl8x2                             1/1     Running   0          43m

## 웹 서비스 접속이 되는지 확인해보기
## 1. 생성된 pods의 정보를 확인해보자
madfalcon@madfalcon:~/my_tmp/component$ kubectl describe pods test-web-6dd5c847d7-7f22d
Name:         test-web-6dd5c847d7-7f22d
Namespace:    default
Priority:     0
Node:         madfalcon.slave.com/192.168.85.131
Start Time:   Thu, 03 Dec 2020 15:04:22 +0000
Labels:       app=test
              pod-template-hash=6dd5c847d7
Annotations:  <none>
Status:       Running
IP:           10.244.1.41
IPs:
  IP:           10.244.1.41
Controlled By:  ReplicaSet/test-web-6dd5c847d7
.........
.........
.........

## 2. ip를 통해 접속 테스트 확인해보자, kubectl exec -it [pod 이름] -- curl [할당된IP]:[port]
madfalcon@madfalcon:~/my_tmp/component$ kubectl exec -it test-web-6dd5c847d7-7f22d -- curl 10.244.1.41:8080
Hello World! I'm test-web-6dd5c847d7-7f22d
```







## 2. StatefulSet



## 3. DaemonSet



## 4. Job or CronJob

