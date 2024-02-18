declare double @sqrt(double)

declare double @printval(double, double, double)

define double @eqn2(double %a, double %b, double %c) {
entry:
  %x2 = alloca double, align 8
  %x1 = alloca double, align 8
  %delta36 = alloca double, align 8
  %x12 = alloca double, align 8
  %im = alloca double, align 8
  %re = alloca double, align 8
  %delta = alloca double, align 8
  %delta2 = alloca double, align 8
  %c3 = alloca double, align 8
  %b2 = alloca double, align 8
  %a1 = alloca double, align 8
  store double %a, ptr %a1, align 8
  store double %b, ptr %b2, align 8
  store double %c, ptr %c3, align 8
  %b4 = load double, ptr %b2, align 8
  %b5 = load double, ptr %b2, align 8
  %mulres = fmul double %b4, %b5
  %a6 = load double, ptr %a1, align 8
  %mulres7 = fmul double 4.000000e+00, %a6
  %c8 = load double, ptr %c3, align 8
  %mulres9 = fmul double %mulres7, %c8
  %subres = fsub double %mulres, %mulres9
  store double %subres, ptr %delta2, align 8
  %delta210 = load double, ptr %delta2, align 8
  %lttest = fcmp ult double %delta210, 0.000000e+00
  br i1 %lttest, label %trueexp, label %falseexp

trueexp:                                          ; preds = %entry
  %delta211 = load double, ptr %delta2, align 8
  %subres12 = fsub double 0.000000e+00, %delta211
  %calltmp = call double @sqrt(double %subres12)
  store double %calltmp, ptr %delta, align 8
  %b13 = load double, ptr %b2, align 8
  %subres14 = fsub double 0.000000e+00, %b13
  %a15 = load double, ptr %a1, align 8
  %mulres16 = fmul double 2.000000e+00, %a15
  %addres = fdiv double %subres14, %mulres16
  store double %addres, ptr %re, align 8
  %delta17 = load double, ptr %delta, align 8
  %a18 = load double, ptr %a1, align 8
  %mulres19 = fmul double 2.000000e+00, %a18
  %addres20 = fdiv double %delta17, %mulres19
  store double %addres20, ptr %im, align 8
  %re21 = load double, ptr %re, align 8
  %im22 = load double, ptr %im, align 8
  %calltmp23 = call double @printval(double %re21, double %im22, double 0.000000e+00)
  br label %endcond54

falseexp:                                         ; preds = %entry
  %delta224 = load double, ptr %delta2, align 8
  %eqtest = fcmp ueq double %delta224, 0.000000e+00
  br i1 %eqtest, label %trueexp25, label %falseexp33

trueexp25:                                        ; preds = %falseexp
  %b26 = load double, ptr %b2, align 8
  %subres27 = fsub double 0.000000e+00, %b26
  %a28 = load double, ptr %a1, align 8
  %mulres29 = fmul double 2.000000e+00, %a28
  %addres30 = fdiv double %subres27, %mulres29
  store double %addres30, ptr %x12, align 8
  %x1231 = load double, ptr %x12, align 8
  %calltmp32 = call double @printval(double %x1231, double 0.000000e+00, double 0.000000e+00)
  br label %endcond

falseexp33:                                       ; preds = %falseexp
  %delta234 = load double, ptr %delta2, align 8
  %calltmp35 = call double @sqrt(double %delta234)
  store double %calltmp35, ptr %delta36, align 8
  %b37 = load double, ptr %b2, align 8
  %subres38 = fsub double 0.000000e+00, %b37
  %delta39 = load double, ptr %delta36, align 8
  %addres40 = fadd double %subres38, %delta39
  %a41 = load double, ptr %a1, align 8
  %mulres42 = fmul double 2.000000e+00, %a41
  %addres43 = fdiv double %addres40, %mulres42
  store double %addres43, ptr %x1, align 8
  %b44 = load double, ptr %b2, align 8
  %subres45 = fsub double 0.000000e+00, %b44
  %delta46 = load double, ptr %delta36, align 8
  %subres47 = fsub double %subres45, %delta46
  %a48 = load double, ptr %a1, align 8
  %mulres49 = fmul double 2.000000e+00, %a48
  %addres50 = fdiv double %subres47, %mulres49
  store double %addres50, ptr %x2, align 8
  %x151 = load double, ptr %x1, align 8
  %x252 = load double, ptr %x2, align 8
  %calltmp53 = call double @printval(double %x151, double %x252, double 1.000000e+00)
  br label %endcond

endcond:                                          ; preds = %falseexp33, %trueexp25
  %condval = phi double [ %calltmp32, %trueexp25 ], [ %calltmp53, %falseexp33 ]
  br label %endcond54

endcond54:                                        ; preds = %endcond, %trueexp
  %condval55 = phi double [ %calltmp23, %trueexp ], [ %condval, %endcond ]
  ret double %condval55
}

