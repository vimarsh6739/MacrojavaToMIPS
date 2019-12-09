// Valid

class Extend12 {
    public static void main(String[] a) {
        System.out.println(new A().go());
    }
}

class A {
    public int go() {
        Class1 c1;
        Class2 c2;
        Class3 c3;
        Class1 c1_2;
        Class1 c1_3;
        Class2 c2_3;
        int x;
        c2 = new Class2(); 
        c1 = c2.DMethod();
        return 1337;
    }
}

class Class1 {
    public int AMethod() {
        return 0;
    }

    public int BMethod() {
        return 1;
    }

    public int CMethod() {
        return 2;
    }
}

class Class2 extends Class1 {
    public int BMethod() {
        return 3;
    }

    public Class1 DMethod() {
        return new Class3();
    }
}

class Class3 extends Class1{
    public int AMethod() {
        return 7;
    }

    public int FMethod() {
        return 6;
    }
}
