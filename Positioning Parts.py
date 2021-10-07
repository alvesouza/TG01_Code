TG01_CodePATH = '/home/pedro/Documents/gits/github/TG01_Code'
import sys
from math import acos, pi
sys.path.append(TG01_CodePATH)
import TG01_Code
def makeRotatingPlacement(axis_origin, axis_dir, angle):
    #import FreeCAD as App
    OZ = App.Vector(0,0,1)
    local_cs = App.Placement(axis_origin, App.Rotation(OZ, axis_dir))
    return local_cs.multiply(   App.Placement( App.Vector(), App.Rotation(angle,0,0) ).multiply( local_cs.inverse() )   )

def position_objects_begin(objs):
    for obj in objs:
        #print('\n////////////////////////////////////////\nlabel is {0}'.format(q))
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>":
                #print(p.Base)
                p = obj.Placement
                r = p.Rotation
                print(dir(p))
                obj.Placement = App.Placement(App.Vector(0,0,0) , r )

if __name__ == '__main__':
    doc = FreeCAD.ActiveDocument
    objs = FreeCAD.ActiveDocument.Objects
    vertexes_obj = []
    positions_obj = []
    quaternions_obj = []
    for obj in objs:
        # print('\n////////////////////////////////////////\nlabel is {0}'.format(q))
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>":
                s = obj.Shape
                p = obj.Placement
                b = p.Base
                r = p.Rotation
                angle = 60
                spin = makeRotatingPlacement(App.Vector(b[0], b[1], b[2]), App.Vector(0, 0, 1), angle)
                obj.Placement = spin.multiply(obj.Placement)

                # print(p.Base)
                p = obj.Placement
                r = p.Rotation
                print(dir(obj))
                obj.Placement = App.Placement(App.Vector(10, 15, 1), r)