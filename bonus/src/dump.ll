@.TreeVisitor_vtable = global [0 x i8*] [] 
@.TV_vtable = global [1 x i8*] [i8* bitcast (i32 (i8*)* @TV.Start to i8*)] 
@.Visitor_vtable = global [1 x i8*] [i8* bitcast (i32 (i8*,i8*)* @Visitor.visit to i8*)] 
@.Tree_vtable = global [21 x i8*] [i8* bitcast (i1 (i8*,i32)* @Tree.Init to i8*), i8* bitcast (i1 (i8*,i8*)* @Tree.SetRight to i8*), i8* bitcast (i1 (i8*,i8*)* @Tree.SetLeft to i8*), i8* bitcast (i8* (i8*)* @Tree.GetRight to i8*), i8* bitcast (i8* (i8*)* @Tree.GetLeft to i8*), i8* bitcast (i32 (i8*)* @Tree.GetKey to i8*), i8* bitcast (i1 (i8*,i32)* @Tree.SetKey to i8*), i8* bitcast (i1 (i8*)* @Tree.GetHas_Right to i8*), i8* bitcast (i1 (i8*)* @Tree.GetHas_Left to i8*), i8* bitcast (i1 (i8*,i1)* @Tree.SetHas_Left to i8*), i8* bitcast (i1 (i8*,i1)* @Tree.SetHas_Right to i8*), i8* bitcast (i1 (i8*,i32,i32)* @Tree.Compare to i8*), i8* bitcast (i1 (i8*,i32)* @Tree.Insert to i8*), i8* bitcast (i1 (i8*,i32)* @Tree.Delete to i8*), i8* bitcast (i1 (i8*,i8*,i8*)* @Tree.Remove to i8*), i8* bitcast (i1 (i8*,i8*,i8*)* @Tree.RemoveRight to i8*), i8* bitcast (i1 (i8*,i8*,i8*)* @Tree.RemoveLeft to i8*), i8* bitcast (i32 (i8*,i32)* @Tree.Search to i8*), i8* bitcast (i1 (i8*)* @Tree.Print to i8*), i8* bitcast (i1 (i8*,i8*)* @Tree.RecPrint to i8*), i8* bitcast (i32 (i8*,i8*)* @Tree.accept to i8*)] 
@.MyVisitor_vtable = global [1 x i8*] [i8* bitcast (i32 (i8*,i8*)* @MyVisitor.visit to i8*)] 

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

CALL
	BEGIN
MOVE TEMP %_0 
BEGIN 
MOVE TEMP %_3 HALLOCATE 4
MOVE TEMP %_4 HALLOCATE 4
HSTORE TEMP %_3 0 TV.Start 
HSTORE TEMP %_4 0 TEMP %_3
RETURN TEMP %_4
END
( TEMP %_0  ) 	call void (i32) @print_int(i32 null)
	ret i32 0
}

TV_Start [1]
BEGIN

MOVE TEMP 1 
BEGIN 
MOVE TEMP %_5 HALLOCATE 84
MOVE TEMP %_6 HALLOCATE 28
HSTORE TEMP %_5 80 Tree.accept 
HSTORE TEMP %_5 76 Tree.RecPrint 
HSTORE TEMP %_5 72 Tree.Print 
HSTORE TEMP %_5 68 Tree.Search 
HSTORE TEMP %_5 64 Tree.RemoveLeft 
HSTORE TEMP %_5 60 Tree.RemoveRight 
HSTORE TEMP %_5 56 Tree.Remove 
HSTORE TEMP %_5 52 Tree.Delete 
HSTORE TEMP %_5 48 Tree.Insert 
HSTORE TEMP %_5 44 Tree.Compare 
HSTORE TEMP %_5 40 Tree.SetHas_Right 
HSTORE TEMP %_5 36 Tree.SetHas_Left 
HSTORE TEMP %_5 32 Tree.GetHas_Left 
HSTORE TEMP %_5 28 Tree.GetHas_Right 
HSTORE TEMP %_5 24 Tree.SetKey 
HSTORE TEMP %_5 20 Tree.GetKey 
HSTORE TEMP %_5 16 Tree.GetLeft 
HSTORE TEMP %_5 12 Tree.GetRight 
HSTORE TEMP %_5 8 Tree.SetLeft 
HSTORE TEMP %_5 4 Tree.SetRight 
HSTORE TEMP %_5 0 Tree.Init 
MOVE TEMP %_7 4
_l58	CJUMP LE TEMP %_7 27 _l59 
HSTORE PLUS TEMP %_6 TEMP %_7 0 0 
MOVE TEMP %_7 PLUS TEMP %_7 4 
JUMP _l58
_l59	
HSTORE TEMP %_6 0 TEMP %_5
RETURN TEMP %_6
END

MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_8 ( TEMP %_8  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_11 ( TEMP %_11  ) 	call void (i32) @print_int(i32 100000000)

MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_17 ( TEMP %_17  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_20 ( TEMP %_20  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_23 ( TEMP %_23  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_26 ( TEMP %_26  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_29 ( TEMP %_29  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_32 ( TEMP %_32  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_35 ( TEMP %_35  ) 	call void (i32) @print_int(i32 100000000)

MOVE TEMP 4 
BEGIN 
MOVE TEMP %_38 HALLOCATE 4
MOVE TEMP %_39 HALLOCATE 12
HSTORE TEMP %_38 0 MyVisitor.visit 
MOVE TEMP %_40 4
_l60	CJUMP LE TEMP %_40 11 _l61 
HSTORE PLUS TEMP %_39 TEMP %_40 0 0 
MOVE TEMP %_40 PLUS TEMP %_40 4 
JUMP _l60
_l61	
HSTORE TEMP %_39 0 TEMP %_38
RETURN TEMP %_39
END
	call void (i32) @print_int(i32 50000000)

MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_41 ( TEMP %_41  ) 	call void (i32) @print_int(i32 100000000)

CALL
	BEGIN
MOVE TEMP %_44 ( TEMP %_44  ) 	call void (i32) @print_int(i32 null)

CALL
	BEGIN
MOVE TEMP %_47 ( TEMP %_47  ) 	call void (i32) @print_int(i32 null)

CALL
	BEGIN
MOVE TEMP %_50 ( TEMP %_50  ) 	call void (i32) @print_int(i32 null)

CALL
	BEGIN
MOVE TEMP %_53 ( TEMP %_53  ) 	call void (i32) @print_int(i32 null)

CALL
	BEGIN
MOVE TEMP %_56 ( TEMP %_56  ) 	call void (i32) @print_int(i32 null)

MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_59 ( TEMP %_59  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_62 ( TEMP %_62  ) 
CALL
	BEGIN
MOVE TEMP %_65 ( TEMP %_65  ) 	call void (i32) @print_int(i32 null)

RETURN 
END

Tree_Init [2]
BEGIN

HSTORE TEMP 0 12 
HSTORE TEMP 0 16 
HSTORE TEMP 0 20 
RETURN 
END

Tree_SetRight [2]
BEGIN

HSTORE TEMP 0 8 
RETURN 
END

Tree_SetLeft [2]
BEGIN

HSTORE TEMP 0 4 
RETURN 
END

Tree_GetRight [1]
BEGIN

RETURN 
END

Tree_GetLeft [1]
BEGIN

RETURN 
END

Tree_GetKey [1]
BEGIN

RETURN 
END

Tree_SetKey [2]
BEGIN

HSTORE TEMP 0 12 
RETURN 
END

Tree_GetHas_Right [1]
BEGIN

RETURN 
END

Tree_GetHas_Left [1]
BEGIN

RETURN 
END

Tree_SetHas_Left [2]
BEGIN

HSTORE TEMP 0 16 
RETURN 
END

Tree_SetHas_Right [2]
BEGIN

HSTORE TEMP 0 20 
RETURN 
END

Tree_Compare [3]
BEGIN

MOVE TEMP 3 
MOVE TEMP 4 	%_0 = num2
	%_1 = 1
	%_2 = add i32 %_0, %_1

MOVE TEMP %_3 	%_4 = num1
	%_5 = num2
	%_6 = icmp sle i32 %_4, %_5
	%_7 = num1
	%_8 = num2
	%_9 = icmp ne i32 %_7, %_8
	%_10 = null
	%_11 = null
	%_12 = and i1 %_10, %_11

CJUMP TEMP %_3 _l62 
MOVE TEMP 3 
JUMP _l63 
_l62	
MOVE TEMP %_13 	%_14 = nti
	%_15 = 1
	%_16 = sub i32 %_14, %_15
	%_17 = num1
	%_18 = %_16
	%_19 = icmp sle i32 %_17, %_18
	%_20 = xor i1 null, 1

CJUMP TEMP %_13 _l64 
MOVE TEMP 3 
JUMP _l65 
_l64	
MOVE TEMP 3 
_l65    NOOP 

_l63    NOOP 

RETURN 
END

Tree_Insert [2]
BEGIN

MOVE TEMP 2 
BEGIN 
MOVE TEMP %_0 HALLOCATE 84
MOVE TEMP %_1 HALLOCATE 28
HSTORE TEMP %_0 80 Tree.accept 
HSTORE TEMP %_0 76 Tree.RecPrint 
HSTORE TEMP %_0 72 Tree.Print 
HSTORE TEMP %_0 68 Tree.Search 
HSTORE TEMP %_0 64 Tree.RemoveLeft 
HSTORE TEMP %_0 60 Tree.RemoveRight 
HSTORE TEMP %_0 56 Tree.Remove 
HSTORE TEMP %_0 52 Tree.Delete 
HSTORE TEMP %_0 48 Tree.Insert 
HSTORE TEMP %_0 44 Tree.Compare 
HSTORE TEMP %_0 40 Tree.SetHas_Right 
HSTORE TEMP %_0 36 Tree.SetHas_Left 
HSTORE TEMP %_0 32 Tree.GetHas_Left 
HSTORE TEMP %_0 28 Tree.GetHas_Right 
HSTORE TEMP %_0 24 Tree.SetKey 
HSTORE TEMP %_0 20 Tree.GetKey 
HSTORE TEMP %_0 16 Tree.GetLeft 
HSTORE TEMP %_0 12 Tree.GetRight 
HSTORE TEMP %_0 8 Tree.SetLeft 
HSTORE TEMP %_0 4 Tree.SetRight 
HSTORE TEMP %_0 0 Tree.Init 
MOVE TEMP %_2 4
_l66	CJUMP LE TEMP %_2 27 _l67 
HSTORE PLUS TEMP %_1 TEMP %_2 0 0 
MOVE TEMP %_2 PLUS TEMP %_2 4 
JUMP _l66
_l67	
HSTORE TEMP %_1 0 TEMP %_0
RETURN TEMP %_1
END

MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_3 ( TEMP %_3  ) 
MOVE TEMP 4 
MOVE TEMP 5 
_l68 NOOP 
CJUMP  	_l69 
MOVE TEMP 6 
CALL
	BEGIN
MOVE TEMP %_6 ( TEMP %_6  ) 
MOVE TEMP %_9 	%_10 = key_aux
	%_11 = 1
	%_12 = sub i32 %_10, %_11
	%_13 = v_key
	%_14 = %_12
	%_15 = icmp sle i32 %_13, %_14

CJUMP TEMP %_9 _l70 
MOVE TEMP %_16 
CALL
	BEGIN
MOVE TEMP %_17 ( TEMP %_17  ) 
CJUMP TEMP %_16 _l72 
MOVE TEMP 4 
CALL
	BEGIN
MOVE TEMP %_20 ( TEMP %_20  ) 
JUMP _l73 
_l72	
MOVE TEMP 5 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_23 ( TEMP %_23  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_26 ( TEMP %_26  ) 
_l73    NOOP 

JUMP _l71 
_l70	
MOVE TEMP %_29 
CALL
	BEGIN
MOVE TEMP %_30 ( TEMP %_30  ) 
CJUMP TEMP %_29 _l74 
MOVE TEMP 4 
CALL
	BEGIN
MOVE TEMP %_33 ( TEMP %_33  ) 
JUMP _l75 
_l74	
MOVE TEMP 5 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_36 ( TEMP %_36  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_39 ( TEMP %_39  ) 
_l75    NOOP 

_l71    NOOP 

JUMP _l68 
_l69 NOOP 
RETURN 
END

Tree_Delete [2]
BEGIN

MOVE TEMP 2 
MOVE TEMP 3 
MOVE TEMP 4 
MOVE TEMP 5 
MOVE TEMP 7 
_l76 NOOP 
CJUMP  	_l77 
MOVE TEMP 8 
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 
MOVE TEMP %_3 	%_4 = key_aux
	%_5 = 1
	%_6 = sub i32 %_4, %_5
	%_7 = v_key
	%_8 = %_6
	%_9 = icmp sle i32 %_7, %_8

CJUMP TEMP %_3 _l78 
MOVE TEMP %_10 
CALL
	BEGIN
MOVE TEMP %_11 ( TEMP %_11  ) 
CJUMP TEMP %_10 _l80 
MOVE TEMP 3 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
JUMP _l81 
_l80	
MOVE TEMP 4 
_l81    NOOP 

JUMP _l79 
_l78	
MOVE TEMP %_17 	%_18 = key_aux
	%_19 = v_key
	%_20 = icmp sle i32 %_18, %_19
	%_21 = key_aux
	%_22 = v_key
	%_23 = icmp ne i1 %_21, %_22
	%_24 = null
	%_25 = null
	%_26 = and i1 %_24, %_25

CJUMP TEMP %_17 _l82 
MOVE TEMP %_27 
CALL
	BEGIN
MOVE TEMP %_28 ( TEMP %_28  ) 
CJUMP TEMP %_27 _l84 
MOVE TEMP 3 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_31 ( TEMP %_31  ) 
JUMP _l85 
_l84	
MOVE TEMP 4 
_l85    NOOP 

JUMP _l83 
_l82	
MOVE TEMP %_34 
CJUMP TEMP %_34 _l86 
MOVE TEMP %_35 
CALL
	BEGIN
MOVE TEMP %_36 ( TEMP %_36  ) 	%_39 = xor i1 null, 1

CALL
	BEGIN
MOVE TEMP %_40 ( TEMP %_40  ) 	%_43 = xor i1 null, 1
	%_44 = %_39
	%_45 = %_43
	%_46 = and i1 %_44, %_45

CJUMP TEMP %_35 _l88 
MOVE TEMP 6 
JUMP _l89 
_l88	
MOVE TEMP 6 
CALL
	BEGIN
MOVE TEMP %_47 ( TEMP %_47  ) 
_l89    NOOP 

JUMP _l87 
_l86	
MOVE TEMP 6 
CALL
	BEGIN
MOVE TEMP %_50 ( TEMP %_50  ) 
_l87    NOOP 

MOVE TEMP 5 
MOVE TEMP 4 
_l83    NOOP 

_l79    NOOP 

MOVE TEMP 7 
JUMP _l76 
_l77 NOOP 
RETURN 
END

Tree_Remove [3]
BEGIN

MOVE TEMP %_0 
CALL
	BEGIN
MOVE TEMP %_1 ( TEMP %_1  ) 
CJUMP TEMP %_0 _l90 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_4 ( TEMP %_4  ) 
JUMP _l91 
_l90	
MOVE TEMP %_7 
CALL
	BEGIN
MOVE TEMP %_8 ( TEMP %_8  ) 
CJUMP TEMP %_7 _l92 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_11 ( TEMP %_11  ) 
JUMP _l93 
_l92	
MOVE TEMP 4 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
MOVE TEMP 5 
CALL
	BEGIN
MOVE TEMP %_17 
CALL
	BEGIN
MOVE TEMP %_20 ( TEMP %_20  ) ( TEMP %_17  ) 
MOVE TEMP %_23 
CALL
	BEGIN
MOVE TEMP %_24 ( TEMP %_24  ) 
CJUMP TEMP %_23 _l94 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_27 ( TEMP %_27  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_30 ( TEMP %_30  ) 
JUMP _l95 
_l94	
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_33 ( TEMP %_33  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_36 ( TEMP %_36  ) 
_l95    NOOP 

_l93    NOOP 

_l91    NOOP 

RETURN 
END

Tree_RemoveRight [3]
BEGIN

_l96 NOOP 
CJUMP  
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 	_l97 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_3 ( TEMP %_3 
CALL
	BEGIN
MOVE TEMP %_6 
CALL
	BEGIN
MOVE TEMP %_9 ( TEMP %_9  ) ( TEMP %_6  )  ) 
MOVE TEMP 1 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_12 ( TEMP %_12  ) 
JUMP _l96 
_l97 NOOP 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_15 ( TEMP %_15  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_18 ( TEMP %_18  ) 
RETURN 
END

Tree_RemoveLeft [3]
BEGIN

_l98 NOOP 
CJUMP  
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 	_l99 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_3 ( TEMP %_3 
CALL
	BEGIN
MOVE TEMP %_6 
CALL
	BEGIN
MOVE TEMP %_9 ( TEMP %_9  ) ( TEMP %_6  )  ) 
MOVE TEMP 1 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_12 ( TEMP %_12  ) 
JUMP _l98 
_l99 NOOP 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_15 ( TEMP %_15  ) 
MOVE TEMP 3 
CALL
	BEGIN
MOVE TEMP %_18 ( TEMP %_18  ) 
RETURN 
END

Tree_Search [2]
BEGIN

MOVE TEMP 2 
MOVE TEMP 4 
MOVE TEMP 3 
_l100 NOOP 
CJUMP  	_l101 
MOVE TEMP 5 
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 
MOVE TEMP %_3 	%_4 = key_aux
	%_5 = 1
	%_6 = sub i32 %_4, %_5
	%_7 = v_key
	%_8 = %_6
	%_9 = icmp sle i32 %_7, %_8

CJUMP TEMP %_3 _l102 
MOVE TEMP %_10 
CALL
	BEGIN
MOVE TEMP %_11 ( TEMP %_11  ) 
CJUMP TEMP %_10 _l104 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
JUMP _l105 
_l104	
MOVE TEMP 4 
_l105    NOOP 

JUMP _l103 
_l102	
MOVE TEMP %_17 	%_18 = v_key
	%_19 = 1
	%_20 = sub i32 %_18, %_19
	%_21 = key_aux
	%_22 = %_20
	%_23 = icmp sle i32 %_21, %_22

CJUMP TEMP %_17 _l106 
MOVE TEMP %_24 
CALL
	BEGIN
MOVE TEMP %_25 ( TEMP %_25  ) 
CJUMP TEMP %_24 _l108 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_28 ( TEMP %_28  ) 
JUMP _l109 
_l108	
MOVE TEMP 4 
_l109    NOOP 

JUMP _l107 
_l106	
MOVE TEMP 3 
MOVE TEMP 4 
_l107    NOOP 

_l103    NOOP 

JUMP _l100 
_l101 NOOP 
RETURN 
END

Tree_Print [1]
BEGIN

MOVE TEMP 2 
MOVE TEMP 1 
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 
RETURN 
END

Tree_RecPrint [2]
BEGIN

MOVE TEMP %_0 
CALL
	BEGIN
MOVE TEMP %_1 ( TEMP %_1  ) 
CJUMP TEMP %_0 _l110 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_4 ( TEMP %_4 
CALL
	BEGIN
MOVE TEMP %_7 ( TEMP %_7  )  ) 
JUMP _l111 
_l110	
MOVE TEMP 2 
_l111    NOOP 

CALL
	BEGIN
MOVE TEMP %_10 ( TEMP %_10  ) 	call void (i32) @print_int(i32 null)

MOVE TEMP %_13 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
CJUMP TEMP %_13 _l112 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_17 ( TEMP %_17 
CALL
	BEGIN
MOVE TEMP %_20 ( TEMP %_20  )  ) 
JUMP _l113 
_l112	
MOVE TEMP 2 
_l113    NOOP 

RETURN 
END

Tree_accept [2]
BEGIN
	call void (i32) @print_int(i32 333)

MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_0 ( TEMP %_0  ) 
RETURN 
END

Visitor_visit [2]
BEGIN

MOVE TEMP %_0 
CALL
	BEGIN
MOVE TEMP %_1 ( TEMP %_1  ) 
CJUMP TEMP %_0 _l114 
HSTORE TEMP 0 8 
CALL
	BEGIN
MOVE TEMP %_4 ( TEMP %_4  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_7 ( TEMP %_7  ) 
JUMP _l115 
_l114	
MOVE TEMP 2 
_l115    NOOP 

MOVE TEMP %_10 
CALL
	BEGIN
MOVE TEMP %_11 ( TEMP %_11  ) 
CJUMP TEMP %_10 _l116 
HSTORE TEMP 0 4 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_17 ( TEMP %_17  ) 
JUMP _l117 
_l116	
MOVE TEMP 2 
_l117    NOOP 

RETURN 
END

MyVisitor_visit [2]
BEGIN

MOVE TEMP %_0 
CALL
	BEGIN
MOVE TEMP %_1 ( TEMP %_1  ) 
CJUMP TEMP %_0 _l118 
HSTORE TEMP 0 8 
CALL
	BEGIN
MOVE TEMP %_4 ( TEMP %_4  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_7 ( TEMP %_7  ) 
JUMP _l119 
_l118	
MOVE TEMP 2 
_l119    NOOP 

CALL
	BEGIN
MOVE TEMP %_10 ( TEMP %_10  ) 	call void (i32) @print_int(i32 null)

MOVE TEMP %_13 
CALL
	BEGIN
MOVE TEMP %_14 ( TEMP %_14  ) 
CJUMP TEMP %_13 _l120 
HSTORE TEMP 0 4 
CALL
	BEGIN
MOVE TEMP %_17 ( TEMP %_17  ) 
MOVE TEMP 2 
CALL
	BEGIN
MOVE TEMP %_20 ( TEMP %_20  ) 
JUMP _l121 
_l120	
MOVE TEMP 2 
_l121    NOOP 

RETURN 
END
