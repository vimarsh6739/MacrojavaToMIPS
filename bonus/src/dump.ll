@.A_vtable = global [2 x i8*] [i8* bitcast (i32 (i8*,i32,i32)* @A.add to i8*), i8* bitcast (i32 (i8*,i32,i32)* @A.sub to i8*)] 
@.B_vtable = global [3 x i8*] [i8* bitcast (i32 (i8*,i32,i32)* @A.add to i8*), i8* bitcast (i32 (i8*,i32,i32)* @A.sub to i8*), i8* bitcast (i1 (i8*,i32,i32)* @B.multi to i8*)] 
@.T14_vtable = global [0 x i8*] [] 

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
	%_0 = call i8* @calloc(i32 1, i32 12)
	%_1 = bitcast i8* %_0 to i8***
	%_2 = getelementptr [3 x i8*], [3 x i8*]* @.B_vtable, i32 0, i32 0
	store i8** %_2, i8*** %_1
	; B.multi : 2
	%_3 = bitcast i8* %_0 to i8***
	%_4 = load i8**, i8*** %_3
	%_5 = getelementptr i8*, i8** %_4, i32 2
	%_6 = load i8*, i8** %_5
	%_7 = bitcast i8* %_6 to i1 (i8*,i32,i32)* 
	%_8 = call i1 %_7 ( i8* %_0, i32 5, i32 10 ) 
	%_9 =zext i1 %_8 to i32 
	call void (i32) @print_int(i32 %_9)
	ret i32 0
}


define i32 @A.add(i8* %this, i32 %.x, i32 %.y) {
	%x = alloca i32
	store i32 %.x, i32* %x
	%y = alloca i32
	store i32 %.y, i32* %y
	%_0 = load i32, i32* %x
	%_1 = load i32, i32* %y
	%_2 = add i32 %_0, %_1
	%_3 = getelementptr i8, i8* %this, i32 8
	%_4 = bitcast i8* %_3 to i32* 
	store i32 %_2, i32* %_4
	%_6 = getelementptr i8, i8* %this, i32 8
	%_7 = bitcast i8* %_6 to i32*
	%_5 = load i32, i32* %_7
	call void (i32) @print_int(i32 %_5)
	%_9 = getelementptr i8, i8* %this, i32 8
	%_10 = bitcast i8* %_9 to i32*
	%_8 = load i32, i32* %_10
	ret i32 %_8
}


define i32 @A.sub(i8* %this, i32 %.x, i32 %.y) {
	%x = alloca i32
	store i32 %.x, i32* %x
	%y = alloca i32
	store i32 %.y, i32* %y
	%_0 = load i32, i32* %x
	%_1 = load i32, i32* %y
	%_2 = sub i32 %_0, %_1
	%_3 = getelementptr i8, i8* %this, i32 8
	%_4 = bitcast i8* %_3 to i32* 
	store i32 %_2, i32* %_4
	%_6 = getelementptr i8, i8* %this, i32 8
	%_7 = bitcast i8* %_6 to i32*
	%_5 = load i32, i32* %_7
	call void (i32) @print_int(i32 %_5)
	%_9 = getelementptr i8, i8* %this, i32 8
	%_10 = bitcast i8* %_9 to i32*
	%_8 = load i32, i32* %_10
	ret i32 %_8
}


define i1 @B.multi(i8* %this, i32 %.x, i32 %.y) {
	%x = alloca i32
	store i32 %.x, i32* %x
	%y = alloca i32
	store i32 %.y, i32* %y
	%_0 = load i32, i32* %x
	%_1 = load i32, i32* %y
	%_2 = mul i32 %_0, %_1
	%_3 = getelementptr i8, i8* %this, i32 8
	%_4 = bitcast i8* %_3 to i32* 
	store i32 %_2, i32* %_4
	%_6 = getelementptr i8, i8* %this, i32 8
	%_7 = bitcast i8* %_6 to i32*
	%_5 = load i32, i32* %_7
	call void (i32) @print_int(i32 %_5)
	; B.add : 0
	%_8 = bitcast i8* %this to i8***
	%_9 = load i8**, i8*** %_8
	%_10 = getelementptr i8*, i8** %_9, i32 0
	%_11 = load i8*, i8** %_10
	%_12 = bitcast i8* %_11 to i32 (i8*,i32,i32)* 
	%_13 = load i32, i32* %x
	%_14 = load i32, i32* %y
	%_15 = call i32 %_12 ( i8* %this, i32 %_13, i32 %_14 ) 
	%_16 = getelementptr i8, i8* %this, i32 8
	%_17 = bitcast i8* %_16 to i32* 
	store i32 %_15, i32* %_17
	; B.sub : 1
	%_18 = bitcast i8* %this to i8***
	%_19 = load i8**, i8*** %_18
	%_20 = getelementptr i8*, i8** %_19, i32 1
	%_21 = load i8*, i8** %_20
	%_22 = bitcast i8* %_21 to i32 (i8*,i32,i32)* 
	%_23 = load i32, i32* %x
	%_24 = load i32, i32* %y
	%_25 = call i32 %_22 ( i8* %this, i32 %_23, i32 %_24 ) 
	%_26 = getelementptr i8, i8* %this, i32 8
	%_27 = bitcast i8* %_26 to i32* 
	store i32 %_25, i32* %_27
	ret i1 1
}

