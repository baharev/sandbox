typedef unsigned int T;

const int LOOP_BOUND = 200000000;

__attribute__((noinline))
static T add(const T& x, const T& y) {

    return x + y;
}

__attribute__((noinline))
static T work(T xval, T yval) {

    T sum{0};

    for (int i=0; i<LOOP_BOUND; ++i) {

        T x{xval+sum};
        T y{yval+sum};
        T z = add(x, y);

        sum += z;
    }

    return sum;
}

int main(int , char* argv[]) {

    T result = work(*argv[1], *argv[2]);

    return result;
}
