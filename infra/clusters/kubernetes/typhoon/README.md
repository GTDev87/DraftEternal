# Typhoon [![IRC](https://img.shields.io/badge/freenode-%23typhoon-0099ef.svg)]() <img align="right" src="https://storage.googleapis.com/poseidon/typhoon-logo.png">

Typhoon is a minimal and free Kubernetes distribution.

* Minimal, stable base Kubernetes distribution
* Declarative infrastructure and configuration
* [Free](#social-contract) (freedom and cost) and privacy-respecting
* Practical for labs, datacenters, and clouds

Typhoon distributes upstream Kubernetes, architectural conventions, and cluster addons, much like a GNU/Linux distribution provides the Linux kernel and userspace components.

## Features <a href="https://www.cncf.io/certification/software-conformance/"><img align="right" src="https://storage.googleapis.com/poseidon/certified-kubernetes.png"></a>

* Kubernetes v1.11.2 (upstream, via [kubernetes-incubator/bootkube](https://github.com/kubernetes-incubator/bootkube))
* Single or multi-master, workloads isolated on workers, [Calico](https://www.projectcalico.org/) or [flannel](https://github.com/coreos/flannel) networking
* On-cluster etcd with TLS, [RBAC](https://kubernetes.io/docs/admin/authorization/rbac/)-enabled, [network policy](https://kubernetes.io/docs/concepts/services-networking/network-policies/)
* Advanced features like [worker pools](https://typhoon.psdn.io/advanced/worker-pools/) and [preemption](https://typhoon.psdn.io/cl/google-cloud/#preemption) (varies by platform)
* Ready for Ingress, Prometheus, Grafana, and other optional [addons](https://typhoon.psdn.io/addons/overview/)

## Modules

Typhoon provides a Terraform Module for each supported operating system and platform.

| Platform      | Operating System | Terraform Module | Status |
|---------------|------------------|------------------|--------|
| AWS           | Container Linux  | [aws/container-linux/kubernetes](aws/container-linux/kubernetes) | stable |
| AWS           | Fedora Atomic    | [aws/fedora-atomic/kubernetes](aws/fedora-atomic/kubernetes) | alpha |
| Azure         | Container Linux  | [azure/container-linux/kubernetes](cl/azure.md) | alpha |
| Bare-Metal    | Container Linux  | [bare-metal/container-linux/kubernetes](bare-metal/container-linux/kubernetes) | stable |
| Bare-Metal    | Fedora Atomic    | [bare-metal/fedora-atomic/kubernetes](bare-metal/fedora-atomic/kubernetes) | alpha |
| Digital Ocean | Container Linux  | [digital-ocean/container-linux/kubernetes](digital-ocean/container-linux/kubernetes) | beta |
| Digital Ocean | Fedora Atomic    | [digital-ocean/fedora-atomic/kubernetes](digital-ocean/fedora-atomic/kubernetes) | alpha |
| Google Cloud  | Container Linux  | [google-cloud/container-linux/kubernetes](google-cloud/container-linux/kubernetes) | stable |
| Google Cloud  | Fedora Atomic    | [google-cloud/fedora-atomic/kubernetes](google-cloud/fedora-atomic/kubernetes) | alpha |

The AWS and bare-metal `container-linux` modules allow picking Red Hat Container Linux (formerly CoreOS Container Linux) or Kinvolk's Flatcar Linux friendly fork.

## Documentation

* [Docs](https://typhoon.psdn.io)
* Architecture [concepts](https://typhoon.psdn.io/architecture/concepts/) and [operating systems](https://typhoon.psdn.io/architecture/operating-systems/)
* Tutorials for [AWS](cl/aws.md), [Azure](cl/azure.md), [Bare-Metal](cl/bare-metal.md), [Digital Ocean](cl/digital-ocean.md), and [Google-Cloud](cl/google-cloud.md)

## Usage

Define a Kubernetes cluster by using the Terraform module for your chosen platform and operating system. Here's a minimal example:

```tf
module "google-cloud-yavin" {
  source = "git::https://github.com/poseidon/typhoon//google-cloud/container-linux/kubernetes?ref=v1.11.2"
  
  providers = {
    google   = "google.default"
    local    = "local.default"
    null     = "null.default"
    template = "template.default"
    tls      = "tls.default"
  }

  # Google Cloud
  cluster_name  = "yavin"
  region        = "us-central1"
  dns_zone      = "example.com"
  dns_zone_name = "example-zone"

  # configuration
  ssh_authorized_key = "ssh-rsa AAAAB3Nz..."
  asset_dir          = "/home/user/.secrets/clusters/yavin"
  
  # optional
  worker_count = 2
}
```

Initialize modules, plan the changes to be made, and apply the changes.

```sh
$ terraform init
$ terraform plan
Plan: 64 to add, 0 to change, 0 to destroy.
$ terraform apply
Apply complete! Resources: 64 added, 0 changed, 0 destroyed.
```

In 4-8 minutes (varies by platform), the cluster will be ready. This Google Cloud example creates a `yavin.example.com` DNS record to resolve to a network load balancer across controller nodes.

```sh
$ export KUBECONFIG=/home/user/.secrets/clusters/yavin/auth/kubeconfig
$ kubectl get nodes
NAME                                          STATUS   AGE    VERSION
yavin-controller-0.c.example-com.internal     Ready    6m     v1.11.2
yavin-worker-jrbf.c.example-com.internal      Ready    5m     v1.11.2
yavin-worker-mzdm.c.example-com.internal      Ready    5m     v1.11.2
```

List the pods.

```
$ kubectl get pods --all-namespaces
NAMESPACE     NAME                                      READY  STATUS    RESTARTS  AGE
kube-system   calico-node-1cs8z                         2/2    Running   0         6m
kube-system   calico-node-d1l5b                         2/2    Running   0         6m
kube-system   calico-node-sp9ps                         2/2    Running   0         6m
kube-system   coredns-1187388186-zj5dl                  1/1    Running   0         6m
kube-system   kube-apiserver-zppls                      1/1    Running   0         6m
kube-system   kube-controller-manager-3271970485-gh9kt  1/1    Running   0         6m
kube-system   kube-controller-manager-3271970485-h90v8  1/1    Running   1         6m
kube-system   kube-proxy-117v6                          1/1    Running   0         6m
kube-system   kube-proxy-9886n                          1/1    Running   0         6m
kube-system   kube-proxy-njn47                          1/1    Running   0         6m
kube-system   kube-scheduler-3895335239-5x87r           1/1    Running   0         6m
kube-system   kube-scheduler-3895335239-bzrrt           1/1    Running   1         6m
kube-system   pod-checkpointer-l6lrt                    1/1    Running   0         6m
```

## Non-Goals

Typhoon is strict about minimalism, maturity, and scope. These are not in scope:

* In-place Kubernetes Upgrades
* Adding every possible option
* Openstack or Mesos platforms

## Help

Ask questions on the IRC #typhoon channel on [freenode.net](http://freenode.net/).

## Motivation

Typhoon powers the author's cloud and colocation clusters. The project has evolved through operational experience and Kubernetes changes. Typhoon is shared under a free license to allow others to use the work freely and contribute to its upkeep.

Typhoon addresses real world needs, which you may share. It is honest about limitations or areas that aren't mature yet. It avoids buzzword bingo and hype. It does not aim to be the one-solution-fits-all distro. An ecosystem of Kubernetes distributions is healthy.

## Social Contract

Typhoon is not a product, trial, or free-tier. It is not run by a company, does not offer support or services, and does not accept or make any money. It is not associated with any operating system or platform vendor.

Typhoon clusters will contain only [free](https://www.debian.org/intro/free) components. Cluster components will not collect data on users without their permission.

## Donations

Typhoon does not accept money donations. Instead, we encourage you to donate to one of [these organizations](https://github.com/poseidon/typhoon/wiki/Donations) to show your appreciation.
