echo off
echo ------------------------------------
set CURRENTDIR=%CD%
echo 'after you enter the password, run the following command:'
echo 'python %CURRENTDIR%\image_diff.py'
echo ------------------------------------

echo "runas /noprofile /user:%COMPUTERNAME%\administrator cmd"
runas /noprofile /user:%COMPUTERNAME%\administrator cmd
pause