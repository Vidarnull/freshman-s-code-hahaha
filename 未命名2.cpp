 #include <stdio.h>
 void butler(void); /* ANSI/ISO C函数原型 */
int main(void)
 {
 printf("I　will　summon　the　butler　function.\n");
 butler();
 printf("Yes.　Bring　me　some　tea　and　writeable　DVDs.\n");
 return 0;
 }
 void butler(void) /* 函数定义开始 */
 {
 printf("You　rang,　sir?\n");
 }
