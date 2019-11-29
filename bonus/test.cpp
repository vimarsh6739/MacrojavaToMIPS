class Base{
	protected:
	int x1;
	int x2;
	public:
	int foo_in_base(int x){
		return x+1;
	}
};

class Derived : public Base {
	protected:
	int x2;
	int x3;
	public:
	int foo_in_d(int x){return x+1;}	
};

int main(int argc, char*argv[]){
	return sizeof(Derived);	
}


