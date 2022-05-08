#!/bin/bash
#####################################################################################
# UQAM - Département d'informatique
# INF3105 - Structures de données et algorithmes
# TP1 - Positionement de stations radio
#
# Script d'évaluation
#
# Instructions:
# 1. Déposer ce script avec les fichiers problèmes dans un répertoire 
#    distinct (ex: tests).
# 2. Étudiants : Se placer dans le répertoire contenant votre programme
#    Correcteur : Se placer dans répertoire contenant les soumissions Oto (*.tp_oto).
# 3. Lancer ce script (ex: ../tests/evaluer.sh).
#####################################################################################

echo "Évaluation du TP1 d'INF3105..."

# Répertoire contenant les fichiers tests
repertoire_tests=`dirname $0`
pushd $repertoire_tests
repertoire_tests=`pwd`
popd

if [ `pwd` -ef $repertoire_tests ];
then
    echo "Ce script doit être dans un répertoire différent de celui contenant tp1."
    echo "Ce script a été arrêté pour ne pas écraser les fichiers *-req[0-9]+.txt !"
    exit -2;
fi

tests=`cd $repertoire_tests && ls test[A-Z][0-9][0-9].txt`

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

# Limiter le temps d'exécution et la quantite de mémoire
ulimit -t 120 -v 2097152 -f 1024
echo "Limite de temps par test : `ulimit -t` secondes."
echo "Limite de mémoire par test : `ulimit -v` KiO."
echo "Limite de taille de fichier : `ulimit -f` KiO."


function Nettoyer
{
    echo "Nettoyage"
    # Au cas où le Makefile des étudiants ne ferait pas un «make clean» correctement.
    #make clean

    rm -f *.o* *.gch tp[1-3] *+.txt
    # Au besoin, nettoyer les précédents fichiers logs
    rm -f log*.txt
}


##### Fonction d'évaluation d'un TP ######
function EvaluerTP
{
    ## Forcer la recompilation.
    #rm -f tp1 *.o *.gch
    #make clean
    # Recompiler
    make tp1

    if [ ! -x tp1 ]
        then
        echo " Erreur : le fichier tp1 n'existe pas ou n'est pas exécutable!"
        return
    fi

    date2=`date +%Y%m%d_%H%M%S`
    logfile="log-${date2}.txt"

    echo "Évaluation des temps d'exécution de tp1 sur les jeux de tests."
    echo "Les résultats sont déposés dans $logfile."

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
    # echo "Taille des fichiers source :" >> ${logfile}
    # wc *.{c*,h*}  >> ${logfile}

    echo -e "Fichier_test\t#Stat\t#Imm\t#Cli\tOpt?\tCPU\tMém.(k)"
    echo -e "Fichier_test\t#Stat\t#Imm\t#Cli\tOpt?\tCPU\tMém.(k)" >> $logfile

    for test in $tests;
    do
        fichier=$repertoire_tests/$test

        if [ $souslinux -eq 0 ]; then
            tcpu="`(/usr/bin/time -f "%U\t%Mk" ./tp1 $fichier > ${test%.txt}+.txt) 2>&1 | tail -n 1`"
        else
            tcpu=`(time -p ./tp1 $fichier > ${test%.txt}+.txt) 2>&1 | egrep user | cut -f 2 -d " "`
        fi

        if ( [ -x ${valideur} ] && [ -e "${fichier%.txt}+.txt" ] )
        then
            compte=`$valideur $fichier "${test%.txt}+.txt"`
            echo $compte > "${test%.txt}=.txt"
            comptesolution=`$valideur $fichier "${fichier%.txt}+.txt"`
            [ "$compte" != "$comptesolution" ];
            optimal=$?
        else
            compte="?"
            optimal="?"
        fi

        #test2="${test%.txt}"
        #nbstations=`echo $test2 | cut -d _ -f 2`
        #nbimmeubles=`echo $test2 | cut -d _ -f 3`
        #
        #echo -e "$test\t#$nstations\t$nbimmeubles\t$compte\t$optimal\t$tcpu"
        #echo -e "$test\t#$nbstations\t$nbimmeubles\t$compte\t$optimal\t$tcpu" >> $logfile
        echo -e "$test\t$compte\t$optimal\t$tcpu"
        echo -e "$test\t$compte\t$optimal\t$tcpu" >> $logfile
        sommaire="${sommaire}\t$test\t$compte\t$optimal\t$tcpu\t"
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
echo "#Rapport d'évaluation INF3105 / $programme" > "rapport-${date}.txt"
echo -e "#Date:\t${date}" >> "rapport-${date}.txt"
echo -e "#Machine :\t" `hostname` >> "rapport-${date}.txt"
echo -e "#CPU :\t$cpuinfo" >> "rapport-${date}.txt"
echo >> "rapport-${date}.txt"

# Génération des titres des colonnes
echo -e -n "Soumission\t" >> rapport-${date}.txt
for test in $tests;
do
    echo -e -n "\tFichier_test\t#Stat\t#Imm\t#Clients\tOpt?\tCPU\tMém.(k)\t" >> "rapport-${date}.txt"
done
echo >> "rapport-${date}.txt"


# Itération sur chaque TP
for tp in $tps; do
    sommaire=""
    echo "## ÉVALUATION : $tp"
    pushd $tp
        EvaluerTP
#        Nettoyer
    popd
    #echo -e ">> ${sommaire}"
    echo -e "${tp}\t${sommaire}" >> "rapport-${date}.txt"
done
