#!/bin/bash
##########################################################################
# UQAM - Département d'informatique
# INF3105 - Structures de données et algorithmes
# Automne 2017
# TP2
# http://ericbeaudry.uqam.ca/INF3105/tp2/
# beaudry.eric@uqam.ca
#
# Script d'évaluation
#
# Instructions:
# 1. Déposer ce script avec les fichiers problèmes dans un répertoire 
#    distinct (ex: tests).
# 2. Se placer dans le répertoire contenant votre programme ou contenant
#    la liste des soumissions Oto (*.tp_oto).
# 3. Lancer ce script (ex: ../tests/evaluer.sh).
##########################################################################

# Obtenir le chemin du répertoire contenant le présent script et les fichiers tests
pushd `dirname $0`
repertoire_tests=`pwd`
# Lister les fichier test disponibles
tests=`ls exemple[0-9].txt test[A-Z][0-9].txt`
popd

echo "UQAM | Département d'informatique"
echo "INF3105 | Structures de données et algorithmes"
echo "Évaluation du TP2"
echo

if [ `pwd` -ef $repertoire_tests ];
then
    echo "Ce script doit être dans un répertoire différent de celui contenant votre tp2."
    echo "Ce script a été arrêté afin de ne pas écraser les fichiers test[A-Z]*.resultat!"
    exit -2;
fi

########### Détection du valideur de résultats #######
# Exécutable du programme de validation
valideur="${repertoire_tests}/valideur"
if [ -x "${valideur}-`uname`-`uname -p`" ]
then
    valideur="${valideur}-`uname`-`uname -p`"
else
    if [ -x "${valideur}-`uname`" ]
    then
        valideur="${valideur}-`uname`"
    fi
fi
######################################################


# Détection si l'utilitaire time sous Linux est disponible (peut afficher 0.00)
echo "Détection de /usr/bin/time..."
/usr/bin/time -f %U echo 2>&1 > /dev/null
souslinux=$?

# Fixer les limites : 120s, 2048Mo mémoire et 20Mo fichier
ulimit -t 180 -v 2097152 -f 20480
echo "ulimit (limites courantes des ressources) :"
ulimit -t -v -f
echo "-----"

# Détection du CPU
if [ -e /proc/cpuinfo ] ; then
    cpuinfo=`grep "model name" /proc/cpuinfo | sort -u | cut -d ":" -f 2`
else
    cpuinfo="?"
fi

function Nettoyer
{
    echo "Nettoyage"
    # Au cas où le Makefile des étudiants ne ferait pas un «make clean» correctement.
    #make clean

    rm -f *.o* *.gch tp[1-3] *-req?+.txt
    # Au besoin, nettoyer les précédents fichiers logs
    rm -f log*.txt
}


##### Fonction d'évaluation d'un TP ######
function EvaluerTP
{
    ## Forcer la recompilation.
    #rm tp2 *.o
    #make clean   
    
    date2=`date +%Y%m%d_%H%M%S`
    logfile="log-${date2}.txt"
    echo "Les résultats seront déposés dans $logfile..."

    echo "Machine : " `hostname`
    echo "#Machine : " `hostname`  > $logfile
    echo "CPU :$cpuinfo" 
    echo "#CPU :$cpuinfo"  >> $logfile
    echo "Date début : ${date2}"
    echo "#Date début : ${date2}"  >> $logfile
    echo "Limite de `ulimit -t` secondes par test"
    echo "#Limite de `ulimit -t` secondes par test"  >> $logfile
    echo
    echo "#" >> $logfile

    # Pour statistiques : nombre de lignes de code...
    echo "Taille des fichiers source :" >> ${logfile}
    wc *.{c*,h*}  >> ${logfile}

    taille=`wc *.{c*,h*} | grep total`
    sommaire="$taille"
    
    make tp2
    
    # Vérification de l'existance du programme.
    if [ ! -e ${programme} ]
	    then
	    echo "  Erreur : le fichier ${programme} est inexistant!"
	    return
    fi
    if [ ! -x ${programme} ]
	    then
	    echo "  Erreur : le fichier ${programme} n'est pas exécutable!"
	    return
    fi


	echo 
	echo "#" >> $logfile

	echo -e "Test    \tCPU\tMém.(k)\tValidation"
	echo -e "Test    \tCPU\tMém.(k)\tValidation" >> $logfile

	for test in $tests;
	do
    	requete="${requete#*_}"
    	args=`echo $requete | sed s/'-'/' '/g`
    
	    fichiertest=$repertoire_tests/$test
    
	    fichierresultat="${test%.txt}+.txt"
    	fichiersolution="$repertoire_tests/${test%.txt}+.txt"
    
        if [ $souslinux -eq 0 ]; then
            tcpu="`(/usr/bin/time -f "%U\t%Mk" ./tp2 $fichiertest > $fichierresultat) 2>&1 | tail -n 1`"
    	else
        	tcpu=`(time -p ./tp2 $fichiertest $args > $fichierresultat) 2>&1 | egrep user | cut -f 2 -d " "`
        fi
    
    	validation="?"
    	if ( [ -x ${valideur} ] && [ -e $fichierresultat ] )
	    then
        	validation=`$valideur $fichiersolution $fichierresultat -v`
        	validation2=`$valideur $fichiersolution $fichierresultat`
    	else
        	if( [ -e $fichiersolution ] )
        	then
            	diff -tibw $fichierresultat $fichiersolution 2>&1 > /dev/null
        		if [ $? -eq 0 ];
        		then
        	    	validation="=="
         		else
         	    	validation="!="
        		fi
        	fi
    	fi

    	echo -e "$test\t$tcpu\t$validation"
    	echo -e "$test\t$tcpu\t$validation" >> $logfile
    	sommaire="${sommaire}\t${tcpu}\t${validation2}"
	done
}

# Lister les soumissions Oto (répertoires terminant par .tp_oto)
tps=`ls -1 | grep .tp_oto`
# Si aucun répertoire .tp_oto n'existe, essayer le répertoire courant (auto-évaluation)
if [ ! -n "$tps" ]; then
    tps="."
fi

# Génération de l'entête du rapport
date=`date +%Y%m%d_%H%M%S`
echo "#Rapport de correction INF3105 / TP2" > "rapport-${date}.txt"
echo -e "#Date:\t${date}" >> "rapport-${date}.txt"
echo -e "#Machine :\t" `hostname` >> "rapport-${date}.txt"
echo -e "#CPU :\t$cpuinfo" >> "rapport-${date}.txt"
echo >> "rapport-${date}.txt"

# Génération des titres des colonnes
echo -e -n "#\t" >> "rapport-${date}.txt"
for test in ${tests}; do
    echo -e -n "\t${requete}\t\t" >> "rapport-${date}.txt"
done
echo >> "rapport-${date}.txt"
echo -e -n "#Soumission\tTaille sources" >> "rapport-${date}.txt"
for test in ${tests}; do
   echo -e -n "\tOpt?\tCPU\tMem" >> "rapport-${date}.txt"
done
echo >> "rapport-${date}.txt"

# Itération sur chaque TP
for tp in $tps; do
    sommaire=""
    echo "## CORRECTION : $tp"
    pushd $tp
    	EvaluerTP
#       Nettoyer
    popd
    #echo -e ">> ${sommaire}"
    echo -e "${tp}\t${sommaire}" >> "rapport-${date}.txt"
done

