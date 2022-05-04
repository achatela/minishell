# minishell

## ERREURS A GERER

**ctrl c dans here doc**

**dans redir-in gérer les retours de access (no such file, permission denied...)**

**segfault prompt fix manque manque prompt par défaut/static prompt
-> créer une variable PROMPT= au lancement**

**segfault quand mkdir 1 -> cd 1 -> mkdir 2 -> cd 2 - > rm -rf ../../1/ fix mais cd .. fonctionne bizzarement**

**"." et ".." ignorés**

**"cd ..." ignoré**

**echo $? pour voir la valeur du return.**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

**problème plusieurs redir in == devrait arrêter de parser au premier '<'**

**cat | ls == écrit ls après le prompt après un ctrl c/d**

**ctrl c dans un cat/qqch d'infini == double prompt**

_et la norminette lol_
