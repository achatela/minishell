# minishell

## ERREURS A GERER

**ctrl c dans here doc**

**quand PWD unset, builtin cd qui segfault**

**echo "txt" >> file1 > file2 < file-existant == txt dans file2
mais echo "txt" >> file1 > file2 < file-inexistant == rien faire dans file2 mais le créer**

**segfault quand var prompt manquantes fix mais à gérer (prompt par défaut)**

**quand redir-in n'arrive pas à ouvrir fd -> supprimer tout après <**

**segfault quand mkdir 1 -> cd 1 -> mkdir 2 -> cd 2 - > rm -rf ../../1/**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969592169881026610/unknown.png)

**echo $? pour voir la valeur du return.**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

_et la norminette lol_
