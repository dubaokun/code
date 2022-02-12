class const_val_lambda{
    public:
        const_val_lambda(int v): val(v){}

    public:
        void operator()() const { val = 3; }

    private:
        int val;
};
