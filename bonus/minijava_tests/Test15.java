class Test15 {
 public static void main(String[] a) {
  System.out.println(new TestClass().TestMethod());
 }
}
class TestClass {
 int a;
 public int TestMethod() {
  a = 10; {
   a = a + 1;
   System.out.println(a);
  }
  return 999;
 }
}
