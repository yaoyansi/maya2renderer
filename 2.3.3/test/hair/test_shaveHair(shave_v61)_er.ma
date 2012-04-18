//Maya ASCII 2009 scene
//Name: test_shaveHair(shave_v61)_er.ma
//Last modified: Thu, Apr 19, 2012 12:32:16 AM
//Codeset: 936
requires maya "2009";
requires "liquid_2009x32d" "2.3.5 (buildtime=23:54:27.50)";
requires "stereoCamera" "10.0";
requires "shaveNode" "1.1";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2009";
fileInfo "version" "2009";
fileInfo "cutIdentifier" "200809110030-734661";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -3.1195282267957474 2.4717133442904822 -0.99973011350878749 ;
	setAttr ".r" -type "double3" -12.93835272964383 246.99999999996876 0 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 3.5045410123389193;
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
createNode transform -n "pointLight1";
	setAttr ".t" -type "double3" 0 6.9342733301266515 0 ;
createNode pointLight -n "pointLightShape1" -p "pointLight1";
	setAttr -k off ".v";
	setAttr ".us" no;
createNode transform -n "shaveDisplayGroup";
createNode transform -n "shavedisplay" -p "shaveDisplayGroup";
	setAttr -l on ".t";
	setAttr -l on ".r";
	setAttr -l on ".s";
createNode mesh -n "shaveDisplayShape" -p "shavedisplay";
	setAttr -k off ".v";
	setAttr ".tmp" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "shavedisplay1" -p "shaveDisplayGroup";
	setAttr -l on ".t";
	setAttr -l on ".r";
	setAttr -l on ".s";
createNode mesh -n "shaveDisplayShape" -p "shavedisplay1";
	setAttr -k off ".v";
	setAttr ".tmp" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "shavedisplay2" -p "shaveDisplayGroup";
	setAttr -l on ".t";
	setAttr -l on ".r";
	setAttr -l on ".s";
createNode mesh -n "shaveDisplayShape" -p "shavedisplay2";
	setAttr -k off ".v";
	setAttr ".tmp" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "shavedisplay3" -p "shaveDisplayGroup";
	setAttr -l on ".t";
	setAttr -l on ".r";
	setAttr -l on ".s";
createNode mesh -n "shaveDisplayShape" -p "shavedisplay3";
	setAttr -k off ".v";
	setAttr ".tmp" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "shavedisplay4" -p "shaveDisplayGroup";
	setAttr -l on ".t";
	setAttr -l on ".r";
	setAttr -l on ".s";
createNode mesh -n "shaveDisplayShape" -p "shavedisplay4";
	setAttr -k off ".v";
	setAttr ".tmp" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "pPlane8";
	setAttr ".t" -type "double3" 1.4372149893088204 0 1.0539242284454948 ;
createNode mesh -n "pPlaneShape8" -p "pPlane8";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "shaveHair6";
createNode shaveHair -n "shaveHairShape6" -p "shaveHair6";
	setAttr ".cch" no;
	setAttr ".ihi" 2;
	setAttr ".nds" 0;
	setAttr -k off ".v" yes;
	setAttr ".io" no;
	setAttr ".tmp" no;
	setAttr ".gh" no;
	setAttr ".uoc" no;
	setAttr ".oc" 0;
	setAttr ".ovdt" 0;
	setAttr ".ovlod" 0;
	setAttr ".ovs" yes;
	setAttr ".ovt" yes;
	setAttr ".ovp" yes;
	setAttr ".ove" no;
	setAttr ".ovv" yes;
	setAttr ".ovc" 0;
	setAttr ".lodv" yes;
	setAttr ".rlid" 0;
	setAttr ".rndr" yes;
	setAttr ".lovc" 0;
	setAttr ".gc" 0;
	setAttr ".gpr" 3;
	setAttr ".gps" 3;
	setAttr ".gss" 1;
	setAttr ".grs" 0;
	setAttr ".gre" 100;
	setAttr ".rt" 0;
	setAttr ".rv" no;
	setAttr ".vf" 1;
	setAttr ".mb" yes;
	setAttr ".vir" no;
	setAttr ".vif" no;
	setAttr ".csh" yes;
	setAttr ".rcsh" yes;
	setAttr ".vbo" no;
	setAttr ".mvs" 1;
	setAttr ".gao" no;
	setAttr ".gal" 1;
	setAttr ".sso" no;
	setAttr ".ssa" 1;
	setAttr ".msa" 1;
	setAttr ".vso" no;
	setAttr ".vss" 1;
	setAttr ".dej" no;
	setAttr ".iss" no;
	setAttr ".vis" yes;
	setAttr ".tw" no;
	setAttr ".rtw" yes;
	setAttr ".pv" -type "double2" 0 0 ;
	setAttr ".di" no;
	setAttr ".dcol" no;
	setAttr ".dcc" -type "string" "color";
	setAttr ".ih" no;
	setAttr ".ds" yes;
	setAttr ".op" no;
	setAttr ".smo" yes;
	setAttr ".bbs" -type "float3" 1.5 1.5 1.5 ;
	setAttr ".fbda" yes;
	setAttr ".dsr" 6;
	setAttr ".xsr" 5;
	setAttr ".fth" 0;
	setAttr ".nat" 30;
	setAttr ".dhe" no;
	setAttr ".disabled" no;
	setAttr ".dspyas" 1;
	setAttr ".dg" no;
	setAttr ".dsl" 6;
	setAttr ".htc" -type "float3" 0 0 0 ;
	setAttr ".act" yes;
	setAttr ".mhtc" -type "float3" 0 0 0 ;
	setAttr ".nbi" yes;
	setAttr ".nv" 2;
	setAttr ".sv" -type "string" "5.0v61";
	setAttr ".ogsh" yes;
	setAttr ".rbs" -type "string" "#ShapeNode rib stuff";
	setAttr ".rhtc" -type "float3" 0 0 0 ;
	setAttr ".rd" 0;
	setAttr ".BSD" -type "blindShaveData" 5567 74611066 33554432 100663296 0 16777216 0 -754974720 4095909 -1115684864 12598071
 0 0 -754974720 4095909 -1124073472 -4179145 -738197505 1446936485 -1170374224 -4179145
 -738197505 1446936485 -1203895888 -4179145 -738197505 -2126610523 -1254210936 -4179145 -738197505 1446936485
 -1304526416 -4179145 -738197505 1816035237 -1338072548 -4179145 -738197505 -2109833307 -1388395896 -4179145
 -738197505 -1740734555 -1438719244 -4179145 -738197505 1463713701 -1472265808 -4179145 -738197505 1648263077
 -1522593306 -4179145 -738197505 1832812453 -1572920804 -4179145 -738197505 2017361829 -1606471086 -4179145
 -738197505 -2093056091 -1656798584 -4179145 -738197505 -1908506715 -1707126082 -4179145 -738197505 -1723957339
 -1740676364 -4179145 16777215 16777216 16777216 1275068416 4204540 -1115684864 12598071 0
 0 1275068416 4204540 -1124073472 -4179145 1291845631 1447045116 -1170374224 -4179145 1291845631
 1447045116 -1203895888 -4179145 1291845631 -2126501892 -1254210936 -4179145 1291845631 1447045116 -1304526416
 -4179145 1291845631 1816143868 -1338072548 -4179145 1291845631 -2109724676 -1388395896 -4179145 1291845631
 -1740625924 -1438719244 -4179145 1291845631 1463822332 -1472265808 -4179145 1291845631 1648371708 -1522593306
 -4179145 1291845631 1832921084 -1572920804 -4179145 1291845631 2017470460 -1606471086 -4179145 1291845631
 -2092947460 -1656798584 -4179145 1291845631 -1908398084 -1707126082 -4179145 1291845631 -1723848708 -1740676364
 -4179145 16777215 16777216 33554432 -754974720 4095909 117440512 4149571 0 0
 -754974720 4095909 117440512 -12627645 -738197505 1446936485 306020784 -12627645 -738197505 1446936485
 473825712 -12627645 -738197505 -2126610523 658391688 -12627645 -738197505 1446936485 826180016 -12627645
 -738197505 1816035237 1010737692 -12627645 -738197505 -2109833307 1195295368 -12627645 -738197505 -1740734555
 1363075828 -12627645 -738197505 1463713701 1547633072 -12627645 -738197505 1648263077 1732186598 -12627645
 -738197505 1832812453 1899962908 -12627645 -738197505 2017361829 2084516434 -12627645 -738197505 -2093056091
 -2042674552 -12627645 -738197505 -1908506715 -1858121026 -12627645 -738197505 -1723957339 -1673567500 -12627645
 16777215 16777216 50331648 1275068416 4204540 117440512 4149571 0 0 1275068416
 4204540 117440512 -12627645 1291845631 1447045116 306020784 -12627645 1291845631 1447045116 473825712
 -12627645 1291845631 -2126501892 658391688 -12627645 1291845631 1447045116 826180016 -12627645 1291845631
 1816143868 1010737692 -12627645 1291845631 -2109724676 1195295368 -12627645 1291845631 -1740625924 1363075828
 -12627645 1291845631 1463822332 1547633072 -12627645 1291845631 1648371708 1732186598 -12627645 1291845631
 1832921084 1899962908 -12627645 1291845631 2017470460 2084516434 -12627645 1291845631 -2092947460 -2042674552
 -12627645 1291845631 -1908398084 -1858121026 -12627645 1291845631 -1723848708 -1673567500 -12627645 67108863
 16777216 0 33554432 50331648 0 0 0 50331648 0 50331648
 100663296 0 1715566592 4413030 0 1715582976 960456294 4049076 4145152 -851492864
 4115660 4376576 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576
 4376576 1547880448 4145807 4161536 -851355648 4383948 0 1715582976 960456294 4049076
 -1707130880 4151705 4161536 4376576 4366336 4348928 4268032 4386816 4363776 4328448
 0 4376576 4366336 339888128 4147118 4161536 -851419136 4383948 0 1715582976
 960456294 4049076 -1707130880 4151705 4161536 4376576 4366336 4348928 4268032 4386816
 4363776 4328448 0 4376576 4366336 -331200512 4077649 4161536 -851419136 4383948
 0 1715582976 960456294 4049076 -1707130880 4151705 4161536 4376576 4366336 4348928
 4268032 4386816 4363776 4328448 4235264 4376576 4366336 -331200512 4077649 4161536
 1715615744 4413030 0 1715519488 960456294 4049076 4145152 4145152 4161536 4376576
 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576 4376576 1547880448
 4145807 255819776 251658240 0 33554432 0 33554432 0 33554432 0
 33554432 0 33554432 0 33554432 0 33554432 0 33554432 0
 33554432 0 33554432 0 33554432 0 33554432 0 33554432 0
 33554432 0 33554432 16777216 67108864 1744830464 7498081 0 0 0
 0 0 0 0 0 0 0 4268032 0 503316480
 16777216 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 20938752 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536
 4161536 1715566592 4413030 0 1715582976 960456294 4049076 4145152 -851492864 4115660
 4376576 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576 4376576
 1547880448 4145807 4161536 0 0 4391424 0 0 0 0
 0 -851355648 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 0 4376576 4366336
 339888128 4147118 4161536 0 0 4268032 0 0 0 0
 0 -851419136 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 0 4376576 4366336
 -331200512 4077649 4161536 0 0 4268032 0 0 0 0
 0 -851419136 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 4235264 4376576 4366336
 -331200512 4077649 4161536 0 4268032 0 0 0 0 0
 0 1715615744 4413030 0 1715519488 960456294 4049076 4145152 4145152 4161536
 4376576 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576 4376576
 1547880448 4145807 4161536 0 0 4391424 0 0 0 0
 16777216 -1811939328 16777233 0 16777216 0 16777216 0 16777216 0
 0 1715566592 4413030 0 1715582976 960456294 4049076 4145152 -851492864 4115660
 4376576 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576 4376576
 1547880448 4145807 4161536 0 0 4391424 0 0 0 0
 0 -851355648 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 0 4376576 4366336
 339888128 4147118 4161536 0 0 4268032 0 0 0 0
 0 -851419136 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 0 4376576 4366336
 -331200512 4077649 4161536 0 0 4268032 0 0 0 0
 0 -851419136 4383948 0 1715582976 960456294 4049076 -1707130880 4151705 4161536
 4376576 4366336 4348928 4268032 4386816 4363776 4328448 4235264 4376576 4366336
 -331200512 4077649 4161536 0 4268032 0 0 0 0 0
 0 1715615744 4413030 0 1715519488 960456294 4049076 4145152 4145152 4161536
 4376576 4376576 4376576 4321280 4386816 4386816 4386816 0 4376576 4376576
 1547880448 4145807 4161536 0 0 4391424 0 0 0 0
 0 20938752 16777216 16777216 16777216 16777216 67108864 0 16777216 50331648
 33554432 0 67108864 0 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536 4161536
 4161536 4161536 4161536 1715437568 1715689062 4413030 0 0 4306944 -851331072
 4115660 0 0 -851294208 -851254068 4383948 0 0 4306944 4306944
 0 0 0 -851294208 -851254068 4383948 0 0 4306944 4306944
 0 0 0 -851294208 -851254068 4383948 0 0 4306944 4306944
 0 0 0 1715619840 1715689062 4413030 0 0 4306944 -851331072
 4115660 0 0 675432448 16777216 0 4161536 4161536 4161536 20938752
 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536 20938752
 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536 20938752
 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536 20938752
 0 4161536 4161536 4161536 20938752 0 4161536 4161536 4161536 20938752
 0 4161536 4161536 4161536 4161536 0 4161536 0 0 4161536
 0 0 4161536 0 0 4161536 0 0 4161536 0
 16777216 0 0 0 0 0 0 0 16777216 134217728
 167772160 167772160 419430400 838860800 0 0 0 0 0 0
 0 0 -754974720 4095909 -1124073472 -742376649 1446936485 -1170374224 -742376649 1446936485
 -1203895888 -742376649 -2126610523 -1254210936 -742376649 1446936485 -1304526416 -742376649 1816035237 -1338072548
 -742376649 -2109833307 -1388395896 -742376649 -1740734555 -1438719244 -742376649 1463713701 -1472265808 -742376649
 1648263077 -1522593306 -742376649 1832812453 -1572920804 -742376649 2017361829 -1606471086 -742376649 -2093056091
 -1656798584 -742376649 -1908506715 -1707126082 -742376649 -1723957339 -1740676364 1287666487 4204540 -1124073472
 1287666487 1447045116 -1170374224 1287666487 1447045116 -1203895888 1287666487 -2126501892 -1254210936 1287666487
 1447045116 -1304526416 1287666487 1816143868 -1338072548 1287666487 -2109724676 -1388395896 1287666487 -1740625924
 -1438719244 1287666487 1463822332 -1472265808 1287666487 1648371708 -1522593306 1287666487 1832921084 -1572920804
 1287666487 2017470460 -1606471086 1287666487 -2092947460 -1656798584 1287666487 -1908398084 -1707126082 1287666487
 -1723848708 -1740676364 -742376649 4095909 117440512 -750825149 1446936485 306020784 -750825149 1446936485
 473825712 -750825149 -2126610523 658391688 -750825149 1446936485 826180016 -750825149 1816035237 1010737692
 -750825149 -2109833307 1195295368 -750825149 -1740734555 1363075828 -750825149 1463713701 1547633072 -750825149
 1648263077 1732186598 -750825149 1832812453 1899962908 -750825149 2017361829 2084516434 -750825149 -2093056091
 -2042674552 -750825149 -1908506715 -1858121026 -750825149 -1723957339 -1673567500 1279217987 4204540 117440512
 1279217987 1447045116 306020784 1279217987 1447045116 473825712 1279217987 -2126501892 658391688 1279217987
 1447045116 826180016 1279217987 1816143868 1010737692 1279217987 -2109724676 1195295368 1279217987 -1740625924
 1363075828 1279217987 1463822332 1547633072 1279217987 1648371708 1732186598 1279217987 1832921084 1899962908
 1279217987 2017470460 2084516434 1279217987 -2092947460 -2042674552 1279217987 -1908398084 -1858121026 1279217987
 -1723848708 -1673567500 4149571 0 0 0 0 0 4161536 0
 0 0 4161536 0 0 0 4161536 0 0 0
 4161536 0 0 0 4161536 0 0 -1811939328 17 0
 0 0 0 0 16777216 33554432 50331648 67108864 83886080 100663296
 117440512 134217728 150994944 167772160 184549376 201326592 218103808 234881024 251658240 268435456
 285212672 301989888 318767104 335544320 352321536 369098752 385875968 402653184 419430400 436207616
 452984832 469762048 486539264 503316480 520093696 536870912 553648128 570425344 587202560 603979776
 620756992 637534208 654311424 671088640 687865856 704643072 721420288 738197504 1442840576 1446871472
 1446871472 1446871472 37585328 0 0 0 0 0 4161536 4161536
 4161536 0 0 0;
	setAttr ".spambdif" 0.46279999613761902;
	setAttr ".spec" yes;
	setAttr ".spcm" 1;
	setAttr ".damp" 0;
	setAttr ".spfa" 0;
	setAttr ".spad" -type "float3" 0 1 0 ;
	setAttr ".spas" 0;
	setAttr ".disp" 0;
	setAttr ".spffx" 214.39999389648437;
	setAttr ".spffy" 214.39999389648437;
	setAttr ".spffz" 214.39999389648437;
	setAttr ".sprf" 15.5;
	setAttr ".sptf" 97.739997863769531;
	setAttr ".spgs" 1;
	setAttr ".spgloss" 0.083470001816749573;
	setAttr ".sphcol" -type "float3" 0.33375743 0.33884001 0.33650285 ;
	setAttr ".sphc" 100;
	setAttr ".sphv" 34.709999084472656;
	setAttr ".spis" no;
	setAttr ".spkfx" 155;
	setAttr ".spkfy" 155;
	setAttr ".spkfz" 155;
	setAttr ".spkr" 2;
	setAttr ".spkt" 5;
	setAttr ".spms" 0;
	setAttr ".spmhc" -type "float3" 0.47058824 0.47058824 0.47058824 ;
	setAttr ".spmp" 0;
	setAttr ".dointerp" yes;
	setAttr ".sphp" 7;
	setAttr ".sprm" 0.21488000452518463;
	setAttr ".sprs" 0.40000000596046448;
	setAttr ".sprtc" -type "float3" 0.41299999 0.41299999 0.41299999 ;
	setAttr ".rstf" 0;
	setAttr ".sc" 1;
	setAttr ".spsegs" 36;
	setAttr ".spss" 1;
	setAttr ".spspec" 0.89999997615814209;
	setAttr ".sprsp" 0.45464000105857849;
	setAttr ".sptsp" 0.2892799973487854;
	setAttr ".spstiff" 0;
	setAttr ".sptr" 0.49592000246047974;
	setAttr ".sptt" 0.23139999806880951;
	setAttr ".sptg" 4;
	setAttr ".spvv" 50;
	setAttr -s 32 ".shtx";
	setAttr ".shtx[0:6]" 0 0 0 0 0 0 0;
	setAttr ".shtx[8]" 0;
	setAttr ".shtx[12]" 0;
	setAttr ".shtx[16]" 0;
	setAttr ".shtx[20:21]" 0 0;
	setAttr ".shtx[24:43]" 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr ".tusd" 2;
	setAttr ".tvsd" 2;
	setAttr ".tm" 3.4;
	setAttr ".vl" 0;
	setAttr ".dhm" 1000;
	setAttr ".dhr" 1;
	setAttr ".sptn" -type "float3" 1 1 1 ;
	setAttr ".tf" yes;
	setAttr ".cbn" -type "double3" 0.15977400541305542 -0.18832865357398987 -0.88248354196548462 ;
	setAttr ".cbx" -type "double3" 2.7072725296020508 0.88142800331115723 3.0931859016418457 ;
	setAttr ".slk" no;
createNode lightLinker -n "lightLinker1";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
	setAttr -s 2 ".rlmi";
	setAttr ".rlmi[6]" 5;
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
	setAttr ".rndr" no;
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n"
		+ "                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n"
		+ "                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n"
		+ "            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n"
		+ "                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n"
		+ "                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n"
		+ "            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n"
		+ "                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n"
		+ "                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n"
		+ "                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n"
		+ "            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n"
		+ "            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n"
		+ "            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n"
		+ "                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n"
		+ "                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n"
		+ "                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 8192\n"
		+ "            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n"
		+ "            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n"
		+ "                -showShapes 1\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n"
		+ "            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 0\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n"
		+ "            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n"
		+ "                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n"
		+ "            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n"
		+ "                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n"
		+ "                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n"
		+ "                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n"
		+ "                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n"
		+ "                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n"
		+ "                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n"
		+ "                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"multiListerPanel\" (localizedPanelLabel(\"Multilister\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"multiListerPanel\" -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"devicePanel\" (localizedPanelLabel(\"Devices\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tdevicePanel -unParent -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tdevicePanel -edit -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"webBrowserPanel\" (localizedPanelLabel(\"Web Browser\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"webBrowserPanel\" -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"Stereo\" -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels `;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n"
		+ "                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n"
		+ "                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n"
		+ "                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n"
		+ "                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 8192\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n"
		+ "                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph InputOutput1\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph InputOutput1\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 1\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n"
		+ "                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph InputOutput1\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 1\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n"
		+ "                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 37 100 -ps 2 63 100 $gMainPane;\"\n"
		+ "\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n\t\t\t\t\t\"outlinerPanel\"\n\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 0\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 0\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
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
	setAttr ".spth" -type "string" "://E/dev/autodesk/maya/myplugin/project/liquid_/2.3.3/test/hair/:";
	setAttr ".shdd" -type "string" "generatedShader";
	setAttr ".unt" yes;
	setAttr ".osg" yes;
	setAttr ".tb" yes;
	setAttr ".lbsx" 64;
	setAttr ".lbsy" 64;
	setAttr ".rdc" -type "string" "prman";
	setAttr ".prv" -type "string" "prman";
	setAttr ".lrs" -type "string" "E:/MyDocuments/maya/projects/default/rmantmp/test_shaveHair(shave_v61)_er.xml";
	setAttr ".lrf" -type "string" "E:/MyDocuments/maya/projects/default/rib/_perspShape.0003.rib";
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
	setAttr ".rnd" -type "string" "elvishray";
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
createNode liquidSurface -n "liquidSurface1";
	addAttr -ci true -sn "liqAssignedObjects" -ln "liqAssignedObjects" -at "message";
	addAttr -ci true -h true -sn "specularPower" -ln "specularPower" -at "double";
	addAttr -ci true -h true -sn "translucence" -ln "translucence" -at "double";
	addAttr -ci true -uac -h true -k true -sn "specularColor" -ln "specularColor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "specularColora" -ln "specularColora" -at "float" 
		-p "specularColor";
	addAttr -ci true -h true -k true -sn "specularColorb" -ln "specularColorb" -at "float" 
		-p "specularColor";
	addAttr -ci true -h true -k true -sn "specularColorc" -ln "specularColorc" -at "float" 
		-p "specularColor";
	setAttr ".rms" -type "string" "liquidPfxHair";
	setAttr ".rml" -type "string" "E:/dev/autodesk/maya/myplugin/project/liquid_/2.3.3/lib/shaders/liquidPfxHair.slo";
	setAttr ".rpr" -type "stringArray" 5 "specularPower" "translucence" "specularColor" "pfxHair_vtxColor" "pfxHair_vtxOpacity"  ;
	setAttr ".rdt" -type "stringArray" 5 "uniform" "uniform" "uniform" "varying" "varying"  ;
	setAttr ".rty" -type "stringArray" 5 "float" "float" "color" "color" "color"  ;
	setAttr ".rdf" -type "stringArray" 5 "3.0" "0.0" "0.0000000.0000000.000000" "1.0000000.0000000.000000" "1.0000001.0000001.000000"  ;
	setAttr ".ras" -type "Int32Array" 5 -1 -1 -1 -1 -1 ;
	setAttr ".rlc" -type "stringArray" 5 "liquidAE_LifFloat( \"specularPower\", -1, \"float\", \"specularPower\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"translucence\", -1, \"float\", \"translucence\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"specularColor\", -1, \"color\", \"specularColor\", {\"0\", \"0\"}, \"\", 14 );" "" ""  ;
	setAttr ".rmt" -type "stringArray" 1 "surface"  ;
	setAttr ".rio" -type "Int32Array" 5 0 0 0 1 1 ;
	setAttr ".specularPower" 3;
	setAttr ".translucence" 0.3;
	setAttr -k on ".specularColor" -type "float3" 0.97350001 1 0 ;
createNode shadingEngine -n "liquidSurface1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode liquidSurface -n "liquidSurface2";
	addAttr -ci true -sn "liqAssignedObjects" -ln "liqAssignedObjects" -at "message";
	addAttr -ci true -h true -sn "Ka" -ln "Ka" -at "double";
	addAttr -ci true -h true -sn "Kd" -ln "Kd" -at "double";
	addAttr -ci true -h true -sn "Ks" -ln "Ks" -at "double";
	addAttr -ci true -h true -sn "roughness" -ln "roughness" -at "double";
	addAttr -ci true -uac -h true -k true -sn "rootcolor" -ln "rootcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "rootcolora" -ln "rootcolora" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorb" -ln "rootcolorb" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorc" -ln "rootcolorc" -at "float" -p "rootcolor";
	addAttr -ci true -uac -h true -k true -sn "tipcolor" -ln "tipcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "tipcolora" -ln "tipcolora" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorb" -ln "tipcolorb" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorc" -ln "tipcolorc" -at "float" -p "tipcolor";
	addAttr -ci true -uac -h true -k true -sn "specularcolor" -ln "specularcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "specularcolora" -ln "specularcolora" -at "float" 
		-p "specularcolor";
	addAttr -ci true -h true -k true -sn "specularcolorb" -ln "specularcolorb" -at "float" 
		-p "specularcolor";
	addAttr -ci true -h true -k true -sn "specularcolorc" -ln "specularcolorc" -at "float" 
		-p "specularcolor";
	setAttr ".rms" -type "string" "hair";
	setAttr ".rml" -type "string" "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/hair/hair.slo";
	setAttr ".rpr" -type "stringArray" 7 "Ka" "Kd" "Ks" "roughness" "rootcolor" "tipcolor" "specularcolor"  ;
	setAttr ".rdt" -type "stringArray" 7 "uniform" "uniform" "uniform" "uniform" "uniform" "uniform" "uniform"  ;
	setAttr ".rty" -type "stringArray" 7 "float" "float" "float" "float" "color" "color" "color"  ;
	setAttr ".rdf" -type "stringArray" 7 "1.0" "0.6" "0.35" "0.15" "0.1090000.0370000.007000" "0.5190000.3250000.125000" "000"  ;
	setAttr ".ras" -type "Int32Array" 7 -1 -1 -1 -1 -1 -1
		 -1 ;
	setAttr ".rlc" -type "stringArray" 7 "liquidAE_LifFloat( \"Ka\", -1, \"float\", \"Ka\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"Kd\", -1, \"float\", \"Kd\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"Ks\", -1, \"float\", \"Ks\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"roughness\", -1, \"float\", \"roughness\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"rootcolor\", -1, \"color\", \"rootcolor\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"tipcolor\", -1, \"color\", \"tipcolor\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"specularcolor\", -1, \"color\", \"specularcolor\", {\"0\", \"0\"}, \"\", 14 );"  ;
	setAttr ".rmt" -type "stringArray" 1 "surface"  ;
	setAttr ".rio" -type "Int32Array" 7 0 0 0 0 0 0
		 0 ;
	setAttr ".Ka" 1;
	setAttr ".Kd" 0.6;
	setAttr ".Ks" 0.35;
	setAttr ".roughness" 0.15;
	setAttr -k on ".rootcolor" -type "float3" 0.109 0.037 0.0070000002 ;
	setAttr -k on ".tipcolor" -type "float3" 0.51899999 0.32499999 0.125 ;
createNode shadingEngine -n "liquidSurface2SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode liquidSurface -n "liquidSurface3";
	addAttr -ci true -sn "liqAssignedObjects" -ln "liqAssignedObjects" -at "message";
	addAttr -ci true -h true -sn "Ka" -ln "Ka" -at "double";
	addAttr -ci true -h true -sn "SHAVEambdiff" -ln "SHAVEambdiff" -at "double";
	addAttr -ci true -h true -sn "SHAVEspec" -ln "SHAVEspec" -at "double";
	addAttr -ci true -h true -sn "SHAVEgloss" -ln "SHAVEgloss" -at "double";
	addAttr -ci true -h true -sn "SHAVEopacity" -ln "SHAVEopacity" -at "double";
	addAttr -ci true -h true -sn "SHAVEselfshad" -ln "SHAVEselfshad" -at "double";
	addAttr -ci true -uac -h true -k true -sn "SHAVEspec_color" -ln "SHAVEspec_color" 
		-at "float3" -nc 3;
	addAttr -ci true -h true -k true -sn "SHAVEspec_colora" -ln "SHAVEspec_colora" -at "float" 
		-p "SHAVEspec_color";
	addAttr -ci true -h true -k true -sn "SHAVEspec_colorb" -ln "SHAVEspec_colorb" -at "float" 
		-p "SHAVEspec_color";
	addAttr -ci true -h true -k true -sn "SHAVEspec_colorc" -ln "SHAVEspec_colorc" -at "float" 
		-p "SHAVEspec_color";
	addAttr -ci true -uac -h true -k true -sn "rootcolor" -ln "rootcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "rootcolora" -ln "rootcolora" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorb" -ln "rootcolorb" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorc" -ln "rootcolorc" -at "float" -p "rootcolor";
	addAttr -ci true -uac -h true -k true -sn "tipcolor" -ln "tipcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "tipcolora" -ln "tipcolora" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorb" -ln "tipcolorb" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorc" -ln "tipcolorc" -at "float" -p "tipcolor";
	setAttr ".rms" -type "string" "Shave";
	setAttr ".rml" -type "string" "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/hair/Shave.slo";
	setAttr ".rpr" -type "stringArray" 9 "Ka" "SHAVEambdiff" "SHAVEspec" "SHAVEgloss" "SHAVEopacity" "SHAVEselfshad" "SHAVEspec_color" "rootcolor" "tipcolor"  ;
	setAttr ".rdt" -type "stringArray" 9 "uniform" "uniform" "uniform" "uniform" "uniform" "uniform" "uniform" "uniform" "uniform"  ;
	setAttr ".rty" -type "stringArray" 9 "float" "float" "float" "float" "float" "float" "color" "color" "color"  ;
	setAttr ".rdf" -type "stringArray" 9 "0.0" "0.6" "0.35" "0.07" "1.0" "1.0" "1.0000001.0000001.000000" "1.0000001.0000001.000000" "1.0000001.0000001.000000"  ;
	setAttr ".ras" -type "Int32Array" 9 -1 -1 -1 -1 -1 -1
		 -1 -1 -1 ;
	setAttr ".rlc" -type "stringArray" 9 "liquidAE_LifFloat( \"Ka\", -1, \"float\", \"Ka\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"SHAVEambdiff\", -1, \"float\", \"SHAVEambdiff\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"SHAVEspec\", -1, \"float\", \"SHAVEspec\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"SHAVEgloss\", -1, \"float\", \"SHAVEgloss\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"SHAVEopacity\", -1, \"float\", \"SHAVEopacity\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"SHAVEselfshad\", -1, \"float\", \"SHAVEselfshad\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"SHAVEspec_color\", -1, \"color\", \"SHAVEspec_color\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"rootcolor\", -1, \"color\", \"rootcolor\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"tipcolor\", -1, \"color\", \"tipcolor\", {\"0\", \"0\"}, \"\", 14 );"  ;
	setAttr ".rmt" -type "stringArray" 1 "surface"  ;
	setAttr ".rio" -type "Int32Array" 9 0 0 0 0 0 0
		 0 0 0 ;
	setAttr ".SHAVEambdiff" 0.6;
	setAttr ".SHAVEspec" 0.35;
	setAttr ".SHAVEgloss" 0.07;
	setAttr ".SHAVEopacity" 1;
	setAttr ".SHAVEselfshad" 1;
	setAttr -k on ".SHAVEspec_color" -type "float3" 1 1 1 ;
	setAttr -k on ".rootcolor" -type "float3" 0 0.0018334389 1 ;
	setAttr -k on ".tipcolor" -type "float3" 1 0.051333331 0 ;
createNode shadingEngine -n "liquidSurface3SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode shaveGlobals -s -n "shaveGlobals";
	setAttr ".cch" no;
	setAttr ".ihi" 2;
	setAttr ".nds" 0;
	setAttr ".i1" 0;
	setAttr ".i2" 0;
	setAttr ".rndm" 0;
	setAttr ".eig" yes;
	setAttr ".nil" no;
	setAttr ".dsc" yes;
	setAttr ".c2d" yes;
	setAttr ".dhs" yes;
	setAttr ".ual" yes;
	setAttr ".sm" no;
	setAttr ".smbf" yes;
	setAttr ".khrf" no;
	setAttr ".rq" 1;
	setAttr ".hfn" -type "string" "E:/MyDocuments/maya/projects/default/shaveHair";
	setAttr ".tpd" -type "string" "";
	setAttr ".sso" -type "string" "all";
	setAttr ".sd" 1;
	setAttr ".grav" 1;
	setAttr ".nv" 11;
	setAttr ".dra" yes;
	setAttr ".vxrs" 5;
	setAttr ".mrei" no;
	setAttr ".mrir" 1;
	setAttr ".mroc" no;
	setAttr ".mrsm" yes;
	setAttr ".mss" no;
	setAttr ".rgcb" yes;
	setAttr ".vrfl" no;
	setAttr ".hh" no;
	setAttr ".mth" 0;
	setAttr ".tpp" yes;
	setAttr ".verb" yes;
	setAttr ".vs" 1.1000000238418579;
	setAttr ".addr" ;
	setAttr ".tml" 90;
	setAttr ".td" 30;
	setAttr ".rbin" no;
	setAttr ".rbtb" 1;
	setAttr ".rben" no;
	setAttr ".rbis" 1;
	setAttr ".rbrf" yes;
	setAttr ".rbsc" 0.30000001192092896;
	setAttr ".rbso" -0.30000001192092896;
	setAttr ".rcmp" no;
	setAttr ".rkrf" no;
	setAttr ".rnrm" no;
	setAttr ".ropa" yes;
	setAttr ".prhpt" 1;
	setAttr ".rrp" no;
	setAttr ".rrtc" yes;
	setAttr ".rst" -type "string" "#global rib text";
	setAttr ".rvc" no;
	setAttr ".rtu" 0;
	setAttr ".ruv" no;
	setAttr ".rwc" no;
	setAttr ".rvxe" no;
	setAttr ".rvxp" no;
	setAttr ".rvxr" 5;
	setAttr ".shr" 0.15000000596046448;
	setAttr ".uds" no;
createNode liquidSurface -n "lambert3";
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
createNode renderLayer -n "hairShader";
	setAttr ".do" 5;
createNode polyPlane -n "polyPlane8";
	setAttr ".w" 2.3751187813502788;
	setAttr ".h" 3.7427062285810755;
	setAttr ".sw" 1;
	setAttr ".sh" 1;
	setAttr ".cuv" 2;
createNode objectSet -n "shaveHairShape6_growth";
createNode liquidSurface -n "liquidSurface4";
	addAttr -ci true -h true -sn "Ka" -ln "Ka" -at "double";
	addAttr -ci true -h true -sn "Ks" -ln "Ks" -at "double";
	addAttr -ci true -h true -sn "roughness" -ln "roughness" -at "double";
	addAttr -ci true -uac -h true -k true -sn "rootcolor" -ln "rootcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "rootcolora" -ln "rootcolora" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorb" -ln "rootcolorb" -at "float" -p "rootcolor";
	addAttr -ci true -h true -k true -sn "rootcolorc" -ln "rootcolorc" -at "float" -p "rootcolor";
	addAttr -ci true -uac -h true -k true -sn "tipcolor" -ln "tipcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "tipcolora" -ln "tipcolora" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorb" -ln "tipcolorb" -at "float" -p "tipcolor";
	addAttr -ci true -h true -k true -sn "tipcolorc" -ln "tipcolorc" -at "float" -p "tipcolor";
	addAttr -ci true -uac -h true -k true -sn "specularcolor" -ln "specularcolor" -at "float3" 
		-nc 3;
	addAttr -ci true -h true -k true -sn "specularcolora" -ln "specularcolora" -at "float" 
		-p "specularcolor";
	addAttr -ci true -h true -k true -sn "specularcolorb" -ln "specularcolorb" -at "float" 
		-p "specularcolor";
	addAttr -ci true -h true -k true -sn "specularcolorc" -ln "specularcolorc" -at "float" 
		-p "specularcolor";
	addAttr -ci true -sn "liqAssignedObjects" -ln "liqAssignedObjects" -at "message";
	addAttr -ci true -h true -k true -sn "Cs" -ln "Cs" -at "double3" -nc 3;
	addAttr -ci true -h true -k true -sn "Csa" -ln "Csa" -at "double" -p "Cs";
	addAttr -ci true -h true -k true -sn "Csb" -ln "Csb" -at "double" -p "Cs";
	addAttr -ci true -h true -k true -sn "Csc" -ln "Csc" -at "double" -p "Cs";
	addAttr -ci true -h true -k true -sn "Kd" -ln "Kd" -at "double3" -nc 3;
	addAttr -ci true -h true -k true -sn "Kda" -ln "Kda" -at "double" -p "Kd";
	addAttr -ci true -h true -k true -sn "Kdb" -ln "Kdb" -at "double" -p "Kd";
	addAttr -ci true -h true -k true -sn "Kdc" -ln "Kdc" -at "double" -p "Kd";
	addAttr -ci true -h true -sn "specularpower" -ln "specularpower" -at "double";
	setAttr ".rms" -type "string" "simple_hair";
	setAttr ".rst" -type "string" "surface";
	setAttr ".rml" -type "string" "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/hair/simple_hair.dll";
	setAttr ".rpr" -type "stringArray" 5 "Cs" "Kd" "Ks" "specularcolor" "specularpower"  ;
	setAttr ".rdt" -type "stringArray" 5 "uniform" "uniform" "uniform" "uniform" "uniform"  ;
	setAttr ".rty" -type "stringArray" 5 "vector" "vector" "float" "color" "float"  ;
	setAttr ".rdf" -type "stringArray" 5 "1.0000001.0000001.000000" "1.0000001.0000001.000000" "0.5" "1.0000001.0000001.000000" "60"  ;
	setAttr ".ras" -type "Int32Array" 5 -1 -1 -1 -1 -1 ;
	setAttr ".rlc" -type "stringArray" 5 "liquidAE_LifVector( \"Cs\", -1, \"vector\", \"Cs\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifVector( \"Kd\", -1, \"vector\", \"Kd\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"Ks\", -1, \"float\", \"Ks\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifColor( \"specularcolor\", -1, \"color\", \"specularcolor\", {\"0\", \"0\"}, \"\", 14 );" "liquidAE_LifFloat( \"specularpower\", -1, \"float\", \"specularpower\", {\"0\", \"0\"}, \"\", 14 );"  ;
	setAttr ".rmt" -type "stringArray" 0  ;
	setAttr ".rio" -type "Int32Array" 5 0 0 0 0 0 ;
	setAttr ".Ka" 1;
	setAttr ".Ks" 0.35;
	setAttr ".roughness" 0.15;
	setAttr -k on ".rootcolor" -type "float3" 0.14 0.047507599 0.0089600012 ;
	setAttr -k on ".tipcolor" -type "float3" 1 0 0.026499748 ;
	setAttr -k on ".specularcolor" -type "float3" 0.71503764 0.72600001 0.047915991 ;
	setAttr -k on ".Cs" -type "double3" 0 0.5 0 ;
	setAttr -k on ".Kd" -type "double3" 1 1 1 ;
	setAttr ".specularpower" 60;
createNode shadingEngine -n "liquidSurface4SG";
	addAttr -ci true -uac -k true -sn "liqShadowShader" -ln "liqShadowShader" -at "float3" 
		-nc 3;
	addAttr -ci true -k true -sn "liqShadowShaderred" -ln "liqShadowShaderred" -dv 1 
		-at "float" -p "liqShadowShader";
	addAttr -ci true -k true -sn "liqShadowShadergreen" -ln "liqShadowShadergreen" -dv 
		1 -at "float" -p "liqShadowShader";
	addAttr -ci true -k true -sn "liqShadowShaderblue" -ln "liqShadowShaderblue" -dv 
		1 -at "float" -p "liqShadowShader";
	addAttr -ci true -uac -k true -sn "liqEnvironmentShader" -ln "liqEnvironmentShader" 
		-at "float3" -nc 3;
	addAttr -ci true -k true -sn "liqEnvironmentShaderred" -ln "liqEnvironmentShaderred" 
		-dv 1 -at "float" -p "liqEnvironmentShader";
	addAttr -ci true -k true -sn "liqEnvironmentShadergreen" -ln "liqEnvironmentShadergreen" 
		-dv 1 -at "float" -p "liqEnvironmentShader";
	addAttr -ci true -k true -sn "liqEnvironmentShaderblue" -ln "liqEnvironmentShaderblue" 
		-dv 1 -at "float" -p "liqEnvironmentShader";
	addAttr -ci true -uac -k true -sn "liqPhotonShader" -ln "liqPhotonShader" -at "float3" 
		-nc 3;
	addAttr -ci true -k true -sn "liqPhotonShaderred" -ln "liqPhotonShaderred" -dv 1 
		-at "float" -p "liqPhotonShader";
	addAttr -ci true -k true -sn "liqPhotonShadergreen" -ln "liqPhotonShadergreen" -dv 
		1 -at "float" -p "liqPhotonShader";
	addAttr -ci true -k true -sn "liqPhotonShaderblue" -ln "liqPhotonShaderblue" -dv 
		1 -at "float" -p "liqPhotonShader";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
	setAttr -k on ".liqShadowShader";
createNode materialInfo -n "materialInfo4";
createNode liqGlobalsNodeRenderer -n "liqGlobalsNodeRenderer_elvishray";
	addAttr -ci true -h true -sn "verbose" -ln "verbose" -dv 6 -at "long";
	addAttr -ci true -h true -sn "link" -ln "link" -dt "string";
	addAttr -ci true -h true -sn "contrast" -ln "contrast" -dt "string";
	addAttr -ci true -h true -sn "samples" -ln "samples" -dt "string";
	addAttr -ci true -h true -sn "filterType" -ln "filterType" -dv 4 -at "long";
	addAttr -ci true -h true -sn "filterSize" -ln "filterSize" -dv 3 -at "float";
	addAttr -ci true -h true -sn "trace_depth" -ln "trace_depth" -dt "string";
	addAttr -ci true -h true -sn "displace" -ln "displace" -min 0 -max 1 -at "bool";
	addAttr -ci true -h true -sn "max_displace" -ln "max_displace" -at "float";
	addAttr -ci true -h true -sn "face" -ln "face" -dv 3 -at "long";
	addAttr -ci true -h true -sn "approx_method" -ln "approx_method" -dv 1 -at "long";
	addAttr -ci true -h true -sn "approx_any" -ln "approx_any" -at "long";
	addAttr -ci true -h true -sn "approx_view_dep" -ln "approx_view_dep" -at "long";
	addAttr -ci true -h true -sn "approx_args" -ln "approx_args" -dt "string";
	addAttr -ci true -h true -sn "approx_sharp" -ln "approx_sharp" -at "float";
	addAttr -ci true -h true -sn "approx_min_subdiv" -ln "approx_min_subdiv" -at "long";
	addAttr -ci true -h true -sn "approx_max_subdiv" -ln "approx_max_subdiv" -dv 5 -at "long";
	addAttr -ci true -h true -sn "approx_max_grid_size" -ln "approx_max_grid_size" -dv 
		4096 -at "long";
	addAttr -ci true -h true -sn "approx_motion_factor" -ln "approx_motion_factor" -dv 
		16 -at "float";
	setAttr ".link" -type "string" "eiIMG|eiSHADER|eiSHADER_maya";
	setAttr ".contrast" -type "string" "0.05|0.05|0.05|0.05";
	setAttr ".samples" -type "string" "0|2";
	setAttr ".trace_depth" -type "string" "4|4|4";
	setAttr ".approx_args" -type "string" "0|0|0|0";
createNode liqGlobalsNodeRenderer -n "liqGlobalsNodeRenderer_renderman";
	addAttr -ci true -h true -sn "testBool0" -ln "testBool0" -min 0 -max 1 -at "bool";
	addAttr -ci true -h true -sn "testBool1" -ln "testBool1" -min 0 -max 1 -at "bool";
	addAttr -ci true -h true -sn "testString0" -ln "testString0" -dt "string";
	addAttr -ci true -h true -sn "testString1" -ln "testString1" -dt "string";
	addAttr -ci true -uac -h true -sn "testColor0" -ln "testColor0" -at "float3" -nc 
		3;
	addAttr -ci true -sn "testColor0R" -ln "testColor0R" -at "float" -p "testColor0";
	addAttr -ci true -sn "testColor0G" -ln "testColor0G" -at "float" -p "testColor0";
	addAttr -ci true -sn "testColor0B" -ln "testColor0B" -at "float" -p "testColor0";
	addAttr -ci true -uac -h true -sn "testColor1" -ln "testColor1" -at "float3" -nc 
		3;
	addAttr -ci true -sn "testColor1R" -ln "testColor1R" -at "float" -p "testColor1";
	addAttr -ci true -sn "testColor1G" -ln "testColor1G" -at "float" -p "testColor1";
	addAttr -ci true -sn "testColor1B" -ln "testColor1B" -at "float" -p "testColor1";
	addAttr -ci true -h true -sn "testInt0" -ln "testInt0" -at "long";
	addAttr -ci true -h true -sn "testInt1" -ln "testInt1" -dv 10 -at "long";
	addAttr -ci true -h true -sn "testFloat0" -ln "testFloat0" -at "float";
	addAttr -ci true -h true -sn "testFloat1" -ln "testFloat1" -dv 10 -at "float";
	addAttr -ci true -h true -sn "testIntMenu0" -ln "testIntMenu0" -at "long";
	addAttr -ci true -h true -sn "testIntMenu1" -ln "testIntMenu1" -dv 1 -at "long";
	setAttr ".testBool0" yes;
	setAttr ".testString0" -type "string" "string_test_value0renderman";
	setAttr ".testString1" -type "string" "string_test_value1renderman";
	setAttr ".testColor0" -type "float3" 1 1 0 ;
	setAttr ".testColor1" -type "float3" 1.9 9 2 ;
createNode liquidSurface -n "liquidSurface5";
	setAttr ".rms" -type "string" "opaque";
	setAttr ".rst" -type "string" "shadow";
	setAttr ".rml" -type "string" "E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/hair/opaque.dll";
	setAttr ".rpr" -type "stringArray" 0  ;
	setAttr ".rdt" -type "stringArray" 0  ;
	setAttr ".rty" -type "stringArray" 0  ;
	setAttr ".rdf" -type "stringArray" 0  ;
	setAttr ".ras" -type "Int32Array" 0 ;
	setAttr ".rlc" -type "stringArray" 0  ;
	setAttr ".rmt" -type "stringArray" 0  ;
	setAttr ".rio" -type "Int32Array" 0 ;
createNode shadingEngine -n "liquidSurface5SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo5";
select -ne :time1;
	setAttr ".o" 3.4;
select -ne :renderPartition;
	setAttr -s 7 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 9 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :lambert1;
	setAttr ".c" -type "float3" 0.898 0.53904247 0.13290401 ;
select -ne :initialShadingGroup;
	setAttr -s 6 ".dsm";
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
connectAttr "hairShader.ri" "pointLight1.rlio[4]";
connectAttr "hairShader.ri" "shavedisplay4.rlio[0]";
connectAttr "hairShader.ri" "|shaveDisplayGroup|shavedisplay4|shaveDisplayShape.rlio[0]"
		;
connectAttr "shaveHairShape6.out" "|shaveDisplayGroup|shavedisplay4|shaveDisplayShape.i"
		;
connectAttr "hairShader.ri" "pPlane8.rlio[0]";
connectAttr "polyPlane8.out" "pPlaneShape8.i";
connectAttr "hairShader.ri" "shaveHair6.rlio[0]";
connectAttr ":time1.o" "shaveHairShape6.tm";
connectAttr "shaveHairShape6_growth.msg" "shaveHairShape6.gs";
connectAttr "pPlaneShape8.w" "shaveHairShape6.input[0]";
connectAttr "|shaveDisplayGroup|shavedisplay4|shaveDisplayShape.msg" "shaveHairShape6.dn"
		;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "liquidSurface1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr "liquidSurface2SG.msg" "lightLinker1.lnk[3].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr "liquidSurface3SG.msg" "lightLinker1.lnk[4].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[5].llnk";
connectAttr "liquidSurface4SG.msg" "lightLinker1.lnk[5].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[6].llnk";
connectAttr "liquidSurface5SG.msg" "lightLinker1.lnk[6].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[2].sllk";
connectAttr "liquidSurface1SG.msg" "lightLinker1.slnk[2].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[3].sllk";
connectAttr "liquidSurface2SG.msg" "lightLinker1.slnk[3].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr "liquidSurface3SG.msg" "lightLinker1.slnk[4].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[5].sllk";
connectAttr "liquidSurface4SG.msg" "lightLinker1.slnk[5].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[6].sllk";
connectAttr "liquidSurface5SG.msg" "lightLinker1.slnk[6].solk";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "liquidSurface1.oc" "liquidSurface1SG.ss";
connectAttr "liquidSurface1SG.msg" "materialInfo1.sg";
connectAttr "liquidSurface1.msg" "materialInfo1.m";
connectAttr "liquidSurface1.msg" "materialInfo1.t" -na;
connectAttr "liquidSurface2.oc" "liquidSurface2SG.ss";
connectAttr "liquidSurface2SG.msg" "materialInfo2.sg";
connectAttr "liquidSurface2.msg" "materialInfo2.m";
connectAttr "liquidSurface2.msg" "materialInfo2.t" -na;
connectAttr "liquidSurface3.oc" "liquidSurface3SG.ss";
connectAttr "liquidSurface3SG.msg" "materialInfo3.sg";
connectAttr "liquidSurface3.msg" "materialInfo3.m";
connectAttr "liquidSurface3.msg" "materialInfo3.t" -na;
connectAttr "renderLayerManager.rlmi[6]" "hairShader.rlid";
connectAttr "pPlaneShape8.iog" "shaveHairShape6_growth.dsm" -na;
connectAttr "liquidSurface4.oc" "liquidSurface4SG.ss";
connectAttr "shaveHairShape6.iog" "liquidSurface4SG.dsm" -na;
connectAttr "liquidSurface5.oc" "liquidSurface4SG.liqShadowShader";
connectAttr "liquidSurface4SG.msg" "materialInfo4.sg";
connectAttr "liquidSurface4.msg" "materialInfo4.m";
connectAttr "liquidSurface4.msg" "materialInfo4.t" -na;
connectAttr "liquidSurface5.oc" "liquidSurface5SG.ss";
connectAttr "liquidSurface5SG.msg" "materialInfo5.sg";
connectAttr "liquidSurface5.msg" "materialInfo5.m";
connectAttr "liquidSurface5.msg" "materialInfo5.t" -na;
connectAttr "liquidSurface1SG.pa" ":renderPartition.st" -na;
connectAttr "liquidSurface2SG.pa" ":renderPartition.st" -na;
connectAttr "liquidSurface3SG.pa" ":renderPartition.st" -na;
connectAttr "liquidSurface4SG.pa" ":renderPartition.st" -na;
connectAttr "liquidSurface5SG.pa" ":renderPartition.st" -na;
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "liquidSurface1.msg" ":defaultShaderList1.s" -na;
connectAttr "liquidSurface2.msg" ":defaultShaderList1.s" -na;
connectAttr "liquidSurface3.msg" ":defaultShaderList1.s" -na;
connectAttr "lambert3.msg" ":defaultShaderList1.s" -na;
connectAttr "liquidSurface4.msg" ":defaultShaderList1.s" -na;
connectAttr "liquidSurface5.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "pointLightShape1.ltd" ":lightList1.l" -na;
connectAttr "|shaveDisplayGroup|shavedisplay|shaveDisplayShape.iog" ":initialShadingGroup.dsm"
		 -na;
connectAttr "|shaveDisplayGroup|shavedisplay1|shaveDisplayShape.iog" ":initialShadingGroup.dsm"
		 -na;
connectAttr "|shaveDisplayGroup|shavedisplay2|shaveDisplayShape.iog" ":initialShadingGroup.dsm"
		 -na;
connectAttr "|shaveDisplayGroup|shavedisplay3|shaveDisplayShape.iog" ":initialShadingGroup.dsm"
		 -na;
connectAttr "pPlaneShape8.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|shaveDisplayGroup|shavedisplay4|shaveDisplayShape.iog" ":initialShadingGroup.dsm"
		 -na;
connectAttr "pointLight1.iog" ":defaultLightSet.dsm" -na;
// End of test_shaveHair(shave_v61)_er.ma
