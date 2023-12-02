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
    x, y = zip(*points)

    # Plot the points without connecting lines
    plt.scatter(x, y, color='blue')

    # Plot the connecting lines
    plt.plot(x, y, linestyle='-', color='blue', alpha=0.5)

    # Highlight the first and last points with different colors
    plt.scatter([x[0], x[-1]], [y[0], y[-1]], color=['red', 'green'], marker='o')

    plt.title(file_path)
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')


if __name__ == '__main__':
    display_route('saved_routes/initial_route.txt')
    display_route('saved_routes/greedy_route.txt')
    display_route('saved_routes/opt2_route.txt')
    display_route('saved_routes/best_route.txt')
    plt.show()