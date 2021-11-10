import csv
import sys


def hello(a, b):
    print( "hello and that's your sum:", a + b )

if __name__ == '__main__':
    modelo = int(sys.argv[1])
    algo_version = int(sys.argv[2])
    cross_version = int(sys.argv[3])
    mutation_version = int(sys.argv[4])
    hello(a, b)
    '''
    positions = new_values[0]
    areas = new_values[1]
    scores = new_values[2]
    scores_Fianl = new_values[3]
    times = new_values[4]
    indexes = new_values[5]
    '''
    i = 0
    size = len(new_values[3])
    positions = new_values[0]
    total_area = new_values[1]
    board_area = new_values[2]
    areas = new_values[3]
    scores = new_values[4]
    scores_Fianl = new_values[5]
    times = new_values[6]
    generation = new_values[7]
    with open('Data_modelo_{0}_algo{1}_cross{2}_mutation{3}.csv'.format(modelo, algo_version, cross_version, mutation_version), 'w', newline='') as csvfile:
        fieldnames = ['Generations', 'Time', 'Area', 'Scores', 'Score_Final', 'Area_Total', 'Board_Area']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter = ";")

        writer.writeheader()
        for i in range( size ):
            if i == 0:
                writer.writerow({'Generations':generation[i],
                                 'Time':times[i],
                                 'Area':areas[i],
                                 'Scores':scores[i],
                                 'Score_Final':scores_Fianl[i],
                                 'Area_Total':total_area,
                                 'Board_Area':board_area})
            else:
                writer.writerow({'Generations':generation[i],
                                 'Time':times[i],
                                 'Area':areas[i],
                                 'Scores':scores[i],
                                 'Score_Final':scores_Fianl[i]
                                 })
