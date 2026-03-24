function data = MovAvgMain(v)
    len = length(v);
    DATA = [-1 -1 -1];
    data = [];
    valorMedio = -1;
    for i = 1:len
        DATA(3) = DATA(2);
        DATA(2) = DATA(1);
        DATA(1) = v(i);
        if(DATA(1)>0)&&(DATA(2)>0)&&(DATA(3)>0)
            valorMedio = MovAvg(DATA);
            data = [data valorMedio]; 
        end
    end
end
