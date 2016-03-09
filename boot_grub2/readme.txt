http://boxcounter.com/attachments/2013-11-14/linux、osx下搭建操作系统开发环境的完整步骤_v1.1.pdf

sudo kpartx -av ./antos.img
sudo mkdir /tmp/antos
sudo mount -text2 /dev/mapper/loop0p1 /tmp/antos
sudo cp ./kernel.bin /tmp/antos
sudo bochs -f antos.bxrc
