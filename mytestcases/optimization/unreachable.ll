@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
define i32 @myfunction(i32 %a,i32 %b,i32 %c) {
%1 = alloca i32
store i32 %a, i32* %1
%2 = alloca i32
store i32 %b, i32* %2
%3 = alloca i32
store i32 %c, i32* %3
%4 = load i32* %1
%5 = load i32* %2
%6 = add  i32 %4, %5
%7 = load i32* %3
%8 = add  i32 %6, %7
ret i32 %8
}
%struct.mystruct = type { i32 } 
define i32 @main() {
%b = alloca i32
%c = alloca i32
%1 = call i32 @myfunction(i32 1, i32 2, i32 3)
%a = alloca i32
store i32 %1, i32* %a
%ms = alloca %struct.mystruct
%2 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* %a)
%3 = call i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* %b)
%4 = load i32* %a
%5 = load i32* %b
%6 = add  i32 %4, %5
%7 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0), i32 %6)
ret i32 0
}
declare i32 @scanf(i8*, ...)
declare i32 @printf(i8*, ...)
