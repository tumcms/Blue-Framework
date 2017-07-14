#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2016-2017 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#   
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#   
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#

# written for Pyhton 3.2
import os
import io
import filecmp 

def DetermineCurrentRevision():
	os.environ['PATH'] = "%PATH;C:\Program Files\TortoiseHg"
	os.environ["LANGUAGE"] = "en_US.UTF-8"

	text = os.popen('hg log -l 1').read()
	print(text)
	revision = text[13:15].split(':')[0] # extract revision number
	irev = int(revision) - 1
	return str(irev)
	
def DetermineNextRevision():
	os.environ['PATH'] = "%PATH;C:\Program Files\TortoiseHg"
	os.environ["LANGUAGE"] = "en_US.UTF-8"
	
	text = os.popen('hg log -l 1').read()
	revision = text[13:15].split(':')[0] # extract revision number
	irev = int(revision)
	return str(irev)
	
def HookUpdateVersionHeaderFile():
	os.environ["LANGUAGE"] = "en_US.UTF-8"
	
	dir = os.path.abspath(os.path.join('Core','src','BlueFramework','Core'))
	in_file_filename = os.path.join(dir, 'Version.h')
	in_file = open(in_file_filename,"r")
	line_number = 0
	
	out_file_filename = os.path.join(dir, 'Version.h.2')
	out_file = open(out_file_filename, "w")
	
	for line in in_file:
		line_number = line_number + 1
		#print(str(line_number) + ": " + line)
		
		if line_number == 20:
			out_file.write("#define BLUEFRAMEWORK_API_TWEAK " + DetermineNextRevision() + "\n")
		else:
			out_file.write(line)
	
	in_file.close()
	out_file.close()
	
	# delete old version.h
	os.remove(in_file_filename)
	
	# rename new version.h.2
	os.rename(out_file_filename, os.path.join(dir, 'Version.h'))
	
def HookUpdateVersionCMakeLists():
	os.environ["LANGUAGE"] = "en_US.UTF-8"	
	dir = os.path.abspath(os.getcwd())
	in_file_filename = os.path.join(dir, 'CMake/ProjectVersion.cmake')
	in_file = open(in_file_filename,"r")
	line_number = 0
	
	out_file_filename = os.path.join(dir, 'CMake/ProjectVersion.cmake.2')
	out_file = open(out_file_filename, "w")
	
	for line in in_file:
		line_number = line_number + 1
		#print(str(line_number) + ": " + line)
		
		if line_number == 1:
			out_file.write("set(PROJECT_VERSION_TWEAK \"" + DetermineNextRevision() + "\")\n")
		else:
			out_file.write(line)
	
	in_file.close()
	out_file.close()
	
	# delete old version.h
	os.remove(in_file_filename)
	
	# rename new version.h.2
	os.rename(out_file_filename, os.path.join(dir, 'CMake/ProjectVersion.cmake'))
	
def PreCommitHook(ui, repo, hooktype, node=None, source=None, **kwargs):
	HookUpdateVersionHeaderFile()
	HookUpdateVersionCMakeLists()