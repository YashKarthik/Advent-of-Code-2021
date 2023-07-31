data = [int(x) for x in open("input7.txt").read().strip().split(",")]

pt1 = {x: sum([abs(x - z) for z in data]) for x in range(0, max(data) + 1)}
print(f"Part 1: {min(pt1.values())}")

pt2 = {x: sum([abs(x - z) / 2 * (2 + (abs(x - z) - 1)) for z in data]) for x in range(0, max(data) + 1)}
print(f"Part 2: {int(min(pt2.values()))}")
