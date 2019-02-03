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
    local found=false
    
    dequoted_name=$(echo $name | sed 's/\(<\|>\|"\)//g')
    for w in ${where[@]}
    do
        local f=$w/$dir/$dequoted_name
        if [ -f "$f" ]
        then
            echo -n $(joli $f)' '
            found=true
        fi
    done

    # file not found?
    if [ $found = false ]
    then
        # check if it might be in the STL
        # by assuming that if there's a dot in
        # the name, it's user-defined (and if
        # it's in quotation, check anyway)
        #
        if [[ "$name" =~ .*'.'.* || \
              "$name" =~ \".*\" ]]
        then
            echo not found: $name 1>&2
        else
           :; # should do better checking
        fi
    fi
}


################################3
function find_headers {
    local includes=$1
    local files=$2

    for f in ${files[@]}
    do
        # grep: finds lines that begin by #include
        # sed: extracts between < > or " " but keeps delimiters
        # tr: replaces \n by space
        # sed: removes trailing spaces
        echo -n ${f%.*}.o": "$f" "
        headers=$(
            grep -e '^\ *#\ *include' $f \
                | sed 's/.*\(<\|"\)\(.*\)\(>\|"\).*/\1\2\3/' \
                | tr '\n' ' ' \
                | sed -e 's/[ ]*$//' \
               )
        
        z=$(
            for h in ${headers[@]}
            do
                #echo "$h" 1>&2
                d=$(dirname $h | sed -e 's/^\.//' )
                b=$(basename $h)
                exists "${includes[@]}" "$d" "$b"
            done )
        
        echo $z # | sed -e 's/\ /\ \\\n/g'
        echo
        
        all_headers+=( $z )
    done
}


################################3
includes=$(echo $1 | sed s/-I//g)
files=$2

all_headers=( )

find_headers "$includes" "$files"


headers=$(echo ${all_headers[@]} | tr ' ' '\n' | sort -u)
for h in ${headers[@]}
do
    echo $h":"
    echo
done


exit 0
