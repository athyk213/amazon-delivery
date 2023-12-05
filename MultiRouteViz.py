### methods for visualizing multiroute
import matplotlib.pyplot as plt
import re


def read_multi_route_file(file_path:str):
    '''
    Parses multi-route files, each line is a route
    Returns a list of routes. Routes themselves are lists of tuples
    '''

    routes = []


    with open(file_path, 'r') as file:
        for line in file:
            # Removing parentheses and splitting the string by spaces to get individual tuples
            # Use regular expressions to extract the coordinates
            pattern = r"\(-?\d+,\s?-?\d+\)"
            matches = re.findall(pattern, line)

            # Convert the strings to tuples
            route = []
            for match in matches:
                x, y = match.strip().lstrip("(").rstrip(")").split(",")
                route.append((int(x), int(y)))

                
            routes.append(route)

    return routes

def display_route(file_path: str):
    routes = read_multi_route_file(file_path)

    all_x = []
    all_y = []
    for i, route in enumerate(routes):
        x, y = zip(*route)
        all_x.extend(x)
        all_y.extend(y)

        # Plot the points without connecting lines
        plt.scatter(x, y, color='black', marker = '.')

        # Plot the connecting lines
        if i == 0:
            plt.plot(x, y, linestyle='-', alpha=0.7, label=f'Amazon Prime')
        else:
            plt.plot(x, y, linestyle='-', alpha=0.75, label=f'Route {i}')

    x_range = max(all_x) - min(all_x)
    y_range = max(all_y) - min(all_y)
    max_range = max(x_range, y_range)

    for route in routes:
        x, y = zip(*route)
        for j in range(len(x) - 1):
            mid_x = (x[j] + x[j + 1]) / 2
            mid_y = (y[j] + y[j + 1]) / 2
            dx = x[j + 1] - x[j]
            dy = y[j + 1] - y[j]

            head_width = max_range * 0.01  # Adjust the scaling factor as needed
            #plt.arrow(mid_x, mid_y, dx*0.01, dy*0.01, head_width=head_width, head_length=head_width*1.3, fc='black', ec='black', alpha=0.7)

        # Highlight the first and last points with different colors
        plt.scatter([x[0], x[-1]], [y[0], y[-1]], color=['red', 'green'], marker='o')

    #plt.legend()
    #plt.title(file_path)
    #plt.xlabel('X-axis')
    #plt.ylabel('Y-axis')

def display_route_sub(file_path: str, ax):
    routes = read_multi_route_file(file_path)

    all_x = []
    all_y = []
    for i, route in enumerate(routes):
        x, y = zip(*route)
        all_x.extend(x)
        all_y.extend(y)

        # Plot the points without connecting lines
        ax.scatter(x, y, color='black', marker = '.')

        # Plot the connecting lines
        if i == 0:
            ax.plot(x, y, linestyle='-', alpha=0.7, label=f'Amazon Prime')
        else:
            ax.plot(x, y, linestyle='-', alpha=0.75, label=f'Route {i}')

    x_range = max(all_x) - min(all_x)
    y_range = max(all_y) - min(all_y)
    max_range = max(x_range, y_range)

    for route in routes:
        x, y = zip(*route)
        for j in range(len(x) - 1):
            mid_x = (x[j] + x[j + 1]) / 2
            mid_y = (y[j] + y[j + 1]) / 2
            dx = x[j + 1] - x[j]
            dy = y[j + 1] - y[j]

            head_width = max_range * 0.01  # Adjust the scaling factor as needed
            #plt.arrow(mid_x, mid_y, dx*0.01, dy*0.01, head_width=head_width, head_length=head_width*1.3, fc='black', ec='black', alpha=0.7)

        # Highlight the first and last points with different colors
        ax.scatter([x[0], x[-1]], [y[0], y[-1]], color=['red', 'green'], marker='o')


if __name__ == '__main__':
    plt.figure()
    display_route('saved_routes/MultiRouteOpt.txt')

    plt.figure()
    display_route('saved_routes/MultiRouteUnOpt.txt')

    plt.figure()
    display_route('saved_routes/SingleRouteOpt.txt')

    plt.figure()
    display_route('saved_routes/SingleRouteUnOpt.txt')

    plt.show()