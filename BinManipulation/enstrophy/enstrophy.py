#!/usr/bin/python
#imports
import string
import sys
import os
import shutil
import copy
import math
import numpy as np
import scipy
import findiff

nx = 512
ny = 512
nz = 512
x0 = 0
y0 = 0
z0 = 0
xn = 512
yn = 512
zn = 512

dx = 2.0 * scipy.pi / nx
dy = 2.0 * scipy.pi / ny
dz = 2.0 * scipy.pi / nz

#check for valid number of arguments
if len(sys.argv) < 5 :
	print(">>>ERROR: not enough arguments!\n" + usage)
	exit(-1)

print("dx = " + str(dx))

sys.argv.pop(0)
ufile = sys.argv.pop(0)
vfile = sys.argv.pop(0)
wfile = sys.argv.pop(0)
dstfile = sys.argv.pop(0)


u = np.fromfile(ufile,dtype=np.float32,count=nx*ny*nz)
print ("max = " + str(np.amax(u)))
print ("size = " + str(np.size(u)))
print ("shape = " + str(np.shape(u)))
u = np.reshape(u,(nz,ny,nx))
u = u[z0:zn,y0:yn,x0:xn]
print ("shape = " + str(np.shape(u)))

v = np.fromfile(vfile,dtype=np.float32,count=nx*ny*nz)
print ("max = " + str(np.amax(v)))
v = np.reshape(v,(nz,ny,nx))
v = v[z0:zn,y0:yn,x0:xn]

w = np.fromfile(wfile,dtype=np.float32,count=nx*ny*nz)
print ("max = " + str(np.amax(w)))
w = np.reshape(w,(nz,ny,nx))
w = w[z0:zn,y0:yn,x0:xn]

print ("max = " + str(np.amax(u)))

wx,wy,wz = findiff.curl_findiff(u,v,w,dx,dy,dz)
enstrophy = np.sqrt(findiff.mag3d(wx,wy,wz))

enstrophy.tofile(dstfile)
