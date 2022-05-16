# minishell

## ERREURS A GERER

**echo "$HOME '$USER"' == segfault**

**<< e | ls == segfault**

**dans str quotes if str[i] $ et str[i+1]= "' ou espace**

**echo "$" doit print $**

**env -i ./minishell puis cd ~/validpath == segfault**

**faire un fonction rapide pour voir si la chaîne reçu ne contient que des espaces -> free tout et ne rien faire**

**redirigé vers la bonne sortie**

**unset PATH et env -i bash == bizzare**

**Gestion de echo "$?" et echo '$?' inversé mais pour l'instant je comprends plus rien à str-quotes.c**

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
