define double @fibo(double %n) {
entry:
  %oldb = alloca double, align 8
  %i = alloca double, align 8
  %b = alloca double, align 8
  %a = alloca double, align 8
  %n1 = alloca double, align 8
  store double %n, ptr %n1, align 8
  store double 0.000000e+00, ptr %a, align 8
  store double 1.000000e+00, ptr %b, align 8
  store double 1.000000e+00, ptr %i, align 8
  br label %condeval

condeval:                                         ; preds = %forloop, %entry
  %i2 = load double, ptr %i, align 8
  %n3 = load double, ptr %n1, align 8
  %lttest = fcmp ult double %i2, %n3
  br i1 %lttest, label %forloop, label %endloop

forloop:                                          ; preds = %condeval
  %b4 = load double, ptr %b, align 8
  store double %b4, ptr %oldb, align 8
  %a5 = load double, ptr %a, align 8
  %b6 = load double, ptr %b, align 8
  %addres = fadd double %a5, %b6
  store double %addres, ptr %b, align 8
  %ret_b = load double, ptr %b, align 8
  %oldb7 = load double, ptr %oldb, align 8
  store double %oldb7, ptr %a, align 8
  %ret_a = load double, ptr %a, align 8
  %i8 = load double, ptr %i, align 8
  %addres9 = fadd double %i8, 1.000000e+00
  store double %addres9, ptr %i, align 8
  %ret_i = load double, ptr %i, align 8
  br label %condeval

endloop:                                          ; preds = %condeval
  %b10 = load double, ptr %b, align 8
  ret double %b10
}

