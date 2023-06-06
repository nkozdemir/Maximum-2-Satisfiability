# A function used to convert the generated samples into a specific format
def convert_parentheses_to_braces(input_file, output_file):
    with open(input_file, 'r') as file:
        content = file.read()

    converted_content = content.replace('(', '{').replace(')', '}').replace('[', '{').replace(']', '}')

    with open(output_file, 'w') as file:
        file.write(converted_content)


input_file_path = 'sample.txt'  # Replace with input file name
output_file_path = 'output.txt'  # Replace with output file name

convert_parentheses_to_braces(input_file_path, output_file_path)