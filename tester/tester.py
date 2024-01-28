
import os
from test_command import test_command, run_command
from setup import SHELL, MINISHELL_EXECUTABLE

def run_tests(minishell_executable):
    test_folder = "tests"  # Changez le nom du dossier si nécessaire

    for filename in os.listdir(test_folder):
        if filename.endswith(".txt"):
            filepath = os.path.join(test_folder, filename)
            run_test_file(filepath, minishell_executable)

def run_test_file(filepath, minishell_executable):
    with open(filepath, "r") as file:
        for line in file:
            command = line.strip()
            test_command(command, minishell_executable)

# Exemple d'utilisation
minishell_executable = "./minishell"  # Remplacez cela par le chemin réel de votre exécutable minishell

run_tests(MINISHELL_EXECUTABLE)
# # Basique
# test_command("ls -l", minishell_executable)
# test_command("echo Hello, World!", minishell_executable)