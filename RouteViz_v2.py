import ast
import matplotlib.pyplot as plt

def read_route_file(file_path:str):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Process each line and convert it into a tuple
    list_of_tuples = [ast.literal_eval(line.strip()) for line in lines]

    # Output the result
    return list_of_tuples


def display_route(file_path:str):
    plt.figure()
    points = read_route_file(file_path)
    x1, y1 = zip(*points[0:len(points)//2])
    x2, y2 = zip(*points[len(points)//2:])

    # Plot the points without connecting lines
    plt.scatter(x1, y1, color='blue')
    plt.scatter(x2, y2, color='red')

    # Plot the connecting lines
    plt.plot(x1, y1, linestyle='-', color='blue', alpha=0.5)
    plt.plot(x2, y2, linestyle='-', color='red', alpha=0.5)

    # Highlight the first and last points with different colors
    plt.scatter([x1[0], x1[-1]], [y1[0], y1[-1]], color=['red', 'green'], marker='o')

    plt.title(file_path)
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')


display_route('saved_routes/initial_route.txt')
# display_route('saved_routes/greedy_route.txt')
display_route('saved_routes/opt2_route.txt')
# display_route('saved_routes/best_route.txt')
plt.show()