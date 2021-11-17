from subprocess import Popen, run, PIPE, call
import time
import os
from Teste_FreeCad import FileName
import csv
import math

number_models = 11
number_algo_versions = 4
number_cross_version = 4
number_mutation_versions = 4
max_process = 10

def FileNameRef( model, algo_version, cross_version, mutation_version):
    type = "Constant"
    try:
        os.mkdir("RefactorData_knolling")
    except OSError as e:
        print(e)

    try:
        os.mkdir("RefactorData_knolling/{0}".format( type ) )
    except OSError as e:
        print(e)

    try:
        os.mkdir("RefactorData_knolling/{0}/Algo_{1}".format( type, algo_version ) )
    except OSError as e:
        print(e)

    try:
        os.mkdir("RefactorData_knolling/{0}/Algo_{1}/Cross_{2}".format( type, algo_version, cross_version ) )
    except OSError as e:
        print(e)

    try:
        os.mkdir("RefactorData_knolling/{0}/Algo_{1}/Cross_{2}/Mutation_{3}".format( type, algo_version, cross_version, mutation_version ) )
    except OSError as e:
        print(e)

    return 'RefactorData_knolling/{0}/Algo_{2}/Cross_{3}/Mutation_{4}/Data_algo{2}_cross{3}_mutation{4}.csv'.format( type, model, algo_version, cross_version,
                                                                       mutation_version)

if __name__ == '__no_board__':
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 1"] )
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 2"] )#, stdout=PIPE, stderr=PIPE, stdin=PIPE)
    print(range(number_models))
    popen_list = []
    number_of_checks = 0
    for algo in range(number_algo_versions):
        for cross in range(1, number_cross_version+1):
            for mutation in range(1, number_mutation_versions+1):

                fieldnames = ['Generation', 'Time', 'Area', 'Score', 'Score_Final', 'Area_Total', 'Board_Area',
                              'Number of Objects', 'Positions']
                sum_values = {}
                '''for key in fieldnames:
                    sum_values[key] = 0'''
                sum_values["area_fraction"] = []
                sum_values["score_fraction"] = []
                sum_values["score_final_fraction"] = []
                sum_values["Generation"] = []
                filename_str_ref = FileNameRef(0, algo, cross, mutation)
                for model in range(number_models):#[11]:#range(number_models):

                    filename_str = FileName(model, algo, cross, mutation)
                    with open(filename_str, 'r') as csvfile:
                        csv_reader = csv.DictReader(csvfile, delimiter=";")
                        i = 0
                        for row in csv_reader:
                            if model == 0:
                                sum_values["area_fraction"].append(0)
                                sum_values["score_fraction"].append(0)
                                sum_values["score_final_fraction"].append(0)
                                sum_values["Generation"].append(row["Generation"])
                            if i == 0:
                                print(row)
                                print(row["Area_Total"])
                                total_area = float( row['Area_Total'] )
                            sum_values["area_fraction"][i] += float(row["Area"])/total_area
                            row["Score"] = float(row["Score"])
                            if math.isinf(row["Score"]) or row["Score"] > 10**12:
                                row["Score"] = 100*total_area
                            row["Score_Final"] = float(row["Score_Final"])
                            if math.isinf(row["Score_Final"]) or row["Score_Final"] > 10**12:
                                row["Score_Final"] = 100*total_area
                            sum_values["score_fraction"][i] += row["Score"]/total_area
                            sum_values["score_final_fraction"][i] += row["Score_Final"]/total_area
                            i += 1


                with open(filename_str_ref, 'w',
                          newline='') as csvfile:
                    fieldnames = ["Generation", "area_fraction", "score_fraction", "score_final_fraction"]
                    writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=";")
                    writer.writeheader()
                    for i in range(len(sum_values["score_final_fraction"])):
                        writer.writerow({ "Generation": sum_values["Generation"][i],
                            "area_fraction": sum_values["area_fraction"][i]/number_models,
                                             "score_fraction": sum_values["score_fraction"][i]/number_models,
                                             "score_final_fraction": sum_values["score_final_fraction"][i]/number_models
                                             })

    '''cmd = ['lxterminal', '-i', '-e', 'python3', "-i", 'Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 1',
           '--tab', '-e', 'python3 Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 2', '--tab', '-e',
           'python3 Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 3']
    '''
    #call(cmd)
    #Popen(['gnome-terminal', '--tab', ' -e', "python3", "i", "Teste_FreeCad.py 0 3 1 1"], shell=True)
    #run("python3 Teste_FreeCad.py 0 3 1 2 & Teste_FreeCad.py 0 3 1 2", shell=True)

if __name__ == '__main__':
    number_models = 10
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 1"] )
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 2"] )#, stdout=PIPE, stderr=PIPE, stdin=PIPE)
    print(range(number_models))
    popen_list = []
    number_of_checks = 0
    for algo in [1]:#range(number_algo_versions):
        for cross in range(1, number_cross_version+1):
            for mutation in range(1, number_mutation_versions+1):

                fieldnames = ['Generation', 'Time', 'Area', 'Score', 'Score_Final', 'Area_Total', 'Board_Area',
                              'Number of Objects', 'Positions']
                sum_values = {}
                '''for key in fieldnames:
                    sum_values[key] = 0'''
                sum_values["score_fraction"] = []
                sum_values["score_final_fraction"] = []
                sum_values["Generation"] = []
                filename_str_ref = FileNameRef(0, algo, cross, mutation)
                for model in range(number_models):#[11]:#range(number_models):

                    filename_str = FileName(model, algo, cross, mutation)
                    with open(filename_str, 'r') as csvfile:
                        csv_reader = csv.DictReader(csvfile, delimiter=";")
                        i = 0
                        for row in csv_reader:
                            if model == 0:
                                sum_values["score_fraction"].append(0)
                                sum_values["score_final_fraction"].append(0)
                                sum_values["Generation"].append(row["Generation"])
                            if i == 0:
                                print(row)
                                print(row["Area_Total"])
                                total_area = float( row['Number of Vertices'] )
                            #sum_values["area_fraction"][i] += float(row["Area"])/total_area
                            row["Score"] = float(row["Score"])
                            if math.isinf(row["Score"]) or row["Score"] > 10**12:
                                row["Score"] = 100*total_area
                            row["Score_Final"] = float(row["Score_Final"])
                            if math.isinf(row["Score_Final"]) or row["Score_Final"] > 10**12:
                                row["Score_Final"] = 100*total_area
                            sum_values["score_fraction"][i] += row["Score"]/total_area
                            sum_values["score_final_fraction"][i] += row["Score_Final"]/total_area
                            i += 1


                with open(filename_str_ref, 'w',
                          newline='') as csvfile:
                    fieldnames = ["Generation", "area_fraction", "score_fraction", "score_final_fraction"]
                    writer = csv.DictWriter(csvfile, fieldnames=fieldnames, delimiter=";")
                    writer.writeheader()
                    for i in range(len(sum_values["score_final_fraction"])):
                        writer.writerow({ "Generation": sum_values["Generation"][i],
                                             "score_fraction": sum_values["score_fraction"][i]/number_models,
                                             "score_final_fraction": sum_values["score_final_fraction"][i]/number_models
                                             })

