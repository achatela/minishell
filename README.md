# minishell

## ERREURS A GERER

**Unset the $PATH and check if it is not working anymore**

**./minishell devrait fonctionner**

**récupérer la valeur de retour du dernier pipe**
**prbl peut-être parce que le dernier pipe est dans un child du coup il modifie pas g-env**

**Probleme sur les fd check avec valgrind --track-fds=yes (pipes)**

**valeur de retour de tous les builtins**

**export txt puis export txt=value crée une nouvelle var txt (doublon)**

**unset ne fonctionne pas avec les var export sans =**

**export arg= doit être dans env et export arg doit être dans export sans arg uniquement**

**cat << ok << salut doit afficher ce qu'on a place dans le heredoc**

**cat | cat |ls**

**créer un fichier dans heredoc pour pouvoir remplacer << txt par < file quand cat **
**que si cmd == cat et pour le dernier <<**

**yes | head**
![image](https://cdn.discordapp.com/attachments/856902451403423745/969613000052994068/unknown.png)

**test**
|   |   |   |   |   |
|---|---|---|---|---|
|   |   |   |   |   |
|   |   |   |   |   |
|   |   |   |   |   |
