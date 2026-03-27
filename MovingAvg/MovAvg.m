function y = MovAvg(x, N)
% MovingAverage
% Filtro de media movil simple con ventana N
%
% Entradas:
%   x : senal de entrada
%   N : tamano de ventana
%
% Salida:
%   y : senal filtrada con la misma longitud que x
%
% Nota:
% En las primeras muestras usa promedio progresivo para no perder longitud.

    x = x(:); % asegurar vector columna
    len = length(x);

    if N <= 0 || floor(N) ~= N
        error('N debe ser un entero positivo.');
    end

    y = zeros(len,1);

    for i = 1:len
        if i < N
            y(i) = mean(x(1:i));
        else
            y(i) = mean(x(i-N+1:i));
        end
    end
end