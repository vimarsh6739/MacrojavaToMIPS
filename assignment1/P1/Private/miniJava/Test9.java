class Test9 { public static void main ( String [ ] a ) { System.out.println ( new TestClass ( ).TestMethod ( )  ) ; } }  class TestClass {   int i ; int j ; public int TestMethod ( ) {   i = 0   ; j = 0   ; while ( i  <= 10   ){ i = i  + 1   ; if ( i  <= 5   )j = j  + 2   ; else j = j  + 1   ;      }        return j   ; }    }     