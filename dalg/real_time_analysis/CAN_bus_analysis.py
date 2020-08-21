#!/usr/bin/python3

import math

def name(task):
    return task[0]

def Pi(task):
    return task[1]

def Ci(task, data = -1):
    if data != -1:
        task[3] = data
    else:
        return task[3]

def Ti(task):
    return task[2]

def Ji(task):
    return task[4]

def Bi(task, data = -1):
    if data != -1:
        task[5] = data
    else:
        return task[5]

def Ri(task, data = -1):
    if data != -1:
        task[6] = data
    else:
        return task[6]

def ti(task, data = -1):
    if data != -1:
        task[7] = data
    else:
        return task[7]

def Qi(task, data = -1):
    if data != -1:
        task[8] = data
    else:
        return task[8]

def Wi(task, data = -1):
    if data != -1:
        task[9] = data
    else:
        return task[9]


#
# Calculate blocking times for each task.
#
# Bi = max_lower_prio( Cj )
#
def calc_blocking_times(tasks):

    Bi(tasks[-1], 0) # Lowest priority task cant be blocked
    
    for i in range(0, len(tasks) - 1):

        arr = [ Ci(x) for x in tasks[i+1:] ]
        res = max(arr)

        Bi(tasks[i], res)

    return tasks


def calc_busy_periods(tasks):

    for i in range(0, len(tasks)):
        t_prev = 0
        t = Ci(tasks[i])

        while t_prev != t:
            t_prev = t

            arr = [ math.ceil( (t_prev + Ji(x)) / Ti(x)) * Ci(x) for x in tasks ]
            
            t = Bi(tasks[i]) + sum(arr)

        ti(tasks[i], t)

    return tasks


def calc_instance_accumulation(tasks):
    for task in tasks:
        q = math.ceil( (ti(task) + Ji(task)) / Ti(task) )
        Qi(task, q)

    return tasks


def help_calc_queueing_time(tasks, T_bit, i, q):

    w_prev = 0
    w = Bi(tasks[i])

    while w != w_prev:
        w_prev = w
        
        sum_arr = [ math.ceil( (w_prev + Ji(x) + T_bit) / Ti(x) ) * Ci(x) for x in tasks[:i] ]
        
        w = Bi(tasks[i]) + Ji(tasks[i]) + sum(sum_arr)

    return w
    

def calc_queueing_times(tasks, T_bit):

    w_arr = []

    #Highest priority message will always be transmitted as fast as possible
    w_arr.append( Bi(tasks[0]) ) 

    for i in range(1, len(tasks)):
        
        for q in range(0, Qi(tasks[i])):
            w_tmp = help_calc_queueing_time(tasks, T_bit, i, q)

            Wi(tasks[i]).append(w_tmp)

    return tasks


def calc_response_times(tasks):
    for task in tasks:

        r_res = 0
        for q in range(0, len( Wi(task) )):
            r_res = max( Ji(task) + Wi(task)[q] - q*Ti(task) + Ci(task), r_res )

        Ri(task, r_res)

    return tasks


def can_response_analysis(tasks, T_bit, Cm):

    print(Cm)
    
    for task in tasks:
        Ci(task, Cm)

    calc_blocking_times(tasks)    
    calc_busy_periods(tasks)
    calc_instance_accumulation(tasks)
    calc_queueing_times(tasks, T_bit)

    list_tasks(tasks)

    calc_response_times(tasks)

    print(tasks)



def list_tasks(tasks):
    print("{:15}{:15}{:15}{:15}{:15}{:15}{:15}".format("Name",
                                                       "Priority",
                                                       "Transfer (Ci)",
                                                       "Period (Ti)",
                                                       "Response (Ri)",
                                                       "Jitter (Ji)",
                                                       "Blocking (Bi)"))
    
    for task in tasks:
        print("{:15}{:<15}{:<15}{:<15}{:<15}{:<15}{:<15}".format(name(task),
                                                                 Pi(task),
                                                                 Ci(task),
                                                                 Ti(task),
                                                                 Ri(task),
                                                                 Ji(task),
                                                                 Bi(task)), end='')

        if tasks.index(task) == 0:
            print(" (Highest prio) ")
        else:
            print()



def add_task(tasks):
    print("Enter task set on the following format:")
    print("{:15}{:15}{:15}{:15}".format("Name",
                                        "Priority (Pi)",
                                        "Period (Ti)",
                                        "Jitter (Ji)"))

    task = input()
    task = task.split()

    if len(task) < 3:
        print("Wrong format, aborting....")
        return None
    
    task[1] = float(task[1])
    task[2] = float(task[2])

    if len(task) == 3:
        task.append(float(0))

    task[3] = float(task[3])

    task.append(float(0))
    task.append(float(0))
    task.append(float(0))
    task.append(float(0))
    task.append(float(0))
    task.append([])

    tasks.append(task)
    tasks.sort(key = lambda x: Pi(x))

    return tasks


    

def help():
    print("Choose an option:")
    print("a     : add task")
    print("l     : list tasks")
    print("rd     : CAN response time analysis with n = bytes in message")
    print("rf     : CAN response time analysis with Cm = bits in a frame")
    print("reset : reset")
    print("h     : print this again")

tasks = []
T_bit = -1
n = -1

help()

while True:
    print()
    data = input("Option:")
    if data == "a":
        add_task(tasks)

    elif data == "l":
        list_tasks(tasks)

    elif data == "rd":
        if T_bit == -1:
            T_bit = float( input("Enter T_bit: ") )
            n = float( input("Enter n (number of bytes per message): ") )

        Cm = (8*n + 47 + math.floor( (38 + 8*n - 1) / 4 )) / T_bit
            
        can_response_analysis(tasks, T_bit, Cm)

    elif data == "rf":
        if T_bit == -1:
            T_bit = float( input("Enter T_bit: ") )
            Cm = float( input("Enter Cm (number of bits per frame): ") )

        can_response_analysis(tasks, T_bit, Cm)

    elif data == "reset":
        tasks = []

    elif (data == "h"):
      help()
