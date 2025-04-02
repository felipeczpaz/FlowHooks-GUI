import os

def prepend_copyright_to_files(directory, copyright_file):
    # Read the contents of the Copyright.txt file
    try:
        with open(copyright_file, 'r') as copyright:
            copyright_text = copyright.read()
    except FileNotFoundError:
        print(f"Error: {copyright_file} not found.")
        return

    # List of C/C++ file extensions to target
    cpp_extensions = ['.h', '.hpp', '.c', '.cpp', '.cc']
    
    # Iterate through all files in the directory and subdirectories
    for root, _, files in os.walk(directory):
        for file in files:
            # Check if the file has a C/C++ extension
            if any(file.endswith(ext) for ext in cpp_extensions):
                file_path = os.path.join(root, file)
                try:
                    # Read the content of the current file
                    with open(file_path, 'r') as f:
                        file_content = f.read()

                    # Prepend the copyright text
                    with open(file_path, 'w') as f:
                        f.write(copyright_text + "\n" + file_content)
                    print(f"Prepended copyright to: {file_path}")

                except Exception as e:
                    print(f"Error processing file {file_path}: {e}")

if __name__ == "__main__":
    # Specify the directory to search for C/C++ files and the Copyright.txt file
    directory_to_search = '.'
    copyright_txt_file = 'Copyright.txt'

    prepend_copyright_to_files(directory_to_search, copyright_txt_file)
