class Test36 {
 public static void main(String[] a) {
  System.out.println(new TestClass().TestMethod());
 }
}
class TestClass {
 int[] array;
 public int TestMethod() {
  array = new int[10];
  array[5] = 10;
  if ((array[5]) <= 10) {
   {
    array[5] = (array[5]) + 1;
    System.out.println(array[5]);
   }
  }
  return 10;
 }
}
