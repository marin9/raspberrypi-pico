#! /bin/bash

mkdir -p /mnt/pico
sudo mount /dev/sda1 /mnt/pico
cp prog.uf2 /mnt/pico
sync
sudo umount /mnt/pico
