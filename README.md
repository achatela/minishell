# minishell

## ERREURS A GERER

**redirigé vers la bonne sortie**

**je sais pas depuis quand mais echo > file1 > file2 > file3 supprime pas file1 et file2**

**unset PATH et env -i bash == bizzare**

**Gestion de echo "$?" et echo '$?' inversé mais pour l'instant je comprends plus rien à str-quotes.c**

**export 1>e3=32 et export 1 > e3=32 sont gérés différement dans bash =)**

**ctrl c dans un heredoc = interaction aléatoire entre le \n et ^C**
**ctrl c dans heredoc doit tout stop**

**ctrl c doit set args->echo->print à 130 (envoyer args dans signal?)**

**sleep 5 | sleep 5 | sleep 5 doit sleep 5s et pas 15s (le notre fait 15s)** 
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

**test**
|   |   |   |   |   |
|---|---|---|---|---|
|   |   |   |   |   |
|   |   |   |   |   |
|   |   |   |   |   |

_et la norminette lol_
