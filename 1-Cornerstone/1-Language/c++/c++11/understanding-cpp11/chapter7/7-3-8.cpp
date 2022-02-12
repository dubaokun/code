int Prioritize(int );

int AllWorks(int times){
    int i;

    int x;
    try {
        for (i = 0; i < times; i++)
            x += Prioritize(i);
    }
    catch(...) {
        x = 0;
    }

    const int y = [=]{
        int i, val;
        try {
            for (i = 0; i < times; i++)
                val += Prioritize(i);
        }
        catch(...) {
            val = 0;
        }
        return val;
    }();
}
