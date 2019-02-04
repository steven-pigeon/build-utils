#!/usr/bin/env python3
# -*- coding: utf8

import re,os,sys

########################################
#
# "constant"
# matches <filename> and "filename"
#
include_regex="(<|\")([^(>|\")]*)(>|\")"

########################################
#
# checks where on the include paths is
# a file, if it is at all.
#
# if it's a project file, returns the
# fully qualified name (with path), if
# not, outputs a None object
#
# heuristic: if it has a dot in it, it's
# a local file, or a project file with a
# special path (like boost, for e.g.), if
# it doesn't have a dot, let's say it's
# STL or something and output None.
#
def find_file( filename, include_paths ):

    has_dot = filename.find('.')!=-1
    is_local = filename.find('"')!=-1

    if has_dot or is_local:

        if re.match(include_regex,filename):
            strip_name=re.search(include_regex,filename)[2]
        else:
            strip_name=filename

        is_absolute = strip_name[0]=='/'

        if not is_absolute:
        
            for test_path in include_paths:
                test_name=os.path.normpath(test_path+strip_name)
                if (os.path.exists(test_name)):
                    return test_name
                else:
                    pass # not foud, maybe not a problem yet

        else:
            # treat absolute paths as "system" and
            # non-dependable
            return None

        if is_local or is_absolute:
            print("warning: "+strip_name+" not found",file=sys.stderr)
            
    else:
        pass # not a project file?

    return None

########################################
#
# scans a file for #include statements,
# and grabs < > and " " with the include
# names
def find_includes( filename, include_paths, seen ):

    try:
        input=open(filename,"r");
    except:
        raise
    else:
        includes=[]
        for line in input:
            if re.match("^\ *#\ *include",line):
                # extract filename with < > or " ", or none?
                filename=re.search(include_regex,line)
                if filename!=None:
                    if filename[2] not in seen:
                        includes+=[ find_file(filename[0], include_paths) ]
                        seen.add(filename[2])

        # project includes may have project includes,
        # so let's search them recursively
        all_includes=includes
        for include in includes:
             if include is not None:
                 found=find_file(include,include_paths);
                 if found is not None:
                     seen.add(found)
                     all_includes+=find_includes(found,include_paths,seen)

        return all_includes

########################################
#
def make_dependencies( sources, include_paths, seen ):

    for s in sources:
        try:
            includes=find_includes(s,include_paths,seen);

            print(os.path.splitext(s)[0]+".o:",s,end=" ")
            print(" ".join([str(x) for x in includes if x is not None]))
            print()

        except Exception as e:
             print(e,"file not found: "+s,file=sys.stderr)


########################################
#
# makes a list from a single string,
# using a delimiter, and removing substrings
# if need be
#
def make_list_from_arguments( string,
                              delim=' ',
                              remove="",
                              ends=""):
    return( [ x.replace(remove,"")+ends for x in string.split(delim)] )

########################################
#
#
def main():

    if len(sys.argv)==3:

        # hold files already seen
        seen=set()

        include_paths=make_list_from_arguments(sys.argv[1],remove="-I",ends='/');
        sources=make_list_from_arguments(sys.argv[2]);
        make_dependencies(sources,include_paths,seen);

        #print(seen)
        sys.exit(0) # return error code (success)
    else:
        sys.exit(1) # return error code (fail)


# linking to explicit main
#if __name__ == "__main__":
main()
