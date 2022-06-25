# minishell

## ERREURS A GERER

**Refaire les directions, envoyé dans redir/redir-in en se basant que sur la première redirection
de la commande:
	> avancer + créer au fur et à mesure si < check si il existe pas (stop) ou check si il existe et continuer d'avancer
	< tant que < et que le fichier existe continuer, si il existe pas stop et si pas de > exécuter la commande normale, sinon redirect le résultat dans le fichier avec même principe que >

**récupérer la valeur de retour du dernier pipe**

**echo e > d > l < m | ls  qui segfault**

**Fix redir_in echo p > file1 < test**

**cat << text << text2 ne se finis pas bien ??**

**/bin/ls | /bin/ls ne fonctionne pas command not found**
**builtin echo a refaire**
