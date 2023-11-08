#
#   This file is part of BlueFramework, a simple 3D engine.
#   Copyright (c) 2023 Technical University of Munich
#   Chair of Computational Modeling and Simulation.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

import uuid
import string
import sys
import argparse

from optparse import OptionParser

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

textHeader = """/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016 Technical University of Munich
	Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
"""

def main(argv):
	parser = argparse.ArgumentParser()
	parser.add_argument("moduleName")
	parser.add_argument("className")
	args = parser.parse_args()
	
	
	className = args.className
	moduleName = args.moduleName
    
	#strUuid = string.replace(str(uuid.uuid4()), "-", "_")
	strUuid = str(uuid.uuid4())
	strUuid = strUuid.replace("-","_")
	
	print(textHeader)
	
	print("#pragma once")
	print("#ifndef BlueFramework_" + moduleName + "_" + className + "_" + strUuid + "_h")
	print("#define BlueFramework_" + moduleName + "_" + className + "_" + strUuid + "_h")
	print("")
	print("#include \"BlueFramework/" + moduleName + "/namespace.h\"")
	print("")
	print("BLUEFRAMEWORK_" + moduleName.upper() + "_NAMESPACE_BEGIN")
	
	print("class " + className + "{");
	print("public:")
	
	print(className + "() {" )
	print("}")
	
	print("virtual ~" + className + "() {" )
	print("}")	
	
	print("};")
	print("")
	
	print("BLUEFRAMEWORK_" + moduleName.upper() + "_NAMESPACE_END")
	print("")
	
	print("#endif // end define BlueFramework_" + moduleName + "_" + className + "_" + strUuid + "_h")
	   
if __name__ == "__main__":
   main(sys.argv[1:])
