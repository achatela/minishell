# minishell

## ERREURS A GERER

**echo -n "$?" segfault**

**Gestion de echo "$?" et echo '$?' inversé mais pour l'instant je comprends plus rien à str-quotes.c**

**Gérer erreurs dans redir.c**

**ctrl c dans here doc**

**segfault quand mkdir 1 -> cd 1 -> mkdir 2 -> cd 2 - > rm -rf ../../1/ fix mais cd .. fonctionne bizzarement**

**"." et ".." ignorés**

**echo $? pour voir la valeur du return.**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

**problème plusieurs redir in après pipe == devrait arrêter de parser au premier '<'**

**cat | ls == écrit ls après le prompt après un ctrl c**

**ctrl c dans un cat/qqch d'infini == double prompt**

**test**
|   |   |   |   |   |
|---|---|---|---|---|
|   |   |   |   |   |
|   |   |   |   |   |
|   |   |   |   |   |

_et la norminette lol_
