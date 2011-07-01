
surface
test_maketexture (
 string texName = "E:/MyDocuments/maya/projects/default/textures/cat.tex";
 float ss = 0;
 float tt = 1;
)
{
 vector inColor = vector color texture( texName, ss, tt );

 Oi = 1;

 Ci = color inColor;
}