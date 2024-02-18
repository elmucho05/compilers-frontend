declare double @randinit(double)

declare double @randk()

declare double @timek()

declare double @printval(double, double)

@A = common global [10 x double] zeroinitializer
define double @inssort() {
entry:
  %j = alloca double, align 8
  %step = alloca double, align 8
  %pivot = alloca double, align 8
  %i = alloca double, align 8
  store double 1.000000e+00, ptr %i, align 8
  br label %condeval

condeval:                                         ; preds = %endcond29, %entry
  %i1 = load double, ptr %i, align 8
  %lttest = fcmp ult double %i1, 1.000000e+01
  br i1 %lttest, label %forloop, label %endloop32

forloop:                                          ; preds = %condeval
  %i2 = load double, ptr %i, align 8
  %indexinitalize = fptosi double %i2 to i32
  %0 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize
  %A = load double, ptr %0, align 8
  store double %A, ptr %pivot, align 8
  store double 1.000000e+00, ptr %step, align 8
  %i3 = load double, ptr %i, align 8
  %subres = fsub double %i3, 1.000000e+00
  store double %subres, ptr %j, align 8
  br label %condeval4

condeval4:                                        ; preds = %endcond, %forloop
  %j5 = load double, ptr %j, align 8
  %lttest6 = fcmp ult double -1.000000e+00, %j5
  br i1 %lttest6, label %forloop7, label %endloop

forloop7:                                         ; preds = %condeval4
  %pivot8 = load double, ptr %pivot, align 8
  %j9 = load double, ptr %j, align 8
  %indexinitalize10 = fptosi double %j9 to i32
  %1 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize10
  %A11 = load double, ptr %1, align 8
  %lttest12 = fcmp ult double %pivot8, %A11
  br i1 %lttest12, label %trueexp, label %falseexp

trueexp:                                          ; preds = %forloop7
  %j13 = load double, ptr %j, align 8
  %addres = fadd double %j13, 1.000000e+00
  %intindex = fptosi double %addres to i32
  %j14 = load double, ptr %j, align 8
  %indexinitalize15 = fptosi double %j14 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize15
  %A16 = load double, ptr %2, align 8
  %3 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %intindex
  store double %A16, ptr %3, align 8
  %ret_A = load double, ptr %3, align 8
  br label %endcond

falseexp:                                         ; preds = %forloop7
  %j17 = load double, ptr %j, align 8
  %addres18 = fadd double %j17, 1.000000e+00
  %intindex19 = fptosi double %addres18 to i32
  %pivot20 = load double, ptr %pivot, align 8
  %4 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %intindex19
  store double %pivot20, ptr %4, align 8
  %ret_A21 = load double, ptr %4, align 8
  store double 1.000000e+01, ptr %step, align 8
  %ret_step = load double, ptr %step, align 8
  br label %endcond

endcond:                                          ; preds = %falseexp, %trueexp
  %condval = phi double [ %ret_A, %trueexp ], [ %ret_step, %falseexp ]
  %j22 = load double, ptr %j, align 8
  %step23 = load double, ptr %step, align 8
  %subres24 = fsub double %j22, %step23
  store double %subres24, ptr %j, align 8
  %ret_j = load double, ptr %j, align 8
  br label %condeval4

endloop:                                          ; preds = %condeval4
  %step25 = load double, ptr %step, align 8
  %eqtest = fcmp ueq double %step25, 1.000000e+00
  br i1 %eqtest, label %trueexp26, label %endcond29

trueexp26:                                        ; preds = %endloop
  %pivot27 = load double, ptr %pivot, align 8
  store double %pivot27, ptr @A, align 8
  %ret_A28 = load double, ptr @A, align 8
  br label %endcond29

endcond29:                                        ; preds = %trueexp26, %endloop
  %i30 = load double, ptr %i, align 8
  %addres31 = fadd double %i30, 1.000000e+00
  store double %addres31, ptr %i, align 8
  %ret_i = load double, ptr %i, align 8
  br label %condeval

endloop32:                                        ; preds = %condeval
  ret double 0.000000e+00
}

define double @main() {
entry:
  %i11 = alloca double, align 8
  %i = alloca double, align 8
  %seed = alloca double, align 8
  %calltmp = call double @timek()
  store double %calltmp, ptr %seed, align 8
  %seed1 = load double, ptr %seed, align 8
  %calltmp2 = call double @randinit(double %seed1)
  store double 0.000000e+00, ptr %i, align 8
  br label %condeval

condeval:                                         ; preds = %forloop, %entry
  %i3 = load double, ptr %i, align 8
  %lttest = fcmp ult double %i3, 1.000000e+01
  br i1 %lttest, label %forloop, label %endloop

forloop:                                          ; preds = %condeval
  %i4 = load double, ptr %i, align 8
  %intindex = fptosi double %i4 to i32
  %calltmp5 = call double @randk()
  %0 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %intindex
  store double %calltmp5, ptr %0, align 8
  %ret_A = load double, ptr %0, align 8
  %i6 = load double, ptr %i, align 8
  %indexinitalize = fptosi double %i6 to i32
  %1 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize
  %A = load double, ptr %1, align 8
  %calltmp7 = call double @printval(double %A, double 0.000000e+00)
  %i8 = load double, ptr %i, align 8
  %addres = fadd double %i8, 1.000000e+00
  store double %addres, ptr %i, align 8
  %ret_i = load double, ptr %i, align 8
  br label %condeval

endloop:                                          ; preds = %condeval
  %calltmp9 = call double @printval(double 0.000000e+00, double 1.000000e+00)
  %calltmp10 = call double @inssort()
  store double 0.000000e+00, ptr %i11, align 8
  br label %condeval12

condeval12:                                       ; preds = %forloop15, %endloop
  %i13 = load double, ptr %i11, align 8
  %lttest14 = fcmp ult double %i13, 1.000000e+01
  br i1 %lttest14, label %forloop15, label %endloop23

forloop15:                                        ; preds = %condeval12
  %i16 = load double, ptr %i11, align 8
  %indexinitalize17 = fptosi double %i16 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize17
  %A18 = load double, ptr %2, align 8
  %calltmp19 = call double @printval(double %A18, double 0.000000e+00)
  %i20 = load double, ptr %i11, align 8
  %addres21 = fadd double %i20, 1.000000e+00
  store double %addres21, ptr %i11, align 8
  %ret_i22 = load double, ptr %i11, align 8
  br label %condeval12

endloop23:                                        ; preds = %condeval12
  ret double 0.000000e+00
}

