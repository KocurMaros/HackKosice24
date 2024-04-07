import sys

def parse_file_contents(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            parsed_numbers = []
            for line in lines[:20]:  # Read a maximum of 20 lines
                numbers = line.strip().split(',')
                parsed_numbers.append(','.join(numbers) + ',')
            return '$' + ''.join(parsed_numbers)[:-1] + '%'
    except FileNotFoundError:
        print(f"File '{file_path}' not found.")
        return None

if len(sys.argv) < 2:
    print("Usage: python script.py <file_path>")
    exit(1)

file_path = sys.argv[1]
print("Hello, world!")
print("Arguments passed:", sys.argv)
formatted_numbers = parse_file_contents(file_path)
if formatted_numbers is not None:
    print("Formatted numbers:", formatted_numbers)
else:
    exit(1)
exit(0)
