import subprocess
import os
import time
import configparser

def run_command(command, check=True):
    """Executes a command in the terminal and returns the result."""
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    if check and result.returncode != 0:
        print(f"Error executing command: {command}")
        print(result.stderr)
        exit(1)
    return result.stdout

def get_git_token():
    """Retrieves the GitHub token from the configuration file."""
    config = configparser.ConfigParser()
    config_file_path = os.path.expanduser("~/.config/CodeKeeper/CodeKeeper.conf")
    
    if not os.path.exists(config_file_path):
        print(f"Configuration file not found: {config_file_path}")
        exit(1)

    with open(config_file_path, 'r') as file:
        for line in file:
            if line.startswith("git_token="):
                return line.split("=")[1].strip()

    print("Git token not found in the configuration file.")
    exit(1)

def main():
    # Change to the project directory
    project_dir = "../CodeKeeper"  # Replace with the path to your project
    os.chdir(project_dir)

    # Build the project
    start_time = time.time()
    print("Starting the project build...")
    
    build_command = """
#!/bin/bash

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

    # Get GitHub token
    git_token = get_git_token()
    
    # Push changes to GitHub
    username = "Nighty3098"
    remote_url = f"https://{username}:{git_token}@github.com/{username}/CodeKeeper.git"  # Replace 'your-repo' with your repository name
    run_command(f"git push {remote_url} main")  # Replace 'main' with your branch name if necessary

    print("Changes successfully pushed to GitHub.")

if __name__ == "__main__":
    main()
