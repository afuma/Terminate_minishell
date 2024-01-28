
cas a gerer pour l'expand
bash-5.1$ echo $HOME"fdsfgg" -> cas (1) particulier a gerer
/mnt/nfs/homes/edesaintfdsfgg
bash-5.1$ echo $HOME "fdsfgg" -> cas (2) classique gerer par echo et fonctionne avec mon lexing
/mnt/nfs/homes/edesaint fdsfgg
bash-5.1$ echo $HOME"fds    fgg" -> gerer par le cas (1)
/mnt/nfs/homes/edesaintfds    fgg
bash-5.1$ echo $HOME"$HOMEfds    fgg" -> gerer par le cas (1), bien verifier pas d'espaces supplementaires
/mnt/nfs/homes/edesaint    fgg
bash-5.1$ echo $HOME'$HOMEfds    fgg' -> pris en compte dans le cas (1)
/mnt/nfs/homes/edesaint$HOMEfds    fgg
bash-5.1$ echo $HOME"$HOME fds    fgg" -> gerer par le cas (1)
/mnt/nfs/homes/edesaint/mnt/nfs/homes/edesaint fds    fgg
bash-5.1$ echo $HOME"$HOME'fds    fgg" -> gerer par le cas (1)
/mnt/nfs/homes/edesaint/mnt/nfs/homes/edesaint'fds    fgg
bash-5.1$ echo $HOME"$HOME|'fds    fgg"
/mnt/nfs/homes/edesaint/mnt/nfs/homes/edesaint|'fds    fgg
bash-5.1$ echo $HOME"$HOME>'fds    fgg"
/mnt/nfs/homes/edesaint/mnt/nfs/homes/edesaint>'fds    fgg
bash-5.1$ echo $HOME"$HOME<'fds    fgg"
/mnt/nfs/homes/edesaint/mnt/nfs/homes/edesaint<'fds    fgg
bash-5.1$ export L=l
bash-5.1$ $Ls -la
bash: -la: command not found
bash-5.1$ $"L"s -la
bash: Ls: command not found
bash-5.1$ "$L"s -la

--------------------------------------------------------------------------
cas export doit etre gerer

bash-5.1$ export ^=h
bash: export: `^=h': not a valid identifier
bash-5.1$ export $h=h
bash: export: `=h': not a valid identifier
bash-5.1$ export $h=bonjour
bash: export: `=bonjour': not a valid identifier
bash-5.1$ export $h="bonjour"
bash: export: `=bonjour': not a valid identifier
bash-5.1$ 