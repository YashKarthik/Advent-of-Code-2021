f = [l.strip('\n') for l in open('./input3.txt').readlines()]

def filter(initial_list, position: int, greater: bool):
    if len(initial_list) == 1: return initial_list
    if position == len(f[0]): return initial_list

    ones_future_list = []
    zeroes_future_list = []
    ones = 0
    zeroes = 0
    for row in range(len(initial_list)):
        if initial_list[row][position] == "0":
            zeroes_future_list.append(initial_list[row])
            zeroes += 1
        else: 
            ones_future_list.append(initial_list[row])
            ones += 1

    if greater: 
        if (zeroes > ones):
            return filter(zeroes_future_list, position+1, greater)
        else:
            return filter(ones_future_list, position+1, greater)
    else:
        if (zeroes > ones):
            return filter(ones_future_list, position+1, greater)
        else:
            return filter(zeroes_future_list, position+1, greater)

print("Here:", filter(f, 0, True))
print("Here:", filter(f, 0, False))
