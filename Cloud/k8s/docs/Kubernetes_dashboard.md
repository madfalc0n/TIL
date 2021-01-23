# Kubernetes Dashboard

쿠버네티스의 클러스터링 환경을 GUI형식으로 관리할 수 있는 웹 기반 대시보드이다. CLI 상에서 수정했던 각종 리소스(deployment, service, ingress 등...)들을 웹에서도 수정이 가능하다.

<img src="images/Kubernetes_dashboard/image-20201208031600487.png" alt="image-20201208031600487" style="zoom:50%;" />





## 1. 설치

[문서]()절차에 따라 helm을 이용하여 설치한다.

- helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard/
- helm install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard

```bash
madfalcon@madfalcon:~/my_dashboard$ helm install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard
NAME: kubernetes-dashboard
LAST DEPLOYED: Mon Dec  7 18:43:22 2020
NAMESPACE: default
STATUS: deployed
REVISION: 1
TEST SUITE: None
NOTES:
*********************************************************************************
*** PLEASE BE PATIENT: kubernetes-dashboard may take a few minutes to install ***
*********************************************************************************

Get the Kubernetes Dashboard URL by running:
  export POD_NAME=$(kubectl get pods -n default -l "app.kubernetes.io/name=kubernetes-dashboard,app.kubernetes.io/instance=kubernetes-dashboard" -o jsonpath="{.items[0].metadata.name}")
  echo https://127.0.0.1:8443/
  kubectl -n default port-forward $POD_NAME 8443:8443
```





## 2. 접속 설정

설치된 dashboard 서비스를 외부에서 접속하기 위해 keepalived를 이용하여 새로운 VIP를 생성한다. `kubectl proxy` 명령어를 이용하여 접속이 가능하지만 웹 접속용 IP를 그냥 하나 파는게 더 좋지 않을까 생각했다.

1. `/etc/keepalived/keepalived.conf`의 컨피그를 수정하여 GUI 접속용 VIP를 생성해준다. Keepalived 관련 설치 및 가이드는 [링크](https://github.com/madfalc0n/TIL/blob/master/Cloud/k8s/docs/Kubernetes_deploy_web_service.md#1-keepalived-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%85%8B%ED%8C%85)를 참고하자.

<img src="images/Kubernetes_dashboard/image-20201208035157162.png" alt="image-20201208035157162" style="zoom:50%;" />



2. edit 명령어를 이용하여 `kubernetes-dashboard`의 서비스 정보를 수정하자. 

   1. `kubectl get svc`를 입력

      <img src="images/Kubernetes_dashboard/image-20201208035615185.png" alt="image-20201208035615185" style="zoom:80%;" />

   2. `kubectl edit svc kubernetes-dashboard`를 입력하여 externalips를 추가하고 type을 변경해주자.

<img src="images/Kubernetes_dashboard/image-20201208035412792.png" alt="image-20201208035412792" style="zoom:80%;" />

<img src="images/Kubernetes_dashboard/image-20201208035917008.png" alt="image-20201208035917008" style="zoom:80%;" />



3. 아래의 명령어를 입력하여 접속용 Account를 생성한다

   ```bash
   
   # 1.Creating a Service Account
   
   cat <<EOF | kubectl apply -f -
   apiVersion: v1
   kind: ServiceAccount
   metadata:
     name: admin-user
     namespace: default
   EOF
   #CLI에 입력 후 serviceaccount/admin-user created 라는 문구가 나온다
   
   
   
   # 2.Creating a ClusterRoleBinding
   
   cat <<EOF | kubectl apply -f -
   apiVersion: rbac.authorization.k8s.io/v1
   kind: ClusterRoleBinding
   metadata:
     name: admin-user
   roleRef:
     apiGroup: rbac.authorization.k8s.io
     kind: ClusterRole
     name: cluster-admin
   subjects:
   - kind: ServiceAccount
     name: admin-user
     namespace: default
   EOF
   #CLI에 입력 후 clusterrolebinding.rbac.authorization.k8s.io/admin-user created 라는 문구가 나온다
   ```

   

4. 아래의 명령어를 입력하여 웹 접속을 위한 토큰을 추출한다.

   - `kubectl -n [namespace] describe secret $(kubectl -n [namespace] get secret | grep admin-user | awk '{print $1}')`
     - namespace는 helm 설치시 `default`로 명시가 된다. 변경방법도 있는걸로 알고 있는데 안돼서 우선은 default로 진행한다.

   ```bash
   kubectl -n default describe secret $(kubectl -n default  get secret | grep admin-user | awk '{print $1}')
   ```

   ```bash
   madfalcon@madfalcon:~/my_dashboard$ kubectl -n default describe secret $(kubectl -n default  get secret | grep admin-user | awk '{print $1}') 
   Name:         admin-user-token-9rt75
   Namespace:    default
   Labels:       <none>
   Annotations:  kubernetes.io/service-account.name: admin-user
                 kubernetes.io/service-account.uid: 13820daa-0719-4629-8eff-2d7a8b5a10bf
   
   Type:  kubernetes.io/service-account-token
   
   Data
   ====
   ca.crt:     1066 bytes
   namespace:  7 bytes
   token:      
   #아래 내용을 복사한다.
   eyJhbGciOiJSUzI1NiIsImtpZCI6IjFoUTdIaXN6MzYtZ2w2WUttWUY5QkoxUlB2RTdaS3l0cFpwS1J4dFJ6ZjQifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJkZWZhdWx0Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZWNyZXQubmFtZSI6ImFkbWluLXVzZXItdG9rZW4tOXJ0NzUiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoiYWRtaW4tdXNlciIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50LnVpZCI6IjEzODIwZGFhLTA3MTktNDYyOS04ZWZmLTJkN2E4YjVhMTBiZiIsInN1YiI6InN5c3RlbTpzZXJ2aWNlYWNjb3VudDpkZWZhdWx0OmFkbWluLXVzZXIifQ.fFa1YDwJdr8tKOr4z3ExKvMyEeIfqbEkB93n97scFpaXcpTx2tfBz26o865plPR0nIFgEmqtULCuEs76WDoo-KAhBcP1CJdLkU_TMOG8Hg5CIqx7ogwcGb2cVaLk5eCdvjJfHCmtDXLQvQNWU_sPi5l54XF-8lheKXVsutSNP7xpbtyNCHUdVCuw9cOP7FtuzDIpZ3SYgh2EbNz-wUoQaH3ea1VTxBD6cFIsbN0tzNWSHCwQe03-wnuIC0zlytLAtA-SSEIrTQ8_f31Fa-HwW5gKUhmzjiFqPeM_oA2Q-n5_dlDMdhqMSzpFBjnduBX5qKHHqGMQX4gOhIcLNSkmRw 
   ```





## 3. 접속 확인

외부에서 웹사이트를 통해 접속을 해보자

1. `https://[externalip]`를 웹에 입력하여 접속한다. 보안관련 메시지가 뜨더라도 무시하고 이동한다.

   <img src="images/Kubernetes_dashboard/image-20201208041152181.png" alt="image-20201208041152181" style="zoom:33%;" />

2. 위에서 복사한 토큰 값을 아래에서 붙여넣고 로그인해보자

   <img src="images/Kubernetes_dashboard/image-20201208041320577.png" alt="image-20201208041320577" style="zoom:50%;" />

3. 아래처럼 뜬다면 성공!

   <img src="images/Kubernetes_dashboard/image-20201208041400372.png" alt="image-20201208041400372" style="zoom:80%;" />





## 4. 삭제

helm 을 이용하여 간단하게 삭제 가능하다.

- helm uninstall [name]

```bash
madfalcon@madfalcon:~/my_dashboard$ helm list
NAME                    NAMESPACE       REVISION        UPDATED                                 STATUS          CHART                           APP VERSION
kubernetes-dashboard    default         1               2020-12-07 18:37:40.413266291 +0000 UTC deployed        kubernetes-dashboard-3.0.0      2.0.4      
madfalcon@madfalcon:~/my_dashboard$


madfalcon@madfalcon:~/my_dashboard$ helm uninstall kubernetes-dashboard
release "kubernetes-dashboard" uninstalled
```

- 생성했던 account를 삭제한다.

```
kubectl -n kubernetes-dashboard delete serviceaccount admin-user
kubectl -n kubernetes-dashboard delete clusterrolebinding admin-user
```





## 5. 참고

1. [Dashboard 공식 Git 주소](https://github.com/kubernetes/dashboard)
2. [install K8s dashboard for helm](https://artifacthub.io/packages/helm/k8s-dashboard/kubernetes-dashboard)
3. [create sample user](https://github.com/kubernetes/dashboard/blob/master/docs/user/access-control/creating-sample-user.md)