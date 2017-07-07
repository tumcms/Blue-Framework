import os
import sys, getopt
import xml.etree.ElementTree
from subprocess import call

def compileEffect(effectFile, dir):
	effect = xml.etree.ElementTree.parse(effectFile).getroot()
	shader = {}
		
	for pipelinestate in effect.findall('pipelinestate'):
		d3d11 = pipelinestate.find("D3D11")
		vs = d3d11.find("VertexShader")
		gs = d3d11.find("GeometryShader")
		ps = d3d11.find("PixelShader")
		if vs != None:
			filename = vs.get("filename")
			entry = vs.get("entry")
			name = os.path.splitext(filename)[0] + "_" + entry
			shader[name] = ["vs_5_0", filename, entry]
		if gs != None:
			filename = gs.get("filename")
			entry = gs.get("entry")
			name = os.path.splitext(filename)[0] + "_" + entry
			shader[name] = ["gs_5_0", filename, entry]
		if ps != None:
			filename = ps.get("filename")
			entry = ps.get("entry")
			name = os.path.splitext(filename)[0] + "_" + entry
			shader[name] = ["ps_5_0", filename, entry]
			
	for name in shader:
		args = shader[name]
		call("fxc /T " + args[0] + " /E " + args[2] + " /Fo " + dir + "/" + name + ".cso " + dir + "/" + args[1])
	

def main(argv):
	if len(argv) != 1:
		print ("usage: precompileEffectFiles.py <path/to/effectDir>")
		sys.exit(2)
	
	dir = argv[0]
	for file in os.listdir(dir):
		if file.endswith(".be"):
			compileEffect(dir + "/" + file, dir)
	
if __name__ == "__main__":
    main(sys.argv[1:])