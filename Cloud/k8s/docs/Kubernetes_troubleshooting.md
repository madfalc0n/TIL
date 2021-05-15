# Kubernetes Trouble Shooting

쿠버네티스에서 발생하는 모든 에러사항을 다루는 곳 입니다.



## 1. could not find a JWS signature in the cluster-info ConfigMap for token ID when joining a worker node during clustering

### 1-1. 증상

클러스터링 구성이 되어있는 환경(master-worker)에서 새로운 worker node를 추가할 경우 다음과 같은 에러가 발생

```bash
madfalcon@madfalcon:~$ sudo kubeadm join 192.168.85.130:6443 --token e1r2to.7u73xht6kyqj4cmh     --discovery-token-ca-cert-hash sha256:6d85a383d984fcdbd76b2c3b586db01dff62d121ba63ef98717114b66cd4b5c9
[preflight] Running pre-flight checks
        [WARNING IsDockerSystemdCheck]: detected "cgroupfs" as the Docker cgroup driver. The recommended driver is "systemd". Please follow the guide at https://kubernetes.io/docs/setup/cri/
error execution phase preflight: couldn't validate the identity of the API Server: could not find a JWS signature in the cluster-info ConfigMap for token ID "e1r2to"
To see the stack trace of this error execute with --v=5 or higher
```



### 1-2. 원인

master node에서 발행하는 join 관련 토큰이 만료되어 새로운 worker node를 추가할 수 없는 증상이 발생

```bash
#token list를 불러와도 아무것도 나오지 않는다.

madfalcon@madfalcon:~/my_tmp$ kubeadm token list
madfalcon@madfalcon:~/my_tmp$ 
```



### 1-3. 해결방법

master node에서 새로 토큰을 발행한다.

```bash
#token create를 통해 새로운 토큰을 발행
madfalcon@madfalcon:~/my_tmp$ kubeadm token create
W1207 15:34:04.296689   71748 configset.go:348] WARNING: kubeadm cannot validate component configs for API groups [kubelet.config.k8s.io kubeproxy.config.k8s.io]
b50vvv.o21up6d3jpgle9q3
madfalcon@madfalcon:~/my_tmp$ 

# 새로 생성된 토큰 조회가 된다.
madfalcon@madfalcon:~/my_tmp$ kubeadm token list  
TOKEN                     TTL         EXPIRES                USAGES                   DESCRIPTION                                                EXTRA GROUPS
b50vvv.o21up6d3jpgle9q3   23h         2020-12-08T15:34:04Z   authentication,signing   <none>                                                     system:bootstrappers:kubeadm:default-node-token
madfalcon@madfalcon:~/my_tmp$


#worker node에서 해당 토큰으로 변경하여 클러스터 join
madfalcon@madfalcon:~$ sudo kubeadm join 192.168.85.130:6443 --token b50vvv.o21up6d3jpgle9q3     --discovery-token-ca-cert-hash sha256:6d85a383d984fcdbd76b2c3b586db01dff62d121ba63ef98717114b66cd4b5c9
[sudo] password for madfalcon: 
[preflight] Running pre-flight checks
        [WARNING IsDockerSystemdCheck]: detected "cgroupfs" as the Docker cgroup driver. The recommended driver is "systemd". Please follow the guide at https://kubernetes.io/docs/setup/cri/
[preflight] Reading configuration from the cluster...
[preflight] FYI: You can look at this config file with 'kubectl -n kube-system get cm kubeadm-config -oyaml'
[kubelet-start] Writing kubelet configuration to file "/var/lib/kubelet/config.yaml"
[kubelet-start] Writing kubelet environment file with flags to file "/var/lib/kubelet/kubeadm-flags.env"
[kubelet-start] Starting the kubelet
[kubelet-start] Waiting for the kubelet to perform the TLS Bootstrap...

This node has joined the cluster:
* Certificate signing request was sent to apiserver and a response was received.
* The Kubelet was informed of the new secure connection details.

Run 'kubectl get nodes' on the control-plane to see this node join the cluster.
```



### 1-4. 참고

1. [Can't join existing cluster JWS not found?](https://github.com/kubernetes/kubeadm/issues/668)