@.A_vtable = global [2 x i8*] [i8* bitcast (i32 (i8*,i32)* @A.funA to i8*), i8* bitcast (i32 (i8*)* @A.funA2 to i8*)] 
@.B_vtable = global [5 x i8*] [i8* bitcast (i32 (i8*,i32)* @A.funA to i8*), i8* bitcast (i32 (i8*)* @A.funA2 to i8*), i8* bitcast (i32 (i8*)* @B.funC to i8*), i8* bitcast (i32 (i8*,i32,i32)* @B.funB to i8*), i8* bitcast (i32 (i8*)* @B.funOtherB to i8*)] 
@.C_vtable = global [5 x i8*] [i8* bitcast (i32 (i8*,i32)* @A.funA to i8*), i8* bitcast (i32 (i8*)* @A.funA2 to i8*), i8* bitcast (i32 (i8*)* @B.funC to i8*), i8* bitcast (i32 (i8*,i32,i32)* @C.funB to i8*), i8* bitcast (i32 (i8*)* @B.funOtherB to i8*)] 
@.D_vtable = global [1 x i8*] [i8* bitcast (i32 (i8*)* @D.funCall to i8*)] 
@.HT9_vtable = global [0 x i8*] [] 

declare i8* @calloc(i32, i32)
declare i32 @printf(i8*, ...)
declare void @exit(i32)

@_cint = constant [4 x i8] c"%d\0a\00"
@_cOOB = constant [15 x i8] c"Out of bounds\0a\00"

define void @print_int(i32 %i) {
	%_str = bitcast [4 x i8]* @_cint to i8*
	call i32 (i8*, ...) @printf(i8* %_str, i32 %i)
	ret void
}

define void @throw_oob() {
	%_str = bitcast [15 x i8]* @_cOOB to i8*
	call i32 (i8*, ...) @printf(i8* %_str)
	call void @exit(i32 1)
	ret void
}

define i32 @main() {
	%_0 = call i8* @calloc(i32 1, i32 8)
	%_1 = bitcast i8* %_0 to i8***
	%_2 = getelementptr [1 x i8*], [1 x i8*]* @.D_vtable, i32 0, i32 0
	store i8** %_2, i8*** %_1
	; D.funCall : 0
	%_3 = bitcast i8* %_0 to i8***
	%_4 = load i8**, i8*** %_3
	%_5 = getelementptr i8*, i8** %_4, i32 0
	%_6 = load i8*, i8** %_5
	%_7 = bitcast i8* %_6 to i32 (i8*)* 
	%_8 = call i32 %_7 ( i8* %_0 ) 
	call void (i32) @print_int(i32 %_8)
	ret i32 0
}


define i32 @D.funCall(i8* %this) {
	%objA  = alloca i8*
	%objB  = alloca i8*
	%n  = alloca i32
	store i32 5000, i32* %n
	%_0 = call i8* @calloc(i32 1, i32 12)
	%_1 = bitcast i8* %_0 to i8***
	%_2 = getelementptr [2 x i8*], [2 x i8*]* @.A_vtable, i32 0, i32 0
	store i8** %_2, i8*** %_1
	store i8* %_0, i8** %objA
	%_3 = load i8*, i8** %objA
	; A.funA : 0
	%_4 = bitcast i8* %_3 to i8***
	%_5 = load i8**, i8*** %_4
	%_6 = getelementptr i8*, i8** %_5, i32 0
	%_7 = load i8*, i8** %_6
	%_8 = bitcast i8* %_7 to i32 (i8*,i32)* 
	%_9 = load i32, i32* %n
	%_10 = call i32 %_8 ( i8* %_3, i32 %_9 ) 
	store i32 %_10, i32* %n
	%_11 = load i32, i32* %n
	call void (i32) @print_int(i32 %_11)
	%_12 = call i8* @calloc(i32 1, i32 16)
	%_13 = bitcast i8* %_12 to i8***
	%_14 = getelementptr [5 x i8*], [5 x i8*]* @.B_vtable, i32 0, i32 0
	store i8** %_14, i8*** %_13
	store i8* %_12, i8** %objB
	%_15 = load i8*, i8** %objB
	; B.funB : 3
	%_16 = bitcast i8* %_15 to i8***
	%_17 = load i8**, i8*** %_16
	%_18 = getelementptr i8*, i8** %_17, i32 3
	%_19 = load i8*, i8** %_18
	%_20 = bitcast i8* %_19 to i32 (i8*,i32,i32)* 
	%_21 = load i32, i32* %n
	%_22 = call i32 %_20 ( i8* %_15, i32 %_21, i32 10000 ) 
	store i32 %_22, i32* %n
	%_23 = load i32, i32* %n
	call void (i32) @print_int(i32 %_23)
	%_24 = load i8*, i8** %objB
	store i8* %_24, i8** %objA
	%_25 = load i8*, i8** %objA
	; A.funA : 0
	%_26 = bitcast i8* %_25 to i8***
	%_27 = load i8**, i8*** %_26
	%_28 = getelementptr i8*, i8** %_27, i32 0
	%_29 = load i8*, i8** %_28
	%_30 = bitcast i8* %_29 to i32 (i8*,i32)* 
	%_31 = load i32, i32* %n
	%_32 = call i32 %_30 ( i8* %_25, i32 %_31 ) 
	store i32 %_32, i32* %n
	%_33 = load i32, i32* %n
	call void (i32) @print_int(i32 %_33)
	%_34 = call i8* @calloc(i32 1, i32 20)
	%_35 = bitcast i8* %_34 to i8***
	%_36 = getelementptr [5 x i8*], [5 x i8*]* @.C_vtable, i32 0, i32 0
	store i8** %_36, i8*** %_35
	store i8* %_34, i8** %objB
	%_37 = load i8*, i8** %objB
	; B.funB : 3
	%_38 = bitcast i8* %_37 to i8***
	%_39 = load i8**, i8*** %_38
	%_40 = getelementptr i8*, i8** %_39, i32 3
	%_41 = load i8*, i8** %_40
	%_42 = bitcast i8* %_41 to i32 (i8*,i32,i32)* 
	%_43 = load i32, i32* %n
	%_44 = load i32, i32* %n
	%_45 = call i32 %_42 ( i8* %_37, i32 %_43, i32 %_44 ) 
	store i32 %_45, i32* %n
	%_46 = load i32, i32* %n
	call void (i32) @print_int(i32 %_46)
	%_47 = load i8*, i8** %objB
	; B.funC : 2
	%_48 = bitcast i8* %_47 to i8***
	%_49 = load i8**, i8*** %_48
	%_50 = getelementptr i8*, i8** %_49, i32 2
	%_51 = load i8*, i8** %_50
	%_52 = bitcast i8* %_51 to i32 (i8*)* 
	%_53 = call i32 %_52 ( i8* %_47 ) 
	store i32 %_53, i32* %n
	%_54 = load i32, i32* %n
	ret i32 %_54
}


define i32 @A.funA(i8* %this, i32 %.a) {
	%a = alloca i32
	store i32 %.a, i32* %a
	%numA  = alloca i32
	%_0 = load i32, i32* %a
	store i32 %_0, i32* %numA
	%_1 = load i32, i32* %numA
	%_2 = add i32 %_1, 10
	store i32 %_2, i32* %numA
	%_3 = load i32, i32* %numA
	call void (i32) @print_int(i32 %_3)
	; A.funA2 : 1
	%_4 = bitcast i8* %this to i8***
	%_5 = load i8**, i8*** %_4
	%_6 = getelementptr i8*, i8** %_5, i32 1
	%_7 = load i8*, i8** %_6
	%_8 = bitcast i8* %_7 to i32 (i8*)* 
	%_9 = call i32 %_8 ( i8* %this ) 
	store i32 %_9, i32* %numA
	%_10 = load i32, i32* %numA
	ret i32 %_10
}


define i32 @A.funA2(i8* %this) {
	%_1 = getelementptr i8, i8* %this, i32 8
	%_2 = bitcast i8* %_1 to i32*
	%_0 = load i32, i32* %_2
	%_3 = add i32 %_0, 1000
	%_4 = getelementptr i8, i8* %this, i32 8
	%_5 = bitcast i8* %_4 to i32* 
	store i32 %_3, i32* %_5
	%_7 = getelementptr i8, i8* %this, i32 8
	%_8 = bitcast i8* %_7 to i32*
	%_6 = load i32, i32* %_8
	ret i32 %_6
}


define i32 @B.funC(i8* %this) {
	%numB  = alloca i32
	; B.funOtherB : 4
	%_0 = bitcast i8* %this to i8***
	%_1 = load i8**, i8*** %_0
	%_2 = getelementptr i8*, i8** %_1, i32 4
	%_3 = load i8*, i8** %_2
	%_4 = bitcast i8* %_3 to i32 (i8*)* 
	%_5 = call i32 %_4 ( i8* %this ) 
	store i32 %_5, i32* %numB
	%_6 = load i32, i32* %numB
	call void (i32) @print_int(i32 %_6)
	%_7 = load i32, i32* %numB
	ret i32 %_7
}


define i32 @B.funB(i8* %this, i32 %.numA, i32 %.numB) {
	%numA = alloca i32
	store i32 %.numA, i32* %numA
	%numB = alloca i32
	store i32 %.numB, i32* %numB
	%_0 = load i32, i32* %numB
	%_1 = add i32 %_0, 200
	store i32 %_1, i32* %numB
	%_2 = load i32, i32* %numA
	%_3 = load i32, i32* %numB
	%_4 = add i32 %_2, %_3
	store i32 %_4, i32* %numB
	%_5 = load i32, i32* %numB
	call void (i32) @print_int(i32 %_5)
	%_6 = load i32, i32* %numB
	ret i32 %_6
}


define i32 @B.funOtherB(i8* %this) {
	%numA  = alloca i32
	store i32 500, i32* %numA
	%_0 = load i32, i32* %numA
	%_2 = getelementptr i8, i8* %this, i32 12
	%_3 = bitcast i8* %_2 to i32*
	%_1 = load i32, i32* %_3
	%_4 = add i32 %_0, %_1
	call void (i32) @print_int(i32 %_4)
	%_5 = load i32, i32* %numA
	ret i32 %_5
}


define i32 @C.funB(i8* %this, i32 %.numA, i32 %.numB) {
	%numA = alloca i32
	store i32 %.numA, i32* %numA
	%numB = alloca i32
	store i32 %.numB, i32* %numB
	%_0 = load i32, i32* %numB
	%_1 = add i32 %_0, 2000
	call void (i32) @print_int(i32 %_1)
	; C.funA : 0
	%_2 = bitcast i8* %this to i8***
	%_3 = load i8**, i8*** %_2
	%_4 = getelementptr i8*, i8** %_3, i32 0
	%_5 = load i8*, i8** %_4
	%_6 = bitcast i8* %_5 to i32 (i8*,i32)* 
	%_8 = getelementptr i8, i8* %this, i32 16
	%_9 = bitcast i8* %_8 to i32*
	%_7 = load i32, i32* %_9
	%_10 = call i32 %_6 ( i8* %this, i32 %_7 ) 
	ret i32 %_10
}

