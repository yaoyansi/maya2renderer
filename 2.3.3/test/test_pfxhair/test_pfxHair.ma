//Maya ASCII 2009 scene
//Name: test_pfxHair.ma
//Last modified: Sun, Feb 26, 2012 10:44:37 PM
//Codeset: 936
requires maya "2009";
requires "liquid_2009x32d" "2.3.5 (buildtime=21:57:10.67)";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2009";
fileInfo "version" "2009";
fileInfo "cutIdentifier" "200809110030-734661";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 5.4942440362534031 6.1961209260361096 -2.7035032278905109 ;
	setAttr ".r" -type "double3" -45.338352729641763 116.19999999997586 0 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 8.7113467250012491;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 100.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 100.1 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 100.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pPlane1";
	setAttr ".t" -type "double3" 0.34594666752512637 0 2.6786140565862091 ;
createNode mesh -n "pPlaneShape1" -p "pPlane1";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	addAttr -ci true -sn "shaderFullPath" -ln "shaderFullPath" -dt "string";
	addAttr -ci true -sn "liquidSurfaceShaderNode" -ln "liquidSurfaceShaderNode" -at "message";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".shaderFullPath" -type "string" "E:\\MyDocuments\\maya\\projects\\default\\generatedShader\\lambert1.slo";
createNode transform -n "pointLight1";
	setAttr -s 3 ".rlio";
	setAttr -s 3 ".rlio";
	setAttr ".t" -type "double3" 0 6.9342733301266515 0 ;
createNode pointLight -n "pointLightShape1" -p "pointLight1";
	setAttr -k off ".v";
	setAttr ".us" no;
createNode transform -n "hairSystem1";
createNode hairSystem -n "hairSystemShape1" -p "hairSystem1";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".evo" 0;
	setAttr ".sfn" 0.1;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr ".itr" 2;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr ".clc[0]"  0 0.5 1;
	setAttr ".cfl[0]"  0 0 1;
	setAttr -s 2 ".hws[0:1]"  0.80000001 1 3 1 0.2 3;
	setAttr -s 3 ".hcs";
	setAttr ".hcs[0].hcsp" 0;
	setAttr ".hcs[0].hcsc" -type "float3" 0.5 0.5 0.5 ;
	setAttr ".hcs[0].hcsi" 3;
	setAttr ".hcs[1].hcsp" 0.30000001192092896;
	setAttr ".hcs[1].hcsc" -type "float3" 0.80000001 0.80000001 0.80000001 ;
	setAttr ".hcs[1].hcsi" 3;
	setAttr ".hcs[2].hcsp" 1;
	setAttr ".hcs[2].hcsc" -type "float3" 1 1 1 ;
	setAttr ".hcs[2].hcsi" 3;
	setAttr ".hpc" 1;
	setAttr ".dsc[0]"  0 1 1;
createNode transform -n "hairSystem1Follicles";
createNode transform -n "pPlane1Follicle5050" -p "hairSystem1Follicles";
createNode follicle -n "pPlane1FollicleShape5050" -p "pPlane1Follicle5050";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.5;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve1" -p "pPlane1Follicle5050";
createNode nurbsCurve -n "curveShape1" -p "curve1";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pfxHair1";
createNode pfxHair -n "pfxHairShape1" -p "pfxHair1";
	setAttr -k off ".v";
	setAttr ".dpc" 100;
	setAttr ".dam" no;
createNode transform -n "pPlane2";
	setAttr ".t" -type "double3" -1.2021928732397886 0.32153940345859389 1.7470088824845451 ;
	setAttr ".r" -type "double3" 0 0 -79.52643465241178 ;
	setAttr ".s" -type "double3" 2.3468174499045262 1 1 ;
createNode mesh -n "pPlaneShape2" -p "pPlane2";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "locator1";
	setAttr ".t" -type "double3" 0.423477 3 0.955479 ;
createNode locator -n "locatorShape1" -p "locator1";
	setAttr -k off ".v";
createNode transform -n "locator2";
	setAttr ".t" -type "double3" 0.320103 1.5 1.037876 ;
createNode locator -n "locatorShape2" -p "locator2";
	setAttr -k off ".v";
createNode transform -n "locator3";
	setAttr ".t" -type "double3" 0.216729 0 1.120273 ;
createNode locator -n "locatorShape3" -p "locator3";
	setAttr -k off ".v";
createNode transform -n "locator4";
	setAttr ".t" -type "double3" 0.113355 -1.5 1.20267 ;
createNode locator -n "locatorShape4" -p "locator4";
	setAttr -k off ".v";
createNode transform -n "pPlane3";
	setAttr ".t" -type "double3" -0.10441417249703377 0 1.5907267212378136 ;
createNode mesh -n "pPlaneShape3" -p "pPlane3";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "hairSystem2";
createNode hairSystem -n "hairSystemShape2" -p "hairSystem2";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".evo" 0;
	setAttr ".sfn" 0.1;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr ".itr" 2;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr ".clc[0]"  0 0.5 1;
	setAttr ".cfl[0]"  0 0 1;
	setAttr -s 2 ".hws[0:1]"  0.80000001 1 3 1 0.2 3;
	setAttr -s 3 ".hcs";
	setAttr ".hcs[0].hcsp" 0;
	setAttr ".hcs[0].hcsc" -type "float3" 0.5 0.5 0.5 ;
	setAttr ".hcs[0].hcsi" 3;
	setAttr ".hcs[1].hcsp" 0.30000001192092896;
	setAttr ".hcs[1].hcsc" -type "float3" 0.80000001 0.80000001 0.80000001 ;
	setAttr ".hcs[1].hcsi" 3;
	setAttr ".hcs[2].hcsp" 1;
	setAttr ".hcs[2].hcsc" -type "float3" 1 1 1 ;
	setAttr ".hcs[2].hcsi" 3;
	setAttr ".hpc" 1;
	setAttr ".dsc[0]"  0 1 1;
createNode transform -n "hairSystem2Follicles";
createNode transform -n "pPlane3Follicle5050" -p "hairSystem2Follicles";
createNode follicle -n "pPlane3FollicleShape5050" -p "pPlane3Follicle5050";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.5;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve2" -p "pPlane3Follicle5050";
createNode nurbsCurve -n "curveShape2" -p "curve2";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pfxHair2";
	setAttr ".t" -type "double3" -0.21344745718406255 0 -0.11449683743484407 ;
createNode pfxHair -n "pfxHairShape2" -p "pfxHair2";
	setAttr -k off ".v";
	setAttr ".dpc" 100;
	setAttr ".dam" no;
createNode transform -n "pPlane4";
	setAttr ".t" -type "double3" 0.38165441973949221 0 0.18801654169079729 ;
createNode mesh -n "pPlaneShape4" -p "pPlane4";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "hairSystem3";
createNode hairSystem -n "hairSystemShape3" -p "hairSystem3";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr -s 40 ".ih";
	setAttr ".evo" 0;
	setAttr ".sfn" 0.1;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr ".itr" 2;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr ".clc[0]"  0 0.5 1;
	setAttr ".cfl[0]"  0 0 1;
	setAttr -s 2 ".hws[0:1]"  0.80000001 1 3 1 0.2 3;
	setAttr -s 3 ".hcs";
	setAttr ".hcs[0].hcsp" 0;
	setAttr ".hcs[0].hcsc" -type "float3" 0.5 0.5 0.5 ;
	setAttr ".hcs[0].hcsi" 3;
	setAttr ".hcs[1].hcsp" 0.30000001192092896;
	setAttr ".hcs[1].hcsc" -type "float3" 0.80000001 0.80000001 0.80000001 ;
	setAttr ".hcs[1].hcsi" 3;
	setAttr ".hcs[2].hcsp" 1;
	setAttr ".hcs[2].hcsc" -type "float3" 1 1 1 ;
	setAttr ".hcs[2].hcsi" 3;
	setAttr ".dsc[0]"  0 1 1;
createNode transform -n "hairSystem3Follicles";
createNode transform -n "pPlane4Follicle606" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape606" -p "pPlane4Follicle606";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.0625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve3" -p "pPlane4Follicle606";
createNode nurbsCurve -n "curveShape3" -p "curve3";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle619" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape619" -p "pPlane4Follicle619";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.1875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve4" -p "pPlane4Follicle619";
createNode nurbsCurve -n "curveShape4" -p "curve4";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle631" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape631" -p "pPlane4Follicle631";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.3125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve5" -p "pPlane4Follicle631";
createNode nurbsCurve -n "curveShape5" -p "curve5";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle643" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape643" -p "pPlane4Follicle643";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.4375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve6" -p "pPlane4Follicle643";
createNode nurbsCurve -n "curveShape6" -p "curve6";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle656" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape656" -p "pPlane4Follicle656";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.5625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve7" -p "pPlane4Follicle656";
createNode nurbsCurve -n "curveShape7" -p "curve7";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle668" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape668" -p "pPlane4Follicle668";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.6875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve8" -p "pPlane4Follicle668";
createNode nurbsCurve -n "curveShape8" -p "curve8";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle680" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape680" -p "pPlane4Follicle680";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.8125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve9" -p "pPlane4Follicle680";
createNode nurbsCurve -n "curveShape9" -p "curve9";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle693" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape693" -p "pPlane4Follicle693";
	setAttr -k off ".v";
	setAttr ".pu" 0.055555555555555552;
	setAttr ".pv" 0.9375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve10" -p "pPlane4Follicle693";
createNode nurbsCurve -n "curveShape10" -p "curve10";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1706" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1706" -p "pPlane4Follicle1706";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.0625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve11" -p "pPlane4Follicle1706";
createNode nurbsCurve -n "curveShape11" -p "curve11";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1719" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1719" -p "pPlane4Follicle1719";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.1875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve12" -p "pPlane4Follicle1719";
createNode nurbsCurve -n "curveShape12" -p "curve12";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1731" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1731" -p "pPlane4Follicle1731";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.3125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve13" -p "pPlane4Follicle1731";
createNode nurbsCurve -n "curveShape13" -p "curve13";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1743" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1743" -p "pPlane4Follicle1743";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.4375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve14" -p "pPlane4Follicle1743";
createNode nurbsCurve -n "curveShape14" -p "curve14";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1756" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1756" -p "pPlane4Follicle1756";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.5625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve15" -p "pPlane4Follicle1756";
createNode nurbsCurve -n "curveShape15" -p "curve15";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1768" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1768" -p "pPlane4Follicle1768";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.6875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve16" -p "pPlane4Follicle1768";
createNode nurbsCurve -n "curveShape16" -p "curve16";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1780" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1780" -p "pPlane4Follicle1780";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.8125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve17" -p "pPlane4Follicle1780";
createNode nurbsCurve -n "curveShape17" -p "curve17";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle1793" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape1793" -p "pPlane4Follicle1793";
	setAttr -k off ".v";
	setAttr ".pu" 0.16666666666666666;
	setAttr ".pv" 0.9375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve18" -p "pPlane4Follicle1793";
createNode nurbsCurve -n "curveShape18" -p "curve18";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2806" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2806" -p "pPlane4Follicle2806";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.0625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve19" -p "pPlane4Follicle2806";
createNode nurbsCurve -n "curveShape19" -p "curve19";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2819" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2819" -p "pPlane4Follicle2819";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.1875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve20" -p "pPlane4Follicle2819";
createNode nurbsCurve -n "curveShape20" -p "curve20";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2831" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2831" -p "pPlane4Follicle2831";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.3125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve21" -p "pPlane4Follicle2831";
createNode nurbsCurve -n "curveShape21" -p "curve21";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2843" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2843" -p "pPlane4Follicle2843";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.4375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve22" -p "pPlane4Follicle2843";
createNode nurbsCurve -n "curveShape22" -p "curve22";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2856" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2856" -p "pPlane4Follicle2856";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.5625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve23" -p "pPlane4Follicle2856";
createNode nurbsCurve -n "curveShape23" -p "curve23";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2868" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2868" -p "pPlane4Follicle2868";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.6875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve24" -p "pPlane4Follicle2868";
createNode nurbsCurve -n "curveShape24" -p "curve24";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2880" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2880" -p "pPlane4Follicle2880";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.8125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve25" -p "pPlane4Follicle2880";
createNode nurbsCurve -n "curveShape25" -p "curve25";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle2893" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape2893" -p "pPlane4Follicle2893";
	setAttr -k off ".v";
	setAttr ".pu" 0.27777777777777779;
	setAttr ".pv" 0.9375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve26" -p "pPlane4Follicle2893";
createNode nurbsCurve -n "curveShape26" -p "curve26";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3906" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3906" -p "pPlane4Follicle3906";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.0625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve27" -p "pPlane4Follicle3906";
createNode nurbsCurve -n "curveShape27" -p "curve27";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3919" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3919" -p "pPlane4Follicle3919";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.1875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve28" -p "pPlane4Follicle3919";
createNode nurbsCurve -n "curveShape28" -p "curve28";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3931" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3931" -p "pPlane4Follicle3931";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.3125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve29" -p "pPlane4Follicle3931";
createNode nurbsCurve -n "curveShape29" -p "curve29";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3943" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3943" -p "pPlane4Follicle3943";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.4375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve30" -p "pPlane4Follicle3943";
createNode nurbsCurve -n "curveShape30" -p "curve30";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3956" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3956" -p "pPlane4Follicle3956";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.5625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve31" -p "pPlane4Follicle3956";
createNode nurbsCurve -n "curveShape31" -p "curve31";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3968" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3968" -p "pPlane4Follicle3968";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.6875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve32" -p "pPlane4Follicle3968";
createNode nurbsCurve -n "curveShape32" -p "curve32";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3980" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3980" -p "pPlane4Follicle3980";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.8125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve33" -p "pPlane4Follicle3980";
createNode nurbsCurve -n "curveShape33" -p "curve33";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle3993" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape3993" -p "pPlane4Follicle3993";
	setAttr -k off ".v";
	setAttr ".pu" 0.3888888888888889;
	setAttr ".pv" 0.9375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve34" -p "pPlane4Follicle3993";
createNode nurbsCurve -n "curveShape34" -p "curve34";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5006" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5006" -p "pPlane4Follicle5006";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.0625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve35" -p "pPlane4Follicle5006";
createNode nurbsCurve -n "curveShape35" -p "curve35";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5019" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5019" -p "pPlane4Follicle5019";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.1875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve36" -p "pPlane4Follicle5019";
createNode nurbsCurve -n "curveShape36" -p "curve36";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5031" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5031" -p "pPlane4Follicle5031";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.3125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve37" -p "pPlane4Follicle5031";
createNode nurbsCurve -n "curveShape37" -p "curve37";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5043" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5043" -p "pPlane4Follicle5043";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.4375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve38" -p "pPlane4Follicle5043";
createNode nurbsCurve -n "curveShape38" -p "curve38";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5056" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5056" -p "pPlane4Follicle5056";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.5625;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve39" -p "pPlane4Follicle5056";
createNode nurbsCurve -n "curveShape39" -p "curve39";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5068" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5068" -p "pPlane4Follicle5068";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.6875;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve40" -p "pPlane4Follicle5068";
createNode nurbsCurve -n "curveShape40" -p "curve40";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5080" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5080" -p "pPlane4Follicle5080";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.8125;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve41" -p "pPlane4Follicle5080";
createNode nurbsCurve -n "curveShape41" -p "curve41";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pPlane4Follicle5093" -p "hairSystem3Follicles";
createNode follicle -n "pPlane4FollicleShape5093" -p "pPlane4Follicle5093";
	setAttr -k off ".v";
	setAttr ".pu" 0.5;
	setAttr ".pv" 0.9375;
	setAttr -s 2 ".sts[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".cws[0:1]"  0 1 3 1 0.2 3;
	setAttr -s 2 ".ats[0:1]"  0 1 3 1 0.2 3;
	setAttr ".dgr" 1;
createNode transform -n "curve42" -p "pPlane4Follicle5093";
createNode nurbsCurve -n "curveShape42" -p "curve42";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".cc" -type "nurbsCurve" 
		1 1 0 no 3
		2 0 1
		2
		0 0 0
		0 0 1.5
		;
createNode transform -n "pfxHair3";
createNode pfxHair -n "pfxHairShape3" -p "pfxHair3";
	setAttr -k off ".v";
	setAttr ".dpc" 100;
	setAttr ".dam" no;
createNode lightLinker -n "lightLinker1";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
	setAttr ".crl" 4;
	setAttr -s 5 ".rlmi";
	setAttr ".rlmi[1]" 1;
	setAttr ".rlmi[3:5]" 2 3 4;
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
	setAttr ".rndr" no;
	setAttr -s 3 ".adjs";
	setAttr ".adjs[0].val" 1;
	setAttr ".adjs[1].val" 1;
	setAttr ".adjs[2].val" 1;
createNode polyPlane -n "polyPlane1";
	setAttr ".w" 11.612217880543952;
	setAttr ".h" 8.2895441014406472;
	setAttr ".cuv" 2;
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"Stereo\" -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels `;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n"
		+ "                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n"
		+ "                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n"
		+ "                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n"
		+ "                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n"
		+ "                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n"
		+ "                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n"
		+ "            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n"
		+ "            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n"
		+ "                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n"
		+ "                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n"
		+ "            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n"
		+ "            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n"
		+ "                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n"
		+ "                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n"
		+ "                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n"
		+ "            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n"
		+ "            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n"
		+ "                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n"
		+ "                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n"
		+ "            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n"
		+ "            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n"
		+ "                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n"
		+ "                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n"
		+ "            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n"
		+ "                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n"
		+ "                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n"
		+ "                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n"
		+ "                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n"
		+ "                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n"
		+ "                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n"
		+ "                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n"
		+ "                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n"
		+ "            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n"
		+ "                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n"
		+ "                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n"
		+ "\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"multiListerPanel\" (localizedPanelLabel(\"Multilister\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"multiListerPanel\" -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"devicePanel\" (localizedPanelLabel(\"Devices\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tdevicePanel -unParent -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tdevicePanel -edit -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"webBrowserPanel\" (localizedPanelLabel(\"Web Browser\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"webBrowserPanel\" -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 17 100 -ps 2 83 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n"
		+ "\t\t\t\t\t\"outlinerPanel\"\n\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 8192\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 8192\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 24 -ast 1 -aet 48 ";
	setAttr ".st" 6;
createNode script -n "liquidCleanUpNode";
	setAttr ".b" -type "string" "if ( `whatIs liquid` == \"Command\" ) liquidCreateScriptNode;";
	setAttr ".a" -type "string" "if ( `whatIs liquid` == \"Command\" ) liquidCleanUp;";
	setAttr ".st" 2;
createNode liquidGlobals -n "liquidGlobals";
	setAttr ".rc" -type "string" "perspShape";
	setAttr ".ddin[0]" -type "string" "$SCN.$LYR.$CAM.$F.$RND.bmp";
	setAttr ".ddim[0]" -type "string" "rgba";
	setAttr ".ddit[0]" -type "string" "it";
	setAttr ".ddbd[0]"  8;
	setAttr ".shdd" -type "string" "generatedShader";
	setAttr ".unt" yes;
	setAttr ".osg" yes;
	setAttr ".lbsx" 64;
	setAttr ".lbsy" 64;
	setAttr ".rdc" -type "string" "prman";
	setAttr ".prv" -type "string" "prman";
	setAttr ".lrs" -type "string" "E:/MyDocuments/maya/projects/default/rmantmp/.xml";
	setAttr ".lrf" -type "string" "E:/MyDocuments/maya/projects/default/rib/_perspShape.0001.rib";
	setAttr ".shi" -type "string" "sloinfo";
	setAttr ".shcp" -type "string" "shader";
	setAttr ".she" -type "string" "slo";
	setAttr ".mtx" -type "string" "txmake";
	setAttr ".vtx" -type "string" "sho";
	setAttr ".dsdn" -type "string" "deepshad";
	setAttr ".dsim" -type "string" "deepopacity";
	setAttr ".Photon" yes;
	setAttr ".ZBuffer" no;
	setAttr ".DepthMask" yes;
	setAttr ".Blackman_Harris" yes;
	setAttr ".Mitchell" yes;
	setAttr ".SeparableCatmull_Rom" yes;
	setAttr ".Blobbies" yes;
	setAttr ".Points" yes;
	setAttr ".Raytracing" yes;
	setAttr ".AdvancedVisibility" yes;
	setAttr ".rnd" -type "string" "renderman";
createNode liquidSurface -n "lambert2";
	addAttr -ci true -m -sn "assignedObjects" -ln "assignedObjects" -at "message";
	setAttr ".rms" -type "string" "lambert1";
	setAttr ".rml" -type "string" "E:/MyDocuments/maya/projects/default/generatedShader/lambert1.slo";
	setAttr ".rpr" -type "stringArray" 0  ;
	setAttr ".rdt" -type "stringArray" 0  ;
	setAttr ".rty" -type "stringArray" 0  ;
	setAttr ".rdf" -type "stringArray" 0  ;
	setAttr ".ras" -type "Int32Array" 0 ;
	setAttr ".rlc" -type "stringArray" 0  ;
	setAttr ".rmt" -type "stringArray" 1 "surface"  ;
	setAttr ".rio" -type "Int32Array" 0 ;
createNode polyPlane -n "polyPlane2";
	setAttr ".w" 4.5301038356538363;
	setAttr ".h" 4.5256233648231099;
	setAttr ".sw" 1;
	setAttr ".sh" 1;
	setAttr ".cuv" 2;
createNode renderLayer -n "layer1";
	setAttr ".do" 1;
createNode renderLayer -n "layer2";
	setAttr ".adjs[0].val" 0;
	setAttr ".do" 2;
createNode renderLayer -n "layer3";
	setAttr ".adjs[0].val" 1;
	setAttr ".do" 3;
createNode polyPlane -n "polyPlane3";
	setAttr ".w" 1.2544518748341931;
	setAttr ".h" 2.0535736775220248;
	setAttr ".sw" 1;
	setAttr ".sh" 1;
	setAttr ".cuv" 2;
createNode renderLayer -n "layer4";
	setAttr ".adjs[0].val" 1;
	setAttr ".do" 4;
createNode polyPlane -n "polyPlane4";
	setAttr ".w" 2.631375664397833;
	setAttr ".h" 4.8227927657607363;
	setAttr ".sw" 1;
	setAttr ".sh" 1;
	setAttr ".cuv" 2;
select -ne :time1;
	setAttr ".o" 1;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 3 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :lambert1;
	setAttr ".c" -type "float3" 0.898 0.53904247 0.13290401 ;
select -ne :initialShadingGroup;
	setAttr -s 4 ".dsm";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".ren" -type "string" "liquid";
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :defaultLightSet;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "layer2.ri" "pPlane1.rlio[0]";
connectAttr "polyPlane1.out" "pPlaneShape1.i";
connectAttr "lambert2.assignedObjects" "pPlaneShape1.liquidSurfaceShaderNode";
connectAttr "layer2.ri" "pointLight1.rlio[0]";
connectAttr "layer3.ri" "pointLight1.rlio[1]";
connectAttr "layer4.ri" "pointLight1.rlio[2]";
connectAttr "layer2.ri" "hairSystem1.rlio[0]";
connectAttr ":time1.o" "hairSystemShape1.cti";
connectAttr "pPlane1FollicleShape5050.oha" "hairSystemShape1.ih[0]";
connectAttr "layer2.ri" "hairSystem1Follicles.rlio[0]";
connectAttr "pPlane1FollicleShape5050.ot" "pPlane1Follicle5050.t" -l on;
connectAttr "pPlane1FollicleShape5050.or" "pPlane1Follicle5050.r" -l on;
connectAttr "pPlaneShape1.wm" "pPlane1FollicleShape5050.iwm";
connectAttr "pPlaneShape1.o" "pPlane1FollicleShape5050.inm";
connectAttr "curveShape1.ws" "pPlane1FollicleShape5050.sp";
connectAttr "layer2.ri" "pfxHair1.rlio[0]";
connectAttr "hairSystemShape1.orh" "pfxHairShape1.rhs";
connectAttr "layer2.ri" "pPlane2.rlio[0]";
connectAttr "polyPlane2.out" "pPlaneShape2.i";
connectAttr "layer1.ri" "locator1.rlio[0]";
connectAttr "layer1.ri" "locator2.rlio[0]";
connectAttr "layer1.ri" "locator3.rlio[0]";
connectAttr "layer1.ri" "locator4.rlio[0]";
connectAttr "layer3.ri" "pPlane3.rlio[0]";
connectAttr "polyPlane3.out" "pPlaneShape3.i";
connectAttr "layer3.ri" "hairSystem2.rlio[0]";
connectAttr ":time1.o" "hairSystemShape2.cti";
connectAttr "pPlane3FollicleShape5050.oha" "hairSystemShape2.ih[0]";
connectAttr "layer3.ri" "hairSystem2Follicles.rlio[0]";
connectAttr "layer3.ri" "pPlane3Follicle5050.rlio[0]";
connectAttr "pPlane3FollicleShape5050.ot" "pPlane3Follicle5050.t" -l on;
connectAttr "pPlane3FollicleShape5050.or" "pPlane3Follicle5050.r" -l on;
connectAttr "pPlaneShape3.wm" "pPlane3FollicleShape5050.iwm";
connectAttr "pPlaneShape3.o" "pPlane3FollicleShape5050.inm";
connectAttr "curveShape2.ws" "pPlane3FollicleShape5050.sp";
connectAttr "layer3.ri" "curve2.rlio[0]";
connectAttr "layer3.ri" "pfxHair2.rlio[0]";
connectAttr "hairSystemShape2.orh" "pfxHairShape2.rhs";
connectAttr "layer4.ri" "pPlane4.rlio[0]";
connectAttr "polyPlane4.out" "pPlaneShape4.i";
connectAttr "layer4.ri" "hairSystem3.rlio[0]";
connectAttr ":time1.o" "hairSystemShape3.cti";
connectAttr "pPlane4FollicleShape606.oha" "hairSystemShape3.ih[0]";
connectAttr "pPlane4FollicleShape619.oha" "hairSystemShape3.ih[1]";
connectAttr "pPlane4FollicleShape631.oha" "hairSystemShape3.ih[2]";
connectAttr "pPlane4FollicleShape643.oha" "hairSystemShape3.ih[3]";
connectAttr "pPlane4FollicleShape656.oha" "hairSystemShape3.ih[4]";
connectAttr "pPlane4FollicleShape668.oha" "hairSystemShape3.ih[5]";
connectAttr "pPlane4FollicleShape680.oha" "hairSystemShape3.ih[6]";
connectAttr "pPlane4FollicleShape693.oha" "hairSystemShape3.ih[7]";
connectAttr "pPlane4FollicleShape1706.oha" "hairSystemShape3.ih[8]";
connectAttr "pPlane4FollicleShape1719.oha" "hairSystemShape3.ih[9]";
connectAttr "pPlane4FollicleShape1731.oha" "hairSystemShape3.ih[10]";
connectAttr "pPlane4FollicleShape1743.oha" "hairSystemShape3.ih[11]";
connectAttr "pPlane4FollicleShape1756.oha" "hairSystemShape3.ih[12]";
connectAttr "pPlane4FollicleShape1768.oha" "hairSystemShape3.ih[13]";
connectAttr "pPlane4FollicleShape1780.oha" "hairSystemShape3.ih[14]";
connectAttr "pPlane4FollicleShape1793.oha" "hairSystemShape3.ih[15]";
connectAttr "pPlane4FollicleShape2806.oha" "hairSystemShape3.ih[16]";
connectAttr "pPlane4FollicleShape2819.oha" "hairSystemShape3.ih[17]";
connectAttr "pPlane4FollicleShape2831.oha" "hairSystemShape3.ih[18]";
connectAttr "pPlane4FollicleShape2843.oha" "hairSystemShape3.ih[19]";
connectAttr "pPlane4FollicleShape2856.oha" "hairSystemShape3.ih[20]";
connectAttr "pPlane4FollicleShape2868.oha" "hairSystemShape3.ih[21]";
connectAttr "pPlane4FollicleShape2880.oha" "hairSystemShape3.ih[22]";
connectAttr "pPlane4FollicleShape2893.oha" "hairSystemShape3.ih[23]";
connectAttr "pPlane4FollicleShape3906.oha" "hairSystemShape3.ih[24]";
connectAttr "pPlane4FollicleShape3919.oha" "hairSystemShape3.ih[25]";
connectAttr "pPlane4FollicleShape3931.oha" "hairSystemShape3.ih[26]";
connectAttr "pPlane4FollicleShape3943.oha" "hairSystemShape3.ih[27]";
connectAttr "pPlane4FollicleShape3956.oha" "hairSystemShape3.ih[28]";
connectAttr "pPlane4FollicleShape3968.oha" "hairSystemShape3.ih[29]";
connectAttr "pPlane4FollicleShape3980.oha" "hairSystemShape3.ih[30]";
connectAttr "pPlane4FollicleShape3993.oha" "hairSystemShape3.ih[31]";
connectAttr "pPlane4FollicleShape5006.oha" "hairSystemShape3.ih[32]";
connectAttr "pPlane4FollicleShape5019.oha" "hairSystemShape3.ih[33]";
connectAttr "pPlane4FollicleShape5031.oha" "hairSystemShape3.ih[34]";
connectAttr "pPlane4FollicleShape5043.oha" "hairSystemShape3.ih[35]";
connectAttr "pPlane4FollicleShape5056.oha" "hairSystemShape3.ih[36]";
connectAttr "pPlane4FollicleShape5068.oha" "hairSystemShape3.ih[37]";
connectAttr "pPlane4FollicleShape5080.oha" "hairSystemShape3.ih[38]";
connectAttr "pPlane4FollicleShape5093.oha" "hairSystemShape3.ih[39]";
connectAttr "layer4.ri" "hairSystem3Follicles.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle606.rlio[0]";
connectAttr "pPlane4FollicleShape606.ot" "pPlane4Follicle606.t" -l on;
connectAttr "pPlane4FollicleShape606.or" "pPlane4Follicle606.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape606.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape606.inm";
connectAttr "curveShape3.ws" "pPlane4FollicleShape606.sp";
connectAttr "layer4.ri" "curve3.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle619.rlio[0]";
connectAttr "pPlane4FollicleShape619.ot" "pPlane4Follicle619.t" -l on;
connectAttr "pPlane4FollicleShape619.or" "pPlane4Follicle619.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape619.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape619.inm";
connectAttr "curveShape4.ws" "pPlane4FollicleShape619.sp";
connectAttr "layer4.ri" "curve4.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle631.rlio[0]";
connectAttr "pPlane4FollicleShape631.ot" "pPlane4Follicle631.t" -l on;
connectAttr "pPlane4FollicleShape631.or" "pPlane4Follicle631.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape631.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape631.inm";
connectAttr "curveShape5.ws" "pPlane4FollicleShape631.sp";
connectAttr "layer4.ri" "curve5.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle643.rlio[0]";
connectAttr "pPlane4FollicleShape643.ot" "pPlane4Follicle643.t" -l on;
connectAttr "pPlane4FollicleShape643.or" "pPlane4Follicle643.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape643.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape643.inm";
connectAttr "curveShape6.ws" "pPlane4FollicleShape643.sp";
connectAttr "layer4.ri" "curve6.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle656.rlio[0]";
connectAttr "pPlane4FollicleShape656.ot" "pPlane4Follicle656.t" -l on;
connectAttr "pPlane4FollicleShape656.or" "pPlane4Follicle656.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape656.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape656.inm";
connectAttr "curveShape7.ws" "pPlane4FollicleShape656.sp";
connectAttr "layer4.ri" "curve7.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle668.rlio[0]";
connectAttr "pPlane4FollicleShape668.ot" "pPlane4Follicle668.t" -l on;
connectAttr "pPlane4FollicleShape668.or" "pPlane4Follicle668.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape668.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape668.inm";
connectAttr "curveShape8.ws" "pPlane4FollicleShape668.sp";
connectAttr "layer4.ri" "curve8.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle680.rlio[0]";
connectAttr "pPlane4FollicleShape680.ot" "pPlane4Follicle680.t" -l on;
connectAttr "pPlane4FollicleShape680.or" "pPlane4Follicle680.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape680.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape680.inm";
connectAttr "curveShape9.ws" "pPlane4FollicleShape680.sp";
connectAttr "layer4.ri" "curve9.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle693.rlio[0]";
connectAttr "pPlane4FollicleShape693.ot" "pPlane4Follicle693.t" -l on;
connectAttr "pPlane4FollicleShape693.or" "pPlane4Follicle693.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape693.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape693.inm";
connectAttr "curveShape10.ws" "pPlane4FollicleShape693.sp";
connectAttr "layer4.ri" "curve10.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1706.rlio[0]";
connectAttr "pPlane4FollicleShape1706.ot" "pPlane4Follicle1706.t" -l on;
connectAttr "pPlane4FollicleShape1706.or" "pPlane4Follicle1706.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1706.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1706.inm";
connectAttr "curveShape11.ws" "pPlane4FollicleShape1706.sp";
connectAttr "layer4.ri" "curve11.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1719.rlio[0]";
connectAttr "pPlane4FollicleShape1719.ot" "pPlane4Follicle1719.t" -l on;
connectAttr "pPlane4FollicleShape1719.or" "pPlane4Follicle1719.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1719.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1719.inm";
connectAttr "curveShape12.ws" "pPlane4FollicleShape1719.sp";
connectAttr "layer4.ri" "curve12.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1731.rlio[0]";
connectAttr "pPlane4FollicleShape1731.ot" "pPlane4Follicle1731.t" -l on;
connectAttr "pPlane4FollicleShape1731.or" "pPlane4Follicle1731.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1731.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1731.inm";
connectAttr "curveShape13.ws" "pPlane4FollicleShape1731.sp";
connectAttr "layer4.ri" "curve13.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1743.rlio[0]";
connectAttr "pPlane4FollicleShape1743.ot" "pPlane4Follicle1743.t" -l on;
connectAttr "pPlane4FollicleShape1743.or" "pPlane4Follicle1743.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1743.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1743.inm";
connectAttr "curveShape14.ws" "pPlane4FollicleShape1743.sp";
connectAttr "layer4.ri" "curve14.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1756.rlio[0]";
connectAttr "pPlane4FollicleShape1756.ot" "pPlane4Follicle1756.t" -l on;
connectAttr "pPlane4FollicleShape1756.or" "pPlane4Follicle1756.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1756.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1756.inm";
connectAttr "curveShape15.ws" "pPlane4FollicleShape1756.sp";
connectAttr "layer4.ri" "curve15.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1768.rlio[0]";
connectAttr "pPlane4FollicleShape1768.ot" "pPlane4Follicle1768.t" -l on;
connectAttr "pPlane4FollicleShape1768.or" "pPlane4Follicle1768.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1768.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1768.inm";
connectAttr "curveShape16.ws" "pPlane4FollicleShape1768.sp";
connectAttr "layer4.ri" "curve16.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1780.rlio[0]";
connectAttr "pPlane4FollicleShape1780.ot" "pPlane4Follicle1780.t" -l on;
connectAttr "pPlane4FollicleShape1780.or" "pPlane4Follicle1780.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1780.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1780.inm";
connectAttr "curveShape17.ws" "pPlane4FollicleShape1780.sp";
connectAttr "layer4.ri" "curve17.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle1793.rlio[0]";
connectAttr "pPlane4FollicleShape1793.ot" "pPlane4Follicle1793.t" -l on;
connectAttr "pPlane4FollicleShape1793.or" "pPlane4Follicle1793.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape1793.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape1793.inm";
connectAttr "curveShape18.ws" "pPlane4FollicleShape1793.sp";
connectAttr "layer4.ri" "curve18.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2806.rlio[0]";
connectAttr "pPlane4FollicleShape2806.ot" "pPlane4Follicle2806.t" -l on;
connectAttr "pPlane4FollicleShape2806.or" "pPlane4Follicle2806.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2806.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2806.inm";
connectAttr "curveShape19.ws" "pPlane4FollicleShape2806.sp";
connectAttr "layer4.ri" "curve19.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2819.rlio[0]";
connectAttr "pPlane4FollicleShape2819.ot" "pPlane4Follicle2819.t" -l on;
connectAttr "pPlane4FollicleShape2819.or" "pPlane4Follicle2819.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2819.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2819.inm";
connectAttr "curveShape20.ws" "pPlane4FollicleShape2819.sp";
connectAttr "layer4.ri" "curve20.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2831.rlio[0]";
connectAttr "pPlane4FollicleShape2831.ot" "pPlane4Follicle2831.t" -l on;
connectAttr "pPlane4FollicleShape2831.or" "pPlane4Follicle2831.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2831.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2831.inm";
connectAttr "curveShape21.ws" "pPlane4FollicleShape2831.sp";
connectAttr "layer4.ri" "curve21.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2843.rlio[0]";
connectAttr "pPlane4FollicleShape2843.ot" "pPlane4Follicle2843.t" -l on;
connectAttr "pPlane4FollicleShape2843.or" "pPlane4Follicle2843.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2843.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2843.inm";
connectAttr "curveShape22.ws" "pPlane4FollicleShape2843.sp";
connectAttr "layer4.ri" "curve22.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2856.rlio[0]";
connectAttr "pPlane4FollicleShape2856.ot" "pPlane4Follicle2856.t" -l on;
connectAttr "pPlane4FollicleShape2856.or" "pPlane4Follicle2856.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2856.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2856.inm";
connectAttr "curveShape23.ws" "pPlane4FollicleShape2856.sp";
connectAttr "layer4.ri" "curve23.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2868.rlio[0]";
connectAttr "pPlane4FollicleShape2868.ot" "pPlane4Follicle2868.t" -l on;
connectAttr "pPlane4FollicleShape2868.or" "pPlane4Follicle2868.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2868.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2868.inm";
connectAttr "curveShape24.ws" "pPlane4FollicleShape2868.sp";
connectAttr "layer4.ri" "curve24.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2880.rlio[0]";
connectAttr "pPlane4FollicleShape2880.ot" "pPlane4Follicle2880.t" -l on;
connectAttr "pPlane4FollicleShape2880.or" "pPlane4Follicle2880.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2880.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2880.inm";
connectAttr "curveShape25.ws" "pPlane4FollicleShape2880.sp";
connectAttr "layer4.ri" "curve25.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle2893.rlio[0]";
connectAttr "pPlane4FollicleShape2893.ot" "pPlane4Follicle2893.t" -l on;
connectAttr "pPlane4FollicleShape2893.or" "pPlane4Follicle2893.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape2893.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape2893.inm";
connectAttr "curveShape26.ws" "pPlane4FollicleShape2893.sp";
connectAttr "layer4.ri" "curve26.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3906.rlio[0]";
connectAttr "pPlane4FollicleShape3906.ot" "pPlane4Follicle3906.t" -l on;
connectAttr "pPlane4FollicleShape3906.or" "pPlane4Follicle3906.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3906.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3906.inm";
connectAttr "curveShape27.ws" "pPlane4FollicleShape3906.sp";
connectAttr "layer4.ri" "curve27.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3919.rlio[0]";
connectAttr "pPlane4FollicleShape3919.ot" "pPlane4Follicle3919.t" -l on;
connectAttr "pPlane4FollicleShape3919.or" "pPlane4Follicle3919.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3919.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3919.inm";
connectAttr "curveShape28.ws" "pPlane4FollicleShape3919.sp";
connectAttr "layer4.ri" "curve28.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3931.rlio[0]";
connectAttr "pPlane4FollicleShape3931.ot" "pPlane4Follicle3931.t" -l on;
connectAttr "pPlane4FollicleShape3931.or" "pPlane4Follicle3931.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3931.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3931.inm";
connectAttr "curveShape29.ws" "pPlane4FollicleShape3931.sp";
connectAttr "layer4.ri" "curve29.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3943.rlio[0]";
connectAttr "pPlane4FollicleShape3943.ot" "pPlane4Follicle3943.t" -l on;
connectAttr "pPlane4FollicleShape3943.or" "pPlane4Follicle3943.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3943.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3943.inm";
connectAttr "curveShape30.ws" "pPlane4FollicleShape3943.sp";
connectAttr "layer4.ri" "curve30.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3956.rlio[0]";
connectAttr "pPlane4FollicleShape3956.ot" "pPlane4Follicle3956.t" -l on;
connectAttr "pPlane4FollicleShape3956.or" "pPlane4Follicle3956.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3956.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3956.inm";
connectAttr "curveShape31.ws" "pPlane4FollicleShape3956.sp";
connectAttr "layer4.ri" "curve31.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3968.rlio[0]";
connectAttr "pPlane4FollicleShape3968.ot" "pPlane4Follicle3968.t" -l on;
connectAttr "pPlane4FollicleShape3968.or" "pPlane4Follicle3968.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3968.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3968.inm";
connectAttr "curveShape32.ws" "pPlane4FollicleShape3968.sp";
connectAttr "layer4.ri" "curve32.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3980.rlio[0]";
connectAttr "pPlane4FollicleShape3980.ot" "pPlane4Follicle3980.t" -l on;
connectAttr "pPlane4FollicleShape3980.or" "pPlane4Follicle3980.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3980.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3980.inm";
connectAttr "curveShape33.ws" "pPlane4FollicleShape3980.sp";
connectAttr "layer4.ri" "curve33.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle3993.rlio[0]";
connectAttr "pPlane4FollicleShape3993.ot" "pPlane4Follicle3993.t" -l on;
connectAttr "pPlane4FollicleShape3993.or" "pPlane4Follicle3993.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape3993.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape3993.inm";
connectAttr "curveShape34.ws" "pPlane4FollicleShape3993.sp";
connectAttr "layer4.ri" "curve34.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5006.rlio[0]";
connectAttr "pPlane4FollicleShape5006.ot" "pPlane4Follicle5006.t" -l on;
connectAttr "pPlane4FollicleShape5006.or" "pPlane4Follicle5006.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5006.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5006.inm";
connectAttr "curveShape35.ws" "pPlane4FollicleShape5006.sp";
connectAttr "layer4.ri" "curve35.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5019.rlio[0]";
connectAttr "pPlane4FollicleShape5019.ot" "pPlane4Follicle5019.t" -l on;
connectAttr "pPlane4FollicleShape5019.or" "pPlane4Follicle5019.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5019.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5019.inm";
connectAttr "curveShape36.ws" "pPlane4FollicleShape5019.sp";
connectAttr "layer4.ri" "curve36.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5031.rlio[0]";
connectAttr "pPlane4FollicleShape5031.ot" "pPlane4Follicle5031.t" -l on;
connectAttr "pPlane4FollicleShape5031.or" "pPlane4Follicle5031.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5031.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5031.inm";
connectAttr "curveShape37.ws" "pPlane4FollicleShape5031.sp";
connectAttr "layer4.ri" "curve37.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5043.rlio[0]";
connectAttr "pPlane4FollicleShape5043.ot" "pPlane4Follicle5043.t" -l on;
connectAttr "pPlane4FollicleShape5043.or" "pPlane4Follicle5043.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5043.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5043.inm";
connectAttr "curveShape38.ws" "pPlane4FollicleShape5043.sp";
connectAttr "layer4.ri" "curve38.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5056.rlio[0]";
connectAttr "pPlane4FollicleShape5056.ot" "pPlane4Follicle5056.t" -l on;
connectAttr "pPlane4FollicleShape5056.or" "pPlane4Follicle5056.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5056.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5056.inm";
connectAttr "curveShape39.ws" "pPlane4FollicleShape5056.sp";
connectAttr "layer4.ri" "curve39.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5068.rlio[0]";
connectAttr "pPlane4FollicleShape5068.ot" "pPlane4Follicle5068.t" -l on;
connectAttr "pPlane4FollicleShape5068.or" "pPlane4Follicle5068.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5068.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5068.inm";
connectAttr "curveShape40.ws" "pPlane4FollicleShape5068.sp";
connectAttr "layer4.ri" "curve40.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5080.rlio[0]";
connectAttr "pPlane4FollicleShape5080.ot" "pPlane4Follicle5080.t" -l on;
connectAttr "pPlane4FollicleShape5080.or" "pPlane4Follicle5080.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5080.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5080.inm";
connectAttr "curveShape41.ws" "pPlane4FollicleShape5080.sp";
connectAttr "layer4.ri" "curve41.rlio[0]";
connectAttr "layer4.ri" "pPlane4Follicle5093.rlio[0]";
connectAttr "pPlane4FollicleShape5093.ot" "pPlane4Follicle5093.t" -l on;
connectAttr "pPlane4FollicleShape5093.or" "pPlane4Follicle5093.r" -l on;
connectAttr "pPlaneShape4.wm" "pPlane4FollicleShape5093.iwm";
connectAttr "pPlaneShape4.o" "pPlane4FollicleShape5093.inm";
connectAttr "curveShape42.ws" "pPlane4FollicleShape5093.sp";
connectAttr "layer4.ri" "curve42.rlio[0]";
connectAttr "layer4.ri" "pfxHair3.rlio[0]";
connectAttr "hairSystemShape3.orh" "pfxHairShape3.rhs";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "pPlane2.v" "defaultRenderLayer.adjs[0].plg";
connectAttr "pfxHair2.v" "defaultRenderLayer.adjs[1].plg";
connectAttr "pfxHair3.v" "defaultRenderLayer.adjs[2].plg";
connectAttr "renderLayerManager.rlmi[1]" "layer1.rlid";
connectAttr "renderLayerManager.rlmi[3]" "layer2.rlid";
connectAttr "pPlane2.v" "layer2.adjs[0].plg";
connectAttr "renderLayerManager.rlmi[4]" "layer3.rlid";
connectAttr "pfxHair2.v" "layer3.adjs[0].plg";
connectAttr "renderLayerManager.rlmi[5]" "layer4.rlid";
connectAttr "pfxHair3.v" "layer4.adjs[0].plg";
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "pointLightShape1.ltd" ":lightList1.l" -na;
connectAttr "pPlaneShape1.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pPlaneShape2.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pPlaneShape3.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pPlaneShape4.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pointLight1.iog" ":defaultLightSet.dsm" -na;
// End of test_pfxHair.ma
