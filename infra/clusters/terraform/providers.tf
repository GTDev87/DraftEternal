provider "digitalocean" {
  version = "~> 1.3.0"
  token   = "${chomp(file("~/.config/digital-ocean/token"))}"
  alias   = "default"
}

provider "local" {
  version = "~> 1.0"
  alias   = "default"
}

provider "null" {
  version = "~> 1.0"
  alias   = "default"
}

provider "template" {
  version = "~> 1.0"
  alias   = "default"
}

provider "tls" {
  version = "~> 1.0"
  alias   = "default"
}

module "digital-ocean-drafteternal" {
  source = "git::https://github.com/poseidon/typhoon//digital-ocean/container-linux/kubernetes?ref=v1.14.3"

  providers = {
    digitalocean = "digitalocean.default"
    local        = "local.default"
    null         = "null.default"
    template     = "template.default"
    tls          = "tls.default"
  }

  # Digital Ocean
  cluster_name = "drafteternal-k8"
  region       = "nyc1"
  dns_zone     = "drafteternal.com"

  # configuration
  ssh_fingerprints = [
    "06:69:bc:6d:f6:fc:df:30:d7:ec:8a:2d:01:c6:35:6e",
    "6c:13:33:9d:ef:3f:57:7f:74:20:fd:05:68:39:b5:b6"
  ]
  asset_dir        = "/Users/gt/.secrets/clusters/drafteternal"

  # optional
  worker_count    = 1
  controller_type = "s-1vcpu-2gb"
  worker_type     = "s-1vcpu-2gb"
}
