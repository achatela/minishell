# minishell

## ERREURS A GERER

**echo -n "$?" segfault**

**Gestion de echo "$?" et echo '$?' inversé mais pour l'instant je comprends plus rien à str-quotes.c**

**Gérer erreurs dans redir.c**

**command avec un path quand PATH est unset doit fonctionner**

**ctrl c dans here doc**

**segfault prompt fix manque manque prompt par défaut/static prompt
-> créer une variable PROMPT= au lancement**

**segfault quand mkdir 1 -> cd 1 -> mkdir 2 -> cd 2 - > rm -rf ../../1/ fix mais cd .. fonctionne bizzarement**

**si HOME est changé, cd sans arg doit aller au new HOME
et s'il n'est pas dans env, cd: HOME not set**

**cd "" pas bon, cd "$VAR" doit d'abord check si $HOME existe, var inexistante == rien, sinon cd var**

**"." et ".." ignorés**

**"cd ..." ignoré**

**Essayer de remplacer toutes les fois où on utilise getenv() -> les variables exportées ne sont pas dans l'env de la fonction
peut-être par get-env-var mais il renvoyait "\0" au lieu de NULL**

**echo $? pour voir la valeur du return.**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

**problème plusieurs redir in après pipe == devrait arrêter de parser au premier '<'**

**cat | ls == écrit ls après le prompt après un ctrl c**

**ctrl c dans un cat/qqch d'infini == double prompt**

**cd ...... va dans home**

**test**
|   |   |   |   |   |
|---|---|---|---|---|
|   |   |   |   |   |
|   |   |   |   |   |
|   |   |   |   |   |

_et la norminette lol_
