declare double @sqrt(double)

declare double @printval(double, double, double)

define double @eqn2(double %a, double %b, double %c) {
entry:
  %x2 = alloca double, align 8
  %x1 = alloca double, align 8
  %delta35 = alloca double, align 8
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
  br i1 %lttest, label %truestmt, label %elsestmt

truestmt:                                         ; preds = %entry
  %delta211 = load double, ptr %delta2, align 8
  %negtmp = fneg double %delta211
  %calltmp = call double @sqrt(double %negtmp)
  store double %calltmp, ptr %delta, align 8
  %b12 = load double, ptr %b2, align 8
  %a13 = load double, ptr %a1, align 8
  %mulres14 = fmul double 2.000000e+00, %a13
  %addres = fdiv double %b12, %mulres14
  %negtmp15 = fneg double %addres
  store double %negtmp15, ptr %re, align 8
  %delta16 = load double, ptr %delta, align 8
  %a17 = load double, ptr %a1, align 8
  %mulres18 = fmul double 2.000000e+00, %a17
  %addres19 = fdiv double %delta16, %mulres18
  store double %addres19, ptr %im, align 8
  %re20 = load double, ptr %re, align 8
  %im21 = load double, ptr %im, align 8
  %calltmp22 = call double @printval(double %re20, double %im21, double 0.000000e+00)
  br label %endstmt53

elsestmt:                                         ; preds = %entry
  %delta223 = load double, ptr %delta2, align 8
  %eqtest = fcmp ueq double %delta223, 0.000000e+00
  br i1 %eqtest, label %truestmt24, label %elsestmt32

truestmt24:                                       ; preds = %elsestmt
  %b25 = load double, ptr %b2, align 8
  %a26 = load double, ptr %a1, align 8
  %mulres27 = fmul double 2.000000e+00, %a26
  %addres28 = fdiv double %b25, %mulres27
  %negtmp29 = fneg double %addres28
  store double %negtmp29, ptr %x12, align 8
  %x1230 = load double, ptr %x12, align 8
  %calltmp31 = call double @printval(double %x1230, double 0.000000e+00, double 0.000000e+00)
  br label %endstmt

elsestmt32:                                       ; preds = %elsestmt
  %delta233 = load double, ptr %delta2, align 8
  %calltmp34 = call double @sqrt(double %delta233)
  store double %calltmp34, ptr %delta35, align 8
  %b36 = load double, ptr %b2, align 8
  %negtmp37 = fneg double %b36
  %delta38 = load double, ptr %delta35, align 8
  %addres39 = fadd double %negtmp37, %delta38
  %a40 = load double, ptr %a1, align 8
  %mulres41 = fmul double 2.000000e+00, %a40
  %addres42 = fdiv double %addres39, %mulres41
  store double %addres42, ptr %x1, align 8
  %b43 = load double, ptr %b2, align 8
  %negtmp44 = fneg double %b43
  %delta45 = load double, ptr %delta35, align 8
  %subres46 = fsub double %negtmp44, %delta45
  %a47 = load double, ptr %a1, align 8
  %mulres48 = fmul double 2.000000e+00, %a47
  %addres49 = fdiv double %subres46, %mulres48
  store double %addres49, ptr %x2, align 8
  %x150 = load double, ptr %x1, align 8
  %x251 = load double, ptr %x2, align 8
  %calltmp52 = call double @printval(double %x150, double %x251, double 1.000000e+00)
  br label %endstmt

endstmt:                                          ; preds = %elsestmt32, %truestmt24
  %condval = phi double [ %calltmp31, %truestmt24 ], [ %calltmp52, %elsestmt32 ]
  br label %endstmt53

endstmt53:                                        ; preds = %endstmt, %truestmt
  %condval54 = phi double [ %calltmp22, %truestmt ], [ %condval, %endstmt ]
  ret double %condval54
}

