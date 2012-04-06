//Maya ASCII 2009 scene
//Name: MoxMotionMeetsFBIK_NoAux.ma
//Last modified: Fri, Apr 06, 2012 07:28:16 PM
//Codeset: 936
requires maya "2009";
requires "liquid_2009x32d" "2.3.5 (buildtime=16:33:01.12)";
requires "Mayatomr" "10.0.1.8m - 3.7.1.26 ";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2009";
fileInfo "version" "2009";
fileInfo "cutIdentifier" "200809110030-734661";
fileInfo "osv" "Microsoft Windows Vista Service Pack 1 (Build 7601)\n";
createNode transform -s -n "persp";
	setAttr ".t" -type "double3" 7.1895595713877132 32.213920056149483 9.26289329996278 ;
	setAttr ".r" -type "double3" -39.338352729757936 4.4000000000002526 -1.9937226706158092e-016 ;
createNode camera -s -n "perspShape" -p "persp";
	addAttr -ci true -sn "usedBy3dfm" -ln "usedBy3dfm" -at "message";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".fl" 34.999999999999986;
	setAttr ".ncp" 0.01;
	setAttr ".coi" 33.597781344784387;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" -6.4502098462653237 12.664787428785214 -15.291393962670062 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".t" -type "double3" 14.465608220018053 118.76950827508595 -11.165742229059816 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".ncp" 0.01;
	setAttr ".coi" 100.1;
	setAttr ".ow" 210.00140414779429;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".t" -type "double3" 5.7860183687827149 0.25372460567094346 107.47538822662494 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".ncp" 0.01;
	setAttr ".coi" 100.1;
	setAttr ".ow" 11.428270401145355;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".t" -type "double3" 103.89751075559359 9.2124357364184704 -15.503965756809812 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".ncp" 0.01;
	setAttr ".coi" 100.1;
	setAttr ".ow" 14.014868459591137;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pointLight1";
	setAttr ".t" -type "double3" 0 16.406707032062236 0 ;
createNode pointLight -n "pointLightShape1" -p "pointLight1";
	setAttr -k off ".v";
	setAttr ".in" 0.9089999794960022;
	setAttr ".us" no;
createNode lookAt -n "camera2_group";
	setAttr ".t" -type "double3" 0 8.636421 0 ;
	setAttr ".a" -type "double3" 0 0 -1 ;
	setAttr ".db" 56.790324999999996;
	setAttr ".tws" 8.5377364625159387e-007;
createNode transform -n "MoxrenderCam" -p "camera2_group";
	setAttr ".t" -type "double3" 4.1382612358786992e-016 0 51.790325 ;
	setAttr ".rp" -type "double3" 8.8817841970012523e-016 8.8817841970012523e-016 -7.1054273576010019e-015 ;
	setAttr ".rpt" -type "double3" -1.1811224163206093e-015 -6.1901823937336101e-016 
		1.4160548303177237e-016 ;
createNode camera -n "MoxrenderCamShape" -p "MoxrenderCam";
	addAttr -ci true -sn "usedBy3dfm" -ln "usedBy3dfm" -at "message";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".cap" -type "double2" 0.377 0.212 ;
	setAttr ".ff" 2;
	setAttr ".ovr" 1.3;
	setAttr ".ncp" 0.01;
	setAttr ".coi" 56.790324999999996;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "camera2";
	setAttr ".den" -type "string" "camera2_depth";
	setAttr ".man" -type "string" "camera2_mask";
	setAttr ".dfg" yes;
createNode transform -n "camera2_aim" -p "camera2_group";
	setAttr ".drp" yes;
createNode transform -n "MoxMotion:MOX";
createNode transform -n "MoxMotion:MoxCnt" -p "MoxMotion:MOX";
	setAttr ".t" -type "double3" 0 0 -15.323817 ;
	setAttr ".mnsl" -type "double3" 0.001 0.001 0.001 ;
	setAttr ".msxe" yes;
	setAttr ".msye" yes;
	setAttr ".msze" yes;
createNode hikHandle -n "MoxMotion:hikHandle1" -p "MoxMotion:MoxCnt";
	setAttr ".v" no;
	setAttr ".io" yes;
	setAttr -k off ".pvx";
	setAttr -k off ".pvy";
	setAttr -k off ".pvz";
	setAttr -k off ".off";
	setAttr -k off ".rol";
	setAttr -k off ".twi";
	setAttr -s 4 ".eff";
	setAttr -s 22 ".jt";
	setAttr -s 22 ".fj";
	setAttr -s 22 ".fm";
	setAttr -s 22 ".sm";
	setAttr ".sm[0]" -type "matrix" 0.81749643527644233 -0.57593365790714957 0 0 0.57593365790714957 0.81749643527644233 0 0
		 0 0 1 0 0 8.4977872187512844 -0.0087677710271807235 1;
	setAttr ".sm[1]" -type "matrix" -2.2204460492503131e-016 -0.99589320646770396 0.090535746042518808 0
		 1.8041124150158794e-016 0.090535746042518878 0.99589320646770385 0 -1 1.6653345369377348e-016 2.2204460492503131e-016 0
		 0.79392608644671492 7.9384590855092805 -0.0087677710271807235 1;
	setAttr ".sm[2]" -type "matrix" -2.5055100317637641e-016 -0.99614341334943968 -0.087739956921164056 0
		 -1.4901161454429018e-008 0.087739956921164 -0.99614341334943968 0 1 1.3074270854351057e-009 -1.4843693918546604e-008 0
		 0.79392608644671336 4.4608972136133511 0.3073742173269956 1;
	setAttr ".sm[3]" -type "matrix" 1.485310430017223e-008 -0.0075185844740167929 0.99997173504429993 0
		 2.9802323041142354e-008 0.99997173504429948 0.007518584474016347 0 -0.99999999999999956 2.9689806289486679e-008 1.5076755823621183e-008 0
		 0.7939260864467117 0.91799066767122595 -0.0046837288992930826 1;
	setAttr ".sm[4]" -type "matrix" 1 -5.4351218357587378e-016 -1.7624641027844059e-016 0
		 6.1376370986643881e-016 1.0000000000000002 8.100456590893912e-010 0 1.1535922695774343e-016 -8.1004566068952257e-010 1.0000000000000002 0
		 0.79392608644671181 0.90437719391160376 1.8059082811306884 1;
	setAttr ".sm[5]" -type "matrix" 8.8817841970012523e-016 0.99976737234005641 0.021568523460321228 0
		 -4.3496456436642461e-014 0.021568523460321235 -0.99976737234005664 0 -0.99999999999999989 -1.6653345369377348e-016 4.3631764867768652e-014 0
		 -2.7755575615628914e-016 9.2940231266641362 0.054283625774385988 1;
	setAttr ".sm[6]" -type "matrix" -1.1465954119043092e-015 0.99968237722196418 -0.025202076736688252 0
		 4.336794693473151e-014 0.025202076736688232 0.99968237722196451 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615629111e-016 10.550792300495431 0.081396588409426568 1;
	setAttr ".sm[7]" -type "matrix" -9.2758154485989307e-016 0.99979689629958546 -0.020153564193847423 0
		 4.3373184052475599e-014 0.020153564193847402 0.99979689629958579 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.775557561562919e-016 12.304005107215648 0.032420088196603906 1;
	setAttr ".sm[8]" -type "matrix" -5.3268900522569938e-017 0.99999999999999978 0 0
		 4.3383068872505149e-014 -1.3877787807814457e-017 1 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615630353e-016 13.113895811633148 0.016094588125663136 1;
	setAttr ".sm[9]" -type "matrix" -3.7944666293932018e-016 0.99997173504429948 -0.0075185844740132263 0
		 4.3381442145256909e-014 0.0075185844740132107 0.9999717350442997 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615627277e-016 13.424080312981028 0.016094588125663865 1;
	setAttr ".sm[10]" -type "matrix" 0.99996049616811267 -0.0088885377437186337 7.7686504868642555e-017 0
		 0.0088885377437186164 0.99996049616811267 -5.3245117464711273e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 0.40512274026087475 12.301487859188555 0.5881854259223428 1;
	setAttr ".sm[11]" -type "matrix" 0.99996049616811267 -0.0088885377437186337 7.7686504868642555e-017 0
		 0.0088885377437186164 0.99996049616811267 -5.3245117464711273e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 1.6207842174864149 12.716500000000002 0.032420099999999841 1;
	setAttr ".sm[12]" -type "matrix" 0.99989989043539251 -0.014149526751437356 8.0486825569771596e-017 0
		 0.014149526751437339 0.99989989043539251 -5.3203507152395223e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 4.0868290114069348 12.698237905248352 0.032420088196603795 1;
	setAttr ".sm[13]" -type "matrix" -1.1829291194997161e-015 0.99965391935284864 -0.026306682088170261 0
		 4.2938593627986796e-014 0.026306682088170264 0.99965391935284886 0 1 -8.8470897274841653e-017 -4.3225747236789631e-014 0
		 6.4502761152311603 12.664792899062167 0.032420088196603788 1;
	setAttr ".sm[14]" -type "matrix" 0.99996049616811289 0.0088885377437182833 -1.3080557290033257e-016 0
		 0.0088885377437182833 -0.99996049616811289 2.2747537872961659e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -0.40512299999999996 12.301500000000001 0.58818499999999985 1;
	setAttr ".sm[15]" -type "matrix" 0.99996049616811289 0.0088885377437182833 -1.3080557290033257e-016 0
		 0.0088885377437182833 -0.99996049616811289 2.2747537872961659e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -1.6207799999999999 12.7165 0.032420100000000063 1;
	setAttr ".sm[16]" -type "matrix" 0.99989989043539274 0.014149526751437007 -2.5048583555603365e-016 0
		 0.014149526751437007 -0.99989989043539274 2.2746534817987389e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -4.0868300000000009 12.6982 0.0324201 1;
	setAttr ".sm[17]" -type "matrix" -1.3063990685270031e-015 -0.99965391935284809 0.026306682088201791 0
		 4.300410681092003e-014 -0.026306682088201847 -0.99965391935284831 0 1.0000000000000002 -9.3675067701769556e-017 4.2926000693912566e-014 0
		 -6.4502800000000002 12.664799999999998 0.032420099999999993 1;
	setAttr ".sm[18]" -type "matrix" -2.7755575615628914e-016 0.99589320646770396 -0.090535746042518836 0
		 -2.2204460492503131e-016 -0.09053574604251885 -0.99589320646770396 0 -1.0000000000000002 -5.5511151231257827e-017 1.1102230246251565e-016 0
		 -0.79392600000000002 7.9384600000000001 -0.0087677699999999994 1;
	setAttr ".sm[19]" -type "matrix" -2.3371745768259975e-016 0.99614341334943968 0.087739956921164736 0
		 1.4533590695203183e-016 -0.087739956921164694 0.9961434133494399 0 1.0000000000000002 4.4766105491174724e-017 1.0970081802495344e-017 0
		 -0.79392599999999991 4.4609000000000005 0.30737399999999993 1;
	setAttr ".sm[20]" -type "matrix" -1.2611185544294434e-016 0.0075185844740161684 -0.99997173504430037 0
		 2.8606535729832003e-008 -0.99997173504429959 -0.0075185844740163627 0 -1 -2.8605726967513279e-008 -2.1508066452454373e-010 0
		 -0.79392600000000002 0.91799099999999934 -0.0046837299999999971 1;
	setAttr ".sm[21]" -type "matrix" 1.0000000000000002 4.7055732516436705e-016 6.8032416151445676e-016 0
		 6.7139351880062871e-016 -1.0000000000000002 2.8338269308462013e-009 0 4.3445754053683564e-016 -2.8338271270319533e-009 -1.0000000000000004 0
		 -0.79392600000000002 0.90437699999999999 1.8059100000000001 1;
	setAttr ".cs" no;
	setAttr ".hh" 0.81212103366851807;
	setAttr ".hb" 0.48727262020111084;
	setAttr ".hm" 1.4076764583587646;
	setAttr ".hf" 0.7579796314239502;
	setAttr ".his" 0.54141402244567871;
	setAttr ".hos" 0.54141402244567871;
	setAttr ".fh" 0.91799068450927734;
	setAttr ".fra" 0.55079442262649536;
	setAttr ".fma" 1.5911837816238403;
	setAttr ".ffm" 0.7579796314239502;
	setAttr ".fia" 0.54141402244567871;
	setAttr ".foa" 0.54141402244567871;
createNode hikEffector -n "MoxMotion:SpineEff" -p "MoxMotion:MoxCnt";
	setAttr ".ei" 9;
	setAttr ".radi" 0.10827248089911949;
createNode hikEffector -n "MoxMotion:LeftUpLegEff" -p "MoxMotion:MoxCnt";
	setAttr ".ei" 16;
	setAttr ".radi" 0.13265563111602577;
createNode hikEffector -n "MoxMotion:RightUpLegEff" -p "MoxMotion:MoxCnt";
	setAttr ".ei" 17;
	setAttr ".radi" 0.13265563111602577;
createNode joint -n "MoxMotion:CenterRootFK" -p "MoxMotion:MoxCnt";
	setAttr ".ra" -type "double3" -89.999999999999986 35.165043080221949 0 ;
	setAttr ".jo" -type "double3" 89.999999999999986 0 -35.165043080221949 ;
	setAttr ".typ" 1;
	setAttr ".radi" 0.5;
	setAttr ".hni" 1;
createNode joint -n "MoxMotion:LeftHipFK" -p "MoxMotion:CenterRootFK";
	setAttr ".t" -type "double3" 0.793926 -0.559328 0 ;
	setAttr ".ra" -type "double3" -84.805571092265225 89.999999999999943 0 ;
	setAttr ".jo" -type "double3" 89.999999999999957 -5.1944289077348014 -90.000000000000057 ;
	setAttr ".sd" 1;
	setAttr ".typ" 2;
	setAttr ".radi" 0.62889150314120401;
	setAttr ".hni" 2;
createNode joint -n "MoxMotion:LeftKneeFK" -p "MoxMotion:LeftHipFK";
	setAttr ".t" -type "double3" 0 -3.477562 0.316142 ;
	setAttr ".ra" -type "double3" -95.033601731876757 89.999999999999943 0 ;
	setAttr ".jo" -type "double3" 90 5.033601731876753 -89.999999999999943 ;
	setAttr ".sd" 1;
	setAttr ".typ" 3;
	setAttr ".radi" 0.63223911916956865;
	setAttr ".hni" 3;
createNode joint -n "MoxMotion:LeftFootFK" -p "MoxMotion:LeftKneeFK";
	setAttr ".t" -type "double3" 0 -3.542907 -0.312058 ;
	setAttr ".ra" -type "double3" -0.43078721700857175 89.999999999999275 0 ;
	setAttr ".jo" -type "double3" 90.000000000001265 -89.569212782991428 -90.000000000002004 ;
	setAttr ".sd" 1;
	setAttr ".typ" 4;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 4;
createNode joint -n "MoxMotion:LeftToeFK" -p "MoxMotion:LeftFootFK";
	setAttr ".t" -type "double3" 0 -0.013613500000000001 1.810592 ;
	setAttr ".jo" -type "double3" 1.5654292572889945e-015 6.810865497122292e-013 8.5054989645700135e-013 ;
	setAttr ".sd" 1;
	setAttr ".typ" 5;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 16;
createNode joint -n "MoxMotion:CenterSpineFK" -p "MoxMotion:CenterRootFK";
	setAttr ".t" -type "double3" 0 0.796236 0.063051399999999994 ;
	setAttr ".ra" -type "double3" -91.235881199475386 -89.999999999999915 0 ;
	setAttr ".jo" -type "double3" 89.999999999999943 -1.2358811994754069 90.000000000000071 ;
	setAttr ".typ" 6;
	setAttr ".radi" 0.51329628971361918;
	setAttr ".hni" 8;
createNode joint -n "MoxMotion:CenterSpineFK" -p "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK";
	setAttr ".t" -type "double3" 0 1.256769 0.027113 ;
	setAttr ".ra" -type "double3" -88.399842201361352 -89.999999999999915 0 ;
	setAttr ".jo" -type "double3" 90 1.600157798638649 89.999999999999901 ;
	setAttr ".typ" 6;
	setAttr ".radi" 0.5487940566151932;
	setAttr ".hni" 23;
createNode joint -n "MoxMotion:CenterSpineFK" -p "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK";
	setAttr ".t" -type "double3" 0 1.753213 -0.048976499999999999 ;
	setAttr ".ra" -type "double3" -88.845207647621535 -89.999999999999929 0 ;
	setAttr ".jo" -type "double3" 90 1.1547923523784855 89.999999999999915 ;
	setAttr ".typ" 6;
	setAttr ".radi" 0.53271482256405933;
	setAttr ".hni" 24;
createNode joint -n "MoxMotion:CenterNeckFK" -p "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK";
	setAttr ".t" -type "double3" 0 0.809891 -0.0163255 ;
	setAttr ".ra" -type "double3" -89.999999999999986 -89.999999999999901 0 ;
	setAttr ".jo" -type "double3" 90.000000000000014 1.1131941385122334e-014 89.999999999999915 ;
	setAttr ".typ" 7;
	setAttr ".radi" 0.5;
	setAttr ".hni" 20;
createNode joint -n "MoxMotion:CenterHeadFK" -p "MoxMotion:CenterNeckFK";
	setAttr ".t" -type "double3" 0 0.310185 0 ;
	setAttr ".jo" -type "double3" -2.3854160110976437e-014 4.4527765540489159e-014 -1.717499527990299e-013 ;
	setAttr ".typ" 8;
	setAttr ".radi" 0.56058721806697454;
	setAttr ".hni" 15;
createNode joint -n "MoxMotion:LeftCollarFK" -p "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK";
	setAttr ".t" -type "double3" 0.405123 -0.00251725 0.555765 ;
	setAttr ".ra" -type "double3" -90 -18.849284732671219 23.395906305409163 ;
	setAttr ".jo" -type "double3" 89.999999999999986 23.395906305409156 18.849284732671229 ;
	setAttr ".sd" 1;
	setAttr ".typ" 9;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 18;
createNode joint -n "MoxMotion:LeftShoulderFK" -p "MoxMotion:LeftCollarFK";
	setAttr ".t" -type "double3" 1.215661 0.415012 -0.555765 ;
	setAttr ".ra" -type "double3" -89.999999904104939 0.42429149314482911 0 ;
	setAttr ".jo" -type "double3" 89.999999904107582 5.6750757146143021e-014 -0.42429149314482639 ;
	setAttr ".sd" 1;
	setAttr ".typ" 10;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 9;
createNode joint -n "MoxMotion:LeftElbowFK" -p "MoxMotion:LeftShoulderFK";
	setAttr ".t" -type "double3" 2.466045 -0.0182621 0 ;
	setAttr ".ra" -type "double3" -89.999999904105039 0.81073521926236081 0 ;
	setAttr ".jo" -type "double3" 89.999999904114574 -7.1005059871288901e-010 -0.81073521926235803 ;
	setAttr ".sd" 1;
	setAttr ".typ" 11;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 10;
createNode joint -n "MoxMotion:LeftHandFK" -p "MoxMotion:LeftElbowFK";
	setAttr ".t" -type "double3" 2.363447 -0.033445 1.1342200000000001e-008 ;
	setAttr ".jo" -type "double3" -2.4449324123497801e-011 -2.0667806880759214e-009 
		-1.8288189368670756e-013 ;
	setAttr ".sd" 1;
	setAttr ".typ" 12;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 11;
createNode joint -n "MoxMotion:RightCollarFK" -p "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK";
	setAttr ".t" -type "double3" -0.405123 -0.0025051100000000001 0.555765 ;
	setAttr ".ra" -type "double3" 90.000000000000028 -18.848836764235756 -156.60397706143016 ;
	setAttr ".jo" -type "double3" 90.000000000000028 23.396022938569871 161.15116323576427 ;
	setAttr ".sd" 2;
	setAttr ".typ" 9;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 19;
createNode joint -n "MoxMotion:RightShoulderFK" -p "MoxMotion:RightCollarFK";
	setAttr ".t" -type "double3" -1.215657 0.415 -0.555765 ;
	setAttr ".ra" -type "double3" 90 0.42517123305030458 -180 ;
	setAttr ".jo" -type "double3" 90 -5.7331013361602903e-014 -179.57482876694971 ;
	setAttr ".sd" 2;
	setAttr ".typ" 10;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 12;
createNode joint -n "MoxMotion:RightElbowFK" -p "MoxMotion:RightShoulderFK";
	setAttr ".t" -type "double3" -2.46605 -0.0183 0 ;
	setAttr ".ra" -type "double3" 89.999999999999986 0.80964338458742602 180 ;
	setAttr ".jo" -type "double3" 90 -5.0270880063599957e-014 -179.19035661541258 ;
	setAttr ".sd" 2;
	setAttr ".typ" 11;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 13;
createNode joint -n "MoxMotion:RightHandFK" -p "MoxMotion:RightElbowFK";
	setAttr ".t" -type "double3" -2.36345 -0.0334 0 ;
	setAttr ".jo" -type "double3" -1.113194138512241e-014 5.7026351515302868e-014 -1.6571186852093898e-013 ;
	setAttr ".sd" 2;
	setAttr ".typ" 12;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 14;
createNode joint -n "MoxMotion:RightHipFK" -p "MoxMotion:CenterRootFK";
	setAttr ".t" -type "double3" -0.793926 -0.559327 1.02718e-009 ;
	setAttr ".ra" -type "double3" -84.805571879595092 89.999999999999815 0 ;
	setAttr ".jo" -type "double3" 90.000000000000227 -5.1944281204049441 -89.999999999999986 ;
	setAttr ".sd" 2;
	setAttr ".typ" 2;
	setAttr ".radi" 0.62889150314120401;
	setAttr ".hni" 5;
createNode joint -n "MoxMotion:RightKneeFK" -p "MoxMotion:RightHipFK";
	setAttr ".t" -type "double3" 0 -3.47756 0.316142 ;
	setAttr ".ra" -type "double3" -95.033594793293545 89.999999999999815 0 ;
	setAttr ".jo" -type "double3" 90 5.0335947932935463 -89.999999999999815 ;
	setAttr ".sd" 2;
	setAttr ".typ" 3;
	setAttr ".radi" 0.63223911916956865;
	setAttr ".hni" 6;
createNode joint -n "MoxMotion:RightFootFK" -p "MoxMotion:RightKneeFK";
	setAttr ".t" -type "double3" 0 -3.542909 -0.312058 ;
	setAttr ".ra" -type "double3" -0.43080345960041339 89.99999999999811 0 ;
	setAttr ".jo" -type "double3" 90.000000000006338 -89.569196540399602 -90.000000000004462 ;
	setAttr ".sd" 2;
	setAttr ".typ" 4;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 7;
createNode joint -n "MoxMotion:RightToeFK" -p "MoxMotion:RightFootFK";
	setAttr ".t" -type "double3" 0 -0.013614 1.810594 ;
	setAttr ".jo" -type "double3" 1.5902773407070625e-015 2.1411600302344007e-012 -1.669145157598674e-012 ;
	setAttr ".sd" 2;
	setAttr ".typ" 5;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 17;
createNode transform -n "MoxMotion:MoxBns" -p "MoxMotion:MOX";
createNode joint -n "MoxMotion:CenterRoot" -p "MoxMotion:MoxBns";
	setAttr ".t" -type "double3" 4.3069499042758252e-006 8.4977931976318359 -15.332584381103516 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -8.1318826439662544e-006 4.3083984538504104e-006 -3.7611401748068342e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 -35.165043080221864 ;
	setAttr ".ssc" no;
	setAttr ".typ" 1;
	setAttr ".radi" 0.5;
	setAttr ".hni" 1;
createNode joint -n "MoxMotion:LeftHip" -p "MoxMotion:CenterRoot";
	setAttr ".t" -type "double3" 0.97116958097979733 -4.588447147568786e-006 -1.5775426671638115e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -0.0001096591020758256 9.393374248616775e-006 -0.00040846823394747488 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 90 -5.1944289077348174 -54.834956919778143 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 2;
	setAttr ".radi" 0.62889150314120401;
	setAttr ".hni" 2;
createNode joint -n "MoxMotion:LeftKnee" -p "MoxMotion:LeftHip";
	setAttr ".t" -type "double3" 3.4919030773330522 -1.1112094253640237e-006 -8.3554496654869581e-007 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 0.00016651199077699082 2.9985673828918554e-005 -0.00083777660674932855 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 179.99999914622634 -1.1934888103431355e-014 -10.228030639611561 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 3;
	setAttr ".radi" 0.63223911916956865;
	setAttr ".hni" 3;
createNode joint -n "MoxMotion:LeftFoot" -p "MoxMotion:LeftKnee";
	setAttr ".t" -type "double3" 3.5566120177834835 4.3000157923245297e-007 3.4338830534608178e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 8.2442023941416349e-005 3.1422944737227757e-005 -0.0004312630995028699 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 179.99999822393914 8.510201864926018e-007 -94.602814514868143 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 4;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 4;
createNode joint -n "MoxMotion:LeftToe" -p "MoxMotion:LeftFoot";
	setAttr ".t" -type "double3" 1.8106436580060983 8.1613195079821566e-007 5.0055567065721007e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 7.8148518522929256e-009 1.4172122143529758e-005 1.7655625192201169e-031 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 63.078122409728799 89.999998092133893 63.508909580325195 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 5;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 16;
createNode transform -n "LToe" -p "MoxMotion:LeftToe";
	setAttr ".r" -type "double3" 2.1820428865188843e-006 1.7097891071468694e-010 2.6515342541105289e-008 ;
	setAttr ".s" -type "double3" 0.7 0.7 0.7 ;
createNode transform -n "Sp" -p "LToe";
createNode transform -n "LLeg" -p "MoxMotion:LeftFoot";
	setAttr ".r" -type "double3" 172.60361519691475 89.999986579858515 173.03440021824105 ;
	setAttr ".s" -type "double3" 0.99999999999999978 0.99999999999999989 0.99999999999999978 ;
createNode transform -n "Sp" -p "LLeg";
	setAttr ".r" -type "double3" 6.0929336289446476e-009 4.4295854795152757e-011 -2.6680850244805096e-008 ;
	setAttr ".s" -type "double3" 1.0000000000000004 1.0000000000000002 1.0000000000000002 ;
createNode transform -n "LKnee" -p "MoxMotion:LeftKnee";
	setAttr ".r" -type "double3" -92.306626923403527 -89.999012189933012 177.42554069415931 ;
	setAttr ".s" -type "double3" 0.8 0.8 0.8 ;
createNode transform -n "Sp1" -p "LKnee";
createNode joint -n "MoxMotion:CenterSpine" -p "MoxMotion:CenterRoot";
	setAttr ".t" -type "double3" -0.45857610357602852 0.65091556445897325 0.063049274777149833 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 8.6522751411913305e-005 8.004111677801971e-005 -6.122245231788183e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" -89.999999999997513 -1.2358811994754215 125.16504308022182 ;
	setAttr ".ssc" no;
	setAttr ".typ" 6;
	setAttr ".radi" 0.51329628971361918;
	setAttr ".hni" 8;
createNode joint -n "MoxMotion:CenterSpine" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine";
	setAttr ".t" -type "double3" 1.2570606822708468 -8.5104503000366094e-008 5.8408820358124558e-007 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -0.00018982165827194776 5.8658921332504829e-005 -0.00011251224177356617 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 180 6.5695077911180929e-014 2.6800067304112742 ;
	setAttr ".ssc" no;
	setAttr ".typ" 6;
	setAttr ".radi" 0.5487940566151932;
	setAttr ".hni" 23;
createNode joint -n "MoxMotion:CenterSpine" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine";
	setAttr ".t" -type "double3" 1.7538894741098439 -0.0047765470861342862 5.5941776366807971e-007 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 9.4189916477354052e-005 4.5645974474127104e-005 5.6248673918410057e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" -1.3419034353392711e-016 -5.314650767448497e-014 0.28933317855711838 ;
	setAttr ".ssc" no;
	setAttr ".typ" 6;
	setAttr ".radi" 0.53271482256405933;
	setAttr ".hni" 24;
createNode joint -n "MoxMotion:CenterNeck" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine";
	setAttr ".t" -type "double3" 0.81005565445707539 -6.1890769842420923e-008 -2.7347068609628877e-008 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -7.8374422880689022e-005 -9.3848013915650275e-005 -6.9094353271831343e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 1.1547923523787313 ;
	setAttr ".ssc" no;
	setAttr ".typ" 7;
	setAttr ".radi" 0.5;
	setAttr ".hni" 20;
createNode joint -n "MoxMotion:CenterHead" -p "MoxMotion:CenterNeck";
	setAttr ".t" -type "double3" 0.3101914849679126 1.6964033644484289e-006 9.5642100924942425e-008 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 6.7529569298426431e-005 1.4222294006518958e-005 5.7772466410589914e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 8.1730770987008462e-017 -2.1740692336751164e-014 -0.43078721700839556 ;
	setAttr ".ssc" no;
	setAttr ".typ" 8;
	setAttr ".radi" 0.56058721806697454;
	setAttr ".hni" 15;
createNode joint -n "MoxMotion:joint11" -p "MoxMotion:CenterHead";
	setAttr ".t" -type "double3" 2.1713528826281756 -3.7470027081099033e-015 8.2391260537731378e-016 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 90.000000000002487 -2.4848083448933725e-017 -179.56921278299149 ;
	setAttr ".ssc" no;
	setAttr ".radi" 0.56058721806697454;
createNode transform -n "Head" -p "MoxMotion:CenterHead";
	setAttr ".r" -type "double3" -88.423439471551589 -89.999914605572755 -1.145767959144316 ;
	setAttr ".s" -type "double3" 2 2 2 ;
createNode transform -n "Sp2" -p "Head";
createNode joint -n "MoxMotion:LeftCollar" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine";
	setAttr ".t" -type "double3" -0.013716776990140289 0.55560125135101046 0.40512240177940662 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -7.8845807046853345e-006 -4.9870471472186631e-005 -1.6763243113506718e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 90.000000000280536 -89.49071759502236 -178.84520764790184 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 9;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 18;
createNode joint -n "MoxMotion:LeftShoulder" -p "MoxMotion:LeftCollar";
	setAttr ".t" -type "double3" 1.2119224948654761 0.42580107454544525 -0.55576583891207321 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 0.00050274431288946332 0.2762761361456747 -0.00011612617700738526 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 10;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 9;
createNode joint -n "MoxMotion:LeftElbow" -p "MoxMotion:LeftShoulder";
	setAttr ".t" -type "double3" 2.4661062095149742 0.0036585762540948252 9.7793295594783558e-007 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -359.99908111711517 -0.56452843247462559 360 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" -1.1946893552707875e-017 4.5413740884034709e-015 -0.30145281428433718 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 11;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 10;
createNode joint -n "MoxMotion:LeftHand" -p "MoxMotion:LeftElbow";
	setAttr ".t" -type "double3" 2.3636825311307819 2.486727918693532e-006 -1.6036819552311954e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 5760.2770122148295 0.007360216030722214 5760.0038267605041 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 90.000000000002487 1.5074357587713512 90.810735219262071 ;
	setAttr ".ssc" no;
	setAttr ".sd" 1;
	setAttr ".typ" 12;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 11;
createNode transform -n "LHan" -p "MoxMotion:LeftHand";
	setAttr ".r" -type "double3" -0.18832724608273496 -89.988865329493066 -88.303949756413004 ;
	setAttr ".s" -type "double3" 1.0000000000000002 0.99999999999999989 0.99999999999999989 ;
createNode transform -n "Sp3" -p "LHan";
	setAttr ".sh" -type "double3" -4.7018140929707814e-007 0 -6.9014725656284182e-007 ;
createNode transform -n "polySurface22" -p "Sp3";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 0 -2.3141581051921216e-026 -2.2450843273299644e-026 ;
	setAttr ".s" -type "double3" 1 0.99999999999999978 1 ;
createNode transform -n "MoxMotion:Lowerarm_L_obj" -p "MoxMotion:LeftElbow";
	setAttr ".ove" yes;
	setAttr ".t" -type "double3" -0.08540317591770874 -0.09943982770781723 -0.032077659682509155 ;
	setAttr ".r" -type "double3" 90.000045366052703 0.0081686726943690363 0.81055296111366448 ;
	setAttr ".s" -type "double3" 0.10000000000000003 0.1 0.1 ;
createNode mesh -n "MoxMotion:Lowerarm_L_objShape" -p "MoxMotion:Lowerarm_L_obj";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -max 12 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".iog[0].og[0].gcl" -type "componentList" 1 "f[0:5]";
	setAttr ".ovdt" 2;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Diffuse";
	setAttr -s 24 ".vt[0:23]"  0.64454395 4.9745488 4.8500028 0.49473128 
		4.8243937 4.8500004 0.64471555 4.8245625 4.9999862 0.50575608 -4.8756299 4.8499093 
		0.6559121 -5.0254436 4.8499069 0.65574038 -4.8754611 4.9998937 24.505928 -4.9983182 
		4.849967 24.655741 -4.8481631 4.8499694 24.505756 -4.8483348 4.9999537 24.644716 
		4.8518615 4.8500605 24.49456 5.0016751 4.8500619 24.494732 4.8516893 5.0000448 24.644758 
		4.8519545 -4.8499684 24.494774 4.8517857 -4.9999552 24.494602 5.0017681 -4.8499684 
		0.64475805 4.8246589 -5.0000129 0.49477363 4.8244867 -4.8500285 0.64458632 4.9746423 
		-4.8500285 0.65578282 -4.8753657 -5.0001049 0.65595442 -5.0253515 -4.8501229 0.5057984 
		-4.8755374 -4.8501205 24.505972 -4.9982247 -4.8500633 24.5058 -4.8482385 -5.0000477 
		24.655785 -4.8480692 -4.8500605;
	setAttr -s 48 ".ed[0:47]"  16 20 0 20 3 0 
		3 1 0 1 16 0 5 8 0 8 11 0 
		11 2 0 2 5 0 10 14 0 14 17 0 
		17 0 0 0 10 0 19 21 0 21 6 0 
		6 4 0 4 19 0 23 12 0 12 9 0 
		9 7 0 7 23 0 22 18 0 18 15 0 
		15 13 0 13 22 0 1 0 0 17 16 0 
		2 1 0 3 5 0 0 2 0 11 10 0 
		4 3 0 20 19 0 5 4 0 6 8 0 
		7 6 0 21 23 0 8 7 0 9 11 0 
		10 9 0 12 14 0 13 12 0 23 22 0 
		14 13 0 15 17 0 16 15 0 18 20 0 
		19 18 0 22 21 0;
	setAttr -s 26 ".fc[0:25]" -type "polyFaces" 
		f 4 0 1 2 3 
		f 4 4 5 6 7 
		f 4 8 9 10 11 
		f 4 12 13 14 15 
		f 4 16 17 18 19 
		f 4 20 21 22 23 
		f 4 24 -11 25 -4 
		f 4 26 -3 27 -8 
		f 4 28 -7 29 -12 
		f 4 30 -2 31 -16 
		f 4 32 -15 33 -5 
		f 4 34 -14 35 -20 
		f 4 36 -19 37 -6 
		f 4 38 -18 39 -9 
		f 4 40 -17 41 -24 
		f 4 42 -23 43 -10 
		f 4 44 -22 45 -1 
		f 4 46 -21 47 -13 
		f 3 -25 -27 -29 
		f 3 -31 -33 -28 
		f 3 -35 -37 -34 
		f 3 -39 -30 -38 
		f 3 -41 -43 -40 
		f 3 -45 -26 -44 
		f 3 -47 -32 -46 
		f 3 -48 -42 -36 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".bw" 3;
createNode transform -n "LEl" -p "MoxMotion:LeftElbow";
	setAttr ".r" -type "double3" 0.00019560919500752485 0.01106171430502138 0.8106658664614379 ;
	setAttr ".s" -type "double3" 0.7 0.7 0.7 ;
createNode transform -n "Sp4" -p "LEl";
	setAttr ".sh" -type "double3" -4.7030777595513273e-007 -6.8196812786468728e-009 
		7.3198895308378728e-011 ;
createNode transform -n "LSh" -p "MoxMotion:LeftShoulder";
	setAttr ".r" -type "double3" -0.0001111125111878667 -0.010615140944240173 0.50921305098165293 ;
	setAttr ".s" -type "double3" 1.0000000000000002 0.99999999999999989 1 ;
createNode transform -n "Sp5" -p "LSh";
	setAttr ".sh" -type "double3" -4.6086252722237793e-007 -8.0717776587819312e-010 
		0 ;
createNode joint -n "MoxMotion:RightCollar" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine";
	setAttr ".t" -type "double3" -0.013702738618272647 0.55560145780264136 -0.40512996668582169 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -8.3520414683279397e-006 2.6539025932950196e-006 -1.2721497862093925e-005 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 89.999999999719464 -89.490717595022375 1.1547923526579524 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 9;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 19;
createNode joint -n "MoxMotion:RightShoulder" -p "MoxMotion:RightCollar";
	setAttr ".t" -type "double3" -1.2119162529566134 -0.42579267431943091 0.55576418162504737 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 0.00048766704338882932 0.26841567383639414 -0.00012783450563335282 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".jo" -type "double3" 8.5377364625159387e-007 -2.97693298666961e-022 2.0191537963748215e-024 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 10;
	setAttr ".radi" 0.57802454612008458;
	setAttr ".hni" 12;
createNode joint -n "MoxMotion:RightElbow" -p "MoxMotion:RightShoulder";
	setAttr ".t" -type "double3" -2.4661060148840317 -0.0036197294534332514 -4.871354017055296e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -1439.9990650041543 -0.54858704471808606 0 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 7.839950579313094e-018 -2.9802013601423822e-015 -0.30145281428433718 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 11;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 13;
createNode joint -n "MoxMotion:RightHand" -p "MoxMotion:RightElbow";
	setAttr ".t" -type "double3" -2.3636864589552875 -3.827608948370198e-005 4.8851997966892213e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -28619.719924144487 -900.00753386549889 34380.004029627962 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 90.000000000002458 1.5074357587718825 90.810735219262043 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 12;
	setAttr ".radi" 0.57053536540552197;
	setAttr ".hni" 14;
createNode transform -n "Sp14" -p "MoxMotion:RightHand";
	setAttr ".t" -type "double3" 0 -3.5527136788005009e-015 0 ;
	setAttr ".r" -type "double3" -54.8025308492197 -89.99995074681452 146.30993780558492 ;
	setAttr ".s" -type "double3" 0.99999999999999989 1 1 ;
createNode transform -n "polySurface4" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 89.999999999999986 -2.3141581051921216e-026 -2.2450843273299644e-026 ;
	setAttr ".s" -type "double3" 1 1 0.99999999999999978 ;
createNode mesh -n "polySurfaceShape4" -p "polySurface4";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[166:331]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[332:359]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "polySurface5" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 89.999999999999986 89.999999999999986 0 ;
	setAttr ".s" -type "double3" 1 1 0.99999999999999978 ;
createNode mesh -n "polySurfaceShape5" -p "polySurface5";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[166:331]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[332:359]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "polySurface22" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 0 -2.3141581051921216e-026 -2.2450843273299644e-026 ;
	setAttr ".s" -type "double3" 1 0.99999999999999978 1 ;
createNode mesh -n "polySurfaceShape22" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:RightCollar|MoxMotion:RightShoulder|MoxMotion:RightElbow|MoxMotion:RightHand|Sp14|polySurface22";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[166:331]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0;
	setAttr ".pt[332:359]" 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 
		-0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 
		0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 
		0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 
		0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 0 0 0.029999999 0 0 -0.029999999 
		0;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "polySurface10" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 89.999999973320328 -2.3141581051921216e-026 -2.2450843273299644e-026 ;
	setAttr ".s" -type "double3" 1 1 0.99999999999999978 ;
createNode mesh -n "polySurfaceShape10" -p "polySurface10";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -max 12 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.0099999998 0 0 0.0099999998 0 -0.020544423 
		-0.0099999998 0.0014366012 -0.020582044 -0.0099999998 0.00071873574 0 0.0099999998 
		0 -0.020481771 -0.0099999998 0.0021527165 0 0.0099999998 0 -0.020394163 -0.0099999998 
		0.0028662076 0 0.0099999998 0 -0.020281712 -0.0099999998 0.0035762074 0 0.0099999998 
		0 -0.020144543 -0.0099999998 0.0042818519 0 0.0099999998 0 -0.019982832 -0.0099999998 
		0.0049822778 0 0.0099999998 0 -0.019796779 -0.0099999998 0.0056766341 0 0.0099999998 
		0 -0.019586606 -0.0099999998 0.0063640736 0 0.0099999998 0 -0.019352579 -0.0099999998 
		0.0070437598 0 0.0099999998 0 -0.019094966 -0.0099999998 0.0077148639 0 0.0099999998 
		0 -0.018814096 -0.0099999998 0.0083765686 0 0.0099999998 0 -0.018510297 -0.0099999998 
		0.0090280697 0 0.0099999998 0 -0.018183941 -0.0099999998 0.0096685672 0 0.0099999998 
		0 -0.017835431 -0.0099999998 0.01029729 0 0.0099999998 0 -0.017465197 -0.0099999998 
		0.010913462 0 0.0099999998 0 -0.017073683 -0.0099999998 0.011516339 0 0.0099999998 
		0 -0.01666137 -0.0099999998 0.01210519 0 0.0099999998 0 -0.01622875 -0.0099999998 
		0.012679292 0 0.0099999998 0 -0.01577636 -0.0099999998 0.013237939 0 0.0099999998 
		0 -0.015304753 -0.0099999998 0.013780462 0 0.0099999998 0 -0.014814507 -0.0099999998 
		0.014306194 0 0.0099999998 0 -0.014306211 -0.0099999998 0.014814497 0 0.0099999998 
		0 -0.013780475 -0.0099999998 0.015304753 0 0.0099999998 0 -0.013237954 -0.0099999998 
		0.015776364 0 0.0099999998 0 -0.012679301 -0.0099999998 0.016228748 0 0.0099999998 
		0 -0.0121052 -0.0099999998 0.016661361 0 0.0099999998 0 -0.011516348 -0.0099999998 
		0.017073676 0 0.0099999998 0 -0.010913474 -0.0099999998 0.017465191 0 0.0099999998 
		0 -0.010297292 -0.0099999998 0.017835425 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		0.018183932 0 0.0099999998 0 -0.009028065 -0.0099999998 0.018510282 0 0.0099999998 
		0 -0.0083765695 -0.0099999998 0.018814081 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		0.019094959 0 0.0099999998 0 -0.007043757 -0.0099999998 0.01935257 0 0.0099999998 
		0 -0.0063640689 -0.0099999998 0.019586606 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		0.019796776 0 0.0099999998 0 -0.0049822717 -0.0099999998 0.019982828 0 0.0099999998 
		0 -0.0042818524 -0.0099999998 0.020144535 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		0.020281695 0 0.0099999998 0 -0.0028662051 -0.0099999998 0.020394148 0 0.0099999998 
		0 -0.0021527156 -0.0099999998 0.020481752 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		0.020544408 0 0.0099999998 0 -0.00071872404 -0.0099999998 0.020582028 0 0.0099999998 
		0 9.8202451e-009 -0.0099999998 0.020594569 0 0.0099999998 0 0.00071874366 -0.0099999998 
		0.020582026 0 0.0099999998 0 0.0014366135 -0.0099999998 0.020544404 0 0.0099999998 
		0 0.0021527254 -0.0099999998 0.02048175 0 0.0099999998 0 0.0028662151 -0.0099999998 
		0.020394145 0 0.0099999998 0 0.0035762191 -0.0099999998 0.020281689 0 0.0099999998 
		0 0.0042818626 -0.0099999998 0.020144528 0 0.0099999998 0 0.0049822815 -0.0099999998 
		0.019982822 0 0.0099999998 0 0.0056766314 -0.0099999998 0.019796772 0 0.0099999998 
		0 0.0063640778 -0.0099999998 0.019586597 0 0.0099999998 0 0.0070437673 -0.0099999998 
		0.019352563 0 0.0099999998 0 0.0077148722 -0.0099999998 0.019094951 0 0.0099999998 
		0 0.0083765695 -0.0099999998 0.018814072 0 0.0099999998 0 0.0090280846 -0.0099999998 
		0.018510271 0 0.0099999998 0 0.0096685812 -0.0099999998 0.018183919 0 0.0099999998 
		0 0.010297292 -0.0099999998 0.017835416 0 0.0099999998 0 0.010913474 -0.0099999998 
		0.017465182 0 0.0099999998 0 0.011516348 -0.0099999998 0.01707367 0 0.0099999998 
		0 0.01210519 -0.0099999998 0.016661352 0 0.0099999998 0 0.012679292 -0.0099999998 
		0.016228735 0 0.0099999998 0 0.013237936 -0.0099999998 0.015776353 0 0.0099999998 
		0 0.013780454 -0.0099999998 0.015304745 0 0.0099999998 0 0.014306202 -0.0099999998 
		0.014814489 0 0.0099999998 0 0.014814507 -0.0099999998 0.01430618 0 0.0099999998 
		0 0.015304753 -0.0099999998 0.013780446 0 0.0099999998 0 0.015776351 -0.0099999998 
		0.013237924 0 0.0099999998 0 0.01622875 -0.0099999998 0.012679273 0 0.0099999998 
		0 0.01666137 -0.0099999998 0.012105175 0 0.0099999998 0 0.017073683 -0.0099999998 
		0.011516329 0 0.0099999998 0 0.017465197 -0.0099999998 0.010913447 0 0.0099999998 
		0 0.017835431 -0.0099999998 0.010297275 0 0.0099999998 0 0.018183932 -0.0099999998 
		0.0096685542 0 0.0099999998 0 0.018510288 -0.0099999998 0.0090280538 0 0.0099999998 
		0 0.018814087 -0.0099999998 0.0083765527 0 0.0099999998 0 0.019094957 -0.0099999998 
		0.0077148476 0 0.0099999998 0 0.019352579 -0.0099999998 0.0070437454 0 0.0099999998 
		0 0.019586615 -0.0099999998 0.006364061 0 0.0099999998 0 0.019796779 -0.0099999998 
		0.0056766197 0 0.0099999998 0 0.019982813 -0.0099999998 0.0049822633;
	setAttr ".pt[166:331]" 0 0.0099999998 0 0.020144535 -0.0099999998 0.0042818389 
		0 0.0099999998 0 0.020281693 -0.0099999998 0.0035761963 0 0.0099999998 0 0.020394145 
		-0.0099999998 0.0028661957 0 0.0099999998 0 0.02048175 -0.0099999998 0.0021527046 
		0 0.0099999998 0 0.020544423 -0.0099999998 0.0014365911 0 0.0099999998 0 0.020582026 
		-0.0099999998 0.00071872625 0 0.0099999998 0 0.020594554 -0.0099999998 -1.4200041e-008 
		0 0.0099999998 0 0.020582026 -0.0099999998 -0.00071875472 0 0.0099999998 0 0.020544423 
		-0.0099999998 -0.0014366197 0 0.0099999998 0 0.020481741 -0.0099999998 -0.0021527326 
		0 0.0099999998 0 0.020394124 -0.0099999998 -0.0028662232 0 0.0099999998 0 0.020281682 
		-0.0099999998 -0.0035762237 0 0.0099999998 0 0.020144535 -0.0099999998 -0.0042818668 
		0 0.0099999998 0 0.019982824 -0.0099999998 -0.0049822913 0 0.0099999998 0 0.019796768 
		-0.0099999998 -0.0056766467 0 0.0099999998 0 0.019586595 -0.0099999998 -0.0063640852 
		0 0.0099999998 0 0.019352559 -0.0099999998 -0.007043771 0 0.0099999998 0 0.019094957 
		-0.0099999998 -0.0077148755 0 0.0099999998 0 0.018814074 -0.0099999998 -0.0083765807 
		0 0.0099999998 0 0.01851028 -0.0099999998 -0.0090280781 0 0.0099999998 0 0.018183911 
		-0.0099999998 -0.0096685803 0 0.0099999998 0 0.01783541 -0.0099999998 -0.010297298 
		0 0.0099999998 0 0.017465187 -0.0099999998 -0.010913473 0 0.0099999998 0 0.017073683 
		-0.0099999998 -0.011516354 0 0.0099999998 0 0.016661352 -0.0099999998 -0.012105198 
		0 0.0099999998 0 0.016228737 -0.0099999998 -0.012679295 0 0.0099999998 0 0.015776342 
		-0.0099999998 -0.013237947 0 0.0099999998 0 0.015304744 -0.0099999998 -0.013780468 
		0 0.0099999998 0 0.014814488 -0.0099999998 -0.014306203 0 0.0099999998 0 0.014306189 
		-0.0099999998 -0.014814504 0 0.0099999998 0 0.013780454 -0.0099999998 -0.015304754 
		0 0.0099999998 0 0.013237924 -0.0099999998 -0.015776364 0 0.0099999998 0 0.012679281 
		-0.0099999998 -0.016228752 0 0.0099999998 0 0.012105181 -0.0099999998 -0.016661363 
		0 0.0099999998 0 0.011516329 -0.0099999998 -0.017073678 0 0.0099999998 0 0.010913454 
		-0.0099999998 -0.017465195 0 0.0099999998 0 0.010297283 -0.0099999998 -0.017835427 
		0 0.0099999998 0 0.0096685709 -0.0099999998 -0.01818393 0 0.0099999998 0 0.0090280557 
		-0.0099999998 -0.018510282 0 0.0099999998 0 0.0083765509 -0.0099999998 -0.018814085 
		0 0.0099999998 0 0.0077148527 -0.0099999998 -0.019094957 0 0.0099999998 0 0.0070437482 
		-0.0099999998 -0.019352568 0 0.0099999998 0 0.0063640689 -0.0099999998 -0.019586606 
		0 0.0099999998 0 0.0056766314 -0.0099999998 -0.019796776 0 0.0099999998 0 0.0049822717 
		-0.0099999998 -0.019982828 0 0.0099999998 0 0.0042818426 -0.0099999998 -0.020144535 
		0 0.0099999998 0 0.0035761991 -0.0099999998 -0.020281695 0 0.0099999998 0 0.0028662051 
		-0.0099999998 -0.020394148 0 0.0099999998 0 0.0021527156 -0.0099999998 -0.020481752 
		0 0.0099999998 0 0.0014366035 -0.0099999998 -0.020544404 0 0.0099999998 0 0.00071873382 
		-0.0099999998 -0.020582028 0 0.0099999998 0 0 -0.0099999998 -0.020594569 0 0.0099999998 
		0 -0.00071873382 -0.0099999998 -0.020582026 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		-0.020544404 0 0.0099999998 0 -0.0021527254 -0.0099999998 -0.020481752 0 0.0099999998 
		0 -0.0028662151 -0.0099999998 -0.020394145 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		-0.020281693 0 0.0099999998 0 -0.0042818524 -0.0099999998 -0.02014453 0 0.0099999998 
		0 -0.0049822815 -0.0099999998 -0.01998282 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		-0.019796772 0 0.0099999998 0 -0.0063640587 -0.0099999998 -0.019586599 0 0.0099999998 
		0 -0.007043757 -0.0099999998 -0.019352563 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		-0.01909495 0 0.0099999998 0 -0.0083765611 -0.0099999998 -0.018814074 0 0.0099999998 
		0 -0.009028065 -0.0099999998 -0.018510275 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		-0.018183921 0 0.0099999998 0 -0.010297283 -0.0099999998 -0.017835416 0 0.0099999998 
		0 -0.010913454 -0.0099999998 -0.01746518 0 0.0099999998 0 -0.011516329 -0.0099999998 
		-0.017073667 0 0.0099999998 0 -0.012105181 -0.0099999998 -0.016661353 0 0.0099999998 
		0 -0.012679271 -0.0099999998 -0.016228737 0 0.0099999998 0 -0.013237924 -0.0099999998 
		-0.015776351 0 0.0099999998 0 -0.013780445 -0.0099999998 -0.015304743 0 0.0099999998 
		0 -0.014306181 -0.0099999998 -0.014814489 0 0.0099999998 0 -0.014814488 -0.0099999998 
		-0.014306187 0 0.0099999998 0 -0.015304735 -0.0099999998 -0.013780452 0 0.0099999998 
		0 -0.015776342 -0.0099999998 -0.013237932 0 0.0099999998 0 -0.01622873 -0.0099999998 
		-0.012679281 0 0.0099999998 0 -0.016661342 -0.0099999998 -0.012105183 0 0.0099999998 
		0 -0.017073654 -0.0099999998 -0.011516336 0 0.0099999998 0 -0.017465167 -0.0099999998 
		-0.010913458 0 0.0099999998 0 -0.017835401 -0.0099999998 -0.010297284 0 0.0099999998 
		0 -0.018183911 -0.0099999998 -0.0096685654;
	setAttr ".pt[332:359]" 0 0.0099999998 0 -0.018510258 -0.0099999998 -0.0090280669 
		0 0.0099999998 0 -0.018814066 -0.0099999998 -0.0083765676 0 0.0099999998 0 -0.019094935 
		-0.0099999998 -0.0077148639 0 0.0099999998 0 -0.01935254 -0.0099999998 -0.0070437607 
		0 0.0099999998 0 -0.019586576 -0.0099999998 -0.0063640764 0 0.0099999998 0 -0.01979675 
		-0.0099999998 -0.0056766379 0 0.0099999998 0 -0.019982802 -0.0099999998 -0.0049822819 
		0 0.0099999998 0 -0.020144505 -0.0099999998 -0.0042818584 0 0.0099999998 0 -0.020281672 
		-0.0099999998 -0.0035762175 0 0.0099999998 0 -0.020394124 -0.0099999998 -0.0028662186 
		0 0.0099999998 0 -0.020481732 -0.0099999998 -0.0021527279 0 0.0099999998 0 -0.020544384 
		-0.0099999998 -0.0014366142 0 0.0099999998 0 -0.020581996 -0.0099999998 -0.00071875029 
		0 0.0099999998 0 -0.020594554 -0.0099999998 -1.0959254e-008;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "polySurface11" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" -2.3141581051921216e-026 0 89.999999999999986 ;
	setAttr ".s" -type "double3" 0.99999999999999978 1 1 ;
createNode mesh -n "polySurfaceShape11" -p "polySurface11";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -max 12 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.0099999998 0 0 0.0099999998 0 -0.020544423 
		-0.0099999998 0.0014366012 -0.020582044 -0.0099999998 0.00071873574 0 0.0099999998 
		0 -0.020481771 -0.0099999998 0.0021527165 0 0.0099999998 0 -0.020394163 -0.0099999998 
		0.0028662076 0 0.0099999998 0 -0.020281712 -0.0099999998 0.0035762074 0 0.0099999998 
		0 -0.020144543 -0.0099999998 0.0042818519 0 0.0099999998 0 -0.019982832 -0.0099999998 
		0.0049822778 0 0.0099999998 0 -0.019796779 -0.0099999998 0.0056766341 0 0.0099999998 
		0 -0.019586606 -0.0099999998 0.0063640736 0 0.0099999998 0 -0.019352579 -0.0099999998 
		0.0070437598 0 0.0099999998 0 -0.019094966 -0.0099999998 0.0077148639 0 0.0099999998 
		0 -0.018814096 -0.0099999998 0.0083765686 0 0.0099999998 0 -0.018510297 -0.0099999998 
		0.0090280697 0 0.0099999998 0 -0.018183941 -0.0099999998 0.0096685672 0 0.0099999998 
		0 -0.017835431 -0.0099999998 0.01029729 0 0.0099999998 0 -0.017465197 -0.0099999998 
		0.010913462 0 0.0099999998 0 -0.017073683 -0.0099999998 0.011516339 0 0.0099999998 
		0 -0.01666137 -0.0099999998 0.01210519 0 0.0099999998 0 -0.01622875 -0.0099999998 
		0.012679292 0 0.0099999998 0 -0.01577636 -0.0099999998 0.013237939 0 0.0099999998 
		0 -0.015304753 -0.0099999998 0.013780462 0 0.0099999998 0 -0.014814507 -0.0099999998 
		0.014306194 0 0.0099999998 0 -0.014306211 -0.0099999998 0.014814497 0 0.0099999998 
		0 -0.013780475 -0.0099999998 0.015304753 0 0.0099999998 0 -0.013237954 -0.0099999998 
		0.015776364 0 0.0099999998 0 -0.012679301 -0.0099999998 0.016228748 0 0.0099999998 
		0 -0.0121052 -0.0099999998 0.016661361 0 0.0099999998 0 -0.011516348 -0.0099999998 
		0.017073676 0 0.0099999998 0 -0.010913474 -0.0099999998 0.017465191 0 0.0099999998 
		0 -0.010297292 -0.0099999998 0.017835425 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		0.018183932 0 0.0099999998 0 -0.009028065 -0.0099999998 0.018510282 0 0.0099999998 
		0 -0.0083765695 -0.0099999998 0.018814081 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		0.019094959 0 0.0099999998 0 -0.007043757 -0.0099999998 0.01935257 0 0.0099999998 
		0 -0.0063640689 -0.0099999998 0.019586606 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		0.019796776 0 0.0099999998 0 -0.0049822717 -0.0099999998 0.019982828 0 0.0099999998 
		0 -0.0042818524 -0.0099999998 0.020144535 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		0.020281695 0 0.0099999998 0 -0.0028662051 -0.0099999998 0.020394148 0 0.0099999998 
		0 -0.0021527156 -0.0099999998 0.020481752 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		0.020544408 0 0.0099999998 0 -0.00071872404 -0.0099999998 0.020582028 0 0.0099999998 
		0 9.8202451e-009 -0.0099999998 0.020594569 0 0.0099999998 0 0.00071874366 -0.0099999998 
		0.020582026 0 0.0099999998 0 0.0014366135 -0.0099999998 0.020544404 0 0.0099999998 
		0 0.0021527254 -0.0099999998 0.02048175 0 0.0099999998 0 0.0028662151 -0.0099999998 
		0.020394145 0 0.0099999998 0 0.0035762191 -0.0099999998 0.020281689 0 0.0099999998 
		0 0.0042818626 -0.0099999998 0.020144528 0 0.0099999998 0 0.0049822815 -0.0099999998 
		0.019982822 0 0.0099999998 0 0.0056766314 -0.0099999998 0.019796772 0 0.0099999998 
		0 0.0063640778 -0.0099999998 0.019586597 0 0.0099999998 0 0.0070437673 -0.0099999998 
		0.019352563 0 0.0099999998 0 0.0077148722 -0.0099999998 0.019094951 0 0.0099999998 
		0 0.0083765695 -0.0099999998 0.018814072 0 0.0099999998 0 0.0090280846 -0.0099999998 
		0.018510271 0 0.0099999998 0 0.0096685812 -0.0099999998 0.018183919 0 0.0099999998 
		0 0.010297292 -0.0099999998 0.017835416 0 0.0099999998 0 0.010913474 -0.0099999998 
		0.017465182 0 0.0099999998 0 0.011516348 -0.0099999998 0.01707367 0 0.0099999998 
		0 0.01210519 -0.0099999998 0.016661352 0 0.0099999998 0 0.012679292 -0.0099999998 
		0.016228735 0 0.0099999998 0 0.013237936 -0.0099999998 0.015776353 0 0.0099999998 
		0 0.013780454 -0.0099999998 0.015304745 0 0.0099999998 0 0.014306202 -0.0099999998 
		0.014814489 0 0.0099999998 0 0.014814507 -0.0099999998 0.01430618 0 0.0099999998 
		0 0.015304753 -0.0099999998 0.013780446 0 0.0099999998 0 0.015776351 -0.0099999998 
		0.013237924 0 0.0099999998 0 0.01622875 -0.0099999998 0.012679273 0 0.0099999998 
		0 0.01666137 -0.0099999998 0.012105175 0 0.0099999998 0 0.017073683 -0.0099999998 
		0.011516329 0 0.0099999998 0 0.017465197 -0.0099999998 0.010913447 0 0.0099999998 
		0 0.017835431 -0.0099999998 0.010297275 0 0.0099999998 0 0.018183932 -0.0099999998 
		0.0096685542 0 0.0099999998 0 0.018510288 -0.0099999998 0.0090280538 0 0.0099999998 
		0 0.018814087 -0.0099999998 0.0083765527 0 0.0099999998 0 0.019094957 -0.0099999998 
		0.0077148476 0 0.0099999998 0 0.019352579 -0.0099999998 0.0070437454 0 0.0099999998 
		0 0.019586615 -0.0099999998 0.006364061 0 0.0099999998 0 0.019796779 -0.0099999998 
		0.0056766197 0 0.0099999998 0 0.019982813 -0.0099999998 0.0049822633;
	setAttr ".pt[166:331]" 0 0.0099999998 0 0.020144535 -0.0099999998 0.0042818389 
		0 0.0099999998 0 0.020281693 -0.0099999998 0.0035761963 0 0.0099999998 0 0.020394145 
		-0.0099999998 0.0028661957 0 0.0099999998 0 0.02048175 -0.0099999998 0.0021527046 
		0 0.0099999998 0 0.020544423 -0.0099999998 0.0014365911 0 0.0099999998 0 0.020582026 
		-0.0099999998 0.00071872625 0 0.0099999998 0 0.020594554 -0.0099999998 -1.4200041e-008 
		0 0.0099999998 0 0.020582026 -0.0099999998 -0.00071875472 0 0.0099999998 0 0.020544423 
		-0.0099999998 -0.0014366197 0 0.0099999998 0 0.020481741 -0.0099999998 -0.0021527326 
		0 0.0099999998 0 0.020394124 -0.0099999998 -0.0028662232 0 0.0099999998 0 0.020281682 
		-0.0099999998 -0.0035762237 0 0.0099999998 0 0.020144535 -0.0099999998 -0.0042818668 
		0 0.0099999998 0 0.019982824 -0.0099999998 -0.0049822913 0 0.0099999998 0 0.019796768 
		-0.0099999998 -0.0056766467 0 0.0099999998 0 0.019586595 -0.0099999998 -0.0063640852 
		0 0.0099999998 0 0.019352559 -0.0099999998 -0.007043771 0 0.0099999998 0 0.019094957 
		-0.0099999998 -0.0077148755 0 0.0099999998 0 0.018814074 -0.0099999998 -0.0083765807 
		0 0.0099999998 0 0.01851028 -0.0099999998 -0.0090280781 0 0.0099999998 0 0.018183911 
		-0.0099999998 -0.0096685803 0 0.0099999998 0 0.01783541 -0.0099999998 -0.010297298 
		0 0.0099999998 0 0.017465187 -0.0099999998 -0.010913473 0 0.0099999998 0 0.017073683 
		-0.0099999998 -0.011516354 0 0.0099999998 0 0.016661352 -0.0099999998 -0.012105198 
		0 0.0099999998 0 0.016228737 -0.0099999998 -0.012679295 0 0.0099999998 0 0.015776342 
		-0.0099999998 -0.013237947 0 0.0099999998 0 0.015304744 -0.0099999998 -0.013780468 
		0 0.0099999998 0 0.014814488 -0.0099999998 -0.014306203 0 0.0099999998 0 0.014306189 
		-0.0099999998 -0.014814504 0 0.0099999998 0 0.013780454 -0.0099999998 -0.015304754 
		0 0.0099999998 0 0.013237924 -0.0099999998 -0.015776364 0 0.0099999998 0 0.012679281 
		-0.0099999998 -0.016228752 0 0.0099999998 0 0.012105181 -0.0099999998 -0.016661363 
		0 0.0099999998 0 0.011516329 -0.0099999998 -0.017073678 0 0.0099999998 0 0.010913454 
		-0.0099999998 -0.017465195 0 0.0099999998 0 0.010297283 -0.0099999998 -0.017835427 
		0 0.0099999998 0 0.0096685709 -0.0099999998 -0.01818393 0 0.0099999998 0 0.0090280557 
		-0.0099999998 -0.018510282 0 0.0099999998 0 0.0083765509 -0.0099999998 -0.018814085 
		0 0.0099999998 0 0.0077148527 -0.0099999998 -0.019094957 0 0.0099999998 0 0.0070437482 
		-0.0099999998 -0.019352568 0 0.0099999998 0 0.0063640689 -0.0099999998 -0.019586606 
		0 0.0099999998 0 0.0056766314 -0.0099999998 -0.019796776 0 0.0099999998 0 0.0049822717 
		-0.0099999998 -0.019982828 0 0.0099999998 0 0.0042818426 -0.0099999998 -0.020144535 
		0 0.0099999998 0 0.0035761991 -0.0099999998 -0.020281695 0 0.0099999998 0 0.0028662051 
		-0.0099999998 -0.020394148 0 0.0099999998 0 0.0021527156 -0.0099999998 -0.020481752 
		0 0.0099999998 0 0.0014366035 -0.0099999998 -0.020544404 0 0.0099999998 0 0.00071873382 
		-0.0099999998 -0.020582028 0 0.0099999998 0 0 -0.0099999998 -0.020594569 0 0.0099999998 
		0 -0.00071873382 -0.0099999998 -0.020582026 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		-0.020544404 0 0.0099999998 0 -0.0021527254 -0.0099999998 -0.020481752 0 0.0099999998 
		0 -0.0028662151 -0.0099999998 -0.020394145 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		-0.020281693 0 0.0099999998 0 -0.0042818524 -0.0099999998 -0.02014453 0 0.0099999998 
		0 -0.0049822815 -0.0099999998 -0.01998282 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		-0.019796772 0 0.0099999998 0 -0.0063640587 -0.0099999998 -0.019586599 0 0.0099999998 
		0 -0.007043757 -0.0099999998 -0.019352563 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		-0.01909495 0 0.0099999998 0 -0.0083765611 -0.0099999998 -0.018814074 0 0.0099999998 
		0 -0.009028065 -0.0099999998 -0.018510275 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		-0.018183921 0 0.0099999998 0 -0.010297283 -0.0099999998 -0.017835416 0 0.0099999998 
		0 -0.010913454 -0.0099999998 -0.01746518 0 0.0099999998 0 -0.011516329 -0.0099999998 
		-0.017073667 0 0.0099999998 0 -0.012105181 -0.0099999998 -0.016661353 0 0.0099999998 
		0 -0.012679271 -0.0099999998 -0.016228737 0 0.0099999998 0 -0.013237924 -0.0099999998 
		-0.015776351 0 0.0099999998 0 -0.013780445 -0.0099999998 -0.015304743 0 0.0099999998 
		0 -0.014306181 -0.0099999998 -0.014814489 0 0.0099999998 0 -0.014814488 -0.0099999998 
		-0.014306187 0 0.0099999998 0 -0.015304735 -0.0099999998 -0.013780452 0 0.0099999998 
		0 -0.015776342 -0.0099999998 -0.013237932 0 0.0099999998 0 -0.01622873 -0.0099999998 
		-0.012679281 0 0.0099999998 0 -0.016661342 -0.0099999998 -0.012105183 0 0.0099999998 
		0 -0.017073654 -0.0099999998 -0.011516336 0 0.0099999998 0 -0.017465167 -0.0099999998 
		-0.010913458 0 0.0099999998 0 -0.017835401 -0.0099999998 -0.010297284 0 0.0099999998 
		0 -0.018183911 -0.0099999998 -0.0096685654;
	setAttr ".pt[332:359]" 0 0.0099999998 0 -0.018510258 -0.0099999998 -0.0090280669 
		0 0.0099999998 0 -0.018814066 -0.0099999998 -0.0083765676 0 0.0099999998 0 -0.019094935 
		-0.0099999998 -0.0077148639 0 0.0099999998 0 -0.01935254 -0.0099999998 -0.0070437607 
		0 0.0099999998 0 -0.019586576 -0.0099999998 -0.0063640764 0 0.0099999998 0 -0.01979675 
		-0.0099999998 -0.0056766379 0 0.0099999998 0 -0.019982802 -0.0099999998 -0.0049822819 
		0 0.0099999998 0 -0.020144505 -0.0099999998 -0.0042818584 0 0.0099999998 0 -0.020281672 
		-0.0099999998 -0.0035762175 0 0.0099999998 0 -0.020394124 -0.0099999998 -0.0028662186 
		0 0.0099999998 0 -0.020481732 -0.0099999998 -0.0021527279 0 0.0099999998 0 -0.020544384 
		-0.0099999998 -0.0014366142 0 0.0099999998 0 -0.020581996 -0.0099999998 -0.00071875029 
		0 0.0099999998 0 -0.020594554 -0.0099999998 -1.0959254e-008;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "polySurface23" -p "Sp14";
	setAttr ".t" -type "double3" 0 -2.2204460492503131e-016 4.4408920985006262e-016 ;
	setAttr ".r" -type "double3" 0 -2.3141581051921216e-026 -2.2450843273299644e-026 ;
	setAttr ".s" -type "double3" 1 0.99999999999999978 1 ;
createNode mesh -n "polySurfaceShape23" -p "polySurface23";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -max 12 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".csh" no;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 362 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.375 0.3125 0.37638888 0.3125 
		0.37638888 0.68843985 0.375 0.68843985 0.37777776 0.3125 0.37777776 0.68843985 0.37916663 
		0.3125 0.37916663 0.68843985 0.38055551 0.3125 0.38055551 0.68843985 0.38194439 0.3125 
		0.38194439 0.68843985 0.38333327 0.3125 0.38333327 0.68843985 0.38472214 0.3125 0.38472214 
		0.68843985 0.38611102 0.3125 0.38611102 0.68843985 0.3874999 0.3125 0.3874999 0.68843985 
		0.38888878 0.3125 0.38888878 0.68843985 0.39027765 0.3125 0.39027765 0.68843985 0.39166653 
		0.3125 0.39166653 0.68843985 0.39305541 0.3125 0.39305541 0.68843985 0.39444429 0.3125 
		0.39444429 0.68843985 0.39583316 0.3125 0.39583316 0.68843985 0.39722204 0.3125 0.39722204 
		0.68843985 0.39861092 0.3125 0.39861092 0.68843985 0.3999998 0.3125 0.3999998 0.68843985 
		0.40138867 0.3125 0.40138867 0.68843985 0.40277755 0.3125 0.40277755 0.68843985 0.40416643 
		0.3125 0.40416643 0.68843985 0.40555531 0.3125 0.40555531 0.68843985 0.40694419 0.3125 
		0.40694419 0.68843985 0.40833306 0.3125 0.40833306 0.68843985 0.40972194 0.3125 0.40972194 
		0.68843985 0.41111082 0.3125 0.41111082 0.68843985 0.4124997 0.3125 0.4124997 0.68843985 
		0.41388857 0.3125 0.41388857 0.68843985 0.41527745 0.3125 0.41527745 0.68843985 0.41666633 
		0.3125 0.41666633 0.68843985 0.41805521 0.3125 0.41805521 0.68843985 0.41944408 0.3125 
		0.41944408 0.68843985 0.42083296 0.3125 0.42083296 0.68843985 0.42222184 0.3125 0.42222184 
		0.68843985 0.42361072 0.3125 0.42361072 0.68843985 0.42499959 0.3125 0.42499959 0.68843985 
		0.42638847 0.3125 0.42638847 0.68843985 0.42777735 0.3125 0.42777735 0.68843985 0.42916623 
		0.3125 0.42916623 0.68843985 0.43055511 0.3125 0.43055511 0.68843985 0.43194398 0.3125 
		0.43194398 0.68843985 0.43333286 0.3125 0.43333286 0.68843985 0.43472174 0.3125 0.43472174 
		0.68843985 0.43611062 0.3125 0.43611062 0.68843985 0.43749949 0.3125 0.43749949 0.68843985 
		0.43888837 0.3125 0.43888837 0.68843985 0.44027725 0.3125 0.44027725 0.68843985 0.44166613 
		0.3125 0.44166613 0.68843985 0.443055 0.3125 0.443055 0.68843985 0.44444388 0.3125 
		0.44444388 0.68843985 0.44583276 0.3125 0.44583276 0.68843985 0.44722164 0.3125 0.44722164 
		0.68843985 0.44861051 0.3125 0.44861051 0.68843985 0.44999939 0.3125 0.44999939 0.68843985 
		0.45138827 0.3125 0.45138827 0.68843985 0.45277715 0.3125 0.45277715 0.68843985 0.45416602 
		0.3125 0.45416602 0.68843985 0.4555549 0.3125 0.4555549 0.68843985 0.45694378 0.3125 
		0.45694378 0.68843985 0.45833266 0.3125 0.45833266 0.68843985 0.45972154 0.3125 0.45972154 
		0.68843985 0.46111041 0.3125 0.46111041 0.68843985 0.46249929 0.3125 0.46249929 0.68843985 
		0.46388817 0.3125 0.46388817 0.68843985 0.46527705 0.3125 0.46527705 0.68843985 0.46666592 
		0.3125 0.46666592 0.68843985 0.4680548 0.3125 0.4680548 0.68843985 0.46944368 0.3125 
		0.46944368 0.68843985 0.47083256 0.3125 0.47083256 0.68843985 0.47222143 0.3125 0.47222143 
		0.68843985 0.47361031 0.3125 0.47361031 0.68843985 0.47499919 0.3125 0.47499919 0.68843985 
		0.47638807 0.3125 0.47638807 0.68843985 0.47777694 0.3125 0.47777694 0.68843985 0.47916582 
		0.3125 0.47916582 0.68843985 0.4805547 0.3125 0.4805547 0.68843985 0.48194358 0.3125 
		0.48194358 0.68843985 0.48333246 0.3125 0.48333246 0.68843985 0.48472133 0.3125 0.48472133 
		0.68843985 0.48611021 0.3125 0.48611021 0.68843985 0.48749909 0.3125 0.48749909 0.68843985 
		0.48888797 0.3125 0.48888797 0.68843985 0.49027684 0.3125 0.49027684 0.68843985 0.49166572 
		0.3125 0.49166572 0.68843985 0.4930546 0.3125 0.4930546 0.68843985 0.49444348 0.3125 
		0.49444348 0.68843985 0.49583235 0.3125 0.49583235 0.68843985 0.49722123 0.3125 0.49722123 
		0.68843985 0.49861011 0.3125 0.49861011 0.68843985 0.49999899 0.3125 0.49999899 0.68843985 
		0.50138789 0.3125 0.50138789 0.68843985 0.5027768 0.3125 0.5027768 0.68843985 0.50416571 
		0.3125 0.50416571 0.68843985 0.50555462 0.3125 0.50555462 0.68843985 0.50694352 0.3125 
		0.50694352 0.68843985 0.50833243 0.3125 0.50833243 0.68843985 0.50972134 0.3125 0.50972134 
		0.68843985 0.51111025 0.3125 0.51111025 0.68843985 0.51249915 0.3125 0.51249915 0.68843985 
		0.51388806 0.3125 0.51388806 0.68843985 0.51527697 0.3125 0.51527697 0.68843985 0.51666588 
		0.3125 0.51666588 0.68843985 0.51805478 0.3125 0.51805478 0.68843985 0.51944369 0.3125 
		0.51944369 0.68843985 0.5208326 0.3125 0.5208326 0.68843985 0.52222151 0.3125 0.52222151 
		0.68843985 0.52361041 0.3125 0.52361041 0.68843985 0.52499932 0.3125 0.52499932 0.68843985 
		0.52638823 0.3125 0.52638823 0.68843985 0.52777714 0.3125 0.52777714 0.68843985 0.52916604 
		0.3125 0.52916604 0.68843985 0.53055495 0.3125 0.53055495 0.68843985 0.53194386 0.3125 
		0.53194386 0.68843985 0.53333277 0.3125 0.53333277 0.68843985 0.53472167 0.3125 0.53472167 
		0.68843985 0.53611058 0.3125 0.53611058 0.68843985 0.53749949 0.3125 0.53749949 0.68843985 
		0.53888839 0.3125 0.53888839 0.68843985 0.5402773 0.3125 0.5402773 0.68843985 0.54166621 
		0.3125 0.54166621 0.68843985 0.54305512 0.3125 0.54305512 0.68843985 0.54444402 0.3125 
		0.54444402 0.68843985 0.54583293 0.3125 0.54583293 0.68843985 0.54722184 0.3125 0.54722184 
		0.68843985;
	setAttr ".uvst[0].uvsp[250:361]" 0.54861075 0.3125 0.54861075 0.68843985 0.54999965 
		0.3125 0.54999965 0.68843985 0.55138856 0.3125 0.55138856 0.68843985 0.55277747 0.3125 
		0.55277747 0.68843985 0.55416638 0.3125 0.55416638 0.68843985 0.55555528 0.3125 0.55555528 
		0.68843985 0.55694419 0.3125 0.55694419 0.68843985 0.5583331 0.3125 0.5583331 0.68843985 
		0.55972201 0.3125 0.55972201 0.68843985 0.56111091 0.3125 0.56111091 0.68843985 0.56249982 
		0.3125 0.56249982 0.68843985 0.56388873 0.3125 0.56388873 0.68843985 0.56527764 0.3125 
		0.56527764 0.68843985 0.56666654 0.3125 0.56666654 0.68843985 0.56805545 0.3125 0.56805545 
		0.68843985 0.56944436 0.3125 0.56944436 0.68843985 0.57083327 0.3125 0.57083327 0.68843985 
		0.57222217 0.3125 0.57222217 0.68843985 0.57361108 0.3125 0.57361108 0.68843985 0.57499999 
		0.3125 0.57499999 0.68843985 0.5763889 0.3125 0.5763889 0.68843985 0.5777778 0.3125 
		0.5777778 0.68843985 0.57916671 0.3125 0.57916671 0.68843985 0.58055562 0.3125 0.58055562 
		0.68843985 0.58194453 0.3125 0.58194453 0.68843985 0.58333343 0.3125 0.58333343 0.68843985 
		0.58472234 0.3125 0.58472234 0.68843985 0.58611125 0.3125 0.58611125 0.68843985 0.58750015 
		0.3125 0.58750015 0.68843985 0.58888906 0.3125 0.58888906 0.68843985 0.59027797 0.3125 
		0.59027797 0.68843985 0.59166688 0.3125 0.59166688 0.68843985 0.59305578 0.3125 0.59305578 
		0.68843985 0.59444469 0.3125 0.59444469 0.68843985 0.5958336 0.3125 0.5958336 0.68843985 
		0.59722251 0.3125 0.59722251 0.68843985 0.59861141 0.3125 0.59861141 0.68843985 0.60000032 
		0.3125 0.60000032 0.68843985 0.60138923 0.3125 0.60138923 0.68843985 0.60277814 0.3125 
		0.60277814 0.68843985 0.60416704 0.3125 0.60416704 0.68843985 0.60555595 0.3125 0.60555595 
		0.68843985 0.60694486 0.3125 0.60694486 0.68843985 0.60833377 0.3125 0.60833377 0.68843985 
		0.60972267 0.3125 0.60972267 0.68843985 0.61111158 0.3125 0.61111158 0.68843985 0.61250049 
		0.3125 0.61250049 0.68843985 0.6138894 0.3125 0.6138894 0.68843985 0.6152783 0.3125 
		0.6152783 0.68843985 0.61666721 0.3125 0.61666721 0.68843985 0.61805612 0.3125 0.61805612 
		0.68843985 0.61944503 0.3125 0.61944503 0.68843985 0.62083393 0.3125 0.62083393 0.68843985 
		0.62222284 0.3125 0.62222284 0.68843985 0.62361175 0.3125 0.62361175 0.68843985 0.62500066 
		0.3125 0.62500066 0.68843985;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 360 ".pt";
	setAttr ".pt[0:165]" -type "float3"  0 0.0099999998 0 0 0.0099999998 0 -0.020544423 
		-0.0099999998 0.0014366012 -0.020582044 -0.0099999998 0.00071873574 0 0.0099999998 
		0 -0.020481771 -0.0099999998 0.0021527165 0 0.0099999998 0 -0.020394163 -0.0099999998 
		0.0028662076 0 0.0099999998 0 -0.020281712 -0.0099999998 0.0035762074 0 0.0099999998 
		0 -0.020144543 -0.0099999998 0.0042818519 0 0.0099999998 0 -0.019982832 -0.0099999998 
		0.0049822778 0 0.0099999998 0 -0.019796779 -0.0099999998 0.0056766341 0 0.0099999998 
		0 -0.019586606 -0.0099999998 0.0063640736 0 0.0099999998 0 -0.019352579 -0.0099999998 
		0.0070437598 0 0.0099999998 0 -0.019094966 -0.0099999998 0.0077148639 0 0.0099999998 
		0 -0.018814096 -0.0099999998 0.0083765686 0 0.0099999998 0 -0.018510297 -0.0099999998 
		0.0090280697 0 0.0099999998 0 -0.018183941 -0.0099999998 0.0096685672 0 0.0099999998 
		0 -0.017835431 -0.0099999998 0.01029729 0 0.0099999998 0 -0.017465197 -0.0099999998 
		0.010913462 0 0.0099999998 0 -0.017073683 -0.0099999998 0.011516339 0 0.0099999998 
		0 -0.01666137 -0.0099999998 0.01210519 0 0.0099999998 0 -0.01622875 -0.0099999998 
		0.012679292 0 0.0099999998 0 -0.01577636 -0.0099999998 0.013237939 0 0.0099999998 
		0 -0.015304753 -0.0099999998 0.013780462 0 0.0099999998 0 -0.014814507 -0.0099999998 
		0.014306194 0 0.0099999998 0 -0.014306211 -0.0099999998 0.014814497 0 0.0099999998 
		0 -0.013780475 -0.0099999998 0.015304753 0 0.0099999998 0 -0.013237954 -0.0099999998 
		0.015776364 0 0.0099999998 0 -0.012679301 -0.0099999998 0.016228748 0 0.0099999998 
		0 -0.0121052 -0.0099999998 0.016661361 0 0.0099999998 0 -0.011516348 -0.0099999998 
		0.017073676 0 0.0099999998 0 -0.010913474 -0.0099999998 0.017465191 0 0.0099999998 
		0 -0.010297292 -0.0099999998 0.017835425 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		0.018183932 0 0.0099999998 0 -0.009028065 -0.0099999998 0.018510282 0 0.0099999998 
		0 -0.0083765695 -0.0099999998 0.018814081 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		0.019094959 0 0.0099999998 0 -0.007043757 -0.0099999998 0.01935257 0 0.0099999998 
		0 -0.0063640689 -0.0099999998 0.019586606 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		0.019796776 0 0.0099999998 0 -0.0049822717 -0.0099999998 0.019982828 0 0.0099999998 
		0 -0.0042818524 -0.0099999998 0.020144535 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		0.020281695 0 0.0099999998 0 -0.0028662051 -0.0099999998 0.020394148 0 0.0099999998 
		0 -0.0021527156 -0.0099999998 0.020481752 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		0.020544408 0 0.0099999998 0 -0.00071872404 -0.0099999998 0.020582028 0 0.0099999998 
		0 9.8202451e-009 -0.0099999998 0.020594569 0 0.0099999998 0 0.00071874366 -0.0099999998 
		0.020582026 0 0.0099999998 0 0.0014366135 -0.0099999998 0.020544404 0 0.0099999998 
		0 0.0021527254 -0.0099999998 0.02048175 0 0.0099999998 0 0.0028662151 -0.0099999998 
		0.020394145 0 0.0099999998 0 0.0035762191 -0.0099999998 0.020281689 0 0.0099999998 
		0 0.0042818626 -0.0099999998 0.020144528 0 0.0099999998 0 0.0049822815 -0.0099999998 
		0.019982822 0 0.0099999998 0 0.0056766314 -0.0099999998 0.019796772 0 0.0099999998 
		0 0.0063640778 -0.0099999998 0.019586597 0 0.0099999998 0 0.0070437673 -0.0099999998 
		0.019352563 0 0.0099999998 0 0.0077148722 -0.0099999998 0.019094951 0 0.0099999998 
		0 0.0083765695 -0.0099999998 0.018814072 0 0.0099999998 0 0.0090280846 -0.0099999998 
		0.018510271 0 0.0099999998 0 0.0096685812 -0.0099999998 0.018183919 0 0.0099999998 
		0 0.010297292 -0.0099999998 0.017835416 0 0.0099999998 0 0.010913474 -0.0099999998 
		0.017465182 0 0.0099999998 0 0.011516348 -0.0099999998 0.01707367 0 0.0099999998 
		0 0.01210519 -0.0099999998 0.016661352 0 0.0099999998 0 0.012679292 -0.0099999998 
		0.016228735 0 0.0099999998 0 0.013237936 -0.0099999998 0.015776353 0 0.0099999998 
		0 0.013780454 -0.0099999998 0.015304745 0 0.0099999998 0 0.014306202 -0.0099999998 
		0.014814489 0 0.0099999998 0 0.014814507 -0.0099999998 0.01430618 0 0.0099999998 
		0 0.015304753 -0.0099999998 0.013780446 0 0.0099999998 0 0.015776351 -0.0099999998 
		0.013237924 0 0.0099999998 0 0.01622875 -0.0099999998 0.012679273 0 0.0099999998 
		0 0.01666137 -0.0099999998 0.012105175 0 0.0099999998 0 0.017073683 -0.0099999998 
		0.011516329 0 0.0099999998 0 0.017465197 -0.0099999998 0.010913447 0 0.0099999998 
		0 0.017835431 -0.0099999998 0.010297275 0 0.0099999998 0 0.018183932 -0.0099999998 
		0.0096685542 0 0.0099999998 0 0.018510288 -0.0099999998 0.0090280538 0 0.0099999998 
		0 0.018814087 -0.0099999998 0.0083765527 0 0.0099999998 0 0.019094957 -0.0099999998 
		0.0077148476 0 0.0099999998 0 0.019352579 -0.0099999998 0.0070437454 0 0.0099999998 
		0 0.019586615 -0.0099999998 0.006364061 0 0.0099999998 0 0.019796779 -0.0099999998 
		0.0056766197 0 0.0099999998 0 0.019982813 -0.0099999998 0.0049822633;
	setAttr ".pt[166:331]" 0 0.0099999998 0 0.020144535 -0.0099999998 0.0042818389 
		0 0.0099999998 0 0.020281693 -0.0099999998 0.0035761963 0 0.0099999998 0 0.020394145 
		-0.0099999998 0.0028661957 0 0.0099999998 0 0.02048175 -0.0099999998 0.0021527046 
		0 0.0099999998 0 0.020544423 -0.0099999998 0.0014365911 0 0.0099999998 0 0.020582026 
		-0.0099999998 0.00071872625 0 0.0099999998 0 0.020594554 -0.0099999998 -1.4200041e-008 
		0 0.0099999998 0 0.020582026 -0.0099999998 -0.00071875472 0 0.0099999998 0 0.020544423 
		-0.0099999998 -0.0014366197 0 0.0099999998 0 0.020481741 -0.0099999998 -0.0021527326 
		0 0.0099999998 0 0.020394124 -0.0099999998 -0.0028662232 0 0.0099999998 0 0.020281682 
		-0.0099999998 -0.0035762237 0 0.0099999998 0 0.020144535 -0.0099999998 -0.0042818668 
		0 0.0099999998 0 0.019982824 -0.0099999998 -0.0049822913 0 0.0099999998 0 0.019796768 
		-0.0099999998 -0.0056766467 0 0.0099999998 0 0.019586595 -0.0099999998 -0.0063640852 
		0 0.0099999998 0 0.019352559 -0.0099999998 -0.007043771 0 0.0099999998 0 0.019094957 
		-0.0099999998 -0.0077148755 0 0.0099999998 0 0.018814074 -0.0099999998 -0.0083765807 
		0 0.0099999998 0 0.01851028 -0.0099999998 -0.0090280781 0 0.0099999998 0 0.018183911 
		-0.0099999998 -0.0096685803 0 0.0099999998 0 0.01783541 -0.0099999998 -0.010297298 
		0 0.0099999998 0 0.017465187 -0.0099999998 -0.010913473 0 0.0099999998 0 0.017073683 
		-0.0099999998 -0.011516354 0 0.0099999998 0 0.016661352 -0.0099999998 -0.012105198 
		0 0.0099999998 0 0.016228737 -0.0099999998 -0.012679295 0 0.0099999998 0 0.015776342 
		-0.0099999998 -0.013237947 0 0.0099999998 0 0.015304744 -0.0099999998 -0.013780468 
		0 0.0099999998 0 0.014814488 -0.0099999998 -0.014306203 0 0.0099999998 0 0.014306189 
		-0.0099999998 -0.014814504 0 0.0099999998 0 0.013780454 -0.0099999998 -0.015304754 
		0 0.0099999998 0 0.013237924 -0.0099999998 -0.015776364 0 0.0099999998 0 0.012679281 
		-0.0099999998 -0.016228752 0 0.0099999998 0 0.012105181 -0.0099999998 -0.016661363 
		0 0.0099999998 0 0.011516329 -0.0099999998 -0.017073678 0 0.0099999998 0 0.010913454 
		-0.0099999998 -0.017465195 0 0.0099999998 0 0.010297283 -0.0099999998 -0.017835427 
		0 0.0099999998 0 0.0096685709 -0.0099999998 -0.01818393 0 0.0099999998 0 0.0090280557 
		-0.0099999998 -0.018510282 0 0.0099999998 0 0.0083765509 -0.0099999998 -0.018814085 
		0 0.0099999998 0 0.0077148527 -0.0099999998 -0.019094957 0 0.0099999998 0 0.0070437482 
		-0.0099999998 -0.019352568 0 0.0099999998 0 0.0063640689 -0.0099999998 -0.019586606 
		0 0.0099999998 0 0.0056766314 -0.0099999998 -0.019796776 0 0.0099999998 0 0.0049822717 
		-0.0099999998 -0.019982828 0 0.0099999998 0 0.0042818426 -0.0099999998 -0.020144535 
		0 0.0099999998 0 0.0035761991 -0.0099999998 -0.020281695 0 0.0099999998 0 0.0028662051 
		-0.0099999998 -0.020394148 0 0.0099999998 0 0.0021527156 -0.0099999998 -0.020481752 
		0 0.0099999998 0 0.0014366035 -0.0099999998 -0.020544404 0 0.0099999998 0 0.00071873382 
		-0.0099999998 -0.020582028 0 0.0099999998 0 0 -0.0099999998 -0.020594569 0 0.0099999998 
		0 -0.00071873382 -0.0099999998 -0.020582026 0 0.0099999998 0 -0.0014366035 -0.0099999998 
		-0.020544404 0 0.0099999998 0 -0.0021527254 -0.0099999998 -0.020481752 0 0.0099999998 
		0 -0.0028662151 -0.0099999998 -0.020394145 0 0.0099999998 0 -0.0035762093 -0.0099999998 
		-0.020281693 0 0.0099999998 0 -0.0042818524 -0.0099999998 -0.02014453 0 0.0099999998 
		0 -0.0049822815 -0.0099999998 -0.01998282 0 0.0099999998 0 -0.0056766314 -0.0099999998 
		-0.019796772 0 0.0099999998 0 -0.0063640587 -0.0099999998 -0.019586599 0 0.0099999998 
		0 -0.007043757 -0.0099999998 -0.019352563 0 0.0099999998 0 -0.0077148634 -0.0099999998 
		-0.01909495 0 0.0099999998 0 -0.0083765611 -0.0099999998 -0.018814074 0 0.0099999998 
		0 -0.009028065 -0.0099999998 -0.018510275 0 0.0099999998 0 -0.0096685709 -0.0099999998 
		-0.018183921 0 0.0099999998 0 -0.010297283 -0.0099999998 -0.017835416 0 0.0099999998 
		0 -0.010913454 -0.0099999998 -0.01746518 0 0.0099999998 0 -0.011516329 -0.0099999998 
		-0.017073667 0 0.0099999998 0 -0.012105181 -0.0099999998 -0.016661353 0 0.0099999998 
		0 -0.012679271 -0.0099999998 -0.016228737 0 0.0099999998 0 -0.013237924 -0.0099999998 
		-0.015776351 0 0.0099999998 0 -0.013780445 -0.0099999998 -0.015304743 0 0.0099999998 
		0 -0.014306181 -0.0099999998 -0.014814489 0 0.0099999998 0 -0.014814488 -0.0099999998 
		-0.014306187 0 0.0099999998 0 -0.015304735 -0.0099999998 -0.013780452 0 0.0099999998 
		0 -0.015776342 -0.0099999998 -0.013237932 0 0.0099999998 0 -0.01622873 -0.0099999998 
		-0.012679281 0 0.0099999998 0 -0.016661342 -0.0099999998 -0.012105183 0 0.0099999998 
		0 -0.017073654 -0.0099999998 -0.011516336 0 0.0099999998 0 -0.017465167 -0.0099999998 
		-0.010913458 0 0.0099999998 0 -0.017835401 -0.0099999998 -0.010297284 0 0.0099999998 
		0 -0.018183911 -0.0099999998 -0.0096685654;
	setAttr ".pt[332:359]" 0 0.0099999998 0 -0.018510258 -0.0099999998 -0.0090280669 
		0 0.0099999998 0 -0.018814066 -0.0099999998 -0.0083765676 0 0.0099999998 0 -0.019094935 
		-0.0099999998 -0.0077148639 0 0.0099999998 0 -0.01935254 -0.0099999998 -0.0070437607 
		0 0.0099999998 0 -0.019586576 -0.0099999998 -0.0063640764 0 0.0099999998 0 -0.01979675 
		-0.0099999998 -0.0056766379 0 0.0099999998 0 -0.019982802 -0.0099999998 -0.0049822819 
		0 0.0099999998 0 -0.020144505 -0.0099999998 -0.0042818584 0 0.0099999998 0 -0.020281672 
		-0.0099999998 -0.0035762175 0 0.0099999998 0 -0.020394124 -0.0099999998 -0.0028662186 
		0 0.0099999998 0 -0.020481732 -0.0099999998 -0.0021527279 0 0.0099999998 0 -0.020544384 
		-0.0099999998 -0.0014366142 0 0.0099999998 0 -0.020581996 -0.0099999998 -0.00071875029 
		0 0.0099999998 0 -0.020594554 -0.0099999998 -1.0959254e-008;
	setAttr -s 360 ".vt";
	setAttr ".vt[0:165]"  0.99939299 -0.0099999998 -0.034899864 0.99756622 -0.0099999998 
		-0.069756918 0.99756622 0.0099999998 -0.069756918 0.99939299 0.0099999998 -0.034899864 
		0.994524 -0.0099999998 -0.104529 0.994524 0.0099999998 -0.104529 0.99027014 -0.0099999998 
		-0.13917367 0.99027014 0.0099999998 -0.13917367 0.98480988 -0.0099999998 -0.1736488 
		0.98480988 0.0099999998 -0.1736488 0.97814941 -0.0099999998 -0.20791246 0.97814941 
		0.0099999998 -0.20791246 0.97029734 -0.0099999998 -0.24192274 0.97029734 0.0099999998 
		-0.24192274 0.96126318 -0.0099999998 -0.27563825 0.96126318 0.0099999998 -0.27563825 
		0.95105791 -0.0099999998 -0.30901796 0.95105791 0.0099999998 -0.30901796 0.9396944 
		-0.0099999998 -0.34202117 0.9396944 0.0099999998 -0.34202117 0.92718554 -0.0099999998 
		-0.37460765 0.92718554 0.0099999998 -0.37460765 0.91354752 -0.0099999998 -0.40673777 
		0.91354752 0.0099999998 -0.40673777 0.89879608 -0.0099999998 -0.4383724 0.89879608 
		0.0099999998 -0.4383724 0.88294935 -0.0099999998 -0.46947283 0.88294935 0.0099999998 
		-0.46947283 0.86602688 -0.0099999998 -0.50000131 0.86602688 0.0099999998 -0.50000131 
		0.84804964 -0.0099999998 -0.52992058 0.84804964 0.0099999998 -0.52992058 0.8290391 
		-0.0099999998 -0.55919421 0.8290391 0.0099999998 -0.55919421 0.80901861 -0.0099999998 
		-0.58778679 0.80901861 0.0099999998 -0.58778679 0.78801203 -0.0099999998 -0.61566311 
		0.78801203 0.0099999998 -0.61566311 0.76604557 -0.0099999998 -0.64278919 0.76604557 
		0.0099999998 -0.64278919 0.74314594 -0.0099999998 -0.66913217 0.74314594 0.0099999998 
		-0.66913217 0.71934128 -0.0099999998 -0.69465989 0.71934128 0.0099999998 -0.69465989 
		0.69466019 -0.0099999998 -0.71934134 0.69466019 0.0099999998 -0.71934134 0.66913223 
		-0.0099999998 -0.74314648 0.66913223 0.0099999998 -0.74314648 0.64278936 -0.0099999998 
		-0.76604617 0.64278936 0.0099999998 -0.76604617 0.61566305 -0.0099999998 -0.78801244 
		0.61566305 0.0099999998 -0.78801244 0.58778667 -0.0099999998 -0.80901867 0.58778667 
		0.0099999998 -0.80901867 0.55919409 -0.0099999998 -0.82903928 0.55919409 0.0099999998 
		-0.82903928 0.52992058 -0.0099999998 -0.84804988 0.52992058 0.0099999998 -0.84804988 
		0.50000095 -0.0099999998 -0.86602724 0.50000095 0.0099999998 -0.86602724 0.46947241 
		-0.0099999998 -0.88294941 0.46947241 0.0099999998 -0.88294941 0.43837166 -0.0099999998 
		-0.89879584 0.43837166 0.0099999998 -0.89879584 0.40673733 -0.0099999998 -0.91354734 
		0.40673733 0.0099999998 -0.91354734 0.37460709 -0.0099999998 -0.92718577 0.37460709 
		0.0099999998 -0.92718577 0.34202051 -0.0099999998 -0.93969446 0.34202051 0.0099999998 
		-0.93969446 0.30901718 -0.0099999998 -0.95105839 0.30901718 0.0099999998 -0.95105839 
		0.27563763 -0.0099999998 -0.9612636 0.27563763 0.0099999998 -0.9612636 0.2419219 
		-0.0099999998 -0.97029763 0.2419219 0.0099999998 -0.97029763 0.20791197 -0.0099999998 
		-0.97814947 0.20791197 0.0099999998 -0.97814947 0.17364836 -0.0099999998 -0.98480958 
		0.17364836 0.0099999998 -0.98480958 0.13917303 -0.0099999998 -0.9902699 0.13917303 
		0.0099999998 -0.9902699 0.10452843 -0.0099999998 -0.99452376 0.10452843 0.0099999998 
		-0.99452376 0.069756508 -0.0099999998 -0.99756593 0.069756508 0.0099999998 -0.99756593 
		0.034898758 -0.0099999998 -0.99939269 0.034898758 0.0099999998 -0.99939269 -4.7683716e-007 
		-0.0099999998 -1.0000018 -4.7683716e-007 0.0099999998 -1.0000018 -0.034899712 -0.0099999998 
		-0.99939257 -0.034899712 0.0099999998 -0.99939257 -0.069756985 -0.0099999998 -0.99756581 
		-0.069756985 0.0099999998 -0.99756581 -0.1045289 -0.0099999998 -0.99452358 -0.1045289 
		0.0099999998 -0.99452358 -0.13917351 -0.0099999998 -0.99026972 -0.13917351 0.0099999998 
		-0.99026972 -0.17364883 -0.0099999998 -0.9848094 -0.17364883 0.0099999998 -0.9848094 
		-0.20791245 -0.0099999998 -0.97814924 -0.20791245 0.0099999998 -0.97814924 -0.24192238 
		-0.0099999998 -0.97029734 -0.24192238 0.0099999998 -0.97029734 -0.27563763 -0.0099999998 
		-0.9612633 -0.27563763 0.0099999998 -0.9612633 -0.30901766 -0.0099999998 -0.95105803 
		-0.30901766 0.0099999998 -0.95105803 -0.34202099 -0.0099999998 -0.93969417 -0.34202099 
		0.0099999998 -0.93969417 -0.37460756 -0.0099999998 -0.92718542 -0.37460756 0.0099999998 
		-0.92718542 -0.40673733 -0.0099999998 -0.91354692 -0.40673733 0.0099999998 -0.91354692 
		-0.43837261 -0.0099999998 -0.89879537 -0.43837261 0.0099999998 -0.89879537 -0.46947289 
		-0.0099999998 -0.88294888 -0.46947289 0.0099999998 -0.88294888 -0.50000095 -0.0099999998 
		-0.8660267 -0.50000095 0.0099999998 -0.8660267 -0.52992058 -0.0099999998 -0.8480494 
		-0.52992058 0.0099999998 -0.8480494 -0.55919409 -0.0099999998 -0.82903898 -0.55919409 
		0.0099999998 -0.82903898 -0.5877862 -0.0099999998 -0.80901819 -0.5877862 0.0099999998 
		-0.80901819 -0.61566257 -0.0099999998 -0.78801191 -0.61566257 0.0099999998 -0.78801191 
		-0.64278841 -0.0099999998 -0.76604575 -0.64278841 0.0099999998 -0.76604575 -0.66913128 
		-0.0099999998 -0.74314612 -0.66913128 0.0099999998 -0.74314612 -0.69465971 -0.0099999998 
		-0.71934092 -0.69465971 0.0099999998 -0.71934092 -0.71934128 -0.0099999998 -0.69465923 
		-0.71934128 0.0099999998 -0.69465923 -0.74314594 -0.0099999998 -0.6691314 -0.74314594 
		0.0099999998 -0.6691314 -0.76604509 -0.0099999998 -0.64278841 -0.76604509 0.0099999998 
		-0.64278841 -0.78801203 -0.0099999998 -0.61566228 -0.78801203 0.0099999998 -0.61566228 
		-0.80901861 -0.0099999998 -0.58778608 -0.80901861 0.0099999998 -0.58778608 -0.8290391 
		-0.0099999998 -0.55919367 -0.8290391 0.0099999998 -0.55919367 -0.84804964 -0.0099999998 
		-0.52991986 -0.84804964 0.0099999998 -0.52991986 -0.86602688 -0.0099999998 -0.5000006 
		-0.86602688 0.0099999998 -0.5000006 -0.88294888 -0.0099999998 -0.46947214 -0.88294888 
		0.0099999998 -0.46947214 -0.8987956 -0.0099999998 -0.43837163 -0.8987956 0.0099999998 
		-0.43837163 -0.91354704 -0.0099999998 -0.40673697 -0.91354704 0.0099999998 -0.40673697 
		-0.92718506 -0.0099999998 -0.37460688 -0.92718506 0.0099999998 -0.37460688 -0.9396944 
		-0.0099999998 -0.34202048 -0.9396944 0.0099999998 -0.34202048 -0.95105839 -0.0099999998 
		-0.30901733 -0.95105839 0.0099999998 -0.30901733 -0.96126318 -0.0099999998 -0.27563757 
		-0.96126318 0.0099999998 -0.27563757 -0.97029638 -0.0099999998 -0.24192205 -0.97029638 
		0.0099999998 -0.24192205;
	setAttr ".vt[166:331]" -0.97814894 -0.0099999998 -0.20791183 -0.97814894 0.0099999998 
		-0.20791183 -0.98480892 -0.0099999998 -0.17364825 -0.98480892 0.0099999998 -0.17364825 
		-0.99026918 -0.0099999998 -0.13917311 -0.99026918 0.0099999998 -0.13917311 -0.99452305 
		-0.0099999998 -0.10452844 -0.99452305 0.0099999998 -0.10452844 -0.99756622 -0.0099999998 
		-0.069756441 -0.99756622 0.0099999998 -0.069756441 -0.99939203 -0.0099999998 -0.034899399 
		-0.99939203 0.0099999998 -0.034899399 -1.0000005 -0.0099999998 1.5306313e-007 -1.0000005 
		0.0099999998 1.5306313e-007 -0.99939203 -0.0099999998 0.034899708 -0.99939203 0.0099999998 
		0.034899708 -0.99756622 -0.0099999998 0.069756746 -0.99756622 0.0099999998 0.069756746 
		-0.99452257 -0.0099999998 0.10452873 -0.99452257 0.0099999998 0.10452873 -0.99026823 
		-0.0099999998 0.13917336 -0.99026823 0.0099999998 0.13917336 -0.98480844 -0.0099999998 
		0.17364854 -0.98480844 0.0099999998 0.17364854 -0.97814894 -0.0099999998 0.2079121 
		-0.97814894 0.0099999998 0.2079121 -0.97029686 -0.0099999998 0.2419223 -0.97029686 
		0.0099999998 0.2419223 -0.9612627 -0.0099999998 0.27563784 -0.9612627 0.0099999998 
		0.27563784 -0.95105743 -0.0099999998 0.30901748 -0.95105743 0.0099999998 0.30901748 
		-0.93969345 -0.0099999998 0.34202063 -0.93969345 0.0099999998 0.34202063 -0.92718506 
		-0.0099999998 0.37460718 -0.92718506 0.0099999998 0.37460718 -0.91354656 -0.0099999998 
		0.40673727 -0.91354656 0.0099999998 0.40673727 -0.89879513 -0.0099999998 0.43837181 
		-0.89879513 0.0099999998 0.43837181 -0.88294792 -0.0099999998 0.46947232 -0.88294792 
		0.0099999998 0.46947232 -0.86602592 -0.0099999998 0.50000072 -0.86602592 0.0099999998 
		0.50000072 -0.84804916 -0.0099999998 0.52991998 -0.84804916 0.0099999998 0.52991998 
		-0.8290391 -0.0099999998 0.55919379 -0.8290391 0.0099999998 0.55919379 -0.80901766 
		-0.0099999998 0.58778608 -0.80901766 0.0099999998 0.58778608 -0.78801155 -0.0099999998 
		0.61566228 -0.78801155 0.0099999998 0.61566228 -0.76604462 -0.0099999998 0.64278841 
		-0.76604462 0.0099999998 0.64278841 -0.74314547 -0.0099999998 0.6691314 -0.74314547 
		0.0099999998 0.6691314 -0.71934032 -0.0099999998 0.69465923 -0.71934032 0.0099999998 
		0.69465923 -0.69465923 -0.0099999998 0.71934062 -0.69465923 0.0099999998 0.71934062 
		-0.66913128 -0.0099999998 0.74314547 -0.66913128 0.0099999998 0.74314547 -0.64278793 
		-0.0099999998 0.76604515 -0.64278793 0.0099999998 0.76604515 -0.6156621 -0.0099999998 
		0.78801161 -0.6156621 0.0099999998 0.78801161 -0.58778572 -0.0099999998 0.80901778 
		-0.58778572 0.0099999998 0.80901778 -0.55919313 -0.0099999998 0.82903832 -0.55919313 
		0.0099999998 0.82903832 -0.52991962 -0.0099999998 0.84804899 -0.52991962 0.0099999998 
		0.84804899 -0.50000048 -0.0099999998 0.86602622 -0.50000048 0.0099999998 0.86602622 
		-0.46947241 -0.0099999998 0.88294828 -0.46947241 0.0099999998 0.88294828 -0.43837118 
		-0.0099999998 0.89879483 -0.43837118 0.0099999998 0.89879483 -0.40673637 -0.0099999998 
		0.91354638 -0.40673637 0.0099999998 0.91354638 -0.37460661 -0.0099999998 0.92718464 
		-0.37460661 0.0099999998 0.92718464 -0.34202003 -0.0099999998 0.93969333 -0.34202003 
		0.0099999998 0.93969333 -0.30901718 -0.0099999998 0.95105731 -0.30901718 0.0099999998 
		0.95105731 -0.27563763 -0.0099999998 0.96126252 -0.27563763 0.0099999998 0.96126252 
		-0.2419219 -0.0099999998 0.97029656 -0.2419219 0.0099999998 0.97029656 -0.20791149 
		-0.0099999998 0.9781484 -0.20791149 0.0099999998 0.9781484 -0.17364788 -0.0099999998 
		0.9848085 -0.17364788 0.0099999998 0.9848085 -0.13917303 -0.0099999998 0.99026883 
		-0.13917303 0.0099999998 0.99026883 -0.10452843 -0.0099999998 0.99452257 -0.10452843 
		0.0099999998 0.99452257 -0.069756508 -0.0099999998 0.99756479 -0.069756508 0.0099999998 
		0.99756479 -0.034899235 -0.0099999998 0.99939156 -0.034899235 0.0099999998 0.99939156 
		0 -0.0099999998 1.0000007 0 0.0099999998 1.0000007 0.034899235 -0.0099999998 0.9993915 
		0.034899235 0.0099999998 0.9993915 0.069756508 -0.0099999998 0.99756473 0.069756508 
		0.0099999998 0.99756473 0.1045289 -0.0099999998 0.99452257 0.1045289 0.0099999998 
		0.99452257 0.13917351 -0.0099999998 0.99026871 0.13917351 0.0099999998 0.99026871 
		0.17364836 -0.0099999998 0.98480844 0.17364836 0.0099999998 0.98480844 0.20791197 
		-0.0099999998 0.97814822 0.20791197 0.0099999998 0.97814822 0.24192238 -0.0099999998 
		0.9702962 0.24192238 0.0099999998 0.9702962 0.27563763 -0.0099999998 0.96126223 0.27563763 
		0.0099999998 0.96126223 0.3090167 -0.0099999998 0.95105702 0.3090167 0.0099999998 
		0.95105702 0.34202051 -0.0099999998 0.93969309 0.34202051 0.0099999998 0.93969309 
		0.37460709 -0.0099999998 0.92718428 0.37460709 0.0099999998 0.92718428 0.40673685 
		-0.0099999998 0.91354591 0.40673685 0.0099999998 0.91354591 0.43837166 -0.0099999998 
		0.89879441 0.43837166 0.0099999998 0.89879441 0.46947241 -0.0099999998 0.88294786 
		0.46947241 0.0099999998 0.88294786 0.50000048 -0.0099999998 0.86602569 0.50000048 
		0.0099999998 0.86602569 0.52991962 -0.0099999998 0.84804827 0.52991962 0.0099999998 
		0.84804827 0.55919313 -0.0099999998 0.82903773 0.55919313 0.0099999998 0.82903773 
		0.58778572 -0.0099999998 0.80901718 0.58778572 0.0099999998 0.80901718 0.61566162 
		-0.0099999998 0.78801095 0.61566162 0.0099999998 0.78801095 0.64278793 -0.0099999998 
		0.76604462 0.64278793 0.0099999998 0.76604462 0.6691308 -0.0099999998 0.74314487 
		0.6691308 0.0099999998 0.74314487 0.69465876 -0.0099999998 0.71933985 0.69465876 
		0.0099999998 0.71933985 0.71934032 -0.0099999998 0.6946584 0.71934032 0.0099999998 
		0.6946584 0.74314499 -0.0099999998 0.66913062 0.74314499 0.0099999998 0.66913062 
		0.76604462 -0.0099999998 0.64278775 0.76604462 0.0099999998 0.64278775 0.78801107 
		-0.0099999998 0.61566162 0.78801107 0.0099999998 0.61566162 0.80901718 -0.0099999998 
		0.5877853 0.80901718 0.0099999998 0.5877853 0.82903767 -0.0099999998 0.55919302 0.82903767 
		0.0099999998 0.55919302 0.84804821 -0.0099999998 0.52991927 0.84804821 0.0099999998 
		0.52991927 0.86602545 -0.0099999998 0.5 0.86602545 0.0099999998 0.5 0.88294792 -0.0099999998 
		0.4694716 0.88294792 0.0099999998 0.4694716;
	setAttr ".vt[332:359]" 0.89879417 -0.0099999998 0.43837121 0.89879417 0.0099999998 
		0.43837121 0.91354609 -0.0099999998 0.40673664 0.91354609 0.0099999998 0.40673664 
		0.9271841 -0.0099999998 0.37460658 0.9271841 0.0099999998 0.37460658 0.9396925 -0.0099999998 
		0.34202015 0.9396925 0.0099999998 0.34202015 0.95105648 -0.0099999998 0.30901697 
		0.95105648 0.0099999998 0.30901697 0.96126175 -0.0099999998 0.27563736 0.96126175 
		0.0099999998 0.27563736 0.97029591 -0.0099999998 0.24192189 0.97029591 0.0099999998 
		0.24192189 0.97814751 -0.0099999998 0.20791171 0.97814751 0.0099999998 0.20791171 
		0.98480797 -0.0099999998 0.17364822 0.98480797 0.0099999998 0.17364822 0.99026823 
		-0.0099999998 0.13917314 0.99026823 0.0099999998 0.13917314 0.99452209 -0.0099999998 
		0.10452849 0.99452209 0.0099999998 0.10452849 0.99756432 -0.0099999998 0.069756478 
		0.99756432 0.0099999998 0.069756478 0.9993906 -0.0099999998 0.034899496 0.9993906 
		0.0099999998 0.034899496 1.0000005 -0.0099999998 -4.2983097e-009 1.0000005 0.0099999998 
		-4.2983097e-009;
	setAttr -s 540 ".ed";
	setAttr ".ed[0:165]"  0 3 1 1 2 1 4 5 
		1 6 7 1 8 9 1 10 11 1 12 13 
		1 14 15 1 16 17 1 18 19 1 20 21 
		1 22 23 1 24 25 1 26 27 1 28 29 
		1 30 31 1 32 33 1 34 35 1 36 37 
		1 38 39 1 40 41 1 42 43 1 44 45 
		1 46 47 1 48 49 1 50 51 1 52 53 
		1 54 55 1 56 57 1 58 59 1 60 61 
		1 62 63 1 64 65 1 66 67 1 68 69 
		1 70 71 1 72 73 1 74 75 1 76 77 
		1 78 79 1 80 81 1 82 83 1 84 85 
		1 86 87 1 88 89 1 90 91 1 92 93 
		1 94 95 1 96 97 1 98 99 1 100 101 
		1 102 103 1 104 105 1 106 107 1 108 109 
		1 110 111 1 112 113 1 114 115 1 116 117 
		1 118 119 1 120 121 1 122 123 1 124 125 
		1 126 127 1 128 129 1 130 131 1 132 133 
		1 134 135 1 136 137 1 138 139 1 140 141 
		1 142 143 1 144 145 1 146 147 1 148 149 
		1 150 151 1 152 153 1 154 155 1 156 157 
		1 158 159 1 160 161 1 162 163 1 164 165 
		1 166 167 1 168 169 1 170 171 1 172 173 
		1 174 175 1 176 177 1 178 179 1 180 181 
		1 182 183 1 184 185 1 186 187 1 188 189 
		1 190 191 1 192 193 1 194 195 1 196 197 
		1 198 199 1 200 201 1 202 203 1 204 205 
		1 206 207 1 208 209 1 210 211 1 212 213 
		1 214 215 1 216 217 1 218 219 1 220 221 
		1 222 223 1 224 225 1 226 227 1 228 229 
		1 230 231 1 232 233 1 234 235 1 236 237 
		1 238 239 1 240 241 1 242 243 1 244 245 
		1 246 247 1 248 249 1 250 251 1 252 253 
		1 254 255 1 256 257 1 258 259 1 260 261 
		1 262 263 1 264 265 1 266 267 1 268 269 
		1 270 271 1 272 273 1 274 275 1 276 277 
		1 278 279 1 280 281 1 282 283 1 284 285 
		1 286 287 1 288 289 1 290 291 1 292 293 
		1 294 295 1 296 297 1 298 299 1 300 301 
		1 302 303 1 304 305 1 306 307 1 308 309 
		1 310 311 1 312 313 1 314 315 1 316 317 
		1 318 319 1 320 321 1 322 323 1 324 325 
		1 326 327 1 328 329 1 330 331 1;
	setAttr ".ed[166:331]" 332 333 1 334 335 1 336 337 
		1 338 339 1 340 341 1 342 343 1 344 345 
		1 346 347 1 348 349 1 350 351 1 352 353 
		1 354 355 1 356 357 1 358 359 1 0 1 
		0 3 2 0 1 4 0 2 5 0 4 6 
		0 5 7 0 6 8 0 7 9 0 8 10 
		0 9 11 0 10 12 0 11 13 0 12 14 
		0 13 15 0 14 16 0 15 17 0 16 18 
		0 17 19 0 18 20 0 19 21 0 20 22 
		0 21 23 0 22 24 0 23 25 0 24 26 
		0 25 27 0 26 28 0 27 29 0 28 30 
		0 29 31 0 30 32 0 31 33 0 32 34 
		0 33 35 0 34 36 0 35 37 0 36 38 
		0 37 39 0 38 40 0 39 41 0 40 42 
		0 41 43 0 42 44 0 43 45 0 44 46 
		0 45 47 0 46 48 0 47 49 0 48 50 
		0 49 51 0 50 52 0 51 53 0 52 54 
		0 53 55 0 54 56 0 55 57 0 56 58 
		0 57 59 0 58 60 0 59 61 0 60 62 
		0 61 63 0 62 64 0 63 65 0 64 66 
		0 65 67 0 66 68 0 67 69 0 68 70 
		0 69 71 0 70 72 0 71 73 0 72 74 
		0 73 75 0 74 76 0 75 77 0 76 78 
		0 77 79 0 78 80 0 79 81 0 80 82 
		0 81 83 0 82 84 0 83 85 0 84 86 
		0 85 87 0 86 88 0 87 89 0 88 90 
		0 89 91 0 90 92 0 91 93 0 92 94 
		0 93 95 0 94 96 0 95 97 0 96 98 
		0 97 99 0 98 100 0 99 101 0 100 102 
		0 101 103 0 102 104 0 103 105 0 104 106 
		0 105 107 0 106 108 0 107 109 0 108 110 
		0 109 111 0 110 112 0 111 113 0 112 114 
		0 113 115 0 114 116 0 115 117 0 116 118 
		0 117 119 0 118 120 0 119 121 0 120 122 
		0 121 123 0 122 124 0 123 125 0 124 126 
		0 125 127 0 126 128 0 127 129 0 128 130 
		0 129 131 0 130 132 0 131 133 0 132 134 
		0 133 135 0 134 136 0 135 137 0 136 138 
		0 137 139 0 138 140 0 139 141 0 140 142 
		0 141 143 0 142 144 0 143 145 0 144 146 
		0 145 147 0 146 148 0 147 149 0 148 150 
		0 149 151 0 150 152 0 151 153 0;
	setAttr ".ed[332:497]" 152 154 0 153 155 0 154 156 
		0 155 157 0 156 158 0 157 159 0 158 160 
		0 159 161 0 160 162 0 161 163 0 162 164 
		0 163 165 0 164 166 0 165 167 0 166 168 
		0 167 169 0 168 170 0 169 171 0 170 172 
		0 171 173 0 172 174 0 173 175 0 174 176 
		0 175 177 0 176 178 0 177 179 0 178 180 
		0 179 181 0 180 182 0 181 183 0 182 184 
		0 183 185 0 184 186 0 185 187 0 186 188 
		0 187 189 0 188 190 0 189 191 0 190 192 
		0 191 193 0 192 194 0 193 195 0 194 196 
		0 195 197 0 196 198 0 197 199 0 198 200 
		0 199 201 0 200 202 0 201 203 0 202 204 
		0 203 205 0 204 206 0 205 207 0 206 208 
		0 207 209 0 208 210 0 209 211 0 210 212 
		0 211 213 0 212 214 0 213 215 0 214 216 
		0 215 217 0 216 218 0 217 219 0 218 220 
		0 219 221 0 220 222 0 221 223 0 222 224 
		0 223 225 0 224 226 0 225 227 0 226 228 
		0 227 229 0 228 230 0 229 231 0 230 232 
		0 231 233 0 232 234 0 233 235 0 234 236 
		0 235 237 0 236 238 0 237 239 0 238 240 
		0 239 241 0 240 242 0 241 243 0 242 244 
		0 243 245 0 244 246 0 245 247 0 246 248 
		0 247 249 0 248 250 0 249 251 0 250 252 
		0 251 253 0 252 254 0 253 255 0 254 256 
		0 255 257 0 256 258 0 257 259 0 258 260 
		0 259 261 0 260 262 0 261 263 0 262 264 
		0 263 265 0 264 266 0 265 267 0 266 268 
		0 267 269 0 268 270 0 269 271 0 270 272 
		0 271 273 0 272 274 0 273 275 0 274 276 
		0 275 277 0 276 278 0 277 279 0 278 280 
		0 279 281 0 280 282 0 281 283 0 282 284 
		0 283 285 0 284 286 0 285 287 0 286 288 
		0 287 289 0 288 290 0 289 291 0 290 292 
		0 291 293 0 292 294 0 293 295 0 294 296 
		0 295 297 0 296 298 0 297 299 0 298 300 
		0 299 301 0 300 302 0 301 303 0 302 304 
		0 303 305 0 304 306 0 305 307 0 306 308 
		0 307 309 0 308 310 0 309 311 0 310 312 
		0 311 313 0 312 314 0 313 315 0 314 316 
		0 315 317 0 316 318 0 317 319 0;
	setAttr ".ed[498:539]" 318 320 0 319 321 0 320 322 
		0 321 323 0 322 324 0 323 325 0 324 326 
		0 325 327 0 326 328 0 327 329 0 328 330 
		0 329 331 0 330 332 0 331 333 0 332 334 
		0 333 335 0 334 336 0 335 337 0 336 338 
		0 337 339 0 338 340 0 339 341 0 340 342 
		0 341 343 0 342 344 0 343 345 0 344 346 
		0 345 347 0 346 348 0 347 349 0 348 350 
		0 349 351 0 350 352 0 351 353 0 352 354 
		0 353 355 0 354 356 0 355 357 0 356 358 
		0 357 359 0 358 0 0 359 3 0;
	setAttr -s 180 ".fc[0:179]" -type "polyFaces" 
		f 4 180 1 -182 -1 
		mu 0 4 0 1 2 3 
		f 4 182 2 -184 -2 
		mu 0 4 1 4 5 2 
		f 4 184 3 -186 -3 
		mu 0 4 4 6 7 5 
		f 4 186 4 -188 -4 
		mu 0 4 6 8 9 7 
		f 4 188 5 -190 -5 
		mu 0 4 8 10 11 9 
		f 4 190 6 -192 -6 
		mu 0 4 10 12 13 11 
		f 4 192 7 -194 -7 
		mu 0 4 12 14 15 13 
		f 4 194 8 -196 -8 
		mu 0 4 14 16 17 15 
		f 4 196 9 -198 -9 
		mu 0 4 16 18 19 17 
		f 4 198 10 -200 -10 
		mu 0 4 18 20 21 19 
		f 4 200 11 -202 -11 
		mu 0 4 20 22 23 21 
		f 4 202 12 -204 -12 
		mu 0 4 22 24 25 23 
		f 4 204 13 -206 -13 
		mu 0 4 24 26 27 25 
		f 4 206 14 -208 -14 
		mu 0 4 26 28 29 27 
		f 4 208 15 -210 -15 
		mu 0 4 28 30 31 29 
		f 4 210 16 -212 -16 
		mu 0 4 30 32 33 31 
		f 4 212 17 -214 -17 
		mu 0 4 32 34 35 33 
		f 4 214 18 -216 -18 
		mu 0 4 34 36 37 35 
		f 4 216 19 -218 -19 
		mu 0 4 36 38 39 37 
		f 4 218 20 -220 -20 
		mu 0 4 38 40 41 39 
		f 4 220 21 -222 -21 
		mu 0 4 40 42 43 41 
		f 4 222 22 -224 -22 
		mu 0 4 42 44 45 43 
		f 4 224 23 -226 -23 
		mu 0 4 44 46 47 45 
		f 4 226 24 -228 -24 
		mu 0 4 46 48 49 47 
		f 4 228 25 -230 -25 
		mu 0 4 48 50 51 49 
		f 4 230 26 -232 -26 
		mu 0 4 50 52 53 51 
		f 4 232 27 -234 -27 
		mu 0 4 52 54 55 53 
		f 4 234 28 -236 -28 
		mu 0 4 54 56 57 55 
		f 4 236 29 -238 -29 
		mu 0 4 56 58 59 57 
		f 4 238 30 -240 -30 
		mu 0 4 58 60 61 59 
		f 4 240 31 -242 -31 
		mu 0 4 60 62 63 61 
		f 4 242 32 -244 -32 
		mu 0 4 62 64 65 63 
		f 4 244 33 -246 -33 
		mu 0 4 64 66 67 65 
		f 4 246 34 -248 -34 
		mu 0 4 66 68 69 67 
		f 4 248 35 -250 -35 
		mu 0 4 68 70 71 69 
		f 4 250 36 -252 -36 
		mu 0 4 70 72 73 71 
		f 4 252 37 -254 -37 
		mu 0 4 72 74 75 73 
		f 4 254 38 -256 -38 
		mu 0 4 74 76 77 75 
		f 4 256 39 -258 -39 
		mu 0 4 76 78 79 77 
		f 4 258 40 -260 -40 
		mu 0 4 78 80 81 79 
		f 4 260 41 -262 -41 
		mu 0 4 80 82 83 81 
		f 4 262 42 -264 -42 
		mu 0 4 82 84 85 83 
		f 4 264 43 -266 -43 
		mu 0 4 84 86 87 85 
		f 4 266 44 -268 -44 
		mu 0 4 86 88 89 87 
		f 4 268 45 -270 -45 
		mu 0 4 88 90 91 89 
		f 4 270 46 -272 -46 
		mu 0 4 90 92 93 91 
		f 4 272 47 -274 -47 
		mu 0 4 92 94 95 93 
		f 4 274 48 -276 -48 
		mu 0 4 94 96 97 95 
		f 4 276 49 -278 -49 
		mu 0 4 96 98 99 97 
		f 4 278 50 -280 -50 
		mu 0 4 98 100 101 99 
		f 4 280 51 -282 -51 
		mu 0 4 100 102 103 101 
		f 4 282 52 -284 -52 
		mu 0 4 102 104 105 103 
		f 4 284 53 -286 -53 
		mu 0 4 104 106 107 105 
		f 4 286 54 -288 -54 
		mu 0 4 106 108 109 107 
		f 4 288 55 -290 -55 
		mu 0 4 108 110 111 109 
		f 4 290 56 -292 -56 
		mu 0 4 110 112 113 111 
		f 4 292 57 -294 -57 
		mu 0 4 112 114 115 113 
		f 4 294 58 -296 -58 
		mu 0 4 114 116 117 115 
		f 4 296 59 -298 -59 
		mu 0 4 116 118 119 117 
		f 4 298 60 -300 -60 
		mu 0 4 118 120 121 119 
		f 4 300 61 -302 -61 
		mu 0 4 120 122 123 121 
		f 4 302 62 -304 -62 
		mu 0 4 122 124 125 123 
		f 4 304 63 -306 -63 
		mu 0 4 124 126 127 125 
		f 4 306 64 -308 -64 
		mu 0 4 126 128 129 127 
		f 4 308 65 -310 -65 
		mu 0 4 128 130 131 129 
		f 4 310 66 -312 -66 
		mu 0 4 130 132 133 131 
		f 4 312 67 -314 -67 
		mu 0 4 132 134 135 133 
		f 4 314 68 -316 -68 
		mu 0 4 134 136 137 135 
		f 4 316 69 -318 -69 
		mu 0 4 136 138 139 137 
		f 4 318 70 -320 -70 
		mu 0 4 138 140 141 139 
		f 4 320 71 -322 -71 
		mu 0 4 140 142 143 141 
		f 4 322 72 -324 -72 
		mu 0 4 142 144 145 143 
		f 4 324 73 -326 -73 
		mu 0 4 144 146 147 145 
		f 4 326 74 -328 -74 
		mu 0 4 146 148 149 147 
		f 4 328 75 -330 -75 
		mu 0 4 148 150 151 149 
		f 4 330 76 -332 -76 
		mu 0 4 150 152 153 151 
		f 4 332 77 -334 -77 
		mu 0 4 152 154 155 153 
		f 4 334 78 -336 -78 
		mu 0 4 154 156 157 155 
		f 4 336 79 -338 -79 
		mu 0 4 156 158 159 157 
		f 4 338 80 -340 -80 
		mu 0 4 158 160 161 159 
		f 4 340 81 -342 -81 
		mu 0 4 160 162 163 161 
		f 4 342 82 -344 -82 
		mu 0 4 162 164 165 163 
		f 4 344 83 -346 -83 
		mu 0 4 164 166 167 165 
		f 4 346 84 -348 -84 
		mu 0 4 166 168 169 167 
		f 4 348 85 -350 -85 
		mu 0 4 168 170 171 169 
		f 4 350 86 -352 -86 
		mu 0 4 170 172 173 171 
		f 4 352 87 -354 -87 
		mu 0 4 172 174 175 173 
		f 4 354 88 -356 -88 
		mu 0 4 174 176 177 175 
		f 4 356 89 -358 -89 
		mu 0 4 176 178 179 177 
		f 4 358 90 -360 -90 
		mu 0 4 178 180 181 179 
		f 4 360 91 -362 -91 
		mu 0 4 180 182 183 181 
		f 4 362 92 -364 -92 
		mu 0 4 182 184 185 183 
		f 4 364 93 -366 -93 
		mu 0 4 184 186 187 185 
		f 4 366 94 -368 -94 
		mu 0 4 186 188 189 187 
		f 4 368 95 -370 -95 
		mu 0 4 188 190 191 189 
		f 4 370 96 -372 -96 
		mu 0 4 190 192 193 191 
		f 4 372 97 -374 -97 
		mu 0 4 192 194 195 193 
		f 4 374 98 -376 -98 
		mu 0 4 194 196 197 195 
		f 4 376 99 -378 -99 
		mu 0 4 196 198 199 197 
		f 4 378 100 -380 -100 
		mu 0 4 198 200 201 199 
		f 4 380 101 -382 -101 
		mu 0 4 200 202 203 201 
		f 4 382 102 -384 -102 
		mu 0 4 202 204 205 203 
		f 4 384 103 -386 -103 
		mu 0 4 204 206 207 205 
		f 4 386 104 -388 -104 
		mu 0 4 206 208 209 207 
		f 4 388 105 -390 -105 
		mu 0 4 208 210 211 209 
		f 4 390 106 -392 -106 
		mu 0 4 210 212 213 211 
		f 4 392 107 -394 -107 
		mu 0 4 212 214 215 213 
		f 4 394 108 -396 -108 
		mu 0 4 214 216 217 215 
		f 4 396 109 -398 -109 
		mu 0 4 216 218 219 217 
		f 4 398 110 -400 -110 
		mu 0 4 218 220 221 219 
		f 4 400 111 -402 -111 
		mu 0 4 220 222 223 221 
		f 4 402 112 -404 -112 
		mu 0 4 222 224 225 223 
		f 4 404 113 -406 -113 
		mu 0 4 224 226 227 225 
		f 4 406 114 -408 -114 
		mu 0 4 226 228 229 227 
		f 4 408 115 -410 -115 
		mu 0 4 228 230 231 229 
		f 4 410 116 -412 -116 
		mu 0 4 230 232 233 231 
		f 4 412 117 -414 -117 
		mu 0 4 232 234 235 233 
		f 4 414 118 -416 -118 
		mu 0 4 234 236 237 235 
		f 4 416 119 -418 -119 
		mu 0 4 236 238 239 237 
		f 4 418 120 -420 -120 
		mu 0 4 238 240 241 239 
		f 4 420 121 -422 -121 
		mu 0 4 240 242 243 241 
		f 4 422 122 -424 -122 
		mu 0 4 242 244 245 243 
		f 4 424 123 -426 -123 
		mu 0 4 244 246 247 245 
		f 4 426 124 -428 -124 
		mu 0 4 246 248 249 247 
		f 4 428 125 -430 -125 
		mu 0 4 248 250 251 249 
		f 4 430 126 -432 -126 
		mu 0 4 250 252 253 251 
		f 4 432 127 -434 -127 
		mu 0 4 252 254 255 253 
		f 4 434 128 -436 -128 
		mu 0 4 254 256 257 255 
		f 4 436 129 -438 -129 
		mu 0 4 256 258 259 257 
		f 4 438 130 -440 -130 
		mu 0 4 258 260 261 259 
		f 4 440 131 -442 -131 
		mu 0 4 260 262 263 261 
		f 4 442 132 -444 -132 
		mu 0 4 262 264 265 263 
		f 4 444 133 -446 -133 
		mu 0 4 264 266 267 265 
		f 4 446 134 -448 -134 
		mu 0 4 266 268 269 267 
		f 4 448 135 -450 -135 
		mu 0 4 268 270 271 269 
		f 4 450 136 -452 -136 
		mu 0 4 270 272 273 271 
		f 4 452 137 -454 -137 
		mu 0 4 272 274 275 273 
		f 4 454 138 -456 -138 
		mu 0 4 274 276 277 275 
		f 4 456 139 -458 -139 
		mu 0 4 276 278 279 277 
		f 4 458 140 -460 -140 
		mu 0 4 278 280 281 279 
		f 4 460 141 -462 -141 
		mu 0 4 280 282 283 281 
		f 4 462 142 -464 -142 
		mu 0 4 282 284 285 283 
		f 4 464 143 -466 -143 
		mu 0 4 284 286 287 285 
		f 4 466 144 -468 -144 
		mu 0 4 286 288 289 287 
		f 4 468 145 -470 -145 
		mu 0 4 288 290 291 289 
		f 4 470 146 -472 -146 
		mu 0 4 290 292 293 291 
		f 4 472 147 -474 -147 
		mu 0 4 292 294 295 293 
		f 4 474 148 -476 -148 
		mu 0 4 294 296 297 295 
		f 4 476 149 -478 -149 
		mu 0 4 296 298 299 297 
		f 4 478 150 -480 -150 
		mu 0 4 298 300 301 299 
		f 4 480 151 -482 -151 
		mu 0 4 300 302 303 301 
		f 4 482 152 -484 -152 
		mu 0 4 302 304 305 303 
		f 4 484 153 -486 -153 
		mu 0 4 304 306 307 305 
		f 4 486 154 -488 -154 
		mu 0 4 306 308 309 307 
		f 4 488 155 -490 -155 
		mu 0 4 308 310 311 309 
		f 4 490 156 -492 -156 
		mu 0 4 310 312 313 311 
		f 4 492 157 -494 -157 
		mu 0 4 312 314 315 313 
		f 4 494 158 -496 -158 
		mu 0 4 314 316 317 315 
		f 4 496 159 -498 -159 
		mu 0 4 316 318 319 317 
		f 4 498 160 -500 -160 
		mu 0 4 318 320 321 319 
		f 4 500 161 -502 -161 
		mu 0 4 320 322 323 321 
		f 4 502 162 -504 -162 
		mu 0 4 322 324 325 323 
		f 4 504 163 -506 -163 
		mu 0 4 324 326 327 325 
		f 4 506 164 -508 -164 
		mu 0 4 326 328 329 327 
		f 4 508 165 -510 -165 
		mu 0 4 328 330 331 329 
		f 4 510 166 -512 -166 
		mu 0 4 330 332 333 331 
		f 4 512 167 -514 -167 
		mu 0 4 332 334 335 333 
		f 4 514 168 -516 -168 
		mu 0 4 334 336 337 335 
		f 4 516 169 -518 -169 
		mu 0 4 336 338 339 337 
		f 4 518 170 -520 -170 
		mu 0 4 338 340 341 339 
		f 4 520 171 -522 -171 
		mu 0 4 340 342 343 341 
		f 4 522 172 -524 -172 
		mu 0 4 342 344 345 343 
		f 4 524 173 -526 -173 
		mu 0 4 344 346 347 345 
		f 4 526 174 -528 -174 
		mu 0 4 346 348 349 347 
		f 4 528 175 -530 -175 
		mu 0 4 348 350 351 349 
		f 4 530 176 -532 -176 
		mu 0 4 350 352 353 351 
		f 4 532 177 -534 -177 
		mu 0 4 352 354 355 353 
		f 4 534 178 -536 -178 
		mu 0 4 354 356 357 355 
		f 4 536 179 -538 -179 
		mu 0 4 356 358 359 357 
		f 4 538 0 -540 -180 
		mu 0 4 358 360 361 359 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "RHan" -p "MoxMotion:RightHand";
	setAttr ".r" -type "double3" -54.802530836149479 -89.999950746814505 146.30993779447033 ;
	setAttr ".s" -type "double3" 0.99999999999999989 1 1 ;
createNode transform -n "Sp10" -p "RHan";
	setAttr ".sh" -type "double3" -3.0366745444851098e-007 -3.656402807395388e-009 
		0 ;
createNode transform -n "REl" -p "MoxMotion:RightElbow";
	setAttr ".r" -type "double3" 179.99998088302615 -0.0015275834564813118 0.83626456116271841 ;
	setAttr ".s" -type "double3" 0.7 0.7 0.7 ;
createNode transform -n "Sp6" -p "REl";
	setAttr ".sh" -type "double3" -3.036424430996763e-007 -3.6332987410758018e-009 
		0 ;
createNode transform -n "RSh" -p "MoxMotion:RightShoulder";
	setAttr ".r" -type "double3" 179.99943654134702 -0.050265045433304498 0.53481206395727476 ;
	setAttr ".s" -type "double3" 0.99999999999999989 1.0000000000000002 0.99999999999999978 ;
createNode transform -n "Sp7" -p "RSh";
	setAttr ".sh" -type "double3" -3.0364244310234075e-007 -3.6332987409232767e-009 
		0 ;
createNode transform -n "Neck" -p "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine";
	setAttr ".r" -type "double3" -91.780863263804363 -89.999933318160132 2.935665047872396 ;
	setAttr ".s" -type "double3" 1.7 1.7 1.7 ;
createNode transform -n "Sp12" -p "Neck";
	setAttr ".sh" -type "double3" 1.5020892724786215e-008 5.538801082102252e-008 5.9362802861031213e-010 ;
createNode joint -n "MoxMotion:RightHip" -p "MoxMotion:CenterRoot";
	setAttr ".t" -type "double3" -0.32689364291011813 -0.91450060940528566 -1.5120431005044566e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 2.257439213068704e-005 -1.2808529819911505e-005 -0.00071050639733995094 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" -90 5.1944289077348262 125.16504308022188 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 2;
	setAttr ".radi" 0.62889150314120401;
	setAttr ".hni" 5;
createNode joint -n "MoxMotion:RightKnee" -p "MoxMotion:RightHip";
	setAttr ".t" -type "double3" -3.4919018784129516 -2.0294878471105449e-006 -5.6982086755752448e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" -6.0099981279096731e-005 3.6419290962861543e-005 -0.001408538530064036 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 180 -5.4092182082754634e-016 -10.228030639611601 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 3;
	setAttr ".radi" 0.63223911916956865;
	setAttr ".hni" 6;
createNode joint -n "MoxMotion:RightFoot" -p "MoxMotion:RightKnee";
	setAttr ".t" -type "double3" -3.5566127394858165 -1.5663253360997942e-006 -4.5296421762319738e-006 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 4.4336239407569614e-006 -4.4845135128379638e-005 -0.00069993338200433357 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 179.99999836096626 -8.510201939192321e-007 -94.6028145148682 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 4;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 7;
createNode joint -n "MoxMotion:RightToe" -p "MoxMotion:RightFoot";
	setAttr ".t" -type "double3" -1.810644710835124 5.3479180961435446e-007 -1.963464164589368e-007 ;
	setAttr -k off -cb on ".tx";
	setAttr -k off -cb on ".ty";
	setAttr -k off -cb on ".tz";
	setAttr ".r" -type "double3" 2.0195728360844842e-007 1.3660688611692724e-005 0 ;
	setAttr -k off -cb on ".rx";
	setAttr -k off -cb on ".ry";
	setAttr -k off -cb on ".rz";
	setAttr -k off -cb on ".sx";
	setAttr -k off -cb on ".sy";
	setAttr -k off -cb on ".sz";
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 89.569213954818707 89.999998360966302 90.000001334193612 ;
	setAttr ".ssc" no;
	setAttr ".sd" 2;
	setAttr ".typ" 5;
	setAttr ".radi" 0.54192982005755885;
	setAttr ".hni" 17;
createNode transform -n "RToe" -p "MoxMotion:RightToe";
	setAttr ".r" -type "double3" -179.99999758249896 -4.888474351780731e-011 1.1140364979366022e-008 ;
	setAttr ".s" -type "double3" 0.7 0.7 0.7 ;
createNode transform -n "Sp8" -p "RToe";
	setAttr ".sh" -type "double3" 1.5020892831415534e-008 5.5388010511142193e-008 5.9362784293799183e-010 ;
createNode transform -n "RLeg" -p "MoxMotion:RightFoot";
	setAttr ".r" -type "double3" -6.8937703615083583 89.999986252251063 173.53701459332018 ;
	setAttr ".s" -type "double3" 0.99999999999999944 1 0.99999999999999956 ;
createNode transform -n "Sp13" -p "RLeg";
createNode transform -n "RKnee" -p "MoxMotion:RightKnee";
	setAttr ".r" -type "double3" -94.744492529238528 -89.992524308850122 -0.20940270448899989 ;
	setAttr ".s" -type "double3" 0.8 0.8 0.8 ;
createNode transform -n "Sp9" -p "RKnee";
	setAttr ".sh" -type "double3" 1.5020892868162682e-008 5.5388010726785592e-008 5.9362775013076852e-010 ;
createNode transform -n "Hip" -p "MoxMotion:CenterRoot";
	setAttr ".t" -type "double3" 0.32888892526051616 -0.46683358206088932 -4.1525762989822249e-008 ;
	setAttr ".r" -type "double3" 4.1664276312155601e-006 -8.2055285214964164e-006 35.16507834266644 ;
	setAttr ".s" -type "double3" 1.5202707406940197 1.5202707406940197 1.5202707406940197 ;
createNode transform -n "Sp11" -p "Hip";
createNode hikEffector -n "MoxMotion:LeftHandEff";
	setAttr ".t" -type "double3" 6.450223445892334 12.664785385131836 -15.291393671391726 ;
	setAttr -av ".tz";
	setAttr ".r" -type "double3" -0.00029735265486465477 -0.011141214002158381 -3.4347499040486596e-005 ;
	setAttr -av ".ry";
	setAttr -av ".rx";
	setAttr ".s" -type "double3" 0.99999999999999989 1 1 ;
	setAttr ".pin" 3;
	setAttr ".ei" 3;
	setAttr -av ".rt" 1;
	setAttr -av ".rr" 1;
createNode lightLinker -n "lightLinker1";
	setAttr -s 8 ".lnk";
	setAttr -s 8 ".slnk";
createNode displayLayerManager -n "layerManager";
	setAttr ".cdl" 1;
	setAttr -s 2 ".dli[1]"  1;
	setAttr -s 2 ".dli";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode mentalrayItemsList -s -n "mentalrayItemsList";
createNode mentalrayGlobals -s -n "mentalrayGlobals";
	setAttr ".rvb" 3;
	setAttr ".ivb" no;
createNode mentalrayOptions -s -n "miDefaultOptions";
	addAttr -ci true -m -sn "stringOptions" -ln "stringOptions" -at "compound" -nc 
		3;
	addAttr -ci true -sn "name" -ln "name" -dt "string" -p "stringOptions";
	addAttr -ci true -sn "value" -ln "value" -dt "string" -p "stringOptions";
	addAttr -ci true -sn "type" -ln "type" -dt "string" -p "stringOptions";
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 2;
	setAttr ".rflr" 10;
	setAttr ".rfrr" 10;
	setAttr ".maxr" 20;
	setAttr -s 2 ".stringOptions";
	setAttr ".stringOptions[0].name" -type "string" "motion factor";
	setAttr ".stringOptions[0].value" -type "string" "1.0";
	setAttr ".stringOptions[0].type" -type "string" "scalar";
	setAttr ".stringOptions[1].name" -type "string" "rast motion factor";
	setAttr ".stringOptions[1].value" -type "string" "1.0";
	setAttr ".stringOptions[1].type" -type "string" "scalar";
createNode mentalrayFramebuffer -s -n "miDefaultFramebuffer";
createNode mentalrayOptions -s -n "miContourPreset";
createNode mentalrayOptions -s -n "Draft";
	setAttr ".maxr" 2;
createNode mentalrayOptions -s -n "DraftMotionBlur";
	setAttr ".maxr" 2;
	setAttr ".mb" 1;
	setAttr ".tconr" 1;
	setAttr ".tcong" 1;
	setAttr ".tconb" 1;
	setAttr ".tcona" 1;
createNode mentalrayOptions -s -n "DraftRapidMotion";
	setAttr ".scan" 3;
	setAttr ".rapc" 1;
	setAttr ".raps" 0.25;
	setAttr ".maxr" 2;
	setAttr ".mb" 1;
	setAttr ".tconr" 1;
	setAttr ".tcong" 1;
	setAttr ".tconb" 1;
	setAttr ".tcona" 1;
createNode mentalrayOptions -s -n "Preview";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
createNode mentalrayOptions -s -n "PreviewMotionblur";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
	setAttr ".mb" 1;
	setAttr ".tconr" 0.5;
	setAttr ".tcong" 0.5;
	setAttr ".tconb" 0.5;
	setAttr ".tcona" 0.5;
createNode mentalrayOptions -s -n "PreviewRapidMotion";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".scan" 3;
	setAttr ".rapc" 3;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
	setAttr ".mb" 1;
	setAttr ".tconr" 0.5;
	setAttr ".tcong" 0.5;
	setAttr ".tconb" 0.5;
	setAttr ".tcona" 0.5;
createNode mentalrayOptions -s -n "PreviewCaustics";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
	setAttr ".ca" yes;
	setAttr ".cc" 1;
	setAttr ".cr" 1;
createNode mentalrayOptions -s -n "PreviewGlobalIllum";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
	setAttr ".gi" yes;
	setAttr ".gc" 1;
	setAttr ".gr" 1;
createNode mentalrayOptions -s -n "PreviewFinalGather";
	setAttr ".minsp" -1;
	setAttr ".maxsp" 1;
	setAttr ".fil" 1;
	setAttr ".rflr" 2;
	setAttr ".rfrr" 2;
	setAttr ".maxr" 4;
	setAttr ".fg" yes;
createNode mentalrayOptions -s -n "Production";
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 2;
	setAttr ".rflr" 10;
	setAttr ".rfrr" 10;
	setAttr ".maxr" 20;
createNode mentalrayOptions -s -n "ProductionMotionblur";
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 2;
	setAttr ".rflr" 10;
	setAttr ".rfrr" 10;
	setAttr ".maxr" 20;
	setAttr ".mb" 2;
createNode mentalrayOptions -s -n "ProductionRapidMotion";
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 2;
	setAttr ".scan" 3;
	setAttr ".rapc" 8;
	setAttr ".raps" 2;
	setAttr ".rflr" 10;
	setAttr ".rfrr" 10;
	setAttr ".maxr" 20;
	setAttr ".mb" 2;
createNode mentalrayOptions -s -n "ProductionFineTrace";
	setAttr ".conr" 0.019999999552965164;
	setAttr ".cong" 0.019999999552965164;
	setAttr ".conb" 0.019999999552965164;
	setAttr ".minsp" 1;
	setAttr ".maxsp" 2;
	setAttr ".fil" 1;
	setAttr ".filw" 0.75;
	setAttr ".filh" 0.75;
	setAttr ".jit" yes;
	setAttr ".scan" 0;
createNode mentalrayOptions -s -n "ProductionRapidFur";
	setAttr ".conr" 0.039999999105930328;
	setAttr ".cong" 0.029999999329447746;
	setAttr ".conb" 0.070000000298023224;
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 1;
	setAttr ".filw" 1.1449999809265137;
	setAttr ".filh" 1.1449999809265137;
	setAttr ".jit" yes;
	setAttr ".scan" 3;
	setAttr ".rapc" 3;
	setAttr ".raps" 0.25;
	setAttr ".ray" no;
	setAttr ".shmth" 3;
	setAttr ".shmap" 3;
	setAttr ".mbsm" no;
	setAttr ".bism" 0.019999999552965164;
createNode mentalrayOptions -s -n "ProductionRapidHair";
	setAttr ".conr" 0.039999999105930328;
	setAttr ".cong" 0.029999999329447746;
	setAttr ".conb" 0.070000000298023224;
	setAttr ".minsp" 0;
	setAttr ".maxsp" 2;
	setAttr ".fil" 1;
	setAttr ".filw" 1.1449999809265137;
	setAttr ".filh" 1.1449999809265137;
	setAttr ".jit" yes;
	setAttr ".scan" 3;
	setAttr ".rapc" 6;
	setAttr ".ray" no;
	setAttr ".shmth" 3;
	setAttr ".shmap" 3;
	setAttr ".mbsm" no;
	setAttr ".bism" 0.019999999552965164;
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"Stereo\" -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels `;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"MoxrenderCam\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n"
		+ "                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n"
		+ "                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"MoxrenderCam\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n"
		+ "                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n"
		+ "                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                $editorName;\nstereoCameraView -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n"
		+ "                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 1\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n"
		+ "                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n"
		+ "            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n"
		+ "            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"MoxrenderCam\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 1\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n"
		+ "                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n"
		+ "                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 0\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"MoxrenderCam\" \n"
		+ "            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n"
		+ "            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 0\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n"
		+ "                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 1\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n"
		+ "                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 0\n                -nParticles 1\n                -nRigids 0\n                -dynamicConstraints 0\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n"
		+ "                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n"
		+ "            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n"
		+ "            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 0\n            -nParticles 1\n            -nRigids 0\n            -dynamicConstraints 0\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n"
		+ "                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n"
		+ "                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n"
		+ "            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n"
		+ "            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 0\n                -showConnected 1\n                -showAnimCurvesOnly 0\n                -showMuteInfo 1\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n"
		+ "                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 1\n            -showAttributes 0\n            -showConnected 1\n            -showAnimCurvesOnly 0\n            -showMuteInfo 1\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n"
		+ "            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n"
		+ "                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n"
		+ "                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n"
		+ "                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n"
		+ "                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -constrainDrag 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n"
		+ "                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n"
		+ "                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n"
		+ "                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n"
		+ "                -snapValue \"none\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy1\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy1\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 1\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n"
		+ "                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy1\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 1\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n"
		+ "                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"multiListerPanel\" (localizedPanelLabel(\"Multilister\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"multiListerPanel\" -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"devicePanel\" (localizedPanelLabel(\"Devices\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tdevicePanel -unParent -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tdevicePanel -edit -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"webBrowserPanel\" (localizedPanelLabel(\"Web Browser\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"webBrowserPanel\" -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Manual TTL Dragger View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Manual TTL Dragger View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"all\" \n"
		+ "                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n"
		+ "                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Manual TTL Dragger View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"all\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n"
		+ "            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n"
		+ "            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n"
		+ "                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n"
		+ "                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 0\n                -nParticles 1\n                -nRigids 0\n                -dynamicConstraints 0\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n"
		+ "            -nCloths 0\n            -nParticles 1\n            -nRigids 0\n            -dynamicConstraints 0\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n"
		+ "                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n"
		+ "                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n"
		+ "                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n"
		+ "            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n"
		+ "            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n"
		+ "                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n"
		+ "                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 0\n                -nParticles 1\n                -nRigids 0\n                -dynamicConstraints 0\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n"
		+ "            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n"
		+ "            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 0\n            -nParticles 1\n            -nRigids 0\n            -dynamicConstraints 0\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n"
		+ "            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n"
		+ "                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n"
		+ "                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n"
		+ "                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n"
		+ "            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n"
		+ "                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n"
		+ "                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n"
		+ "                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n"
		+ "            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n"
		+ "            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -showShapes 0\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n"
		+ "                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 0\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n"
		+ "            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n"
		+ "                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n"
		+ "                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n"
		+ "                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n"
		+ "            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n"
		+ "            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n"
		+ "                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 0\n                -polymeshes 0\n"
		+ "                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 0\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 0\n                -manipulators 1\n                -dimensions 0\n                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n"
		+ "            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n"
		+ "            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 0\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 0\n            -manipulators 1\n            -dimensions 0\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Model Panel15\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Model Panel15\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n"
		+ "                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 1\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n"
		+ "                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 0\n                -nurbsSurfaces 0\n                -polymeshes 1\n                -subdivSurfaces 0\n                -planes 0\n                -lights 0\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n                -joints 1\n                -ikHandles 0\n                -deformers 0\n                -dynamics 0\n                -fluids 0\n                -hairSystems 0\n                -follicles 0\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n"
		+ "                -handles 0\n                -pivots 0\n                -textures 0\n                -strokes 0\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Model Panel15\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 1\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n"
		+ "            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 0\n            -nurbsSurfaces 0\n            -polymeshes 1\n"
		+ "            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -joints 1\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n"
		+ "\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 36 100 -ps 2 64 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n\t\t\t\t\t\"outlinerPanel\"\n\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 1\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 1\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 1\\n    -showAttributes 0\\n    -showConnected 1\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 1\\n    -organizeByLayer 1\\n    -showAnimLayerWeight 1\\n    -autoExpandLayers 1\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -showAssets 1\\n    -showContainedOnly 1\\n    -showPublishedAsConnected 0\\n    -showContainerContents 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -containersIgnoreFilters 0\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -animLayerFilterOptions \\\"allAffecting\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 1000 -ast 1 -aet 1500 ";
	setAttr ".st" 6;
createNode animCurveTA -n "CenterRootFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -8.1318792614006323e-006 57 -5.6413007549149752 
		62 -12.965125146014159 65 -14.495910337302552 68 -16.131845813700888 71 -28.756855208296518 
		76 -47.158311062492274 80 -45.419989659058871 87 -36.061103796613317 91 -28.475680662408177 
		96 -21.621005363867276 100 -21.648131793556111 105 -22.770402715097191 109 -22.418292718006619 
		117 -20.249741236691527 128 -19.545564649093311 139 -22.413040358361823 151 -22.77138050999152 
		164 -22.49188914904212 192 -22.49188914904212 196 -22.491890999002209 202 -22.49188975777405 
		238 -22.49188975777405 248 -22.491889829948512 259 -22.49189019331007 271 -22.491890255008208 
		331 -22.491890255008208 345 -22.491889054887078 364 -22.491889306829485 379 -22.443078025677202 
		390 -31.56556124564284 393 -35.717918228623269 398 6.644790791264179 416 2.9032305442461732 
		420 -7.6926894571362885 428 -17.60002784811206 439 -18.085145814175085 456 -19.965597326221893 
		490 -19.965600233956206 499 -19.965600233956206 508 -19.965600233956206 624 -19.965600233956206 
		644 -19.965581521094514 655 -19.965581372227991 666 -19.965580678153977 677 -19.965580513973162 
		682 -23.44021476271574 686 -32.605779937981787 690 -43.133665544738321 695 -37.776103656228941 
		704 -40.264171247337323 723 -37.776103656228941 735 -37.283265083574179 741 -37.333670341509524 
		749 -37.688039632824683 757 -38.412408164172192 767 -38.574193722617288 792 -38.574194473783493 
		815 -38.574193997107692 841 -38.574172057348321 858 -38.57416774199752 880 -38.574151877027461;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterRootFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -3.5160532939961126e-005 57 -12.982241375015011 
		62 -5.0227820852311176 65 5.7193595504379786 68 26.310706358331732 71 15.646760042333479 
		76 7.4719915420124945 80 4.7187450718630597 87 2.0556948120009579 91 1.5310741735510329 
		96 0.11494708699554661 100 2.3757262405548514 105 6.5913754749830371 109 7.3587925942428134 
		117 9.2372864483733572 128 9.8753844014138856 139 6.690006588478175 151 6.2819540735483281 
		164 6.60042937175192 192 6.60042937175192 196 6.6004272826744206 202 6.6004272164223172 
		238 6.6004272164223172 248 6.600427081014705 259 6.6004263993064756 271 6.6004262835536487 
		331 6.6004262835536487 345 6.600431677062411 364 6.6004338430603253 379 6.5916240672956672 
		390 1.0928908353102416 393 -1.4214181846500069 398 -19.556862073395347 416 -22.018161812133471 
		420 -10.77653921525525 428 -9.0818338249217341 439 -1.3814051827790594 456 6.1444722368965232 
		490 6.1444730268439454 499 6.1444730268439454 508 6.1444730268439454 624 6.1444730268439454 
		644 6.1444823078768502 655 6.1444823929209926 666 6.1444827894300937 677 6.1444828832229517 
		682 5.1690119391949656 686 3.3332244547373584 690 8.145039268504652 695 0.2454514918100256 
		704 1.3574414121276073 723 0.2454514918100254 735 -2.6182709338969063 741 -4.3897389223686192 
		749 -6.9866054484110238 757 -9.5244031848122344 767 -10.756488178887276 792 -10.756489015389473 
		815 -10.7564890063388 841 -10.756468371521702 858 -10.756464312841166 880 -10.756453195212359;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterRootFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -4.3083996332340784e-006 57 6.032791375731696 
		62 10.815041331224824 65 13.067579971667904 68 7.2379294492217223 71 -18.847847559722425 
		76 -36.020199316669057 80 -39.380826439206068 87 -42.131690592954399 91 -36.380755709873817 
		96 -27.713245964994282 100 -26.102613262268516 105 -26.41107065026549 109 -27.005097586893772 
		117 -29.879282755966891 128 -30.907792098004425 139 -32.817132086451728 151 -33.065544147563152 
		164 -32.871595328438971 192 -32.871595328438971 196 -32.871595948035058 202 -32.871593992098433 
		238 -32.871593992098433 248 -32.871594130123256 259 -32.871594825007776 271 -32.871594942997916 
		331 -32.871594942997916 345 -32.871596300131451 364 -32.871598057334666 379 -32.899092281019989 
		390 -32.272254190071827 393 -28.475565105419996 398 -67.266310338999162 416 -52.201851449346393 
		420 -52.992768721394832 428 -16.74839818659429 439 -20.385534394595265 456 -34.294588786154883 
		490 -34.294595481185674 499 -34.294595481185674 508 -34.294595481185674 624 -34.294595481185674 
		644 -34.294566765016732 655 -34.294566657323152 666 -34.294566155213488 677 -34.294566036441182 
		682 -40.7627001175685 686 -55.374624116030454 690 -49.163573846680798 695 -47.935382142857208 
		704 -46.563132549475824 723 -47.935382142857208 735 -45.379095084765829 741 -43.864220065427901 
		749 -41.8315455250669 757 -39.744810016681029 767 -39.278743302457308 792 -39.278744650156291 
		815 -39.27874498219952 841 -39.278731755184175 858 -39.278729153550756 880 -39.278714409891265;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftToeFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 0 62 0 65 -1.4675510126791996e-006 
		68 0 71 -5.3380494433917102e-005 76 -4.1105740567957564e-005 80 -3.9488937431784798e-005 
		87 -3.4519959737658391e-005 91 -3.6307953066646351e-005 96 -3.1701871314019111e-005 
		100 -2.7568077496441973e-005 105 -3.1850473982217633e-005 109 -3.3700714476308635e-005 
		117 -3.2594247965013458e-005 128 -3.1497908245976285e-005 139 -3.2601087512677174e-005 
		151 -3.1913745791821865e-005 164 -3.1535279194988718e-005 192 -3.1535279194988718e-005 
		196 -3.1500215629663972e-005 202 -3.1247857978484341e-005 238 -3.180091845477253e-005 
		248 -3.1574428809853782e-005 259 -3.043416903120349e-005 271 -3.0240554977655766e-005 
		331 -3.0240554977655766e-005 345 -2.9781856722191397e-005 364 -2.9794386950883495e-005 
		379 -2.9815532543914208e-005 390 -2.2854645224892831e-005 393 -2.5108112380509122e-005 
		398 -1.7441942687170964e-005 416 -1.626613804405558e-005 420 -2.2717990567333528e-005 
		428 -2.3837938706426266e-005 439 -2.5518510836815586e-005 456 -3.0100573283699351e-005 
		490 -3.0148771935255958e-005 499 -2.9804892125125199e-005 508 -3.0687377173931843e-005 
		624 -2.9156380836193893e-005 644 -2.9731853761198603e-005 655 -2.9779774787305308e-005 
		666 -3.0003201383500855e-005 677 -3.0056052172839557e-005 682 -2.835687790772155e-005 
		686 -1.9730849847754916e-005 690 -1.8371614997443102e-005 695 -1.2989306473951296e-005 
		704 -1.0384203060416476e-005 723 -1.4028392906398055e-005 735 -1.1754635655825769e-005 
		741 -9.8731325860681216e-006 749 -9.8328252593892662e-006 757 -1.0765053967358764e-005 
		767 -1.0689747728043708e-005 792 -1.092152166038717e-005 815 -1.0830334474152498e-005 
		841 -9.5643410382672542e-006 858 -9.3153316627850431e-006 880 -6.4554959625205126e-006;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftToeFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 1.3310212174627646e-005 57 0.00021427339027695592 
		62 7.5115535584692713e-005 65 0.00011497049376840437 68 0.00010551553795895983 71 
		-0.0003585537639635657 76 -0.00049046159276981271 80 -0.00062010434238102946 87 -0.00087115530727417179 
		91 -0.00080147006569226042 96 -0.0011714119928318788 100 -0.0015228268313270562 105 
		-0.00097186923666110845 109 -0.0010146849929659663 117 -0.0010217374411835337 128 
		-0.0010326826381026545 139 -0.0010141352900467039 151 -0.0010983855965518757 164 
		-0.0010303513676764365 192 -0.0010303513676764365 196 -0.0010982687742562074 202 
		-0.0011527623889029382 238 -0.0011269483668076162 248 -0.0011543382633737841 259 
		-0.0012922324148127915 271 -0.0013156465929856215 331 -0.0013156465929856215 345 
		-0.0014395759695267571 364 -0.0014473963786899723 379 -0.001448000637031746 390 -0.0020373589490599443 
		393 -0.0020391890503392391 398 -0.00241729613072177 416 -0.0026100354826804877 420 
		-0.0023221130295220838 428 -0.0018844247918218555 439 -0.0017919274610470864 456 
		-0.0015130613973281385 490 -0.001588527154813533 499 -0.0015533544311567421 508 -0.0015836643825729681 
		624 -0.0016685141667166479 644 -0.0017062884871585386 655 -0.0017001904632370952 
		666 -0.001671759086887736 677 -0.0016650337430493764 682 -0.0018230478118766405 686 
		-0.002231342676169981 690 -0.0023241355844550388 695 -0.0027816639998896218 704 -0.0029188931554109928 
		723 -0.0027558563004414097 735 -0.0028837375075267718 741 -0.0030062809548602075 
		749 -0.0029889120589557563 757 -0.002996080432827463 767 -0.0030072903638482065 792 
		-0.0030051281477160596 815 -0.0030057082458084384 841 -0.0031336097331418401 858 
		-0.003158766790501988 880 -0.0033421831773442004;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftToeFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 0 62 0 65 0 68 0 71 1.934090046211793e-005 
		76 1.6332529230166878e-005 80 1.5054022827001552e-005 87 1.0799118109211867e-005 
		91 5.1971773767996873e-006 96 0 100 0 105 1.0668470555908593e-005 109 9.7585153361971693e-006 
		117 1.095482725923446e-005 128 1.0311735545766122e-005 139 1.3080687385196643e-005 
		151 9.838600128780217e-006 164 1.158337254102569e-005 192 1.158337254102569e-005 
		196 1.1212618360805387e-005 202 1.0734521755826589e-005 238 1.0709900673266561e-005 
		248 1.0469301376738069e-005 259 9.2580067027523652e-006 271 9.0523310521135728e-006 
		331 9.0523310521135728e-006 345 4.3854796745868705e-006 364 4.1780641013561985e-006 
		379 4.1492013814823783e-006 390 0 393 -1.0434740301758682e-005 398 -1.9683956238372771e-005 
		416 -2.6872289599680719e-005 420 -1.49909330173805e-005 428 0 439 0 456 0 490 -1.2226770585137805e-006 
		499 0 508 0 624 0 644 1.6343721482021463e-006 655 1.7391567900355576e-006 666 2.2277038383871297e-006 
		677 2.3432679546299203e-006 682 1.9154560661919595e-006 686 0 690 -9.1032966130572349e-006 
		695 -1.6363127965026293e-005 704 -2.1144463726761217e-005 723 -1.5854324106351252e-005 
		735 -1.7226928468656929e-005 741 -2.351513861288014e-005 749 -2.0350392442227153e-005 
		757 -2.0739028693663899e-005 767 -2.0845972153848468e-005 792 -2.180364953156014e-005 
		815 -2.2352974796489099e-005 841 -2.7038918204818129e-005 858 -2.7960600583713783e-005 
		880 -2.9665202836916149e-005;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftFootFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -3.4673055977256032e-005 57 -12.657121836272175 
		62 -22.077474139171482 65 -38.898029235167243 68 -57.334287229825989 71 -46.421577999851706 
		76 -36.348118100410687 80 -43.398519944147679 87 -46.884373248964913 91 -50.595321612722671 
		96 -54.408583151969594 100 -55.588784840874666 105 -57.518594346022134 109 -57.381902569660532 
		117 -46.838191069231357 128 -46.57257913809098 139 -52.872592023572437 151 -53.081668785364023 
		164 -53.065238072717662 192 -53.065238072717662 196 -53.065202010905345 202 -53.065069196913512 
		238 -53.064954701053438 248 -53.064150945445981 259 -53.06010444613969 271 -53.059417357856795 
		331 -53.059417357856795 345 -55.208243483349584 364 -56.778482512676035 379 -56.803885163769046 
		390 -32.071367614698623 393 -32.952782825532623 398 -32.621399034966764 416 -25.309856241659858 
		420 -44.769401795116941 428 -48.727324296563239 439 -49.462385265732827 456 -56.798334522878768 
		490 -58.098341513306949 499 -58.098327594676881 508 -58.098330468685838 624 -58.096954196378711 
		644 -56.945836379616658 655 -56.94491677208142 666 -56.940629201506944 677 -56.939614991502118 
		682 -54.225978785398098 686 -47.499849659982587 690 -43.830201154443486 695 -43.824859300818716 
		704 -42.928633718553499 723 -43.824835146878655 735 -42.855282238384561 741 -41.977325998347176 
		749 -40.626408002990551 757 -39.464135097337291 767 -39.204519485077114 792 -39.203007894747749 
		815 -39.203043713122952 841 -39.202999827887552 858 -39.202991196061554 880 -39.202905941539882;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftFootFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 3.595458641461135e-005 57 5.5733334943945065 
		62 6.5412386443691091 65 7.3688849803183052 68 -2.2172463572641403 71 -17.325589704732288 
		76 -13.77817720009191 80 -6.6831146657059195 87 2.0991013207528346 91 3.4559253005084574 
		96 3.3460449221484487 100 1.2813093174578365 105 -2.5371891597063874 109 -7.0400880221937694 
		117 -17.390633329879257 128 -17.539545315336611 139 -14.167477786019621 151 -13.953123406580497 
		164 -14.251181693398534 192 -14.251181693398534 196 -14.251143237434963 202 -14.251220112939606 
		238 -14.251304293749349 248 -14.251756396569391 259 -14.254032503548551 271 -14.254418982407838 
		331 -14.254418982407838 345 -13.265911250602635 364 -12.787520162708583 379 -12.791681349347757 
		390 1.6792668663780737 393 -0.19366706191034377 398 -1.3734923089037494 416 3.2595727803936589 
		420 -0.89435028069566758 428 -17.977908550004866 439 -17.455592319903936 456 -14.05479303652419 
		490 -12.997364636717354 499 -12.997401989901293 508 -12.997371309295108 624 -12.99895442608209 
		644 -13.872425076598349 655 -13.873260254940179 666 -13.877154183540867 677 -13.878075278896922 
		682 -14.914045999533945 686 -17.306669126665657 690 -16.887340584066724 695 -16.918152898001946 
		704 -16.815752369413808 723 -16.918173582211875 735 -16.780018288422365 741 -16.70118590989815 
		749 -16.632069694536597 757 -16.704921339638407 767 -16.721166946716487 792 -16.719113588876596 
		815 -16.719159722892808 841 -16.719132998563296 858 -16.719127742131143 880 -16.71898047786814;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftFootFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0029514288043624493 57 26.939593127454952 
		62 26.043936500863829 65 11.463810266665135 68 -13.260283706968416 71 -48.326269714077611 
		76 -49.61766785935157 80 -30.98111183900912 87 -4.368782845270931 91 -1.8591070926536208 
		96 -2.7038278150583346 100 -6.5388694181173284 105 -13.828339239498698 109 -22.007786425678724 
		117 -48.739120009687021 128 -48.646726055367573 139 -37.359047519320299 151 -36.739286428411319 
		164 -36.907705841281746 192 -36.907705841281746 196 -36.907683215766681 202 -36.907908124775325 
		238 -36.90818271308472 248 -36.909513032007347 259 -36.916210508886643 271 -36.917347728379447 
		331 -36.917347728379447 345 -34.347041723626575 364 -32.243635954868694 379 -32.239284164538432 
		390 -2.578880555630477 393 -10.074147442780609 398 -14.113654905549156 416 4.715030040000542 
		420 -8.9022033035451624 428 -47.294839725727329 439 -47.358306601408664 456 -34.508360231228444 
		490 -32.006496559848216 499 -32.00651664022633 508 -32.006501070892654 624 -32.009910040363806 
		644 -34.107543773392962 655 -34.10949809626112 666 -34.118609915054961 677 -34.120765284307176 
		682 -37.879533366028411 686 -46.928548188519422 690 -49.243363513729939 695 -49.318443513984022 
		704 -49.933195334057004 723 -49.318437193578667 735 -50.007769479237339 741 -50.73107684590979 
		749 -51.965338923982799 757 -53.25473684375622 767 -53.542684109243019 792 -53.539306271037567 
		815 -53.539467141166405 841 -53.53944938625785 858 -53.539445894029093 880 -53.539306758317842;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftKneeFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.00016369928944828837 57 1.0449359965389267 
		62 21.969086386444665 65 32.113256767072727 68 17.006524506489601 71 -9.2796582776588146 
		76 -6.2263310912271539 80 3.4770939182354978 87 8.0424269050298189 91 8.0195322676664063 
		96 7.0683736229616523 100 4.5791656637907998 105 -2.2977375281220178 109 -6.9936211133926269 
		117 -22.099635523982315 128 -23.142576458497651 139 -13.679182269042448 151 -13.047143443955081 
		164 -13.475534980973356 192 -13.475534980973356 196 -13.475548088138448 202 -13.475696680937803 
		238 -13.47581449258157 248 -13.476648740660602 259 -13.48084875400019 271 -13.481561908689022 
		331 -13.481561908689022 345 -11.403975920077345 364 -9.886461251025521 379 -9.924390632409354 
		390 29.05339106714224 393 31.366161838240028 398 19.883679296985957 416 24.797519232985412 
		420 17.60624976929984 428 -15.614634284580873 439 -15.115167685455534 456 -13.418670719407102 
		490 -11.842471166469883 499 -11.842513851847851 508 -11.842489177567865 624 -11.844444986946797 
		644 -13.276975443045629 655 -13.278127751215488 666 -13.283500263306252 677 -13.284771112478031 
		682 -3.327116903783979 686 20.631244700593779 690 26.467121024173004 695 26.899855470086571 
		704 28.264409626944943 723 26.899806898880989 735 28.838458334025837 741 30.401363469493475 
		749 32.695863412571597 757 34.594001751137128 767 35.017949922391047 792 35.01824666742413 
		815 35.01822974858149 841 35.018218069947117 858 35.018215772866121 880 35.018211908562897;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftKneeFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -2.1495962866131157e-005 57 0.00073481037470553496 
		62 0.00059396546895252916 65 0.00046183122143881607 68 -0.00046755886385358895 71 
		-0.00031215325486153131 76 0.0001372810010747936 80 0.00062449510640175999 87 0.0014131801110240916 
		91 0.0015658614253344185 96 0.0016893195672698694 100 0.0017398258693748267 105 0.0014962696272073713 
		109 0.0012741810161500623 117 -0.0018953861562434565 128 -0.00085808564950155949 
		139 -6.3094984854130131e-006 151 0.00010319128648946337 164 2.877620893224685e-005 
		192 2.8776208932246843e-005 196 -1.6401392463020522e-006 202 -8.8014904994918628e-007 
		238 4.2444996967362753e-006 248 4.4143359433404131e-006 259 5.2693747731690464e-006 
		271 5.414558824105035e-006 331 5.414558824105035e-006 345 7.1872331087981134e-005 
		364 0.00015708066123103868 379 0.00015717494634986156 390 0.00099012061639541533 
		393 0.0012038250212900591 398 0.00096519959598104395 416 0.0014464373980345613 420 
		0.0012534959551113454 428 -0.0009519187361174174 439 -0.00055175120691757006 456 
		1.6653404777819835e-005 490 0.00013510099789606719 499 0.00011644101557969065 508 
		0.00015903294592270464 624 0.00021619166617691912 644 0.00010065915637106947 655 
		9.9300997149782884e-005 666 9.2968726817591309e-005 677 9.1470850149992359e-005 682 
		0.00012697058955211271 686 0.00029195373944332055 690 0.00036268039614253245 695 
		0.00061026137637107934 704 0.0006539256500433891 723 0.00057371277704871149 735 0.00054390098210291532 
		741 0.00063882239174394711 749 0.00055372397375360748 757 0.00053372613863803952 
		767 0.00053132154174099751 792 0.00057285043346939001 815 0.0005198595301129375 841 
		0.00055061128777747687 858 0.00055665987835778487 880 0.0005694719881613661;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftKneeFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.0059535104953200484 57 -63.53277328650092 
		62 -73.724404704185062 65 -64.776400349822708 68 -20.1651102165882 71 10.19785381881384 
		76 -6.8321862144804104 80 -36.804729583408268 87 -78.71262353018146 91 -83.112950477909507 
		96 -82.427948741968578 100 -77.631530031359844 105 -65.835496570445756 109 -52.316402830562595 
		117 -4.0231149437387863 128 -2.0927996962495103 139 -21.976806207351881 151 -23.164705977024724 
		164 -22.980837711092814 192 -22.980837711092814 196 -22.980831803714075 202 -22.980321528742561 
		238 -22.979772395790135 248 -22.976656070942294 259 -22.960966965674476 271 -22.958302983900918 
		331 -22.958302983900918 345 -28.076923849559186 364 -32.476129517289699 379 -32.486067415731519 
		390 -86.274847720868536 393 -81.62393369228208 398 -55.197455920977447 416 -77.203798167917341 
		420 -73.813148743832357 428 -5.4690406335278157 439 -5.7477754666146561 456 -28.76754245271696 
		490 -33.013645723022137 499 -33.013658258039293 508 -33.013453717426842 624 -33.00623109011034 
		644 -29.35672359727965 655 -29.352968345268724 666 -29.335459889318937 677 -29.331318324559838 
		682 -30.345297121967999 686 -32.741231554511678 690 -32.740267758496728 695 -34.133575726692207 
		704 -34.133677204524318 723 -34.133665316717853 735 -34.952153893718837 741 -35.302511525351875 
		749 -35.620463323807556 757 -35.704971248108919 767 -35.724001799050185 792 -35.733133393294594 
		815 -35.732281151979116 841 -35.732665630194958 858 -35.732741253557371 880 -35.732815689939024;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHipFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -9.3514275698201464e-005 57 19.685106204454435 
		62 27.057455866107389 65 32.509419862657651 68 6.1710580735848124 71 10.694093300762809 
		76 15.511080441871101 80 24.502307855916261 87 34.473777081809153 91 41.48185874342645 
		96 49.93375359532844 100 48.124432555222157 105 41.925115180622029 109 39.233964548610622 
		117 16.986014428301111 128 14.318450928020802 139 28.764773756493593 151 29.798229118101883 
		164 29.443274720135207 192 29.443274720135207 196 29.443274693557061 202 29.443005058940692 
		238 29.442699466096204 248 29.440841918336986 259 29.431490113323896 271 29.429902193702009 
		331 29.429902193702009 345 32.666898069711223 364 35.405567995174479 379 35.446643443900975 
		390 37.524909097036847 393 44.818028555163963 398 25.72700408653288 416 37.641699994655397 
		420 43.175503668217509 428 43.137368205288205 439 25.90853098113265 456 35.873797727693642 
		490 37.540575568986185 499 37.540655880777216 508 37.540441956567769 624 37.537410750028421 
		644 36.03683564944167 655 36.035268396578992 666 36.027961249780773 677 36.026232769453564 
		682 29.908943242639108 686 14.829792582236463 690 7.3742766652488161 695 17.025560974990039 
		704 15.310455480744295 723 17.02568267948768 735 20.591897928961487 741 22.171173894070641 
		749 24.060912495227043 757 26.021993272320547 767 26.974232498890501 792 26.97763095189487 
		815 26.977131573585485 841 26.977290542985806 858 26.977321810818619 880 26.977153538911985;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHipFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.00011408607756730867 57 17.891856634279591 
		62 32.88373782272577 65 39.530587384774357 68 35.658897952704642 71 40.223190740058762 
		76 32.161263075860674 80 26.518570917521885 87 18.359512115227762 91 24.302422222214464 
		96 33.461286733270214 100 35.64329415933431 105 36.402221257385527 109 39.917250916162821 
		117 51.27365349290676 128 50.73277422713781 139 46.389309442975865 151 45.919637275249869 
		164 46.213292735432091 192 46.213292735432091 196 46.213247149684996 202 46.213352645986916 
		238 46.213507350546159 248 46.214316956993997 259 46.218392912295791 271 46.219085002153584 
		331 46.219085002153584 345 45.394901738295331 364 44.690259237317875 379 44.680390902847371 
		390 44.124571498434683 393 44.132506399006047 398 31.926681277433328 416 40.670091677741311 
		420 30.57561306968449 428 72.61759148647117 439 66.871799908371273 456 45.262859400495465 
		490 44.171755247873904 499 44.17174286375613 508 44.171829271117716 624 44.174467210425938 
		644 45.053099206419688 655 45.054303505382748 666 45.059918418918166 677 45.061246607314132 
		682 42.307096724279766 686 36.125479103864556 690 39.215270125629154 695 38.909129773487685 
		704 39.658304722788273 723 38.909115242962578 735 39.695599514280502 741 40.035674754149717 
		749 40.151026536759524 757 39.330600965988481 767 39.147316411881661 792 39.145324219863902 
		815 39.145605983612064 841 39.145355418301264 858 39.145306134387312 880 39.145305370122486;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHipFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0030040477914651345 57 31.236386631774035 
		62 42.970511799125291 65 52.494848632723645 68 17.935727233743528 71 21.357821400548644 
		76 32.723732489557513 80 51.520734694495388 87 74.425827048041256 91 79.797576339869849 
		96 83.154074039872299 100 79.530742391603141 105 68.502543855228581 109 63.263770343004332 
		117 35.111531158100526 128 32.327661556942154 139 51.267678935775876 151 52.618510332065071 
		164 52.214003157018681 192 52.214003157018681 196 52.213950999513983 202 52.213549815422283 
		238 52.213158868443159 248 52.210653359025137 259 52.198039397731584 271 52.195897569857735 
		331 52.195897569857735 345 56.228055060901852 364 59.781045901491716 379 59.832003874984444 
		390 93.514077735880861 393 99.331031192529878 398 119.64732686116628 416 121.16790420044445 
		420 117.08077535012511 428 62.228566142184356 439 45.77803189269202 456 60.118118629883881 
		490 62.431703175779973 499 62.431765706545683 508 62.431516830380716 624 62.427127083730618 
		644 60.298208861681118 655 60.295972625212919 666 60.285546414779454 677 60.283080130726425 
		682 69.411837653833672 686 89.65581003393828 690 76.802879427898276 695 90.996919771596609 
		704 88.211200578433321 723 90.997024430755985 735 95.939615701613533 741 98.80401478478187 
		749 102.70238406575625 757 106.1368548356502 767 107.40439852505159 792 107.40971726861348 
		815 107.40894144914984 841 107.40923028605394 858 107.40928709764165 880 107.40910414274025;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterHeadFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.0984275552391315e-005 57 -6.0496064370988734 
		62 -16.698192275822105 65 27.79150192490815 68 23.799855662776675 71 9.4804216448291889 
		76 7.9757180134323145 80 1.822503466906326 87 17.531526820528423 91 14.498411929680055 
		96 3.8887886289959805 100 2.6584885547336272 105 0.49046284999562562 109 0.061658044736296089 
		117 0.45072709645937653 128 1.5117439732532114 139 0.051629548349363515 151 -0.11893859286813598 
		164 0.016152183066761461 192 0.01615218306676186 196 -0.2274384744868973 202 -2.6160674998823934 
		238 -3.2586522960508355 248 -7.3618252674947833 259 -34.754390102057108 271 -43.733492413194156 
		331 -43.733492413194156 345 -72.899376907925983 364 -79.225317964314797 379 -79.103789512633085 
		390 -41.527106441522015 393 -67.688202841981067 398 -82.967444919904452 416 -106.70452856563341 
		420 -6.4966881554944935 428 -82.496964274606839 439 -66.516639282761574 456 -70.124457365176326 
		490 -70.078359220943995 499 -36.206990817810627 508 -37.701138194715888 624 -36.049763554740622 
		644 -55.671540740667439 655 -58.129544595177506 666 -59.711818979629975 677 -60.086100518142665 
		682 -56.06266928927792 686 -46.604484068792658 690 -64.669995419392208 695 -21.853893191981957 
		704 -17.5163400939763 723 -4.5419071143973495 735 4.4046866060200935 741 8.1841528526983112 
		749 13.520496751489256 757 20.473339469344999 767 23.152192773802746 792 23.150763417512927 
		815 23.149393694833989 841 -1.3512778512364132 858 -5.7487478927347722 880 -5.8672084060969549;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "CenterHeadFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 5.8056616949282089e-005 57 2.9234938624592108 
		62 3.2107196874713972 65 26.295902962884938 68 25.508629614509637 71 17.427448966861089 
		76 -1.956191510814961 80 -0.24464750599843663 87 10.517265247868369 91 6.5109945435529299 
		96 4.7766083869677036 100 7.1431703811557306 105 11.070668936145317 109 10.004725635297701 
		117 7.4195072754024469 128 7.3120548558979488 139 8.5269140977567766 151 8.6825919981157043 
		164 8.5930694937593337 192 8.5930694937593337 196 -16.797806658382861 202 -31.267017968983801 
		238 -31.267027260812885 248 -27.226877004632843 259 -0.25504875038735536 271 8.5861388789047126 
		331 8.5861388789047126 345 34.851509548288163 364 34.162620245758127 379 34.166928189890662 
		390 12.961895345781086 393 19.971157229396852 398 41.628608449160765 416 55.11325486299701 
		420 36.033149763632146 428 36.739624512572455 439 37.256829436740297 456 34.387862658113448 
		490 33.655286600407884 499 31.311800285714199 508 31.376243973956068 624 31.547578440678841 
		644 -0.77475664928098187 655 -7.3202741007654222 666 -16.895082232624812 677 -20.772135476299724 
		682 -25.168522544986629 686 -35.501896805500678 690 -40.653852686517993 695 -65.910713627229484 
		704 -66.311556776646867 723 -67.115979161291875 735 -67.025869254467167 741 -67.25289070617039 
		749 -68.283704246936495 757 -68.584867348251905 767 -68.652158302612193 792 -68.652427101029645 
		815 -68.652636036101356 841 -44.081819320697321 858 -39.331216729080857 880 -39.2792641217248;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "CenterHeadFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 6.659438239672982e-005 57 13.128675471525522 
		62 23.275619909940861 65 -6.6404990703052817 68 19.496954472950542 71 -0.42963372433636599 
		76 -20.386441009325171 80 -10.367256200781647 87 -15.542730344399468 91 -6.9809479476244691 
		96 3.9099218566973324 100 -2.6787154278117336 105 -16.038392658513004 109 -18.313394386957263 
		117 -23.469172126641638 128 -24.649867510668425 139 -24.661888286723148 151 -24.652700791626085 
		164 -24.623248097707094 192 -24.623248097707094 196 -7.6392856726860643 202 2.0391524556395395 
		238 2.0391434836638722 248 9.694287565259307 259 60.799621091836109 271 77.551613892803019 
		331 77.551613892803019 345 65.724114872967618 364 55.773786641205902 379 55.734398810983485 
		390 -59.327747815892856 393 -98.797242888587519 398 -48.623436783467156 416 -75.821255515363148 
		420 28.637500635393174 428 54.426228936453626 439 56.029891579853491 456 53.744432346045386 
		490 53.044549200237512 499 54.069636401913272 508 54.55368419000817 624 56.318389083471416 
		644 80.492997176475342 655 85.213242301497786 666 91.653885486064894 677 92.949814747157632 
		682 88.095617399934383 686 76.682195648654371 690 87.830304250445806 695 29.819822169224405 
		704 27.181342825600247 723 21.896570160558813 735 12.199793356949968 741 10.49836764413743 
		749 8.3449400978757371 757 4.0676786419320363 767 1.9913865239502597 792 1.992428027201568 
		815 1.9934567303894821 841 8.9502592014457836 858 9.6521628204724887 880 10.928972341815134;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "CenterNeckFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -5.4641503950215448e-005 57 0.74689625903905177 
		62 -3.081699908291843 65 18.729807175165345 68 29.822652719908934 71 16.972285587751678 
		76 0.16517272269948158 80 5.6283624948105482 87 7.9865942952839797 91 -1.4597573419414476 
		96 -3.3450159341361685 100 5.3234765402897297 105 16.924616089315776 109 16.230008295386625 
		117 14.636861582829507 128 14.309605413388667 139 16.311012713893192 151 16.569299826413637 
		164 16.394009346624124 192 16.394009346624124 196 -7.2521877606348299 202 -20.898759850999415 
		238 -20.93809606324767 248 -17.380363912431168 259 6.3708670806961694 271 14.156364667103643 
		331 14.156364667103643 345 -0.2222479243357503 364 0.92406312591417794 379 1.0684207443709077 
		390 1.0737628881163586 393 -15.617594898022183 398 14.413192481091937 416 47.453647680142616 
		420 -4.131654615294325 428 6.0361766464234794 439 9.4686496032327252 456 11.736980348333915 
		490 8.5324473242701 499 4.9202873144377399 508 5.5470850169417858 624 4.3698217565067816 
		644 61.462447484930955 655 61.374337390293725 666 44.413487375706886 677 40.401456908475943 
		682 42.247852125351706 686 46.58742947527923 690 27.698798959493896 695 45.292242939727288 
		704 45.787550193740898 723 46.05229060984086 735 46.307990998663556 741 45.963879723515589 
		749 44.768905573856763 757 44.435681663723869 767 44.361259417988016 792 44.361260790871981 
		815 44.361257410583931 841 68.910819609970503 858 73.721273917880822 880 73.738667434428194;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "CenterNeckFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -8.1962422930615197e-005 57 13.857922870264735 
		62 23.545928773092868 65 -10.026276542272456 68 10.399016719614202 71 -2.3325000253436214 
		76 -19.174240440445733 80 -15.607225552330902 87 -17.498408043670835 91 -23.949641446683046 
		96 -27.615052282769856 100 -21.662527644298706 105 -12.667636481273588 109 -12.971523504810209 
		117 -18.971941645306359 128 -21.054964528676173 139 -20.581041879368371 151 -20.519900829191581 
		164 -20.538167477789386 192 -20.538167477789386 196 -4.29213993823587 202 3.1343742758002739 
		238 2.6270397747568728 248 -1.1419290805872122 259 -26.303364672757446 271 -34.551117543963194 
		331 -34.551117543963194 345 -49.051321563899329 364 -56.002960119741203 379 -55.90775441476719 
		390 62.844743351322812 393 54.485989421516123 398 32.365367193444051 416 61.642574771717605 
		420 -34.919399374846719 428 -53.911310328747398 439 -63.981619699693674 456 -48.871688753166602 
		490 -49.128737391256344 499 -70.201363718612413 508 -69.14479861800244 624 -69.284952570200943 
		644 -31.364760038371205 655 -29.631384032349114 666 -35.838168962817562 677 -39.603926302406101 
		682 -44.992223804594865 686 -57.655798322045058 690 -60.245765615456101 695 -5.9623580953480895 
		704 -5.8070602265983622 723 -5.2923113041899086 735 -8.5780790547012025 741 -8.3650454934960994 
		749 -8.2929732820368507 757 -9.638457882558896 767 -9.9389676788202426 792 -9.9389635723668075 
		815 -9.9390053541445376 841 -2.4637295803021289 858 -1.4259427984505157 880 -0.99581015974761933;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "CenterNeckFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -4.098361061748489e-005 57 -5.5471421393332321 
		62 -17.512561737292739 65 35.088056587056023 68 35.18640844120138 71 23.2149059430097 
		76 13.675109121951287 80 7.3587026653119461 87 23.590125450639828 91 41.069968718105507 
		96 48.983912254257234 100 31.659486097821706 105 8.6107610718140286 109 7.8041085922331055 
		117 5.7378860187828664 128 6.0669264403483671 139 5.3199940353190431 151 5.2235354030607937 
		164 5.3126500287154679 192 5.3126500287154679 196 -2.4018186759528755 202 -8.2273404904760472 
		238 -8.6213388148839325 248 -6.6400656903432562 259 5.9386646775912997 271 10.922490061687274 
		331 10.922490061687274 345 14.554351866120673 364 8.805783144950972 379 8.7321945215335379 
		390 41.350472622251516 393 81.00300872974131 398 54.44316639595786 416 63.079649672496537 
		420 18.652506302930096 428 1.8713173601057238 439 15.272201573068127 456 3.2937269320938931 
		490 5.9588898685738156 499 35.549349904511367 508 33.574532394538565 624 35.350373023104488 
		644 -61.072826279845451 655 -62.95852250844127 666 -40.169461302137009 677 -34.778787615343582 
		682 -33.289781752072095 686 -29.790473177470364 690 -24.848036799496082 695 -77.790839053892668 
		704 -75.642075266788709 723 -67.328448868780228 735 -66.119124850350303 741 -63.85454690968043 
		749 -60.386515118384565 757 -57.231022369806936 767 -56.061590725711895 792 -56.061600751208786 
		815 -56.061587954724111 841 -76.442694098139839 858 -80.739913645370166 880 -79.614253691256948;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 3 3;
createNode animCurveTA -n "LeftHandFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00010175013801851892 57 1.985355668127222 
		62 -2.2930445612775561 65 -0.64484941441814647 68 -0.012660907743691779 71 -0.00059611703211430011 
		76 -0.013848092210263526 80 -0.016335939661228531 87 1.8964469918182858 91 -2.3636962392422611 
		96 -5.2043843074851504 100 2.3755558342193495 105 -2.5038450823216087 109 1.0144048599632394 
		117 1.8471885976619626 128 0.42885937844539479 139 0.035335642150512346 151 -0.063928122010857097 
		164 0.88250584382118158 192 0.88250584382118158 196 0.88228886823891828 202 0.88220028827448149 
		238 0.88220028827448149 248 0.87867126042605581 259 0.860904406163292 271 0.85788762635836269 
		331 0.85788762635836269 345 -0.46624863819428447 364 -1.030798485922555 379 -1.0235504737972505 
		390 8.5547197315498824 393 7.4895837041857227 398 -10.593037382952533 416 -5.4228758570465612 
		420 6.9719115508664204 428 -6.1770431355890114 439 -1.4483978293330868 456 -0.95705509618169127 
		490 -0.6604600178263067 499 -0.6598111559854668 508 -0.65995434896039362 624 -1.2339905384452223 
		644 -3.6995012087267698 655 -3.6987561838631069 666 -3.6952825860941698 677 -3.6944609185440238 
		682 2.8912943481191942 686 14.483881177785477 690 6.1522742018788596 695 -2.5708825921490144 
		704 -4.0522154629856404 723 -2.5706964439632802 735 -3.4731095602118538 741 -0.52877940158006576 
		749 4.8082742601796769 757 8.2118089736511539 767 9.4021386346470219 792 8.6834833359764421 
		815 8.6787449118561319 841 10.029194850577644 858 10.294816050758588 880 10.312372066133813;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHandFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -7.9499799758723974e-005 57 2.9587306245949856 
		62 -3.6807908946887711 65 -1.1680229712789181 68 -1.2316469505811796 71 -0.00030352077091749341 
		76 -0.53221249588157737 80 0.30492855960357274 87 -8.2265779840168385 91 9.2553484030463036 
		96 -4.0968477391633362 100 3.9801446494591795 105 -3.7311774614590179 109 1.8861976928281943 
		117 3.4617791456637743 128 0.7094329337851154 139 0.058988596066919675 151 -0.10572697430327004 
		164 1.4902910108163889 192 1.4902910108163889 196 1.489944217286435 202 1.4897691001045896 
		238 1.4897691001045896 248 1.483734476308042 259 1.453353225116812 271 1.4481945434680141 
		331 1.4481945434680141 345 -0.32589677520539717 364 -1.7312785635523478 379 -1.7196719026477565 
		390 35.077600919466583 393 22.371415776643236 398 -11.299726347305743 416 -38.883991274235797 
		420 29.235129537196222 428 -9.0319734460311292 439 -4.7582637348551051 456 -1.6483419071378682 
		490 -1.1388140807239557 499 -1.1375212272767128 508 -1.1378164462655862 624 -2.104754652960104 
		644 -6.2620973872632186 655 -6.2609787313411474 666 -6.2557631192124363 677 -6.2545293841845551 
		682 2.658311858227187 686 18.364471840551904 690 8.1726630995796761 695 -3.1462912398813572 
		704 -4.8919287036108177 723 -3.1460165306852965 735 -4.3057937242222115 741 -0.51006801429612769 
		749 6.3720843447710838 757 10.763875604564742 767 12.300021117340997 792 11.401044120833964 
		815 11.394915381111131 841 14.137772941768821 858 14.677268036179358 880 14.805568306500492;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHandFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00010383819988170319 57 66.101448315885492 
		62 62.204729961655566 65 56.1721551354279 68 -0.45112053777361016 71 -0.00066026771325302248 
		76 1.267242636197025 80 -7.5674993444525063 87 -27.550369407732081 91 -22.169911270079904 
		96 101.97224859731733 100 58.507099687045717 105 66.089462854266117 109 59.150072129229422 
		117 60.091285481334914 128 60.707950040053525 139 60.57422275648338 151 60.568807297673125 
		164 59.65597594595161 192 59.65597594595161 196 59.65601844234093 202 59.65603761398544 
		238 59.65603761398544 248 59.658155230540238 259 59.668816349219192 271 59.670626587939744 
		331 59.670626587939744 345 59.70583500166434 364 59.909956786096203 379 59.884530886299835 
		390 25.007128393355483 393 35.012924139898914 398 84.685059603052125 416 13.693743102731782 
		420 26.555061793968711 428 67.050098386102434 439 63.800442079661899 456 58.654679302425912 
		490 58.601057106395473 499 58.601318547514197 508 58.601425156473205 624 59.137781063738394 
		644 59.493353667551929 655 59.49219939562871 666 59.486817727750513 677 59.48554471280886 
		682 63.804247772406214 686 74.720363153262483 690 72.278398783839833 695 76.888261441316359 
		704 77.647954465893974 723 76.88819379784546 735 74.215498534772493 741 74.82275901305205 
		749 74.660687928235973 757 73.365820699774858 767 73.076684804992738 792 72.888245440027234 
		815 72.887982397823066 841 69.069275914936156 858 68.31817113863957 880 67.936902779532744;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftElbowFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 -5.1062236976310045 62 -1.8436023289079051 
		65 -0.066979938564737468 68 -0.19900597597943875 71 0.67797534513492108 76 -0.032114948931476997 
		80 2.1153133328299902 87 -8.8033140078927481 91 -24.349928917098886 96 24.38449709582223 
		100 51.128310017885873 105 52.318522880122089 109 49.05321818854388 117 24.57423307932125 
		128 14.485051664938574 139 13.671702828985701 151 13.501980721753684 164 14.517490065208053 
		192 14.517490065208053 196 14.517366248349886 202 14.517302558908241 238 14.517302558908241 
		248 14.513002244728861 259 14.491352357397085 271 14.487676245581481 331 14.487676245581481 
		345 20.901481612847121 364 27.431275339265561 379 27.394042491818482 390 25.976030347632562 
		393 26.75927058409469 398 21.086707493365608 416 -3.8244123167987074 420 53.699977857035897 
		428 23.295619536674959 439 25.326077448781444 456 25.011545088233532 490 25.496901883165464 
		499 25.498193850136115 508 25.498068869018294 624 24.849122273251371 644 13.233180054703988 
		655 13.234172465804386 666 13.238799475119565 677 13.23989397818567 682 12.342991786551067 
		686 2.806529103895921 690 -7.4030896025696604 695 -35.108045082090641 704 -41.206758534118684 
		723 -35.107668388498169 735 -30.304013093632427 741 -23.667519083363821 749 -12.365841559376836 
		757 -4.9342931284619072 767 -2.3195304215006636 792 -3.0011809855069309 815 -3.0062199661132611 
		841 8.3059747831970281 858 10.530980434896339 880 11.487930943823759;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftElbowFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -5.8062646345954363e-008 57 -0.31074631470654202 
		62 -0.14047952509225603 65 -0.04037326891465258 68 -0.020408500303603562 71 -0.3666826879275506 
		76 -0.8413311067083673 80 16.092428537486605 87 46.712718724879494 91 53.431310915153993 
		96 22.853272579766987 100 0.4776571726844947 105 0.89319157686578798 109 2.459709642674309 
		117 2.2034672175311965 128 1.9111461898604676 139 2.044840264103275 151 2.0553192836668717 
		164 2.2197851930938279 192 2.2197851930938279 196 2.2197038397854003 202 2.2196943390641164 
		238 2.2196943390641164 248 2.2190007154347313 259 2.2155086744348305 271 2.2149157321721948 
		331 2.2149157321721948 345 2.2593652529885513 364 2.3142621109087385 379 2.3171784902709454 
		390 0.37124385200217569 393 0.49040943048108487 398 0.31257323126946024 416 0.29743234832662974 
		420 1.2416817827888358 428 0.37820343267434592 439 1.2169548545518925 456 2.3134246638773823 
		490 2.4648141186723218 499 2.4652461565765904 508 2.4652185908532758 624 2.3402707324543242 
		644 2.3777426555327925 655 2.3777375163544092 666 2.3777135554915749 677 2.3777078876322619 
		682 2.7227561929112989 686 3.2098054447782021 690 1.1481656808745011 695 0.65190575510820337 
		704 0.66839868585135853 723 0.65201692905012998 735 0.50168634276099044 741 0.47149747596776947 
		749 0.42227507079889071 757 0.34908312065148916 767 0.33272959013395903 792 0.3305479568301718 
		815 0.33054453871442735 841 0.32771508055692566 858 0.32715855191405807 880 0.32713070379579201;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftElbowFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.021679025505117685 57 54.774825218110315 
		62 44.181216512180818 65 26.206769307621723 68 0.011428677119745885 71 56.820253790959505 
		76 91.470487850581051 80 49.206925051078457 87 4.2715359504230026 91 27.38508795312125 
		96 22.279710178198837 100 19.246261116092224 105 25.23630096022428 109 35.530301437578188 
		117 28.555104720388016 128 24.460479480911751 139 26.728589206888408 151 26.890096837514442 
		164 29.735213900547173 192 29.735213900547173 196 29.734396179804502 202 29.734098398849053 
		238 29.734098398849053 248 29.722333883853466 259 29.663105554586533 271 29.653048691116521 
		331 29.653048691116521 345 31.512105150257039 364 34.098069513118084 379 34.138090041738032 
		390 69.725237375566394 393 74.92954964319047 398 38.092819851234339 416 23.699338998950367 
		420 83.144527613918157 428 22.748364650007762 439 37.007330549783731 456 34.100429037381467 
		490 37.088594301330602 499 37.096566068942977 508 37.096178027504727 624 34.621046623088041 
		644 35.365500961617769 655 35.365467185781696 666 35.365309709602656 677 35.365272459156621 
		682 43.947162626326225 686 57.746924849911913 690 34.154350399835657 695 31.110009143898282 
		704 32.906573870030584 723 31.110494753119145 735 22.900414171316402 741 27.907692497035217 
		749 36.038395276334136 757 40.609940768899975 767 42.166028707051019 792 40.010924555687453 
		815 39.999795606469348 841 36.712082914669281 858 36.065419779660509 880 35.984658023167938;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftShoulderFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 3.513194920375638e-005 57 -52.453281518717127 
		62 -71.164668973650208 65 -59.108420925407138 68 80.816759037016709 71 93.027175955468167 
		76 89.409264747076762 80 76.306835505525299 87 20.34450574451369 91 9.3208343720863471 
		96 -28.823648427068093 100 -65.30210434716318 105 -98.328112354031177 109 -95.893082336616089 
		117 -62.190409312212523 128 -49.820959283678022 139 -52.427708173351562 151 -52.746232292314644 
		164 -52.960859392699959 192 -52.960859392699959 196 -52.96084137594773 202 -52.96084643971048 
		238 -52.96084643971048 248 -52.960172357764577 259 -52.956778699168382 271 -52.956202462060425 
		331 -52.956202462060425 345 -53.191655549100098 364 -53.678724707947914 379 -53.694560175691812 
		390 -13.692672068427033 393 -0.50577153115447215 398 0.98587156736357062 416 10.465880918688422 
		420 -37.662310292843522 428 -52.787953563997256 439 -52.195927888340002 456 -54.724737581023987 
		490 -54.499012335115395 499 -54.498257851940032 508 -54.498233140395378 624 -54.607648084714924 
		644 -55.05586219174711 655 -55.055869129379808 666 -55.055901475341145 677 -55.055909126666542 
		682 -27.181784797046834 686 32.357129404166983 690 -15.675377220108722 695 -36.410301618553369 
		704 -38.702548301893053 723 -36.410120629842076 735 -38.846150507304735 741 -35.999756783537691 
		749 -30.33110852939873 757 -25.478788572796834 767 -23.695542330553849 792 -24.505153586813286 
		815 -24.509218473431144 841 -28.605355539725483 858 -29.411028384351468 880 -28.77155547800556;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftShoulderFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.00014695943882983255 57 16.035091069038309 
		62 -11.407421504173849 65 -37.416507981569524 68 -34.928459459105028 71 -58.738651975881915 
		76 1.4901512155142407 80 7.4833857614150929 87 -6.0042062136924921 91 0.90795266144626452 
		96 -8.1473139507306307 100 4.2208558987002673 105 -7.019488331941437 109 -5.7353496327737501 
		117 11.467950149398 128 18.395508259010381 139 18.124094295132039 151 18.122721490625924 
		164 17.368594113050126 192 17.368594113050126 196 17.369092857592367 202 17.369185509848499 
		238 17.369185509848499 248 17.376229403120977 259 17.411691811067232 271 17.417713263967343 
		331 17.417713263967343 345 3.6543906785028613 364 -10.499145159709629 379 -10.473146947304972 
		390 -20.410748470537573 393 -27.074505184577358 398 -31.626740322258623 416 -24.474163226388274 
		420 -11.866223297126139 428 -11.60579827519561 439 -17.51732462217166 456 -6.8989279081778143 
		490 -9.1476782994051629 499 -9.1539119566564509 508 -9.1538930415885815 624 -7.9985738895284531 
		644 -13.111211679910554 655 -13.111190486618286 666 -13.111091675187513 677 -13.111068301684982 
		682 -18.583947314418481 686 -35.866106095236148 690 -49.618655136591492 695 -35.314817865806333 
		704 -31.393868903935328 723 -35.314973586134883 735 -36.014162514599896 741 -37.617413465238812 
		749 -37.506769894350676 757 -36.330580478442101 767 -36.067874697871602 792 -35.55991198090851 
		815 -35.557380399054537 841 -32.86367636729512 858 -32.333849324224161 880 -33.122330015708478;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftShoulderFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.01065403126830833 57 -33.2941562864197 
		62 -30.833803939315679 65 -27.595760489539554 68 -21.650835306492375 71 -36.108463067758578 
		76 25.3260194471255 80 21.858433070555598 87 -4.8148129218918854 91 -0.17863958294819582 
		96 24.953358561391877 100 0.34389526105942425 105 7.0573689115068658 109 7.1711920489931771 
		117 1.2538984874699539 128 0.41415116496640114 139 -5.0888810497821755 151 -5.7674495625946749 
		164 -6.3942773709992302 192 -6.3942773709992302 196 -6.3940614686636597 202 -6.3940235864279567 
		238 -6.3940235864279567 248 -6.3907499667354104 259 -6.374268962196119 271 -6.3714705173547443 
		331 -6.3714705173547443 345 -5.9758932074485527 364 -7.0466156057140159 379 -7.1231152526849861 
		390 -30.035582624943494 393 -76.632626838125006 398 -62.425476695822859 416 -81.242097202906137 
		420 -19.232615302157384 428 -10.998282578333283 439 -14.468053954781418 456 -11.619909285535069 
		490 -12.77387347881324 499 -12.776929109333372 508 -12.776858183471219 624 -12.05891009130819 
		644 -31.625434043860871 655 -31.625426098126706 666 -31.625389052001378 677 -31.625380288868438 
		682 -35.804323093457505 686 -35.247642031508505 690 33.733903410012026 695 56.262076433341122 
		704 59.754346802793982 723 56.261797815395894 735 59.475804185416088 741 53.234165557157347 
		749 43.292143517197609 757 36.349674138959514 767 33.879760368113331 792 35.260061754989088 
		815 35.267115061660434 841 42.847882887050162 858 44.338950856574016 880 43.31264541729756;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftCollarFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 3.3015800867281271e-006 57 -0.081041778811106663 
		62 -0.19608363608453724 65 -0.27849083061133328 68 5.8265329314003678 71 5.3046356358774931 
		76 5.3047341517963478 80 5.3044627995749902 87 5.3047924587446857 91 5.3045145894664092 
		96 5.3045599285835197 100 -1.2362868668221472 105 5.278086717871509 109 5.3915746084130909 
		117 6.297647850885741 128 6.4305730925148614 139 6.4306164409801294 151 6.4307048517018144 
		164 6.4305115195819544 192 6.4305115195819544 196 6.4305414764033708 202 6.4305208327198322 
		238 6.4305208327198322 248 6.4305082731390675 259 6.430445042059393 271 6.4304343055361244 
		331 6.4304343055361244 345 6.4305970314485315 364 6.4304527073100708 379 6.4304535489768018 
		390 11.598361082587347 393 11.914895380821807 398 11.233466822604646 416 11.453363821223741 
		420 9.7898962264265101 428 7.5176116963264503 439 7.1460472243407676 456 6.4304945287847408 
		490 6.430375697021204 499 6.4305647635585625 508 6.4304815027539473 624 6.430370582995204 
		644 6.4304245047655497 655 6.4304270200388123 666 6.4304387472280879 677 6.430441521254191 
		682 7.0104052292968415 686 8.364015829797566 690 8.2646790603971798 695 8.2241471383831737 
		704 8.2242588938525945 723 8.2241281561544888 735 7.9926597238292327 741 7.8294115186300557 
		749 7.5774607345713054 757 7.3410598993855549 767 7.2882771138412297 792 7.2882784041575626 
		815 7.2883064249497558 841 7.2882559418161916 858 7.288246012243726 880 7.2882479416553654;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftCollarFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -1.5781303066355466e-005 57 -2.7466828167010386 
		62 -4.032042252705712 65 -7.6913216510061844 68 -27.01329302065751 71 -20.860421194916199 
		76 -20.860363523040508 80 -20.860144735158684 87 -20.859929867313593 91 -20.860167297666365 
		96 -20.860040350066473 100 -29.583836556484098 105 -20.931169688124289 109 -21.100741897907369 
		117 -26.448295206197418 128 -28.355679787695998 139 -28.35581789017024 151 -28.355863063206861 
		164 -28.355665302928902 192 -28.355665302928902 196 -28.355679685565637 202 -28.355625539269468 
		238 -28.355625539269468 248 -28.355594487475059 259 -28.355438157536739 271 -28.355411612995209 
		331 -28.355411612995209 345 -28.355409928222539 364 -28.355199103419544 379 -28.355198574044106 
		390 12.952841169761857 393 28.814204883681633 398 10.075043610925359 416 11.217497018191224 
		420 -1.4742838274550343 428 -27.190464875262482 439 -27.58849366227571 456 -28.355117994099814 
		490 -28.354983787366713 499 -28.355188520175226 508 -28.355102159121564 624 -28.35506096862871 
		644 -28.355083450306825 655 -28.355094165142969 666 -28.355144121906477 677 -28.355155939006274 
		682 -20.165780027477229 686 -1.2628471696138468 690 -4.8853087817235989 695 -5.14064513203388 
		704 -5.1407156094827355 723 -5.1406619365344444 735 -6.7704272601563966 741 -7.6764576857903073 
		749 -10.21004407816652 757 -13.022055423226091 767 -14.387253996126576 792 -14.3872801080259 
		815 -14.387296733629135 841 -14.387290975326485 858 -14.38728984272081 880 -14.387301966991245;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftCollarFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 3.8168091644718281e-005 57 1.4797582561668969 
		62 3.0326069919711722 65 4.143203799983687 68 -19.365823460373267 71 -18.083539732786665 
		76 -18.083880261902021 80 -18.083609574391861 87 -18.08401650557369 91 -18.083599011470334 
		96 -18.083512293025866 100 -2.7045374688535313 105 -18.009121522746717 109 -18.29143412344483 
		117 -20.46257791986703 128 -20.781219201575688 139 -20.78107716882576 151 -20.781088425720935 
		164 -20.781026150970821 192 -20.781026150970821 196 -20.781013208824675 202 -20.780985617881061 
		238 -20.780985617881061 248 -20.781001171533735 259 -20.781079476237522 271 -20.78109277223497 
		331 -20.78109277223497 345 -20.78126927606419 364 -20.781283532196866 379 -20.781284513453915 
		390 -23.003205015599288 393 -20.747267174369014 398 -22.759141802602308 416 -20.469145274409339 
		420 -22.164502128745983 428 -23.281965503971559 439 -22.427368411314461 456 -20.781238540571053 
		490 -20.781282043543143 499 -20.781345715225925 508 -20.781377007898971 624 -20.781364906295305 
		644 -20.781273371447028 655 -20.781271854703359 666 -20.781264783050208 677 -20.781263110275091 
		682 -22.428339716825512 686 -26.137269596945423 690 -24.429777403304758 695 -23.965056864991102 
		704 -23.964977639392782 723 -23.965091565213147 735 -23.001455959798527 741 -22.201045354857079 
		749 -20.967697513342124 757 -18.948741192750902 767 -18.49781945113633 792 -18.497845669122057 
		815 -18.497828008044898 841 -18.497883042216127 858 -18.497893866936238 880 -18.497952881181174;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHandFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 2.4883033952317871e-005 57 -3.176467964577355 
		62 -5.3896566510003812 65 -8.0506394710281572 68 -16.641884838655688 71 -22.832737090531971 
		76 -7.8382566195561925 80 -7.3096443381973781 87 -6.6666367029251639 91 -5.585087062781291 
		96 -12.43776589068829 100 -14.304248109014607 105 -13.055760369274354 109 -8.7159253454249228 
		117 -8.7221202950157899 128 -4.4324427360525105 139 -14.897456894878442 151 -3.9366760542063193 
		164 -0.00041956693143055358 192 0.023497140550950518 196 -0.013814301235913765 202 
		0.020591789846157983 238 0.020591789846157983 248 -0.068633616330341832 259 -0.51783800239971856 
		271 -0.59411209685322641 331 -0.59411209685322641 345 -7.3773919041036917 364 -1.0455850738345229 
		379 -1.1026134170790478 390 -13.258062557223466 393 -17.759546607506255 398 -0.11057953455635536 
		416 -3.5767008624149028 420 6.4313690393459444 428 -27.851957612946244 439 -15.083047977770049 
		456 -8.4257677835470535 490 -5.5401741004349896 499 -5.5405343179961131 508 -5.5408943462327285 
		624 -5.380471326122918 644 -10.649812408415606 655 -10.62169852734 666 -10.49062060049047 
		677 -10.459614569799228 682 -8.5278854789225971 686 -6.4804736223258166 690 -5.6829333051675039 
		695 -4.2820937458486652 704 0.59837185269779336 723 -0.089333331359308266 735 -1.991855990030676 
		741 -0.0095447591201402709 749 -1.0006203396023499 757 -0.33283871455170821 767 -0.26292138714607466 
		792 -0.26278224666495092 815 -0.26273967174887219 841 -0.26268459121109083 858 -0.26267375737109977 
		880 -0.23882155893754278;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHandFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -3.3809221905754935e-005 57 -12.575703102973129 
		62 -24.043948274326318 65 -16.785497605825054 68 -22.092252287732688 71 -23.115062513791059 
		76 -7.0603206067137299 80 -6.6734583871507889 87 -8.4541291575651627 91 -7.5418345069056194 
		96 -16.270271294418084 100 -18.10457536161028 105 -16.928858027376062 109 -11.205204315553525 
		117 -9.3864849305474802 128 -4.1951110320404981 139 -13.913521744420288 151 -3.9607484993946311 
		164 -0.011041439666294874 192 0.013597517222193588 196 -0.024879255624172682 202 
		0.010546137539966345 238 0.010546137539966345 248 -0.081070253458996031 259 -0.5423120279281618 
		271 -0.62063004921821063 331 -0.62063004921821063 345 -6.7316449601987225 364 -0.94866529541711009 
		379 -0.99951305999410089 390 -8.5250501622588253 393 -17.007257330185215 398 -0.21590464889132938 
		416 -5.9729521968267747 420 7.3324628604570865 428 -21.023698144456805 439 -12.261545547526314 
		456 -7.2292418453820169 490 -4.9487511630757748 499 -4.9490725350937117 508 -4.9493355283044975 
		624 -4.8112270510150479 644 -9.6783779281534628 655 -9.6537774682005537 666 -9.5390804869655348 
		677 -9.511949312359393 682 -8.9698448060923006 686 -14.613688395503591 690 -38.019596311005365 
		695 8.411656988207481 704 -1.3769816081481885 723 0.21485371744182613 735 3.7280248180207693 
		741 -3.3173004659178722 749 -2.8375706523322961 757 -3.9245617442300085 767 -4.1514279432896402 
		792 -4.1470843034719271 815 -4.1473683789530229 841 -4.1471042687764905 858 -4.1470523207108423 
		880 -3.9503164234963424;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHandFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 10.082389587330319 62 27.037456560253236 
		65 52.62157495866397 68 75.303263624315449 71 90.899085384487023 76 97.625760478091507 
		80 92.849864841821528 87 78.114762782073441 91 75.895364445791941 96 76.264969426113396 
		100 78.082741169702203 105 76.74283376727908 109 77.889064368900506 117 90.621594243887557 
		128 94.801090754617448 139 95.62089138101642 151 91.300060939805874 164 89.89577076262232 
		192 89.886184632264118 196 89.901641390038833 202 89.888301991532629 238 89.888301991532629 
		248 89.922210549981486 259 90.092922837358302 271 90.121909475814107 331 90.121909475814107 
		345 96.729622181302076 364 97.753613428621989 379 97.760343605725751 390 116.31826214645571 
		393 94.232873820921512 398 68.287891580968932 416 52.348788870189829 420 85.501952015842434 
		428 108.02249221411191 439 103.96722843219483 456 100.45931188299609 490 98.191979262815622 
		499 98.192039145556933 508 98.192263644583107 624 98.134513713013263 644 97.176951165449182 
		655 97.171233646317802 666 97.144576332358056 677 97.138270636848162 682 86.289541921966659 
		686 49.333815916478819 690 18.046087675800006 695 -52.395766632862781 704 -44.580224058863777 
		723 -48.4810484638692 735 -54.863051931309819 741 -37.88494420977856 749 28.176687676220862 
		757 12.352178618586027 767 9.1627469971362032 792 9.1661028255708494 815 9.1642842245507499 
		841 9.165681630568697 858 9.1659564876018855 880 8.8535701973653058;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightElbowFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 5.5110225351940141 62 7.8358634281100237 
		65 40.460737713696183 68 40.670929170706302 71 37.949542946313372 76 -14.614162592589576 
		80 -21.171696343338123 87 -22.874185237118326 91 -30.291598523768258 96 -22.661987236775008 
		100 -20.354200861714929 105 -11.011420511674553 109 -9.4177124549990943 117 -10.893634897289031 
		128 -17.475405625412066 139 -7.2706866854682302 151 -17.629004321738197 164 -21.476584856650565 
		192 -21.500508808570391 196 -21.463243205891004 202 -21.497703903506874 238 -21.497703903506874 
		248 -21.409293286574677 259 -20.964190948542377 271 -20.888613374446052 331 -20.888613374446052 
		345 -19.024577917064438 364 -28.243754599459098 379 -28.157043121279582 390 -29.912192617236038 
		393 10.649014431938182 398 -54.639813299767539 416 -41.52678105194088 420 -55.895821198222826 
		428 -1.5683036411688693 439 -14.281965344524796 456 -18.80517696065154 490 -21.535372011679865 
		499 -21.535008143175997 508 -21.534758280821066 624 -21.688423327408714 644 -4.9583376621773487 
		655 -4.9852494534429148 666 -5.1107227666938027 677 -5.1404030454035388 682 -20.504850808734648 
		686 -7.951166110361628 690 -44.673755605512 695 -53.095209336123119 704 -55.34723554803751 
		723 -54.905793048750958 735 -54.406388838983197 741 -49.146987143651572 749 -60.333892292511166 
		757 -47.387688717278103 767 -41.26220511173662 792 -41.256845530611322 815 -41.259976238508607 
		841 -41.285193006241997 858 -41.290152914727287 880 -41.302428324022451;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightElbowFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 -0.29662487834696982 62 -0.23482384157626568 
		65 -0.28316881781214714 68 -0.29514692885220251 71 -0.3385034452902233 76 -0.34717721187489792 
		80 -0.34153881629770289 87 -0.34346707228843837 91 -0.33428164499530316 96 -0.32665514905574627 
		100 -0.33760322588451275 105 -0.33781984935465198 109 -0.34217082983916403 117 -0.33845964628103758 
		128 -0.33514285448602216 139 -0.31085685612795999 151 -0.33555329635623399 164 -0.33788271033554884 
		192 -0.33800783887671754 196 -0.33810194304154684 202 -0.33812274509656942 238 -0.33812274509656942 
		248 -0.33813694411885825 259 -0.33820842894995462 271 -0.33822056694532626 331 -0.33822056694532626 
		345 -0.34002837012656961 364 -0.34113158106213332 379 -0.34113119361741795 390 -0.33007560325735102 
		393 -0.30924958591462476 398 -0.32389855745752205 416 -0.33115995994706116 420 -0.29929876165349101 
		428 -0.33385100063180351 439 -0.33684853943312748 456 -0.34102661203281615 490 -0.34110837735127458 
		499 -0.34099355979918916 508 -0.34099847259582494 624 -0.34086963555999372 644 -0.34106056868236129 
		655 -0.34105846738436285 666 -0.34104867030993596 677 -0.34104635284583151 682 -0.34147257351532695 
		686 -0.33774866677348042 690 -0.3445826495617178 695 -0.041704907945517539 704 0.021283154214546504 
		723 -0.014885012106538581 735 -0.017690167346227234 741 -0.035143945821604593 749 
		-0.054823391404614022 757 -0.066152714535810023 767 -0.068688974020699761 792 -0.067421531215005104 
		815 -0.06701307033244315 841 -0.052733013980281421 858 -0.049924256988886639 880 
		-0.055541490211267232;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightElbowFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 20.95293221047929 62 28.452245194815436 
		65 11.201243173911369 68 17.48486115443939 71 14.066244811569016 76 14.464704571541752 
		80 18.994351058879001 87 16.11312037319933 91 14.099669842966119 96 15.178804286107363 
		100 17.370184486193629 105 17.944094815172054 109 7.9992248525817375 117 15.595503160685157 
		128 10.184673286841013 139 28.981182515782386 151 8.1527048523018895 164 0.048648382465091684 
		192 -0.002726248611761736 196 0.076446315452545724 202 0.0033906933628514379 238 
		0.003390693362851437 248 0.19448383521310816 259 1.1565402846632802 271 1.3198957343663822 
		331 1.3198957343663822 345 15.180963540863242 364 3.2773732957208055 379 3.3484783191652499 
		390 39.616621241490492 393 20.294867361834381 398 19.084476509846318 416 3.8449481299793757 
		420 16.092645010318027 428 40.279021286092927 439 21.504894827022067 456 13.955239300403981 
		490 9.0253335887610451 499 9.0258041042309625 508 9.0265019575064596 624 8.7071549061699631 
		644 10.736639548561396 655 10.686844218896743 666 10.454678885278147 677 10.399760977796413 
		682 13.48745001406385 686 26.330038852295615 690 97.946618092777285 695 52.308791727755448 
		704 72.227794145750522 723 66.576674329027057 735 56.263149823389924 741 64.827628792871351 
		749 94.554628715120117 757 108.26492932307451 767 112.21955917854642 792 113.0243801216066 
		815 113.27074677822212 841 121.10194072538187 858 122.64226523164501 880 120.62208515802195;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightShoulderFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 3.5708068908244104 62 6.735911421614027 
		65 21.423460862706158 68 30.624004360439219 71 29.826966412117095 76 28.009775874591526 
		80 27.04527768670058 87 33.736095699701899 91 31.378111970914571 96 20.825849580165691 
		100 25.18628787580429 105 35.662349087178342 109 36.767460883386271 117 37.805693615816622 
		128 38.687975410806722 139 36.987430128605368 151 39.822222654865634 164 40.392793718999194 
		192 40.397254746060305 196 40.390452762602528 202 40.396687165085041 238 40.396687165085041 
		248 40.380076005592677 259 40.296447294652332 271 40.282247290389009 331 40.282247290389009 
		345 43.504461102213526 364 47.275805092000603 379 47.253795269067666 390 77.265612505156056 
		393 8.7487047001049998 398 35.967925541158429 416 29.704791521031499 420 51.210581088059733 
		428 47.745761275296999 439 48.459649900866729 456 46.59089143139488 490 46.158703423990652 
		499 46.158696516430631 508 46.158807763577862 624 46.142071279107874 644 43.859890721690498 
		655 43.855832214114997 666 43.836909861926422 677 43.832433844897388 682 57.042013358774227 
		686 65.946500958773257 690 99.913354522000006 695 50.446964674072852 704 54.889273931942505 
		723 51.502205212052282 735 52.786553306872108 741 45.316216373180119 749 33.945745672125476 
		757 40.940692953689869 767 44.414089259882175 792 45.260395178092772 815 44.976020255318161 
		841 38.026394280872815 858 36.659466163649583 880 34.321744129870041;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightShoulderFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 9.4019995868629387 62 13.284540010639892 
		65 -10.954103364042556 68 -5.3975228096516545 71 -13.05932960041468 76 10.259577880242995 
		80 15.984417474156718 87 11.171390874403695 91 9.8625181951948857 96 2.4944116462370909 
		100 4.3094808930465032 105 18.078411880398498 109 14.890086564641988 117 17.352521990953019 
		128 10.886795314639985 139 21.697556071393443 151 15.735723738512556 164 13.041476243480147 
		192 13.025221130310902 196 13.04951967152128 202 13.026068791110173 238 13.026068791110173 
		248 13.090992137286971 259 13.41784805322674 271 13.473347598151546 331 13.473347598151546 
		345 5.0206533842775194 364 -12.677021744545835 379 -12.633584611757755 390 -43.21237535486771 
		393 -51.76647644012278 398 4.1686369190935082 416 5.1218233078281514 420 -9.2221294712668982 
		428 -6.1708333469352725 439 -11.909891725312502 456 -8.5435425266929919 490 -9.2543971701072412 
		499 -9.2544781282798034 508 -9.2543175961946407 624 -9.3940805808121386 644 -14.531299930573148 
		655 -14.551030013967825 666 -14.643019391776885 677 -14.664779161252717 682 -24.156520424634873 
		686 -50.732291158852235 690 3.9957373844623207 695 3.9918644659672169 704 1.6526659779870823 
		723 9.1504792388316947 735 16.707594692141313 741 18.934951072119585 749 18.279884074428061 
		757 4.5957995025995295 767 -2.0476458897149548 792 -2.4997366595394017 815 -1.8292335814769896 
		841 11.787312991582422 858 14.465563654083725 880 15.907466239941229;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightShoulderFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 -9.9762976548903737 62 -11.633232057946634 
		65 -7.482135219638276 68 -36.551596441763721 71 -21.162132462426943 76 -52.271983994429768 
		80 -54.491115726055426 87 -32.538419100364997 91 -40.817784172297486 96 -33.544139149110094 
		100 -25.808384463918369 105 -14.761984908896666 109 -11.237859455181608 117 -22.005290844007362 
		128 -23.81862375325521 139 -25.774771516978255 151 -16.691650302588979 164 -13.978927771892984 
		192 -13.959101341173715 196 -13.989281648995872 202 -13.961692816560587 238 -13.961692816560587 
		248 -14.03398477878086 259 -14.397937916104452 271 -14.4597365023021 331 -14.4597365023021 
		345 -24.911553042493626 364 -25.692443916020334 379 -25.64086504616531 390 -67.55508414698366 
		393 -7.6693258191471223 398 -52.427544709062467 416 -8.3657394511777667 420 -67.371365738241565 
		428 -29.767696280531275 439 -24.454750451050852 456 -24.016956461079047 490 -21.972457251014973 
		499 -21.972483538835764 508 -21.972795039080289 624 -21.860974697921172 644 -10.99445890456783 
		655 -10.977323439745781 666 -10.89743119013297 677 -10.878532954533542 682 -5.5969623642188902 
		686 -15.902050362241724 690 -6.4936620742946358 695 52.532665132317845 704 40.365376799288356 
		723 41.27141813994087 735 50.281580306030285 741 48.166873092152962 749 50.70106268708323 
		757 57.603969603689634 767 60.955352145577365 792 60.573789508037066 815 60.202145724746053 
		841 49.42044636830969 858 47.299784327510189 880 47.949115198672686;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightCollarFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -1.0368625970899531e-005 57 -1.3037644576760106 
		62 -3.9048137369159805 65 -2.9092503043076436 68 -8.4188787235917886 71 -1.7773315690696245 
		76 -1.1427156101740501 80 -1.1425749577587825 87 -0.87667400217114833 91 -1.243531219131889 
		96 -0.95313165142500755 100 -0.50512375634104001 105 -1.6493036341883203 109 -1.6919979988532281 
		117 -1.1767289388252065 128 -1.2312156152948623 139 -1.1723131737719605 151 -1.1723209615610073 
		164 -1.1723452681266766 192 -1.1723452681266766 196 -1.1723753415760882 202 -1.1723912098860678 
		238 -1.1723912098860678 248 -1.1724007335582394 259 -1.172448680387447 271 -1.172456821672557 
		331 -1.172456821672557 345 -1.1723311221675066 364 -1.1722484076491611 379 -1.1722489561671723 
		390 -3.1098287775493803 393 -2.7710760411251427 398 1.8127224017635304 416 -3.6455403415346774 
		420 -0.13280871461299354 428 -1.1720195175786832 439 -1.1720587137740499 456 -1.1722718391551312 
		490 -1.1723127171667469 499 -1.1722555131720289 508 -1.1722702007413421 624 -1.1722693807464588 
		644 -1.9979353786326488 655 -1.9979377885546752 666 -1.9979490245552192 677 -1.9979516823923249 
		682 -1.997927572197749 686 -1.9977261849502148 690 -1.9983614846390148 695 -4.3557552031139544 
		704 -4.211404802677194 723 -4.1770363830344337 735 -4.2070324594754602 741 -4.0942571095803002 
		749 -3.9201984039775977 757 -3.8262294590187182 767 -3.805251953444182 792 -3.8052486214732664 
		815 -3.8051830934827904 841 -3.805217951318435 858 -3.8052248075371469 880 -3.8051630515451387;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightCollarFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 9.9329524820493352e-006 57 2.5948459421861254 
		62 -1.232167185163783 65 -19.508699854067171 68 -25.688901366238465 71 -22.218925138143192 
		76 -20.616447344005618 80 -20.616546003390322 87 -16.048426583908132 91 -19.925102750156015 
		96 -18.067112790639992 100 -12.137920498065396 105 -15.362858099234204 109 -14.89330996277036 
		117 -20.420794049157937 128 -18.75333538264951 139 -20.465908491758025 151 -20.465661358313934 
		164 -20.465803232697166 192 -20.465803232697166 196 -20.465637062917143 202 -20.465566465604354 
		238 -20.465566465604354 248 -20.465540516250591 259 -20.465409874497016 271 -20.465387691762917 
		331 -20.465387691762917 345 -20.466006556358082 364 -20.466113111783443 379 -20.46611480872091 
		390 8.5846504309374829 393 6.5385581694691393 398 6.3211622027546737 416 30.20709218333733 
		420 2.9525871289276147 428 -20.457055555881084 439 -20.460281624084658 456 -20.466252195324937 
		490 -20.466322718328062 499 -20.466148415897472 508 -20.466107398210234 624 -20.466143061725589 
		644 -20.287679253846711 655 -20.28766690562583 666 -20.287609333382818 677 -20.287595714867656 
		682 -20.287707954449868 686 -20.287857540798232 690 -20.28812585193219 695 0.67783498266850617 
		704 1.638819876797871 723 1.586069332622309 735 -3.3820735367351413 741 -3.1950428083535485 
		749 -2.9068351326865036 757 -5.3988968247400031 767 -6.6087888083143405 792 -6.608787824241519 
		815 -6.6087961229073198 841 -6.608811037222571 858 -6.6088139707325091 880 -6.6088713918838611;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightCollarFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 1.2366891616911526e-005 57 11.087374127563992 
		62 21.217047714415415 65 11.728445112333819 68 26.052631329829822 71 9.1580735155199857 
		76 7.3985195549989156 80 7.3987112497872296 87 6.5812948978318975 91 7.7012778550628456 
		96 6.8736249407548158 100 5.0827787594379279 105 9.0342508233151158 109 9.1796624286866972 
		117 7.4974441395500335 128 7.6602364522143578 139 7.484606463257645 151 7.4845945091703294 
		164 7.4846510924684866 192 7.4846510924684866 196 7.4846961415937345 202 7.4847472777328159 
		238 7.4847472777328159 248 7.4847751858947271 259 7.4849156892476936 271 7.48493954646358 
		331 7.48493954646358 345 7.4849811994098676 364 7.4849321911162834 379 7.4849342222393531 
		390 26.938957124349084 393 26.849220589709567 398 44.527481932805394 416 27.142612976503383 
		420 26.156467017486737 428 7.4848912116175441 439 7.484920017860599 456 7.4850738777816543 
		490 7.4851567532674599 499 7.4850445665752083 508 7.4850924288763059 624 7.4851167018838378 
		644 9.8563170466358034 655 9.8563162446586308 666 9.8563125055268888 677 9.8563116210481958 
		682 9.8564447661214416 686 9.8566839528760379 690 9.8572416546731798 695 23.519147920772724 
		704 31.297570551803844 723 32.523157811104717 735 24.057178138221357 741 19.022289078209077 
		749 11.502435565401077 757 2.2479703037007308 767 -1.299556862675042 792 -1.2995784624457904 
		815 -1.2996161511091218 841 -1.2995299570239651 858 -1.2995130034326536 880 -1.2994756493948201;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 8.6344589857558195e-005 57 -1.5134328452729404 
		62 -6.6867486701338814 65 -10.99267023187689 68 -15.26882677719772 71 -22.910818738152408 
		76 -15.416970793593098 80 -15.764087132805784 87 -22.204995271106853 91 -11.91253743130228 
		96 -3.1976851063341263 100 -9.1141633627300305 105 -22.872770903146325 109 -23.917094264896754 
		117 -24.874318203333988 128 -25.010123476558633 139 -27.655912522395074 151 -27.997392028681855 
		164 -27.800390398448798 192 -27.800390398448798 196 -27.800408311406894 202 -27.800412904765256 
		238 -27.800412904765256 248 -27.800426500892808 259 -27.800494950456606 271 -27.800506573069068 
		331 -27.800506573069068 345 -25.78273321362116 364 -24.272469905115312 379 -24.316383263137091 
		390 -26.785222722668475 393 -38.214801834955033 398 -38.605208298701982 416 -37.140668024313612 
		420 -21.524966517507188 428 -19.23185583394342 439 -21.68988728373197 456 -26.545266802579384 
		490 -26.545261572894137 499 -26.545266934754974 508 -26.54529562072381 624 -26.545258170699046 
		644 -32.910653074040688 655 -32.91065001790377 666 -32.910635768996251 677 -32.910632398466419 
		682 -32.644544172814996 686 -30.509802300017554 690 -16.227325064375353 695 -15.570580959151583 
		704 -13.175163646426141 723 -15.570582169803819 735 -15.037213444686916 741 -16.202045739479043 
		749 -17.123585697391327 757 -16.651237564987554 767 -16.545740624016371 792 -16.545739541867668 
		815 -16.545729040283451 841 -14.089474966586039 858 -13.606352167067456 880 -13.67692425921722;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 3.7606261416088496e-005 57 -7.906546546699226 
		62 -4.7874088672167421 65 6.0495534349609725 68 5.1300197603475457 71 0.34753688395240839 
		76 -15.318746581368025 80 -16.30207016260492 87 -11.763869583031664 91 -14.676053381977637 
		96 -14.186133873998806 100 -18.877721734930333 105 -20.365923302574938 109 -18.536680741182522 
		117 -17.185241964153757 128 -16.714586869346714 139 -18.936437797401766 151 -19.223186126297687 
		164 -19.05145507195326 192 -19.05145507195326 196 -19.051456770868064 202 -19.051461504217674 
		238 -19.051461504217674 248 -19.051458244191345 259 -19.051441831622455 271 -19.05143904479786 
		331 -19.05143904479786 345 -13.960903249084211 364 -8.6955672379607876 379 -8.7155455723061639 
		390 -27.633598487562654 393 -19.839542271708552 398 -23.420649502188393 416 -29.700616685402547 
		420 -27.124243704348274 428 -7.9420042360998799 439 -6.1578160844655638 456 -9.7296081709220612 
		490 -9.729603348020925 499 -9.7295451103755362 508 -9.7295858786704894 624 -9.729601886607826 
		644 -5.2074257041007623 655 -5.2074239918346148 666 -5.2074160085790773 677 -5.2074141201675639 
		682 -3.3905964886406346 686 2.8664819214159079 690 12.163223428364013 695 17.856965699859142 
		704 19.080209171368029 723 17.856990406191198 735 16.034053325708612 741 13.84368763623063 
		749 9.0370668055956713 757 5.1023561973789056 767 3.6655894042416763 792 3.6656004714304382 
		815 3.6655964801623537 841 0.75164814143474656 858 0.17850104963595526 880 -0.061968526155649073;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 5.1224922569716459e-005 57 0.11286251814665088 
		62 -5.2427918842965884 65 16.143166468974787 68 16.198625262997279 71 20.652261422029461 
		76 22.428738381725836 80 20.765034238217105 87 12.353879161025645 91 10.033883807344949 
		96 7.0823679287225065 100 10.165433500114302 105 18.422636454691833 109 21.692570974567744 
		117 23.928913629355929 128 22.915084019945109 139 23.046265133138515 151 23.063188244333244 
		164 23.069433130333014 192 23.069433130333014 196 23.069457490095648 202 23.069478805688053 
		238 23.069478805688053 248 23.069476883255369 259 23.069467204787877 271 23.069465561401554 
		331 23.069465561401554 345 19.851666165421118 364 16.649035882440206 379 16.669796651710154 
		390 6.0976950715113629 393 -6.9983421028730781 398 -11.687045140167612 416 -1.5222646010932626 
		420 15.162964962724558 428 7.2605150914816079 439 9.7334065381299446 456 17.723508064283394 
		490 17.723480317330257 499 17.723461088809398 508 17.723493638184024 624 17.723510796682156 
		644 16.295501362941994 655 16.295501186820648 666 16.295500365673931 677 16.295500171434512 
		682 13.055828075008584 686 8.9243578675173172 690 23.782810677966381 695 47.508036660688191 
		704 52.278098196562063 723 47.507996351404842 735 43.835917440574946 741 41.565257524505995 
		749 38.570854702973456 757 35.803897677850287 767 34.77637930838749 792 34.776387507118081 
		815 34.776360937282632 841 33.538322573079611 858 33.294811705523145 880 32.25507391362359;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "MoxMotion:_spine_angularValues_6_";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00019440362048415237 57 -0.43197278435218495 
		62 -4.588708831325472 65 -11.386638868533144 68 -14.867800658371225 71 -19.449794925266538 
		76 -7.4783324366112067 80 -7.3030962873607619 87 -10.367070241285832 91 -2.5129170908328202 
		96 3.6864522401692668 100 0.22158831920093694 105 -10.400661558735774 109 -13.318055047808228 
		117 -15.434012202598314 128 -15.488743516693749 139 -16.962462873994141 151 -17.15261924562623 
		164 -17.051836325808424 192 -17.051836325808424 196 -17.051814252063622 202 -17.05179721643896 
		238 -17.05179721643896 248 -17.051796137167237 259 -17.051790703584913 271 -17.051789780972435 
		331 -17.051789780972435 345 -14.870195449456794 364 -13.166527670856086 379 -13.208516372922331 
		390 -10.567912986972191 393 -13.592673538310679 398 -8.8447824840568341 416 -16.931958309196375 
		420 -4.8397372698580146 428 -6.3695569814236546 439 -9.3325347698939591 456 -15.339742578608583 
		490 -15.339776820032927 499 -15.339733893632161 508 -15.339716050918396 624 -15.339765371553183 
		644 -21.721529332061742 655 -21.721529018410191 666 -21.721527556043792 677 -21.721527210126073 
		682 -21.629613912425633 686 -20.818426283320054 690 -11.998950069877079 695 -7.6359269039317308 
		704 -6.1634746380526444 723 -7.6358784764937635 735 -6.6953095474521165 741 -6.1206431212217742 
		749 -4.9033388178031183 757 -3.0566617843769555 767 -2.6442111446268548 792 -2.6442038284619684 
		815 -2.6442502096365978 841 1.04621556480524 858 1.7720965620393643 880 1.8709230207813081;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "MoxMotion:_spine_angularValues_5_";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.9231875504910204e-005 57 -8.4279727500656758 
		62 -7.2209759333946293 65 5.1072270717368404 68 3.422495903066392 71 -2.7753872422783785 
		76 -15.862547353041501 80 -16.853127621072179 87 -15.201616214271173 91 -16.714791635712835 
		96 -15.157247432718336 100 -20.108900486023334 105 -23.451944962759825 109 -21.640868053570191 
		117 -20.159743152260766 128 -20.178758842340557 139 -23.29986343428585 151 -23.702676315531729 
		164 -23.459952461094819 192 -23.459952461094819 196 -23.459962895465008 202 -23.459963017461238 
		238 -23.459963017461238 248 -23.459958174592423 259 -23.459933793219374 271 -23.459929653306212 
		331 -23.459929653306212 345 -19.76519490612225 364 -16.115484457205348 379 -16.142416297230291 
		390 -38.403948687535966 393 -24.387881981900275 398 -26.012364763839717 416 -30.735920235921743 
		420 -29.046991962199332 428 -16.244214625553408 439 -14.567575463376675 456 -17.509395636711179 
		490 -17.509373919127484 499 -17.509407320246698 508 -17.509380753938164 624 -17.509414228814581 
		644 -16.226081835394449 655 -16.226082893298354 666 -16.22608782566077 677 -16.226088992394054 
		682 -15.323932859049851 686 -9.9226277336036759 690 6.3919590002745679 695 13.686409319737905 
		704 16.718696603318119 723 13.686443045366156 735 10.586960592386935 741 7.0113097732466727 
		749 2.8433067888167405 757 0.62438690548961318 767 -0.1210609996619203 792 -0.12106376045542744 
		815 -0.12103893277147866 841 -1.1423842710712877 858 -1.3432735945328005 880 -1.5490929977189638;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "MoxMotion:_spine_angularValues_4_";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00012294303438566476 57 -0.022397102823354404 
		62 -5.1440147486397425 65 15.755965962272784 68 16.55992923265536 71 22.71406774708414 
		76 23.078136868615598 80 20.998220769542716 87 9.596551120501978 91 12.557597062625762 
		96 15.535586696309064 100 15.07774328329649 105 16.859575638395022 109 19.821912562188814 
		117 21.55607564432048 128 20.234733994033494 139 20.377297562847271 151 20.395722424243118 
		164 20.401543737808058 192 20.401543737808058 196 20.401531249199827 202 20.401516823834939 
		238 20.401516823834939 248 20.401504030893324 259 20.401439624960869 271 20.401428688949718 
		331 20.401428688949718 345 15.350190389500348 364 10.181735930119682 379 10.203956341605853 
		390 0.040965425480360813 393 -18.392691250627912 398 -32.173847476090451 416 -18.530828271550117 
		420 5.8055808040527301 428 0.26699190372559811 439 2.855840556128673 456 11.331811073575494 
		490 11.331809820261912 499 11.331818102222945 508 11.33179466093673 624 11.331834485427351 
		644 8.0609783221619882 655 8.0609782844932578 666 8.0609781088668875 677 8.0609780673230773 
		682 4.0759792752711084 686 -2.8363424570317806 690 6.3705478349240359 695 29.136172578715222 
		704 32.928289380862218 723 29.136237600850823 735 25.444478368079288 741 23.645583062218982 
		749 21.032156663740583 757 18.432382861307591 767 17.170208211657709 792 17.170196057136113 
		815 17.170166597969626 841 15.858363890274562 858 15.600344248355478 880 14.553036427490548;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 9.3943019146784003e-005 57 -2.4452832541797154 
		62 -0.38579728056450263 65 4.9839206768619722 68 -3.3309169061424084 71 -8.0664291686369882 
		76 -14.899392887590508 80 -13.962492091635417 87 -14.513505201832789 91 -6.4324799079078199 
		96 5.0564273352081104 100 4.0229431028255442 105 -1.5202828070128318 109 -1.1701405064472845 
		117 -0.40302394790723423 128 -1.5935909526768441 139 -5.6597993040640979 151 -6.1523267018930081 
		164 -5.6864263552048868 192 -5.6864263552048868 196 -5.6862883853795374 202 -5.6862318971021759 
		238 -5.6862318971021759 248 -5.6866502134809602 259 -5.6887562229704756 271 -5.689113819582853 
		331 -5.689113819582853 345 -5.5105976408713548 364 -5.6422491232264802 379 -5.6143130190753556 
		390 -2.3881377225099287 393 -14.406194824680568 398 -14.73522723240108 416 -15.297277945245609 
		420 -3.0194909918865007 428 -5.855554078683574 439 -5.1552332110655232 456 -4.1995827012227123 
		490 -4.1994592963512982 499 -4.1995200141874625 508 -4.1994850050251475 624 -4.1967349445003403 
		644 -9.6388762480890531 655 -9.6382637797248645 666 -9.6354082122838971 677 -9.6347327376723921 
		682 -8.5868820148589311 686 -6.4092818048339844 690 -5.0741913563875656 695 1.1730721867549547 
		704 0.83082603756752971 723 1.1732232805179297 735 -0.41361702450964299 741 -1.1979854080999808 
		749 -2.1723550175148238 757 -3.5685994410678297 767 -3.8804402237195026 792 -3.8803206955782552 
		815 -3.8803790647389866 841 -1.9719901350172473 858 -1.596627418199615 880 -1.5599015551988415;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00011909042529376036 57 6.432623348820993 
		62 -22.49907900838145 65 -42.964423684677385 68 -62.804726024605216 71 -44.663733241916312 
		76 -18.592205000756721 80 -16.970378999108405 87 -19.235768163607393 91 -18.471564116276099 
		96 -20.328236319208038 100 -19.48787014667111 105 -23.156523530858856 109 -28.331283222339671 
		117 -33.095830005803826 128 -34.732231697098335 139 -27.572995040570223 151 -26.653042767563363 
		164 -27.293609833433898 192 -27.293609833433898 196 -27.293651327347717 202 -27.293702553584428 
		238 -27.293702553584428 248 -27.295732946216191 259 -27.305954936955331 271 -27.307690612543816 
		331 -27.307690612543816 345 -27.534533939419415 364 -27.756976739697546 379 -27.759092613292314 
		390 22.721925170327154 393 5.2548077358414247 398 2.4239088858081712 416 0.89327471543239378 
		420 4.6795758036822876 428 -15.343893517304604 439 -25.887823399615193 456 -27.87318130510381 
		490 -27.873152366492953 499 -27.87315046487582 508 -27.873148425143267 624 -27.868688802786799 
		644 -31.322734164814843 655 -31.321707523510661 666 -31.31692091957617 677 -31.315788664954304 
		682 -30.67827429668024 686 -28.509490850572224 690 -31.537757123848532 695 -26.01613296852257 
		704 -27.05452702558604 723 -26.016127213956931 735 -19.289849779440644 741 -14.431694667570202 
		749 -7.7288486908030301 757 -1.716714979007991 767 0.50713321748769624 792 0.50724487916493011 
		815 0.50737189072177669 841 0.41400448897777831 858 0.39563997164328468 880 0.55350179899313889;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "CenterSpineFK_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 6.3687716953285723e-005 57 12.988666817376004 
		62 24.986822515526899 65 28.340677069723089 68 45.203723460111043 71 40.125130317125766 
		76 50.628016144705136 80 47.537358285673932 87 41.87425469996672 91 22.581765394421595 
		96 2.4512144237205407 100 7.2468253321795633 105 17.448394963662334 109 18.025107039238453 
		117 18.03404299379708 128 20.69512771638626 139 22.398816001191083 151 22.561096170317395 
		164 22.42412999114795 192 22.42412999114795 196 22.424054914163559 202 22.424007513620676 
		238 22.424007513620676 248 22.425989282633044 259 22.435966478262397 271 22.437660588082814 
		331 22.437660588082814 345 24.099941031106034 364 25.932524140201608 379 25.863749199821314 
		390 22.2005040770824 393 50.524736550573579 398 29.266388510843896 416 20.107266352906557 
		420 -3.2652182800713825 428 29.064206056709978 439 29.975579938315907 456 20.790419484813629 
		490 20.790440273986317 499 20.790441871705625 508 20.79041003951831 624 20.782877197483 
		644 26.72222390414877 655 26.720694213821933 666 26.713562198280425 677 26.711875144646871 
		682 23.941755500272517 686 19.647086094978189 690 35.075258376230295 695 13.953749374462006 
		704 17.453983354451658 723 13.953654688097213 735 14.510280039873344 741 14.95253486472275 
		749 15.77872555134851 757 17.136679400166468 767 17.440042891192196 792 17.441575252892857 
		815 17.443201967973916 841 16.814900579804526 858 16.691319420654782 880 17.147524529862071;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightToeFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 -3.6158720393840251e-028 62 0 65 
		0 68 0 71 0 76 0 80 0 87 0 91 0 96 0 100 0 105 0 109 0 117 0 128 0 139 0 151 0 164 
		0 192 0 196 0 202 0 238 0 248 0 259 0 271 0 331 0 345 0 364 0 379 0 390 -9.3679210803550253e-006 
		393 -1.3282698736191949e-005 398 -2.009954623352295e-005 416 -0.00010784115644508926 
		420 -0.00016104497942915618 428 -0.00032078047418704282 439 -0.00027180258341474563 
		456 -0.00017778091886246631 490 -0.0001563631225899035 499 -0.00013476813235396292 
		508 -0.00010595706670132052 624 0 644 0 655 0 666 0 677 0 682 0 686 0 690 0 695 0 
		704 0 723 0 735 0 741 0 749 -2.1710174079166499e-006 757 -2.2290710795588154e-006 
		767 -2.2836260948926008e-006 792 -2.2974268835395562e-006 815 -2.5209063842755662e-006 
		841 -3.7595044364037274e-006 858 -4.0031253894762463e-006 880 -5.3757671204878685e-006;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightToeFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -1.3660371709060207e-005 57 -0.00019682077967673355 
		62 -0.00023786433897465554 65 -0.00028841549270222134 68 -0.00025206690608896445 
		71 -0.00021687535338337521 76 -0.00011483932700437009 80 -0.00013112347517875219 
		87 5.0919568917233627e-005 91 0.00012235502026861406 96 0.00035545199069911059 100 
		0.00026292537246855362 105 -4.1638625913675949e-006 109 1.2139608661402783e-005 117 
		7.6363669854068549e-005 128 0.00016624288485476835 139 2.7621078012379788e-005 151 
		8.0205976432330114e-005 164 6.030499623394542e-005 192 7.6604107997779258e-005 196 
		7.5125133541254345e-005 202 7.540268089992342e-005 238 7.5402680874372136e-005 248 
		8.0956296229952449e-005 259 0.00010891591539194364 271 0.00011366340829045791 331 
		0.00011366340829045791 345 0.00015063146611059665 364 0.00018940321920509235 379 
		0.00019024685567688138 390 0.00034603939702180727 393 0.00042650233936022692 398 
		0.0004300371879340845 416 0.00044902717302406107 420 0.00026714841281037902 428 2.8137733188146563e-005 
		439 -0.00015997819308558966 456 -0.00051648345009274658 490 -0.00039416097205640369 
		499 -0.00037503035218735875 508 -0.00019017361930089968 624 0.00025262502279520515 
		644 0.0002636900869213569 655 0.00026303071578602868 666 0.00025995646925241008 677 
		0.00025922926685712633 682 0.00028488200469017308 686 0.00041166181990509609 690 
		0.00047076528246165373 695 0.00059377296670637414 704 0.0005942865448446674 723 0.00058922634514025447 
		735 0.000583135975380703 741 0.00067166141707859306 749 0.00061367378540553728 757 
		0.00061327731497179112 767 0.00061272915051808867 792 0.00059059938394327835 815 
		0.00059222893648192378 841 0.00072548627872224636 858 0.00075169678395008697 880 
		0.00078730175836082869;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightToeFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0 57 1.4672973350502302e-006 62 0 65 
		0 68 0 71 0 76 0 80 0 87 0 91 0 96 0 100 0 105 0 109 0 117 0 128 0 139 0 151 0 164 
		0 192 0 196 0 202 0 238 0 248 0 259 0 271 0 331 0 345 0 364 0 379 0 390 0 393 1.8749421904129527e-006 
		398 0 416 -7.042818982098915e-006 420 -2.7173342671511938e-006 428 7.9786243797626233e-006 
		439 6.859593084322442e-006 456 3.775331729241846e-006 490 3.2312278271781263e-006 
		499 2.7404581466729811e-006 508 2.3773114692241356e-006 624 0 644 0 655 0 666 0 677 
		0 682 0 686 0 690 0 695 0 704 0 723 0 735 0 741 0 749 -1.283484099808405e-006 757 
		-1.6719974989646639e-006 767 -1.7710852746381375e-006 792 -1.811733368157433e-006 
		815 -1.7953854873996386e-006 841 -1.7352497228366857e-006 858 -1.7234215657913885e-006 
		880 -1.4883270712205509e-006;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightFootFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 2.4406752973207941e-005 57 -16.200573357493479 
		62 -35.275717698749283 65 -58.359514363837128 68 -71.566328011018896 71 -55.736531116541265 
		76 -48.991897032198615 80 -56.276637004495541 87 -64.551768972934042 91 -66.72098040448104 
		96 -67.266376381756601 100 -68.559887441577928 105 -70.687719516106 109 -70.227537998838855 
		117 -60.188974313206714 128 -46.529166219711769 139 -52.535481240082731 151 -53.098193088985731 
		164 -53.060727188864654 192 -53.061012860400893 196 -53.060955563547274 202 -53.060570819827326 
		238 -53.060564172730324 248 -53.059931796397287 259 -53.056748104278405 271 -53.056207519099544 
		331 -53.056207519099544 345 -55.886782429874998 364 -58.239014439558574 379 -58.257013646673101 
		390 -63.644887160165787 393 -40.605104934449393 398 -19.646499425543574 416 -16.464674882272881 
		420 -33.888171320750978 428 -28.357251440070261 439 -21.278719566922266 456 -27.616862540207055 
		490 -27.897627545346811 499 -26.319521150604409 508 -26.832275832803585 624 -26.87541910556682 
		644 -24.46949636977271 655 -27.842706886416181 666 -48.826845295361302 677 -57.245567072487034 
		682 -62.529302995514279 686 -41.438193413440935 690 -39.724510966425932 695 -37.987743065682153 
		704 -37.767730259099665 723 -37.987643243320626 735 -36.56802116174795 741 -35.749848498570394 
		749 -34.635739598133995 757 -33.559949742804108 767 -33.319767271118145 792 -33.324720005189548 
		815 -33.324376677783192 841 -33.324087043252 858 -33.324030074778321 880 -33.324244010303573;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightFootFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.3907992015508704e-005 57 7.2904260006022126 
		62 14.151539819153385 65 13.428252293691695 68 -0.44781820217019813 71 -17.79759767244844 
		76 -15.069646332775848 80 -8.7563324041413431 87 1.9293329400223371 91 3.7384593979261016 
		96 3.0416329825518678 100 0.56993057238994127 105 -3.4436224854640511 109 -6.7388753580042957 
		117 -17.20773599683206 128 -20.436832399737 139 -19.505057584243957 151 -19.362071962946253 
		164 -19.564688396739168 192 -19.564690904465198 196 -19.564721306819056 202 -19.5647531455073 
		238 -19.564745850998285 248 -19.564666655665949 259 -19.564267947583037 271 -19.564200247669774 
		331 -19.564200247669774 345 -19.660432441544906 364 -19.597152120820077 379 -19.609037026483193 
		390 0.7148235214583456 393 -1.062349546585698 398 4.1172863279027441 416 4.0586839527045786 
		420 -3.1653149196823813 428 -13.260924019102674 439 -10.149052148241235 456 -14.458233850579411 
		490 -14.738659299659661 499 -13.970580141048716 508 -14.481133670102999 624 -16.576148238776248 
		644 -15.492988430754707 655 -16.238642782881623 666 -19.715175473629003 677 -20.53753726938848 
		682 -21.110273290663631 686 -26.606163522699479 690 -24.782797229252097 695 -23.152773683897923 
		704 -22.966924473101638 723 -23.152716914900289 735 -22.174257336503608 741 -21.57303657993512 
		749 -20.725795065212257 757 -19.681858058474322 767 -19.448716237004703 792 -19.449190197646438 
		815 -19.449097792514163 841 -19.449203978060776 858 -19.44922486379043 880 -19.449209369113873;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightFootFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0036219949749241357 57 20.847121531130103 
		62 24.915547194509806 65 14.603169515582309 68 -9.8270143590870145 71 -42.195351103371536 
		76 -41.581186618684121 80 -26.979166388714173 87 -6.1514494677007985 91 -3.563236677575043 
		96 -4.6345271987847481 100 -7.8981634089114534 105 -14.059787866949527 109 -19.852901007613976 
		117 -40.235027508093921 128 -54.698982763798597 139 -47.708169598890358 151 -46.907277082765688 
		164 -47.253641959048274 192 -47.25346403814617 196 -47.253479603168287 202 -47.25375429931502 
		238 -47.253745080517085 248 -47.254048124939409 259 -47.255573798954416 271 -47.255832855650063 
		331 -47.255832855650063 345 -45.390924806997148 364 -43.6040182822247 379 -43.61191322825303 
		390 -7.9978324725070591 393 -12.976588142489581 398 12.344548931298485 416 16.062981915719323 
		420 -8.5257205388207087 428 -58.511916590018636 439 -70.071653514523149 456 -63.69782045161827 
		490 -68.566834607165163 499 -70.678942468849542 508 -70.888806187911925 624 -71.848478806270478 
		644 -73.302409272538327 655 -69.249294381108641 666 -49.179488089838038 677 -45.882015412984032 
		682 -43.590326928193505 686 -73.1664760115072 690 -71.757593925097623 695 -70.652505439610678 
		704 -70.54988138248541 723 -70.652583904735621 735 -70.291676544862469 741 -70.009176497054 
		749 -69.544555496524254 757 -68.871752352135857 767 -68.72138414828261 792 -68.714848166043694 
		815 -68.715023712410499 841 -68.715337252273187 858 -68.715398922707791 880 -68.714867979046474;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightKneeFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.9567686050621486e-005 57 -7.3473284545557567 
		62 2.6895658188774196 65 5.3717000663666896 68 -6.6075624121903562 71 -29.262226123787485 
		76 -22.865080462873379 80 -15.591052275707773 87 -10.657384534727539 91 -10.768519475276323 
		96 -12.627882132518673 100 -14.756171060913323 105 -19.492383801877541 109 -21.708706970854578 
		117 -36.029724456204328 128 -48.621811000672331 139 -40.870207851109214 151 -40.042125262740612 
		164 -40.495745224188802 192 -40.495517212142246 196 -40.49558642220854 202 -40.495901120734956 
		238 -40.495901593758312 248 -40.496364964464156 259 -40.498697799498032 271 -40.499093910678681 
		331 -40.499093910678681 345 -38.873217631201776 364 -36.661955146889845 379 -36.700568930889027 
		390 -9.8219961316963165 393 10.137081751898593 398 12.801687337861175 416 -20.207081325428717 
		420 -23.866404771319822 428 -46.597430071193706 439 -49.047654526914698 456 -41.519142345215357 
		490 -50.198619333915182 499 -52.19821024385481 508 -54.442216726872751 624 -61.841138097931662 
		644 -63.624822995806682 655 -61.313822112938951 666 -47.562554306638503 677 -40.201753783580266 
		682 -33.849029774009402 686 -46.396319985044641 690 -40.526765290473485 695 -37.107598477602394 
		704 -36.541491732116796 723 -37.107599901849831 735 -35.236311419215994 741 -34.009524575537974 
		749 -32.207386391158479 757 -29.868805818469006 767 -29.346416002847253 792 -29.342516377476752 
		815 -29.342836011521051 841 -29.343061264363701 858 -29.34310556954577 880 -29.343026405564924;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightKneeFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.0512123760305282e-005 57 -0.00033399978833708211 
		62 -0.00022084142951829839 65 -0.00013203299326933747 68 -9.2339787763376244e-005 
		71 0.00028837024994319383 76 6.5518553292413098e-005 80 0.00033271264568454265 87 
		0.00085080554951093637 91 0.0010223919976493179 96 0.00061953170670852079 100 0.0010164281561708378 
		105 0.0012416860205338215 109 0.001328324242012307 117 0.00040653311333977338 128 
		0.00012909371379808958 139 0.00017554595739390568 151 0.00014317847580124448 164 
		0.00012446832822670065 192 0.00019285516623718664 196 0.00014325229385129452 202 
		0.00010953520675613232 238 0.00012275680024896103 248 0.00012870881684479122 259 
		0.00015867418293699783 271 0.00016376224804617932 331 0.00016376224804617932 345 
		0.00026953911420018914 364 0.00034043334377949365 379 0.00034301213880775095 390 
		0.00073172351639248356 393 0.000908884611558738 398 0.00091606208038258865 416 0.00082998488552378329 
		420 0.00040283274158054778 428 0.00049461355756621355 439 0.00021782950962004999 
		456 -5.6308033216313147e-005 490 -0.00010451227978420758 499 -9.0606524652950783e-005 
		508 -2.1078018605926059e-005 624 0.000186465409546317 644 3.1755943825267246e-005 
		655 9.3318713933151031e-005 666 0.00038034846465147612 677 0.00044824436042870629 
		682 0.00063881162014622688 686 0.0010050381839882805 690 0.0010808261896378631 695 
		0.00099954372589363457 704 0.0009719161475956568 723 0.00097180474076742401 735 0.00096637584134826352 
		741 0.0010448470430871176 749 0.0010131497025543 757 0.0010198309898059651 767 0.0010284636954996716 
		792 0.00101703550327752 815 0.00097153183593506616 841 0.00099315376079296409 858 
		0.00099740659643410929 880 0.00099512254927082108;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightKneeFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.0073321049323861447 57 -53.51961079719478 
		62 -70.333324776878428 65 -66.165912387833558 68 -19.692948856504369 71 -4.943346755845786 
		76 -19.931508196343596 80 -48.449845876116974 87 -90.625045389866173 91 -98.662440432810328 
		96 -100.8221041656308 100 -97.713394974677158 105 -88.015265048878419 109 -76.79648428935279 
		117 -42.097232048501461 128 -18.562820139837306 139 -29.225293243161975 151 -30.422509008596965 
		164 -30.1666317088368 192 -30.167048382496738 196 -30.166934639795382 202 -30.166297416570256 
		238 -30.166300503038165 248 -30.165342396802462 259 -30.160518820852069 271 -30.15969978635674 
		331 -30.15969978635674 345 -34.283154883262782 364 -37.982784492744422 379 -37.987695306388979 
		390 -92.14259400683261 393 -86.087928631170058 398 -93.761956344583567 416 -100.63033980255689 
		420 -114.27053343272752 428 -36.169589105562579 439 -13.461215421225306 456 -32.571037888825686 
		490 -25.713971729678661 499 -21.054090104744681 508 -21.786778641751308 624 -24.308540249486978 
		644 -19.796697061186627 655 -22.196432212574909 666 -30.416830821488993 677 -34.924342673806464 
		682 -39.331934287663259 686 -40.94361763579775 690 -40.943219584083621 695 -40.276827092594068 
		704 -40.276603270487392 723 -40.276825265846277 735 -39.649766182823257 741 -39.380264909315699 
		749 -39.139095195394646 757 -39.075716338750837 767 -39.061787844710054 792 -39.072198500650167 
		815 -39.071569717987124 841 -39.071087066876188 858 -39.070992133799678 880 -39.071482968869844;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHipFK_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -1.6913817054693995e-005 57 24.755671188639404 
		62 39.518064941090167 65 52.265405693732795 68 40.803236088803764 71 50.362477955580118 
		76 49.515127604625292 80 51.384655960042458 87 52.36213478088311 91 54.974637619816043 
		96 58.506418614378802 100 58.784554274684204 105 58.629112010414325 109 59.76046588563571 
		117 58.395029615797363 128 55.075071377857185 139 58.622500236527294 151 58.977797203160208 
		164 58.967200137475857 192 58.96727729169212 196 58.967312850499411 202 58.96717446384789 
		238 58.96717446384789 248 58.966738258285048 259 58.964542185883097 271 58.964169296750654 
		331 58.964169296750654 345 60.593055268815839 364 61.52094625503419 379 61.556793465612806 
		390 55.658344622531864 393 44.915421673204541 398 25.241696224119384 416 21.821431585186108 
		420 19.165464742176411 428 66.839875961217217 439 57.122743824662095 456 47.908283377657561 
		490 55.98174185635424 499 56.601038577102358 508 58.946971762939555 624 65.157828002274456 
		644 64.780852515961342 655 64.502010418118999 666 63.201939324937179 677 62.894411999895929 
		682 64.095153120376168 686 64.93338094569296 690 57.859698385590036 695 59.775407720766594 
		704 59.064530703604483 723 59.775394594314278 735 60.574926100312389 741 60.999774939611115 
		749 61.559824593011676 757 62.041720688863556 767 62.149346425977143 792 62.149025064950322 
		815 62.148971035633487 841 62.148967684008198 858 62.148967024774038 880 62.14891838098994;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHipFK_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -2.4141283651165224e-005 57 13.932268140471878 
		62 19.402432023272564 65 23.582900148286289 68 30.246494902904239 71 31.64287188846324 
		76 16.41633616987901 80 4.5986735980035807 87 -11.977294604004186 91 -8.7715719041938769 
		96 -1.588451944785916 100 0.047524139523074431 105 2.4014593483962003 109 8.1174094884186108 
		117 25.543544476410158 128 35.715156439514615 139 29.693911132912358 151 28.949120721671381 
		164 29.297912925836336 192 29.297753244060885 196 29.297814042583667 202 29.298082882454956 
		238 29.298082882454956 248 29.298392954122289 259 29.299954006729742 271 29.300219070646566 
		331 29.300219070646566 345 27.822650001255194 364 26.657522284651876 379 26.653754442609262 
		390 1.9090175077414995 393 19.633824690374972 398 -22.621803339242188 416 -26.130238474962386 
		420 -30.034423649768311 428 23.850909112541764 439 32.390564297559223 456 14.081293349754313 
		490 15.351718441080784 499 17.404345013488953 508 16.67397265470834 624 14.480022503554705 
		644 16.667551564229605 655 18.147009552830237 666 25.629314956630363 677 27.847635133108337 
		682 21.144925537655936 686 -10.661834520161575 690 -9.1359869095015416 695 -7.9879147108195276 
		704 -7.8244637620530497 723 -7.9879284974372382 735 -6.6763395985944305 741 -6.1326811635525855 
		749 -5.6806316940285102 757 -5.6353671633525453 767 -5.6253808729263435 792 -5.6298786962730176 
		815 -5.6295568665024609 841 -5.6293130651278833 858 -5.6292651116185644 880 -5.6294044937695524;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightHipFK_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0037120071598020989 57 24.486236568517945 
		62 31.391392175096549 65 37.963316124143219 68 21.278918472668462 71 37.578500666295646 
		76 41.63471316037699 80 53.193635571072761 87 70.313079392119079 91 74.551606458168166 
		96 76.135503347203596 100 74.261157259817764 105 68.536887970894796 109 66.684695370099007 
		117 60.173352690571036 128 53.081763788060108 139 59.00462977926577 151 59.639671757348744 
		164 59.47531208741615 192 59.475486347503008 196 59.475489612420922 202 59.475218262557576 
		238 59.475218262557576 248 59.474573272999457 259 59.471326079729181 271 59.470774712169373 
		331 59.470774712169373 345 61.351285697848169 364 63.387566664556516 379 63.433039003625979 
		390 71.996166188258513 393 88.844405066389939 398 121.45496631007464 416 103.29481653541202 
		420 131.05042572375524 428 74.382752517399609 439 67.955672351301914 456 78.9618084112536 
		490 74.493416291202948 499 72.937728909984642 508 72.50569159316602 624 71.271488522300174 
		644 70.032182168749031 655 69.188435889619171 666 65.289116006499128 677 64.718549838830569 
		682 71.540497745017205 686 91.219527668896973 690 80.44085926238202 695 87.059410793565533 
		704 84.27140784256801 723 87.059465477411052 735 87.434560209877901 741 87.53097645221294 
		749 87.65598355766835 757 87.8968533204511 767 87.950726069543123 792 87.952854734800056 
		815 87.952521747835007 841 87.952439958566444 858 87.952423871362427 880 87.952298424388587;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "LeftUpLegEff_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.79392331838607788 57 -0.45024657249450684 
		62 -2.2064716815948486 65 -3.6263628005981445 68 -5.3668837547302246 71 -7.1851744651794434 
		76 -8.138671875 80 -7.7660727500915527 87 -6.2727417945861816 91 -5.7556533813476563 
		96 -5.4634218215942383 100 -5.5511798858642578 105 -5.9292678833007812 109 -6.4190850257873535 
		117 -7.6555442810058594 128 -8.1554117202758789 139 -8.0058708190917969 151 -7.986912727355957 
		164 -7.9925460815429687 192 -7.9925460815429687 196 -7.9925475769042968 202 -7.9925470352172852 
		238 -7.9925470352172852 248 -7.9925496653415147 259 -7.9925629066747916 271 -7.9925651550292969 
		331 -7.9925651550292969 345 -7.9309072494506836 364 -7.8685612678527832 379 -7.8685119315318044 
		390 -5.7507305145263672 393 -6.1091127395629883 398 -6.5724163055419922 416 -5.3616514205932617 
		420 -6.4205284118652344 428 -8.2559843063354492 439 -8.2727375030517578 456 -7.9559478759765625 
		490 -7.8660087585449219 499 -7.8660087585449219 508 -7.8660087585449219 624 -7.8660068511962891 
		644 -7.9404058456420898 655 -7.9404055637094819 666 -7.9404042492292213 677 -7.940403938293457 
		682 -8.0153029994517571 686 -8.1913290023803711 690 -8.1913375854492187 695 -8.16497802734375 
		704 -8.16497802734375 723 -8.16497802734375 735 -8.1464471817016602 741 -8.1384592056274414 
		749 -8.1311731338500977 757 -8.1291515570189663 767 -8.1287002563476563 792 -8.1287021636962891 
		815 -8.1287021636962891 841 -8.1287013667700947 858 -8.1287012100219727 880 -8.1287012100219727;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "LeftUpLegEff_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 7.9384646415710449 57 6.3989982604980469 
		62 5.1218843460083008 65 3.8864727020263672 68 3.7838904857635498 71 3.3294720649719238 
		76 3.5399477481842041 80 3.4626414775848389 87 3.1329472064971924 91 2.9226536750793457 
		96 2.7679166793823242 100 2.7696473598480225 105 2.9229147434234619 109 2.9403660297393799 
		117 3.0220391750335693 128 3.0941915512084961 139 3.0108168125152588 151 3.0009334087371826 
		164 2.9877426624298096 192 2.9877426624298096 196 2.9877430362701416 202 2.9877440929412842 
		238 2.9877440929412842 248 2.9877450965413193 259 2.9877501491553327 271 2.9877510070800781 
		331 2.9877510070800781 345 2.8652968406677246 364 2.7412762641906738 379 2.740583874300409 
		390 2.8405730724334717 393 2.568608283996582 398 4.0402474403381348 416 4.1318635940551758 
		420 2.7457280158996582 428 2.8319883346557617 439 2.7920389175415039 456 2.7354810237884521 
		490 2.7054374217987061 499 2.7054364681243896 508 2.7054364681243896 624 2.7054429054260254 
		644 2.7430427074432373 655 2.7430435884826365 666 2.7430476962334525 677 2.7430486679077148 
		682 2.2590724692985109 686 1.1216239929199219 690 1.1216390132904053 695 1.0320219993591309 
		704 1.0320223569869995 723 1.0320219993591309 735 0.98176753520965576 741 0.95050287246704102 
		749 0.90547668933868408 757 0.86301064139252748 767 0.84239363670349121 792 0.84239423274993896 
		815 0.84239625930786133 841 0.84240592203796505 858 0.84240782260894775 880 0.84240663051605225;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "LeftUpLegEff_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0087678851559758186 57 -0.45248354878300745 
		62 -0.88644778728485107 65 -1.7109724283218384 68 -2.4664068222045898 71 -2.6689474582672119 
		76 -2.1512517929077148 80 -1.9538445472717285 87 -1.8392840623855591 91 -1.7771978378295898 
		96 -1.7127617597579956 100 -1.7475098371505737 105 -1.7717208862304687 109 -1.7247784284667969 
		117 -1.4307293891906738 128 -1.3309242872314453 139 -1.3783242702484131 151 -1.384272575378418 
		164 -1.3796312808990479 192 -1.3796312808990479 196 -1.3796307201385498 202 -1.3796311616897583 
		238 -1.3796311616897583 248 -1.3796298293241944 259 -1.3796231215435213 271 -1.3796219825744629 
		331 -1.3796219825744629 345 -1.379683747680664 364 -1.379683747680664 379 -1.3796097846582889 
		390 -1.4615166334228515 393 -1.4408753065185547 398 -1.5375301984863281 416 -1.4542458204345703 
		420 -1.4524948743896484 428 -1.2460968641357422 439 -1.2719109205322265 456 -1.3758576063232422 
		490 -1.3758576063232422 499 -1.3758576063232422 508 -1.3758576063232422 624 -1.3758556989746094 
		644 -1.3758576063232422 655 -1.3758573243906345 666 -1.3758560099103734 677 -1.3758556989746094 
		682 -1.4319963653293752 686 -1.56393934765625 690 -1.56393934765625 695 -1.5775311140136719 
		704 -1.5775311140136719 723 -1.5775311140136719 735 -1.5770561842041015 741 -1.5768330244140625 
		749 -1.576491609008789 757 -1.5759287656757566 767 -1.5758030561523437 792 -1.5758030561523437 
		815 -1.5758030561523437 841 -1.5758030561523437 858 -1.5758030561523437 880 -1.5758030561523437;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "LeftHandEff_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 6.450223445892334 57 5.535405158996582 
		62 3.8086085319519043 65 1.037896990776062 68 -4.1278085708618164 71 -9.2229642868041992 
		76 -9.3097858428955078 80 -7.5030622482299805 87 -3.3307592868804932 91 -2.3986809253692627 
		96 -2.5723979473114014 100 -3.474193811416626 105 -4.5885782241821289 109 -4.6948680877685547 
		117 -5.5220451354980469 128 -5.9417972564697266 139 -5.9415626525878906 151 -5.9423675537109375 
		164 -5.9124364852905273 192 -5.9124364852905273 196 -5.9124275131225588 202 -5.9124245643615723 
		238 -5.9124245643615723 248 -5.9124224187339109 259 -5.912411616593606 271 -5.912409782409668 
		331 -5.912409782409668 345 -5.9134311676025391 364 -5.9124088287353516 379 -5.9124087089646373 
		390 -3.003074629965556 393 -2.6335358619689941 398 -5.4717836380004883 416 -4.7461585998535156 
		420 -3.497793436050415 428 -6.1579904556274414 439 -6.3460397720336914 456 -5.912933349609375 
		490 -5.9126505851745605 499 -5.9129276275634766 508 -5.9129295349121094 624 -5.9129352569580078 
		644 -5.9130301475524902 655 -5.9129371802750796 666 -5.912503730408976 677 -5.9124011993408203 
		682 -5.9124105195888674 686 -5.9124040603637695 690 -5.9121208190917969 695 -5.9116711616516113 
		704 -5.9116640090942383 723 -5.9116640090942383 735 -5.9116911888122559 741 -5.9117059707641602 
		749 -5.9117116928100586 757 -5.9117260276395589 767 -5.9117293357849121 792 -5.9117298126220703 
		815 -5.9117193222045898 841 -5.9118882705577427 858 -5.911921501159668 880 -5.911928653717041;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "LeftHandEff_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 12.664785385131836 57 11.268715143954854 
		62 5.67694091796875 65 2.7947890758514404 68 2.2460708618164062 71 4.3874096870422363 
		76 3.5423243045806885 80 1.6717948913574219 87 1.9164313077926636 91 3.0328021049499512 
		96 1.8100441694259644 100 0.79646086692810059 105 0.74675679206848145 109 0.79059016704559326 
		117 0.7617952823638916 128 0.73192191123962402 139 0.73310518264770508 151 0.7339174747467041 
		164 0.75595808029174805 192 0.75595808029174805 196 0.75595303344726561 202 0.75597739219665527 
		238 0.75597739219665527 248 0.75597621556213135 259 0.75597029180777064 271 0.75596928596496582 
		331 0.75596928596496582 345 0.74239110946655273 364 0.75596928596496582 379 0.75596916158768601 
		390 3.8358155039683117 393 3.9628767967224121 398 2.4503312110900879 416 3.9891557693481445 
		420 3.2498254776000977 428 0.86264944076538086 439 0.78968977928161621 456 0.75610661506652832 
		490 0.75602579116821289 499 0.75609993934631348 508 0.75609707832336426 624 0.75614643096923828 
		644 0.75606584548950195 655 0.75605114975232213 666 0.75598263246871145 677 0.7559664249420166 
		682 0.75600081370356609 686 0.75607728958129883 690 0.75576210021972656 695 0.75537109375 
		704 0.75537967681884766 723 0.7553703784942627 735 0.75544166564941406 741 0.75548315048217773 
		749 0.75554156303405762 757 0.75560968957372487 767 0.75562453269958496 792 0.75562310218811035 
		815 0.75562262535095215 841 0.75562083226701537 858 0.75562047958374023 880 0.75562000274658203;
	setAttr -s 62 ".kit[0:61]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 9 3 10 10 10 3 3 10 1 9 10 10 10 10 10 
		10 9 9 10 9 9 10 10 10 10 9 9 9 9 3 10 3 
		9 9 3;
	setAttr -s 62 ".kot[0:61]"  3 10 10 10 10 10 10 10 
		10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 
		10 10 9 3 10 10 10 3 3 10 1 9 10 10 10 10 10 
		10 9 9 2 9 9 10 10 10 10 9 9 9 9 3 10 3 
		9 9 3;
	setAttr -s 62 ".kix[35:61]"  0.96529132127761841 0.99354749917984009 
		1 1 1 1 1 1 1 1 1 1 0.99999964237213135 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 62 ".kiy[35:61]"  -0.26117563247680664 -0.11341644823551178 
		0 0 0 0 0 0 -0.00011347226245561615 -0.00011553378863027319 0 0.00036954972892999649 
		-0.00089517614105716348 0 0 0 0 0.00018795319192577153 0.00021406558516900986 0.0002372610179008916 
		0.00013828268856741488 0 0 0 0 0 0;
	setAttr -s 62 ".kox[35:61]"  0.96529144048690796 0.99354749917984009 
		1 1 1 1 1 1 1 1 1 1 0.99999964237213135 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 62 ".koy[35:61]"  -0.2611752450466156 -0.11341644823551178 
		0 0 0 0 0 0 -0.00011347226245561615 -0.00011553378863027319 0.00020633336680475622 
		0.00036954972892999649 -0.00089517614105716348 0 0 0 0 0.00018795319192577153 0.00021406558516900986 
		0.0002372610179008916 0.00013828268856741488 0 0 0 0 0 0;
createNode animCurveTL -n "LeftHandEff_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.03242332860827446 57 -0.058977498673144169 
		62 -1.4321424961090088 65 -2.1173520088195801 68 -5.6714320182800293 71 -4.0287075042724609 
		76 -3.0933992862701416 80 -3.0761079788208008 87 -4.1050586700439453 91 -4.5681695938110352 
		96 -4.2584867477416992 100 -3.7573986053466797 105 -3.3617599010467529 109 -3.3856709150390625 
		117 -3.0894131660461426 128 -2.9554970411376953 139 -2.9526715278625488 151 -2.9544203281402588 
		164 -2.9597072601318359 192 -2.9597072601318359 196 -2.9597179145812986 202 -2.9597160816192627 
		238 -2.9597160816192627 248 -2.9597159777985693 259 -2.959715455114361 271 -2.9597153663635254 
		331 -2.9597153663635254 345 -3.0078938154296875 364 -2.9597332624511719 379 -2.9597333730087541 
		390 -2.9189446119384765 393 -3.1627991346435547 398 -2.8898003248291015 416 -3.8213703779296875 
		420 -3.3568241743164062 428 -2.9088966993408203 439 -2.8815167097167969 456 -2.9597485212402344 
		490 -2.9597542432861328 499 -2.9597485212402344 508 -2.9597485212402344 624 -2.9597370771484375 
		644 -2.9596798566894531 655 -2.9596880327350785 666 -2.9597261526626508 677 -2.9597351697998047 
		682 -2.959766873652085 686 -2.9597637800292969 690 -2.9590122846679687 695 -2.9585278181152344 
		704 -2.9585335401611328 723 -2.9585392622070312 735 -2.9585220960693359 741 -2.958501115234375 
		749 -2.9584877637939453 757 -2.9584702652172505 767 -2.9584667829589844 792 -2.9584667829589844 
		815 -2.9584686903076172 841 -2.9583029296592405 858 -2.9582703260498047 880 -2.958266511352539;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "SpineEff_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 5.1669044296431821e-006 57 -0.91131359338760376 
		62 -2.8469982147216797 65 -4.5034298896789551 68 -6.6585750579833984 71 -8.3328361511230469 
		76 -9.1552248001098633 80 -8.6903543472290039 87 -7.0388689041137695 91 -6.5057587623596191 
		96 -6.2075629234313965 100 -6.3567781448364258 105 -6.8293190002441406 109 -7.3288168907165527 
		117 -8.568140983581543 128 -9.0674324035644531 139 -8.8536405563354492 151 -8.8263444900512695 
		164 -8.8384895324707031 192 -8.8384895324707031 196 -8.8384895324707031 202 -8.8384895324707031 
		238 -8.8384895324707031 248 -8.8384881481947932 259 -8.8384811790720157 271 -8.8384799957275391 
		331 -8.8384799957275391 345 -8.776885986328125 364 -8.7145166397094727 379 -8.7137032491522461 
		390 -6.5492215156555176 393 -6.9083957672119141 398 -6.203831672668457 416 -5.1881375312805176 
		420 -6.5438933372497559 428 -8.8206882476806641 439 -9.0093269348144531 456 -8.7623510360717773 
		490 -8.6724119186401367 499 -8.6724119186401367 508 -8.6724119186401367 624 -8.6724491119384766 
		644 -8.7468099594116211 655 -8.746810805209444 666 -8.7468147486502268 677 -8.7468156814575195 
		682 -8.7500223409436995 686 -8.783360481262207 690 -9.0552377700805664 695 -8.8460636138916016 
		704 -8.9067697525024414 723 -8.8460636138916016 735 -8.7946786880493164 741 -8.7666463851928711 
		749 -8.7276878356933594 757 -8.6912006015667114 767 -8.673487663269043 792 -8.6734838485717773 
		815 -8.6734895706176758 841 -8.6734871798390927 858 -8.6734867095947266 880 -8.6734905242919922;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "SpineEff_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 9.2940235137939453 57 7.8963403701782227 
		62 6.5184307098388672 65 5.1181297302246094 68 4.6248183250427246 71 4.375178337097168 
		76 4.6229519844055176 80 4.5843729972839355 87 4.3017096519470215 91 4.1423754692077637 
		96 4.0589485168457031 100 4.0343928337097168 105 4.1169672012329102 109 4.1165266036987305 
		117 4.1494317054748535 128 4.2015047073364258 139 4.1662559509277344 151 4.1621565818786621 
		164 4.1445250511169434 192 4.1445250511169434 196 4.1445235557556153 202 4.1445531845092773 
		238 4.1445531845092773 248 4.1447554964335884 259 4.1457740337274966 271 4.1459469795227051 
		331 4.1459469795227051 345 4.0215311050415039 364 3.896446704864502 379 3.8956806329523825 
		390 4.0895552635192871 393 3.8664083480834961 398 5.1029272079467773 416 5.3989510536193848 
		420 3.9450092315673828 428 4.2784218788146973 439 4.1338357925415039 456 3.887855052947998 
		490 3.8578109741210937 499 3.8578100204467773 508 3.8578100204467773 624 3.8569684028625488 
		644 3.895416259765625 655 3.8952776898889079 666 3.8946316228405689 677 3.8944787979125977 
		682 3.3744927249620105 686 2.1481776237487793 690 2.1099157333374023 695 2.1810002326965332 
		704 2.1704835891723633 723 2.1810002326965332 735 2.1979300975799561 741 2.2048599720001221 
		749 2.2107701301574707 757 2.2113386471320164 767 2.2114708423614502 792 2.2115931510925293 
		815 2.2117810249328613 841 2.2117328108981171 858 2.2117233276367187 880 2.2118039131164551;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "SpineEff_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.054283104836940765 57 -0.58469714131230432 
		62 -1.2263386249542236 65 -2.1467695236206055 68 -2.7834501266479492 71 -2.415961742401123 
		76 -1.6317696571350098 80 -1.3479341268539429 87 -1.113415002822876 91 -1.125074028968811 
		96 -1.2076492309570312 100 -1.2704480886459351 105 -1.2815195322036743 109 -1.2137539533691406 
		117 -0.82094508409500122 128 -0.68734861889648435 139 -0.72859311103820801 151 -0.73378229141235352 
		164 -0.72971808910369873 192 -0.72971808910369873 196 -0.72971874332427977 202 -0.7297133207321167 
		238 -0.7297133207321167 248 -0.72967568573080155 259 -0.72948621270529268 271 -0.72945404052734375 
		331 -0.72945404052734375 345 -0.73005987683105467 364 -0.7299893049316406 379 -0.7292062592498314 
		390 -0.93518568554687498 393 -1.0551235822753906 398 -0.43896414318847654 416 -0.53971029797363279 
		420 -0.44328524151611326 428 -0.99925734082031248 439 -0.91260458508300779 456 -0.67136217633056638 
		490 -0.67136217633056638 499 -0.67136217633056638 508 -0.67136217633056638 624 -0.67126394787597654 
		644 -0.67136217633056638 655 -0.67135780637514597 666 -0.67133743193109874 677 -0.67133261242675779 
		682 -0.62457480852672975 686 -0.53065229931640623 690 -0.69850279370117185 695 -0.74809576550292967 
		704 -0.78655554333496092 723 -0.74809576550292967 735 -0.82026220837402342 741 -0.86693312207031248 
		749 -0.93426062145996092 757 -1.0019379554771743 767 -1.0273335126953125 792 -1.0273335126953125 
		815 -1.0273335126953125 841 -1.0273335126953125 858 -1.0273335126953125 880 -1.0273335126953125;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "RightUpLegEff_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.79391539096832275 57 -1.9952819347381592 
		62 -3.7845535278320312 65 -5.208643913269043 68 -6.8056597709655762 71 -8.5148458480834961 
		76 -9.0660333633422852 80 -8.6420917510986328 87 -7.200070858001709 91 -6.8667616844177246 
		96 -6.7644820213317871 100 -6.8760242462158203 105 -7.2418971061706543 109 -7.7270612716674805 
		117 -8.9447698593139648 128 -9.4374532699584961 139 -9.239985466003418 151 -9.2141599655151367 
		164 -9.2251644134521484 192 -9.2251644134521484 196 -9.2251651611328125 202 -9.2251653671264648 
		238 -9.2251653671264648 248 -9.2251634291401903 259 -9.2251536723683021 271 -9.2251520156860352 
		331 -9.2251520156860352 345 -9.1636753082275391 364 -9.1013326644897461 379 -9.101382083728911 
		390 -6.8915042877197266 393 -7.2556962966918945 398 -7.3774080276489258 416 -6.3734331130981445 
		420 -7.4244208335876465 428 -9.6796989440917969 439 -9.6848697662353516 456 -9.1938285827636719 
		490 -9.1038894653320312 499 -9.1038894653320312 508 -9.1038894653320312 624 -9.1038923263549805 
		644 -9.1782865524291992 655 -9.1782869753281116 666 -9.1782889470485021 677 -9.1782894134521484 
		682 -9.1033906499134538 686 -8.9273662567138672 690 -8.9273748397827148 695 -8.9537353515625 
		704 -8.9537343978881836 723 -8.9537353515625 735 -8.9722671508789062 741 -8.980255126953125 
		749 -8.9875402450561523 757 -8.9895616477743694 767 -8.9900131225585937 792 -8.9900131225585937 
		815 -8.9900140762329102 841 -8.9900140762329102 858 -8.9900140762329102 880 -8.9900140762329102;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "RightUpLegEff_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 7.9384675025939941 57 6.7594180107116699 
		62 5.2868633270263672 65 3.7654850482940674 68 3.1306571960449219 71 2.8937978744506836 
		76 3.2327384948730469 80 3.16680908203125 87 2.8257350921630859 91 2.6801931858062744 
		96 2.6415433883666992 100 2.5984916687011719 105 2.6409263610839844 109 2.6328768730163574 
		117 2.6396961212158203 128 2.6865012645721436 139 2.6683387756347656 151 2.6666934490203857 
		164 2.6470761299133301 192 2.6470761299133301 196 2.6470768775939941 202 2.6470775604248047 
		238 2.6470775604248047 248 2.6470785986317376 259 2.6470838254738207 271 2.6470847129821777 
		331 2.6470847129821777 345 2.524580717086792 364 2.400550365447998 379 2.3998095006645808 
		390 2.6610219478607178 393 2.5078186988830566 398 4.0918536186218262 416 4.4042234420776367 
		420 2.6608376502990723 428 3.0327169895172119 439 2.7620987892150879 456 2.3922567367553711 
		490 2.3622121810913086 499 2.3622112274169922 508 2.3622112274169922 624 2.3622074127197266 
		644 2.3998174667358398 655 2.3998168676290486 666 2.3998140743584937 677 2.3998134136199951 
		682 1.8647065879294447 686 0.60708731412887573 690 0.60710287094116211 695 0.69671720266342163 
		704 0.69671708345413208 723 0.69671720266342163 735 0.74697166681289673 741 0.77823805809020996 
		749 0.82326197624206543 757 0.86572918928289666 767 0.88634681701660156 792 0.88634753227233887 
		815 0.88634991645812988 841 0.88635848341471668 858 0.88636016845703125 880 0.88635897636413574;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "RightUpLegEff_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.0087676569819450378 57 -0.51750983204716761 
		62 -0.94217491149902344 65 -1.7600604295730591 68 -2.311894416809082 71 -1.9187030792236328 
		76 -0.89973849058151245 80 -0.66325497627258301 87 -0.58779323101043701 91 -0.66935372352600098 
		96 -0.81168580055236816 100 -0.8895186185836792 105 -0.92428982257843018 109 -0.8786556867675781 
		117 -0.58670532703399658 128 -0.48745943585205076 139 -0.44005921483039856 151 -0.43411079049110413 
		164 -0.43875199556350708 192 -0.43875199556350708 196 -0.4387523694038391 202 -0.4387516975402832 
		238 -0.4387516975402832 248 -0.43875289147825597 259 -0.43875890234665144 271 -0.43875992298126221 
		331 -0.43875992298126221 345 -0.43869997540283201 364 -0.43870283642578123 379 -0.4387767994481564 
		390 -0.37172247448730467 393 -0.34409834423828123 398 -0.16983248272705076 416 -0.26118589916992185 
		420 -0.22519327679443357 428 -0.57228781262207029 439 -0.54647280255126951 456 -0.4425280241088867 
		490 -0.4425280241088867 499 -0.4425280241088867 508 -0.4425280241088867 624 -0.44252993145751951 
		644 -0.4425280241088867 655 -0.4425281650751906 666 -0.44252882231532115 677 -0.4425289777832031 
		682 -0.38638800016696834 686 -0.25444437542724607 690 -0.25444532910156248 695 -0.2408535627441406 
		704 -0.2408535627441406 723 -0.2408535627441406 735 -0.24132849255371092 741 -0.24155165234374998 
		749 -0.24189402142333982 757 -0.24245608519496917 767 -0.24258162060546873 792 -0.24258257427978513 
		815 -0.24258352795410154 841 -0.24258273102790742 858 -0.24258257427978513 880 -0.24258257427978513;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftUpLegEff_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.0029998800288309939 57 -36.651960993730675 
		62 -47.161351772430876 65 -52.088615745252632 68 -27.145018117914482 71 -0.37288565079603225 
		76 8.1586353920409866 80 -3.470646955492132 87 -20.541922476002565 91 -22.282985401914811 
		96 -22.034447363463446 100 -21.14318060082611 105 -17.709389556625986 109 -11.781526503958341 
		117 13.075644285357381 128 14.921780027025896 139 5.4498006911772858 151 4.8977215351551697 
		164 4.9889427142934384 192 4.9889427142934384 196 4.9889205873511315 202 4.9891859864350252 
		238 4.9894987458770901 248 4.9913222039513281 259 5.0005023847973655 271 5.0020611629452771 
		331 5.0020611629452771 345 2.5977261680957797 364 0.59341717592481535 379 0.58163258590942601 
		390 1.3592917045297395 393 7.4846565633966611 398 8.4397818859483138 416 7.0775632550930787 
		420 -8.4041418909910863 428 15.023831980612547 439 14.543840380220859 456 1.8853525380126963 
		490 -0.02896251763056398 499 -0.028995430399897063 508 -0.028823522168335027 624 
		-0.024631773894856598 644 1.6125659467074542 655 1.6145746068918407 666 1.6239397675399414 
		677 1.6261550639324205 682 4.7226633131372244 686 13.050579364148433 690 24.198849952488029 
		695 23.81430843415799 704 27.794438844948882 723 23.814205095138234 735 28.524159713878905 
		741 33.592380754333739 749 43.187360224350662 757 52.465341394483907 767 55.930294641812388 
		792 55.925837198043439 815 55.926472511381327 841 55.925820928356181 858 55.925692767911137 
		880 55.925765919469278;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftUpLegEff_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.00011165912192474977 57 -4.7804409083304522 
		62 12.126649277327827 65 23.130728645032548 68 23.055667279887579 71 32.823027746429915 
		76 50.064887177788549 80 49.348188964623816 87 43.131479506421073 91 38.896507277914132 
		96 35.256209381102693 100 34.360452305092466 105 30.799457870660287 109 29.437672607539124 
		117 27.481250897803356 128 26.829788571734262 139 29.743543530483066 151 30.073064183451486 
		164 29.83462741016924 192 29.83462741016924 196 29.834591488399539 202 29.834571538777361 
		238 29.834594637264878 248 29.834642977905279 259 29.834886348360214 271 29.834927672224456 
		331 29.834927672224456 345 29.507926940445117 364 29.33596229798961 379 29.285379649797278 
		390 61.436359156054564 393 64.146610346029078 398 64.503590861592599 416 64.258076208875792 
		420 50.891360049364437 428 32.133033977502691 439 31.709828002063951 456 26.748690629786239 
		490 26.718108078462468 499 26.718072844798947 508 26.718109422098969 624 26.71809779331636 
		644 26.707679178232215 655 26.707666299186208 666 26.707606252028494 677 26.707592048080816 
		682 37.244600637097534 686 62.674348317406711 690 69.684498354438574 695 69.911600766620538 
		704 71.409832118324601 723 69.911544743318629 735 71.721067056182193 741 73.151670601836699 
		749 74.992565667702038 757 76.091946390466219 767 76.337497631383059 792 76.337396535818385 
		815 76.337418812409894 841 76.337554181253694 858 76.337580807072058 880 76.337687434240948;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftUpLegEff_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 6.9996046669165316e-005 57 13.170260070577113 
		62 33.413052166912621 65 48.249639841322718 68 57.228280836612996 71 66.290352507300128 
		76 75.990024875696477 80 77.296285080940862 87 75.492896501048563 91 76.282829464937706 
		96 77.402949356237144 100 77.370941565778352 105 75.498982298498831 109 76.437415114828156 
		117 78.499891232467945 128 78.033453348321743 139 79.108652585061094 151 79.247685559773615 
		164 79.315750263380167 192 79.315750263380167 196 79.315684681961955 202 79.31563106620159 
		238 79.315632745148122 248 79.315463163780791 259 79.314609408138054 271 79.31446444196996 
		331 79.31446444196996 345 80.179829224650206 364 81.137022018755772 379 81.126266180803569 
		390 104.47267709356206 393 113.93213250621066 398 89.706765476358953 416 90.354174593080003 
		420 90.806610901180449 428 82.550649089698069 439 82.613616967083487 456 80.456052935409758 
		490 80.579930401550854 499 80.579953332088763 508 80.579904316445138 624 80.580099796156404 
		644 80.351985701860244 655 80.35203663136673 666 80.352274084676992 677 80.352330253437074 
		682 90.131066817817185 686 114.26731555253876 690 126.42302540901007 695 127.57638270643506 
		704 131.79429937150496 723 127.57635995217531 735 133.43793265039446 741 139.21617822088567 
		749 149.7619679885178 757 159.79480959003871 767 163.5343266758469 792 163.53445166657011 
		815 163.53442298033778 841 163.53408269404329 858 163.5340157628292 880 163.53396214417404;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHandEff_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00029735265486465471 57 -40.446685427845807 
		62 -47.000605999101367 65 -10.222611556602299 68 75.230990233521055 71 32.004874023782627 
		76 61.465523597771451 80 50.113071561866732 87 1.2983570823639812 91 -32.691478189800002 
		96 28.536699720843007 100 -0.047144659035065636 105 4.3911624538421226 109 3.912938021073463 
		117 -0.59788523604178589 128 -2.1918356267331429 139 -2.1918323384326994 151 -2.1918378510203942 
		164 -2.1917930775754373 192 -2.1917930775754373 196 -2.1918190888914766 202 -2.1918240391385306 
		238 -2.1918240391385306 248 -2.1918235168191642 259 -2.1918208872077072 271 -2.1918204407044248 
		331 -2.1918204407044248 345 -2.1918236533643443 364 -2.191808520175818 379 -2.191809290545855 
		390 12.075133177500229 393 17.787169778430219 398 11.01777194768929 416 -29.627145905286326 
		420 26.053543516929487 428 -2.1915593409600427 439 -2.1916981443841026 456 -2.1918185511541362 
		490 -2.1918626344159939 499 -2.1918361149456103 508 -2.1918564578875279 624 -2.1918765911107143 
		644 -2.1918662474327411 655 -2.1918660221035742 666 -2.191864971530729 677 -2.1918647230213519 
		682 -2.1918442344577276 686 -2.1917388271225211 690 -2.1916861728954946 695 -2.1917197379716571 
		704 -2.1916659766641708 723 -2.1917250403366633 735 -2.1916628582064703 741 -2.191640476028045 
		749 -2.1917406323657138 757 -2.1917341504809627 767 -2.1917315529731756 792 -2.1917224070472838 
		815 -2.1917395997510427 841 -2.1901426224227967 858 -2.1898285115309917 880 -2.1898705926278321;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHandEff_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.011141214002158379 57 27.379114754598827 
		62 56.559161730823412 65 23.865641352605618 68 44.768672871036038 71 0.31047762854454597 
		76 -13.024111383046812 80 -4.4925245645126015 87 18.59043045782095 91 21.011972599499213 
		96 22.377037238734282 100 47.439337506942671 105 50.959655655363797 109 49.42964750493298 
		117 38.335773384715687 128 34.553729491022771 139 34.553743405671597 151 34.553688451863366 
		164 34.553751869206081 192 34.553751869206081 196 34.553738596756645 202 34.553732112545539 
		238 34.553732112545539 248 34.553732113398418 259 34.553732117692256 271 34.55373211842133 
		331 34.55373211842133 345 34.553704813119168 364 34.553675376427684 379 34.55367430986518 
		390 31.682909298725242 393 28.93137705504153 398 31.895468062453226 416 16.522731623214295 
		420 24.5437524596909 428 34.553493413360833 439 34.553534445055099 456 34.553618234918737 
		490 34.553582310539973 499 34.55362019588987 508 34.553596306084579 624 34.55363319593711 
		644 34.553576603654399 655 34.553578996324532 666 34.553590151889985 677 34.553592790700456 
		682 34.55356998488142 686 34.553490510346798 690 34.553341077319708 695 34.553326311136146 
		704 34.553364604399185 723 34.553293281991522 735 34.553348405963966 741 34.553365507712378 
		749 34.553345178399638 757 34.553363495315452 767 34.553366964479835 792 34.553359250720526 
		815 34.553347915687809 841 34.552927075653649 858 34.552844300252836 880 34.552755052509902;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "LeftHandEff_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -3.4347499040486596e-005 57 73.016742830306995 
		62 26.610498750864163 65 6.2469343070837544 68 -99.105553664721668 71 -182.54464704004855 
		76 -175.65021136496676 80 -121.08630857456467 87 -73.26204257630458 91 -45.635479834481401 
		96 70.063082822805001 100 0.026062418753991404 105 7.9143030647921249 109 7.466900962752578 
		117 1.4737452584091115 128 -0.65430975189149443 139 -0.65433760985661737 151 -0.6543525852875508 
		164 -0.65433281569519974 192 -0.65433281569519974 196 -0.65434063769347461 202 -0.65434557853030539 
		238 -0.65434557853030539 248 -0.65434541866566054 259 -0.65434461382875697 271 -0.65434447716890254 
		331 -0.65434447716890254 345 -0.65431979866218637 364 -0.65429667998451091 379 -0.65429786558287384 
		390 -8.7448375966342624 393 5.1762282881998098 398 -8.1457208232728053 416 -91.805770186418073 
		420 4.4778437912238749 428 -0.65411518990058948 439 -0.65423790163494466 456 -0.65432377532926256 
		490 -0.65433304464838149 499 -0.65435415495800975 508 -0.65434574267178802 624 -0.65442418356761478 
		644 -0.65434833410512705 655 -0.65434831422276263 666 -0.65434822152339067 677 -0.65434819959567458 
		682 -0.65434328684772769 686 -0.65429628354040004 690 -0.65444841251775798 695 -0.65458012172719637 
		704 -0.65452478501678613 723 -0.65457390717818364 735 -0.65452705740154016 741 -0.65448475236516612 
		749 -0.65460480019240341 757 -0.65460968498033389 767 -0.65460958946899417 792 -0.6546031157652934 
		815 -0.65461892346581807 841 -0.65396385716822114 858 -0.65383501159521862 880 -0.65388190149898884;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "SpineEff_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 5.9520631208405699e-005 57 5.8247202742693878 
		62 9.0221879808404779 65 6.8771766827646861 68 6.1722704157868939 71 -0.69928371144143864 
		76 10.441929978146144 80 11.734787723068182 87 13.694980330838229 91 5.635282457747441 
		96 -11.958263910021428 100 -6.0563779475828783 105 2.1069548512803427 109 -0.24158194289203272 
		117 0.31438099103359551 128 2.5513587152792381 139 5.4139132890096553 151 5.7731120879842504 
		164 5.5628931749558896 192 5.5628931749558896 196 5.5628002220990167 202 5.5627204114224797 
		238 5.5627204114224797 248 5.562497422387886 259 5.5613747863957741 271 5.5611841648293883 
		331 5.5611841648293883 345 6.7993001403242816 364 8.1601066955538286 379 8.1318476945551925 
		390 33.580528398976028 393 35.44402649849475 398 48.293323070160625 416 30.85130508898644 
		420 24.924753161546622 428 13.747779287704612 439 11.022985965585272 456 6.6989938730725633 
		490 6.6990538250111484 499 6.6990499209399594 508 6.6990285136129177 624 6.696994571470297 
		644 7.6246972741317922 655 7.6245761963051253 666 7.6240116840464207 677 7.6238781506221471 
		682 3.5049828046203939 686 -4.2863160225621639 690 -9.4255591245294319 695 -20.282128109884201 
		704 -21.465826968163061 723 -20.282268699881755 735 -12.562664318503737 741 -7.4049983063586637 
		749 -1.0082910409928609 757 3.8692983942896992 767 5.6309933529612239 792 5.6325564801582209 
		815 5.6341993447556282 841 5.222041389388691 858 5.1409736743778458 880 5.8166630048151147;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "SpineEff_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.00010469541988805705 57 -5.5799058679140963 
		62 1.6680868122804302 65 9.9377831094465456 68 23.046877205775811 71 34.158896154698155 
		76 46.958266500344564 80 49.929176084139478 87 49.485220741846618 91 43.496920856600774 
		96 38.425754677344941 100 37.349318925876815 105 35.413172136137199 109 36.629117582266439 
		117 39.993117072601166 128 41.313067174603177 139 39.86918507812026 151 39.684813528456708 
		164 39.895719864777973 192 39.895719864777973 196 39.895829202857868 202 39.895867976584 
		238 39.895867976584 248 39.896615083368701 259 39.900376384761728 271 39.901015046953411 
		331 39.901015046953411 345 40.884847849447816 364 41.65266083997075 379 41.656283434859525 
		390 30.619130381054813 393 29.120218031532794 398 49.331946323707889 416 35.730527130012632 
		420 45.933383065245593 428 24.652985337406296 439 31.529198098044478 456 41.842320737416067 
		490 41.842457138507129 499 41.842397938841692 508 41.842417295122701 624 41.84097296683003 
		644 39.954390402447437 655 39.954020199902359 666 39.952294170614813 677 39.951885884350695 
		682 46.23525829759069 686 61.206938923889659 690 63.129711822693501 695 60.140777777668042 
		704 59.654134905441772 723 60.140882774122645 735 58.377349577658542 741 57.396432756550332 
		749 55.877916236426458 757 53.679780962024758 767 53.188849318087918 792 53.188954035269084 
		815 53.188881214136721 841 55.09668087781521 858 55.471927691370418 880 55.487640880200118;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "SpineEff_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.00015219694237852624 57 -7.0424711223759244 
		62 -28.170629770149361 65 -37.390993027179128 68 -38.412755218099846 71 -34.858449769050715 
		76 -17.656035284155944 80 -16.601083809847943 87 -19.724967763506761 91 -14.875258494049474 
		96 -20.124951115491211 100 -16.321891869744551 105 -15.644340692275444 109 -20.903263879322438 
		117 -23.618849436764702 128 -24.640909117307366 139 -20.114735166444621 151 -19.537566519635348 
		164 -19.8751985860487 192 -19.8751985860487 196 -19.87523062005058 202 -19.875284108114471 
		238 -19.875284108114471 248 -19.878049784710424 259 -19.891973554974832 271 -19.894337786049221 
		331 -19.894337786049221 345 -20.215716782495189 364 -20.569386289783225 379 -20.56192143252823 
		390 32.889535481781166 393 -2.8818734379667821 398 -22.725302312481325 416 -26.15557767912474 
		420 9.3605212356521932 428 -26.107576247225204 439 -28.714833377348427 456 -20.192499750050345 
		490 -20.192437313101095 499 -20.192446166417184 508 -20.19243642392366 624 -20.18601857571716 
		644 -25.966457182571542 655 -25.964907187908203 666 -25.957680505595931 677 -25.955971058864851 
		682 -24.973805306150403 686 -21.503843830920854 690 -28.733796618618086 695 -28.161808474798029 
		704 -29.999192958070893 723 -28.161871694890998 735 -20.754467422390231 741 -15.42709285766438 
		749 -8.9043219112259795 757 -4.4331966059219461 767 -2.8477438177540915 792 -2.8477102646343946 
		815 -2.8476969119405902 841 -2.5769623541565378 858 -2.5237113330656427 880 -2.2623775462092124;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightUpLegEff_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 0.0037078384720120325 57 -32.072381878395312 
		62 -45.799026303552054 65 -52.113873537375483 68 -29.847936612964808 71 -14.576407717715602 
		76 -11.488872734232908 80 -23.721539790531224 87 -43.917658940842564 91 -49.034769426159656 
		96 -52.199705418842377 100 -51.645795132726327 105 -46.881688710333144 109 -40.421005386759383 
		117 -19.873009667586473 128 -7.2488200209842013 139 -12.15809785430935 151 -12.700054588979105 
		164 -12.614583523250451 192 -12.614795467852069 196 -12.614740181669433 202 -12.614394658615796 
		238 -12.614394658615796 248 -12.613863521746216 259 -12.611189518660753 271 -12.610735477760361 
		331 -12.610735477760361 345 -14.658927197950002 364 -16.490855468977053 379 -16.49405280583613 
		390 -41.678463078871921 393 -36.063993738190675 398 -68.294224200338476 416 -76.247401809802227 
		420 -91.005752081074917 428 -37.300537366162516 439 -25.075591928065311 456 -35.571956443809668 
		490 -30.852037329326542 499 -28.215547024357672 508 -28.490494356153825 624 -29.709538229926512 
		644 -27.226349454121898 655 -25.421267200707327 666 -17.005266616008051 677 -15.014490756955714 
		682 -16.65708724137026 686 -37.524874293081119 690 -37.925122132873732 695 -37.824163149450101 
		704 -37.90111895157667 723 -37.824194285693139 735 -37.797004876798248 741 -37.879455279172866 
		749 -38.123545055747947 757 -38.616536508450061 767 -38.726785388157865 792 -38.731885216326596 
		815 -38.731538802209698 841 -38.731305411705243 858 -38.731259505919226 880 -38.731446544498269;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightUpLegEff_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 2.2865887575451987e-005 57 -14.006370453792821 
		62 -12.064446645269403 65 -8.7236440935630934 68 -6.5423734445825819 71 3.5778547498867868 
		76 19.213733287771433 80 19.369606172764666 87 13.934348981094423 91 11.481411230536692 
		96 10.205120673399001 100 8.7382943515253793 105 4.88427475747842 109 4.245683046820206 
		117 2.2591869620021345 128 0.8598507052460338 139 4.0877635762019615 151 4.4901939934298634 
		164 4.1157916719174912 192 4.1158137059853823 196 4.115794162124347 202 4.1157796567898561 
		238 4.1157796567898561 248 4.1157960087286058 259 4.1158783323953907 271 4.1158923108055108 
		331 4.1158923108055108 345 3.6459835906667797 364 4.0118709305017051 379 3.9648689899245237 
		390 17.798278146906437 393 50.236999744821709 398 33.46167622558842 416 20.974706515342991 
		420 25.443596120324756 428 14.166126987337476 439 16.220832093710641 456 20.292813184754035 
		490 11.448495755918245 499 10.52067583544874 508 8.0516221740609701 624 1.4752586188992223 
		644 1.4254133739724653 655 1.4403853205824024 666 1.5101904007580917 677 1.5267025512807071 
		682 3.0830074908295133 686 7.044979083567644 690 14.038067948013543 695 18.605227376942519 
		704 19.315688111251038 723 18.605258118183212 735 21.462425157204212 741 23.241960869071487 
		749 25.779631289850382 757 28.216258930080155 767 29.399232015089062 792 29.3991547486781 
		815 29.399118412261934 841 29.399137002349477 858 29.399140658850339 880 29.399052298099875;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTA -n "RightUpLegEff_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -6.0733027305541992e-005 57 12.850996296151886 
		62 36.556221469491646 65 60.111266325907174 68 72.155674146604596 71 72.415937597532945 
		76 69.621528462139679 80 68.755849697984203 87 65.297425731146532 91 64.708387405531113 
		96 64.192924974105722 100 65.730388736805807 105 67.836459952502466 109 70.268741654675679 
		117 74.248222054491151 128 75.005462288991311 139 74.862864643830633 151 74.839399914597976 
		164 75.008969282839843 192 75.009012396608128 196 75.009054763364674 202 75.008990898531991 
		238 75.008990898531991 248 75.008646331549741 259 75.006911612635534 271 75.006617060493099 
		331 75.006617060493099 345 75.891049357083432 364 76.845851653509726 379 76.850185577343808 
		390 68.198618820555936 393 75.932580059004621 398 28.182423147905929 416 8.5607693453252018 
		420 36.874236248145095 428 65.031433731094793 439 68.430982032005517 456 69.468508250135798 
		490 73.271805208627086 499 73.799756714957454 508 74.560145045186701 624 76.533448447757536 
		644 76.378886848529049 655 76.454630246145925 666 76.807775637401562 677 76.891310959502832 
		682 81.835929584542257 686 90.791976345643022 690 88.607704967604803 695 86.321071464672116 
		704 86.08347405744118 723 86.321098203353401 735 84.892528784067139 741 83.983707959504073 
		749 82.651585185854572 757 81.038999236661738 767 80.678840340427357 792 80.678563133811764 
		815 80.678375558746069 841 80.678387427024944 858 80.678389761407274 880 80.678181488201432;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "CenterRootFK_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 4.5155625230108853e-006 57 -1.093940258026123 
		62 -2.9342637062072754 65 -4.4515342712402344 68 -6.3206934928894043 71 -8.0594396591186523 
		76 -8.8480062484741211 80 -8.4235458374023437 87 -6.8811044692993164 91 -6.4094877243041992 
		96 -6.167325496673584 100 -6.286628246307373 105 -6.6997480392456055 109 -7.1922607421875 
		117 -8.4247159957885742 128 -8.9224319458007813 139 -8.7336330413818359 151 -8.7093906402587891 
		164 -8.7191495895385742 192 -8.7191495895385742 196 -8.7191495895385742 202 -8.7191495895385742 
		238 -8.7191495895385742 248 -8.7191476515522996 259 -8.7191378947804115 271 -8.7191362380981445 
		331 -8.7191362380981445 345 -8.6575832366943359 364 -8.5952415466308594 379 -8.5949085840463262 
		390 -6.4325523376464844 393 -6.7929000854492187 398 -6.6742968559265137 416 -5.6030526161193848 
		420 -6.7853946685791016 428 -8.9184150695800781 439 -9.0032405853271484 456 -8.6679468154907227 
		490 -8.5780086517333984 499 -8.578007698059082 508 -8.578007698059082 624 -8.578007698059082 
		644 -8.65240478515625 655 -8.6524049261225535 666 -8.6524055833626843 677 -8.6524057388305664 
		682 -8.6557857686972977 686 -8.6742019653320312 690 -8.7844953536987305 695 -8.699275016784668 
		704 -8.723942756652832 723 -8.699275016784668 735 -8.6779766082763672 741 -8.6663761138916016 
		749 -8.6503067016601562 757 -8.6321296684242608 767 -8.6280698776245117 792 -8.6280698776245117 
		815 -8.6280698776245117 841 -8.6280698776245117 858 -8.6280698776245117 880 -8.6280698776245117;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "CenterRootFK_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 8.4977874755859375 57 7.1193637847900391 
		62 5.7385730743408203 65 4.3493962287902832 68 3.9293270111083984 71 3.6249933242797852 
		76 3.8851766586303711 80 3.8280494213104248 87 3.5188479423522949 91 3.3515067100524902 
		96 3.261397123336792 100 3.2384860515594482 105 3.3293259143829346 109 3.3329167366027832 
		117 3.3732104301452637 128 3.4308195114135742 139 3.3851089477539062 151 3.3798999786376953 
		164 3.3630557060241699 192 3.3630557060241699 196 3.3630557060241699 202 3.3630557060241699 
		238 3.3630557060241699 248 3.3630470889066273 259 3.3630037061173383 271 3.3629963397979736 
		331 3.3629963397979736 345 3.2406811714172363 364 3.1166782379150391 379 3.1159675645646465 
		390 3.298250675201416 393 3.0798115730285645 398 4.5096893310546875 416 4.7473068237304687 
		420 3.2249069213867187 428 3.486191987991333 439 3.3353252410888672 456 3.1099183559417725 
		490 3.0798728466033936 499 3.0798728466033936 508 3.0798728466033936 624 3.079890251159668 
		644 3.1174802780151367 655 3.1174838726558858 666 3.1175006322792149 677 3.1175045967102051 
		682 2.6032859105783821 686 1.3927402496337891 690 1.3712127208709717 695 1.4033498764038086 
		704 1.3976753950119019 723 1.4033498764038086 735 1.4105050563812256 741 1.413353443145752 
		749 1.4157147407531738 757 1.4158849774745741 767 1.415922999382019 792 1.4159126281738281 
		815 1.415922999382019 841 1.415922999382019 858 1.415922999382019 880 1.415922999382019;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode animCurveTL -n "CenterRootFK_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 62 ".ktv[0:61]"  50 -0.008767811581492424 57 -0.55194319691533167 
		62 -1.0679562091827393 65 -1.9294326305389404 68 -2.5760722160339355 71 -2.3668637275695801 
		76 -1.5850436687469482 80 -1.3398237228393555 87 -1.1882929801940918 91 -1.201421856880188 
		96 -1.2611764669418335 100 -1.3206329345703125 105 -1.3426449298858643 109 -1.2874329237060547 
		117 -0.95325171947479248 128 -0.83946920910644529 139 -0.85563689470291138 151 -0.85765200853347778 
		164 -0.85608136653900146 192 -0.85608136653900146 196 -0.85608131980895996 202 -0.85608130693435669 
		238 -0.85608130693435669 248 -0.85608150592401877 259 -0.85608250773541805 271 -0.85608267784118652 
		331 -0.85608267784118652 345 -0.85606695690917967 364 -0.85606886425781248 379 -0.85559991584738704 
		390 -0.94305731335449217 393 -0.97798086682128904 398 -0.69348646679687498 416 -0.74282385388183592 
		420 -0.6906368879394531 428 -0.96974493542480467 439 -0.93371702709960935 456 -0.83179785290527342 
		490 -0.83179785290527342 499 -0.83179785290527342 508 -0.83179785290527342 624 -0.83179976025390623 
		644 -0.83179785290527342 655 -0.8317975709726656 666 -0.83179625649240452 677 -0.8317959455566406 
		682 -0.81020024744091135 686 -0.76613165417480467 690 -0.83658529797363279 695 -0.85655333081054685 
		704 -0.87253309765624998 723 -0.85655333081054685 735 -0.8865292219238281 741 -0.90583540478515623 
		749 -0.9335873273925781 757 -0.96479628860396327 767 -0.97176672497558592 792 -0.97176672497558592 
		815 -0.97176672497558592 841 -0.97176672497558592 858 -0.97176672497558592 880 -0.97176672497558592;
	setAttr -s 62 ".kit[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 10 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
	setAttr -s 62 ".kot[27:61]"  9 3 10 10 10 9 9 10 
		10 9 10 10 10 10 10 10 9 9 2 9 9 10 10 10 10 
		9 9 9 9 3 10 3 9 9 3;
createNode lambert -n "lambert2";
	setAttr ".dc" 1;
	setAttr ".c" -type "float3" 0.40900001 0.21351436 0.15133001 ;
	setAttr ".ambc" -type "float3" 1 1 1 ;
createNode shadingEngine -n "lambert2SG";
	setAttr ".ihi" 0;
	setAttr -s 6 ".dsm";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode lambert -n "lambert4";
	setAttr ".dc" 1;
createNode shadingEngine -n "lambert4SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode file -n "file1";
	setAttr ".ftn" -type "string" "G:/Home/MyComputer/E/dev/autodesk/maya/myplugin/project/liquid_/test/animation_test/MoxMotionMeetsFBIK/MoxMotionMeetsFBIK/sourceimages/FBIK.0001.bmp";
	setAttr ".ufe" yes;
	setAttr ".ece" 3;
createNode place2dTexture -n "place2dTexture1";
createNode displayLayer -n "layer1";
	setAttr ".dt" 2;
	setAttr ".do" 1;
createNode animCurveTU -n "file1_frameExtension";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  637 1 650 2 658 3;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTU -n "RHan_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  674 1 675 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode animCurveTU -n "Sp14_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  674 0 675 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
createNode lightLinker -n "MoxMotion:lightLinker1";
createNode displayLayerManager -n "MoxMotion:layerManager";
	setAttr ".cdl" 1;
	setAttr -s 2 ".dli[1]"  1;
createNode displayLayer -n "MoxMotion:defaultLayer";
createNode renderLayerManager -n "MoxMotion:renderLayerManager";
createNode renderLayer -n "MoxMotion:defaultRenderLayer";
	setAttr ".g" yes;
createNode lightLinker -n "MoxMotion:lightLinker2";
createNode dagPose -n "MoxMotion:hikStancePose";
	addAttr -ci true -sn "hikPose" -ln "hikPose" -bt "HIKP" -min 0 -max 1 -at "bool";
	setAttr -s 23 ".wm";
	setAttr ".wm[0]" -type "matrix" 0.81749643527644233 -0.57593365790714957 0 0 0.57593365790714957 0.81749643527644233 0 0
		 0 0 1 0 0 8.4977872187512844 -0.0087677710271807235 1;
	setAttr ".wm[1]" -type "matrix" -2.2204460492503131e-016 -0.99589320646770396 0.090535746042518808 0
		 1.8041124150158794e-016 0.090535746042518878 0.99589320646770385 0 -1 1.6653345369377348e-016 2.2204460492503131e-016 0
		 0.79392608644671492 7.9384590855092805 -0.0087677710271807235 1;
	setAttr ".wm[2]" -type "matrix" -2.5055100317637641e-016 -0.99614341334943968 -0.087739956921164056 0
		 -1.4901161454429018e-008 0.087739956921164 -0.99614341334943968 0 1 1.3074270854351057e-009 -1.4843693918546604e-008 0
		 0.79392608644671336 4.4608972136133511 0.3073742173269956 1;
	setAttr ".wm[3]" -type "matrix" 1.485310430017223e-008 -0.0075185844740167929 0.99997173504429993 0
		 2.9802323041142354e-008 0.99997173504429948 0.007518584474016347 0 -0.99999999999999956 2.9689806289486679e-008 1.5076755823621183e-008 0
		 0.7939260864467117 0.91799066767122595 -0.0046837288992930826 1;
	setAttr ".wm[4]" -type "matrix" 1 -5.4351218357587378e-016 -1.7624641027844059e-016 0
		 6.1376370986643881e-016 1.0000000000000002 8.100456590893912e-010 0 1.1535922695774343e-016 -8.1004566068952257e-010 1.0000000000000002 0
		 0.79392608644671181 0.90437719391160376 1.8059082811306884 1;
	setAttr ".wm[5]" -type "matrix" 8.8817841970012523e-016 0.99976737234005641 0.021568523460321228 0
		 -4.3496456436642461e-014 0.021568523460321235 -0.99976737234005664 0 -0.99999999999999989 -1.6653345369377348e-016 4.3631764867768652e-014 0
		 -2.7755575615628914e-016 9.2940231266641362 0.054283625774385988 1;
	setAttr ".wm[6]" -type "matrix" -1.1465954119043092e-015 0.99968237722196418 -0.025202076736688252 0
		 4.336794693473151e-014 0.025202076736688232 0.99968237722196451 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615629111e-016 10.550792300495431 0.081396588409426568 1;
	setAttr ".wm[7]" -type "matrix" -9.2758154485989307e-016 0.99979689629958546 -0.020153564193847423 0
		 4.3373184052475599e-014 0.020153564193847402 0.99979689629958579 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.775557561562919e-016 12.304005107215648 0.032420088196603906 1;
	setAttr ".wm[8]" -type "matrix" -5.3268900522569938e-017 0.99999999999999978 0 0
		 4.3383068872505149e-014 -1.3877787807814457e-017 1 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615630353e-016 13.113895811633148 0.016094588125663136 1;
	setAttr ".wm[9]" -type "matrix" -3.7944666293932018e-016 0.99997173504429948 -0.0075185844740132263 0
		 4.3381442145256909e-014 0.0075185844740132107 0.9999717350442997 0 0.99999999999999989 1.696198179545186e-016 -4.3509339085425761e-014 0
		 -2.7755575615627277e-016 13.424080312981028 0.016094588125663865 1;
	setAttr ".wm[10]" -type "matrix" 5.3702581391468984e-017 -0.99999999999999989 -2.1935578353726726e-015 0
		 0.99999999999999989 1.6944700264318177e-016 -9.8390514717364857e-017 0 -1.3767369280097435e-016 -2.2083029849184829e-015 1 0
		 -2.7755575615605622e-016 15.595371822416165 -0.00023091194527194783 1;
	setAttr ".wm[11]" -type "matrix" 0.99996049616811267 -0.0088885377437186337 7.7686504868642555e-017 0
		 0.0088885377437186164 0.99996049616811267 -5.3245117464711273e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 0.40512274026087475 12.301487859188555 0.5881854259223428 1;
	setAttr ".wm[12]" -type "matrix" 0.99996049616811267 -0.0088885377437186337 7.7686504868642555e-017 0
		 0.0088885377437186164 0.99996049616811267 -5.3245117464711273e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 1.6207842174864149 12.716500000000002 0.032420099999999841 1;
	setAttr ".wm[13]" -type "matrix" 0.99989989043539251 -0.014149526751437356 8.0486825569771596e-017 0
		 0.014149526751437339 0.99989989043539251 -5.3203507152395223e-016 0 -1.3767369280098697e-016 5.6551985316843172e-016 1 0
		 4.0868290114069348 12.698237905248352 0.032420088196603795 1;
	setAttr ".wm[14]" -type "matrix" -1.1829291194997161e-015 0.99965391935284864 -0.026306682088170261 0
		 4.2938593627986796e-014 0.026306682088170264 0.99965391935284886 0 1 -8.8470897274841653e-017 -4.3225747236789631e-014 0
		 6.4502761152311603 12.664792899062167 0.032420088196603788 1;
	setAttr ".wm[15]" -type "matrix" 0.99996049616811289 0.0088885377437182833 -1.3080557290033257e-016 0
		 0.0088885377437182833 -0.99996049616811289 2.2747537872961659e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -0.40512299999999996 12.301500000000001 0.58818499999999985 1;
	setAttr ".wm[16]" -type "matrix" 0.99996049616811289 0.0088885377437182833 -1.3080557290033257e-016 0
		 0.0088885377437182833 -0.99996049616811289 2.2747537872961659e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -1.6207799999999999 12.7165 0.032420100000000063 1;
	setAttr ".wm[17]" -type "matrix" 0.99989989043539274 0.014149526751437007 -2.5048583555603365e-016 0
		 0.014149526751437007 -0.99989989043539274 2.2746534817987389e-014 0 1.3767369280097435e-016 -2.2822022049950868e-014 -1.0000000000000002 0
		 -4.0868300000000009 12.6982 0.0324201 1;
	setAttr ".wm[18]" -type "matrix" -1.3063990685270031e-015 -0.99965391935284809 0.026306682088201791 0
		 4.300410681092003e-014 -0.026306682088201847 -0.99965391935284831 0 1.0000000000000002 -9.3675067701769556e-017 4.2926000693912566e-014 0
		 -6.4502800000000002 12.664799999999998 0.032420099999999993 1;
	setAttr ".wm[19]" -type "matrix" -2.7755575615628914e-016 0.99589320646770396 -0.090535746042518836 0
		 -2.2204460492503131e-016 -0.09053574604251885 -0.99589320646770396 0 -1.0000000000000002 -5.5511151231257827e-017 1.1102230246251565e-016 0
		 -0.79392600000000002 7.9384600000000001 -0.0087677699999999994 1;
	setAttr ".wm[20]" -type "matrix" -2.3371745768259975e-016 0.99614341334943968 0.087739956921164736 0
		 1.4533590695203183e-016 -0.087739956921164694 0.9961434133494399 0 1.0000000000000002 4.4766105491174724e-017 1.0970081802495344e-017 0
		 -0.79392599999999991 4.4609000000000005 0.30737399999999993 1;
	setAttr ".wm[21]" -type "matrix" -1.2611185544294434e-016 0.0075185844740161684 -0.99997173504430037 0
		 2.8606535729832003e-008 -0.99997173504429959 -0.0075185844740163627 0 -1 -2.8605726967513279e-008 -2.1508066452454373e-010 0
		 -0.79392600000000002 0.91799099999999934 -0.0046837299999999971 1;
	setAttr ".wm[22]" -type "matrix" 1.0000000000000002 4.7055732516436705e-016 6.8032416151445676e-016 0
		 6.7139351880062871e-016 -1.0000000000000002 2.8338269308462013e-009 0 4.3445754053683564e-016 -2.8338271270319533e-009 -1.0000000000000004 0
		 -0.79392600000000002 0.90437699999999999 1.8059100000000001 1;
	setAttr -s 23 ".xm";
	setAttr ".xm[0]" -type "matrix" "xform" 1 1 1 0 0 0 0 0 8.4977872187512844 -0.0087677710271807235 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.30207909951166573 0.95328286339271895 1
		 1 1 no;
	setAttr ".xm[1]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.97116764329161098 -8.8817841970012523e-016
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.61228175042846322 -0.35371041558350652 -0.2968244148732222 0.64179067205372287 1
		 1 1 no;
	setAttr ".xm[2]" -type "matrix" "xform" 1 1 1 0 0 0 0 3.4919023940632776 0 7.9640379218268858e-016 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.99601929086857066 -0.089137939272061567 -6.6412940624832101e-010 7.4209220636957947e-009 1
		 1 1 no;
	setAttr ".xm[3]" -type "matrix" "xform" 1 1 1 0 0 0 0 3.5566229706116621 -1.0408340855860843e-015
		 -7.4085556220108205e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.6781416192235713 -0.73493125139487192 -1.1390739715758539e-008 1.0510554096506117e-008 1
		 1 1 no;
	setAttr ".xm[4]" -type "matrix" "xform" 1 1 1 0 0 0 0 1.8106431877794722 0 2.6893672037114261e-008 0
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 -0.0026582290137860398 0.70710177929356999 0.0026582500475783033 0.70710178987544814 1
		 1 1 no;
	setAttr ".xm[5]" -type "matrix" "xform" 1 1 1 0 0 0 0 -0.45857905900126905 0.65092001635785746
		 0.063051396801566711 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 -0.31881347569894425 -0.63115605654444684 0.6241328962579018 0.33235241507885122 1
		 1 1 no;
	setAttr ".xm[6]" -type "matrix" "xform" 1 1 1 0 0 0 0 1.2570616011299709 1.6653345369377348e-016
		 1.1164949863573216e-015 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.99972652557249897 0.023385338713383021 1.43193901011606e-018 6.1215594478253268e-017 1
		 1 1 no;
	setAttr ".xm[7]" -type "matrix" "xform" 1 1 1 0 0 0 0 1.753890255914718 -0.0047763404700590841
		 2.2181426004632228e-015 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0.0025249056177588302 0.99999681242073035 1
		 1 1 no;
	setAttr ".xm[8]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.81005522963217835 1.3156142841808105e-014
		 7.5139228132346923e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0.010077293793829904 0.99994922278573373 1
		 1 1 no;
	setAttr ".xm[9]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.31018450134788011 7.2858385991025898e-016
		 1.6523187345942356e-017 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.0037593188013453145 0.99999293373610887 1
		 1 1 no;
	setAttr ".xm[10]" -type "matrix" "xform" 1 1 1 0 0 0 0 2.1713528826281756 -3.7470027081099033e-015
		 8.2391260537731378e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.0026582398170741889 -0.70710178458344786 -0.7071017845834171 0.0026582398170740735 1
		 1 1 no;
	setAttr ".xm[11]" -type "matrix" "xform" 1 1 1 0 0 0 0 -0.013717389175275806
		 0.55560172820939646 0.40512274026085099 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 -0.49268663963527454 -0.50720792099978373 -0.49717551337478738 0.50280862055109476 1
		 1 1 no;
	setAttr ".xm[12]" -type "matrix" "xform" 1 1 1 0 0 0 0 1.2119246028612083 0.42580119916550901
		 -0.55576532592234285 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 no;
	setAttr ".xm[13]" -type "matrix" "xform" 1 1 1 0 0 0 0 2.4661096990200342 0.0036581588995341918
		 -1.1803396232634711e-008 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.0026306690401006255 0.99999653978421421 1
		 1 1 no;
	setAttr ".xm[14]" -type "matrix" "xform" 1 1 1 0 0 0 0 2.3636837311734236 -8.8817841970012523e-015
		 -1.9428902930940239e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.4897834525553868 0.51001193084372709 0.4969508480062037 0.50303066970702037 1
		 1 1 no;
	setAttr ".xm[15]" -type "matrix" "xform" 1 1 1 0 0 0 0 -0.013705242245819704
		 0.55560154705414755 -0.40512300000002383 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.50720792099975598 -0.49268663963525877 0.5028086205511112 0.49717551337481447 1
		 1 1 no;
	setAttr ".xm[16]" -type "matrix" "xform" 1 1 1 0 0 0 0 -1.2119202337265964 -0.42578901903769406
		 0.55576489999999013 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 no;
	setAttr ".xm[17]" -type "matrix" "xform" 1 1 1 0 0 0 0 -2.4661152418160852 -0.0036203014230196118
		 3.0531133177191805e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.0026306690401006255 0.99999653978421421 1
		 1 1 no;
	setAttr ".xm[18]" -type "matrix" "xform" 1 1 1 0 0 0 0 -2.3636859902430261 -4.504266014038194e-005
		 5.9674487573602164e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.48978345255538447 0.51001193084372931 0.49695084800620143 0.50303066970702282 1
		 1 1 no;
	setAttr ".xm[19]" -type "matrix" "xform" 1 1 1 0 0 0 0 -0.32689630381082502
		 -0.91449671276985356 1.0271807241585273e-009 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
		-0.35371041558350641 -0.61228175042846322 0.64179067205372287 0.29682441487322209 1
		 1 1 no;
	setAttr ".xm[20]" -type "matrix" "xform" 1 1 1 0 0 0 0 -3.4919005100859799 4.7983946482865747e-008
		 8.8817841970012523e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.99601929086857055 -0.089137939272061914 -5.4581246006060889e-018 6.0988591822560571e-017 1
		 1 1 no;
	setAttr ".xm[21]" -type "matrix" "xform" 1 1 1 0 0 0 0 -3.5566253962335659 4.307113291440734e-007
		 -8.8817841970012523e-016 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0.67814161922357086 -0.73493125139487236 -1.0511918461106913e-008 9.6996411471568642e-009 1
		 1 1 no;
	setAttr ".xm[22]" -type "matrix" "xform" 1 1 1 0 0 0 0 -1.8106449116574583 5.1329376338227206e-007
		 1.4876988529977098e-014 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 -0.0026582307051105092 0.70710178454164463 0.0026582509328424986 0.70710178461768725 1
		 1 1 no;
	setAttr -s 23 ".m";
	setAttr -s 23 ".p";
createNode lambert -n "MoxMotion:lambert3";
	setAttr ".dc" 1;
	setAttr ".c" -type "float3" 0.60000002 0.60000002 1 ;
createNode shadingEngine -n "MoxMotion:lambert3SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "MoxMotion:materialInfo7";
createNode displayLayerManager -n "Man:layerManager";
	setAttr ".cdl" 1;
	setAttr -s 2 ".dli[1]"  1;
createNode displayLayer -n "Man:defaultLayer";
createNode renderLayerManager -n "Man:renderLayerManager";
createNode renderLayer -n "Man:defaultRenderLayer";
	addAttr -ci true -sn "usedBy3dfm" -ln "usedBy3dfm" -at "message";
	setAttr ".g" yes;
createNode lambert -n "Man:Hair";
	setAttr ".c" -type "float3" 0 0 0 ;
createNode shadingEngine -n "Man:lambert2SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Man:materialInfo1";
createNode lambert -n "Man:Body";
	setAttr ".c" -type "float3" 1 0.95419699 0.83700001 ;
createNode shadingEngine -n "Man:lambert3SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Man:materialInfo2";
createNode lambert -n "Man:GroundAtt";
	setAttr ".c" -type "float3" 0.96700001 0.96700001 0.96700001 ;
createNode shadingEngine -n "Man:lambert4SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "Man:materialInfo3";
createNode mib_amb_occlusion -n "Man:mib_amb_occlusion1";
	setAttr ".S00" 32;
	setAttr ".S01" -type "float3" 0.60176003 0.60176003 0.60176003 ;
	setAttr ".S03" 0.5;
createNode script -n "liquidCleanUpNode";
	setAttr ".b" -type "string" "if ( `whatIs liquid` == \"Command\" ) liquidCreateScriptNode;";
	setAttr ".a" -type "string" "if ( `whatIs liquid` == \"Command\" ) liquidCleanUp;";
	setAttr ".st" 2;
createNode liquidGlobals -n "liquidGlobals";
	setAttr ".rc" -type "string" "MoxrenderCamShape";
	setAttr ".ddin[0]" -type "string" "$SCN.$CAM.$F.$RND.bmp";
	setAttr ".ddim[0]" -type "string" "rgba";
	setAttr ".ddit[0]" -type "string" "it";
	setAttr ".ddbd[0]"  8;
	setAttr ".shdd" -type "string" "generatedShader";
	setAttr ".unt" yes;
	setAttr ".osg" yes;
	setAttr ".rdc" -type "string" "prman";
	setAttr ".prv" -type "string" "prman";
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
createNode animCurveTU -n "MoxrenderCamShape_focalLength";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  906 18 916 530.17829482071704;
	setAttr -s 2 ".kit[1]"  3;
	setAttr -s 2 ".kot[1]"  3;
	setAttr -s 2 ".kix[0:1]"  0.00035746846697293222 1;
	setAttr -s 2 ".kiy[0:1]"  0.99999994039535522 0;
	setAttr -s 2 ".kox[0:1]"  0.00036557603743858635 1;
	setAttr -s 2 ".koy[0:1]"  1 0;
createNode animCurveTL -n "camera2_aim_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  851 -5 856 -4.0364615718282764 873 -4.0295825837221528 
		906 -4.0168658171992817 939 -4.0240326644074855 977 -4.0158724481841972 1000 -4.020649833344395;
	setAttr -s 7 ".kit[1:6]"  9 1 3 10 10 10;
	setAttr -s 7 ".kot[1:6]"  9 1 3 10 10 10;
	setAttr -s 7 ".kix[2:6]"  0.99079287052154541 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  -0.13538682460784912 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  0.99079287052154541 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  -0.13538675010204315 0 0 0 0;
createNode animCurveTL -n "camera2_aim_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  851 0 856 -3.9856513671927036 873 -3.6265261296864062 
		906 -4.4292913946672829 939 -4.4244081001077991 977 -4.4945544009210696 1000 -4.4825760126153229;
	setAttr -s 7 ".kit[1:6]"  9 9 3 10 10 10;
	setAttr -s 7 ".kot[1:6]"  9 9 3 10 10 10;
createNode animCurveTL -n "camera2_aim_translateX";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  851 0 856 -5.9621345210915626 873 -6.2752872842835146 
		906 -5.9231357443580688 939 -5.8911290536352352 977 -5.9643859550507807 1000 -5.9375145674768044;
	setAttr -s 7 ".kit[0:6]"  10 9 1 1 1 10 9;
	setAttr -s 7 ".kot[0:6]"  10 9 1 1 1 10 9;
	setAttr -s 7 ".kix[2:6]"  0.80037516355514526 0.99532264471054077 
		0.99852460622787476 1 0.99938637018203735;
	setAttr -s 7 ".kiy[2:6]"  0.5994994044303894 0.096606500446796417 
		-0.054300412535667419 0 0.035028137266635895;
	setAttr -s 7 ".kox[2:6]"  0.80037522315979004 0.99532270431518555 
		0.99852466583251953 1 0.99938637018203735;
	setAttr -s 7 ".koy[2:6]"  0.59949946403503418 0.096606500446796417 
		-0.054300412535667419 0 0.035028137266635895;
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 1;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 8 ".st";
	setAttr -cb on ".an";
	setAttr -cb on ".pt";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 8 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -cb on ".an";
	setAttr -cb on ".il";
	setAttr -cb on ".vo";
	setAttr -cb on ".eo";
	setAttr -cb on ".fo";
	setAttr -cb on ".epo";
	setAttr ".ro" yes;
	setAttr -cb on ".mimt";
	setAttr -cb on ".miop";
	setAttr -cb on ".mise";
	setAttr -cb on ".mism";
	setAttr -cb on ".mice";
	setAttr -av ".micc";
	setAttr -cb on ".mica";
	setAttr -cb on ".micw";
	setAttr -cb on ".mirw";
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -cb on ".an";
	setAttr -cb on ".il";
	setAttr -cb on ".vo";
	setAttr -cb on ".eo";
	setAttr -cb on ".fo";
	setAttr -cb on ".epo";
	setAttr ".ro" yes;
	setAttr -cb on ".mimt";
	setAttr -cb on ".miop";
	setAttr -cb on ".mise";
	setAttr -cb on ".mism";
	setAttr -cb on ".mice";
	setAttr -cb on ".micc";
	setAttr -cb on ".mica";
	setAttr -cb on ".micw";
	setAttr -cb on ".mirw";
select -ne :defaultRenderGlobals;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".mcfr" 30;
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr ".ren" -type "string" "liquid";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".outf";
	setAttr ".imfkey" -type "string" "iff";
	setAttr -k on ".gama";
	setAttr ".an" yes;
	setAttr ".fs" 1;
	setAttr ".ef" 300;
	setAttr -av ".bfs";
	setAttr -k on ".be";
	setAttr ".ep" 4;
	setAttr -k on ".fec";
	setAttr -k on ".ofc";
	setAttr ".pff" yes;
	setAttr ".ifp" -type "string" "Mox/MoxMotion";
	setAttr -k on ".comp";
	setAttr -k on ".cth";
	setAttr -k on ".soll";
	setAttr -k on ".rd";
	setAttr -k on ".lp";
	setAttr -k on ".sp";
	setAttr -k on ".shs";
	setAttr -k on ".lpr";
	setAttr -k on ".mm";
	setAttr -k on ".npu";
	setAttr -k on ".itf";
	setAttr -k on ".shp";
	setAttr -k on ".uf";
	setAttr -k on ".oi";
	setAttr -k on ".rut";
	setAttr -av -k on ".mbf";
	setAttr -k on ".afp";
	setAttr -k on ".pfb";
	setAttr -av -k on ".bll";
	setAttr -k on ".bls";
	setAttr -k on ".smv";
	setAttr -k on ".ubc";
	setAttr -k on ".mbc";
	setAttr -k on ".udbx";
	setAttr -k on ".smc";
	setAttr -k on ".kmv";
	setAttr -k on ".rlen";
	setAttr -av -k on ".frts";
	setAttr -k on ".tlwd";
	setAttr -k on ".tlht";
	setAttr -k on ".jfc";
select -ne :defaultRenderQuality;
	setAttr ".rfl" 10;
	setAttr ".rfr" 10;
	setAttr ".sl" 10;
	setAttr ".eaa" 0;
	setAttr ".ufil" yes;
	setAttr ".ss" 2;
	setAttr ".ert" yes;
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".w" 1280;
	setAttr ".h" 720;
	setAttr ".pa" 1;
	setAttr -k on ".al";
	setAttr ".dar" 1.7769999504089355;
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
	setAttr -k off -cb on ".ehql";
	setAttr -k off -cb on ".eams";
	setAttr -k off ".eeaa";
	setAttr -k off ".engm";
	setAttr -k off ".mes";
	setAttr -k off ".emb";
	setAttr -k off ".mbbf";
	setAttr -k off ".mbs";
	setAttr -k off ".trm";
	setAttr -k off -cb on ".tshc";
	setAttr -k off ".clmt";
	setAttr -k off -cb on ".tcov";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr -k off -cb on ".mgcs";
	setAttr -k off ".twa";
	setAttr -k off ".twz";
	setAttr -k on ".hwcc";
	setAttr -k on ".hwdp";
	setAttr -k on ".hwql";
	setAttr ".hwfr" 30;
select -ne :defaultHardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".rp";
	setAttr -k on ".cai";
	setAttr -k on ".coi";
	setAttr -cb on ".bc";
	setAttr -av -k on ".bcb";
	setAttr -av -k on ".bcg";
	setAttr -av -k on ".bcr";
	setAttr -k on ".ei";
	setAttr -k on ".ex";
	setAttr -k on ".es";
	setAttr -av ".ef";
	setAttr -k on ".bf";
	setAttr -k on ".fii";
	setAttr -k on ".sf";
	setAttr -k on ".gr";
	setAttr -k on ".li";
	setAttr -k on ".ls";
	setAttr -k on ".mb";
	setAttr -k on ".ti";
	setAttr -k on ".txt";
	setAttr -k on ".mpr";
	setAttr -k on ".wzd";
	setAttr ".fn" -type "string" "im";
	setAttr -k on ".if";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
	setAttr -k on ".as";
	setAttr -k on ".ds";
	setAttr -k on ".lm";
	setAttr -k on ".fir";
	setAttr -k on ".aap";
	setAttr -k on ".gh";
	setAttr -cb on ".sd";
connectAttr "camera2_aim.tx" "camera2_group.tg[0].ttx";
connectAttr "camera2_aim.ty" "camera2_group.tg[0].tty";
connectAttr "camera2_aim.tz" "camera2_group.tg[0].ttz";
connectAttr "camera2_aim.rp" "camera2_group.tg[0].trp";
connectAttr "camera2_aim.rpt" "camera2_group.tg[0].trt";
connectAttr "camera2_aim.pm" "camera2_group.tg[0].tpm";
connectAttr "MoxrenderCam.pim" "camera2_group.cpim";
connectAttr "MoxrenderCam.t" "camera2_group.ct";
connectAttr "MoxrenderCam.rp" "camera2_group.crp";
connectAttr "MoxrenderCam.rpt" "camera2_group.crt";
connectAttr "camera2_group.crx" "MoxrenderCam.rx";
connectAttr "camera2_group.cry" "MoxrenderCam.ry";
connectAttr "camera2_group.crz" "MoxrenderCam.rz";
connectAttr "camera2_group.db" "MoxrenderCamShape.coi";
connectAttr "MoxrenderCamShape_focalLength.o" "MoxrenderCamShape.fl";
connectAttr "camera2_aim_translateX.o" "camera2_aim.tx";
connectAttr "camera2_aim_translateY.o" "camera2_aim.ty";
connectAttr "camera2_aim_translateZ.o" "camera2_aim.tz";
connectAttr ":time1.o" "MoxMotion:hikHandle1.tim";
connectAttr "MoxMotion:CenterRoot.msg" "MoxMotion:hikHandle1.jt[0]";
connectAttr "MoxMotion:LeftHip.msg" "MoxMotion:hikHandle1.jt[1]";
connectAttr "MoxMotion:LeftKnee.msg" "MoxMotion:hikHandle1.jt[2]";
connectAttr "MoxMotion:LeftFoot.msg" "MoxMotion:hikHandle1.jt[3]";
connectAttr "MoxMotion:LeftToe.msg" "MoxMotion:hikHandle1.jt[4]";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.msg" "MoxMotion:hikHandle1.jt[5]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine.msg" "MoxMotion:hikHandle1.jt[6]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.msg" "MoxMotion:hikHandle1.jt[7]"
		;
connectAttr "MoxMotion:CenterNeck.msg" "MoxMotion:hikHandle1.jt[8]";
connectAttr "MoxMotion:CenterHead.msg" "MoxMotion:hikHandle1.jt[9]";
connectAttr "MoxMotion:LeftCollar.msg" "MoxMotion:hikHandle1.jt[10]";
connectAttr "MoxMotion:LeftShoulder.msg" "MoxMotion:hikHandle1.jt[11]";
connectAttr "MoxMotion:LeftElbow.msg" "MoxMotion:hikHandle1.jt[12]";
connectAttr "MoxMotion:LeftHand.msg" "MoxMotion:hikHandle1.jt[13]";
connectAttr "MoxMotion:RightCollar.msg" "MoxMotion:hikHandle1.jt[14]";
connectAttr "MoxMotion:RightShoulder.msg" "MoxMotion:hikHandle1.jt[15]";
connectAttr "MoxMotion:RightElbow.msg" "MoxMotion:hikHandle1.jt[16]";
connectAttr "MoxMotion:RightHand.msg" "MoxMotion:hikHandle1.jt[17]";
connectAttr "MoxMotion:RightHip.msg" "MoxMotion:hikHandle1.jt[18]";
connectAttr "MoxMotion:RightKnee.msg" "MoxMotion:hikHandle1.jt[19]";
connectAttr "MoxMotion:RightFoot.msg" "MoxMotion:hikHandle1.jt[20]";
connectAttr "MoxMotion:RightToe.msg" "MoxMotion:hikHandle1.jt[21]";
connectAttr "MoxMotion:CenterRootFK.msg" "MoxMotion:hikHandle1.fj[0]";
connectAttr "MoxMotion:LeftHipFK.msg" "MoxMotion:hikHandle1.fj[1]";
connectAttr "MoxMotion:LeftKneeFK.msg" "MoxMotion:hikHandle1.fj[2]";
connectAttr "MoxMotion:LeftFootFK.msg" "MoxMotion:hikHandle1.fj[3]";
connectAttr "MoxMotion:LeftToeFK.msg" "MoxMotion:hikHandle1.fj[4]";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.msg" "MoxMotion:hikHandle1.fj[5]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.msg" "MoxMotion:hikHandle1.fj[6]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.msg" "MoxMotion:hikHandle1.fj[7]"
		;
connectAttr "MoxMotion:CenterNeckFK.msg" "MoxMotion:hikHandle1.fj[8]";
connectAttr "MoxMotion:CenterHeadFK.msg" "MoxMotion:hikHandle1.fj[9]";
connectAttr "MoxMotion:LeftCollarFK.msg" "MoxMotion:hikHandle1.fj[10]";
connectAttr "MoxMotion:LeftShoulderFK.msg" "MoxMotion:hikHandle1.fj[11]";
connectAttr "MoxMotion:LeftElbowFK.msg" "MoxMotion:hikHandle1.fj[12]";
connectAttr "MoxMotion:LeftHandFK.msg" "MoxMotion:hikHandle1.fj[13]";
connectAttr "MoxMotion:RightCollarFK.msg" "MoxMotion:hikHandle1.fj[14]";
connectAttr "MoxMotion:RightShoulderFK.msg" "MoxMotion:hikHandle1.fj[15]";
connectAttr "MoxMotion:RightElbowFK.msg" "MoxMotion:hikHandle1.fj[16]";
connectAttr "MoxMotion:RightHandFK.msg" "MoxMotion:hikHandle1.fj[17]";
connectAttr "MoxMotion:RightHipFK.msg" "MoxMotion:hikHandle1.fj[18]";
connectAttr "MoxMotion:RightKneeFK.msg" "MoxMotion:hikHandle1.fj[19]";
connectAttr "MoxMotion:RightFootFK.msg" "MoxMotion:hikHandle1.fj[20]";
connectAttr "MoxMotion:RightToeFK.msg" "MoxMotion:hikHandle1.fj[21]";
connectAttr "MoxMotion:LeftHandEff.ha" "MoxMotion:hikHandle1.eff[3]";
connectAttr "MoxMotion:SpineEff.ha" "MoxMotion:hikHandle1.eff[9]";
connectAttr "MoxMotion:LeftUpLegEff.ha" "MoxMotion:hikHandle1.eff[15]";
connectAttr "MoxMotion:RightUpLegEff.ha" "MoxMotion:hikHandle1.eff[16]";
connectAttr "MoxMotion:CenterRootFK.wm" "MoxMotion:hikHandle1.fm[0]";
connectAttr "MoxMotion:LeftHipFK.wm" "MoxMotion:hikHandle1.fm[1]";
connectAttr "MoxMotion:LeftKneeFK.wm" "MoxMotion:hikHandle1.fm[2]";
connectAttr "MoxMotion:LeftFootFK.wm" "MoxMotion:hikHandle1.fm[3]";
connectAttr "MoxMotion:LeftToeFK.wm" "MoxMotion:hikHandle1.fm[4]";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.wm" "MoxMotion:hikHandle1.fm[5]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.wm" "MoxMotion:hikHandle1.fm[6]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.wm" "MoxMotion:hikHandle1.fm[7]"
		;
connectAttr "MoxMotion:CenterNeckFK.wm" "MoxMotion:hikHandle1.fm[8]";
connectAttr "MoxMotion:CenterHeadFK.wm" "MoxMotion:hikHandle1.fm[9]";
connectAttr "MoxMotion:LeftCollarFK.wm" "MoxMotion:hikHandle1.fm[10]";
connectAttr "MoxMotion:LeftShoulderFK.wm" "MoxMotion:hikHandle1.fm[11]";
connectAttr "MoxMotion:LeftElbowFK.wm" "MoxMotion:hikHandle1.fm[12]";
connectAttr "MoxMotion:LeftHandFK.wm" "MoxMotion:hikHandle1.fm[13]";
connectAttr "MoxMotion:RightCollarFK.wm" "MoxMotion:hikHandle1.fm[14]";
connectAttr "MoxMotion:RightShoulderFK.wm" "MoxMotion:hikHandle1.fm[15]";
connectAttr "MoxMotion:RightElbowFK.wm" "MoxMotion:hikHandle1.fm[16]";
connectAttr "MoxMotion:RightHandFK.wm" "MoxMotion:hikHandle1.fm[17]";
connectAttr "MoxMotion:RightHipFK.wm" "MoxMotion:hikHandle1.fm[18]";
connectAttr "MoxMotion:RightKneeFK.wm" "MoxMotion:hikHandle1.fm[19]";
connectAttr "MoxMotion:RightFootFK.wm" "MoxMotion:hikHandle1.fm[20]";
connectAttr "MoxMotion:RightToeFK.wm" "MoxMotion:hikHandle1.fm[21]";
connectAttr "SpineEff_translateZ.o" "MoxMotion:SpineEff.tz";
connectAttr "SpineEff_translateX.o" "MoxMotion:SpineEff.tx";
connectAttr "SpineEff_translateY.o" "MoxMotion:SpineEff.ty";
connectAttr "SpineEff_rotateZ.o" "MoxMotion:SpineEff.rz";
connectAttr "SpineEff_rotateY.o" "MoxMotion:SpineEff.ry";
connectAttr "SpineEff_rotateX.o" "MoxMotion:SpineEff.rx";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.msg" "MoxMotion:SpineEff.jt"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.msg" "MoxMotion:SpineEff.fj"
		;
connectAttr "LeftUpLegEff_translateZ.o" "MoxMotion:LeftUpLegEff.tz";
connectAttr "LeftUpLegEff_translateY.o" "MoxMotion:LeftUpLegEff.ty";
connectAttr "LeftUpLegEff_translateX.o" "MoxMotion:LeftUpLegEff.tx";
connectAttr "LeftUpLegEff_rotateZ.o" "MoxMotion:LeftUpLegEff.rz";
connectAttr "LeftUpLegEff_rotateY.o" "MoxMotion:LeftUpLegEff.ry";
connectAttr "LeftUpLegEff_rotateX.o" "MoxMotion:LeftUpLegEff.rx";
connectAttr "MoxMotion:LeftHip.msg" "MoxMotion:LeftUpLegEff.jt";
connectAttr "MoxMotion:LeftHipFK.msg" "MoxMotion:LeftUpLegEff.fj";
connectAttr "RightUpLegEff_translateZ.o" "MoxMotion:RightUpLegEff.tz";
connectAttr "RightUpLegEff_translateX.o" "MoxMotion:RightUpLegEff.tx";
connectAttr "RightUpLegEff_translateY.o" "MoxMotion:RightUpLegEff.ty";
connectAttr "RightUpLegEff_rotateY.o" "MoxMotion:RightUpLegEff.ry";
connectAttr "RightUpLegEff_rotateX.o" "MoxMotion:RightUpLegEff.rx";
connectAttr "RightUpLegEff_rotateZ.o" "MoxMotion:RightUpLegEff.rz";
connectAttr "MoxMotion:RightHip.msg" "MoxMotion:RightUpLegEff.jt";
connectAttr "MoxMotion:RightHipFK.msg" "MoxMotion:RightUpLegEff.fj";
connectAttr "CenterRootFK_rotateZ.o" "MoxMotion:CenterRootFK.rz";
connectAttr "CenterRootFK_rotateY.o" "MoxMotion:CenterRootFK.ry";
connectAttr "CenterRootFK_rotateX.o" "MoxMotion:CenterRootFK.rx";
connectAttr "CenterRootFK_translateZ.o" "MoxMotion:CenterRootFK.tz";
connectAttr "CenterRootFK_translateY.o" "MoxMotion:CenterRootFK.ty";
connectAttr "CenterRootFK_translateX.o" "MoxMotion:CenterRootFK.tx";
connectAttr "MoxMotion:CenterRootFK.s" "MoxMotion:LeftHipFK.is";
connectAttr "LeftHipFK_rotateZ.o" "MoxMotion:LeftHipFK.rz";
connectAttr "LeftHipFK_rotateY.o" "MoxMotion:LeftHipFK.ry";
connectAttr "LeftHipFK_rotateX.o" "MoxMotion:LeftHipFK.rx";
connectAttr "MoxMotion:LeftHipFK.s" "MoxMotion:LeftKneeFK.is";
connectAttr "LeftKneeFK_rotateZ.o" "MoxMotion:LeftKneeFK.rz";
connectAttr "LeftKneeFK_rotateY.o" "MoxMotion:LeftKneeFK.ry";
connectAttr "LeftKneeFK_rotateX.o" "MoxMotion:LeftKneeFK.rx";
connectAttr "MoxMotion:LeftKneeFK.s" "MoxMotion:LeftFootFK.is";
connectAttr "LeftFootFK_rotateZ.o" "MoxMotion:LeftFootFK.rz";
connectAttr "LeftFootFK_rotateY.o" "MoxMotion:LeftFootFK.ry";
connectAttr "LeftFootFK_rotateX.o" "MoxMotion:LeftFootFK.rx";
connectAttr "LeftToeFK_rotateY.o" "MoxMotion:LeftToeFK.ry";
connectAttr "LeftToeFK_rotateZ.o" "MoxMotion:LeftToeFK.rz";
connectAttr "LeftToeFK_rotateX.o" "MoxMotion:LeftToeFK.rx";
connectAttr "MoxMotion:LeftFootFK.s" "MoxMotion:LeftToeFK.is";
connectAttr "MoxMotion:CenterRootFK.s" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.is"
		;
connectAttr "CenterSpineFK_rotateZ1.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.rz"
		;
connectAttr "CenterSpineFK_rotateY1.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.ry"
		;
connectAttr "CenterSpineFK_rotateX1.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.rx"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.s" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.is"
		;
connectAttr "MoxMotion:_spine_angularValues_4_.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.rz"
		;
connectAttr "MoxMotion:_spine_angularValues_5_.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.ry"
		;
connectAttr "MoxMotion:_spine_angularValues_6_.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.rx"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.s" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.is"
		;
connectAttr "CenterSpineFK_rotateZ.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.rz"
		;
connectAttr "CenterSpineFK_rotateY.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.ry"
		;
connectAttr "CenterSpineFK_rotateX.o" "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.rx"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.s" "MoxMotion:CenterNeckFK.is"
		;
connectAttr "CenterNeckFK_rotateZ.o" "MoxMotion:CenterNeckFK.rz";
connectAttr "CenterNeckFK_rotateY.o" "MoxMotion:CenterNeckFK.ry";
connectAttr "CenterNeckFK_rotateX.o" "MoxMotion:CenterNeckFK.rx";
connectAttr "CenterHeadFK_rotateZ.o" "MoxMotion:CenterHeadFK.rz";
connectAttr "CenterHeadFK_rotateY.o" "MoxMotion:CenterHeadFK.ry";
connectAttr "CenterHeadFK_rotateX.o" "MoxMotion:CenterHeadFK.rx";
connectAttr "MoxMotion:CenterNeckFK.s" "MoxMotion:CenterHeadFK.is";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.s" "MoxMotion:LeftCollarFK.is"
		;
connectAttr "LeftCollarFK_rotateZ.o" "MoxMotion:LeftCollarFK.rz";
connectAttr "LeftCollarFK_rotateY.o" "MoxMotion:LeftCollarFK.ry";
connectAttr "LeftCollarFK_rotateX.o" "MoxMotion:LeftCollarFK.rx";
connectAttr "MoxMotion:LeftCollarFK.s" "MoxMotion:LeftShoulderFK.is";
connectAttr "LeftShoulderFK_rotateZ.o" "MoxMotion:LeftShoulderFK.rz";
connectAttr "LeftShoulderFK_rotateY.o" "MoxMotion:LeftShoulderFK.ry";
connectAttr "LeftShoulderFK_rotateX.o" "MoxMotion:LeftShoulderFK.rx";
connectAttr "MoxMotion:LeftShoulderFK.s" "MoxMotion:LeftElbowFK.is";
connectAttr "LeftElbowFK_rotateZ.o" "MoxMotion:LeftElbowFK.rz";
connectAttr "LeftElbowFK_rotateY.o" "MoxMotion:LeftElbowFK.ry";
connectAttr "LeftElbowFK_rotateX.o" "MoxMotion:LeftElbowFK.rx";
connectAttr "MoxMotion:LeftElbowFK.s" "MoxMotion:LeftHandFK.is";
connectAttr "LeftHandFK_rotateZ.o" "MoxMotion:LeftHandFK.rz";
connectAttr "LeftHandFK_rotateY.o" "MoxMotion:LeftHandFK.ry";
connectAttr "LeftHandFK_rotateX.o" "MoxMotion:LeftHandFK.rx";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.s" "MoxMotion:RightCollarFK.is"
		;
connectAttr "RightCollarFK_rotateZ.o" "MoxMotion:RightCollarFK.rz";
connectAttr "RightCollarFK_rotateY.o" "MoxMotion:RightCollarFK.ry";
connectAttr "RightCollarFK_rotateX.o" "MoxMotion:RightCollarFK.rx";
connectAttr "MoxMotion:RightCollarFK.s" "MoxMotion:RightShoulderFK.is";
connectAttr "RightShoulderFK_rotateZ.o" "MoxMotion:RightShoulderFK.rz";
connectAttr "RightShoulderFK_rotateY.o" "MoxMotion:RightShoulderFK.ry";
connectAttr "RightShoulderFK_rotateX.o" "MoxMotion:RightShoulderFK.rx";
connectAttr "MoxMotion:RightShoulderFK.s" "MoxMotion:RightElbowFK.is";
connectAttr "RightElbowFK_rotateZ.o" "MoxMotion:RightElbowFK.rz";
connectAttr "RightElbowFK_rotateY.o" "MoxMotion:RightElbowFK.ry";
connectAttr "RightElbowFK_rotateX.o" "MoxMotion:RightElbowFK.rx";
connectAttr "MoxMotion:RightElbowFK.s" "MoxMotion:RightHandFK.is";
connectAttr "RightHandFK_rotateZ.o" "MoxMotion:RightHandFK.rz";
connectAttr "RightHandFK_rotateY.o" "MoxMotion:RightHandFK.ry";
connectAttr "RightHandFK_rotateX.o" "MoxMotion:RightHandFK.rx";
connectAttr "MoxMotion:CenterRootFK.s" "MoxMotion:RightHipFK.is";
connectAttr "RightHipFK_rotateZ.o" "MoxMotion:RightHipFK.rz";
connectAttr "RightHipFK_rotateY.o" "MoxMotion:RightHipFK.ry";
connectAttr "RightHipFK_rotateX.o" "MoxMotion:RightHipFK.rx";
connectAttr "MoxMotion:RightHipFK.s" "MoxMotion:RightKneeFK.is";
connectAttr "RightKneeFK_rotateZ.o" "MoxMotion:RightKneeFK.rz";
connectAttr "RightKneeFK_rotateY.o" "MoxMotion:RightKneeFK.ry";
connectAttr "RightKneeFK_rotateX.o" "MoxMotion:RightKneeFK.rx";
connectAttr "MoxMotion:RightKneeFK.s" "MoxMotion:RightFootFK.is";
connectAttr "RightFootFK_rotateZ.o" "MoxMotion:RightFootFK.rz";
connectAttr "RightFootFK_rotateY.o" "MoxMotion:RightFootFK.ry";
connectAttr "RightFootFK_rotateX.o" "MoxMotion:RightFootFK.rx";
connectAttr "RightToeFK_rotateY.o" "MoxMotion:RightToeFK.ry";
connectAttr "RightToeFK_rotateZ.o" "MoxMotion:RightToeFK.rz";
connectAttr "RightToeFK_rotateX.o" "MoxMotion:RightToeFK.rx";
connectAttr "MoxMotion:RightFootFK.s" "MoxMotion:RightToeFK.is";
connectAttr "MoxMotion:CenterRootFK.hfk" "MoxMotion:CenterRoot.hfk";
connectAttr "MoxMotion:CenterRoot.s" "MoxMotion:LeftHip.is";
connectAttr "MoxMotion:LeftHipFK.hfk" "MoxMotion:LeftHip.hfk";
connectAttr "MoxMotion:LeftHip.s" "MoxMotion:LeftKnee.is";
connectAttr "MoxMotion:LeftKneeFK.hfk" "MoxMotion:LeftKnee.hfk";
connectAttr "MoxMotion:LeftKnee.s" "MoxMotion:LeftFoot.is";
connectAttr "MoxMotion:LeftFootFK.hfk" "MoxMotion:LeftFoot.hfk";
connectAttr "MoxMotion:LeftFoot.s" "MoxMotion:LeftToe.is";
connectAttr "MoxMotion:LeftToeFK.hfk" "MoxMotion:LeftToe.hfk";
connectAttr "MoxMotion:CenterRoot.s" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.is"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK.hfk" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.hfk"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.s" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine.is"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.hfk" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine.hfk"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine.s" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.is"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxCnt|MoxMotion:CenterRootFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK|MoxMotion:CenterSpineFK.hfk" "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.hfk"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.s" "MoxMotion:CenterNeck.is"
		;
connectAttr "MoxMotion:CenterNeckFK.hfk" "MoxMotion:CenterNeck.hfk";
connectAttr "MoxMotion:CenterNeck.s" "MoxMotion:CenterHead.is";
connectAttr "MoxMotion:CenterHeadFK.hfk" "MoxMotion:CenterHead.hfk";
connectAttr "MoxMotion:CenterHead.s" "MoxMotion:joint11.is";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.s" "MoxMotion:LeftCollar.is"
		;
connectAttr "MoxMotion:LeftCollarFK.hfk" "MoxMotion:LeftCollar.hfk";
connectAttr "MoxMotion:LeftCollar.s" "MoxMotion:LeftShoulder.is";
connectAttr "MoxMotion:LeftShoulderFK.hfk" "MoxMotion:LeftShoulder.hfk";
connectAttr "MoxMotion:LeftShoulder.s" "MoxMotion:LeftElbow.is";
connectAttr "MoxMotion:LeftElbowFK.hfk" "MoxMotion:LeftElbow.hfk";
connectAttr "MoxMotion:LeftElbow.s" "MoxMotion:LeftHand.is";
connectAttr "MoxMotion:LeftHandFK.hfk" "MoxMotion:LeftHand.hfk";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.s" "MoxMotion:RightCollar.is"
		;
connectAttr "MoxMotion:RightCollarFK.hfk" "MoxMotion:RightCollar.hfk";
connectAttr "MoxMotion:RightCollar.s" "MoxMotion:RightShoulder.is";
connectAttr "MoxMotion:RightShoulderFK.hfk" "MoxMotion:RightShoulder.hfk";
connectAttr "MoxMotion:RightShoulder.s" "MoxMotion:RightElbow.is";
connectAttr "MoxMotion:RightElbowFK.hfk" "MoxMotion:RightElbow.hfk";
connectAttr "MoxMotion:RightElbow.s" "MoxMotion:RightHand.is";
connectAttr "MoxMotion:RightHandFK.hfk" "MoxMotion:RightHand.hfk";
connectAttr "Sp14_visibility.o" "Sp14.v";
connectAttr "RHan_visibility.o" "RHan.v";
connectAttr "MoxMotion:CenterRoot.s" "MoxMotion:RightHip.is";
connectAttr "MoxMotion:RightHipFK.hfk" "MoxMotion:RightHip.hfk";
connectAttr "MoxMotion:RightHip.s" "MoxMotion:RightKnee.is";
connectAttr "MoxMotion:RightKneeFK.hfk" "MoxMotion:RightKnee.hfk";
connectAttr "MoxMotion:RightKnee.s" "MoxMotion:RightFoot.is";
connectAttr "MoxMotion:RightFootFK.hfk" "MoxMotion:RightFoot.hfk";
connectAttr "MoxMotion:RightFoot.s" "MoxMotion:RightToe.is";
connectAttr "MoxMotion:RightToeFK.hfk" "MoxMotion:RightToe.hfk";
connectAttr "LeftHandEff_translateZ.o" "MoxMotion:LeftHandEff.tz";
connectAttr "LeftHandEff_translateX.o" "MoxMotion:LeftHandEff.tx";
connectAttr "LeftHandEff_translateY.o" "MoxMotion:LeftHandEff.ty";
connectAttr "LeftHandEff_rotateY.o" "MoxMotion:LeftHandEff.ry";
connectAttr "LeftHandEff_rotateX.o" "MoxMotion:LeftHandEff.rx";
connectAttr "LeftHandEff_rotateZ.o" "MoxMotion:LeftHandEff.rz";
connectAttr "MoxMotion:LeftHand.msg" "MoxMotion:LeftHandEff.jt";
connectAttr "MoxMotion:LeftHandFK.msg" "MoxMotion:LeftHandEff.fj";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "lambert2SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr "lambert4SG.msg" "lightLinker1.lnk[4].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[8].llnk";
connectAttr "MoxMotion:lambert3SG.msg" "lightLinker1.lnk[8].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[9].llnk";
connectAttr "Man:lambert2SG.msg" "lightLinker1.lnk[9].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[10].llnk";
connectAttr "Man:lambert3SG.msg" "lightLinker1.lnk[10].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[11].llnk";
connectAttr "Man:lambert4SG.msg" "lightLinker1.lnk[11].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[2].sllk";
connectAttr "lambert2SG.msg" "lightLinker1.slnk[2].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr "lambert4SG.msg" "lightLinker1.slnk[4].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[10].sllk";
connectAttr "MoxMotion:lambert3SG.msg" "lightLinker1.slnk[10].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[13].sllk";
connectAttr "Man:lambert2SG.msg" "lightLinker1.slnk[13].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[14].sllk";
connectAttr "Man:lambert3SG.msg" "lightLinker1.slnk[14].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[15].sllk";
connectAttr "Man:lambert4SG.msg" "lightLinker1.slnk[15].solk";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "lambert2.oc" "lambert2SG.ss";
connectAttr "polySurfaceShape4.iog" "lambert2SG.dsm" -na;
connectAttr "polySurfaceShape5.iog" "lambert2SG.dsm" -na;
connectAttr "polySurfaceShape22.iog" "lambert2SG.dsm" -na;
connectAttr "polySurfaceShape10.iog" "lambert2SG.dsm" -na;
connectAttr "polySurfaceShape11.iog" "lambert2SG.dsm" -na;
connectAttr "polySurfaceShape23.iog" "lambert2SG.dsm" -na;
connectAttr "lambert2SG.msg" "materialInfo1.sg";
connectAttr "lambert2.msg" "materialInfo1.m";
connectAttr "file1.oc" "lambert4.c";
connectAttr "file1.ot" "lambert4.it";
connectAttr "Man:mib_amb_occlusion1.S11" "lambert4.ambc";
connectAttr "lambert4.oc" "lambert4SG.ss";
connectAttr "lambert4SG.msg" "materialInfo3.sg";
connectAttr "lambert4.msg" "materialInfo3.m";
connectAttr "file1.msg" "materialInfo3.t" -na;
connectAttr "place2dTexture1.c" "file1.c";
connectAttr "place2dTexture1.tf" "file1.tf";
connectAttr "place2dTexture1.rf" "file1.rf";
connectAttr "place2dTexture1.mu" "file1.mu";
connectAttr "place2dTexture1.mv" "file1.mv";
connectAttr "place2dTexture1.s" "file1.s";
connectAttr "place2dTexture1.wu" "file1.wu";
connectAttr "place2dTexture1.wv" "file1.wv";
connectAttr "place2dTexture1.re" "file1.re";
connectAttr "place2dTexture1.of" "file1.of";
connectAttr "place2dTexture1.r" "file1.ro";
connectAttr "place2dTexture1.n" "file1.n";
connectAttr "place2dTexture1.vt1" "file1.vt1";
connectAttr "place2dTexture1.vt2" "file1.vt2";
connectAttr "place2dTexture1.vt3" "file1.vt3";
connectAttr "place2dTexture1.vc1" "file1.vc1";
connectAttr "place2dTexture1.o" "file1.uv";
connectAttr "place2dTexture1.ofs" "file1.fs";
connectAttr "file1_frameExtension.o" "file1.fe";
connectAttr "layerManager.dli[1]" "layer1.id";
connectAttr "MoxMotion:layerManager.dli[0]" "MoxMotion:defaultLayer.id";
connectAttr "MoxMotion:renderLayerManager.rlmi[0]" "MoxMotion:defaultRenderLayer.rlid"
		;
connectAttr "MoxMotion:CenterRoot.msg" "MoxMotion:hikStancePose.m[0]";
connectAttr "MoxMotion:LeftHip.msg" "MoxMotion:hikStancePose.m[1]";
connectAttr "MoxMotion:LeftKnee.msg" "MoxMotion:hikStancePose.m[2]";
connectAttr "MoxMotion:LeftFoot.msg" "MoxMotion:hikStancePose.m[3]";
connectAttr "MoxMotion:LeftToe.msg" "MoxMotion:hikStancePose.m[4]";
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine.msg" "MoxMotion:hikStancePose.m[5]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine.msg" "MoxMotion:hikStancePose.m[6]"
		;
connectAttr "|MoxMotion:MOX|MoxMotion:MoxBns|MoxMotion:CenterRoot|MoxMotion:CenterSpine|MoxMotion:CenterSpine|MoxMotion:CenterSpine.msg" "MoxMotion:hikStancePose.m[7]"
		;
connectAttr "MoxMotion:CenterNeck.msg" "MoxMotion:hikStancePose.m[8]";
connectAttr "MoxMotion:CenterHead.msg" "MoxMotion:hikStancePose.m[9]";
connectAttr "MoxMotion:joint11.msg" "MoxMotion:hikStancePose.m[10]";
connectAttr "MoxMotion:LeftCollar.msg" "MoxMotion:hikStancePose.m[11]";
connectAttr "MoxMotion:LeftShoulder.msg" "MoxMotion:hikStancePose.m[12]";
connectAttr "MoxMotion:LeftElbow.msg" "MoxMotion:hikStancePose.m[13]";
connectAttr "MoxMotion:LeftHand.msg" "MoxMotion:hikStancePose.m[14]";
connectAttr "MoxMotion:RightCollar.msg" "MoxMotion:hikStancePose.m[15]";
connectAttr "MoxMotion:RightShoulder.msg" "MoxMotion:hikStancePose.m[16]";
connectAttr "MoxMotion:RightElbow.msg" "MoxMotion:hikStancePose.m[17]";
connectAttr "MoxMotion:RightHand.msg" "MoxMotion:hikStancePose.m[18]";
connectAttr "MoxMotion:RightHip.msg" "MoxMotion:hikStancePose.m[19]";
connectAttr "MoxMotion:RightKnee.msg" "MoxMotion:hikStancePose.m[20]";
connectAttr "MoxMotion:RightFoot.msg" "MoxMotion:hikStancePose.m[21]";
connectAttr "MoxMotion:RightToe.msg" "MoxMotion:hikStancePose.m[22]";
connectAttr "MoxMotion:hikStancePose.w" "MoxMotion:hikStancePose.p[0]";
connectAttr "MoxMotion:hikStancePose.m[0]" "MoxMotion:hikStancePose.p[1]";
connectAttr "MoxMotion:hikStancePose.m[1]" "MoxMotion:hikStancePose.p[2]";
connectAttr "MoxMotion:hikStancePose.m[2]" "MoxMotion:hikStancePose.p[3]";
connectAttr "MoxMotion:hikStancePose.m[3]" "MoxMotion:hikStancePose.p[4]";
connectAttr "MoxMotion:hikStancePose.m[0]" "MoxMotion:hikStancePose.p[5]";
connectAttr "MoxMotion:hikStancePose.m[5]" "MoxMotion:hikStancePose.p[6]";
connectAttr "MoxMotion:hikStancePose.m[6]" "MoxMotion:hikStancePose.p[7]";
connectAttr "MoxMotion:hikStancePose.m[7]" "MoxMotion:hikStancePose.p[8]";
connectAttr "MoxMotion:hikStancePose.m[8]" "MoxMotion:hikStancePose.p[9]";
connectAttr "MoxMotion:hikStancePose.m[9]" "MoxMotion:hikStancePose.p[10]";
connectAttr "MoxMotion:hikStancePose.m[7]" "MoxMotion:hikStancePose.p[11]";
connectAttr "MoxMotion:hikStancePose.m[11]" "MoxMotion:hikStancePose.p[12]";
connectAttr "MoxMotion:hikStancePose.m[12]" "MoxMotion:hikStancePose.p[13]";
connectAttr "MoxMotion:hikStancePose.m[13]" "MoxMotion:hikStancePose.p[14]";
connectAttr "MoxMotion:hikStancePose.m[7]" "MoxMotion:hikStancePose.p[15]";
connectAttr "MoxMotion:hikStancePose.m[15]" "MoxMotion:hikStancePose.p[16]";
connectAttr "MoxMotion:hikStancePose.m[16]" "MoxMotion:hikStancePose.p[17]";
connectAttr "MoxMotion:hikStancePose.m[17]" "MoxMotion:hikStancePose.p[18]";
connectAttr "MoxMotion:hikStancePose.m[0]" "MoxMotion:hikStancePose.p[19]";
connectAttr "MoxMotion:hikStancePose.m[19]" "MoxMotion:hikStancePose.p[20]";
connectAttr "MoxMotion:hikStancePose.m[20]" "MoxMotion:hikStancePose.p[21]";
connectAttr "MoxMotion:hikStancePose.m[21]" "MoxMotion:hikStancePose.p[22]";
connectAttr "Man:mib_amb_occlusion1.S11" "MoxMotion:lambert3.ambc";
connectAttr "MoxMotion:lambert3.oc" "MoxMotion:lambert3SG.ss";
connectAttr "MoxMotion:Lowerarm_L_objShape.iog" "MoxMotion:lambert3SG.dsm" -na;
connectAttr "MoxMotion:lambert3SG.msg" "MoxMotion:materialInfo7.sg";
connectAttr "MoxMotion:lambert3.msg" "MoxMotion:materialInfo7.m";
connectAttr "Man:layerManager.dli[0]" "Man:defaultLayer.id";
connectAttr "Man:renderLayerManager.rlmi[0]" "Man:defaultRenderLayer.rlid";
connectAttr "Man:mib_amb_occlusion1.S11" "Man:Hair.ambc";
connectAttr "Man:Hair.oc" "Man:lambert2SG.ss";
connectAttr "Man:lambert2SG.msg" "Man:materialInfo1.sg";
connectAttr "Man:Hair.msg" "Man:materialInfo1.m";
connectAttr "Man:mib_amb_occlusion1.S11" "Man:Body.ambc";
connectAttr "Man:Body.oc" "Man:lambert3SG.ss";
connectAttr "Man:lambert3SG.msg" "Man:materialInfo2.sg";
connectAttr "Man:Body.msg" "Man:materialInfo2.m";
connectAttr "Man:mib_amb_occlusion1.S11" "Man:GroundAtt.ambc";
connectAttr "Man:GroundAtt.oc" "Man:lambert4SG.ss";
connectAttr "Man:lambert4SG.msg" "Man:materialInfo3.sg";
connectAttr "Man:GroundAtt.msg" "Man:materialInfo3.m";
connectAttr "lambert2SG.pa" ":renderPartition.st" -na;
connectAttr "lambert4SG.pa" ":renderPartition.st" -na;
connectAttr "MoxMotion:lambert3SG.pa" ":renderPartition.st" -na;
connectAttr "Man:lambert2SG.pa" ":renderPartition.st" -na;
connectAttr "Man:lambert3SG.pa" ":renderPartition.st" -na;
connectAttr "Man:lambert4SG.pa" ":renderPartition.st" -na;
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "lambert4.msg" ":defaultShaderList1.s" -na;
connectAttr "MoxMotion:lambert3.msg" ":defaultShaderList1.s" -na;
connectAttr "Man:Hair.msg" ":defaultShaderList1.s" -na;
connectAttr "Man:Body.msg" ":defaultShaderList1.s" -na;
connectAttr "Man:GroundAtt.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "pointLightShape1.ltd" ":lightList1.l" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Man:mib_amb_occlusion1.msg" ":defaultTextureList1.tx" -na;
connectAttr "Man:mib_amb_occlusion1.S11" ":lambert1.ambc";
connectAttr "pointLight1.iog" ":defaultLightSet.dsm" -na;
// End of MoxMotionMeetsFBIK_NoAux.ma
