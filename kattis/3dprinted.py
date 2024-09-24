def print_statue(statues, days, n):
    if statues == n:
        print(days)

    print_statue(statues + 1, days + 1, n)
    print_statue(statues + 1, days, n)

print_statue(0, 0, 5)

