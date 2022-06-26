# minishell

## ERREURS A GERER

**redir.c masterclass**

**Refaire les directions, envoyé dans redir/redir-in en se basant que sur la première redirection
de la commande:
	< tant que < et que le fichier existe continuer, si il existe pas stop et si pas de > exécuter la commande normale, sinon redirect le résultat dans le fichier avec même principe que >

**récupérer la valeur de retour du dernier pipe**

**echo e > d > l < m | ls  qui segfault**

**Fix redir_in echo p > file1 < test**

**cat << text << text2 ne se finis pas bien ??**

**/bin/ls | /bin/ls ne fonctionne pas command not found**
**builtin echo a refaire**
