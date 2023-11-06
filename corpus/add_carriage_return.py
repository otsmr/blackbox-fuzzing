def add_carriage_return(file):

    lines = []
    with open(file, 'r') as f:
        lines = f.readlines()

    replace = True
    with open(file, 'w') as modified:
        for line in lines:
            if line == "\n":
                replace = True
            if replace:
                line = line.rstrip('\n')  # Remove existing newline characters
                line = line.rstrip('\r')  # Remove existing newline characters
                modified.write(line + '\r\n')  # Add '\r\n' after each line
            else:
                modified.write(line)  # Add '\r\n' after each line

    print("OK")


import sys

if len(sys.argv) < 2:
    print("Usage: .py file.txt")
    exit(1)

add_carriage_return(sys.argv[1])

