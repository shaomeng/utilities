#!/bin/bash

for i in {0..20}
do
    ./cropanysize /opt/Public_Data/15plume3d_1024z/U1024z.${i}.float 504 504 1024 \
    U.${i}.float 192 255 192 255 512 575
done
