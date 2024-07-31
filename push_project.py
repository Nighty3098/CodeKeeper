import subprocess
import os
import time

def run_command(command, check=True):
    """Executes a command in the terminal and returns the result."""
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    if check and result.returncode != 0:
        print(f"Error executing command: {command}")
        print(result.stderr)
        exit(1)
    return result.stdout

def main():
    # Change to the project directory
    project_dir = "../CodeKeeper"  # Replace with the path to your project
    os.chdir(project_dir)

    # Build the project
    start_time = time.time()
    print("Starting the project build...")
    
    build_command = """
cd src/CodeKeeper
qmake CodeKeeper.pro
make
cd ../..
"""
    
    build_output = run_command(build_command, check=True)
    
    end_time = time.time()
    build_time = end_time - start_time
    print(f"Build completed in {build_time:.2f} seconds.")

    # Check for errors
    if "error" in build_output.lower():
        print("Errors detected during the build:")
        print(build_output)
        return

    # Commit changes
    run_command("git add .")
    commit_message = input("Enter commit message: ")
    run_command(f"git commit -m \"{commit_message}\"")

    # Push changes to GitHub
    run_command("git push")  # Replace 'main' with your branch name if necessary

    print("Changes successfully pushed to GitHub.")

if __name__ == "__main__":
    main()
