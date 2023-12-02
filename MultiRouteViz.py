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

def display_route(file_path:str):
    routes = read_multi_route_file(file_path)

    for i,route in enumerate(routes):

        x, y = zip(*route)

        # Plot the points without connecting lines
        plt.scatter(x, y, color='black')

        # Plot the connecting lines
        plt.plot(x, y, linestyle='-', alpha=0.5,label = f'Route {i}')

        # Highlight the first and last points with different colors
        plt.scatter([x[0], x[-1]], [y[0], y[-1]], color=['red', 'green'], marker='o')

    plt.title(file_path)
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')

plt.figure()
display_route('saved_routes/MultiRouteOpt.txt')

plt.figure()
display_route('saved_routes/MultiRouteUnOpt.txt')

plt.figure()
display_route('saved_routes/SingleRouteOpt.txt')

plt.figure()
display_route('saved_routes/SingleRouteUnOpt.txt')

plt.show()