set TARGET_NUMBER=%1
set CMD=xcopy
%CMD% "InputData\day01\*.*" "InputData\day%TARGET_NUMBER%\*.*" /s/h/e/k/f/c
%CMD% "Shared\day\dayXX.*" "Shared\day\day%TARGET_NUMBER%.*" /h/k/f/c
%CMD% "TestLibrary\TestDayXX.*" "TestLibrary\TestDay%TARGET_NUMBER%.*" /h/k/f/c