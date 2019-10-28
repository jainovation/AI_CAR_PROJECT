- Jetson Tx 보드에서 I2C permission 문제 : 10/25
Instructions
Here are the necessary commands to setup I2C permissions for non-root users.
1) Create new user group called i2c:
xander@alix:~
▶ sudo groupadd i2c
2) Change the group ownership of /dev/i2c-1 to i2c:
xander@alix:~
▶ sudo chown :i2c /dev/i2c-1
3) Change the file permissions of the device /dev/i2c-1 so users of the i2c group can read and write to the device:
xander@alix:~
▶ sudo chmod g+rw /dev/i2c-1
4) Add your user to the group i2c:
xander@alix:~
▶ sudo usermod -aG i2c xander
5) After you logout and login again you should be able to run i2cdetect -y 1