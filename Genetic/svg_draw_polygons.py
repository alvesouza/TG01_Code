from pulp import LpMinimize, LpProblem, LpStatus, lpSum, LpVariable
import pulp
from math import sin, cos

colorpal=["rgb(%d,%d,%d)"%(i,255-i,255) for i in range(0,255,30) ] +\
  ["rgb(%d,%d,%d)"%(255,i,255-i) for i in range(0,255,30) ] +\
  ["rgb(%d,%d,%d)" % (255-i, 255, i) for i in range(0, 255, 30)]

svgoutp=open("out.svg","w")
svgoutp.write('<svg width="500" height="520">\n')
polygons_string = [
"111.687,28.2302 121.66,27.4885 122.401,37.4609 112.429,38.2027",
"63.7302,98.9549 73.7302,98.9549 73.7302,118.955 63.7302,118.955",
"60.7364,6.18299 82.2844,27.056 68.369,41.4214 46.821,20.5483",
"230.859,31.4031 260.776,29.1779 264.485,79.0401 234.568,81.2653",
"77.8401,107.619 255.859,80.9902 263.256,130.44 85.2371,157.069",
"50.5628,65.518 130.342,59.5841 132.568,89.5014 52.788,95.4353",
"3.16018,109.762 53.1602,109.762 53.1602,179.762 3.16018,179.762",
"148.778,6.84739 188.778,6.84739 188.778,61.8474 148.778,61.8474",
]

for i in range(len(polygons_string)):
    svgoutp.write('<polygon points="%s"  style="fill:%s;stroke-width:1;stroke:rgb(0,0,0)"/>\n'
          % (polygons_string[i],colorpal[2*i]) )
svgoutp.write('</svg>\n')
svgoutp.close()