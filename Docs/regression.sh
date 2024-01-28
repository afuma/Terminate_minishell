#!/bin/bash

# commande de test:
# valgrind --leak-check=full --show-leak-kinds=all -s ./minishell "bonjour'j'k> n"

# Assurez-vous que le répertoire courant est le bon
cd "$(dirname "$0")"

# Compile et configure les droits de l'exécutable
make -C ../final_minishell > /dev/null

pipe=/tmp/testpipe
trap "rm -f $pipe" EXIT
if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

function exec_test()
{
    rm -f msh_log
    # Exécute les commandes, séparées par ';' dans minishell, en utilisant nfifo
    ./minishell <"$pipe" >msh_log 2>&- &
    mshpid=$!
    IFS=';' read -ra CMND <<< "$@"
    for command in "${CMND[@]}"; do
        echo "$command" > "$pipe"
    done

    echo 'exit' > "$pipe"
    sleep 0.03
    wait $!
    ES_1=$?
    TEST1=$(cat msh_log)

    rm -f msh_log
    TEST2=$(echo "$@" "; exit" | bash 2>&-)
    ES_2=$?
    if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
        printf "✓ "
    else
        printf "✗ "
    fi
    printf "\"$@\" "
    if [ "$TEST1" != "$TEST2" ]; then
        echo
        echo
        printf "Your output : \n%.20s\n%s\n%.20s\n" "-----------------------------------------" "$TEST1" "-----------------------------------------"
        printf "Expected output : \n%.20s\n%s\n%.20s\n" "-----------------------------------------" "$TEST2" "-----------------------------------------"
    fi
    if [ "$ES_1" != "$ES_2" ]; then
        echo
        echo
        printf "Your exit status : %d\n" "$ES_1"
        printf "Expected exit status : %d\n" "$ES_2"
    fi
    echo
    sleep 0.01
}

# Exemple de test
exec_test "echo hello world"

