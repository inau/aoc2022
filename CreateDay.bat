set TARGET_NUMBER=%1
set CMD=xcopy
%CMD% "InputData\day01\*.*" "InputData\day%TARGET_NUMBER%\*.*" /s/h/e/k/f/c
%CMD% "Shared\day\day08.*" "Shared\day\day%TARGET_NUMBER%.*" /h/k/f/c
%CMD% "TestLibrary\TestDay08.*" "TestLibrary\TestDay%TARGET_NUMBER%.*" /h/k/f/c