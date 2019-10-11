IMU_Software Installation
=========================
### 1. Arduino IDE Install
+  ####  ubuntu-make install
   - `$ sudo apt-add-respository ppa:ubuntu-desktop/ubuntu-make`
   - `$ sudo apt-get update`
   - `$ sudo apt-get install ubuntu-make`
+  #### Arduino IDE 최신 버전 Install
   - `$ sudo umake ide arduino`
+  #### tty 접근 가능하게 하기
   - `$ sudo usermod -aG dialout (아이디)`
+  #### 설정 적용을 위해 재부팅
   - `$ sudo reboot`

### 2. Visual Python Install(Required for the 3D visualization node)
   - `$ sudo apt-get install python-visual`
