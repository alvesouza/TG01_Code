TG01_CodePATH = '/home/pedro/Documents/gits/github/TG01_Code'
import sys
sys.path.append(TG01_CodePATH)
import TG01_Code

def makeRotatingPlacement(axis_origin, axis_dir, angle):
    #import FreeCAD as App
    OZ = App.Vector(0,0,1)
    local_cs = App.Placement(axis_origin, App.Rotation(OZ, axis_dir))
    return local_cs.multiply(   App.Placement( App.Vector(), App.Rotation(angle,0,0) ).multiply( local_cs.inverse() )   )

def convert_vertexes_to_list( vertexes ):
    vertexes_list = []

    for vert in vertexes:
        Point = vert.Point
        vertexes_list.append( [Point[0], Point[1], Point[2]] )

    return vertexes_list

if __name__ == '__main__':
    TG01_Code.teste3()
    doc = FreeCAD.ActiveDocument
    objs = FreeCAD.ActiveDocument.Objects
    vertexes_obj = []
    positions_obj = []
    quaternions_obj = []
    for obj in objs:
        # c = obj.Content
        #l = obj.Label
        #p = obj.Placement
        #q = p.Rotation
        methodList = []
        try:
            print("obj attr = {0}".format(dir(obj)))
            print("Shape attr = {0}".format(dir(obj.Shape)))
            for method_name in dir(obj):
                try:
                    if callable(getattr(obj, method_name)):
                        methodList.append(str(method_name))
                        print("{0} has method {1}".format(str(method_name)))
                except:
                    methodList.append(str(method_name))
                    print("{0} has method {1}".format(str(method_name)))
        except:
            print('{0} doesnt has it \\n'.format(type(obj)))
        #print('\n////////////////////////////////////////\nlabel is {0}'.format(q))
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>":
                s = obj.Shape
                p = obj.Placement
                b = p.Base
                r = p.Rotation
                '''l = obj.Label
                print("{0} Object type = {1}\n".format( l, str(type(obj))))
                p = obj.Placement
                q = p.Rotation
                print("Placement = {0}\n Rotation = {1}\n".format(p.Base[2], q))'''
                spin = makeRotatingPlacement(App.Vector(b[0], b[1], b[2]),App.Vector(0,0,1), 45)
                obj.Placement = spin.multiply( obj.Placement )
                vertexes_obj.append(convert_vertexes_to_list(s.Vertexes))
                positions_obj.append([b[0], b[1], b[2]])
                r = r.Q
                quaternions_obj.append([r[0], r[1], r[2], r[3]])
                #quaternions_obj.append([r[0], r[1], r[2], r[3]])
        '''if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>":
                #c = obj.Content
                l = obj.Label
                print("{0} Object type = {1}\n".format( l, str(type(obj))))
                p = obj.Placement
                q = p.Rotation
                print("Placement = {0}\n Rotation = {1}\n".format(p, q))
                vertexes = obj.Shape.Vertexes
                vertexes_list = []
                for vert in vertexes:
                    vertexes_list.append([vert.Point[0], vert.Point[1], vert.Point[2]])
                    try:
                        print('label is {0} content is {1}'.format(l, [vert.Point[0], vert.Point[1], vert.Point[2]]))
                    except:
                        print('label is %s \\n'.format(l))'''
    print("vertexes_obj = {0}".format(vertexes_obj))    
    print("positions_obj = {0}".format(positions_obj))    
    print("quaternions_obj = {0}".format(quaternions_obj))    
    Cads = TG01_Code.get_Cad_Data(vertexes_obj, positions_obj, quaternions_obj)
    Cads_XY = TG01_Code.Project_Cad_Data_Vector(Cads)
    for cad in Cads_XY:
        print("Vertexes = {0}".format(TG01_Code.Point_2VectorPythonList(cad.vertexes)))
        print("Position = {0}".format(TG01_Code.Point_2toPythonList(cad.position)))

    """for cad in Cads:
        print("Vertexes = {0}".format(TG01_Code.Point_3VectorPythonList(cad.vertexes)))
        print("Position = {0}".format(TG01_Code.Point_3toPythonList(cad.position)))
        print("Quaternion= {0}".format(TG01_Code.QuaterniontoPythonList(cad.quaternion)))"""