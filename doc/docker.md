# docker

## docker engine installation
1. curl installation (curl is used in the next step)
   ```
   sudo apt-get update
   sudo apt-get install curl
   ```
2. docker engine installation
   ```
   $ curl -fsSL https://get.docker.com/ | sh
   ```
3. docker group setting so that `sudo` is no longer needed after the second and subsequent calls
   > The Docker daemon binds to a Unix socket instead of a TCP port. By default that Unix socket is owned by the user root and other users can only access it using sudo. The Docker daemon always runs as the root user.
   > 
   > If you don’t want to preface the docker command with sudo, create a Unix group called docker and add users to it. When the Docker daemon starts, it creates a Unix socket accessible by members of the docker group.
   >
   > ref: https://docs.docker.com/engine/install/linux-postinstall/#manage-docker-as-a-non-root-user
   1. generate docker group
      ```
      sudo groupadd docker
      ```
   2. add users who use docker without `sudo` to the docker group
      ここではログインユーザを追加する．
      ```
      sudo gpasswd -a $USER docker
      ```
   3. reboot the system
      ```
      reboot
      ```
   4. verify that the docker command can run without `sudo`
      ```
      docker run hello-world
      ```
