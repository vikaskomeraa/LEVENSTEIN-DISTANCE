def edit_distance(str1, str2):
    rows = len(str1) + 1
    cols = len(str2) + 1
    distances = [[0 for _ in range(cols)] for _ in range(rows)]

    for i in range(1, rows):
        distances[i][0] = i
    for j in range(1, cols):
        distances[0][j] = j

    for col in range(1, cols):
        for row in range(1, rows):
            cost = 0 if str1[row - 1] == str2[col - 1] else 1
            distances[row][col] = min(distances[row-1][col] + 1,      # deletion
                                      distances[row][col-1] + 1,      # insertion
                                      distances[row-1][col-1] + cost) # substitution
    return distances[rows - 1][cols - 1]

with open("input.txt", "r") as file:
    lines = file.readlines()
    num_inputs = len(lines) // 2  
    for i in range(num_inputs):
        str1 = lines[i * 2].strip()
        str2 = lines[i * 2 + 1].strip()

        distance = edit_distance(str1, str2)
        print("Edit distance between '{}' and '{}' is: {}".format(str1, str2, distance))