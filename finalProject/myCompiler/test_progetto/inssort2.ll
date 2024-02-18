declare double @randinit(double)

declare double @randk()

declare double @timek()

declare double @printval(double, double)

@A = common global [10 x double] zeroinitializer
define double @inssort() {
entry:
  %j = alloca double, align 8
  %pivot = alloca double, align 8
  %i = alloca double, align 8
  store double 1.000000e+00, ptr %i, align 8
  br label %condeval

condeval:                                         ; preds = %endloop, %entry
  %i1 = load double, ptr %i, align 8
  %lttest = fcmp ult double %i1, 1.000000e+01
  br i1 %lttest, label %forloop, label %endloop27

forloop:                                          ; preds = %condeval
  %i2 = load double, ptr %i, align 8
  %indexinitalize = fptosi double %i2 to i32
  %0 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize
  %A = load double, ptr %0, align 8
  store double %A, ptr %pivot, align 8
  store double 0.000000e+00, ptr %j, align 8
  %i3 = load double, ptr %i, align 8
  %subres = fsub double %i3, 1.000000e+00
  store double %subres, ptr %j, align 8
  %ret_j = load double, ptr %j, align 8
  br label %condeval4

condeval4:                                        ; preds = %forloop12, %forloop
  %j5 = load double, ptr %j, align 8
  %lttest6 = fcmp ult double -1.000000e+00, %j5
  %pivot7 = load double, ptr %pivot, align 8
  %j8 = load double, ptr %j, align 8
  %indexinitalize9 = fptosi double %j8 to i32
  %1 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %indexinitalize9
  %A10 = load double, ptr %1, align 8
  %lttest11 = fcmp ult double %pivot7, %A10
  %andres = and i1 %lttest6, %lttest11
  br i1 %andres, label %forloop12, label %endloop

forloop12:                                        ; preds = %condeval4
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
  %j17 = load double, ptr %j, align 8
  %subres18 = fsub double %j17, 1.000000e+00
  store double %subres18, ptr %j, align 8
  %ret_j19 = load double, ptr %j, align 8
  br label %condeval4

endloop:                                          ; preds = %condeval4
  %j20 = load double, ptr %j, align 8
  %addres21 = fadd double %j20, 1.000000e+00
  %intindex22 = fptosi double %addres21 to i32
  %pivot23 = load double, ptr %pivot, align 8
  %4 = getelementptr inbounds [10 x double], ptr @A, i32 0, i32 %intindex22
  store double %pivot23, ptr %4, align 8
  %ret_A24 = load double, ptr %4, align 8
  %i25 = load double, ptr %i, align 8
  %addres26 = fadd double %i25, 1.000000e+00
  store double %addres26, ptr %i, align 8
  %ret_i = load double, ptr %i, align 8
  br label %condeval

endloop27:                                        ; preds = %condeval
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

