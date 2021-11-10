from subprocess import Popen, run, PIPE, call
import time

number_models = 11
number_algo_versions = 4
number_cross_version = 3
number_mutation_versions = 3
max_process = 10
if __name__ == '__main__':
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 1"] )
    #Popen(["gnome-terminal", "--tab", "-e", "python3 -i Teste_FreeCad.py 0 3 1 2"] )#, stdout=PIPE, stderr=PIPE, stdin=PIPE)
    print(range(number_models))
    popen_list = []
    for model in [11]:#range(number_models):
        for algo in range(number_algo_versions):
            for cross in [3]:#range(1, number_cross_version+1):
                for mutation in [3]:#range(1, number_mutation_versions+1):
                    while len(popen_list) >= max_process:
                        removed = False
                        print(popen_list)
                        to_remove = []
                        for i in range( len(popen_list) ):
                            print(" test index = ", i, " poll = ", popen_list[i].poll())
                            if popen_list[i].poll() is not None:
                                to_remove.append(i)

                        i = len(to_remove) - 1
                        if i >= 0:
                            removed = True

                        print("to_remove = ", to_remove)
                        while i >= 0:
                            popen_list.pop(to_remove[i])
                            i -= 1

                        if not removed:
                            print("sleep 30 seconds")
                            time.sleep(5)
                            print("check list of Popen")
                    popen_list.append(
                    Popen(
                        ["gnome-terminal", "--tab", "-e",
                         "python3 Teste_FreeCad.py {0} {1} {2} {3}".format(model, algo, cross, mutation)])#"python3 -i Teste_FreeCad.py {0} {1} {2} {3}".format(model, algo, cross, mutation)])
                    )
                    time.sleep(0)
    '''cmd = ['lxterminal', '-i', '-e', 'python3', "-i", 'Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 1',
           '--tab', '-e', 'python3 Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 2', '--tab', '-e',
           'python3 Documents/gits/github/TG01_Code/Teste_FreeCad.py 0 3 1 3']
    '''
    #call(cmd)
    #Popen(['gnome-terminal', '--tab', ' -e', "python3", "i", "Teste_FreeCad.py 0 3 1 1"], shell=True)
    #run("python3 Teste_FreeCad.py 0 3 1 2 & Teste_FreeCad.py 0 3 1 2", shell=True)