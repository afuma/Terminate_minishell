
import subprocess

def run_command(command):
    try:
        result = subprocess.check_output(command, shell=True, executable='/bin/bash', stderr=subprocess.STDOUT, text=True)
        return result.strip()
    except subprocess.CalledProcessError as e:
        return e.output.strip()

def test_command(command, minishell_executable):
    bash_result = run_command(command)
    minishell_result = run_command(f"{minishell_executable} {command}")

    if bash_result == minishell_result:
        print(f"Test for command '{command}' passed!")
    else:
        print(f"Test for command '{command}' failed:")
        print(f"  Bash result: {bash_result}")
        print(f"  Minishell result: {minishell_result}")
