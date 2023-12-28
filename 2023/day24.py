import sympy

lines = open("./inputs/day24").readlines()
positions = [[int(num) for num in line.split(" @ ")[0].split(", ")] for line in lines]
velocities = [[int(num) for num in line.split(" @ ")[1].split(", ")] for line in lines]
x, y, z, vx, vy, vz, n1, n2, n3 = sympy.symbols("x, y, z, vx, vy, vz, n1, n2, n3")

solution = sympy.solve([(positions[0][0] - x) + n1 * (velocities[0][0] - vx),
                        (positions[0][1] - y) + n1 * (velocities[0][1] - vy),
                        (positions[0][2] - z) + n1 * (velocities[0][2] - vz),
                        (positions[1][0] - x) + n2 * (velocities[1][0] - vx),
                        (positions[1][1] - y) + n2 * (velocities[1][1] - vy),
                        (positions[1][2] - z) + n2 * (velocities[1][2] - vz),
                        (positions[2][0] - x) + n3 * (velocities[2][0] - vx),
                        (positions[2][1] - y) + n3 * (velocities[2][1] - vy),
                        (positions[2][2] - z) + n3 * (velocities[2][2] - vz)])[0]

print(solution[x] + solution[y] + solution[z])
