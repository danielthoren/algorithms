#!/usr/bin/python3

import CAN_bus_analysis as CAN

def test_can_1():
    m1 = ["m1", 1, 20, 1]
    m2 = ["m2", 2, 10, 2]
    m3 = ["m3", 3, 5]

    T_bit = 0.1
    Cm = 10

    tasks = []

    CAN.add_task(tasks, m1)
    CAN.add_task(tasks, m2)
    CAN.add_task(tasks, m3)

    CAN.can_response_analysis(tasks, T_bit, Cm)

    if CAN.Ri(tasks[0]) != 2 or CAN.Ri(tasks[1]) != 5 or CAN.Ri(tasks[2]) != 3:
        print("Failed test 1!")

test_can_1()
