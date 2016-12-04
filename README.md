# ECMA-C-Compiler

---

위 파일은 simple 컴파일러 제작 프로젝트로, javascript 구문을 기반으로 한 C Compiler 입니다.

---

### 실행

---

    flex ast.l
    bison ast.y
    gcc lex.yy.c y.tab.c
    ./a.out <filename>

---

### 제작자

---


* 부산대학교 정승현 [https://github.com/seunggu](https://github.com/seunggu)
* 부산대학교 구진현 [https://github.com/koocci](https://github.com/koocci)
