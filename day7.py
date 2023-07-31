import statistics
f = open("input7.txt").readlines()
positions = [int(x) for x in f[0].split(",")]
aim=round(statistics.median(positions))

fuel=0
for position in positions:
    fuel+=abs(position-aim)

print(aim,fuel)
