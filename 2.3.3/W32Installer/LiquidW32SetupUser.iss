#include "liquidversion.iss"

[Setup]
AppPublisher=Liquidmaya at Sourceforge
AppPublisherURL=http://liquidmaya.sf.net/
AppSupportURL=http://www.plastickitten.net/liquidwiki/
AppUpdatesURL=http://www.plastickitten.net/liquidwiki/index.php/Download
DefaultDirName={pf}\Liquid
DefaultGroupName=Liquid
AllowNoIcons=true
LicenseFile=mpl.rtf
WizardImageFile=.\liquidlarge.bmp
WizardSmallImageFile=.\liquidsmall.bmp
WizardImageBackColor=$FFFFFF
AlwaysShowDirOnReadyPage=true
AlwaysShowGroupOnReadyPage=true
Compression=lzma/ultra
SolidCompression=yes
FlatComponentsList=true
WindowVisible=false
DisableStartupPrompt=true
ShowTasksTreeLines=yes

[Dirs]
Name: {app}\bin;
Name: {app}\mel;
Name: {app}\scripts;
Name: {app}\renderers;
Name: {app}\shaders;
Name: {app}\shaders\src;

[Files]
Source: ..\LICENSE.txt; DestDir: {app}
Source: ..\README.txt; DestDir: {app}
Source: ..\CHANGES.txt; DestDir: {app}
Source: ..\mel\*.mel; DestDir: {app}\mel
Source: ..\mel\*.png; DestDir: {app}\mel
Source: ..\renderers\*.lg; DestDir: {app}\renderers
Source: ..\scripts\*.py; DestDir: {app}\scripts
Source: ..\shaders\compile.cmd; DestDir: {app}\shaders; Flags: deleteafterinstall
Source: ..\shaders\src\*.sl; DestDir: {app}\shaders\src
Source: ..\shaders\src\*.h; DestDir: {app}\shaders\src
Source: ..\icons\*.xpm; DestDir: {app}\icons
Source: ..\icons\*.iff; DestDir: {app}\icons
Source: ..\icons\*.jpg; DestDir: {app}\icons
;Source: ..\artwork\*.png; DestDir: {app}\artwork

[Tasks]
Name: registry; Description: Create LIQUIDHOME &environment variable; MinVersion: 0,4.0.1381;
Name: shaders; Description: &Compile Liquid shaders; MinVersion: 0,4.0.1381

[Icons]
Name: {group}\Liquid Wiki; Filename: {app}\LiquidWiki.url
Name: {group}\Liquid Website; Filename: {app}\Liquid.url
Name: {group}\Uninstall Liquid; Filename: {uninstallexe}
Name: {group}\Artwork; Filename: {app}\artwork; Flags: foldershortcut

[Messages]
WelcomeLabel2=This will install [name/ver] on your computer.%n%nIt is recommended — but not strictly neccessary — that you close all other applications before continuing.%n%nThe source code for this plug-in is available via anonymous CVS access from cvs.sourceforge.net:/cvsroot/liquidmaya. The project’s homepage is at http://liquidmaya.sf.net/.
DiskSpaceMBLabel=The program requires at least [mb] MB of disk space.
ComponentsDiskSpaceMBLabel=The current selection requires at least [mb] MB of disk space.
FinishedLabel=Setup has finished installing [name] on your computer.%n%nThanks for using [name].%n
SelectTasksLabel2=Select the additional tasks you would like Setup to perform, then click Next.
NoIconsCheck=&Suppress creation of a Start Menu folder for Liquid

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: LIQUIDHOME; ValueData: {app}; MinVersion: 0,4.00.1381; Flags: uninsdeletevalue; Tasks: registry

[Types]
Name: full; Description: Full Installation
Name: minimal; Description: Minimal Installation — Just the Plug-In
Name: custom; Description: Custom Installation; Flags: iscustom

[Run]
Filename: "{app}\shaders\compile.cmd"; WorkingDir: "{app}\shaders"; Flags: runhidden shellexec waituntilidle skipifdoesntexist; Tasks: shaders
Filename: "{app}\CHANGES.txt"; Description: "View CHANGES.txt"; Flags: postinstall nowait shellexec skipifdoesntexist skipifsilent

[UninstallDelete]
Type: files; Name: {app}\Liquid.url

[INI]
Filename: {app}\Liquid.url; Section: InternetShortcut; Key: URL; String: http://liquid.sf.net/
Filename: {app}\LiquidWiki.url; Section: InternetShortcut; Key: URL; String: http://www.plastickitten.net/liquidwiki/

[LangOptions]
WelcomeFontName=Tahoma
DialogFontName=Tahoma
DialogFontSize=8

[_ISTool]
EnableISX=true

[Code]
function GetTargetRenderer: String;
begin
  #include "targetrenderer.iss"
end;

function InsertPath_NT(PathToAdd: String; RootKey: Integer; Location: String; PathVar: String): Boolean;
var CurrentPath: String;
var Offset: Integer;
begin
  Offset := 0;
  if RegValueExists(RootKey, Location, PathVar) then begin
    RegQueryStringValue(RootKey, Location, PathVar, CurrentPath);
    if Pos(PathToAdd, CurrentPath) = 0 then begin
      if (StrGet(CurrentPath, Length(CurrentPath)) <> ';') then
        Offset := 1;
      Insert(';', CurrentPath, Length(CurrentPath)+Offset);
      Insert(PathToAdd, CurrentPath, Length(CurrentPath)+Offset);
      RegWriteStringValue(RootKey, Location, PathVar, CurrentPath);
    end;
  end
  else
    RegWriteStringValue(RootKey, Location, PathVar, PathToAdd);
  Result := True;
end;

function NextButtonClick(CurPage: Integer): Boolean;
var EnvName: String;
begin
  EnvName := 'Environment';
  if CurPage = wpFinished then begin
    InsertPath_NT(ExpandConstant('{app}\bin\maya7')+GetTargetRenderer, HKCU, 'Environment', 'MAYA_PLUG_IN_PATH')
    InsertPath_NT(ExpandConstant('{app}\mel'), HKCU, 'Environment', 'MAYA_SCRIPT_PATH')
    InsertPath_NT(ExpandConstant('{app}\bin\maya7')+GetTargetRenderer, HKCU, 'Environment', 'PATH')
    SendBroadcastMessage(26, 0, CastStringToInteger(EnvName));
  end;
  Result := True;
end;

function PowerUserPrivileges(): Boolean;
begin
  Result := IsPowerUserLoggedOn() or IsAdminLoggedOn();
end;

function AdminPrivileges(): Boolean;
begin
  Result := IsAdminLoggedOn();
end;

function NoAdminPrivileges(): Boolean;
begin
  Result := not IsAdminLoggedOn();
end;

