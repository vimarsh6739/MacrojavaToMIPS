class Test7 {
 public static void main(String[] a) {
  System.out.println(new TestClass().TestMethod());
 }
}
class TestClass {
 int i;
 int j;
 public int TestMethod() {
  i = 0;
  j = 0;
  while (i <= 10) {
   i = i + 1;
   j = j + 2;
  }
  return j;
 }
}