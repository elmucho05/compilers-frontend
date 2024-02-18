define double @iterate(double %y, double %x) {
entry:
  %z = alloca double, align 8
  %eps = alloca double, align 8
  %x2 = alloca double, align 8
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  store double %x, ptr %x2, align 8
  store double 1.000000e-04, ptr %eps, align 8
  %x3 = load double, ptr %x2, align 8
  %x4 = load double, ptr %x2, align 8
  %mulres = fmul double %x3, %x4
  store double %mulres, ptr %z, align 8
  br label %condeval

condeval:                                         ; preds = %forloop, %entry
  %z5 = load double, ptr %z, align 8
  %y6 = load double, ptr %y1, align 8
  %subres = fsub double %z5, %y6
  %eps7 = load double, ptr %eps, align 8
  %lttest = fcmp ult double %subres, %eps7
  %y8 = load double, ptr %y1, align 8
  %z9 = load double, ptr %z, align 8
  %subres10 = fsub double %y8, %z9
  %eps11 = load double, ptr %eps, align 8
  %lttest12 = fcmp ult double %subres10, %eps11
  %andres = and i1 %lttest, %lttest12
  %notres = xor i1 %andres, true
  br i1 %notres, label %forloop, label %endloop

forloop:                                          ; preds = %condeval
  %x13 = load double, ptr %x2, align 8
  %x14 = load double, ptr %x2, align 8
  %mulres15 = fmul double %x13, %x14
  store double %mulres15, ptr %z, align 8
  %ret_z = load double, ptr %z, align 8
  %x16 = load double, ptr %x2, align 8
  %y17 = load double, ptr %y1, align 8
  %x18 = load double, ptr %x2, align 8
  %addres = fdiv double %y17, %x18
  %addres19 = fadd double %x16, %addres
  %addres20 = fdiv double %addres19, 2.000000e+00
  store double %addres20, ptr %x2, align 8
  %ret_x = load double, ptr %x2, align 8
  br label %condeval

endloop:                                          ; preds = %condeval
  %x21 = load double, ptr %x2, align 8
  ret double %x21
}

define double @sqrt(double %y) {
entry:
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  %y2 = load double, ptr %y1, align 8
  %eqtest = fcmp ueq double %y2, 1.000000e+00
  br i1 %eqtest, label %trueexp, label %falseexp

trueexp:                                          ; preds = %entry
  br label %endcond11

falseexp:                                         ; preds = %entry
  %y3 = load double, ptr %y1, align 8
  %lttest = fcmp ult double %y3, 1.000000e+00
  br i1 %lttest, label %trueexp4, label %falseexp7

trueexp4:                                         ; preds = %falseexp
  %y5 = load double, ptr %y1, align 8
  %y6 = load double, ptr %y1, align 8
  %subres = fsub double 1.000000e+00, %y6
  %calltmp = call double @iterate(double %y5, double %subres)
  br label %endcond

falseexp7:                                        ; preds = %falseexp
  %y8 = load double, ptr %y1, align 8
  %y9 = load double, ptr %y1, align 8
  %addres = fdiv double %y9, 2.000000e+00
  %calltmp10 = call double @iterate(double %y8, double %addres)
  br label %endcond

endcond:                                          ; preds = %falseexp7, %trueexp4
  %condval = phi double [ %calltmp, %trueexp4 ], [ %calltmp10, %falseexp7 ]
  br label %endcond11

endcond11:                                        ; preds = %endcond, %trueexp
  %condval12 = phi double [ 1.000000e+00, %trueexp ], [ %condval, %endcond ]
  ret double %condval12
}

