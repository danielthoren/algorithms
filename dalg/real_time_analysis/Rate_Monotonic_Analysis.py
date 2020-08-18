#!/usr/bin/python3

import math

def name(task):
    return task[0]

def Ci(task):
    return task[1]

def Ti(task):
    return task[2]

def Ji(task):
    return task[3]

def Bi(task):
    return task[4]

def Ri(task, data = -1):
    if data != -1:
        task[5] = data
    else:
        return task[5]


# Calculates the RMS response time analysis
#
# wi = Ci + Bi + sum_higher_priority( roof( (wi + Jj) / Tj ) * Cj )
#
# Ri = wi + Jj
#
def rms_response_time_analysis(tasks):

    Ri(tasks[0], Ci(tasks[0]) + Ji(tasks[0]))

    for i in range(1, len(tasks)):
        wi_prev = Ci(tasks[i]) + Ji(tasks[i])
        wi = 0.0

        while True:
            wi = Ci(tasks[i]) + Bi(tasks[i])

            for hp in range(0, i):
                wi += math.ceil( (wi_prev + Ji(tasks[hp])) / Ti(tasks[hp]) ) * Ci(tasks[hp])

            if wi == wi_prev:
                break

            wi_prev = wi

        Ri(tasks[i], wi)

def rms_response_time_print(tasks):
    res = True

    print("{:20} {:<10} {:10} {:<10}".format("Task:", "Ti:", "", "Ri:"))
    
    for task in tasks:
        print("{:20} {:<10}".format(name(task), Ti(task)), end='')

        if Ri(task) <= Ti(task):
            print(" {:10} {:<10}, OK!".format("<=", Ri(task)))
        else:
            res = False
            print(" {:10} {:<10}, BAD!".format("> ", Ri(task)))

    if res == True:
        print("Success, is schedulable with RMS!")
    else:
        print("Fail, is not schedulable with RMS!")
        

# Calculates the RMS utilization based schedulability test
#
# sum( Ci / Ti ) <= n(2^(1/n) - 1)
#
# n is the number of tasks
#
def rms_utilization_schedulability(tasks):
    res = float(0)

    for task in tasks:
        res += Ci(task) / Ti(task)

    thresh = len(tasks) * (math.pow(2, float(1) / float(len(tasks))) - 1)

    if res <= thresh:
        print("Success, task set is schedulable {} =< {}".format(res, thresh))
    else:
        print("Fail, task set might not be schedulable {} !< {}".format(res, thresh))


def list_tasks(tasks):
    print("{:15}{:15}{:15}{:15}{:15}{:15}{:15}".format("Name",
                                                       "Priority",
                                                       "WCET (Ci)",
                                                       "Period (Ti)",
                                                       "Response (Ri)",
                                                       "Jitter (Ji)",
                                                       "Blocking (Bi)"))
    
    for task in tasks:
        print("{:15}{:<15}{:<15}{:<15}{:<15}{:<15}{:<15}".format(name(task),
                                                                 tasks.index(task),
                                                                 Ci(task),
                                                                 Ti(task),
                                                                 Ri(task),
                                                                 Ji(task),
                                                                 Bi(task)), end='')

        if tasks.index(task) == 0:
            print(" (Highest prio) ")
        else:
            print()


def get_task(tasks):
    print("Enter task set on the following format:")
    print("{:15}{:15}{:15}{:15}{:15}".format("Name",
                                             "WCET (Ci)",
                                             "Period (Ti)",
                                             "Jitter (Ji)",
                                             "Blocking (Bi)"))

    task = input()
    task = task.split()

    if len(task) < 3:
        print("Wrong format, aborting....")
        return None
    
    task[1] = float(task[1])
    task[2] = float(task[2])

    if len(task) == 3:
        task.append(0)
    if len(task) == 4:
        task.append(0)

    task[3] = float(task[3])
    task[4] = float(task[4])
    task.append(float(-1))

    tasks.append(task)
    tasks.sort(key = lambda x: Ti(x))

    return tasks


def help():
    print("Choose an option:")
    print("a     : add task")
    print("l     : list tasks")
    print("t     : RMS schedulability test")
    print("r     : RMS response time analysis")
    print("reset : reset")
    print("h     : print this again")

tasks = []

help()

while True:
    print()
    data = input("Option:")
    if data == "a":
        get_task(tasks)

    elif data == "l":
        list_tasks(tasks)
        
    elif data == "t":
        rms_utilization_schedulability(tasks)

    elif data == "r":
        rms_response_time_analysis(tasks)
        rms_response_time_print(tasks)

    elif data == "reset":
        tasks = []

    elif (data == "h"):
      help()
