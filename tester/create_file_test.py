
from setup import *

def is_part_line(line):
    return line.strip().startswith('//-')

def is_title_line(line):
    return line.strip().startswith('// ')

def add_deb_line(line, deb_str_add):
    return deb_str_add + line

def add_end_line(line, end_str_add):
    return line + end_str_add

def is_separated_line(line):
    return line.strip().startswith('// -----------')

def add_deb_title_line(line, deb_str_add_title):
    return "// " + deb_str_add_title + line[3:]

def add_end_title_line(line, end_str_add_title):
    return "// " + line[3:] + end_str_add_title

def process_file(input_file, output_file, deb_str_add, end_str_add, deb_str_add_title, end_str_add_title):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            if not line.isspace() and not is_title_line(line) and not is_part_line(line) and not is_separated_line(line):
                line = add_deb_line(line, deb_str_add)
                line = add_end_line(line, end_str_add)
            if not is_separated_line(line) and is_title_line(line):
                line = add_deb_title_line(line, deb_str_add_title)
                line = add_end_title_line(line, end_str_add_title)
            outfile.write(line)

def main():
    # input_file = input("Fichier a modifier: ")
    # output_file = input("Nom du nouveau fichier: ")
    # deb_str_add = input("Mot a ajouter au debut: ")
    # end_str_add = input("Mot a ajouter a la fin: ")
    # deb_str_add_title = input("Mot a ajouter a la fin du titre: ")
    # end_str_add_title = input("Mot a ajouter au debut du titre: ")
    input_file = PATH + RELATIVE_PATH + INPUT_FILE_NAME
    output_file = PATH + RELATIVE_PATH + OUTPUT_FILE_NAME
    process_file(input_file, output_file, DEB_STR_ADD, END_STR_ADD, DEB_STR_ADD_TITLE, END_STR_ADD_TITLE)

if __name__ == "__main__":
    main()