TG01_CodePATH = '/home/pedro/Documents/gits/github/TG01_Code'
import sys
sys.path.append(TG01_CodePATH)
import TG01_Code

if __name__ == '__main__':
    Cads = TG01_Code.get_Cad_Data(
        [[[0.0, 0.0, 6.0], [0.0, 0.0, 16.0], [23.703047, 3.945976, 6.0], [23.703047, 3.945976, 16.0], [24.42581, 24.484627000000003, 6.0], [24.42581, 24.484627000000003, 16.0], [7.500997999999999, 16.112568, 6.0], [7.500997999999999, 16.112568, 16.0], [5.633849, 26.592699, 6.0], [5.633849, 26.592699, 16.0], [-6.231589, 18.702484, 6.0], [-6.231589, 18.702484, 16.0], [-3.581439, 16.112568, 6.0], [-3.581439, 16.112568, 16.0], [-8.339662, 4.849436000000001, 6.0], [-8.339662, 4.849436000000001, 16.0]]],
        [[0.0, 0.0, 6.0]],
        [[0.0, 0.0, 0.0, 1.0]]
    )

    for cad in Cads:
        print("oi")
        #cad.printa()
        #TG01_Code.Point_3VectorPythonList(cad.vertexes)
        print("Vertexes = {0}".format(TG01_Code.Point_3VectorPythonList(cad.vertexes)))
        print("Position = {0}".format(TG01_Code.Point_3toPythonList(cad.position)))
        print("Quaternion= {0}".format(TG01_Code.QuaterniontoPythonList(cad.quaternion)))
