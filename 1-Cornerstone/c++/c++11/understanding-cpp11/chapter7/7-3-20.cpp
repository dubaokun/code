int d = 0;

class healthyFunctor{
public:
    healthyFunctor(int d): data(d){}

    void operator () () const {}

private:
    int data;
};

int TryCapture() {
    healthyFunctor hf(d);
}

