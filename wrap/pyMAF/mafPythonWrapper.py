__author__ = 'Matteo Balasso'

import sys, os
import pprint
from jinja2 import Environment, PackageLoader
from lxml import etree
import re

from mafClassExtractor import mafClassExtractor

DEBUG = False

def main( target_wrap_file_path, source_dir, target_dir):

    # look for target_wrap_files
    wrap_class_list = []
    try:
        target_wrap_file = open( target_wrap_file_path, 'r' )

        buff = target_wrap_file.read()
        for line in buff.split("\n"):
            if str(line).startswith("#") or not line :
                continue
            wrap_class_list.append( line.replace(" ","") )

        if DEBUG:
            print wrap_class_list

        target_wrap_file.close()

    except Exception, e:
        print e
        wrap_class_list = []


    # load jinja environment variable
    env = Environment(loader=PackageLoader('pyMAF', 'templates'))
    decorator_template_header = env.get_template('mafDecoratorTemplate.h')
    decorator_template_source = env.get_template('mafDecoratorTemplate.cpp')

    # create extractor
    extractor = mafClassExtractor()

    # cycle for all xml files into doxygen directory

    files_into_source_dir = []
    for directory, root, filenames in os.walk( source_dir):
        for filename in filenames:
            files_into_source_dir.append( os.path.join( directory, filename) )

    x = re.compile("\Aclass[maf|vtk].*\.xml")

    files_to_parse = [ filename for filename in files_into_source_dir if re.match(x, os.path.basename(filename))]

    debugClassDetails = {}

    for file_to_parse in files_to_parse:

        doxygen = etree.fromstring( open(file_to_parse, 'r').read() )
        
        try:
          classDetails = extractor.extractFromDoxygen( doxygen )
        except Exception, e:
          print e
          continue

        if not classDetails['compoundname'] in wrap_class_list:
            continue

        print "\n Wrapping file %s " % file_to_parse

        print "\n\t - wrapping class %s " % classDetails['compoundname' ]

        if classDetails['compoundname'] == 'mafMatrix':
            debugClassDetails = classDetails


        # generate decorator header file
        output_file_name = os.path.join( target_dir, classDetails['compoundname'] + "Decorator.h"  )
        decorator_template_header.stream(classDetails).dump(output_file_name)

        print "\n\t - written file %s" % output_file_name

        # generate decorator source file
        output_file_name = os.path.join( target_dir, classDetails['compoundname'] + "Decorator.cpp"  )
        decorator_template_source.stream(classDetails).dump(output_file_name)

        print "\n\t - written file %s" % output_file_name


    if DEBUG:
        f = open("debug.txt","w")
        defstdout = sys.stdout
        sys.stdout = f
        for key in debugClassDetails.keys():
            pprint.pprint(debugClassDetails)
        f.close()

        sys.stdout = defstdout


def usage():
    print "\n\n"
    print "\tUsage: %s <absolute_path_to_wrap_class_file_list> <absolute_path_doxygen_source_xml_directory> <absolute_path_destination_directory> \n" % sys.argv[0]
    print "\t\t%s will look for a 'target_wrap_files' with the list of the classes to be wrapped" % sys.argv[0]
    print "\t\tIf 'target_wrap_files' not found: no files will be wrapped\n\n"
    print "arguments: ", sys.argv

if __name__ == '__main__':

    if len(sys.argv) < 4:
        usage()
        print "please provide all inputs!"
        sys.exit( -1 )

    main(sys.argv[1], sys.argv[2], sys.argv[3])

