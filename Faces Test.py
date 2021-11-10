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

def Rotate2ShorterstHeight( objs ):
    for obj in objs:
        '''print('\n////////////////////////////////////////\nlabel is {0}'.format(objs))'''
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>" and obj.Label != "Board Body":
                s = obj.Shape
                p = obj.Placement
                b = p.Base
                r = p.Rotation
                faces = s.Faces
                '''print(dir(faces[0]))'''
                size_list = len(faces)
                print("len = ", len(faces), "obj.Label = ", obj.Label)
                best_face = -1
                smallest_height = 9999999
                for i in range( size_list ):
                    height = -1
                    for j in range( size_list ):
                        if i == j:
                            continue
                        for vertex in faces[j].Vertexes:
                            distance = faces[i].distToShape( vertex )[0]
                            if height < distance:
                                height = distance
                    print( "height = ", height )
                    if height < smallest_height:
                        smallest_height = height
                        best_face = i

                '''print( "best_face = {0}, smallest_height = {1}".format(best_face, smallest_height) )'''
                uv = faces[ best_face ].Surface.parameter(faces[ best_face ].CenterOfMass)
                faceNormalInCOM = faces[ best_face ].normalAt(uv[0], uv[1])
                #print("dir face = {0}".format( dir( faces[ best_face ] )))
                '''print( "Faces Normal = {0}".format(faceNormalInCOM) )'''
                center_mass = faces[best_face].CenterOfMass
                angle = acos( -faceNormalInCOM[2] )*180/(pi)
                spin = makeRotatingPlacement(App.Vector(b[0], b[1], b[2]), App.Vector(-faceNormalInCOM[1], faceNormalInCOM[0], 0), angle)
                obj.Placement = spin.multiply(obj.Placement)

def LowestHeightOnZero( objs ):
    for obj in objs:
        #print('\n////////////////////////////////////////\nlabel is {0}'.format(q))
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>" and obj.Label != "Board Body":
                s = obj.Shape
                p = obj.Placement
                b = p.Base
                r = p.Rotation
                faces = s.Faces
                #print(dir(faces[0]))
                size_list = len(faces)
                best_face = -1
                lowest_height = 9999999
                highest_x = -9999999
                highest_y = -9999999
                for vertex in s.Vertexes:
                    Point = vertex.Point
                    if lowest_height > Point[2]:
                        lowest_height = Point[2]
                    if highest_x < Point[0]:
                        highest_x = Point[0]
                    if highest_y < Point[1]:
                        highest_y = Point[1]
                #obj.Placement = App.Placement(App.Vector(b[0], b[1], b[2] - lowest_height), r)
                #obj.Placement = App.Placement(App.Vector(b[0], b[1], b[2] - lowest_height), r)
                print( "Label = ", obj.Label )
                obj.Placement = App.Placement(App.Vector( b[0]-highest_x, b[1]-highest_y, b[2] - lowest_height), r)

def GetPositionsValues( objs ):
    vertexesAll = []
    positions = []
    CadData = []
    for obj in objs:
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>" and obj.Label != "Board Body":
                # c = obj.Content
                l = obj.Label
                '''print("{0} Object type = {1}\n".format(l, str(type(obj))))'''
                p = obj.Placement
                b = p.Base
                positions.append( [ b[ 0 ], b[ 1 ], b[ 2 ] ] )
                vertexes = obj.Shape.Vertexes
                vertexes_list = []
                for vert in vertexes:
                    vertexes_list.append([vert.Point[0], vert.Point[1], vert.Point[2]])
                    '''try:
                        print('label is {0} content is {1}'.format(l, [vert.Point[0], vert.Point[1], vert.Point[2]]))
                    except:
                        print('label is %s \\n'.format(l))'''

                vertexesAll.append(vertexes_list)
    return [ positions, vertexesAll ]

def PlaceObjects( objs, values ):
    i = 0
    for obj in objs:
        if 'Shape' in dir(obj):
            if str(type(obj)) == "<class 'PartDesign.Body'>"  and obj.Label != "Board Body":
                s = obj.Shape
                p = obj.Placement
                b = p.Base
                r = p.Rotation

                value = values[ i ]

                spin = makeRotatingPlacement(App.Vector(b[0], b[1], b[2]), App.Vector(0, 0, 1), value[ 1 ])
                obj.Placement = spin.multiply(obj.Placement)

                p = obj.Placement
                b = p.Base
                r = p.Rotation

                obj.Placement = App.Placement(App.Vector(value[ 0 ][ 0 ] + b[0], value[ 0 ][ 1 ] + b[1], b[2]), r)
                i += 1

def GetBoard( objs ):
    for obj in objs:
        if obj.Label == "Board":
            vertexes = obj.Shape.Vertexes
            vertexes_list = []
            for vert in vertexes:
                vertexes_list.append([vert.Point[0], vert.Point[1], 0])
            return vertexes_list
def WriteValues( values ):
    print( "values = [" )
    print("             [")
    for i in range(len(values[0])):
        print("                 ", values[0][i], end="")
        if i + 1 < len(values[0]):
            print(",")
        else:
            print("\n], [");

    for i in range( len( values[1] ) ):
        print( " [ " )
        for j in range(len(values[1][i])):
            if j == 0:
                print("         ", end ="")
            print( values[1][i][j], end="" )
            if j + 1 < len( values[1][i] ):
                if j%2 == 0:
                    print(", ", end="")
                else:
                    print(", ", end="\n         ")
            else:
                print("\n]", end="")
                if i + 1 != len( values[1] ):
                    print("", end=",")
    print( "]] " )

if __name__ == '__main__':
    doc = FreeCAD.ActiveDocument
    objs = FreeCAD.ActiveDocument.Objects
    vertexes_obj = []
    positions_obj = []
    quaternions_obj = []

    vertex_board = GetBoard( objs )

    print( vertex_board )

    Rotate2ShorterstHeight(objs)
    LowestHeightOnZero(objs)
    values = GetPositionsValues(objs)

    WriteValues( values )
    #new_values = TG01_Code.GeneticAlgoV01_parser01( 1, 1000,1000, values[0], values[1] )
    #new_values = TG01_Code.GeneticAlgo_knolling_V01_parser01( 1, 1000, 1000, values[0], values[1], [[0,0,0]], vertex_board, 3, 3)

    
    #scores = new_values[4]
    #scores_Final = new_values[5]
    #print("new positions = ", new_values[0] )
    #print("scores = ", scores  )
    #print("scores_Final = ", scores_Final )
    #PlaceObjects( objs, new_values[0] )
