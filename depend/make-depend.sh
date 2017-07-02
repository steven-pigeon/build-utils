#!/usr/bin/env bash


function joli {
    # sed: the first symbol after s is the separator
    # replaces multiple consecutives ///// by /
    # then removes initial ./ at the begining
    echo $1 | sed -e 's,/[/]*,/,g' | sed -e 's,^\./,,'
    }

function exists {
    local where=$1
    local dir=$2
    local name=$3
    for w in ${where[@]}
    do
        local f=$w/$dir/$name
        if [ -f "$f" ]
        then
            echo -n $(joli $f)' '
        fi
    done
}


################################3
includes=$(echo $1 | sed s/-I//g)
files=$2

all_headers=( )

for f in ${files[@]}
do
    # grep: finds lines that begin by #include
    # sed: extracts between < >
    # tr: replaces \n by space
    # sed: removes trailing spaces
    echo -n ${f%.*}.o": "$f" "
    headers=$(
        grep -e '^\ *#\ *include' $f \
            | sed 's/.*<\(.*\)>.*/\1/' \
            | tr '\n' ' ' \
            | sed -e 's/[ ]*$//' \
           )

    z=$(
    for h in ${headers[@]}
    do
        d=$(dirname $h | sed -e 's/^\.//' )
        b=$(basename $h)
        exists "${includes[@]}" "$d" "$b"
    done )

    echo $z # | sed -e 's/\ /\ \\\n/g'
    echo

    all_headers+=( $z )
done


headers=$(echo ${all_headers[@]} | tr ' ' '\n' | sort -u)
for h in ${headers[@]}
do
    echo $h":"
    echo
done


exit 0
