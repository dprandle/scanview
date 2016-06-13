@echo off
mkdir "bin\x86"
copy "deps\libssh\bin\x86\ssh.dll" "bin\x86"
copy "deps\libssh\bin\x86\zlib1.dll" "bin\x86"