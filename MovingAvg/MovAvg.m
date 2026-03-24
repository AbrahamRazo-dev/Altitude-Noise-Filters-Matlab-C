function ValorFiltrado = MovAvg(data)
len = length(data);
for i = 1:(len-1)
        for j = 1:(len-i)
            if (data(j) > data(j+1))
                temp = data(j);
                data(j) = data(j+1);
                data(j+1) = temp;
            end
        end
    end
ValorFiltrado = data();
end
