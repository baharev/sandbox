const int LOOP_BOUND = 2000000000;

__attribute__((noinline))
static int add(const int& x, const int& y) {
    return x + y;
}

__attribute__((noinline))
static int work(int xval, int yval) {
    int sum(0);
    for (int i=0; i<LOOP_BOUND; ++i) {
        int x(xval+sum);
        int y(yval+sum);
        int z = add(x, y);
        sum += z;
    }
    return sum;
}

int main(int , char* argv[]) {

    int result = work(*argv[1], *argv[2]);

    return result;
}
